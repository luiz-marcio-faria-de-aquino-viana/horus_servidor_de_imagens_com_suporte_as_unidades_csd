/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_tablemetadata.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CTableMetadata::CTableMetadata(int maxNumEntries)
{
    m_maxNumEntries = maxNumEntries; 
    m_currNumEntries = 0; 

    m_arrTableMetadata = (table_metadata_t*)allocDataArray(sizeof(table_metadata_t), m_maxNumEntries);
}

CTableMetadata::~CTableMetadata()
{
    freeDataArray(m_arrTableMetadata);
}

// saveFile(): save table of table metadata to file
// fileName - table metadata file name
int CTableMetadata::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(table_metadata_t);
        for(int i = 0; i < m_currNumEntries; i++)
        {
            table_metadata_t* p = &m_arrTableMetadata[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_03, __HORUSSRV_MOD_TABLEMETADATA_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// loadFile(): load table of table metadata from file
// fileName - table metadata table file name
int CTableMetadata::loadFile(char* fileName)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(table_metadata_t);

        m_currNumEntries = 0;
        while(m_currNumEntries < m_maxNumEntries)
        {
            if(fread(&m_arrTableMetadata[m_currNumEntries], 1, size, f) == 0) break;
            m_currNumEntries += 1;
        }
        fclose(f);
    }
    return rscode;
}

// addItem(): add item to table metadata
// key - table metadata key
// tablespace_oid - pointer tablespace identifier array
// num_tablespaces - number of tablespaces in array
// num_entries - number of entries
// table_type - table type (1=TBTYPE_DATATABLE/2=TBTYPE_IMAGETABLE)
// reference_table_oid - referencied table oid
// module_name - module name for data classification
// table_name - table name
// table_filename - table filename
// idx1_name - index IDX1 name
// idx1_filename - index IDX1 filename
// idx1_name - index IDX2 name
// idx1_filename - index IDX2 filename
// seq_name - sequence name
// uid - user identifier
int CTableMetadata::addItem(
    char* key, 
    long* tablespace_oid,
    long num_tablespaces,
    long num_entries,
    long table_type,
    long reference_table_oid,
    char* module_name,
    char* table_name,
    char* table_filename,
    char* idx1_name,
    char* idx1_filename,
    char* idx2_name,
    char* idx2_filename,
    char* seq_name,
    long uid)
{
    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    table_metadata_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(key, &data) != RSOK)
    {
        data = &(m_arrTableMetadata[m_currNumEntries]);

        long oid = seq->nextVal((char*)SEQ_TABLE_METADATA);

        /* Add new item
         */
        setItemData(
            &data, 
            oid,
            keyHash,
            tablespace_oid,
            num_tablespaces,
            num_entries,
            uid,
            uid,
            DBNULL_LONG,
            currTimestamp,
            currTimestamp,
            DBNULL_LONG,
            DBTRUE,
            DBFALSE,
            table_type,
            reference_table_oid,
            module_name,
            table_name,
            table_filename,
            idx1_name,
            idx1_filename,
            idx2_name,
            idx2_filename,
            seq_name,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        for(int i = 0; i < num_tablespaces; i++)
            data->tablespace_oid[i] = tablespace_oid[i];
        data->num_tablespaces = num_tablespaces;
        data->num_entries = num_entries;
        data->modify_uid = uid;
        data->modify_date = currTimestamp;
        data->is_modified = DBTRUE;
        data->table_type = table_type;
        data->reference_table_oid = reference_table_oid;
        strNCpyUtil(data->module_name         , module_name         , STRSZ);
        strNCpyUtil(data->table_name          , table_name          , STRSZ);
        strNCpyUtil(data->table_filename      , table_filename      , STRSZ);
        strNCpyUtil(data->idx1_name           , idx1_name           , STRSZ);
        strNCpyUtil(data->idx1_filename       , idx1_filename       , STRSZ);
        strNCpyUtil(data->idx2_name           , idx2_name           , STRSZ);
        strNCpyUtil(data->idx2_filename       , idx2_filename       , STRSZ);
        strNCpyUtil(data->seq_name            , seq_name            , STRSZ);
    }

    return(RSOK);
}

