/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_superblockman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

// SUPERBLOCK MUTEX
pthread_mutex_t m_superblock_mutex;

CDskSuperBlockMan::CDskSuperBlockMan(int maxNumDskSuperBlock, char* superBlockTableFile, char* superBlockTableFilePath)
{
    init(maxNumDskSuperBlock, superBlockTableFile, superBlockTableFilePath);
}

CDskSuperBlockMan::~CDskSuperBlockMan()
{
    terminate();
}

// init(): initiate block manager
void CDskSuperBlockMan::init(int maxNumDskSuperBlock, char* superBlockTableFile, char* superBlockTableFilePath)
{
    bigstr_t errmsg;

    if(pthread_mutex_init(& m_superblock_mutex, NULL) != 0)  {
        sprintf(errmsg, ERR_CANTCREATEMUTEX, __HORUSWRK_DSK_SUPERBLOCKMAN_H); 
        errMsg(__HORUSWRK_DSK_SUPERBLOCKMAN_H, "init()", errmsg);
    }

    strNCpyUtil(m_superBlockTableFile, superBlockTableFile, BIGSTRSZ);
    strNCpyUtil(m_superBlockTableFilePath, superBlockTableFilePath, PATHNAMESZ);

    sprintf(
        errmsg, 
        "\nX.I) CDskSuperBlockMan::init() - SuperBlockTableFile: %s, SuperBlockTableFilePath: %s... ", 
        m_superBlockTableFile,
        m_superBlockTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "init()", errmsg);

    m_maxNumDskSuperBlock = maxNumDskSuperBlock; 
    m_currNumDskSuperBlock = 0; 
    m_arrDskSuperBlock = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), m_maxNumDskSuperBlock);

    m_pSuperBlockIndex = new CDskSuperBlockIdx(DEF_DSK_MAX_NUMOFSUPERBLOCKSINDEX);

    loadFile(m_superBlockTableFilePath);

}

// term(): terminate block manager
void CDskSuperBlockMan::terminate()
{
    saveFile(m_superBlockTableFilePath);

    pthread_mutex_destroy(& m_superblock_mutex);

    if(m_pSuperBlockIndex != NULL)
        delete(m_pSuperBlockIndex);

    freeDataArray(m_arrDskSuperBlock);
}

/* Methodes */

// loadFile(): load table of superblocks from file
// fileName - block's table file name
int CDskSuperBlockMan::loadFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    pthread_mutex_lock(& m_superblock_mutex);

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_superblock_t);

        m_currNumDskSuperBlock = 0;
        while(m_currNumDskSuperBlock < m_maxNumDskSuperBlock)
        {
            dsk_superblock_t* p = & m_arrDskSuperBlock[m_currNumDskSuperBlock];
            if(fread(p, sizeof(byte), size, f) == 0) break;

            m_pSuperBlockIndex->addIndexItem(p->path_oid, p);
            m_currNumDskSuperBlock += 1;
        }
        fclose(f);

        sprintf(errmsg, "\nSuperBlock Table File: %s... loaded!", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "loadFile()", errmsg);
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    return rscode;
}

// saveFile(): save table of superblocks to file
// fileName - block's table file name
int CDskSuperBlockMan::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    pthread_mutex_lock(& m_superblock_mutex);

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_superblock_t);
        for(int i = 0; i < m_currNumDskSuperBlock; i++)
        {
            dsk_superblock_t* p = &m_arrDskSuperBlock[i];

            long num_write = fwrite(p, sizeof(byte), size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "saveFile()", errmsg);
        }
        fclose(f);

        sprintf(errmsg, "\nSuperBlock Table File: %s... saved!", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "saveFile()", errmsg);
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    return rscode;
}

// addItem(): add item to superblock table
// disk_group - disk device group
// disk_dev - disk device oid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector at disk device
// incr_read_val - increment read value
// incr_write_val - increment write value
// uid - user id
// superblock_oid - return superblock oid
int CDskSuperBlockMan::addItem(
    long disk_group,
    long disk_dev,
    long path_oid,
    long block_num,
    long block_sector,
    long incr_read_val,
    long incr_write_val,
    long uid,
    long* superblock_oid)
{
    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    dsk_superblock_t* data = NULL;

    str_t key;
    sprintf(key, "%ld_%ld", path_oid, block_num);

    if(findItem(key, &data) != RSOK)
    {
        pthread_mutex_lock(& m_superblock_mutex);

        data = &(m_arrDskSuperBlock[m_currNumDskSuperBlock]);

        (*superblock_oid) = seq->nextVal((char*)SEQ_TABLE_BLOCK);
            
        m_currNumDskSuperBlock += 1;

        /* Add new item
         */
        setItemData_NotThreadSafe(
            &data, 
            (*superblock_oid),
            disk_group,
            disk_dev,
            path_oid,
            block_num,
            block_sector,
            incr_read_val,
            incr_write_val,
            currTimestamp,
            uid,
            currTimestamp,
            uid,
            DBTRUE,
            DBNULL_LONG,
            DBNULL_LONG,
            DBFALSE,
            key);

        pthread_mutex_unlock(& m_superblock_mutex);
    }
    else
    {
        pthread_mutex_lock(& m_superblock_mutex);

        /* Update existent item
         */
        data->block_sector = block_sector;
        data->read_count = data->read_count + incr_read_val;
        data->write_count = data->write_count + incr_write_val;
        data->modify_date = currTimestamp;
        data->modify_uid = uid;
        data->is_modified = DBTRUE;

        (*superblock_oid) = data->oid;

        pthread_mutex_unlock(& m_superblock_mutex);
    }

    m_pSuperBlockIndex->addIndexItem(path_oid, data);
    return(RSOK);
}

