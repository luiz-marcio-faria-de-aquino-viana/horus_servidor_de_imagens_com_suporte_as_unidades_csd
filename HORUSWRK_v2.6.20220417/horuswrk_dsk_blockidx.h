/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_blockidx.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 13/04/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_BLOCKIDX_H
#define __HORUSWRK_DSK_BLOCKIDX_H                  "__HORUSWRK_DSK_BLOCKIDX_H"

class CDskBlockIdx
{
private:
    dsk_block_idx_t* m_arrDskBlockIndex;
    int m_maxNumDskBlockIndex;
    int m_currNumDskBlockIndex;

    // BLOCK INDEX MUTEX
    //pthread_mutex_t m_blockidx_mutex;

public:

    CDskBlockIdx(int maxNumDskBlockIndex);
    ~CDskBlockIdx();

    // init(): initiate block index
    void init(int maxNumDskBlockIndex);

    // terminate(): terminate block index
    void terminate();

    // initIndexItem(): initialize block index item
    // p_idx - pointer superblock index item
    void initIndexItem(long oid, dsk_block_idx_t* p_idx);

    // termIndexItem(): terminate block index
    // p_idx - pointer block index item
    void termIndexItem(dsk_block_idx_t* p_idx);

    /* Methodes */

    // addIndexItem(): add block index item
    // path_oid - file path oid
    // p_sb - pointer to superblock
    int addIndexItem(long path_oid, dsk_block_t* p_sb);

    // findIndexItem(): find block from index
    // path_oid - file path oid
    // p_idx - pointer to block index
    int findIndexItem(long path_oid, dsk_block_idx_t** p_idx);

    // setIndexItemData(): add index item to block index table
    // data - return data
    // block_num - block number at disk device
    // p_sb - pointer to block
    dsk_block_idx_t* setIndexItemData(dsk_block_idx_t** data, long path_oid, dsk_block_t* p_sb);

    // setIndexItemData_NotThreadSafe(): add index item to block index table not thread safe (internal class use only)
    // data - return data
    // path_oid - file path oid
    // p_sb - pointer to block
    dsk_block_idx_t* setIndexItemData_NotThreadSafe(dsk_block_idx_t** data, long path_oid, dsk_block_t* p_sb);

    /* Debug */

    // debug(): show all blocks
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debugEntry(): show block
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    // p - pointer to a superblock index entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_block_idx_t* p);

    /* Getters/Setters */

    int getMaxNumDskBlockIndex();

    int getCurrNumDskBlockIndex();

};

/* NEW_TYPE: CDskBlockIdx Pointer */

typedef CDskBlockIdx* CDskBlockIdxPtr_t;

#endif
