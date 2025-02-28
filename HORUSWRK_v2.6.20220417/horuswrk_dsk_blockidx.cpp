/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_blockidx.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 13/04/2022
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

// BLOCK INDEX MUTEX
pthread_mutex_t m_block_index_mutex;

CDskBlockIdx::CDskBlockIdx(int maxNumDskBlockIndex)
{
    init(maxNumDskBlockIndex);
}

CDskBlockIdx::~CDskBlockIdx()
{
    terminate();
}

// init(): initiate block index
void CDskBlockIdx::init(int maxNumDskBlockIndex)
{
    m_maxNumDskBlockIndex = maxNumDskBlockIndex; 
    m_arrDskBlockIndex = (dsk_block_idx_t*)allocDataArray(sizeof(dsk_block_idx_t), m_maxNumDskBlockIndex);
    m_currNumDskBlockIndex = 0;

    for(int i = 0; i < m_maxNumDskBlockIndex; i++) {
        dsk_block_idx_t* p_idx = & m_arrDskBlockIndex[i];
        initIndexItem(i, p_idx);

        m_currNumDskBlockIndex++;
    }
}

// terminate(): terminate block index
void CDskBlockIdx::terminate()
{
    for(int i = 0; i < m_maxNumDskBlockIndex; i++) {
        dsk_block_idx_t* p_idx = & m_arrDskBlockIndex[i];
        termIndexItem(p_idx);
    }
    freeDataArray(m_arrDskBlockIndex);
}

// initIndexItem(): initialize block index item
// p_idx - pointer block index item
void CDskBlockIdx::initIndexItem(long oid, dsk_block_idx_t* p_idx)
{
    p_idx->oid = oid;
    p_idx->is_valid = DBFALSE;

    if(p_idx->pLsBlock == NULL) {
        p_idx->pLsBlock = new CIdxDoubleLinkedList(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_CRESCENT);
    }
    else {
        (p_idx->pLsBlock)->removeAll();
    }
}

// termIndexItem(): terminate block index
// p_idx - pointer block index item
void CDskBlockIdx::termIndexItem(dsk_block_idx_t* p_idx)
{
    //p_idx->path_oid = DBNULL_LONG;
    p_idx->is_valid = DBFALSE;

    if(p_idx->pLsBlock != NULL) {
        (p_idx->pLsBlock)->removeAll();
        delete(p_idx->pLsBlock);
    }
}

/* Methodes */

// addIndexItem(): add block index item
// path_oid - file path oid
// p_sb - pointer to block
int CDskBlockIdx::addIndexItem(long path_oid, dsk_block_t* p_sb)
{
    long result = RSERR;

    pthread_mutex_lock(& m_block_index_mutex);

    dsk_block_idx_t* p_idx = NULL;
    if(this->setIndexItemData_NotThreadSafe(& p_idx, path_oid, p_sb) != NULL)
        result = RSOK;

    pthread_mutex_unlock(& m_block_index_mutex);

    return(result);
}

// findIndexItem(): find block from index
// path_oid - file path oid
// p_idx - pointer to block index
int CDskBlockIdx::findIndexItem(long path_oid, dsk_block_idx_t** p_idx)
{
    long result = RSERR;

    (*p_idx) = NULL;

    pthread_mutex_lock(& m_block_index_mutex);

    int pos_idx = (path_oid % m_maxNumDskBlockIndex);
    
    dsk_block_idx_t* p = & m_arrDskBlockIndex[pos_idx];
    if(p->is_valid == DBTRUE) {
        (*p_idx) = p;
        result = RSOK;
    }

    pthread_mutex_unlock(& m_block_index_mutex);

    return(result);
}

// setIndexItemData(): add index item to block index table
// data - return data
// block_num - block number at disk device
// p_sb - pointer to block
dsk_block_idx_t* CDskBlockIdx::setIndexItemData(dsk_block_idx_t** data, long path_oid, dsk_block_t* p_sb)
{
    pthread_mutex_lock(& m_block_index_mutex);

    this->setIndexItemData_NotThreadSafe(data, path_oid, p_sb);

    pthread_mutex_unlock(& m_block_index_mutex);

    return(*data);
}

// setIndexItemData_NotThreadSafe(): add index item to block index table not thread safe (internal class use only)
// data - return data
// path_oid - file path oid
// p_sb - pointer to superblock
dsk_block_idx_t* CDskBlockIdx::setIndexItemData_NotThreadSafe(dsk_block_idx_t** data, long path_oid, dsk_block_t* p_sb)
{
    int pos_idx = (path_oid % m_maxNumDskBlockIndex);
    
    (*data) = & m_arrDskBlockIndex[pos_idx];
    (*data)->is_valid = DBTRUE;

    CIdxDescriptor* p_descr = ((*data)->pLsBlock)->getDescriptorPtr();
    CIdxEntry* p_entry = new CIdxEntry(p_descr, p_sb->block_num, p_sb);
    if(p_entry != NULL) {   
        ((*data)->pLsBlock)->insertNewEntry(p_entry);
    }

    return(*data);
}

/* Debug */

// debug(): show all blocks
// debugLevel - debug level
// className - class name
// methodName - method name
void CDskBlockIdx::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    int currNumDskBlockIndex = getCurrNumDskBlockIndex();

    dsk_block_idx_t* p = NULL;
    for(int i = 0; i < currNumDskBlockIndex; i++)
    {
        p = & m_arrDskBlockIndex[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show block
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a superblock index entry
void CDskBlockIdx::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_block_idx_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;

    pthread_mutex_lock(& m_block_index_mutex);

    CIdxDescriptor* p_descr = (p->pLsBlock)->getDescriptorPtr();

    sprintf(
        errmsg, 
        "BlockIdx: Oid=%ld,IsValid=%ld,NumberOfEntries=%ld\n",
        p->oid,
        p->is_valid,
        p_descr->getNumberOfEntries());
    warnMsg(debugLevel, className, methodName, errmsg);

    pthread_mutex_unlock(& m_block_index_mutex);
}

/* Getters/Setters */

int CDskBlockIdx::getMaxNumDskBlockIndex()
{
    return m_maxNumDskBlockIndex;
}

int CDskBlockIdx::getCurrNumDskBlockIndex()
{
    pthread_mutex_lock(& m_block_index_mutex);

    int currNumDskBlockIndex = m_currNumDskBlockIndex;

    pthread_mutex_unlock(& m_block_index_mutex);

    return currNumDskBlockIndex;
}