// findItem(): find item in block table
// oid - block oid
// resval - result data
int CDskSuperBlockMan::findItem(long oid, dsk_superblock_t** resval)
{
    (*resval) = NULL;

    pthread_mutex_lock(& m_superblock_mutex);

    long flag = DBFALSE;

    int currNumDskSuperBlock = m_currNumDskSuperBlock;
    for(int i = 0; i < currNumDskSuperBlock; i++)
    {
        dsk_superblock_t* p = & m_arrDskSuperBlock[i];    

        long p_oid = p->oid;
        if(p_oid == oid) {
            (*resval) = p;
            
            flag = DBTRUE;
            break;
        }
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findItem(): find item in block table
// key - block key
// resval - result data
int CDskSuperBlockMan::findItem(char* key, dsk_superblock_t** resval)
{
    (*resval) = NULL;

    str_t p_key;

    pthread_mutex_lock(& m_superblock_mutex);

    long flag = DBFALSE;

    int currNumDskSuperBlock = m_currNumDskSuperBlock;
    for(int i = 0; i < currNumDskSuperBlock; i++)
    {
        dsk_superblock_t* p = & m_arrDskSuperBlock[i];    

        strNCpyUtil(p_key, p->key, STRSZ);
        if(strNCmpUtil(p_key, key, STRSZ) == 0) {
            (*resval) = p;

            flag = DBTRUE;
            break;
        }
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findFirstFreeSuperBlock(): find first free item in superblock table
// disk_group - disk device group
// disk_dev - disk device oid
// path_oid - file path oid
// block_num - number of blocks
// block_sector - block sector at disk device
// uid - user id
// resval - result data
// block_oid - return block oid
// int CDskSuperBlockMan::findFirstFreeSuperBlock(
//     long disk_group, 
//     long disk_dev, 
//     long path_oid, 
//     long block_num,
//     long block_sector,
//     long uid, 
//     dsk_superblock_t** resval, 
//     long* superblock_oid)
// {
//     (*resval) = NULL;
//
//     CSequence* seq = gAppMain.getSequencePtr();
//
//     long currTimestamp = getCurrentTimestamp();
//
//     int currNumDskSuperBlock = getCurrNumDskSuperBlock();
//     for(int i = 0; i < currNumDskSuperBlock; i++) {
//         dsk_superblock_t* p = & m_arrDskSuperBlock[i];    
//
//         pthread_mutex_lock(& m_superblock_mutex);
//         long p_is_deleted = p->is_deleted;
//         pthread_mutex_unlock(& m_superblock_mutex);
//
//         if(p_is_deleted == DBTRUE) {
//             (*resval) = p;
//             break;
//         }
//     }
//
//     if( (*resval) != NULL) 
//     {
//         pthread_mutex_lock(& m_superblock_mutex);
//
//         (*resval)->disk_group   = disk_group;
//         (*resval)->disk_dev     = disk_dev;
//         (*resval)->path_oid     = path_oid;
//         (*resval)->block_num    = block_num;
//         (*resval)->block_sector = block_sector;
//         (*resval)->read_count   = 0L;
//         (*resval)->write_count  = 0L;
//         (*resval)->create_date  = currTimestamp;
//         (*resval)->create_uid   = uid;
//         (*resval)->modify_date  = currTimestamp;
//         (*resval)->modify_uid   = uid;
//         (*resval)->is_modified  = DBTRUE;
//         (*resval)->is_deleted   = DBFALSE;
//
//         pthread_mutex_unlock(& m_superblock_mutex);
//     }
//     else 
//     {
//         pthread_mutex_lock(& m_superblock_mutex);
//
//         long flag = DBFALSE;
//         if(m_currNumDskSuperBlock < m_maxNumDskSuperBlock) 
//         {
//             (*superblock_oid) = seq->nextVal((char*)SEQ_TABLE_SUPERBLOCK);
//
//             (*resval) = & m_arrDskSuperBlock[m_currNumDskSuperBlock];
//             m_currNumDskSuperBlock++;
//
//             flag = DBTRUE;
//         }
//
//         pthread_mutex_unlock(& m_superblock_mutex);
//
//         if(flag == DBTRUE)
//         {
//             str_t key;
//             sprintf(key, "%ld_%ld", path_oid, block_num);
//
//             setItemData(
//                 resval,
//                 (*superblock_oid),
//                 disk_group,
//                 disk_dev,
//                 path_oid,
//                 block_num,
//                 block_sector,
//                 0L,
//                 0L,
//                 currTimestamp,
//                 uid,
//                 currTimestamp,
//                 uid,
//                 DBTRUE,
//                 DBNULL_LONG,
//                 DBNULL_LONG,
//                 DBFALSE,
//                 key);
//         }
//     }
//
//     if((*resval) != NULL)
//         return(RSOK);
//
//     return(RSERR);
// }

// findFirstFreeSuperBlock(): find first free item in superblock table
// disk_group - disk device group
// disk_dev - disk device oid
// path_oid - file path oid
// block_num - number of blocks
// block_sector - block sector at disk device
// uid - user id
// resval - result data
// block_oid - return block oid
int CDskSuperBlockMan::findFirstFreeSuperBlock(
    long disk_group, 
    long disk_dev, 
    long path_oid, 
    long block_num,
    long block_sector,
    long uid, 
    dsk_superblock_t** resval, 
    long* superblock_oid)
{
    (*resval) = NULL;

    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    pthread_mutex_lock(& m_superblock_mutex);

    int currNumDskSuperBlock = m_currNumDskSuperBlock;
    if(currNumDskSuperBlock < m_maxNumDskSuperBlock) {
        /* nothing todo! */
    }
    else {
        for(int i = 0; i < currNumDskSuperBlock; i++) {
            dsk_superblock_t* p = & m_arrDskSuperBlock[i];    

            long p_is_deleted = p->is_deleted;
            if(p_is_deleted == DBTRUE) {
                (*resval) = p;
                break;
            }
        }
    }

    if( (*resval) != NULL) 
    {
        (*resval)->disk_group   = disk_group;
        (*resval)->disk_dev     = disk_dev;
        (*resval)->path_oid     = path_oid;
        (*resval)->block_num    = block_num;
        (*resval)->block_sector = block_sector;
        (*resval)->read_count   = 0L;
        (*resval)->write_count  = 0L;
        (*resval)->create_date  = currTimestamp;
        (*resval)->create_uid   = uid;
        (*resval)->modify_date  = currTimestamp;
        (*resval)->modify_uid   = uid;
        (*resval)->is_modified  = DBTRUE;
        (*resval)->is_deleted   = DBFALSE;
    }
    else 
    {
        long flag = DBFALSE;
        if(m_currNumDskSuperBlock < m_maxNumDskSuperBlock) 
        {
            (*superblock_oid) = seq->nextVal((char*)SEQ_TABLE_SUPERBLOCK);

            (*resval) = & m_arrDskSuperBlock[m_currNumDskSuperBlock];
            m_currNumDskSuperBlock++;

            flag = DBTRUE;
        }

        if(flag == DBTRUE)
        {
            str_t key;
            sprintf(key, "%ld_%ld", path_oid, block_num);

            (*resval)->oid          = (*superblock_oid);
            (*resval)->disk_group   = disk_group;
            (*resval)->disk_dev     = disk_dev;
            (*resval)->path_oid     = path_oid;
            (*resval)->block_num    = block_num;
            (*resval)->block_sector = block_sector;
            (*resval)->read_count   = 0L;
            (*resval)->write_count  = 0L;
            (*resval)->create_date  = currTimestamp;
            (*resval)->create_uid   = uid;
            (*resval)->modify_date  = currTimestamp;
            (*resval)->modify_uid   = uid;
            (*resval)->is_modified  = DBTRUE;
            (*resval)->delete_date  = DBNULL_LONG;
            (*resval)->delete_uid   = DBNULL_LONG;
            (*resval)->is_deleted   = DBFALSE;
            strNCpyUtil((*resval)->key, (char*)key, STRSZ);
        }
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    if((*resval) != NULL) {
        m_pSuperBlockIndex->addIndexItem((*resval)->path_oid, (*resval));
        return(RSOK);
    }

    return(RSERR);
}

// findAll(): find all blocks
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
int CDskSuperBlockMan::findAll(dsk_superblock_t** arr, long* arrsz)
{
    (*arr) = NULL;
    (*arrsz) = 0;

    pthread_mutex_lock(& m_superblock_mutex);

    long flag = DBFALSE;

    int currNumDskSuperBlock = m_currNumDskSuperBlock;

    (*arrsz) = currNumDskSuperBlock;
    (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), (*arrsz));
    if((*arr) != NULL) 
    {
        dsk_superblock_t* p = (*arr);
        for(int i = 0; i < currNumDskSuperBlock; i++) {
            memNCpyUtil((byte*)p, (byte*)& m_arrDskSuperBlock[i], sizeof(dsk_superblock_t));
            p++;
        }  

        flag = DBTRUE;
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    if(flag == DBTRUE)
        return RSOK;
    return RSERR;
}

// findAllByPathOid(): find all blocks
// path_oid - file path oid
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
int CDskSuperBlockMan::findAllByPathOid(long path_oid, dsk_superblock_t** arr, long* arrsz)
{
    (*arr) = NULL;
    (*arrsz) = 0;

    dsk_superblock_index_t* p_sbIDX = NULL;

    int rscode = m_pSuperBlockIndex->findIndexItem(path_oid, & p_sbIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_lsSB = p_sbIDX->pLsSuperblock;
        if(p_lsSB != NULL) {
            CIdxDescriptor* p_descr = p_lsSB->getDescriptorPtr();

            long max_arrsz = p_descr->getNumberOfEntries();
            if(max_arrsz > 0) 
            {
                (*arrsz) = 0;
                (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), max_arrsz);
                if((*arr) != NULL) 
                {
                    pthread_mutex_lock(& m_superblock_mutex);

                    CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
                    dsk_superblock_t* p_sbDST = (*arr);
                    dsk_superblock_t* p_sbSRC = NULL;
                    while(p_src != NULL) {
                        p_sbSRC = (dsk_superblock_t*)p_src->getEntryObjPtr();

                        long p_path_oid = p_sbSRC->path_oid;
                        if(p_path_oid == path_oid)
                        {
                            memNCpyUtil((byte*)p_sbDST, (byte*)p_sbSRC, sizeof(dsk_superblock_t));
                            p_sbDST++;

                            (*arrsz) += 1;
                        }
                        p_src = p_src->getEntryNextPtr();
                    }

                    pthread_mutex_unlock(& m_superblock_mutex);
                }
            }
        }
    }
    else {
        int rscode = countItemsByPathOid(path_oid, arrsz);
        if(rscode == RSOK) 
        {
            if((*arrsz) > 0) 
            {
                (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), (*arrsz));
                if((*arr) != NULL) 
                {
                    pthread_mutex_lock(& m_superblock_mutex);

                    int pos_dst = 0;
                    dsk_superblock_t* p_dst = & (*arr)[pos_dst];

                    int currNumDskSuperBlock = m_currNumDskSuperBlock;
                    for(int i = 0; i < currNumDskSuperBlock; i++) 
                    {
                        dsk_superblock_t* p_src = & m_arrDskSuperBlock[i];

                        long p_path_oid = p_src->path_oid;
                        if(p_path_oid == path_oid)
                        {
                            memNCpyUtil((byte*) p_dst, (byte*) p_src, sizeof(dsk_superblock_t));

                            pos_dst += 1;
                            p_dst = & (*arr)[pos_dst];
                        }
                    }  

                    pthread_mutex_unlock(& m_superblock_mutex);
                }
            }
        }
    }

    return RSOK;
}

// findAllByPathOidAndDiskDev(): find all blocks
// path_oid - file path oid
// disk_dev - disk device oid
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
// int CDskSuperBlockMan::findAllByPathOidAndDiskDev(long path_oid, long disk_dev, dsk_superblock_t** arr, long* arrsz)
// {
//     (*arr) = NULL;
//     (*arrsz) = 0;

//     dsk_superblock_index_t* p_sbIDX = NULL;

//     int rscode = m_pSuperBlockIndex->findIndexItem(path_oid, & p_sbIDX);
//     if(rscode == RSOK) {
//         CIdxDoubleLinkedList* p_lsSB = p_sbIDX->pLsSuperblock;

//         CIdxEntryPtr_t* arrEntryPtr = NULL;
//         long szArrEntry = 0;

//         p_lsSB->findAll(& arrEntryPtr, & szArrEntry);
//         if(szArrEntry > 0) {
//             (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), szArrEntry);
//             (*arrsz) = 0;

//             if((*arr) != NULL)
//             {
//                 pthread_mutex_lock(& m_superblock_mutex);

//                 dsk_superblock_t* p_sbDST = (*arr);
//                 for(int i = 0; i < szArrEntry; i++) {
//                     CIdxEntry* p = arrEntryPtr[i];

//                     dsk_superblock_t* p_sbSRC = (dsk_superblock_t*)p->getEntryObjPtr();

//                     long p_path_oid = p_sbSRC->path_oid;
//                     long p_disk_dev = p_sbSRC->disk_dev;

//                     if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) ) {
//                         memNCpyUtil((byte*)p_sbDST, (byte*)p_sbSRC, sizeof(dsk_superblock_t));
//                         p_sbDST++;

//                         (*arrsz) += 1;
//                     }
//                 }

//                 pthread_mutex_unlock(& m_superblock_mutex);
//             }

//             freeDataArray(arrEntryPtr);
//             szArrEntry = 0;
//         }
//     }
//     else {
//         int rscode = countItemsByPathOidAndDiskDev(path_oid, disk_dev, arrsz);
//         if(rscode == RSOK) 
//         {
//             if((*arrsz) > 0) 
//             {
//                 (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), (*arrsz));
//                 if((*arr) != NULL) 
//                 {
//                     pthread_mutex_lock(& m_superblock_mutex);

//                     int pos_dst = 0;
//                     dsk_superblock_t* p_dst = & (*arr)[pos_dst];

//                     int currNumDskSuperBlock = m_currNumDskSuperBlock;
//                     for(int i = 0; i < currNumDskSuperBlock; i++) 
//                     {
//                         dsk_superblock_t* p_src = & m_arrDskSuperBlock[i];

//                         long p_path_oid = p_src->path_oid;
//                         long p_disk_dev = p_src->disk_dev;

//                         if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) )
//                         {
//                             memNCpyUtil((byte*) p_dst, (byte*) p_src, sizeof(dsk_superblock_t));

//                             pos_dst += 1;
//                             p_dst = & (*arr)[pos_dst];
//                         }
//                     }  

//                     pthread_mutex_unlock(& m_superblock_mutex);
//                 }
//             }
//         }
//     }

//     return RSOK;
// }

// findAllByPathOidAndDiskDev(): find all blocks
// path_oid - file path oid
// disk_dev - disk device oid
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
int CDskSuperBlockMan::findAllByPathOidAndDiskDev(long path_oid, long disk_dev, dsk_superblock_t** arr, long* arrsz)
{
    (*arr) = NULL;
    (*arrsz) = 0;

    dsk_superblock_index_t* p_sbIDX = NULL;

    int rscode = m_pSuperBlockIndex->findIndexItem(path_oid, & p_sbIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_lsSB = p_sbIDX->pLsSuperblock;
        if(p_lsSB != NULL) {
            CIdxDescriptor* p_descr = p_lsSB->getDescriptorPtr();

            long max_arrsz = p_descr->getNumberOfEntries();

            if(max_arrsz > 0) 
            {
                (*arrsz) = 0;
                (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), max_arrsz);

                if((*arr) != NULL) 
                {
                    pthread_mutex_lock(& m_superblock_mutex);

                    CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
                    dsk_superblock_t* p_sbDST = (*arr);
                    dsk_superblock_t* p_sbSRC = NULL;
                    while(p_src != NULL) {
                        p_sbSRC = (dsk_superblock_t*)p_src->getEntryObjPtr();

                        long p_path_oid = p_sbSRC->path_oid;
                        long p_disk_dev = p_sbSRC->disk_dev;

                        if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) )
                        {
                            memNCpyUtil((byte*)p_sbDST, (byte*)p_sbSRC, sizeof(dsk_superblock_t));
                            p_sbDST++;

                            (*arrsz) += 1;
                        }
                        p_src = p_src->getEntryNextPtr();
                    }

                    pthread_mutex_unlock(& m_superblock_mutex);
                }
            }
        }
    }
    else {
        int rscode = countItemsByPathOidAndDiskDev(path_oid, disk_dev, arrsz);
        if(rscode == RSOK) 
        {
            if((*arrsz) > 0) 
            {
                (*arr) = (dsk_superblock_t*)allocDataArray(sizeof(dsk_superblock_t), (*arrsz));
                if((*arr) != NULL) 
                {
                    pthread_mutex_lock(& m_superblock_mutex);

                    int pos_dst = 0;
                    dsk_superblock_t* p_dst = & (*arr)[pos_dst];

                    int currNumDskSuperBlock = m_currNumDskSuperBlock;
                    for(int i = 0; i < currNumDskSuperBlock; i++) 
                    {
                        dsk_superblock_t* p_src = & m_arrDskSuperBlock[i];

                        long p_path_oid = p_src->path_oid;
                        long p_disk_dev = p_src->disk_dev;

                        if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) )
                        {
                            memNCpyUtil((byte*) p_dst, (byte*) p_src, sizeof(dsk_superblock_t));

                            pos_dst += 1;
                            p_dst = & (*arr)[pos_dst];
                        }
                    }  

                    pthread_mutex_unlock(& m_superblock_mutex);
                }
            }
        }
    }

    return RSOK;
}

