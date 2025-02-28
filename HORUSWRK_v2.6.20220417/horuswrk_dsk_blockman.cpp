/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_blockman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

// BLOCK MUTEX
pthread_mutex_t m_block_mutex;

CDskBlockMan::CDskBlockMan(int maxNumDskBlock, char* blockTableFile, char* blockTableFilePath)
{
    init(maxNumDskBlock, blockTableFile, blockTableFilePath);
}

CDskBlockMan::~CDskBlockMan()
{
    terminate();
}

// init(): initiate block manager
void CDskBlockMan::init(int maxNumDskBlock, char* blockTableFile, char* blockTableFilePath)
{
    bigstr_t errmsg;

    if(pthread_mutex_init(& m_block_mutex, NULL) != 0)  {
        sprintf(errmsg, ERR_CANTCREATEMUTEX, __HORUSWRK_DSK_BLOCKMAN_H); 
        errMsg(__HORUSWRK_DSK_BLOCKMAN_H, "init()", errmsg);
    }

    strNCpyUtil(m_blockTableFile, blockTableFile, BIGSTRSZ);
    strNCpyUtil(m_blockTableFilePath, blockTableFilePath, PATHNAMESZ);

    sprintf(
        errmsg, 
        "\nX.I) CDskBlockMan::init() - BlockTableFile: %s, BlockTableFilePath: %s... ", 
        m_blockTableFile,
        m_blockTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "init()", errmsg);

    m_maxNumDskBlock = maxNumDskBlock; 
    m_currNumDskBlock = 0; 
    m_arrDskBlock = (dsk_block_t*)allocDataArray(sizeof(dsk_block_t), m_maxNumDskBlock);

    m_pBlockIndex = new CDskBlockIdx(DEF_DSK_MAX_NUMOFBLOCKSINDEX);

    loadFile(m_blockTableFilePath);

}

// term(): terminate block manager
void CDskBlockMan::terminate()
{
    saveFile(m_blockTableFilePath);

    pthread_mutex_destroy(& m_block_mutex);

    if(m_pBlockIndex != NULL)
        delete(m_pBlockIndex);

    freeDataArray(m_arrDskBlock);
}

/* Methodes */

// loadFile(): load table of blocks from file
// fileName - block's table file name
int CDskBlockMan::loadFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    pthread_mutex_lock(& m_block_mutex);

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_block_t);

        m_currNumDskBlock = 0;
        while(m_currNumDskBlock < m_maxNumDskBlock)
        {
            dsk_block_t* ptr_block = & m_arrDskBlock[m_currNumDskBlock];
            if(fread(ptr_block, sizeof(byte), size, f) == 0) break;

            m_pBlockIndex->addIndexItem(ptr_block->path_oid, ptr_block);
            m_currNumDskBlock += 1;
        }
        fclose(f);

        sprintf(errmsg, "\nBlock Table File: %s... loaded!", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "loadFile()", errmsg);
    }

    pthread_mutex_unlock(& m_block_mutex);

    return rscode;
}

// saveFile(): save table of blocks to file
// fileName - block's table file name
int CDskBlockMan::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    pthread_mutex_lock(& m_block_mutex);

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_block_t);
        for(int i = 0; i < m_currNumDskBlock; i++)
        {
            dsk_block_t* p = &m_arrDskBlock[i];

            long num_write = fwrite(p, sizeof(byte), size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "saveFile()", errmsg);
        }
        fclose(f);

        sprintf(errmsg, "\nBlock Table File: %s... saved!", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "saveFile()", errmsg);
    }

    pthread_mutex_unlock(& m_block_mutex);

    return rscode;
}

