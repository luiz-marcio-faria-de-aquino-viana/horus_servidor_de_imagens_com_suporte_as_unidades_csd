/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_users.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 19/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_USERS_H
#define __HORUSSRV_MOD_USERS_H      "__HORUSSRV_MOD_USERS_H"

class CUsers
{
private:
    users_t* m_arrUsers;
    int m_maxNumEntries; 
    int m_currNumEntries; 

public:
    CUsers(int maxNumEntries);
    ~CUsers();

    // loadFile(): load table of users from file
    // fileName - users' table file name
    int loadFile(char* fileName);

    // saveFile(): save table of users to file
    // fileName - users' table file name
    int saveFile(char* fileName);

    // addItem(): add item to users' table
    // key - user's key
    // username - user's name
    // passwd - user's password
    // userType - user's type (0=SYSTEM, 1=ADMIN, 99=USER)
    int addItem(char* key, char* username, char* passwd, long user_type);

    // addItem(): add item to users' table
    // oid - user id
    // key - user's key
    // username - user's name
    // passwd - user's password
    // userType - user's type (0=SYSTEM, 1=ADMIN, 99=USER)
    int addItem(long oid, char* key, char* username, char* passwd, long user_type);

    // findItem(): find user in users' table
    // oid - user oid
    // resval - result data
    int findItem(long oid, users_t** resval);

    // findItem(): find item in users' table
    // key - user key
    // resval - result data
    int findItem(char* key, users_t** resval);

    // findAll(): find all users
    // arr - result data (array of users)
    // arrsz - return the number of rows in the array
    int findAll(users_t** arr, long* arrsz);

    // deleteItem(): mark item as deleted in users' table
    // oid - user oid
    int deleteItem(long oid);

    // deleteItem(): mark item as deleted in users' table
    // key - user key
    int deleteItem(char* key);

    // newItemData(): mark item as deleted in users' table
    // data - data reference
    users_t* newItemData(users_t** data);

    // newItemData(): mark item as deleted in tablespace
    // data - data reference
    // oid - user id
    // key_hash - hash key value
    // create_date - create date
    // modify_date - modify date
    // delete_date - deleted date
    // is_deleted - mark deleted entry
    // user_type - user's type (0=SYSTEM, 1=ADMIN, 99=USER)
    // username - user's name
    // passwd - user's password
    // key - user's key
    users_t* setItemData(
        users_t** data,
        long oid,
        long key_hash,
        long create_date,
        long modify_date,
        long delete_date,
        long is_deleted,
        long user_type,
        char* username,
        char* passwd,
        char* key);

    // debug(): list all tables in tablespace (=DEBUGLEVEL)
    // debugLevel - debug level
    // className - caller class name
    // methodName - caller method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debugEntry(): list table data (=DEBUGLEVEL)
    // debugLevel - debug level
    // className - caller class name
    // methodName - caller method name
    // p - pointer to a users entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, users_t* p);

    // showAll(): show list of all users
    void showAll();

    // showEntry(): show users data
    // p - pointer to a users entry
    void showEntry(users_t* p);

    // toXml(): return XML data
    // p - pointer to a users entry
    // returnXml - XML return data
    char* toXml(users_t* p, char* returnXml);
    
    // parserXml(): xml data entry parser
    // data - data reference
    // xmlData - xml data
    int parserXml(users_t* p, char* xmlData);

};

/* NEW_TYPE: CUsers Pointer */

typedef CUsers* CUsersPtr_t;

#endif
