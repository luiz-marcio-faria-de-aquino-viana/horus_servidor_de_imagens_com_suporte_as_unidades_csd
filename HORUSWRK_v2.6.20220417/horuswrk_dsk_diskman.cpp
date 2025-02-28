/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/08/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskDiskMan::CDskDiskMan(
    void* pRemoteUnit,
    char* dirTableFile,
    char* dirTableFilePath,
    int maxNumDskPath, 
    int maxNumRoundRobinTable,
    int maxNumDiskGroup,
    int maxNumThreads)
{
    m_pRemoteUnit = pRemoteUnit;

    init(
        dirTableFile,
        dirTableFilePath,
        maxNumDskPath, 
        maxNumRoundRobinTable,
        maxNumDiskGroup,
        maxNumThreads);
}

CDskDiskMan::~CDskDiskMan()
{
    terminate();
}

// init(): initiate disk groups
void CDskDiskMan::init(
    char* dirTableFile,
    char* dirTableFilePath,
    int maxNumDskPath, 
    int maxNumRoundRobinTable,
    int maxNumDiskGroup,
    int maxNumThreads)
{
    bigstr_t errmsg;

    //CCfgConfig* pConfig = gAppMain.getConfigPtr();

    //CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    strSetEmptyUtil(m_session);

    strNCpyUtil(m_dirTableFile, dirTableFile, PATHNAMESZ);
    sprintf(errmsg, "XII.1) CDskDiskMan::init() - DirTableFile: %s\n", m_dirTableFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);

    strNCpyUtil(m_dirTableFilePath, dirTableFilePath, PATHNAMESZ);
    sprintf(errmsg, "XII.2) CDskDiskMan::init() - DirTableFilePath: %s\n", m_dirTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);

    m_maxNumDskPath = maxNumDskPath;
    m_maxNumRoundRobinTable = maxNumRoundRobinTable;
    m_maxNumDiskGroup = maxNumDiskGroup;
    m_maxNumThreads = maxNumThreads;

    m_currDir = DBNULL_LONG;       // current directory
    
    /* INIT_DISPATCH */

    m_pDispatch = new CCmdDispatch((char*)"CCmdDispatch");

    /* INIT_SHMEM */

    m_shMem = new CDskShMem();

    /* INIT_MAIN_TABLES */

    m_pathMan = new CDskPathMan(m_maxNumDskPath, m_dirTableFile, m_dirTableFilePath);

    sprintf(errmsg, "XII.4) CDskDiskMan::init() - MaxNumDskPath: %d\n", m_pathMan->getMaxNumDskPath());
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);

    m_roundRobin = new CDskRoundRobin(m_maxNumRoundRobinTable);

    sprintf(errmsg, "XII.5) CDskDiskMan::init() - MaxNumRoundRobinTable: %d\n", m_roundRobin->getMaxNumRoundRobinTable());
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);

    m_arrDiskGroup = (CDskDiskGroupPtr_t*)allocDataArray(sizeof(CDskDiskGroupPtr_t), m_maxNumDiskGroup);
    m_currNumDiskGroup = 0;

    sprintf(errmsg, "XII.6) CDskDiskMan::init() - MaxNumDiskGroup: %d\n", m_maxNumDiskGroup);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);

    initDiskGroup();

    m_diskManExec = new CDskDiskManExec(this, m_maxNumThreads);

    sprintf(errmsg, "XII.7) CDskDiskMan::init() - MaxNumThreads: %d\n", maxNumThreads);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_DISKMAN_H, "init()", errmsg);
}

// initDiskGroup(): initiate disk groups
void CDskDiskMan::initDiskGroup()
{
    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    long numOfDiskGroup = pConfig->getCurrNumDiskGroups();
    for(long i = 0; i < numOfDiskGroup; i++) {
        CCfgDiskGroup* pCfgDiskGroup = pConfig->getDiskGroupAtPtr(i);

        CDskDiskGroup* pDiskGroup = addDiskGroup(
            pCfgDiskGroup->getOid(), 
            pCfgDiskGroup->getNumOfDisks(), 
            pCfgDiskGroup->getNumOfCopies(), 
            //pCfgDiskGroup->getNumOfSuperBlocks(),
            //pCfgDiskGroup->getNumOfBlocks(),
            //pCfgDiskGroup->getBlockSize(),
            pCfgDiskGroup->getName(), 
            pCfgDiskGroup->getSuperBlockTableFile(), 
            pCfgDiskGroup->getSuperBlockTableFilePath());

        long numOfDiskDev = pDiskGroup->getNumOfDisks();
        for(long j = 0; j < numOfDiskDev; j++) {
            CCfgDiskDev* pCfgDiskDev = pCfgDiskGroup->getDiskDevAtPtr(j);
 
            CDskDiskDev* pDiskDev = pDiskGroup->addDiskDev(
                pCfgDiskDev->getOid(),
                pCfgDiskDev->getName(),
                pCfgDiskDev->getBlockTableFile(),
                pCfgDiskDev->getDataFile(),
                pCfgDiskDev->getBlockTableFilePath(),
                pCfgDiskDev->getDataFilePath());

            m_roundRobin->addRoundRobinTableItem(
                (CCfgRemoteUnit*)m_pRemoteUnit, 
                pDiskGroup, 
                pDiskDev);
        }
    }
}

// terminate(): terminate disk groups
void CDskDiskMan::terminate()
{
    if(m_shMem != NULL)
        delete(m_shMem);
    if(m_roundRobin != NULL)
        delete(m_roundRobin);
    if(m_pathMan != NULL)
        delete(m_pathMan);
    if(m_pDispatch != NULL)
        delete((CCmdDispatch*)m_pDispatch);
    if(m_diskManExec != NULL)
        delete((CDskDiskManExec*)m_diskManExec);

    if(m_arrDiskGroup != NULL) {
        for(int i = 0; i < m_currNumDiskGroup; i++) {
            CDskDiskGroup* p = m_arrDiskGroup[i];
            p->terminate();
        } 
        freeDataArray(m_arrDiskGroup);
    }
}

/* Methodes */

