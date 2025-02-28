/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_users.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 19/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CUsers::CUsers(int maxNumEntries)
{
    m_maxNumEntries = maxNumEntries; 
    m_currNumEntries = 0; 

    m_arrUsers = (users_t*)allocDataArray(sizeof(users_t), m_maxNumEntries);
}

CUsers::~CUsers()
{
    freeDataArray(m_arrUsers);
}

// saveFile(): save table of table metadata to file
// fileName - table metadata file name
int CUsers::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(users_t);
        for(int i = 0; i < m_currNumEntries; i++)
        {
            users_t* p = &m_arrUsers[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_03, __HORUSSRV_MOD_USERS_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// loadFile(): load table of table metadata from file
// fileName - table metadata table file name
int CUsers::loadFile(char* fileName)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(users_t);

        m_currNumEntries = 0;
        while(m_currNumEntries < m_maxNumEntries)
        {
            if(fread(&m_arrUsers[m_currNumEntries], 1, size, f) == 0) break;
            m_currNumEntries += 1;
        }
        fclose(f);
    }
    return rscode;
}

// addItem(): add item to users' table
// oid - user id
// key - user's key
// username - user's name
// passwd - user's password
// user_type - user's type (0=SYSTEM, 1=ADMIN, 99=USER)
int CUsers::addItem(long oid, char* key, char* username, char* passwd, long user_type)
{
    long currTimestamp = getCurrentTimestamp();

    users_t* data = NULL;
    
    long keyHash = getHash(key);

    if(findItem(oid, &data) != RSOK)
    {
        data = &(m_arrUsers[m_currNumEntries]);

        /* Add new item
         */
        setItemData(
            &data, 
            oid,
            keyHash,
            currTimestamp,
            currTimestamp,
            DBNULL_LONG,
            DBFALSE,
            user_type,
            username,
            passwd,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        data->modify_date  = currTimestamp;
        data->user_type = user_type;
        strNCpyUtil(data->username, username, STRSZ);
        strNCpyUtil(data->passwd  , passwd  , STRSZ);
    }

    return(RSOK);
}

// findItem(): find item in users
// oid - users oid
// resval - result data
int CUsers::findItem(long oid, users_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        users_t* p = &m_arrUsers[i];    
        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in users
// key - users key
// resval - result data
int CUsers::findItem(char* key, users_t** resval)
{
    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumEntries; i++)
    {
        users_t* p = &m_arrUsers[i];    
        if(p->key_hash == keyHash)
        {
            if(strncmp(p->key, key, STRSZ) == 0)
            {
                (*resval) = p;
                return(RSOK);
            }
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findAll(): find all users
// arr - result data (array of users)
// arrsz - return the number of rows in the array
int CUsers::findAll(users_t** arr, long* arrsz)
{
    (*arrsz) = m_currNumEntries;
    (*arr) = (users_t*)allocDataArray(sizeof(users_t), (*arrsz));
    if((*arr) == NULL) return RSERR;

    users_t* p = (*arr);
    for(int i = 0; i < m_currNumEntries; i++) {
        memNCpyUtil((byte*)p, (byte*)&m_arrUsers[i], sizeof(users_t));
        debugEntry(DEBUG_LEVEL_01, __HORUSSRV_MOD_USERS_H, "findAll()", p);
        p++;
    }  
    return RSOK;
}

// deleteItem(): mark item as deleted in users
// oid - users oid
// uid - user id
int CUsers::deleteItem(long oid)
{
    long currTimestamp = getCurrentTimestamp();

    users_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_USERS_H, "deleteItem()", (char*)ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in tablespace
// key - users key
// uid - user id
int CUsers::deleteItem(char* key)
{
    long currTimestamp = getCurrentTimestamp();

    users_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_USERS_H, "deleteItem()", (char*)ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): new item data
// data - data reference
users_t* CUsers::newItemData(users_t** data)
{
    if((*data) == NULL)
        (*data) = (users_t*)allocData(sizeof(users_t));

    (*data)->oid         = DBNULL_LONG;
    (*data)->key_hash    = DBNULL_LONG;
    (*data)->create_date = DBNULL_LONG;
    (*data)->modify_date = DBNULL_LONG;
    (*data)->delete_date = DBNULL_LONG;
    (*data)->is_deleted  = DBNULL_LONG;
    (*data)->user_type   = DBNULL_LONG;
    strNCpyUtil((*data)->username, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->passwd  , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->key     , (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): set item data
// data - data reference
// oid - object id
// key_hash - record key hash
// create_date - create timestamp
// modify_date - modify timestamp
// delete_date - delete timestamp
// is_deleted - record is deleted
// user_type - user's type (0=SYSTEM, 1=ADMIN, 99=USER)
// username = users' name
// passwd = users' passwd
// key - record key
users_t* CUsers::setItemData(
    users_t** data,
    long oid,
    long key_hash,
    long create_date,
    long modify_date,
    long delete_date,
    long is_deleted,
    long user_type,
    str_t username,
    str_t passwd,
    str_t key)
{
    if((*data) == NULL)
        (*data) = (users_t*)allocData(sizeof(users_t));
        
    (*data)->oid         = oid;
    (*data)->key_hash    = key_hash;
    (*data)->create_date = create_date;
    (*data)->modify_date = modify_date;
    (*data)->delete_date = delete_date;
    (*data)->is_deleted  = is_deleted;
    (*data)->user_type   = user_type;
    strNCpyUtil((*data)->username, username, STRSZ);
    strNCpyUtil((*data)->passwd  , passwd  , STRSZ);
    strNCpyUtil((*data)->key     , key     , STRSZ);

    return (*data);
}

// debug(): list all tables in tablespace (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
void CUsers::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    users_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrUsers[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): list table data (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
// p - pointer to a users entry
void CUsers::debugEntry(int debugLevel, const char* className, const char* methodName, users_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;

    bigstr_t usersXml;
    strSetEmptyUtil(usersXml);

    toXml(p, usersXml);

    sprintf(
        errmsg, 
        "Users: Oid=%ld,KeyHash=%ld,CreateDate=%ld,ModifyDate=%ld,DeleteDate=%ld,IsDeleted=%ld,UserType=%ld,Username=%s,Passwd=%s,Key=%s,Xml=%s\n",
        p->oid,
        p->key_hash,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_deleted,
        p->user_type,
        p->username,
        p->passwd,
        p->key,
        usersXml);
    warnMsg(debugLevel, className, methodName, errmsg);
}

// showAll(): show list of all users
void CUsers::showAll()
{
    users_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrUsers[i];
        showEntry(p);
    }  
}

// showEntry(): show users data
// p - pointer to a users entry
void CUsers::showEntry(users_t* p)
{
    bigstr_t usersXml;
    strSetEmptyUtil(usersXml);

    toXml(p, usersXml);

    printf(
        "Users: Oid=%ld,KeyHash=%ld,CreateDate=%ld,ModifyDate=%ld,DeleteDate=%ld,IsDeleted=%ld,UserType=%ld,Username=%s,Passwd=%s,Key=%s,Xml=%s\n",
        p->oid,
        p->key_hash,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_deleted,
        p->user_type,
        p->username,
        p->passwd,
        p->key,
        usersXml);
}

// toXml(): return XML data
// p - pointer to a users entry
// returnXml - XML return data
char* CUsers::toXml(users_t* p, char* returnXml)
{
    sprintf(returnXml,
        DEF_XML_RESPONSE_USER,
        p->oid,
        p->key_hash,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_deleted,
        p->user_type,
        p->username,
        p->passwd,
        p->key);
    return returnXml;
}

// parserXml(): xml data entry parser
// data - data reference
// xmlData - xml data
int CUsers::parserXml(users_t* p, char* xmlData)
{
    str_t str_oid;
    xmlNodeUtil(str_oid, xmlData, (char*)"Oid", 1);
    p->oid = atol(str_oid);       

    str_t str_key_hash;
    xmlNodeUtil(str_key_hash, xmlData, (char*)"KeyHash", 1);
    p->key_hash = atol(str_key_hash);       

    str_t str_create_date;
    xmlNodeUtil(str_create_date, xmlData, (char*)"CreateDate", 1);
    p->create_date = atol(str_create_date);       

    str_t str_modify_date;
    xmlNodeUtil(str_modify_date, xmlData, (char*)"ModifyDate", 1);
    p->modify_date = atol(str_modify_date);       

    str_t str_delete_date;
    xmlNodeUtil(str_delete_date, xmlData, (char*)"DeleteDate", 1);
    p->delete_date = atol(str_delete_date);       

    str_t str_is_deleted;
    xmlNodeUtil(str_is_deleted, xmlData, (char*)"IsDeleted", 1);
    p->is_deleted = atol(str_is_deleted);       

    str_t str_user_type;
    xmlNodeUtil(str_user_type, xmlData, (char*)"UserType", 1);
    p->user_type = atol(str_user_type);       

    str_t str_username;
    xmlNodeUtil(str_username, xmlData, (char*)"UserName", 1);
    strNCpyUtil(p->username, str_username, STRSZ);       

    str_t str_passwd;
    xmlNodeUtil(str_passwd, xmlData, (char*)"Passwd", 1);
    strNCpyUtil(p->passwd, str_passwd, STRSZ);       

    str_t str_key;
    xmlNodeUtil(str_key, xmlData, (char*)"Key", 1);
    strNCpyUtil(p->key, str_key, STRSZ);       

    return RSOK;
}
