/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_tablespace.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CTableSpace::CTableSpace(int maxNumEntries)
{
    m_maxNumEntries = maxNumEntries; 
    m_currNumEntries = 0; 

    m_arrTableSpace = (tablespace_t*)allocDataArray(sizeof(tablespace_t), m_maxNumEntries);
}

CTableSpace::~CTableSpace()
{
    freeDataArray(m_arrTableSpace);
}

// saveFile(): save table of table metadata to file
// fileName - table metadata file name
int CTableSpace::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(tablespace_t);
        for(int i = 0; i < m_currNumEntries; i++)
        {
            tablespace_t* p = &m_arrTableSpace[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_03, __HORUSSRV_MOD_TABLESPACE_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// loadFile(): load table of table metadata from file
// fileName - table metadata table file name
int CTableSpace::loadFile(char* fileName)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(tablespace_t);

        m_currNumEntries = 0;
        while(m_currNumEntries < m_maxNumEntries)
        {
            if(fread(&m_arrTableSpace[m_currNumEntries], 1, size, f) == 0) break;
            m_currNumEntries += 1;
        }
        fclose(f);
    }
    return rscode;
}

// addItem(): create new tablespace
// key - tablespace key
// name - tablespace name
// path - tablespace path
// uid - create tablespace user id
int CTableSpace::addItem(char* key, char* name, char* path, long uid)
{
    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    tablespace_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(key, &data) != RSOK)
    {
        data = &(m_arrTableSpace[m_currNumEntries]);

        long oid = seq->nextVal((char*)SEQ_TABLESPACE);

        /* Add new item
         */
        setItemData(
            &data, 
            oid,
            keyHash,
            uid,
            DBNULL_LONG,
            currTimestamp,
            DBNULL_LONG,
            DBFALSE,
            name,
            path,
            key);
            
        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        data->key_hash = keyHash;
        strNCpyUtil(data->tablespace_name, name, STRSZ);
        strNCpyUtil(data->tablespace_path, path, STRSZ);
        strNCpyUtil(data->key            , key , STRSZ);
    }

    return(RSOK);
}

// addItem(): create new tablespace
// oid - tablespace id
// key - tablespace key
// name - tablespace name
// path - tablespace path
// uid - create tablespace user id
int CTableSpace::addItemEx(long oid, char* key, char* name, char* path, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    tablespace_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(key, &data) != RSOK)
    {
        data = &(m_arrTableSpace[m_currNumEntries]);

        /* Add new item
         */
        setItemData(
            &data, 
            oid,
            keyHash,
            uid,
            DBNULL_LONG,
            currTimestamp,
            DBNULL_LONG,
            DBFALSE,
            name,
            path,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        data->key_hash = keyHash;
        strNCpyUtil(data->tablespace_name, name, STRSZ);
        strNCpyUtil(data->tablespace_path, path, STRSZ);
        strNCpyUtil(data->key            , key , STRSZ);
    }

    return(RSOK);
}