// addDiskGroup(): add new disk group
// oid - disk group oid 
// numOfDisks - number of disks
// numOfCopies - number of copies
// numOfSuperBlocks - number of superblocks
// numOfBlocks - number of blocks 
// blockSize - block size
// name - disk group name
// superBlockTableFile - superblock table file
// superBlockTableFilePath - superblock table file path
CDskDiskGroup* CDskDiskMan::addDiskGroup(
    long oid,
    long numOfDisks,
    long numOfCopies,
    //long numOfSuperBlocks,
    //long numOfBlocks,
    //long blockSize,
    char* name,
    char* superBlockTableFile,
    char* superBlockTableFilePath)
{
    CDskDiskGroup* pDiskGroup = NULL;

    if(m_currNumDiskGroup < m_maxNumDiskGroup)
    {
        pDiskGroup = new CDskDiskGroup(
            m_pRemoteUnit,
            oid,
            ((CCfgRemoteUnit*)m_pRemoteUnit)->getOid(),
            numOfDisks, 
            numOfCopies, 
            //numOfSuperBlocks,
            //numOfBlocks,
            //blockSize,
            name, 
            superBlockTableFile,
            superBlockTableFilePath);
    
        m_arrDiskGroup[m_currNumDiskGroup] = pDiskGroup;
        m_currNumDiskGroup += 1;
    }
    return pDiskGroup;
}

/* DISK MANAGER TEST */