// addItem(): add item to block table
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector at disk device
// block_oid - return block oid
int CDskBlockMan::addItem(
    long path_oid,
    long block_num,
    long block_sector,
    long* block_oid)
{
    CSequence* seq = gAppMain.getSequencePtr();

    dsk_block_t* data = NULL;

    str_t key;
    sprintf(key, "%ld_%ld_%ld", path_oid, block_num, block_sector);

    if(findItem(key, &data) != RSOK)
    {
        pthread_mutex_lock(& m_block_mutex);

        data = &(m_arrDskBlock[m_currNumDskBlock]);

        (*block_oid) = seq->nextVal((char*)SEQ_TABLE_BLOCK);
            
        m_currNumDskBlock += 1;

        /* Add new item
         */
        setItemData_NotThreadSafe(
            &data, 
            (*block_oid),
            path_oid,
            block_num,
            block_sector,
            DBTRUE,
            key);

        pthread_mutex_unlock(& m_block_mutex);
    }
    else
    {
        /* Update existent item
         */
        pthread_mutex_lock(& m_block_mutex);

        data->path_oid = path_oid;
        data->block_num = block_num;
        data->is_valid = DBTRUE;

        (*block_oid) = data->oid;

        pthread_mutex_unlock(& m_block_mutex);
    }

    m_pBlockIndex->addIndexItem(path_oid, data);
    return(RSOK);
}