// findItem(): find item in tablespace
// oid - tablespace oid
// resval - result data
int CTableSpace::findItem(long oid, tablespace_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        tablespace_t* p = &m_arrTableSpace[i];    
        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in tablespace
// key - tablespace key
// resval - result data
int CTableSpace::findItem(char* key, tablespace_t** resval)
{
    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumEntries; i++)
    {
        tablespace_t* p = &m_arrTableSpace[i];    
        if(p->key_hash == keyHash)
        {
            if(strNCmpUtil(p->key, key, STRSZ) == 0)
            {
                (*resval) = p;
                return(RSOK);
            }
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findAll(): find all tablespace
// arr - result data (array of tables)
// arrsz - return the number of rows in the array
int CTableSpace::findAll(tablespace_t** arr, long* arrsz)
{
    (*arrsz) = m_currNumEntries;
    (*arr) = (tablespace_t*)allocDataArray(sizeof(tablespace_t), (*arrsz));
    if((*arr) == NULL) return RSERR;

    tablespace_t* p = (*arr);
    for(int i = 0; i < m_currNumEntries; i++) {
        memNCpyUtil((byte*)p, (byte*)&m_arrTableSpace[i], sizeof(tablespace_t));
        debugEntry(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLESPACE_H, "findAll()", p);
        p++;
    }  
    return RSOK;
}

// deleteItem(): mark item as deleted in tablespace
// oid - tablespace oid
// uid - user id
int CTableSpace::deleteItem(long oid, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    tablespace_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLESPACE_H, "deleteItem()", ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in tablespace
// key - tablespace key
// uid - user id
int CTableSpace::deleteItem(char* key, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    tablespace_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLESPACE_H, "deleteItem()", ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): new item data
// data - tablespace reference
tablespace_t* CTableSpace::newItemData(tablespace_t** data)
{
    if((*data) == NULL)
        (*data) = (tablespace_t*)allocData(sizeof(tablespace_t));

    (*data)->oid         = DBNULL_LONG;
    (*data)->key_hash    = DBNULL_LONG;
    (*data)->create_uid  = DBNULL_LONG;
    (*data)->delete_uid  = DBNULL_LONG;
    (*data)->create_date = DBNULL_LONG;
    (*data)->delete_date = DBNULL_LONG;
    (*data)->is_deleted  = DBNULL_LONG;
    strNCpyUtil((*data)->tablespace_name, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->tablespace_path, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->key            , (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): set item data
// data - tablespace reference
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
tablespace_t* CTableSpace::setItemData(
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
    char* key)
{
    if((*data) == NULL)
        (*data) = (tablespace_t*)allocData(sizeof(tablespace_t));
        
    (*data)->oid         = oid;
    (*data)->key_hash    = key_hash;
    (*data)->create_uid  = create_uid;
    (*data)->delete_uid  = delete_uid;
    (*data)->create_date = create_date;
    (*data)->delete_date = delete_date;
    (*data)->is_deleted  = is_deleted;
    strNCpyUtil((*data)->tablespace_name, tablespace_name, STRSZ);
    strNCpyUtil((*data)->tablespace_path, tablespace_path, STRSZ);
    strNCpyUtil((*data)->key            , key            , STRSZ);

    return (*data);
}

// debug(): list all tables in tablespace (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
void CTableSpace::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    tablespace_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrTableSpace[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): list table data (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
// p - pointer to a tablespace entry
void CTableSpace::debugEntry(int debugLevel, const char* className, const char* methodName, tablespace_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "TableSpace: Oid=%ld,KeyHash=%ld,CreateUid=%ld,DeleteUid=%ld,CreateDate=%ld,DeleteDate=%ld,IsDeleted=%ld,TableSpaceName=%s,TableSpacePath=%s,Key=%s\n",
        p->oid,
        p->key_hash,
        p->create_uid,
        p->delete_uid,
        p->create_date,
        p->delete_date,
        p->is_deleted,
        p->tablespace_name,
        p->tablespace_path,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

// showAll(): show list of all tables in tablespace
void CTableSpace::showAll()
{
    tablespace_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrTableSpace[i];
        showEntry(p);
    }  
}

// showEntry(): show tablespace data
// p - pointer to a tablespace entry
void CTableSpace::showEntry(tablespace_t* p)
{
    bigstr_t tableSpaceXml;
    strSetEmptyUtil(tableSpaceXml);

    toXml(p, tableSpaceXml);

    printf(
        "TableSpace: Oid=%ld,KeyHash=%ld,CreateUid=%ld,DeleteUid=%ld,CreateDate=%ld,DeleteDate=%ld,IsDeleted=%ld,TableSpaceName=%s,TableSpacePath=%s,Key=%s,Data=%s\n",
        p->oid,
        p->key_hash,
        p->create_uid,
        p->delete_uid,
        p->create_date,
        p->delete_date,
        p->is_deleted,
        p->tablespace_name,
        p->tablespace_path,
        p->key,
        tableSpaceXml);
}

// toXml(): show tablespace data
// p - pointer to a tablespace entry
// returnXml - XML return data
char* CTableSpace::toXml(tablespace_t* p, char* returnXml)
{
    sprintf(returnXml,
        DEF_XML_RESPONSE_TABLESPACE,
        p->oid,
        p->key_hash,
        p->create_uid,
        p->delete_uid,
        p->create_date,
        p->delete_date,
        p->is_deleted,
        p->tablespace_name,
        p->tablespace_path,
        p->key);
    return returnXml;
}

// parserXml(): xml data entry parser
// data - data reference
// xmlData - xml data
int CTableSpace::parserXml(tablespace_t* p, char* xmlData)
{
    str_t str_oid;
    xmlNodeUtil(str_oid, xmlData, (char*)"Oid", 1);
    p->oid = atol(str_oid);       

    str_t str_key_hash;
    xmlNodeUtil(str_key_hash, xmlData, (char*)"KeyHash", 1);
    p->key_hash = atol(str_key_hash);       

    str_t str_create_uid;
    xmlNodeUtil(str_create_uid, xmlData, (char*)"CreateUid", 1);
    p->create_uid = atol(str_create_uid);       

    str_t str_delete_uid;
    xmlNodeUtil(str_delete_uid, xmlData, (char*)"DeleteUid", 1);
    p->delete_uid = atol(str_delete_uid);       

    str_t str_create_date;
    xmlNodeUtil(str_create_date, xmlData, (char*)"CreateDate", 1);
    p->create_date = atol(str_create_date);       

    str_t str_delete_date;
    xmlNodeUtil(str_delete_date, xmlData, (char*)"DeleteDate", 1);
    p->delete_date = atol(str_delete_date);       

    str_t str_is_deleted;
    xmlNodeUtil(str_is_deleted, xmlData, (char*)"IsDeleted", 1);
    p->is_deleted = atol(str_is_deleted);       

    str_t str_tablespace_name;
    xmlNodeUtil(str_tablespace_name, xmlData, (char*)"TableSpaceName", 1);
    strNCpyUtil(p->tablespace_name, str_tablespace_name, STRSZ);       

    str_t str_tablespace_path;
    xmlNodeUtil(str_tablespace_path, xmlData, (char*)"TableSpacePath", 1);
    strNCpyUtil(p->tablespace_path, str_tablespace_path, STRSZ);       

    str_t str_key;
    xmlNodeUtil(str_key, xmlData, (char*)"Key", 1);
    strNCpyUtil(p->key, str_key, STRSZ);       

    return RSOK;
}
