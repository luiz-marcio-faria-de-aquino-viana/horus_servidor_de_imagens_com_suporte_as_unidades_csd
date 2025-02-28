/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_superblockidx.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 05/04/2022
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

// SUPERBLOCK INDEX MUTEX
pthread_mutex_t m_superblock_index_mutex;

CDskSuperBlockIdx::CDskSuperBlockIdx(int maxNumDskSuperBlockIndex)
{
    init(maxNumDskSuperBlockIndex);
}

CDskSuperBlockIdx::~CDskSuperBlockIdx()
{
    terminate();
}

// init(): initiate superblock index
void CDskSuperBlockIdx::init(int maxNumDskSuperBlockIndex)
{
    m_maxNumDskSuperBlockIndex = maxNumDskSuperBlockIndex; 
    m_arrDskSuperBlockIndex = (dsk_superblock_index_t*)allocDataArray(sizeof(dsk_superblock_index_t), m_maxNumDskSuperBlockIndex);
    m_currNumDskSuperBlockIndex = 0;

    for(int i = 0; i < m_maxNumDskSuperBlockIndex; i++) {
        dsk_superblock_index_t* p_idx = & m_arrDskSuperBlockIndex[i];
        initIndexItem(i, p_idx);

        m_currNumDskSuperBlockIndex++;
    }
}

// terminate(): terminate superblock index
void CDskSuperBlockIdx::terminate()
{
    for(int i = 0; i < m_maxNumDskSuperBlockIndex; i++) {
        dsk_superblock_index_t* p_idx = & m_arrDskSuperBlockIndex[i];
        termIndexItem(p_idx);
    }
    freeDataArray(m_arrDskSuperBlockIndex);
}

// initIndexItem(): initialize superblock index item
// p_idx - pointer superblock index item
void CDskSuperBlockIdx::initIndexItem(long oid, dsk_superblock_index_t* p_idx)
{
    p_idx->oid = oid;
    p_idx->is_valid = DBFALSE;

    if(p_idx->pLsSuperblock == NULL) {
        p_idx->pLsSuperblock = new CIdxDoubleLinkedList(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_CRESCENT);
    }
    else {
        (p_idx->pLsSuperblock)->removeAll();
    }
}

// termIndexItem(): terminate superblock index
// p_idx - pointer superblock index item
void CDskSuperBlockIdx::termIndexItem(dsk_superblock_index_t* p_idx)
{
    //p_idx->path_oid = DBNULL_LONG;
    p_idx->is_valid = DBFALSE;

    if(p_idx->pLsSuperblock != NULL) {
        (p_idx->pLsSuperblock)->removeAll();
        delete(p_idx->pLsSuperblock);
    }
}

/* Methodes */

// addIndexItem(): add superblock index item
// path_oid - file path oid
// p_sb - pointer to superblock
int CDskSuperBlockIdx::addIndexItem(long path_oid, dsk_superblock_t* p_sb)
{
    long result = RSERR;

    pthread_mutex_lock(& m_superblock_index_mutex);

    dsk_superblock_index_t* p_idx = NULL;
    if(this->setIndexItemData_NotThreadSafe(& p_idx, path_oid, p_sb) != NULL)
        result = RSOK;

    pthread_mutex_unlock(& m_superblock_index_mutex);

    return(result);
}

// findIndexItem(): find superblock from index
// path_oid - file path oid
// p_idx - pointer to superblock index
int CDskSuperBlockIdx::findIndexItem(long path_oid, dsk_superblock_index_t** p_idx)
{
    long result = RSERR;

    (*p_idx) = NULL;

    pthread_mutex_lock(& m_superblock_index_mutex);

    int pos_idx = (path_oid % m_maxNumDskSuperBlockIndex);
    
    dsk_superblock_index_t* p = & m_arrDskSuperBlockIndex[pos_idx];
    if(p->is_valid == DBTRUE) {
        (*p_idx) = p;
        result = RSOK;
    }

    pthread_mutex_unlock(& m_superblock_index_mutex);

    return(result);
}

// setIndexItemData(): add index item to superblock index table
// data - return data
// block_num - block number at disk device
// p_sb - pointer to superblock
dsk_superblock_index_t* CDskSuperBlockIdx::setIndexItemData(dsk_superblock_index_t** data, long path_oid, dsk_superblock_t* p_sb)
{
    pthread_mutex_lock(& m_superblock_index_mutex);

    this->setIndexItemData_NotThreadSafe(data, path_oid, p_sb);

    pthread_mutex_unlock(& m_superblock_index_mutex);

    return(*data);
}

// setIndexItemData_NotThreadSafe(): add index item to superblock index table not thread safe (internal class use only)
// data - return data
// path_oid - file path oid
// p_sb - pointer to superblock
dsk_superblock_index_t* CDskSuperBlockIdx::setIndexItemData_NotThreadSafe(dsk_superblock_index_t** data, long path_oid, dsk_superblock_t* p_sb)
{
    int pos_idx = (path_oid % m_maxNumDskSuperBlockIndex);
    
    (*data) = & m_arrDskSuperBlockIndex[pos_idx];
    (*data)->is_valid = DBTRUE;

    CIdxDescriptor* p_descr = ((*data)->pLsSuperblock)->getDescriptorPtr();
    CIdxEntry* p_entry = new CIdxEntry(p_descr, p_sb->block_num, p_sb);
    if(p_entry != NULL) {   
        ((*data)->pLsSuperblock)->insertNewEntry(p_entry);
    }

    return(*data);
}

/* Debug */

// debug(): show all blocks
// debugLevel - debug level
// className - class name
// methodName - method name
void CDskSuperBlockIdx::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    int currNumDskSuperBlockIndex = getCurrNumDskSuperBlockIndex();

    dsk_superblock_index_t* p = NULL;
    for(int i = 0; i < currNumDskSuperBlockIndex; i++)
    {
        p = & m_arrDskSuperBlockIndex[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show block
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a superblock index entry
void CDskSuperBlockIdx::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_superblock_index_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;

    pthread_mutex_lock(& m_superblock_index_mutex);

    CIdxDescriptor* p_descr = (p->pLsSuperblock)->getDescriptorPtr();

    sprintf(
        errmsg, 
        "SuperBlockIdx: Oid=%ld,IsValid=%ld,NumberOfEntries=%ld\n",
        p->oid,
        p->is_valid,
        p_descr->getNumberOfEntries());
    warnMsg(debugLevel, className, methodName, errmsg);

    pthread_mutex_unlock(& m_superblock_index_mutex);
}

/* Getters/Setters */

int CDskSuperBlockIdx::getMaxNumDskSuperBlockIndex()
{
    return m_maxNumDskSuperBlockIndex;
}

int CDskSuperBlockIdx::getCurrNumDskSuperBlockIndex()
{
    pthread_mutex_lock(& m_superblock_index_mutex);

    int currNumDskSuperBlockIndex = m_currNumDskSuperBlockIndex;

    pthread_mutex_unlock(& m_superblock_index_mutex);

    return currNumDskSuperBlockIndex;
}
