/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_superblockidx.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 05/04/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_SUPERBLOCKIDX_H
#define __HORUSWRK_DSK_SUPERBLOCKIDX_H                  "__HORUSWRK_DSK_SUPERBLOCKIDX_H"

class CDskSuperBlockIdx
{
private:
    dsk_superblock_index_t* m_arrDskSuperBlockIndex;
    int m_maxNumDskSuperBlockIndex;
    int m_currNumDskSuperBlockIndex;

    // SUPERBLOCK INDEX MUTEX
    //pthread_mutex_t m_superblockidx_mutex;

public:

    CDskSuperBlockIdx(int maxNumDskSuperBlockIndex);
    ~CDskSuperBlockIdx();

    // init(): initiate superblock index
    void init(int maxNumDskSuperBlockIndex);

    // terminate(): terminate superblock index
    void terminate();

    // initIndexItem(): initialize superblock index item
    // p_idx - pointer superblock index item
    void initIndexItem(long oid, dsk_superblock_index_t* p_idx);

    // termIndexItem(): terminate superblock index
    // p_idx - pointer superblock index item
    void termIndexItem(dsk_superblock_index_t* p_idx);

    /* Methodes */

    // addIndexItem(): add superblock index item
    // path_oid - file path oid
    // p_sb - pointer to superblock
    int addIndexItem(long path_oid, dsk_superblock_t* p_sb);

    // findIndexItem(): find superblock from index
    // path_oid - file path oid
    // p_idx - pointer to superblock index
    int findIndexItem(long path_oid, dsk_superblock_index_t** p_idx);

    // setIndexItemData(): add index item to superblock index table
    // data - return data
    // block_num - block number at disk device
    // p_sb - pointer to superblock
    dsk_superblock_index_t* setIndexItemData(dsk_superblock_index_t** data, long path_oid, dsk_superblock_t* p_sb);

    // setIndexItemData_NotThreadSafe(): add index item to superblock index table not thread safe (internal class use only)
    // data - return data
    // path_oid - file path oid
    // p_sb - pointer to superblock
    dsk_superblock_index_t* setIndexItemData_NotThreadSafe(dsk_superblock_index_t** data, long path_oid, dsk_superblock_t* p_sb);

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
    void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_superblock_index_t* p);

    /* Getters/Setters */

    int getMaxNumDskSuperBlockIndex();

    int getCurrNumDskSuperBlockIndex();

};

/* NEW_TYPE: CDskSuperBlockIdx Pointer */

typedef CDskSuperBlockIdx* CDskSuperBlockIdxPtr_t;

#endif