// findItem(): find item in block table
// oid - block oid
// resval - result data
int CDskBlockMan::findItem(long oid, dsk_block_t** resval)
{
    (*resval) = NULL;

    pthread_mutex_lock(& m_block_mutex);

    long flag = DBFALSE;

    int currNumDskBlock = m_currNumDskBlock;
    for(int i = 0; i < currNumDskBlock; i++)
    {
        dsk_block_t* p = &m_arrDskBlock[i];    

        long p_oid = p->oid;
        if(p_oid == oid) {
            (*resval) = p;

            flag = DBTRUE;
            break;
        }
    }

    pthread_mutex_unlock(& m_block_mutex);

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findItem(): find item in block table
// key - block key
// resval - result data
int CDskBlockMan::findItem(char* key, dsk_block_t** resval)
{
    (*resval) = NULL;

    str_t p_key;

    pthread_mutex_lock(& m_block_mutex);

    long flag = DBFALSE;

    int currNumDskBlock = m_currNumDskBlock;
    for(int i = 0; i < currNumDskBlock; i++)
    {
        dsk_block_t* p = &m_arrDskBlock[i];    

        strNCpyUtil(p_key, p->key, STRSZ);
        if(strNCmpUtil(p_key, key, STRSZ) == 0) {
            (*resval) = p;

            flag = DBTRUE;
            break;
        }
    }

    pthread_mutex_unlock(& m_block_mutex);

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findFirstFreeBlock(): find first free item in block table
// path_oid - file path oid
// block_num - block number
// resval - result data
// block_oid - return block oid
// int CDskBlockMan::findFirstFreeBlock(
//     long path_oid,
//     long block_num,
//     dsk_block_t** resval, 
//     long* block_oid,
//     long* block_sector)
// {
//     (*resval) = NULL;
//
//     (*block_oid) = DBNULL_LONG;
//     (*block_sector) = DBNULL_LONG;
//
//     CSequence* seq = gAppMain.getSequencePtr();
//
//     int currNumDskBlock = getCurrNumDskBlock();
//     for(int i = 0; i < currNumDskBlock; i++) {
//         dsk_block_t* p = & m_arrDskBlock[i];    
//
//         pthread_mutex_lock(& m_block_mutex);
//         long p_is_valid = p->is_valid;
//         pthread_mutex_unlock(& m_block_mutex);
//
//         if(p_is_valid == DBFALSE) {
//             (*resval) = p;
//             break;
//         }
//     }
//
//     if((*resval) != NULL)
//     {
//         pthread_mutex_lock(& m_block_mutex);
//
//         (*resval)->path_oid     = path_oid;
//         (*resval)->block_num    = block_num;
//         (*resval)->is_valid     = DBTRUE;
//countItemsByPathOid
//         (*block_oid) = (*resval)->oid;
//         (*block_sector) = (*resval)->block_sector;
//
//         pthread_mutex_unlock(& m_block_mutex);
//     }
//     else
//     {
//         pthread_mutex_lock(& m_block_mutex);
//
//         long flag = DBFALSE;
//         if(m_currNumDskBlock < m_maxNumDskBlock) {
//             (*block_oid) = seq->nextVal((char*)SEQ_TABLE_BLOCK);
//             (*block_sector) = m_currNumDskBlock;
//
//             (*resval) = & m_arrDskBlock[m_currNumDskBlock];
//             m_currNumDskBlock++;
//
//             flag = DBTRUE;
//         }
//
//         pthread_mutex_unlock(& m_block_mutex);
//
//         if(flag == DBTRUE)
//         {
//             str_t key;
//             sprintf(key, "%ld_%ld", path_oid, block_num);
//
//             setItemData(
//                 resval,
//                 (*block_oid),
//                 path_oid,
//                 block_num,
//                 (*block_sector),
//                 DBTRUE,
//                 key);
//         }
//     }
//
//     if((*resval) != NULL)
//         return(RSOK);
//
//     return(RSERR);
// }

// findFirstFreeBlock(): find first free item in block table
// path_oid - file path oid
// block_num - block number
// resval - result data
// block_oid - return block oid
int CDskBlockMan::findFirstFreeBlock(
    long path_oid,
    long block_num,
    dsk_block_t** resval, 
    long* block_oid,
    long* block_sector)
{
    (*resval) = NULL;

    (*block_oid) = DBNULL_LONG;
    (*block_sector) = DBNULL_LONG;

    CSequence* seq = gAppMain.getSequencePtr();

    pthread_mutex_lock(& m_block_mutex);

    int currNumDskBlock = m_currNumDskBlock;
    if(currNumDskBlock < m_maxNumDskBlock) {
        /* nothing todo! */
    }
    else {
        for(int i = 0; i < currNumDskBlock; i++) {
            dsk_block_t* p = & m_arrDskBlock[i];    

            long p_is_valid = p->is_valid;
            if(p_is_valid == DBFALSE) {
                (*resval) = p;
                break;
            }
        }
    }
    
    if((*resval) != NULL)
    {
        (*resval)->path_oid     = path_oid;
        (*resval)->block_num    = block_num;
        (*resval)->is_valid     = DBTRUE;

        (*block_oid) = (*resval)->oid;
        (*block_sector) = (*resval)->block_sector;
    }
    else
    {
        long flag = DBFALSE;
        if(m_currNumDskBlock < m_maxNumDskBlock) {
            (*block_oid) = seq->nextVal((char*)SEQ_TABLE_BLOCK);
            (*block_sector) = m_currNumDskBlock;

            (*resval) = & m_arrDskBlock[m_currNumDskBlock];
            m_currNumDskBlock++;

            flag = DBTRUE;
        }

        if(flag == DBTRUE)
        {
            str_t key;
            sprintf(key, "%ld_%ld", path_oid, block_num);

            //setItemData(
            //    resval,
            //    (*block_oid),
            //    path_oid,
            //    block_num,
            //    (*block_sector),
            //    DBTRUE,
            //    key);

            (*resval)->oid          = (*block_oid);
            (*resval)->path_oid     = path_oid;
            (*resval)->block_num    = block_num;
            (*resval)->block_sector = (*block_sector);
            (*resval)->is_valid     = DBTRUE;
            strNCpyUtil((*resval)->key, (char*)key, STRSZ);
        }
    }

    pthread_mutex_unlock(& m_block_mutex);

    if((*resval) != NULL) {
        m_pBlockIndex->addIndexItem((*resval)->path_oid, (*resval));
        return(RSOK);
    }

    return(RSERR);
}

// findBlockByBlockNum(): find block item by block number
// path_oid - file path oid
// block_num - block number
// resval - result data
// block_oid - return block oid
// block_sector - return block sector
// int CDskBlockMan::findBlockByBlockNum(
//     long path_oid, 
//     long block_num, 
//     dsk_block_t** resval, 
//     long* block_oid,
//     long* block_sector)
// {
//     (*resval) = NULL;
//     (*block_oid) = DBNULL_LONG;

//     int currNumDskBlock = getCurrNumDskBlock();
//     for(int i = 0; i < currNumDskBlock; i++) {
//         dsk_block_t* p = & m_arrDskBlock[i];

//         pthread_mutex_lock(& m_block_mutex);
//         long p_is_valid = p->is_valid;
//         long p_path_oid = p->path_oid;
//         long p_block_num = p->block_num;
//         long p_block_oid = p->oid;
//         long p_block_sector = p->block_sector;
//         pthread_mutex_unlock(& m_block_mutex);

//         if(p_is_valid == DBTRUE) {
//             if((p_path_oid == path_oid) && (p_block_num == block_num)) {
//                 (*resval) = p;
//                 (*block_oid) = p_block_oid;
//                 (*block_sector) = p_block_sector;
//                 return(RSOK);
//             }
//         }
//     }

//     return(RSERR);
// }

// findBlockByBlockNum(): find block item by block number
// path_oid - file path oid
// block_num - block number
// resval - result data
// block_oid - return block oid
// block_sector - return block sector
int CDskBlockMan::findBlockByBlockNum(
    long path_oid, 
    long block_num, 
    dsk_block_t** resval, 
    long* block_oid,
    long* block_sector)
{
    (*resval) = NULL;
    (*block_oid) = DBNULL_LONG;

    long flag = DBFALSE;

    dsk_block_idx_t* p_idx = NULL;
    int rscode = m_pBlockIndex->findIndexItem(path_oid, & p_idx);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_block_mutex);

        CIdxDoubleLinkedList* pLsBlock = p_idx->pLsBlock;
        if(pLsBlock != NULL) {
            CIdxDescriptor* p_descr = pLsBlock->getDescriptorPtr();

            CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
            dsk_block_t* p = NULL;
            while(p_src != NULL) {
                p = (dsk_block_t*)p_src->getEntryObjPtr();

                long p_is_valid = p->is_valid;
                long p_path_oid = p->path_oid;
                long p_block_num = p->block_num;
                long p_block_oid = p->oid;
                long p_block_sector = p->block_sector;

                if(p_is_valid == DBTRUE) {
                    if((p_path_oid == path_oid) && (p_block_num == block_num)) {
                        (*resval) = p;
                        (*block_oid) = p_block_oid;
                        (*block_sector) = p_block_sector;

                        flag = DBTRUE;
                        break;
                    }
                }
                p_src = p_src->getEntryNextPtr();
            }
        }

        pthread_mutex_unlock(& m_block_mutex);
    }
    else {
        pthread_mutex_lock(& m_block_mutex);

        int currNumDskBlock = m_currNumDskBlock;
        for(int i = 0; i < currNumDskBlock; i++) {
            dsk_block_t* p = & m_arrDskBlock[i];

            long p_is_valid = p->is_valid;
            long p_path_oid = p->path_oid;
            long p_block_num = p->block_num;
            long p_block_oid = p->oid;
            long p_block_sector = p->block_sector;

            if(p_is_valid == DBTRUE) {
                if((p_path_oid == path_oid) && (p_block_num == block_num)) {
                    (*resval) = p;
                    (*block_oid) = p_block_oid;
                    (*block_sector) = p_block_sector;

                    flag = DBTRUE;
                    break;
                }
            }
        }

        pthread_mutex_unlock(& m_block_mutex);
    }

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findAll(): find all blocks
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
int CDskBlockMan::findAll(dsk_block_t** arr, long* arrsz)
{
    (*arr) = NULL;
    (*arrsz) = 0;

    pthread_mutex_lock(& m_block_mutex);

    int currNumDskBlock = m_currNumDskBlock;

    long flag = DBFALSE;

    (*arrsz) = currNumDskBlock;
    (*arr) = (dsk_block_t*)allocDataArray(sizeof(dsk_block_t), (*arrsz));
    if((*arr) != NULL) 
    {
        dsk_block_t* p = (*arr);
        for(int i = 0; i < currNumDskBlock; i++) {
            memNCpyUtil((byte*)p, (byte*)&m_arrDskBlock[i], sizeof(dsk_block_t));
            p++;
        }  

        flag = DBTRUE;
    }

    pthread_mutex_unlock(& m_block_mutex);

    if(flag == DBTRUE)
        return(RSOK);
    return(RSERR);
}

// findAllByPathOid(): find all blocks
// path_oid - file path oid
// arr - result data (array of blocks)
// arrsz - return the number of rows in the array
int CDskBlockMan::findAllByPathOid(long path_oid, dsk_block_t** arr, long* arrsz)
{
    (*arr) = NULL;
    (*arrsz) = 0;

    dsk_block_idx_t* p_blockIDX = NULL;

    int rscode = m_pBlockIndex->findIndexItem(path_oid, & p_blockIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_blkDST = p_blockIDX->pLsBlock;
        if(p_blkDST != NULL) {
            CIdxDescriptor* p_descr = p_blkDST->getDescriptorPtr();

            long max_arrsz = p_descr->getNumberOfEntries();
            if(max_arrsz > 0) 
            {
                (*arrsz) = 0;
                (*arr) = (dsk_block_t*)allocDataArray(sizeof(dsk_block_t), max_arrsz);
                if((*arr) != NULL) 
                {
                    pthread_mutex_lock(& m_block_mutex);

                    CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
                    dsk_block_t* p_sbDST = (*arr);
                    dsk_block_t* p_sbSRC = NULL;
                    while(p_src != NULL) {
                        p_sbSRC = (dsk_block_t*)p_src->getEntryObjPtr();

                        long p_path_oid = p_sbSRC->path_oid;
                        if(p_path_oid == path_oid) {
                            memNCpyUtil((byte*)p_sbDST, (byte*)p_sbSRC, sizeof(dsk_block_t));
                            p_sbDST++;

                            (*arrsz) += 1;
                        }
                        p_src = p_src->getEntryNextPtr();
                    }

                    pthread_mutex_unlock(& m_block_mutex);
                }
            }
        }
    }
    else {
        int rscode = countItemsByPathOid(path_oid, arrsz);
        if(rscode == RSOK) {
            if((*arrsz) > 0) {
                (*arr) = (dsk_block_t*)allocDataArray(sizeof(dsk_block_t), (*arrsz));
                if((*arr) != NULL) {
                    int pos_dst = 0;
                    dsk_block_t* p_dst = & (*arr)[pos_dst];

                    pthread_mutex_lock(& m_block_mutex);

                    int currNumDskBlock = m_currNumDskBlock;
                    for(int i = 0; i < currNumDskBlock; i++) {
                        dsk_block_t* p_src = & m_arrDskBlock[i];

                        long p_path_oid = p_src->path_oid;
                        if(p_path_oid == path_oid) {
                            memNCpyUtil((byte*) p_dst, (byte*) p_src, sizeof(dsk_block_t));

                            pos_dst += 1;
                            p_dst = & (*arr)[pos_dst];
                        }
                    }  

                    pthread_mutex_unlock(& m_block_mutex);

                    return(RSOK);
                }
            }
        }
    }
    return(RSERR);
}

// countItemsByPathOid(): caount all blocks with path oid
// path_oid - file path oid
// num_items - return the number of items
int CDskBlockMan::countItemsByPathOid(long path_oid, long* num_items)
{
    (*num_items) = 0;

    pthread_mutex_lock(& m_block_mutex);

    dsk_block_idx_t* p_blockIDX = NULL;

    int rscode = m_pBlockIndex->findIndexItem(path_oid, & p_blockIDX);
    if(rscode == RSOK) {
        CIdxDoubleLinkedList* p_blkDST = p_blockIDX->pLsBlock;
        if(p_blkDST != NULL) {
            CIdxDescriptor* p_descr = p_blkDST->getDescriptorPtr();

            long max_arrsz = p_descr->getNumberOfEntries();
            if(max_arrsz > 0) 
            {
                pthread_mutex_lock(& m_block_mutex);

                CIdxEntry* p_src = p_descr->getFirstEntryPtr();    
                dsk_block_t* p_sbSRC = NULL;
                while(p_src != NULL) {
                    p_sbSRC = (dsk_block_t*)p_src->getEntryObjPtr();

                    long p_path_oid = p_sbSRC->path_oid;
                    if(p_path_oid == path_oid) {
                        (*num_items) += 1;
                    }
                    p_src = p_src->getEntryNextPtr();
                }

                pthread_mutex_unlock(& m_block_mutex);
            }
        }
    }
    else {
        int currNumDskBlock = m_currNumDskBlock;

        dsk_block_t* p = NULL;
        for(int i = 0; i < currNumDskBlock; i++) {
            p = (dsk_block_t*) & m_arrDskBlock[i];

            long p_path_oid = p->path_oid;
            if(p_path_oid == path_oid) {
                (*num_items) += 1;
            }
        }  
    }

    pthread_mutex_unlock(& m_block_mutex);

    return(RSOK);
}

// deleteItem(): mark item as deleted in block table
// oid - block oid
// uid - user id
int CDskBlockMan::deleteItem(long oid, long uid)
{
    int rscode = RSERR;

    dsk_block_t* data = NULL;
    
    rscode = findItem(oid, &data);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_block_mutex);
        data->is_valid  = DBFALSE;
        pthread_mutex_unlock(& m_block_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "deleteItem()", ERR_CANTFINDOBJECTID);
    }

    return(rscode);
}

