/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_blockman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_BLOCKMAN_H
#define __HORUSWRK_DSK_BLOCKMAN_H                      "__HORUSWRK_DSK_BLOCKMAN_H"

class CDskBlockMan
{
private:
    bigstr_t m_blockTableFile;
    pathname_t m_blockTableFilePath;

    dsk_block_t* m_arrDskBlock;
    int m_maxNumDskBlock;
    int m_currNumDskBlock;

    CDskBlockIdx* m_pBlockIndex;

    // BLOCK MUTEX
    //pthread_mutex_t m_block_mutex;

public:
    CDskBlockMan(int maxNumDskBlock, char* blockTableFile, char* blockTableFilePath);
    ~CDskBlockMan();

    // init(): initiate block manager
    void init(int maxNumDskBlock, char* blockTableFile, char* blockTableFilePath);

    // term(): terminate block manager
    void terminate();

    /* Methodes */

    // loadFile(): load table of blocks from file
    // fileName - block's table file name
    int loadFile(char* fileName);

    // saveFile(): save table of blocks to file
    // fileName - block's table file name
    int saveFile(char* fileName);

    // addItem(): add item to block table
    // path_oid - file path oid
    // block_num - block number at disk device
    // block_sector - block sector at disk device
    // block_oid - return block oid
    int addItem(
        long path_oid,
        long block_num,
        long block_sector,
        long* block_oid);

    // findItem(): find item in block table
    // oid - block oid
    // resval - result data
    int findItem(long oid, dsk_block_t** resval);

    // findItem(): find item in block table
    // key - block key
    // resval - result data
    int findItem(char* key, dsk_block_t** resval);

    // findFirstFreeBlock(): find first free item in block table
    // path_oid - file path oid
    // block_num - block number
    // resval - result data
    // block_oid - return block oid
    int findFirstFreeBlock(
        long path_oid,
        long block_num,
        dsk_block_t** resval, 
        long* block_oid,
        long* block_sector);

    // findBlockByBlockNum(): find block item by block number
    // path_oid - file path oid
    // block_num - block number
    // resval - result data
    // block_oid - return block oid
    int findBlockByBlockNum(
        long path_oid, 
        long block_num, 
        dsk_block_t** resval, 
        long* block_oid,
        long* block_sector);

    // findAll(): find all blocks
    // arr - result data (array of blocks)
    // arrsz - return the number of rows in the array
    int findAll(dsk_block_t** arr, long* arrsz);

    // findAllByPathOid(): find all blocks
    // path_oid - file path oid
    // arr - result data (array of blocks)
    // arrsz - return the number of rows in the array
    int findAllByPathOid(long path_oid, dsk_block_t** arr, long* arrsz);

    // countItemsByPathOid(): caount all blocks with path oid
    // path_oid - file path oid
    // num_items - return the number of items
    int countItemsByPathOid(long path_oid, long* num_items);

    // deleteItem(): mark item as deleted in block table
    // oid - block oid
    // uid - user id
    int deleteItem(long oid, long uid);

    // deleteItem(): mark item as deleted in block table
    // key - block key
    // uid - user id
    int deleteItem(char* key, long uid);

    // deleteAllItemByPathOid(): mark all items with same path oid as deleted in block table
    // path_oid - file path oid
    // uid - user id
    int deleteAllItemByPathOid(long path_oid, long uid);

    // copyAllItemByPathOid(): copy all items with same path oid in block table
    // spath_oid - source file path oid
    // dpath_parent - destination parent path oid
    // dpath_oid - destination file path oid
    // uid - user id
    int copyAllItemByPathOid(long spath_oid, long dpath_parent, long dpath_oid, long uid);

    // newItemData(): mark item as deleted in block table
    // data - data reference
    dsk_block_t* newItemData(dsk_block_t** data);

    // setItemData(): add item to block table
    // data - return data
    // oid - block oid
    // path_oid - file path oid
    // block_num - block number at disk device
    // block_sector - block sector number at disk device
    // is_valid - block is valid
    // key - block key
    dsk_block_t* setItemData(
        dsk_block_t** data, 
        long oid,
        long path_oid,
        long block_num,
        long block_sector,
        long is_valid,
        char* key);

    // setItemData_NotThreadSafe(): add item to block table (not thread safe - internal class use only)
    // data - return data
    // oid - block oid
    // path_oid - file path oid
    // block_num - block number at disk device
    // block_sector - block sector number at disk device
    // is_valid - block is valid
    // key - block key
    // bUseMutex - flag indicator to use mutex
    dsk_block_t* setItemData_NotThreadSafe(
        dsk_block_t** data, 
        long oid,
        long path_oid,
        long block_num,
        long block_sector,
        long is_valid,
        char* key);

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
    // p - pointer to a block entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_block_t* p);

    /* Getters/Setters */

    char* getBlockTableFile();

    int getMaxNumDskBlock();

    int getCurrNumDskBlock();

};

/* NEW_TYPE: CDskBlockMan Pointer */

typedef CDskBlockMan* CDskBlockManPtr_t;

#endif