// addItem(): add item to table metadata
// oid - table metadata oid
// key - table metadata key
// tablespace_oid - pointer tablespace identifier array
// num_tablespaces - number of tablespaces in array
// num_entries - number of entries
// table_type - table type (1=TBTYPE_DATATABLE/2=TBTYPE_IMAGETABLE)
// reference_table_oid - referencied table oid
// module_name - module name for data classification
// table_name - table name
// table_filename - table filename
// idx1_name - index IDX1 name
// idx1_filename - index IDX1 filename
// idx2_name - index IDX2 name
// idx2_filename - index IDX2 filename
// seq_name - sequence name
// uid - user identifier
int CTableMetadata::addItem(
    long oid,
    char* key, 
    long* tablespace_oid,
    long num_tablespaces,
    long num_entries,
    long table_type,
    long reference_table_oid,
    char* module_name,
    char* table_name,
    char* table_filename,
    char* idx1_name,
    char* idx1_filename,
    char* idx2_name,
    char* idx2_filename,
    char* seq_name,
    long uid)
{
    long currTimestamp = getCurrentTimestamp();

    table_metadata_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(oid, &data) != RSOK)
    {
        data = &(m_arrTableMetadata[m_currNumEntries]);

        /* Add new item
         */
        setItemData(
            &data, 
            oid,
            keyHash,
            tablespace_oid,
            num_tablespaces,
            num_entries,
            uid,
            uid,
            DBNULL_LONG,
            currTimestamp,
            currTimestamp,
            DBNULL_LONG,
            DBTRUE,
            DBFALSE,
            table_type,
            reference_table_oid,
            module_name,
            table_name,
            table_filename,
            idx1_name,
            idx1_filename,
            idx2_name,
            idx2_filename,
            seq_name,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        for(int i = 0; i < num_tablespaces; i++)
            data->tablespace_oid[i] = tablespace_oid[i];
        data->num_tablespaces = num_tablespaces;
        data->num_entries = num_entries;
        data->modify_uid = uid;
        data->is_modified = DBTRUE;
        data->table_type = table_type;
        data->reference_table_oid = reference_table_oid;
        strNCpyUtil(data->module_name         , module_name         , STRSZ);
        strNCpyUtil(data->table_name          , table_name          , STRSZ);
        strNCpyUtil(data->table_filename      , table_filename      , STRSZ);
        strNCpyUtil(data->idx1_name           , idx1_name           , STRSZ);
        strNCpyUtil(data->idx1_filename       , idx1_filename       , STRSZ);
        strNCpyUtil(data->idx2_name           , idx2_name           , STRSZ);
        strNCpyUtil(data->idx2_filename       , idx2_filename       , STRSZ);
        strNCpyUtil(data->seq_name            , seq_name            , STRSZ);
        strNCpyUtil(data->key                 , key                 , STRSZ);
    }

    return(RSOK);
}