// deleteItem(): mark item as deleted in block table
// key - block key
// uid - user id
int CDskBlockMan::deleteItem(char* key, long uid)
{
    int rscode = RSERR;

    dsk_block_t* data = NULL;
    
    rscode = findItem(key, &data);
    if(rscode != RSOK) {
        pthread_mutex_lock(& m_block_mutex);
        data->is_valid  = DBFALSE;
        pthread_mutex_unlock(& m_block_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "deleteItem()", ERR_CANTFINDKEY);
    }

    return(rscode);
}

// deleteAllItemByPathOid(): mark all items with same path oid as deleted in block table
// path_oid - file path oid
// uid - user id
int CDskBlockMan::deleteAllItemByPathOid(long path_oid, long uid)
{
    int rscode = RSERR;

    dsk_block_t* data = NULL;
    long datasz = 0;

    rscode = findAllByPathOid(path_oid, &data, & datasz);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_block_mutex);

        for(int i = 0; i < datasz; i++) {
            dsk_block_t* p = & data[i];
            p->is_valid  = DBFALSE;
        }

        pthread_mutex_unlock(& m_block_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "deleteItem()", ERR_CANTFINDPATHOID);
    }

    if(data != NULL)
        freeDataArray(data);
    return(rscode);
}

// copyAllItemByPathOid(): copy all items with same path oid in block table
// spath_oid - source file path oid
// dpath_parent - destination parent path oid
// dpath_oid - destination file path oid
// uid - user id
int CDskBlockMan::copyAllItemByPathOid(long spath_oid, long dpath_parent, long dpath_oid, long uid)
{
    int rscode = RSERR;

    dsk_block_t* data = NULL;
    long datasz = 0;

    rscode = findAllByPathOid(spath_oid, & data, & datasz);
    if(rscode == RSOK) {
        pthread_mutex_lock(& m_block_mutex);

        for(int i = 0; i < datasz; i++) {
            dsk_block_t* p = & data[i];

            if(p->is_valid == DBTRUE) {
                p->path_oid = dpath_oid;
            }
        }

        pthread_mutex_unlock(& m_block_mutex);
    }
    else {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_BLOCKMAN_H, "copyAllItemByPathOid()", ERR_CANTFINDPATHOID);
    }

    if(data != NULL)
        freeDataArray(data);
    return rscode;
}