// countItemsByPathOid(): count all blocks with path oid
// path_oid - file path oid
// num_items - return the number of items
int CDskSuperBlockMan::countItemsByPathOid(long path_oid, long* num_items)
{
    (*num_items) = 0;

    pthread_mutex_lock(& m_superblock_mutex);

    dsk_superblock_index_t* p_sbIDX = NULL;

    int rscode = m_pSuperBlockIndex->findIndexItem(path_oid, & p_sbIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_lsSB = p_sbIDX->pLsSuperblock;
        if(p_lsSB != NULL) {
            CIdxDescriptor* p_descr = p_lsSB->getDescriptorPtr();

            CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
            dsk_superblock_t* p = NULL;
            while(p_src != NULL) {
                p = (dsk_superblock_t*)p_src->getEntryObjPtr();

                long p_path_oid = p->path_oid;
                if(p_path_oid == path_oid) {
                    (*num_items) += 1;
                }
            }
        }
    }
    else {
        int currNumDskSuperBlock = m_currNumDskSuperBlock;

        dsk_superblock_t* p = NULL;
        for(int i = 0; i < currNumDskSuperBlock; i++) 
        {
            p = (dsk_superblock_t*) & m_arrDskSuperBlock[i];

            long p_path_oid = p->path_oid;
            if(p_path_oid == path_oid) {
                (*num_items) += 1;
            }
        }  
    }

    pthread_mutex_unlock(& m_superblock_mutex);

    return RSOK;
}

