/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_pathman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_PATHMAN_H
#define __HORUSWRK_DSK_PATHMAN_H                      "__HORUSWRK_DSK_PATHMAN_H"

class CDskPathMan
{
private:
    bigstr_t m_dirTableFile;
    pathname_t m_dirTableFilePath;

    dsk_path_t* m_arrDskPath;
    int m_maxNumDskPath;
    int m_currNumDskPath;

public:
    CDskPathMan(int maxNumDskPath, char* dirTableFile, char* dirTableFilePath);
    ~CDskPathMan();

    // init(): initiate disk group
    void init(int maxNumDskPath, char* dirTableFile, char* dirTableFilePath);

    // term(): terminate disk group
    void terminate();

    /* Methodes */

    // loadFile(): load table of paths from file
    // fileName - path's table file name
    int loadFile(char* fileName);

    // saveFile(): save table of paths to file
    // fileName - path's table file name
    int saveFile(char* fileName);

    // addItem(): add item to tablespace
    // path_name - path name
    // path_ext - path extension
    // path_type - path type (-1=EMPTY / 1=DIR / 2=FILE)
    // path_parent - parent path identity
    // block_start - start block
    // block_qty - block quantity
    // data_size - data size
    // uid - user identifier
    int addItem(
        char* path_name,
        char* path_ext,
        long path_type,
        long disk_group,
        long path_parent,
        long block_start,
        long block_qty,
        long data_size,
        long uid,
        long* oid);

    // findItem(): find item in path
    // oid - path oid
    // resval - result data
    int findItem(long oid, dsk_path_t** resval);

    // findItem(): find item in path
    // key - path key
    // resval - result data
    int findItem(char* key, dsk_path_t** resval);

    // findItem(): find item in path
    // path_parent - path parent oid
    // path_name - path name
    // resval - result data
    int findItem(long path_parent, char* path_name, dsk_path_t** resval);

    // findAll(): find all paths
    // arr - result data (array of paths)
    // arrsz - return the number of rows in the array
    int findAll(dsk_path_t** arr, long* arrsz);

    // findAllChildByPathParent(): find all paths at path parent
    // arr - result data (array of paths)
    // arrsz - return the number of rows in the array
    // path_parent - path parent to be searched
    // bDeleted - retrieve deleted items
    int findAllChildByPathParent(dsk_path_t** arr, long* arrsz, long path_parent, long bDeleted);

    // getNumEntriesByPathParent(): return number of entries at path parent
    // num_entries - result number of entries
    // path_parent - path parent to be searched
    // bDeleted - count deleted items
    int getNumEntriesByPathParent(long* num_entries, long path_parent, long bDeleted);

    // deleteItem(): mark item as deleted in path
    // oid - path oid
    // uid - user id
    int deleteItem(long oid, long uid);

    // deleteItem(): mark item as deleted in path
    // key - path key
    // uid - user id
    int deleteItem(char* key, long uid);

    // newItemData(): mark item as deleted in path
    // data - data reference
    dsk_path_t* newItemData(dsk_path_t** data);

    // setItemData(): mark item as deleted in path
    // data - return data
    // oid - path oid
    // key_hash - path name hash value
    // disk_group - disk group oid
    // path_parent - parent path identity
    // path_type - path type (-1=EMPTY / 1=DIR / 2=FILE)
    // create_date - create date
    // create_uid - user creator uid
    // modify_date - modify date
    // modify_uid - user modifier uid
    // is_modified - file was modified
    // delete_date - delete data
    // delete_uid - user delete uid
    // is_deleted - file was deleted
    // block_start - start block
    // block_qty - block quantity
    // data_size - data size
    // path_name - path name
    // path_ext - path extension
    // key - path key
    dsk_path_t* setItemData(
        dsk_path_t** data, 
        long oid,
        long key_hash,
        long path_type,
        long disk_group,
        long path_parent,
        long create_date,
        long create_uid,
        long modify_date,
        long modify_uid,
        long is_modified,
        long delete_date,
        long delete_uid,
        long is_deleted,
        long block_start,
        long block_qty,
        long data_size,
        char* path_name,
        char* path_ext,
        char* key);

    /* Debug */

    // debug(): show all disk groups
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debugEntry(): show disk group
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    // p - pointer to a disk path entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_path_t* p);

    /* Getters/Setters */

    char* getDirTableFile();

    char* getDirTableFilePath();

    int getMaxNumDskPath();

    int getCurrNumDskPath();

};

/* NEW_TYPE: CDskPathMan Pointer */

typedef CDskPathMan* CDskPathManPtr_t;

#endif