// newItemData(): mark item as deleted in block table
// data - data reference
// dsk_block_t* CDskBlockMan::newItemData(dsk_block_t** data)
// {
//     long isNew = DBFALSE;
//
//     if((*data) == NULL) {
//         isNew = DBTRUE;
//         (*data) = (dsk_block_t*)allocData(sizeof(dsk_block_t));
//     }
//
//     if(isNew == DBFALSE)
//         pthread_mutex_lock(& m_block_mutex);
//
//     (*data)->oid          = DBNULL_LONG;
//     (*data)->path_oid     = DBNULL_LONG;
//     (*data)->block_num    = DBNULL_LONG;
//     (*data)->block_sector = DBNULL_LONG;
//     (*data)->is_valid     = DBFALSE;
//     strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);
//
//     if(isNew == DBFALSE)
//         pthread_mutex_unlock(& m_block_mutex);
//
//     return (*data);
// }

// newItemData(): mark item as deleted in block table
// data - data reference
dsk_block_t* CDskBlockMan::newItemData(dsk_block_t** data)
{
    if((*data) == NULL)
        (*data) = (dsk_block_t*)allocData(sizeof(dsk_block_t));

    pthread_mutex_lock(& m_block_mutex);

    (*data)->oid          = DBNULL_LONG;
    (*data)->path_oid     = DBNULL_LONG;
    (*data)->block_num    = DBNULL_LONG;
    (*data)->block_sector = DBNULL_LONG;
    (*data)->is_valid     = DBFALSE;
    strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);

    pthread_mutex_unlock(& m_block_mutex);

    return (*data);
}