// countItemsByPathOidAndDiskDev(): count all blocks with path oid
// path_oid - file path oid
// disk_dev - disk device oid
// num_items - return the number of items
int CDskSuperBlockMan::countItemsByPathOidAndDiskDev(long path_oid, long disk_dev, long* num_items)
{
    (*num_items) = 0;

    pthread_mutex_lock(& m_superblock_mutex);

    dsk_superblock_index_t* p_sbIDX = NULL;

    int rscode = m_pSuperBlockIndex->findIndexItem(path_oid, & p_sbIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_lsSB = p_sbIDX->pLsSuperblock;
        if(p_lsSB != NULL) {
            CIdxDescriptor* p_descr = p_lsSB->getDescriptorPtr();

            CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
            dsk_superblock_t* p = NULL;
            while(p_src != NULL) {
                p = (dsk_superblock_t*)p_src->getEntryObjPtr();

                long p_path_oid = p->path_oid;
                long p_disk_dev = p->disk_dev;

                if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) ) {
                    (*num_items) += 1;
                }
            }
        }
    }
    else {
        int currNumDskSuperBlock = m_currNumDskSuperBlock;

        dsk_superblock_t* p = NULL;
        for(int i = 0; i < currNumDskSuperBlock; i++) {
            p = (dsk_superblock_t*) & m_arrDskSuperBlock[i];

            long p_path_oid = p->path_oid;
            long p_disk_dev = p->disk_dev;

            if( (p_path_oid == path_oid) && (p_disk_dev == disk_dev) ) {
                (*num_items) += 1;
            }
        }
    }  

    pthread_mutex_unlock(& m_superblock_mutex);

    return RSOK;
}