// findItem(): find item in table metadata
// oid - table metadata oid
// resval - result data
int CTableMetadata::findItem(long oid, table_metadata_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        table_metadata_t* p = &m_arrTableMetadata[i];    
        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in table metadata
// key - table metadata key
// resval - result data
int CTableMetadata::findItem(char* key, table_metadata_t** resval)
{
    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumEntries; i++)
    {
        table_metadata_t* p = &m_arrTableMetadata[i];    
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

// findAll(): find all item in table metadata
// arr - result data (array of table metadata)
// arrsz - return the number of rows in the array
int CTableMetadata::findAll(table_metadata_t** arr, long* arrsz)
{
    (*arrsz) = m_currNumEntries;
    (*arr) = (table_metadata_t*)allocDataArray(sizeof(table_metadata_t), (*arrsz));
    if((*arr) == NULL) return RSERR;

    table_metadata_t* p = (*arr);
    for(int i = 0; i < m_currNumEntries; i++) {
        memNCpyUtil((byte*)p, (byte*)&m_arrTableMetadata[i], sizeof(table_metadata_t));
        debugEntry(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLEMETADATA_H, "findAll()", p);
        p++;
    }  
    return RSOK;
}

// findItemByModuleName(): find item in table matadata
// module_name - name of module to search
// resval - result data
int CTableMetadata::findItemByModuleName(char* module_name, table_metadata_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        table_metadata_t* p = &m_arrTableMetadata[i];    
        if(strNCmpUtil(p->module_name, module_name, STRSZ) == 0)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// deleteItem(): mark item as deleted in table metadata
// oid - table metadata oid
// uid - user id
int CTableMetadata::deleteItem(long oid, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    table_metadata_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLEMETADATA_H, "deleteItem()", ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in table metadata
// key - table metadata key
// uid - user id
int CTableMetadata::deleteItem(char* key, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    table_metadata_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_TABLEMETADATA_H, "deleteItem()", ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): new item data
// data - table metadata reference
table_metadata_t* CTableMetadata::newItemData(table_metadata_t** data)
{
    if((*data) == NULL)
        (*data) = (table_metadata_t*)allocData(sizeof(table_metadata_t));
        
    (*data)->oid                 = DBNULL_LONG;
    (*data)->key_hash            = DBNULL_LONG;
    for(int i = 0; i < MAX_TBLSPC_COPIES; i++)
        (*data)->tablespace_oid[i] = DBNULL_LONG;
    (*data)->num_tablespaces     = DBNULL_LONG;
    (*data)->num_entries         = DBNULL_LONG;
    (*data)->create_uid          = DBNULL_LONG;
    (*data)->modify_uid          = DBNULL_LONG;
    (*data)->delete_uid          = DBNULL_LONG;
    (*data)->create_date         = DBNULL_LONG;
    (*data)->modify_date         = DBNULL_LONG;
    (*data)->delete_date         = DBNULL_LONG;
    (*data)->is_modified         = DBNULL_LONG;
    (*data)->is_deleted          = DBNULL_LONG;
    (*data)->table_type          = DBNULL_LONG;
    (*data)->reference_table_oid = DBNULL_LONG;
    strNCpyUtil((*data)->module_name         , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->table_name          , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->table_filename      , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->idx1_name           , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->idx1_filename       , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->idx2_name           , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->idx2_filename       , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->seq_name            , (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->key                 , (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): mark item as deleted in table metadata
// data - data reference
// oid - object id
// key_hash - record key hash
// tablespace_oid - pointer tablespace identifier array
// num_tablespaces - number of tablespaces in array
// num_entries - number of entries
// create_uid - create user id
// modify_uid - modify user id
// delete_uid - delete user id
// create_date - create timestamp
// modify_date - modify timestamp
// delete_date - delete timestamp
// is_modified - record is modifyed
// is_deleted - record is deleted
// table_type - table type (1=TBTYPE_DATATABLE/2=TBTYPE_IMAGETABLE)
// reference_table_oid - referencied table oid
// module_name - module name for data classification
// table_name - table name
// table_filename - table filename
// idx1_name - index IDX1 name
// idx1_filename - index IDX1 filename
// idx2_name - index IDX2 name
// idx2_filename - index IDX2 filename
// seq_name - sequence name
// key - record key
table_metadata_t* CTableMetadata::setItemData(
    table_metadata_t** data, 
    long oid,
    long key_hash,
    long* tablespace_oid,
    long num_tablespaces,
    long num_entries,
    long create_uid,
    long modify_uid,
    long delete_uid,
    long create_date,
    long modify_date,
    long delete_date,
    long is_modified,
    long is_deleted,
    long table_type,
    long reference_table_oid,
    char* module_name,
    char* table_name,
    char* table_filename,
    char* idx1_name,
    char* idx1_filename,
    char* idx2_name,
    char* idx2_filename,
    char* seq_name,
    char* key)
{
    if((*data) == NULL)
        (*data) = (table_metadata_t*)allocData(sizeof(table_metadata_t));
        
    (*data)->oid                 = oid;
    (*data)->key_hash            = key_hash;
    for(int i = 0; i < num_tablespaces; i++)
        (*data)->tablespace_oid[i] = tablespace_oid[i];
    (*data)->num_tablespaces     = num_tablespaces;
    (*data)->num_entries         = num_entries;
    (*data)->create_uid          = create_uid;
    (*data)->modify_uid          = modify_uid;
    (*data)->delete_uid          = delete_uid;
    (*data)->create_date         = create_date;
    (*data)->modify_date         = modify_date;
    (*data)->delete_date         = delete_date;
    (*data)->is_modified         = is_modified;
    (*data)->is_deleted          = is_deleted;
    (*data)->table_type          = table_type;
    (*data)->reference_table_oid = reference_table_oid;
    strNCpyUtil((*data)->module_name, module_name, STRSZ);
    strNCpyUtil((*data)->table_name, table_name, STRSZ);
    strNCpyUtil((*data)->table_filename, table_filename, STRSZ);
    strNCpyUtil((*data)->idx1_name, idx1_name, STRSZ);
    strNCpyUtil((*data)->idx1_filename, idx1_filename, STRSZ);
    strNCpyUtil((*data)->idx2_name, idx2_name, STRSZ);
    strNCpyUtil((*data)->idx2_filename, idx2_filename, STRSZ);
    strNCpyUtil((*data)->seq_name, seq_name, STRSZ);
    strNCpyUtil((*data)->key, key, STRSZ);

    return (*data);
}

// debug(): list all tables in tablespace (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
void CTableMetadata::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    table_metadata_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrTableMetadata[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): list table data (=DEBUGLEVEL)
// debugLevel - debug level
// className - caller class name
// methodName - caller method name
// p - pointer to a users entry
void CTableMetadata::debugEntry(int debugLevel, const char* className, const char* methodName, table_metadata_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "TableMetadata: Oid=%ld,KeyHash=%ld,TableSpaceOid=%ld,NumTableSpace=%ld,NumEntries=%ld,CreateUid=%ld,ModifyUid=%ld,DeleteUid=%ld,CreateDate=%ld,ModifyDate=%ld,DeleteDate=%ld,IsModified=%ld,IsDeleted=%ld,TableType=%ld,ReferenceTableOid=%ld,ModuleName=%s,TableName=%s,TableFileName=%s,Idx1Name=%s,Idx1FileName=%s,Idx2Name=%s,Idx2FileName=%s,SeqName=%s,Key=%s\n",
        p->oid,
        p->key_hash,
        p->tablespace_oid[0],
        p->num_tablespaces,
        p->num_entries,
        p->create_uid,
        p->modify_uid,
        p->delete_uid,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_modified,
        p->is_deleted,
        p->table_type,
        p->reference_table_oid,
        p->module_name,
        p->table_name,
        p->table_filename,
        p->idx1_name,
        p->idx1_filename,
        p->idx2_name,
        p->idx2_filename,
        p->seq_name,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

// showAll(): show the list of all tables in table metadata
void CTableMetadata::showAll()
{
    table_metadata_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrTableMetadata[i];
        showEntry(p);
    }  
}

// showEntry(): show the list of all tables metadata
// p - pointer to a users entry
void CTableMetadata::showEntry(table_metadata_t* p)
{
    bigstr_t tableMetadataXml;
    strSetEmptyUtil(tableMetadataXml);

    toXml(p, tableMetadataXml);

    printf(
        "TableMetadata: Oid=%ld,KeyHash=%ld,TableSpaceOid=%ld,NumTableSpace=%ld,NumEntries=%ld,CreateUid=%ld,ModifyUid=%ld,DeleteUid=%ld,CreateDate=%ld,ModifyDate=%ld,DeleteDate=%ld,IsModified=%ld,IsDeleted=%ld,TableType=%ld,ReferenceTableOid=%ld,ModuleName=%s,TableName=%s,TableFileName=%s,Idx1Name=%s,Idx1FileName=%s,Idx2Name=%s,Idx2FileName=%s,SeqName=%s,Key=%s,Data=%s\n",
        p->oid,
        p->key_hash,
        p->tablespace_oid[0],
        p->num_tablespaces,
        p->num_entries,
        p->create_uid,
        p->modify_uid,
        p->delete_uid,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_modified,
        p->is_deleted,
        p->table_type,
        p->reference_table_oid,
        p->module_name,
        p->table_name,
        p->table_filename,
        p->idx1_name,
        p->idx1_filename,
        p->idx2_name,
        p->idx2_filename,
        p->seq_name,
        p->key,
        tableMetadataXml);
}

// toXml(): return XML representing the table metadata
// p - pointer to a tablespace entry
// returnXml - XML return data
char* CTableMetadata::toXml(table_metadata_t* p, char* returnXml)
{
    sprintf(returnXml,
        DEF_XML_RESPONSE_TABLEMETADATA,
        p->oid,
        p->key_hash,
        p->tablespace_oid[0],
        p->num_tablespaces,
        p->num_entries,
        p->create_uid,
        p->modify_uid,
        p->delete_uid,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_modified,
        p->is_deleted,
        p->table_type,
        p->reference_table_oid,
        p->module_name,
        p->table_name,
        p->table_filename,
        p->idx1_name,
        p->idx1_filename,
        p->idx2_name,
        p->idx2_filename,
        p->seq_name,
        p->key);
    return returnXml;
}

// parserXml(): xml data entry parser
// data - data reference
// xmlData - xml data
int CTableMetadata::parserXml(table_metadata_t* p, char* xmlData)
{
    str_t str_oid;
    xmlNodeUtil(str_oid, xmlData, (char*)"Oid", 1);
    p->oid = atol(str_oid);       

    str_t str_key_hash;
    xmlNodeUtil(str_key_hash, xmlData, (char*)"KeyHash", 1);
    p->key_hash = atol(str_key_hash);       

    str_t tag_tablespace_oid;
    str_t str_tablespace_oid;
    for(int i = 0; i < p->num_tablespaces; i++)
    {
        sprintf(tag_tablespace_oid, (char*)"TableSpaceOid_%d", i);
        xmlNodeUtil(str_tablespace_oid, xmlData, tag_tablespace_oid, 1);
        p->tablespace_oid[i] = atol(str_tablespace_oid);       
    }

    str_t str_num_tablespaces;
    xmlNodeUtil(str_num_tablespaces, xmlData, (char*)"NumTableSpaces", 1);
    p->num_tablespaces = atol(str_num_tablespaces);       

    str_t str_num_entries;
    xmlNodeUtil(str_num_entries, xmlData, (char*)"NumEntries", 1);
    p->num_entries = atol(str_num_entries);       

    str_t str_create_uid;
    xmlNodeUtil(str_create_uid, xmlData, (char*)"CreateUid", 1);
    p->create_uid = atol(str_create_uid);       

    str_t str_modify_uid;
    xmlNodeUtil(str_modify_uid, xmlData, (char*)"ModifyUid", 1);
    p->modify_uid = atol(str_modify_uid);       

    str_t str_delete_uid;
    xmlNodeUtil(str_delete_uid, xmlData, (char*)"DeleteUid", 1);
    p->delete_uid = atol(str_delete_uid);       

    str_t str_create_date;
    xmlNodeUtil(str_create_date, xmlData, (char*)"CreateDate", 1);
    p->create_date = atol(str_create_date);       

    str_t str_modify_date;
    xmlNodeUtil(str_modify_date, xmlData, (char*)"ModifyDate", 1);
    p->modify_date = atol(str_modify_date);       

    str_t str_delete_date;
    xmlNodeUtil(str_delete_date, xmlData, (char*)"DeleteDate", 1);
    p->delete_date = atol(str_delete_date);       

    str_t str_is_modified;
    xmlNodeUtil(str_is_modified, xmlData, (char*)"IsModified", 1);
    p->is_modified = atol(str_is_modified);       

    str_t str_is_deleted;
    xmlNodeUtil(str_is_deleted, xmlData, (char*)"IsDeleted", 1);
    p->is_deleted = atol(str_is_deleted);       

    str_t str_table_type;
    xmlNodeUtil(str_table_type, xmlData, (char*)"TableType", 1);
    p->table_type = atol(str_table_type);       

    str_t str_reference_table_oid;
    xmlNodeUtil(str_reference_table_oid, xmlData, (char*)"ReferenceTableOid", 1);
    p->reference_table_oid = atol(str_reference_table_oid);       

    str_t str_module_name;
    xmlNodeUtil(str_module_name, xmlData, (char*)"ModuleName", 1);
    strNCpyUtil(p->module_name, str_module_name, STRSZ);       

    str_t str_table_name;
    xmlNodeUtil(str_table_name, xmlData, (char*)"TableName", 1);
    strNCpyUtil(p->table_name, str_table_name, STRSZ);       

    str_t str_table_filename;
    xmlNodeUtil(str_table_filename, xmlData, (char*)"TableFilename", 1);
    strNCpyUtil(p->table_filename, str_table_filename, STRSZ);       

    str_t str_idx1_name;
    xmlNodeUtil(str_idx1_name, xmlData, (char*)"Idx1Name", 1);
    strNCpyUtil(p->idx1_name, str_idx1_name, STRSZ);       

    str_t str_idx1_filename;
    xmlNodeUtil(str_idx1_filename, xmlData, (char*)"Idx1Filename", 1);
    strNCpyUtil(p->idx1_filename, str_idx1_filename, STRSZ);       

    str_t str_idx2_name;
    xmlNodeUtil(str_idx2_name, xmlData, (char*)"Idx2Name", 1);
    strNCpyUtil(p->idx2_name, str_idx2_name, STRSZ);       

    str_t str_idx2_filename;
    xmlNodeUtil(str_idx2_filename, xmlData, (char*)"Idx2Filename", 1);
    strNCpyUtil(p->idx2_filename, str_idx2_filename, STRSZ);       

    str_t str_seq_name;
    xmlNodeUtil(str_seq_name, xmlData, (char*)"SeqName", 1);
    strNCpyUtil(p->seq_name, str_seq_name, STRSZ);       

    str_t str_key;
    xmlNodeUtil(str_key, xmlData, (char*)"Key", 1);
    strNCpyUtil(p->key, str_key, STRSZ);       

    return RSOK;
}

table_metadata_t* CTableMetadata::getDataTable()
{
    return m_arrTableMetadata;
}

table_metadata_t* CTableMetadata::getItemAt(int pos)
{
    if(pos < m_currNumEntries)
    {
        table_metadata_t* p = &m_arrTableMetadata[pos];
        return p;
    }
    return NULL;
}

int CTableMetadata::getMaxNumEntries()
{
    return m_maxNumEntries;
}

int CTableMetadata::getCurrNumEntries()
{
    return m_currNumEntries;
}
