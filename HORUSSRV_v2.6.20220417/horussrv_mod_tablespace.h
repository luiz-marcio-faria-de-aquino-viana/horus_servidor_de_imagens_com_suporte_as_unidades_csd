/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_tablespace.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_TABLESPACE_H
#define __HORUSSRV_MOD_TABLESPACE_H      "__HORUSSRV_MOD_TABLESPACE_H"

class CTableSpace
{
private:
    tablespace_t* m_arrTableSpace;
    int m_maxNumEntries; 
    int m_currNumEntries; 

public:
    CTableSpace(int maxNumEntries);
    ~CTableSpace();

    // loadFile(): load table of tablespace from file
    // fileName - tablespace's table file name
    int loadFile(char* fileName);

    // saveFile(): save table of tablespace to file
    // fileName - tablespace's table file name
    int saveFile(char* fileName);

    // addItem(): add item to tablespace
    // key - tablespace key
    // name - tablespace name
    // path - tablespace path
    int addItem(char* key, char* name, char* path, long uid);

    // addItem(): add item to tablespace
    // oid - tablespace oid
    // key - tablespace key
    // name - tablespace name
    // path - tablespace path
    int addItemEx(long oid, char* key, char* name, char* path, long uid);

    // findItem(): find item in tablespace
    // oid - tablespace oid
    // resval - result data
    int findItem(long oid, tablespace_t** resval);

    // findItem(): find item in tablespace
    // key - tablespace key
    // resval - result data
    int findItem(char* key, tablespace_t** resval);

    // findAll(): find all tablespace
    // arr - result data (array of tables)
    // arrsz - return the number of rows in the array
    int findAll(tablespace_t** arr, long* arrsz);

    // deleteItem(): mark item as deleted in tablespace
    // oid - tablespace oid
    // uid - user id
    int deleteItem(long oid, long uid);

    // deleteItem(): mark item as deleted in tablespace
    // key - tablespace key
    // uid - user id
    int deleteItem(char* key, long uid);

    // newItemData(): mark item as deleted in tablespace
    // data - data reference
    tablespace_t* newItemData(tablespace_t** data);

    // setItemData(): mark item as deleted in tablespace
    // data - data reference
    // oid - object id
    // key_hash - record key hash
    // create_uid - create user id
    // delete_uid - delete user id
    // create_date - create timestamp
    // delete_date - delete timestamp
    // is_deleted - record is deleted
    // tablespace_name = tablespace name
    // tablespace_path = tablespace path
    // key - record key
    tablespace_t* setItemData(
        tablespace_t** data, 
        long oid,
        long key_hash,
        long create_uid,
        long delete_uid,
        long create_date,
        long delete_date,
        long is_deleted,
        char* tablespace_name,
        char* tablespace_path,
        char* key);

    // debug(): list all tables in tablespace (=DEBUGLEVEL)
    // debugLevel - debug level
    // className - caller class name
    // methodName - caller method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debug(): list table data (=DEBUGLEVEL)
    // debugLevel - debug level
    // className - caller class name
    // methodName - caller method name
    // p - pointer to a tablespace entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, tablespace_t* p);

    // showAll(): show list of all tables in tablespace
    void showAll();

    // showEntry(): show tablespace data
    // p - pointer to a tablespace entry
    void showEntry(tablespace_t* p);

    // toXml(): return XML data
    // p - pointer to a tablespace entry
    // returnXml - XML return data
    char* toXml(tablespace_t* p, char* returnXml);

    // parserXml(): xml data entry parser
    // data - data reference
    // xmlData - xml data
    int parserXml(tablespace_t* p, char* xmlData);

};

/* NEW_TYPE: CTableSpace Pointer */

typedef CTableSpace* CTableSpacePtr_t;

#endif