// deleteItem(): mark item as deleted in block table
// oid - block oid
// uid - user id
int CDskSuperBlockMan::deleteItem(long oid, long uid)
{
    int rscode = RSERR;

    dsk_superblock_t* data = NULL;
    
    rscode = findItem(oid, &data);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_superblock_mutex);
    
        long currTimestamp = getCurrentTimestamp();

        data->delete_uid  = uid;
        data->delete_date = currTimestamp;
        data->is_deleted  = DBTRUE;
    
        pthread_mutex_unlock(& m_superblock_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "deleteItem()", ERR_CANTFINDOBJECTID);
    }

    return(rscode);
}

// deleteItem(): mark item as deleted in block table
// key - block key
// uid - user id
int CDskSuperBlockMan::deleteItem(char* key, long uid)
{
    int rscode = RSERR;

    dsk_superblock_t* data = NULL;
    
    rscode = findItem(key, &data);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_superblock_mutex);

        long currTimestamp = getCurrentTimestamp();

        data->delete_uid  = uid;
        data->delete_date = currTimestamp;
        data->is_deleted  = DBTRUE;

        pthread_mutex_unlock(& m_superblock_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "deleteItem()", ERR_CANTFINDKEY);
    }

    return(rscode);
}

// deleteAllItemByPathOid(): mark all items with same path oid as deleted in block table
// path_oid - file path oid
// uid - user id
int CDskSuperBlockMan::deleteAllItemByPathOid(long path_oid, long uid)
{
    pthread_mutex_lock(& m_superblock_mutex);

    int currNumDskSuperBlock = m_currNumDskSuperBlock;

    dsk_superblock_t* p = NULL;
    for(int i = 0; i < currNumDskSuperBlock; i++) 
    {
        p = & m_arrDskSuperBlock[i];

        long p_path_oid = p->path_oid;
        if(p_path_oid == path_oid) 
        {
            long currTimestamp = getCurrentTimestamp();

            p->delete_uid  = uid;
            p->delete_date = currTimestamp;
            p->is_deleted  = DBTRUE;
        }
    }  

    pthread_mutex_unlock(& m_superblock_mutex);

    return(RSOK);
}

