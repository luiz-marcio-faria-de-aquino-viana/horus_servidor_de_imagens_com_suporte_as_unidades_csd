/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskdev.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

// DISKDEV MUTEX
pthread_mutex_t dsk_diskdev_mutex;              // disk device read/write mutext

CDskDiskDev::CDskDiskDev(
    void* pRemoteUnit,
    void* pDiskGroup,
    long oid,
    long posDiskDev,
    long remoteUnitOid,
    long diskGroupOid,
    //long numOfBlocks,
    //long blockSize,
    long lastUpdate,
    char* name,
    char* blockTableFile,
    char* dataFile,
    char* blockTableFilePath,
    char* dataFilePath)
{
    init(
        pRemoteUnit,
        pDiskGroup,
        oid,
        posDiskDev,
        remoteUnitOid,
        diskGroupOid,
        //numOfBlocks,
        //blockSize,
        lastUpdate,
        name,
        blockTableFile,
        dataFile,
        blockTableFilePath,
        dataFilePath);
}

CDskDiskDev::~CDskDiskDev()
{
    terminate();
}

// init(): initiate disk device
void CDskDiskDev::init(
    void* pRemoteUnit,
    void* pDiskGroup,
    long oid,
    long posDiskDev,    
    long remoteUnitOid,
    long diskGroupOid,
    //long numOfBlocks,
    //long blockSize,
    long lastUpdate,
    char* name,
    char* blockTableFile,
    char* dataFile,
    char* blockTableFilePath,
    char* dataFilePath)
{
    bigstr_t errmsg;

    if(pthread_mutex_init(& dsk_diskdev_mutex, NULL) != 0)  {
        sprintf(errmsg, ERR_CANTCREATEMUTEX, __HORUSWRK_DSK_DISKDEV_H); 
        errMsg(__HORUSWRK_DSK_DISKDEV_H, "init()", errmsg);
    }

    m_pRemoteUnit = pRemoteUnit;
    m_pDiskGroup = pDiskGroup;

    m_oid = oid;
    m_posDiskDev = posDiskDev;
    m_remoteUnitOid = remoteUnitOid;
    m_diskGroupOid = diskGroupOid;
    //m_numOfBlocks = numOfBlocks;
	//m_blockSize = blockSize;
    m_lastUpdate = getCurrentTimestamp();

    strNCpyUtil(m_name, name, STRSZ);
    strNCpyUtil(m_blockTableFile, blockTableFile, STRSZ);
    strNCpyUtil(m_dataFile, dataFile, STRSZ);

    strNCpyUtil(m_blockTableFilePath, blockTableFilePath, PATHNAMESZ);
    strNCpyUtil(m_dataFilePath, dataFilePath, PATHNAMESZ);

    //m_maxNumDskBlock = numOfBlocks;    
    m_blockMan = new CDskBlockMan(DEF_DSK_NUMOFBLOCKS, m_blockTableFile, m_blockTableFilePath);

}

// terminate(): terminate disk device
void CDskDiskDev::terminate()
{
    pthread_mutex_destroy(& dsk_diskdev_mutex);

    if(m_blockMan != NULL)
        delete(m_blockMan);
}

/* Methodes */

int CDskDiskDev::writeBlock(
    long path_oid,
    long block_num,
    long block_size,
    byte* blockbuf,
    dsk_block_t** p_block,
    long* block_oid,
    long* block_sector)
{
    bigstr_t errmsg;

    int rscode = RSERR;

    FILE* f = NULL;

    pthread_mutex_lock(& dsk_diskdev_mutex);

    sprintf(errmsg, "\nY.1) WriteBlock - BlockNum: %ld, Find Free Block... ", block_num);
    warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

    //long block_size = DEF_DSK_BLOCKSIZE;
    if(m_blockMan->findFirstFreeBlock(path_oid, block_num, p_block, block_oid, block_sector) == RSOK)
    {
        sprintf(errmsg, "\nY.2) WriteBlock - Found a Free Block: %ld, Block Sector: %ld ", (*block_oid), (*block_sector));
        warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

        sprintf(errmsg, "\nY.3) WriteBlock - Openning Data File: %s ", m_dataFilePath);
        warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

        if(openFileUtil(&f, m_dataFilePath, (char*)FILMODE_APPEND, DBTRUE) == RSOK) 
        {
            sprintf(errmsg, "\nY.4) WriteBlock - File: %s... Openned! ", m_dataFilePath);
            warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

            long pos = (*block_sector) * block_size;

            sprintf(errmsg, "\nY.5) WriteBlock - BlockSector: %ld, BlockSize: %ld, SeekTo: %ld... ", (*p_block)->block_sector, block_size, pos);
            warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

            if(fseek(f, pos, SEEK_SET) == 0) {
                sprintf(errmsg, "\nY.6) WriteBlock - WriteData... ");
                warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);

                fwrite(blockbuf, sizeof(byte), block_size, f);
                rscode = RSOK;

                sprintf(errmsg, "\nY.7) WriteBlock - Data Wrote! ");
                warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);
            }
            else {
                sprintf(
                        errmsg, 
                        "\nY.8) ERROR: WriteBlock - Data File: %s... BlockSector: %ld, BlockSize: %ld, SeekTo: %ld... SEEK FAILURE! ", 
                        m_dataFilePath,
                        (*p_block)->block_sector,
                        block_size, 
                        pos);
                warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);
            }
            fclose(f);

            sprintf(errmsg, "\nY.9) WriteBlock - Data File: %s... Closed! ", m_dataFilePath);
            warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);
        }
        else {
            sprintf(errmsg, "\nY.10) ERROR: WriteBlock - Data File: %s... OPEN FAILURE! ", m_dataFilePath);
            warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);
        }
    }
    else {
        sprintf(errmsg, "\nY.11) ERROR: WriteBlock - Data File: %s... CAN'T FIND ANY FREE BLOCK! ", m_dataFilePath);
        warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "writeBlock()", errmsg);
    }

    pthread_mutex_unlock(& dsk_diskdev_mutex);

    return rscode;
}