// setItemData(): add item to block table
// data - return data
// oid - block oid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector number at disk device
// is_valid - block is valid
// key - block key
// bUseMutex - flag indicator to use mutex
// dsk_block_t* CDskBlockMan::setItemData(
//     dsk_block_t** data, 
//     long oid,
//     long path_oid,
//     long block_num,
//     long block_sector,
//     long is_valid,
//     char* key)
// {
//     long isNew = DBFALSE;
//
//     if((*data) == NULL) {
//         isNew = DBTRUE;
//         (*data) = (dsk_block_t*)allocData(sizeof(dsk_block_t));
//     }
//
//     if(isNew == DBFALSE)
//         pthread_mutex_lock(& m_block_mutex);
//
//     (*data)->oid          = oid;
//     (*data)->path_oid     = path_oid;
//     (*data)->block_num    = block_num;
//     (*data)->block_sector = block_sector;
//     (*data)->is_valid     = is_valid;
//     strNCpyUtil((*data)->key, (char*)key, STRSZ);
//
//     if(isNew == DBFALSE)
//         pthread_mutex_unlock(& m_block_mutex);
//
//     return (*data);
// }

// setItemData(): add item to block table
// data - return data
// oid - block oid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector number at disk device
// is_valid - block is valid
// key - block key
// bUseMutex - flag indicator to use mutex
dsk_block_t* CDskBlockMan::setItemData(
    dsk_block_t** data, 
    long oid,
    long path_oid,
    long block_num,
    long block_sector,
    long is_valid,
    char* key)
{
    if((*data) == NULL) 
        (*data) = (dsk_block_t*)allocData(sizeof(dsk_block_t));
        
    pthread_mutex_lock(& m_block_mutex);
        
    (*data)->oid          = oid;
    (*data)->path_oid     = path_oid;
    (*data)->block_num    = block_num;
    (*data)->block_sector = block_sector;
    (*data)->is_valid     = is_valid;
    strNCpyUtil((*data)->key, (char*)key, STRSZ);

    pthread_mutex_unlock(& m_block_mutex);

    return (*data);
}