// copyAllItemByPathOid(): copy all items with same path oid in block table
// spath_oid - source file path oid
// dpath_parent - destination parent path oid
// dpath_oid - destination file path oid
// uid - user id
int CDskSuperBlockMan::copyAllItemByPathOid(long spath_oid, long dpath_parent, long dpath_oid, long uid)
{
    int rscode = RSERR;

    dsk_superblock_t* data = NULL;
    long datasz = 0;

    rscode = findAllByPathOid(spath_oid, & data, & datasz);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_superblock_mutex);

        for(int i = 0; i < datasz; i++) {
            dsk_superblock_t* p = & data[i];

            long currTimestamp = getCurrentTimestamp();

            if(p->is_deleted == DBFALSE) {
                p->path_oid = dpath_oid;
                p->modify_uid = uid;
                p->modify_date = currTimestamp;
                p->is_modified = DBTRUE;
            }
        }

        pthread_mutex_unlock(& m_superblock_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_SUPERBLOCKMAN_H, "copyAllItemByPathOid()", ERR_CANTFINDSPATHOID);
    }

    return rscode;
}

// newItemData(): mark item as deleted in block table
// data - data reference
// dsk_superblock_t* CDskSuperBlockMan::newItemData(dsk_superblock_t** data)
// {
//     long isNew = DBFALSE;

//     if((*data) == NULL) {
//         isNew = DBTRUE;
//         (*data) = (dsk_superblock_t*)allocData(sizeof(dsk_superblock_t));
//     }

//     if(isNew == DBFALSE)
//         pthread_mutex_lock(& m_superblock_mutex);

