/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_superblockman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 22/08/2021
 * revisoes: 
 *   Luiz Marcio Faria de Aquino Viana, M.Sc. - Implementacao da lista de Superblock usando tabelas hash como indice dos dados (path_oid, block_num, block_sector) - 05/02/2022
 *
 */

#ifndef __HORUSWRK_DSK_SUPERBLOCKMAN_H
#define __HORUSWRK_DSK_SUPERBLOCKMAN_H                  "__HORUSWRK_DSK_SUPERBLOCKMAN_H"

class CDskSuperBlockMan
{
private:
    bigstr_t m_superBlockTableFile;
    pathname_t m_superBlockTableFilePath;

    dsk_superblock_t* m_arrDskSuperBlock;
    int m_maxNumDskSuperBlock;
    int m_currNumDskSuperBlock;

    CDskSuperBlockIdx* m_pSuperBlockIndex;

    // SUPERBLOCK MUTEX
    //pthread_mutex_t m_superblock_mutex;

public:
    CDskSuperBlockMan(int maxNumDskSuperBlock, char* superBlockTableFile, char* superBlockTableFilePath);
    ~CDskSuperBlockMan();

    // init(): initiate block manager
    void init(int maxNumDskSuperBlock, char* superBlockTableFile, char* superBlockTableFilePath);

    // term(): terminate block manager
    void terminate();

    // initSuperBlockIndex(): initialize superblock index
    void initSuperBlockIndex();

    // termSuperBlockIndex(): terminate superblock index
    void termSuperBlockIndex();

    /* Methodes */

    // loadFile(): load table of blocks from file
    // fileName - block's table file name
    int loadFile(char* fileName);

    // saveFile(): save table of blocks to file
    // fileName - block's table file name
    int saveFile(char* fileName);

    // addItem(): add item to block table
    // disk_group - disk device group
    // disk_dev - disk device oid
    // path_oid - file path oid
    // block_num - block number at disk device
    // block_sector - block sector at disk device
    // incr_read_val - increment read value
    // incr_write_val - increment write value
    // uid - user id
    // superblock_oid - return superblock oid
    int addItem(
        long disk_group,
        long disk_dev,
        long path_oid,
        long block_num,
        long block_sector,
        long incr_read_val,
        long incr_write_val,
        long uid,
        long* superblock_oid);

    // addIndexItem(): add superblock index item
    // p_sb - pointer to superblock
    int addIndexItem(dsk_superblock_t* p_sb);

    // findIndexItem(): find superblock from index
    // path_oid - file path oid
    // p_sb - pointer to superblock
    int findIndexItem(long path_oid, dsk_superblock_index_t** p_sb);

    // findItem(): find item in superblock table
    // oid - block oid
    // resval - result data
    int findItem(long oid, dsk_superblock_t** resval);

    // findItem(): find item in superblock table
    // key - block key
    // resval - result data
    int findItem(char* key, dsk_superblock_t** resval);

    // findFirstFreeSuperBlock(): find first free item in block table
    // disk_group - disk device group
    // disk_dev - disk device oid
    // path_oid - file path oid
    // block_num - number of blocks
    // block_sector - block sector at disk device
    // uid - user id
    // resval - result data
    // block_oid - return block oid
    int findFirstFreeSuperBlock(
        long disk_group, 
        long disk_dev, 
        long path_oid, 
        long block_num,
        long block_sector,
        long uid, 
        dsk_superblock_t** resval, 
        long* superblock_oid);

    // findAll(): find all blocks
    // arr - result data (array of blocks)
    // arrsz - return the number of rows in the array
    int findAll(dsk_superblock_t** arr, long* arrsz);

    // findAllByPathOid(): find all blocks
    // path_oid - file path oid
    // arr - result data (array of blocks)
    // arrsz - return the number of rows in the array
    int findAllByPathOid(long path_oid, dsk_superblock_t** arr, long* arrsz);

    // findAllByPathOid(): find all blocks
    // path_oid - file path oid
    // disk_dev - disk device oid
    // arr - result data (array of blocks)
    // arrsz - return the number of rows in the array
    int findAllByPathOidAndDiskDev(long path_oid, long disk_dev, dsk_superblock_t** arr, long* arrsz);

    // countItemsByPathOid(): count all blocks with path oid
    // path_oid - file path oid
    // num_items - return the number of items
    int countItemsByPathOid(long path_oid, long* num_items);

    // countItemsByPathOid(): count all blocks with path oid
    // path_oid - file path oid
    // disk_dev - disk device oid
    // num_items - return the number of items
    int countItemsByPathOidAndDiskDev(long path_oid, long disk_dev, long* num_items);

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
    dsk_superblock_t* newItemData(dsk_superblock_t** data);

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
    dsk_superblock_t* setItemData(
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
        char* key);

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
    dsk_superblock_t* setItemData_NotThreadSafe(
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
    void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_superblock_t* p);

    /* Getters/Setters */

    CDskSuperBlockIdx* getSuperBlockIndex();

    char* getSuperBlockTableFile();

    int getMaxNumDskSuperBlock();

    int getCurrNumDskSuperBlock();

};

/* NEW_TYPE: CDskSuperBlockMan Pointer */

typedef CDskSuperBlockMan* CDskSuperBlockManPtr_t;

#endif