int CDskDiskMan::testDiskMan_MakeDir(long* path_parent, long bWaitKey)
{
    // TEST DISK MANAGER - MAKE DIR

    // MKDIR: [ ROOT ]/_DATASETS
    int rscode = doMakeDir(USR_SYSTEM_UID, DBNULL_LONG, DSK_IMAGE_DAT_DSTDIR_01, & m_path_oid_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_MakeDir()");

    showListDir(DBNULL_LONG, DBTRUE, bWaitKey);

    // MKDIR: [ ROOT ]/_DATASETS/IBGE-1_25000
    rscode = doMakeDir(USR_SYSTEM_UID, m_path_oid_01, DSK_IMAGE_DAT_DSTDIR_01_01, & m_path_oid_01_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_MakeDir()");

    showListDir(m_path_oid_01, DBTRUE, bWaitKey);

    // MKDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Rio_de_Janeiro
    rscode = doMakeDir(USR_SYSTEM_UID, m_path_oid_01_01, DSK_IMAGE_DAT_DSTDIR_01_01_01, & m_path_oid_01_01_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_MakeDir()");

    (*path_parent) = m_path_oid_01_01_01;

    // MKDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Sao_Paulo
    rscode = doMakeDir(USR_SYSTEM_UID, m_path_oid_01_01, DSK_IMAGE_DAT_DSTDIR_01_01_02, & m_path_oid_01_01_02);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_MakeDir()");

    // MKDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Belo_Horizonte
    rscode = doMakeDir(USR_SYSTEM_UID, m_path_oid_01_01, DSK_IMAGE_DAT_DSTDIR_01_01_03, & m_path_oid_01_01_03);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_MakeDir()");

    showListDir(m_path_oid_01_01, DBTRUE, bWaitKey);

    m_currDir = (*path_parent);

    return RSOK;
}

int CDskDiskMan::testDiskMan_WriteLocalFile(long path_parent, long bWaitKey)
{
    bigstr_t errmsg;

    pathname_t imagePath;

    byte* data = NULL;
    long datasz = 0;

    int numOfImages = DSK_NUMOFIMAGES;

    if(DEBUG_LEVEL != DEBUG_LEVEL_00)
        numOfImages = DSK_NUMOFIMAGES_IN_DEBUGMODE;

    for(int i = 0; i < numOfImages; i++) {
        char* p_image_dat = (char*)ARR_DSK_IMAGE_DAT_FILES[i];

        strNCpyUtil(imagePath, DSK_IMAGE_DAT_SRCDIR, PATHNAMESZ);
        strNCatUtil(imagePath, p_image_dat, PATHNAMESZ);

        sprintf(errmsg, "W.1) Image File Path: %s\n", imagePath);
        warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_WriteLocalFile()", errmsg);

        dsk_path_t* p_path = NULL;
        if(m_pathMan->findItem(path_parent, p_image_dat, & p_path) != RSOK) {
            sprintf(errmsg, "W.2) Image: %s... not found in database!\n", p_image_dat);
            warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_WriteLocalFile()", errmsg);

            if(readFileUtil(imagePath, & data, & datasz) == RSOK) {
                sprintf(errmsg, "W.3) Image: %s... Size: %ld... Readed!\n", p_image_dat, datasz);
                warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_WriteLocalFile()", errmsg);

                long path_oid = DBNULL_LONG;

                int rscode = RSERR;

                int filesys_type = (DEF_DSK_MULTITHREAD_FILESYS_TYPE & DEF_DSK_WRITE_THREADS);
                if(filesys_type == DEF_DSK_WRITE_THREADS)
                    rscode = doWriteFileMT(data, datasz, path_parent, p_image_dat, USR_SYSTEM_UID, & path_oid);
                else
                    rscode = doWriteFile(data, datasz, path_parent, p_image_dat, USR_SYSTEM_UID, & path_oid);

                if(rscode == RSOK)
                    m_pathMan->debug(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_WriteLocalFile()");

                freeData(data);
            }
        }

        data = NULL;
        datasz = 0;

        showListDir(path_parent, DBTRUE, bWaitKey);
    }
    return RSOK;
}

int CDskDiskMan::testDiskMan_ReadLocalFile(long path_parent, long bWaitKey)
{
    bigstr_t errmsg;

    pathname_t imagePath;

    pathname_t shmfile;

    byte* data;
    long datasz;

    CDskShMem* pDskShMem = NULL;

    pDskShMem = new CDskShMem();
    if(pDskShMem == NULL) return RSERR;

    int numOfImages = DSK_NUMOFIMAGES;
    
    if(DEBUG_LEVEL != DEBUG_LEVEL_00)
        numOfImages = DSK_NUMOFIMAGES_IN_DEBUGMODE;

    for(int i = 0; i < numOfImages; i++) {
        char* p_image_dat = (char*)ARR_DSK_IMAGE_DAT_FILES[i];

        strNCpyUtil(imagePath, DSK_IMAGE_DAT_DSTDIR, PATHNAMESZ);
        strNCatUtil(imagePath, p_image_dat, PATHNAMESZ);

        strNCpyUtil(shmfile, DEF_SRC_IMAGE_SHMDIR, PATHNAMESZ);
        strNCatUtil(shmfile, p_image_dat, PATHNAMESZ);

        sprintf(errmsg, "F.1) Image File Path: %s\n", imagePath);
        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_ReadLocalFile()", errmsg);

        long path_oid = DBNULL_LONG;

        int rscode = RSERR;

        int fstype_READ_THREADS = (DEF_DSK_MULTITHREAD_FILESYS_TYPE & DEF_DSK_READ_THREADS);
        if(fstype_READ_THREADS == DEF_DSK_READ_THREADS) {
            rscode = doReadFileMT(& data, & datasz, path_parent, p_image_dat, USR_SYSTEM_UID, & path_oid);
            if(rscode == RSOK) {
                if(DEF_IMAGE_SRCTYPE == DEF_IMAGE_SRCTYPE_SHMEM) {
                    rscode = pDskShMem->newShMemObjectForWrite(p_image_dat, data, datasz);
                    if(rscode == RSOK) {
                        sprintf(errmsg, "F.2.1) ShMem File Created: %s\n", shmfile);
                        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_ReadLocalFile()", errmsg);
                    }
                    else {
                        sprintf(errmsg, "F.2.2) ERROR - ShMem File NOT Created: %s\n", shmfile);
                        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_ReadLocalFile()", errmsg);
                    }

                    m_pathMan->debug(DEBUG_LEVEL_11, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_ReadLocalFile(): READ_THREADS_WITH_SHMEM");
                    freeData(data);
                }
                else {
                    writeFileUtil(imagePath, data, datasz);
                    m_pathMan->debug(DEBUG_LEVEL_11, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_ReadLocalFile(): READ_THREADS");
                    freeData(data);
                }
            }
        }
        else {
            rscode = doReadFile(& data, & datasz, path_parent, p_image_dat, USR_SYSTEM_UID, & path_oid);
            if(rscode == RSOK) {
                if(DEF_IMAGE_SRCTYPE == DEF_IMAGE_SRCTYPE_SHMEM) {
                    rscode = pDskShMem->newShMemObjectForWrite(p_image_dat, data, datasz);
                    if(rscode == RSOK) {
                        sprintf(errmsg, "F.3.1) ShMem File Created: %s\n", shmfile);
                        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_ReadLocalFile()", errmsg);
                    }
                    else {
                        sprintf(errmsg, "F.3.2) ERROR - ShMem File NOT Created: %s\n", shmfile);
                        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_H, "testDiskMan_ReadLocalFile()", errmsg);
                    }

                    m_pathMan->debug(DEBUG_LEVEL_11, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_ReadLocalFile(): NOREAD_THREADS_WITH_SHMEM");
                    freeData(data);
                }
                else {
                    writeFileUtil(imagePath, data, datasz);
                    m_pathMan->debug(DEBUG_LEVEL_11, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_ReadLocalFile(): NOREAD_THREADS");
                    freeData(data);
                }
            }
        }
    }
    return RSOK;
}

int CDskDiskMan::testDiskMan_DeleteLocalFile(long path_parent, long bWaitKey)
{
    int numOfImages = DSK_NUMOFIMAGES;
    
    if(DEBUG_LEVEL != DEBUG_LEVEL_00)
        numOfImages = DSK_NUMOFIMAGES_IN_DEBUGMODE;

    for(int i = 0; i < numOfImages; i++) {
        char* p_image_dat = (char*)ARR_DSK_IMAGE_DAT_FILES[i];

        int rscode = doDeleteFile(USR_SYSTEM_UID, path_parent, p_image_dat);
        if(rscode == RSERR) return rscode;
        
        m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_DeleteLocalFile()");

        showListDir(path_parent, DBTRUE, bWaitKey);
    }
    return RSOK;
}

int CDskDiskMan::testDiskMan_UploadRemoteFile(long path_parent, long bWaitKey)
{
    return RSERR;
}

int CDskDiskMan::testDiskMan_DownloadRemoteFile(long path_parent, long bWaitKey)
{
    return RSERR;
}

int CDskDiskMan::testDiskMan_DeleteRemoteFile(long path_parent, long bWaitKey)
{
    return RSERR;
}

int CDskDiskMan::testDiskMan_RemoveDir(long bWaitKey)
{
    // TEST DISK MANAGER - REMOVE DIR

    // REMOVEDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Belo_Horizonte
    int rscode = doRemoveDir(USR_SYSTEM_UID, m_path_oid_01_01_03);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_RemoveDir()");

    showListDir(m_path_oid_01_01, DBTRUE, bWaitKey);

    // REMOVEDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Sao_Paulo
    rscode = doRemoveDir(USR_SYSTEM_UID, m_path_oid_01_01_02);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_RemoveDir()");

    showListDir(m_path_oid_01_01, DBTRUE, bWaitKey);

    // REMOVEDIR: [ ROOT ]/_DATASETS/IBGE-1_25000/Rio_de_Janeiro
    rscode = doRemoveDir(USR_SYSTEM_UID, m_path_oid_01_01_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_RemoveDir()");

    showListDir(m_path_oid_01_01, DBTRUE, bWaitKey);

    // REMOVEDIR: [ ROOT ]/_DATASETS/IBGE-1_25000
    rscode = doRemoveDir(USR_SYSTEM_UID, m_path_oid_01_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_RemoveDir()");

    showListDir(m_path_oid_01, DBTRUE, bWaitKey);

    // REMOVEDIR: [ ROOT ]/_DATASETS
    rscode = doRemoveDir(USR_SYSTEM_UID, m_path_oid_01);
    if(rscode == RSERR) return rscode;
    m_pathMan->debug(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "testDiskMan_RemoveDir()");

    showListDir(DBNULL_LONG, DBTRUE, bWaitKey);

    return RSOK;
}

int CDskDiskMan::testDiskMan()
{
    long path_parent = DBNULL_LONG;

    testDiskMan_MakeDir(& path_parent, DBFALSE);
    testDiskMan_WriteLocalFile(path_parent, DBFALSE);
    testDiskMan_ReadLocalFile(path_parent, DBFALSE);
    testDiskMan_DeleteLocalFile(path_parent, DBFALSE);
    //testDiskMan_UploadRemoteFile(path_parent, DBFALSE);
    //testDiskMan_DownloadRemoteFile(path_parent, DBFALSE);
    //testDiskMan_DeleteRemoteFile(path_parent, DBFALSE);
    testDiskMan_RemoveDir(DBFALSE);

    return RSOK;
}

/* COMMANDS */

//DIRECTORY_OPERATIONS

int CDskDiskMan::doChDir(long path_parent)
{
    m_currDir = path_parent;
    return RSOK;
}

int CDskDiskMan::doMakeDir(long uid, long path_parent, char* path_name, long* path_oid)
{
    int rscode = RSERR;

    dsk_path_t* pParentPath;
    if( (path_parent == DBNULL_LONG) || (m_pathMan->findItem(path_parent, & pParentPath) == RSOK) )
    {
        rscode = m_pathMan->addItem(
            path_name,
            (char*)DBNULL_STR,
            DEF_DSK_PATHTYPE_DIR,
            DBNULL_LONG,
            path_parent,
            DBNULL_LONG,
            DBNULL_LONG,
            DBNULL_LONG,
            uid,
            path_oid);
    }
    return rscode;
}

int CDskDiskMan::doRemoveDir(long uid, long path_oid)
{
    if(m_currDir == path_oid) 
        m_currDir = DBNULL_LONG;

    int rscode = m_pathMan->deleteItem(path_oid, uid);
    return rscode;
}

int CDskDiskMan::doRemoveDir(long uid, long path_parent, char* path_name)
{
    int rscode = RSERR;

    dsk_path_t* pParentPath;
    if(m_pathMan->findItem(path_parent, path_name, & pParentPath) == RSOK) {
        if(m_currDir == pParentPath->oid) 
            m_currDir = DBNULL_LONG;

        rscode = m_pathMan->deleteItem(pParentPath->oid, uid);
    }
    return rscode;
}

int CDskDiskMan::doListDir(dsk_path_t** data, long* datasz, long path_parent, long bDeleted)
{
    int rscode = m_pathMan->findAllChildByPathParent(data, datasz, path_parent, bDeleted);
    return rscode;
}

int CDskDiskMan::doListDir(dsk_path_t** data, long* datasz, long path_parent, char* path_name, long bDeleted)
{
    int rscode = RSERR;

    dsk_path_t* pCurrPath;
    if(m_pathMan->findItem(path_parent, path_name, & pCurrPath) == RSOK)
        rscode = doListDir(data, datasz, pCurrPath->oid, bDeleted);
    return rscode;
}

int CDskDiskMan::showListDir(long path_parent, long bDeleted, long bWaitKey)
{
    bigstr_t strmsg;

    dsk_path_t* data;
    long datasz;

    dsk_path_t* pCurrPath;
    if(m_pathMan->findItem(path_parent, & pCurrPath) == RSOK) {
        printf("\nList entries in directory: %s\n\n", pCurrPath->path_name);
    }
    else {
        printf("\nList entries in directory: [ ROOT ]\n\n");
    }

    if(doListDir(& data, & datasz, path_parent, bDeleted) == RSOK)
    {
        dsk_path_t* p = NULL;
        for(int i = 0; i < datasz; i++) 
        {
            p = & data[i];

            if((bDeleted != DBTRUE) && (p->is_deleted == DBTRUE)) continue;

            if(p->is_deleted == DBTRUE) {
                if(p->path_type == DEF_DSK_PATHTYPE_DIR) {
                    sprintf(
                        strmsg, 
                        DEF_DSK_PATHFMT_DELETEDPATH, 
                        i, 
                        p->path_name);
                }
                else if(p->path_type == DEF_DSK_PATHTYPE_FILE) {
                    sprintf(
                        strmsg, 
                        DEF_DSK_PATHFMT_DELETEDFILE, 
                        i, 
                        p->path_name, 
                        p->modify_date, 
                        p->data_size);
                }
            }
            else {
                if(p->path_type == DEF_DSK_PATHTYPE_DIR) {
                    sprintf(
                        strmsg, 
                        DEF_DSK_PATHFMT_ACTIVEPATH, 
                        i, 
                        p->path_name);
                }
                else if(p->path_type == DEF_DSK_PATHTYPE_FILE) {
                    sprintf(
                        strmsg, 
                        DEF_DSK_PATHFMT_ACTIVEFILE, 
                        i, 
                        p->path_name, 
                        p->modify_date, 
                        p->data_size);
                }
            }
            printf(strmsg);
        }  
        printf("\n\n");
    }
    freeDataArray(data);

    if(DEBUG_LEVEL != DEBUG_LEVEL_00) {
        if(datasz > 0) 
            showMessage("DIRECTORY LISTED", bWaitKey);
    }

    return RSOK;
}

//FILE_OPERATIONS

int CDskDiskMan::doFileExist(long path_oid, dsk_path_t* pCurrPath)
{
    int rscode = m_pathMan->findItem(path_oid, & pCurrPath);
    return rscode;
}

int CDskDiskMan::doFileExist(long path_parent, char* path_name, dsk_path_t* pCurrPath)
{
    int rscode = m_pathMan->findItem(path_parent, path_name, & pCurrPath);
    return rscode;
}

int CDskDiskMan::doDeleteFile(long uid, long path_oid)
{
    dsk_path_t* pCurrPath;

    int rscode = m_pathMan->findItem(path_oid, & pCurrPath);
    if(rscode == RSERR) return RSERR;

    CDskDiskGroup* pDiskGroup = this->getDiskGroupPtr(pCurrPath->disk_group);

    CDskSuperBlockMan* pCurrSuperBlockMan = pDiskGroup->getSuperBlockMan();
    rscode = pCurrSuperBlockMan->deleteAllItemByPathOid(path_oid, uid);
    //if(rscode == RSERR) return RSERR;

    rscode = m_pathMan->deleteItem(path_oid, uid);
    if(rscode == RSERR) return RSERR;

    return rscode;
}

int CDskDiskMan::doDeleteFile(long uid, long path_parent, char* path_name)
{
    int rscode = RSERR;

    dsk_path_t* pCurrPath;
    rscode = m_pathMan->findItem(path_parent, path_name, & pCurrPath);
    if(rscode == RSOK) {
        rscode = doDeleteFile(uid, pCurrPath->oid);
    }
    return rscode;
}

int CDskDiskMan::doCopyFile(long uid, long spath_parent, char* spath_name, long dpath_parent, char* dpath_name, long* dpath_oid)
{
    int rscode = RSERR;

    dsk_path_t* pDestPath;
    if(m_pathMan->findItem(dpath_parent, & pDestPath) == RSOK) {
        dsk_path_t* pCurrPath;
        if(m_pathMan->findItem(spath_parent, spath_name, & pCurrPath) == RSOK) {
            str_t dpath_ext;
            getFileExt(dpath_name, STRSZ, dpath_ext, STRSZ);

            rscode = m_pathMan->addItem(
                dpath_name,
                dpath_ext,
                pCurrPath->path_type,
                pCurrPath->disk_group,
                dpath_parent,
                pCurrPath->block_start,
                pCurrPath->block_qty,
                pCurrPath->data_size,
                uid,
                dpath_oid);

            if(rscode == RSOK) {
                CDskDiskGroup* pDiskGroup = this->getDiskGroupPtr(pCurrPath->disk_group);

                CDskSuperBlockMan* pCurrSuperBlockMan = pDiskGroup->getSuperBlockMan();
                rscode = pCurrSuperBlockMan->copyAllItemByPathOid(pCurrPath->oid, dpath_parent, (*dpath_oid), uid);
            }
        }
    }
    return rscode;
}

int CDskDiskMan::doMoveFile(long uid, long spath_parent, char* spath_name, long dpath_parent, char* dpath_name)
{
    int rscode = RSERR;

    dsk_path_t* pDestPath;
    if(m_pathMan->findItem(dpath_parent, & pDestPath) == RSOK) {
        dsk_path_t* pCurrPath;
        if(m_pathMan->findItem(spath_parent, spath_name, & pCurrPath) == RSOK) {
            pCurrPath->path_parent = pDestPath->oid;
            strNCpyUtil(pCurrPath->path_name, dpath_name, STRSZ);
            rscode = RSOK;
        }
    }
    return rscode;
}

int CDskDiskMan::doRenameFile(long uid, long spath_parent, char* spath_name, char* dpath_name)
{
    int rscode = doMoveFile(uid, spath_parent, spath_name, spath_parent, dpath_name);
    return rscode;
}

int CDskDiskMan::doWriteFile(
    byte* data, 
    long datasz, 
    long path_parent, 
    char* path_name, 
    long uid, 
    long* path_oid)
{
    int rscode = RSERR;

    bigstr_t errmsg;

    byte* tmp_data;
    long tmp_datasz;

    //CCfgConfig* pConfig = gAppMain.getConfigPtr();
    //
    //CCfgRemoteUnit* pRemoteUnit = pConfig->getCurrRemoteUnitPtr();
    //long remoteUnitOid = pRemoteUnit->getOid();
    //
    //long diskGroupOid = m_roundRobin->getDiskGroupWithMinNumBlocksByRemoteUnitOid(remoteUnitOid);
    //if(diskGroupOid == -1) return RSERR;
    //
    //CDskDiskGroup* pDiskGroup = getDiskGroupPtr(diskGroupOid);
    
    CDskDiskGroup* pDiskGroup = getDiskGroupAtPtr(0);
    long diskGroupOid = pDiskGroup->getOid();
    if(diskGroupOid == -1) return RSERR;

    CDskSuperBlockMan* pCurrSuperBlockMan = pDiskGroup->getSuperBlockMan();

    long blockSize = DEF_DSK_BLOCKSIZE;
    byte* blockbuf = (byte*)allocDataArray(sizeof(byte), blockSize);
    if(blockbuf != NULL) {
        long numBlocks = datasz / blockSize;
        if((datasz % blockSize) > 0)
            numBlocks += 1;

        str_t path_ext;
        getFileExt(path_name, STRSZ, path_ext, STRSZ);

        sprintf(
            errmsg, 
            "\nZ.1) Write Image Path: %s, Ext: %s, PathType: %ld, DiskGroupOid: %ld, PathParent: %ld, StartBlock: %ld, NumBlocks: %ld, DataSize: %ld, Uid: %ld\n",
            path_name,
            path_ext,
            DEF_DSK_PATHTYPE_FILE,
            diskGroupOid,
            path_parent,
            0L,
            numBlocks,
            datasz,
            uid);
        warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

        rscode = m_pathMan->addItem(
            path_name,
            path_ext,
            DEF_DSK_PATHTYPE_FILE,
            diskGroupOid,
            path_parent,
            0L,
            numBlocks,
            datasz,
            uid,
            path_oid);

        if(rscode == RSOK) 
        {
            sprintf(
                errmsg, 
                "\nZ.2) Write Image Path: %s, Ext: %s... Added!",
                path_name,
                path_ext);
            warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

            for(long i = 0; i < numBlocks; i++) 
            {
                sprintf(errmsg, "\nZ.2.1) Starting Write Image Block: %ld... ", i);
                warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

                dsk_roundrobin_t* p = m_roundRobin->getEntryWithMinNumBlocksByDiskGroupOidPtr(pDiskGroup->getOid());
                
                sprintf(
                    errmsg, 
                    "\nZ.2.2) Round Robin Entry - Oid: %ld, RemoteUnit: %ld, DiskGroup: %ld, DiskDev: %ld, Sector: %ld, LastUpdate: %ld, NumBlocks: %ld ",
                    p->oid,
                    p->remoteunit_oid,
                    p->diskgroup_oid,
                    p->diskdev_oid,
                    p->diskdev_sector,
                    p->last_update,
                    p->num_blocks);
                warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

                CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevPtr(p->diskdev_oid);
                //CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevAtPtr(0);
                if(pDiskDev != NULL)
                {
                    sprintf(
                        errmsg, 
                        "\nZ.2.3) DiskDev - Oid: %ld, RemoteUnit: %ld, DiskGroup: %ld ",
                        pDiskDev->getOid(),
                        pDiskDev->getRemoteUnitOid(),
                        pDiskDev->getDiskGroupOid());
                    warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

                    dsk_superblock_t* p_sblock = NULL;
                    long sblock_oid = DBNULL_LONG;

                    dsk_block_t* p_block = NULL;
                    long block_oid = DBNULL_LONG;
                    long block_sector = DBNULL_LONG;

                    long block_num = i;

                    long pos_I = i * blockSize;
                    long pos_F = pos_I + blockSize;
                    if(pos_F > datasz)
                        pos_F = datasz;

                    tmp_data = & data[pos_I];
                    tmp_datasz = pos_F - pos_I;

                    memSetNullUtil(blockbuf, blockSize);
                    memNCpyUtil(blockbuf, tmp_data, tmp_datasz);

                    rscode = pDiskDev->writeBlock(
                        (*path_oid),
                        block_num, 
                        blockSize,
                        blockbuf, 
                        & p_block,
                        & block_oid,
                        & block_sector);
                    
                    if(rscode == RSOK) {
                        sprintf(errmsg, 
                                "\nZ.2.4) Block - Oid: %ld, BlockNum: %ld, BlockSector: %ld ",
                                block_oid,
                                block_num,
                                block_sector);
                        warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);

                        rscode = pCurrSuperBlockMan->findFirstFreeSuperBlock(
                                pDiskGroup->getOid(), 
                                pDiskDev->getOid(), 
                                (*path_oid), 
                                block_num,
                                block_sector,
                                uid, 
                                & p_sblock, 
                                & sblock_oid);
                            
                        if(rscode == RSOK ) {
                            sprintf(errmsg, 
                                "\nZ.2.5) SuperBlock - Oid: %ld, BlockOid: %ld, BlockNum: %ld, BlockSector: %ld ",
                                sblock_oid,
                                block_oid,
                                block_num,
                                block_sector);
                            warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doWriteFile()", errmsg);
                        }
                    }
                }
            }

            freeDataArray(blockbuf);
        }
    }
    return rscode;
}

int CDskDiskMan::doWriteFileMT(
    byte* data, 
    long datasz, 
    long path_parent, 
    char* path_name, 
    long uid, 
    long* path_oid)
{
    int rscode = RSERR;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    long posDiskGroup = 0;
    CDskDiskGroup* pDiskGroup = getDiskGroupAtPtr(posDiskGroup);

    long diskGroupOid = pDiskGroup->getOid();
    long num_diskdev = pDiskGroup->getCurrNumDiskDev();
        
    long blockSize = DEF_DSK_BLOCKSIZE;    
    long numBlocks = datasz / blockSize;
    if((datasz % blockSize) > 0)
        numBlocks += 1;

    long numBlocksPart = numBlocks / num_diskdev;
    long remNumBlockPart = numBlocks % num_diskdev;

    long lastNumBlockPart = numBlocksPart + remNumBlockPart;

    //long lastNumBlockPart = numBlocksPart;
    //if(remNumBlockPart > 0)
    //    lastNumBlockPart = numBlocksPart + remNumBlockPart;

    long posLastDiskDev = num_diskdev - 1;

    long thread_group = getCurrentTimestamp();

    str_t path_ext;
    getFileExt(path_name, STRSZ, path_ext, STRSZ);

    rscode = m_pathMan->addItem(
        path_name,
        path_ext,
        DEF_DSK_PATHTYPE_FILE,
        diskGroupOid,
        path_parent,
        0L,
        numBlocks,
        datasz,
        uid,
        path_oid);

    if(rscode == RSOK) 
    {
        //START THREADS

        long startBlockPart = 0;
        for(long i = 0; i < num_diskdev; i++) 
        {
            long thread_id = (thread_group * DEF_DSK_INIT_THREADID) + i;

            long currNumBlocksPart = numBlocksPart;
            if(posLastDiskDev == i)
                currNumBlocksPart = lastNumBlockPart;

            //long startBlockPart = i * currNumBlocksPart;
            //long endBlockPart = startBlockPart + currNumBlocksPart;

            int posDiskDev = i;
            CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevAtPtr(posDiskDev);

            if(pDiskDev != NULL) 
            {
                dsk_diskman_thread_t* pThread = m_diskManExec->addWriteThread(
                    pRemoteUnit,
                    pDiskGroup,
                    pDiskDev,
                    path_parent,
                    (*path_oid),
                    thread_group,
                    thread_id,
                    uid,
                    startBlockPart,
                    currNumBlocksPart,
                    data,
                    datasz);

                if(pThread == NULL)
                    errMsg(__HORUSWRK_DSK_DISKMAN_H, "doWriteFileMT()", ERR_CANTEXECDISKMANWRITETHREAD);

                startBlockPart += currNumBlocksPart;
            }
        }

        //JOIN THREADS - WAIT FOR COMPLETE!

        m_diskManExec->waitThreadGroup(thread_group, DEF_DSK_THREAD_TYPE_WRITE);
        m_diskManExec->resetAllThreadsByGroup(thread_group);
    }

    return rscode;
}

int CDskDiskMan::doReadFile(
    byte** data, 
    long* datasz, 
    long path_parent, 
    char* path_name,
    long uid, 
    long* path_oid)
{
    bigstr_t errmsg;

    int rscode = RSERR;

    dsk_superblock_t* sblock_data;
    long sblock_datasz;

    dsk_block_t* block_data;
    long block_oid;
    long block_sector;

    sprintf(
        errmsg, 
        "\nY.1) Read Image - PathParent: %ld, PathName: %s\n",
        path_parent, 
        path_name);
    warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doReadFile()", errmsg);

    dsk_path_t* p_path = NULL; 
    if(m_pathMan->findItem(path_parent, path_name, & p_path) == RSOK) {
        sprintf(
            errmsg, 
            "\nY.2) Read Image - PathOid: %ld, DiskGroup: %ld, PathParent: %ld, PathType: %ld, IsDeleted: %ld, BlockStart: %ld, BlockQty: %ld, DataSize: %ld, PathName: %s, PathExt: %s\n",
            p_path->oid,
            p_path->disk_group,
            p_path->path_parent,
            p_path->path_type,
            p_path->is_deleted,
            p_path->block_start,
            p_path->block_qty,
            p_path->data_size,
            p_path->path_name,
            p_path->path_ext);
        warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doReadFile()", errmsg);

        (*path_oid) = p_path->oid;

        CDskDiskGroup* pDiskGroup = getDiskGroupPtr(p_path->disk_group);
        if(pDiskGroup != NULL) {
            CDskSuperBlockMan* pCurrSuperBlockMan = pDiskGroup->getSuperBlockMan();
            if(pCurrSuperBlockMan->findAllByPathOid(p_path->oid, & sblock_data, & sblock_datasz) == RSOK) {
                sprintf(
                    errmsg, 
                    "\nY.3) Read Image - SuperBlock Data Size: %ld\n",
                    sblock_datasz);
                warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doReadFile()", errmsg);

                (*datasz) = p_path->data_size;
                (*data) = (byte*)allocData(*datasz);

                long blockSize = DEF_DSK_BLOCKSIZE;
                byte* blockbuf = (byte*)allocDataArray(sizeof(byte), blockSize);
                if(blockbuf != NULL) {
                    for(long i = 0; i < sblock_datasz; i++) {
                        dsk_superblock_t* p_sblock = & sblock_data[i];
                        sprintf(
                            errmsg, 
                            "\nY.4) Read Image - SuperBlockOid: %ld, DiskGroup: %ld, DiskDev: %ld, PathOid: %ld, BlockNum: %ld, IsDeleted: %ld\n",
                            p_sblock->oid, 
                            p_sblock->disk_group, 
                            p_sblock->disk_dev, 
                            p_sblock->path_oid, 
                            p_sblock->block_num, 
                            p_sblock->is_deleted);
                        warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doReadFile()", errmsg);

                        if(p_sblock->is_deleted != DBTRUE) {
                            long block_num = p_sblock->block_num;

                            long pos_I = block_num * blockSize;
                            long pos_F = pos_I + blockSize;
                            if(pos_F > (*datasz))
                                pos_F = (*datasz);

                            long tmp_datasz = pos_F - pos_I;
                            byte* tmp_data = & (*data)[pos_I];

                            long diskDevOid = p_sblock->disk_dev;
                            CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevPtr(diskDevOid);
                            if(pDiskDev != NULL) {
                                sprintf(
                                    errmsg, 
                                    "\nY.5) Read Image - BlockNum: %ld, BlockSize: %ld\n",
                                    block_num, 
                                    blockSize);
                                warnMsg(DEBUG_LEVEL_09, __HORUSWRK_DSK_DISKMAN_H, "doReadFile()", errmsg);

                                rscode = pDiskDev->readBlock(
                                    (*path_oid),
                                    block_num,
                                    blockSize,
                                    blockbuf, 
                                    & block_data,
                                    & block_oid,
                                    & block_sector);
                                if(rscode == RSERR) return rscode;

                                memSetNullUtil(tmp_data, tmp_datasz);
                                memNCpyUtil(tmp_data, blockbuf, tmp_datasz);
                            }
                        }
                    }
                }
            }
        }
    }
    return rscode;
}

int CDskDiskMan::doReadFileMT(
    byte** data, 
    long* datasz, 
    long path_parent, 
    char* path_name, 
    long uid, 
    long* path_oid)
{
    int rscode = RSERR;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    dsk_superblock_t* sblock_data;
    long sblock_datasz;

    long thread_group = getCurrentTimestamp();

    dsk_path_t* p_path = NULL; 
    if(m_pathMan->findItem(path_parent, path_name, & p_path) == RSOK) 
    {
        (*path_oid) = p_path->oid;

        (*datasz) = p_path->data_size;
        (*data) = (byte*)allocData(*datasz);

        CDskDiskGroup* pDiskGroup = getDiskGroupPtr(p_path->disk_group);
        if(pDiskGroup != NULL) 
        {
            CDskSuperBlockMan* pCurrSuperBlockMan = pDiskGroup->getSuperBlockMan();

            long num_diskdev = pDiskGroup->getNumOfDisks();
            for(int j = 0; j < num_diskdev; j++)
            {
                long thread_id = (thread_group * DEF_DSK_INIT_THREADID) + j;

                CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevAtPtr(j);
                long diskdev_oid = pDiskDev->getOid();

                rscode = pCurrSuperBlockMan->findAllByPathOidAndDiskDev(p_path->oid, diskdev_oid, & sblock_data, & sblock_datasz);
                if(rscode == RSOK) {
                    dsk_diskman_thread_t* pThread = m_diskManExec->addReadThread(
                        pRemoteUnit,
                        pDiskGroup,
                        pDiskDev,
                        path_parent,
                        (*path_oid),
                        thread_group,
                        thread_id,
                        uid,
                        sblock_data,
                        sblock_datasz,
                        (*data),
                        (*datasz));    

                    if(pThread == NULL)
                        errMsg(__HORUSWRK_DSK_DISKMAN_H, "doReadFileMT()", ERR_CANTEXECDISKMANWRITETHREAD);
                }
            }

            //JOIN THREADS - WAIT FOR COMPLETE!

            m_diskManExec->waitThreadGroup(thread_group, DEF_DSK_THREAD_TYPE_READ);
            m_diskManExec->resetAllThreadsByGroup(thread_group);
        }
    }

    return rscode;
}

//FILE_OPERATIONS_REQUEST

int CDskDiskMan::doReqUploadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte* data, 
    long datasz, 
    long uid, 
    long* path_oid)
{
    // int rscode = RSERR;

    // dsk_path_t* pParentPath;
    // if(m_pathMan->findItem(path_parent, & pParentPath) == RSOK) 
    // {
    //     int diskGroupOid = m_roundRobin->getDiskGroupWithMinNumBlocksPtr();
    //     if(diskGroupOid != -1) 
    //     {
    //         CDskDiskGroup* pDiskGroup = getDiskGroupPtr(diskGroupOid);
    //         if(pDiskGroup != NULL) 
    //         {
    //             str_t path_ext;
    //             getFileExt(path_name, STRSZ, path_ext, STRSZ);

    //             long block_start = 0;

    //             long blockSize = pDiskGroup->getBlockSize();

    //             long block_qty = datasz / blockSize;

    //             if((datasz % blockSize) != 0)
    //                 block_qty += 1;

    //             if(doReqWriteFile(pDiskGroup, data, datasz, block_qty, uid) == RSOK)
    //             {
    //                 rscode = m_pathMan->addItem(
    //                     path_name,
    //                     path_ext,
    //                     DEF_DSK_PATHTYPE_FILE,
    //                     path_parent,
    //                     block_start,
    //                     block_qty,
    //                     datasz,
    //                     uid,
    //                     path_oid);
    //             }
    //         }
    //     }
    // }
    // return rscode;

    return RSERR;
}

int CDskDiskMan::doReqDownloadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_oid, 
    byte** data, 
    long* datasz,
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doReqDownloadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte** data, 
    long* datasz,
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doReqWriteFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte* data, 
    long datasz, 
    long uid, 
    long* path_oid)
{
    return RSERR;
}

int CDskDiskMan::doReqReadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte** data, 
    long* datasz, 
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doReqWriteBlock(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long block_sector,
    long block_num, 
    byte* data, 
    long datasz, 
    long uid)
{
    // dsk_block_rwreq_t sblock;

    // sblock.dataType = DEF_DSK_DATATYPE_REQWRITE_BYTEARRAY;
    // sblock.oid = generateRandomOid();
    // sblock.src_remoteunit_oid = pCurrRemoteUnit->getOid();
    // sblock.dst_remoteunit_oid = pRemoteUnit->getOid();
    // sblock.disk_group_oid = pDiskGroup->getOid();
    // sblock.disk_dev_oid = pDiskDev->getOid();
    // sblock.block_sector = block_sector;
    // sblock.block_num = block_num;
    // sblock.uid = uid;
    // sblock.datasz = datasz;
    // memNCpyUtil(sblock.data, data, datasz);

    // int rscode = ((CCmdDispatch*)m_pDispatch)->sendDataMessage(
    //     pRemoteUnit->getIpAddr(), 
    //     pRemoteUnit->getInPort(), 
    //     (byte*) & sblock, 
    //     sizeof(dsk_block_rwreq_t));
    // return rscode;

    return RSERR;
}

int CDskDiskMan::doReqReadBlock(
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long block_sector,
    long block_num, 
    byte** data, 
    long* datasz, 
    long uid)
{
    return RSERR;
}

//FILE_OPERATIONS_RESPONSE

int CDskDiskMan::doRespUploadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    long datasz, 
    long uid, 
    long* path_oid)
{
    return RSERR;
}

int CDskDiskMan::doRespDownloadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_oid, 
    byte* data, 
    long datasz,
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doRespDownloadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte* data, 
    long datasz,
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doRespWriteFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    long datasz, 
    long uid, 
    long* path_oid)
{
    return RSERR;
}

int CDskDiskMan::doRespReadFile(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long path_parent, 
    char* path_name, 
    byte* data, 
    long datasz, 
    long uid)
{
    return RSERR;
}

int CDskDiskMan::doRespWriteBlock(
    CCfgRemoteUnit* pCurrRemoteUnit, 
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long block_sector,
    long block_num, 
    long datasz, 
    long uid)
{
    // //dsk_block_rwresp_t* pRespData;

    // int rscode = RSERR;

    // CCfgConfig* pConfig = gAppMain.getConfigPtr();

    // CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    // CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitPtr(pBlockData->src_remoteunit_oid);

    // CDskDiskGroup* pDiskGroup = getDiskGroupPtr(pBlockData->disk_group_oid); 

    // CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevPtr(pBlockData->disk_dev_oid);

    // if(pDiskDev->writeBlock(pBlockData) == RSOK) {
    //     rscode = doRespWriteBlock(
    //         pCurrRemoteUnit, 
    //         pRemoteUnit, 
    //         pDiskGroup, 
    //         pDiskDev,
    //         (char*)DEF_RESMSG_SUCCESS, 
    //         DEF_RESCODE_SUCCESS, 
    //         pBlockData->datasz,
    //         pBlockData->block_sector,
    //         pBlockData->block_num, 
    //         pBlockData->uid);
    // }
    // else {
    //     rscode = doRespWriteBlock(
    //         pCurrRemoteUnit, 
    //         pRemoteUnit, 
    //         pDiskGroup, 
    //         pDiskDev,
    //         (char*)DEF_RESMSG_FAIL_CANT_WRITE_BLOCK, 
    //         DEF_RESCODE_FAIL_CANT_WRITE_BLOCK, 
    //         pBlockData->datasz,
    //         pBlockData->block_sector,
    //         pBlockData->block_num, 
    //         pBlockData->uid);
    // }
    // return rscode;

    return RSERR;
}

int CDskDiskMan::doRespReadBlock(
    CCfgRemoteUnit* pRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev,
    long block_sector,
    long block_num, 
    byte* data, 
    long datasz, 
    long uid)
{
    // CCfgConfig* pConfig = gAppMain.getConfigPtr();

    // CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    // dsk_roundrobin_t* pArrRoundRobin = NULL;
    // long szArrRoundRobin = 0;

    // long blockSize = pDiskGroup->getBlockSize();

    // int rscode = m_roundRobin->getArrRoundRobinTablePtr(
    //                 & pArrRoundRobin, 
    //                 & szArrRoundRobin, 
    //                 maxBlocks, 
    //                 pDiskGroup->getOid());
    // if(rscode == RSOK)
    // {
    //     byte* p_blockBuf = data;
    //     for(int i = 0; i < maxBlocks; i++) {
    //         long pos = i % szArrRoundRobin;
    //         dsk_roundrobin_t* p = & pArrRoundRobin[pos];

    //         CDskDiskDev* pDiskDev = pDiskGroup->getDiskDevPtr(p->disk_dev_oid);

    //         CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitPtr(pDiskDev->getRemoteUnit());

    //         rscode = doReqWriteBlock(
    //                     pCurrRemoteUnit, 
    //                     pRemoteUnit, 
    //                     pDiskGroup, 
    //                     pDiskDev, 
    //                     p_blockBuf, 
    //                     blockSize, 
    //                     p->disk_dev_sector, 
    //                     i, 
    //                     uid);
    //         if(rscode == RSERR) return rscode;
    //     }
    // }
    // return rscode;

    return RSERR;
}

/* Getters/Setters */

char* CDskDiskMan::getDirTableFile()
{
    return m_dirTableFile;    
}

long CDskDiskMan::getCurrDir()
{
    return m_currDir;
}

/* PATH MANAGER */

CDskPathMan* CDskDiskMan::getPathMan()
{
    return m_pathMan;
}

int CDskDiskMan::getMaxNumDskPath()
{
    return m_maxNumDskPath;
}

/* DISK MANAGER EXECUTION */

CDskDiskManExec* CDskDiskMan::getDiskManExecPtr()
{
    return m_diskManExec;
}

/* DISK GROUP */

CDskDiskGroup* CDskDiskMan::getDiskGroupAtPtr(long pos)
{
    if(pos < m_currNumDiskGroup) {
        CDskDiskGroup* p = m_arrDiskGroup[pos];
        return p;
    }
    return NULL;
}

CDskDiskGroup* CDskDiskMan::getDiskGroupPtr(long oid)
{
    for(int i = 0; i < m_currNumDiskGroup; i++) {
        CDskDiskGroup* p = m_arrDiskGroup[i];
        if(p->getOid() == oid)
            return p;
    }
    return NULL;
}

CDskDiskGroup* CDskDiskMan::getDiskGroupPtr(char* groupName)
{
    for(int i = 0; i < m_currNumDiskGroup; i++) {
        CDskDiskGroup* p = m_arrDiskGroup[i];
        if( strNCmpCaseUtil(p->getName(), groupName, STRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 )
            return p;
    }
    return NULL;
}

int CDskDiskMan::getMaxNumDiskGroup()
{
    return m_maxNumDiskGroup;
}

int CDskDiskMan::getCurrNumDiskGroup()
{
    return m_currNumDiskGroup;
}