//     (*data)->oid          = DBNULL_LONG;
//     (*data)->disk_group   = DBNULL_LONG;
//     (*data)->disk_dev     = DBNULL_LONG;
//     (*data)->path_oid     = DBNULL_LONG;
//     (*data)->block_num    = DBNULL_LONG;
//     (*data)->block_sector = DBNULL_LONG;
//     (*data)->read_count   = DBNULL_LONG;
//     (*data)->write_count  = DBNULL_LONG;
//     (*data)->create_date  = DBNULL_LONG;
//     (*data)->create_uid   = DBNULL_LONG;
//     (*data)->modify_date  = DBNULL_LONG;
//     (*data)->modify_uid   = DBNULL_LONG;
//     (*data)->is_modified  = DBFALSE;
//     (*data)->delete_date  = DBNULL_LONG;
//     (*data)->delete_uid   = DBNULL_LONG;
//     (*data)->is_deleted   = DBFALSE;
//     strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);

//     if(isNew == DBFALSE)
//         pthread_mutex_unlock(& m_superblock_mutex);

//     return (*data);
// }

// newItemData(): mark item as deleted in block table
// data - data reference
dsk_superblock_t* CDskSuperBlockMan::newItemData(dsk_superblock_t** data)
{
    if((*data) == NULL) 
        (*data) = (dsk_superblock_t*)allocData(sizeof(dsk_superblock_t));

    pthread_mutex_lock(& m_superblock_mutex);

    (*data)->oid          = DBNULL_LONG;
    (*data)->disk_group   = DBNULL_LONG;
    (*data)->disk_dev     = DBNULL_LONG;
    (*data)->path_oid     = DBNULL_LONG;
    (*data)->block_num    = DBNULL_LONG;
    (*data)->block_sector = DBNULL_LONG;
    (*data)->read_count   = DBNULL_LONG;
    (*data)->write_count  = DBNULL_LONG;
    (*data)->create_date  = DBNULL_LONG;
    (*data)->create_uid   = DBNULL_LONG;
    (*data)->modify_date  = DBNULL_LONG;
    (*data)->modify_uid   = DBNULL_LONG;
    (*data)->is_modified  = DBFALSE;
    (*data)->delete_date  = DBNULL_LONG;
    (*data)->delete_uid   = DBNULL_LONG;
    (*data)->is_deleted   = DBFALSE;
    strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);

    pthread_mutex_unlock(& m_superblock_mutex);

    return (*data);
}

// setItemData(): add item to block table
// data - return data
// oid - block oid
// disk_group - disk device group
// disk_dev - disk device uid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector at disk device
// read_count - read access counter
// write_count - write access counter
// create_date - create date
// create_uid - user creator uid
// modify_date - modify date
// modify_uid - user modifier uid
// is_modified - file was modified
// delete_date - delete data
// delete_uid - user delete uid
// is_deleted - file was deleted
// key - block key
// dsk_superblock_t* CDskSuperBlockMan::setItemData(
//     dsk_superblock_t** data, 
//     long oid,
//     long disk_group,
//     long disk_dev,
//     long path_oid,
//     long block_num,
//     long block_sector,
//     long read_count,
//     long write_count,
//     long create_date,
//     long create_uid,
//     long modify_date,
//     long modify_uid,
//     long is_modified,
//     long delete_date,
//     long delete_uid,
//     long is_deleted,
//     char* key)
// {
//     long isNew = DBFALSE;

//     if((*data) == NULL) {
//         isNew = DBTRUE;
//         (*data) = (dsk_superblock_t*)allocData(sizeof(dsk_superblock_t));
//     }
        
//     if(isNew == DBFALSE)
//         pthread_mutex_lock(& m_superblock_mutex);

//     (*data)->oid          = oid;
//     (*data)->disk_group   = disk_group;
//     (*data)->disk_dev     = disk_dev;
//     (*data)->path_oid     = path_oid;
//     (*data)->block_num    = block_num;
//     (*data)->block_sector = block_sector;
//     (*data)->read_count   = read_count;
//     (*data)->write_count  = write_count;
//     (*data)->create_date  = create_date;
//     (*data)->create_uid   = create_uid;
//     (*data)->modify_date  = modify_date;
//     (*data)->modify_uid   = modify_uid;
//     (*data)->is_modified  = is_modified;
//     (*data)->delete_date  = delete_date;
//     (*data)->delete_uid   = delete_uid;
//     (*data)->is_deleted   = is_deleted;
//     strNCpyUtil((*data)->key, (char*)key, STRSZ);

//     if(isNew == DBFALSE)
//         pthread_mutex_unlock(& m_superblock_mutex);

//     return (*data);
// }