// setItemData_NotThreadSafe(): add item to block table (not thread safe - internal class use only)
// data - return data
// oid - block oid
// path_oid - file path oid
// block_num - block number at disk device
// block_sector - block sector number at disk device
// is_valid - block is valid
// key - block key
// bUseMutex - flag indicator to use mutex
dsk_block_t* CDskBlockMan::setItemData_NotThreadSafe(
    dsk_block_t** data, 
    long oid,
    long path_oid,
    long block_num,
    long block_sector,
    long is_valid,
    char* key)
{
    if((*data) == NULL) 
        (*data) = (dsk_block_t*)allocData(sizeof(dsk_block_t));
        
    (*data)->oid          = oid;
    (*data)->path_oid     = path_oid;
    (*data)->block_num    = block_num;
    (*data)->block_sector = block_sector;
    (*data)->is_valid     = is_valid;
    strNCpyUtil((*data)->key, (char*)key, STRSZ);

    return (*data);
}

/* Debug */

// debug(): show all blocks
// debugLevel - debug level
// className - class name
// methodName - method name
void CDskBlockMan::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    int currNumDskBlock = getCurrNumDskBlock();

    dsk_block_t* p = NULL;
    for(int i = 0; i < currNumDskBlock; i++)
    {
        p = & m_arrDskBlock[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show block
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a block entry
void CDskBlockMan::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_block_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    pthread_mutex_lock(& m_block_mutex);

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "BlockMan: Oid=%ld,PathOid=%ld,BlockNum=%ld,BlockSector=%ld,IsValid=%ld,Key=%s\n",
        p->oid,
        p->path_oid,
        p->block_num,
        p->block_sector,
        p->is_valid,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);

    pthread_mutex_unlock(& m_block_mutex);
}

/* Getters/Setters */

char* CDskBlockMan::getBlockTableFile()
{
    return m_blockTableFile;
}

int CDskBlockMan::getMaxNumDskBlock()
{
    return m_maxNumDskBlock;
}

int CDskBlockMan::getCurrNumDskBlock()
{
    pthread_mutex_lock(& m_block_mutex);

    int currNumDskBlock = m_currNumDskBlock;

    pthread_mutex_unlock(& m_block_mutex);

    return currNumDskBlock;
}