int CDskDiskDev::readBlock(
    long path_oid,
    long block_num,
    long block_size,
    byte* blockbuf,
    dsk_block_t** p_block,
    long* block_oid,
    long* block_sector)
{
    bigstr_t errmsg;

    int rscode = RSERR;

    (*block_oid) = DBNULL_LONG;

    FILE* f = NULL;

    pthread_mutex_lock(& dsk_diskdev_mutex);

    //long block_size = DEF_DSK_BLOCKSIZE;
    sprintf(
        errmsg, 
        "\nK.1) ReadBlock - PathOid: %ld, BlockNum: %ld, BlockSize: %ld\n",
        path_oid,
        block_num, 
        block_size);
    warnMsg(DEBUG_LEVEL_04, __HORUSWRK_DSK_DISKMAN_H, "readBlock()", errmsg);

    if(m_blockMan->findBlockByBlockNum(path_oid, block_num, p_block, block_oid, block_sector) == RSOK)
    {
        sprintf(
            errmsg, 
            "\nK.2) ReadBlock - BlockOid: %ld, PathOid: %ld, BlockNum: %ld, BlockSector: %ld, IsValid: %ld\n",
            (*p_block)->oid,
            (*p_block)->path_oid,
            (*p_block)->block_num,
            (*p_block)->block_sector,
            (*p_block)->is_valid);
        warnMsg(DEBUG_LEVEL_04, __HORUSWRK_DSK_DISKMAN_H, "readBlock()", errmsg);

        if(openFileUtil(&f, m_dataFilePath, (char*)FILMODE_READ, DBTRUE) == RSOK) 
        {
            sprintf(errmsg, "\nK.3) ReadBlock - File: %s... Openned! ", m_dataFilePath);
            warnMsg(DEBUG_LEVEL_04, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);

            long pos = (*block_sector) * block_size;

            if(fseek(f, pos, SEEK_SET) == 0) {
                sprintf(
                    errmsg, 
                    "\nK.4) ReadBlock - BlockSector: %ld, BlockSize: %ld, SeekTo: %ld... ", 
                    (*p_block)->block_sector,
                    block_size, 
                    pos);
                warnMsg(DEBUG_LEVEL_05, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);

                fread(blockbuf, sizeof(byte), block_size, f);
                rscode = RSOK;

                sprintf(errmsg, "\nK.5) ReadBlock - Data Readed! ");
                warnMsg(DEBUG_LEVEL_04, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);
            }
            else {
                sprintf(
                        errmsg, 
                        "\nK.6) ERROR: ReadBlock - Data File: %s... BlockSector: %ld, BlockSize: %ld, SeekTo: %ld... SEEK FAILURE! ", 
                        m_dataFilePath,
                        (*p_block)->block_sector,
                        block_size, 
                        pos);
                warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);
            }
            fclose(f);

            sprintf(errmsg, "\nK.7) ReadBlock - Data File: %s... Closed! ", m_dataFilePath);
            warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);
        }
        else {
            sprintf(errmsg, "\nK.8) ERROR: ReadBlock - Data File: %s... OPEN FAILURE! ", m_dataFilePath);
            warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);
        }
    }
    else {
        sprintf(errmsg, "\nK.9) ERROR: ReadBlock - Data File: %s... CAN'T FIND ANY FREE BLOCK! ", m_dataFilePath);
        warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKDEV_H, "readBlock()", errmsg);
    }

    pthread_mutex_unlock(& dsk_diskdev_mutex);

    return rscode;    
}

/* Getters/Setters */

void* CDskDiskDev::getRemoteUnitPtr()
{
    return m_pRemoteUnit;
}

void* CDskDiskDev::getDiskGroupPtr()
{
    return m_pDiskGroup;
}

long CDskDiskDev::getOid()
{
    return m_oid;
}

long CDskDiskDev::getPosDiskDev()
{
    return m_posDiskDev;
}

long CDskDiskDev::getRemoteUnitOid()
{
    return m_remoteUnitOid;
}

long CDskDiskDev::getDiskGroupOid()
{
    return m_diskGroupOid;
}

//long CDskDiskDev::getNumOfBlocks()
//{
//    return m_numOfBlocks;
//}

//long CDskDiskDev::getBlockSize()
//{
//    return m_blockSize;
//}

long CDskDiskDev::getLastUpdate()
{
    return m_lastUpdate;
}

char* CDskDiskDev::getName()
{
    return m_name;
}

char* CDskDiskDev::getBlockTableFile()
{
    return m_blockTableFile;
}

char* CDskDiskDev::getDataFile()
{
    return m_dataFile;
}

char* CDskDiskDev::getBlockTableFilePath()
{
    return m_blockTableFilePath;
}

char* CDskDiskDev::getDataFilePath()
{
    return m_dataFilePath;
}

//int CDskDiskDev::getMaxNumDskBlock()
//{
//    return m_maxNumDskBlock;
//}

CDskBlockMan* CDskDiskDev::getDskBlockMan()
{
    return m_blockMan;
}