// setItemData(): add item to block table
// data - return data
// oid - block oid
// disk_group - disk device group
// disk_dev - disk device uid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector at disk device
// read_count - read access counter
// write_count - write access counter
// create_date - create date
// create_uid - user creator uid
// modify_date - modify date
// modify_uid - user modifier uid
// is_modified - file was modified
// delete_date - delete data
// delete_uid - user delete uid
// is_deleted - file was deleted
// key - block key
dsk_superblock_t* CDskSuperBlockMan::setItemData(
    dsk_superblock_t** data, 
    long oid,
    long disk_group,
    long disk_dev,
    long path_oid,
    long block_num,
    long block_sector,
    long read_count,
    long write_count,
    long create_date,
    long create_uid,
    long modify_date,
    long modify_uid,
    long is_modified,
    long delete_date,
    long delete_uid,
    long is_deleted,
    char* key)
{
    if((*data) == NULL) 
        (*data) = (dsk_superblock_t*)allocData(sizeof(dsk_superblock_t));
        
    pthread_mutex_lock(& m_superblock_mutex);

    (*data)->oid          = oid;
    (*data)->disk_group   = disk_group;
    (*data)->disk_dev     = disk_dev;
    (*data)->path_oid     = path_oid;
    (*data)->block_num    = block_num;
    (*data)->block_sector = block_sector;
    (*data)->read_count   = read_count;
    (*data)->write_count  = write_count;
    (*data)->create_date  = create_date;
    (*data)->create_uid   = create_uid;
    (*data)->modify_date  = modify_date;
    (*data)->modify_uid   = modify_uid;
    (*data)->is_modified  = is_modified;
    (*data)->delete_date  = delete_date;
    (*data)->delete_uid   = delete_uid;
    (*data)->is_deleted   = is_deleted;
    strNCpyUtil((*data)->key, (char*)key, STRSZ);

    pthread_mutex_unlock(& m_superblock_mutex);

    return (*data);
}

// setItemData_NotThreadSafe(): add item to block table not thread safe (internal class use only)
// data - return data
// oid - block oid
// disk_group - disk device group
// disk_dev - disk device uid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector at disk device
// read_count - read access counter
// write_count - write access counter
// create_date - create date
// create_uid - user creator uid
// modify_date - modify date
// modify_uid - user modifier uid
// is_modified - file was modified
// delete_date - delete data
// delete_uid - user delete uid
// is_deleted - file was deleted
// key - block key
dsk_superblock_t* CDskSuperBlockMan::setItemData_NotThreadSafe(
    dsk_superblock_t** data, 
    long oid,
    long disk_group,
    long disk_dev,
    long path_oid,
    long block_num,
    long block_sector,
    long read_count,
    long write_count,
    long create_date,
    long create_uid,
    long modify_date,
    long modify_uid,
    long is_modified,
    long delete_date,
    long delete_uid,
    long is_deleted,
    char* key)
{
    if((*data) == NULL) 
        (*data) = (dsk_superblock_t*)allocData(sizeof(dsk_superblock_t));
        
    (*data)->oid          = oid;
    (*data)->disk_group   = disk_group;
    (*data)->disk_dev     = disk_dev;
    (*data)->path_oid     = path_oid;
    (*data)->block_num    = block_num;
    (*data)->block_sector = block_sector;
    (*data)->read_count   = read_count;
    (*data)->write_count  = write_count;
    (*data)->create_date  = create_date;
    (*data)->create_uid   = create_uid;
    (*data)->modify_date  = modify_date;
    (*data)->modify_uid   = modify_uid;
    (*data)->is_modified  = is_modified;
    (*data)->delete_date  = delete_date;
    (*data)->delete_uid   = delete_uid;
    (*data)->is_deleted   = is_deleted;
    strNCpyUtil((*data)->key, (char*)key, STRSZ);

    return (*data);
}

/* Debug */

// debug(): show all blocks
// debugLevel - debug level
// className - class name
// methodName - method name
void CDskSuperBlockMan::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    int currNumDskSuperBlock = getCurrNumDskSuperBlock();

    dsk_superblock_t* p = NULL;
    for(int i = 0; i < currNumDskSuperBlock; i++)
    {
        p = & m_arrDskSuperBlock[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show block
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a block entry
void CDskSuperBlockMan::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_superblock_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;

    pthread_mutex_lock(& m_superblock_mutex);

    sprintf(
        errmsg, 
        "SuperBlockMan: Oid=%ld,DiskGroup=%ld,DiskUid=%ld,PathOid=%ld,BlockNum=%ld,BlockSector=%ld,ReadCount=%ld,WriteCount=%ld,CreateDate=%ld,CreateUid=%ld,ModifyDate=%ld,ModifyUid=%ld,IsModified=%ld,DeleteDate=%ld,DeleteUid=%ld,IsDeleted=%ld,Key=%s\n",
        p->oid,
        p->disk_group,
        p->disk_dev,
        p->path_oid,
        p->block_num,
        p->block_sector,
        p->read_count,
        p->write_count,
        p->create_date,
        p->create_uid,
        p->modify_date,
        p->modify_uid,
        p->is_modified,
        p->delete_date,
        p->delete_uid,
        p->is_deleted,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);

    pthread_mutex_unlock(& m_superblock_mutex);
}

/* Getters/Setters */

CDskSuperBlockIdx* CDskSuperBlockMan::getSuperBlockIndex()
{
    return m_pSuperBlockIndex;
}


char* CDskSuperBlockMan::getSuperBlockTableFile()
{
    return m_superBlockTableFile;
}

int CDskSuperBlockMan::getMaxNumDskSuperBlock()
{
    return m_maxNumDskSuperBlock;
}

int CDskSuperBlockMan::getCurrNumDskSuperBlock()
{
    pthread_mutex_lock(& m_superblock_mutex);

    int currNumDskSuperBlock = m_currNumDskSuperBlock;

    pthread_mutex_unlock(& m_superblock_mutex);

    return currNumDskSuperBlock;
}
