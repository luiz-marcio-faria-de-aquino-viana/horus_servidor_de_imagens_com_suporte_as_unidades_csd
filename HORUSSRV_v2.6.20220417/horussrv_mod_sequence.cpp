/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_sequence.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 17/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CSequence::CSequence(int maxNumEntries)
{
    m_maxNumEntries = maxNumEntries; 
    m_currNumEntries = 0; 

    m_arrSequence = (sequence_t*)allocDataArray(sizeof(sequence_t), m_maxNumEntries);
}

CSequence::~CSequence()
{
    freeDataArray(m_arrSequence);
}

// saveFile(): save table of sequence to file
// fileName - sequence's table file name
int CSequence::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(sequence_t);
        for(int i = 0; i < m_currNumEntries; i++)
        {
            sequence_t* p = &m_arrSequence[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_03, __HORUSSRV_MOD_SEQUENCE_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// loadFile(): load table of sequence from file
// fileName - sequence's table file name
int CSequence::loadFile(char* fileName)
{
    FILE* f = NULL;
 
    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(sequence_t);

        m_currNumEntries = 0;
        while(m_currNumEntries < m_maxNumEntries)
        {
            if(fread(&m_arrSequence[m_currNumEntries], 1, size, f) == 0) break;
            m_currNumEntries += 1;
        }
        fclose(f);
    }
    return rscode;
}

// currVal(): current value in sequence
// key - sequence key
long CSequence::currVal(char* key)
{
    sequence_t* data = NULL;
    if(findItem(key, &data) != RSOK)
        errMsg(__HORUSSRV_MOD_SEQUENCE_H, "currVal()", ERR_CANTFINDKEY);
    return data->current_value;
}

// nextVal(): next value in sequence
// key - sequence key
long CSequence::nextVal(char* key)
{
    long currTimestamp = getCurrentTimestamp();

    sequence_t* data = NULL;
    
    if(findItem(key, &data) == RSERR)
        errMsg(__HORUSSRV_MOD_SEQUENCE_H, "nextVal()", ERR_CANTFINDKEY);

    /* Update existent item
    */
    data->modify_date = currTimestamp;
    data->current_value += 1;

    if(data->current_value >= data->max_value)
        errMsg(__HORUSSRV_MOD_SEQUENCE_H, "nextVal()", ERR_SEQUENCEVALUEOVERFLOW);

    return data->current_value;
}

// addItem(): create new sequence
// oid - sequence oid
// key - sequence key
// name - sequence name
// initialVal - sequence initial value
// maxVal - sequence max value
// currVal - sequence current value
int CSequence::addItem(long oid, char* key, char* name, long initialVal, long maxVal, long currVal)
{
    long currTimestamp = getCurrentTimestamp();

    sequence_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(oid, &data) != RSOK)
    {
        data = &(m_arrSequence[m_currNumEntries]);

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
            initialVal,
            maxVal,
            currVal,
            name,
            key);

        m_currNumEntries++;
    }
    else
    {
        /* Update existent item
         */
        data->modify_date   = currTimestamp;
        data->initial_value = initialVal;
        data->max_value     = maxVal;
        data->current_value = currVal;
        strNCpyUtil(data->sequence_name, name, STRSZ);
    }

    return(RSOK);
}

// addItem(): create new sequence
// key - sequence key
// name - sequence name
// initialVal - sequence initial value
// maxVal - sequence max value
// currVal - sequence current value
int CSequence::addItem(char* key, char* name, long initialVal, long maxVal, long currVal)
{
    if(m_currNumEntries >= m_maxNumEntries) 
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "addItem()", ERR_MAXNUMBERENTRIESREACHED);
        return(RSERR);
    }

    long currTimestamp = getCurrentTimestamp();

    sequence_t* data = NULL;

    long keyHash = getHash(key);
    
    if(findItem(key, &data) != RSOK)
    {
        data = &(m_arrSequence[m_currNumEntries]);

        long oid = this->nextVal((char*)SEQ_SEQUENCE);

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
            initialVal,
            maxVal,
            currVal,
            name,
            key);

        m_currNumEntries++;
    }
    else
    {
        /* Update existent item
         */
        data->key_hash      = keyHash;
        data->modify_date   = currTimestamp;
        data->initial_value = initialVal;
        data->max_value     = maxVal;
        data->current_value = currVal;
        strNCpyUtil(data->sequence_name, name, STRSZ);
        strNCpyUtil(data->key          , key , STRSZ);
    }

    return(RSOK);
}

// findItem(): find item in sequence
// oid - sequence oid
// resval - result data
int CSequence::findItem(long oid, sequence_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        sequence_t* p = &m_arrSequence[i];  
        debugEntry(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "findItem()", p);

        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in sequence
// key - sequence key
// resval - result data
int CSequence::findItem(char* key, sequence_t** resval)
{
    bigstr_t errmsg;

    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumEntries; i++)
    {
        sequence_t* p = &m_arrSequence[i];    
        debugEntry(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "findItem()", p);

        if(p->key_hash == keyHash)
        {
            sprintf(errmsg, "... HashKey=%ld | %ld... OK!\n", p->key_hash, keyHash);
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "findItem()", errmsg);

            if(strNCmpUtil(p->key, key, STRSZ) == 0)
            {
                sprintf(errmsg, "... Key=%s | %s... OK!\n", p->key, key);
                warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "findItem()", errmsg);

                (*resval) = p;
                return(RSOK);
            }
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// deleteItem(): mark item as deleted in sequence
// oid - sequence oid
int CSequence::deleteItem(long oid)
{
    long currTimestamp = getCurrentTimestamp();

    sequence_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "deleteItem()", ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in sequence
// key - sequence key
int CSequence::deleteItem(char* key)
{
    long currTimestamp = getCurrentTimestamp();

    sequence_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_SEQUENCE_H, "deleteItem()", ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): new item data
// data - sequence key
sequence_t* CSequence::newItemData(sequence_t** data)
{
    if((*data) == NULL)
        (*data) = (sequence_t*)allocData(sizeof(sequence_t));

    (*data)->oid           = DBNULL_LONG;
    (*data)->key_hash      = DBNULL_LONG;
    (*data)->create_date   = DBNULL_LONG;
    (*data)->modify_date   = DBNULL_LONG;
    (*data)->delete_date   = DBNULL_LONG;
    (*data)->is_deleted    = DBNULL_LONG;
    (*data)->initial_value = DBNULL_LONG;
    (*data)->max_value     = DBNULL_LONG;
    (*data)->current_value = DBNULL_LONG;
    strNCpyUtil((*data)->sequence_name, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->key          , (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): set item data
// data - sequence data
// oid - object identification
// key_hash - key hash value
// create_date - create timestamp
// modify_date - modify timestamp
// delete_date - delete timestamp
// is_deleted - record is deleted
// initial_value - sequence initial value
// max_value - sequence max value
// current_value - sequence current value
// sequence_name - sequence name
// key - sequence key
sequence_t* CSequence::setItemData(
    sequence_t** data, 
    long oid,
    long key_hash,
    long create_date,
    long modify_date,
    long delete_date,
    long is_deleted,
    long initial_value,
    long max_value,
    long current_value,
    char* name,
    char* key)
{
    if((*data) == NULL)
        (*data) = (sequence_t*)allocData(sizeof(sequence_t));
        
    (*data)->oid           = oid;
    (*data)->key_hash      = key_hash;
    (*data)->create_date   = create_date;
    (*data)->modify_date   = modify_date;
    (*data)->delete_date   = delete_date;
    (*data)->is_deleted    = is_deleted;
    (*data)->initial_value = initial_value;
    (*data)->max_value     = max_value;
    (*data)->current_value = current_value;
    strNCpyUtil((*data)->sequence_name, name, STRSZ);
    strNCpyUtil((*data)->key          , key , STRSZ);

    return (*data);
}

void CSequence::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sequence_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrSequence[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

void CSequence::debugEntry(int debugLevel, const char* className, const char* methodName, sequence_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "Sequence: Oid=%ld,KeyHash=%ld,CreateDate=%ld,ModifyDate=%ld,DeleteDate=%ld,IsDeleted=%ld,InitialValue=%ld,MaxValue=%ld,CurrentValue=%ld,SequenceName=%s,Key=%s\n",
        p->oid,
        p->key_hash,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_deleted,
        p->initial_value,
        p->max_value,
        p->current_value,
        p->sequence_name,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

// toXml(): return XML representing the sequence
// p - pointer to a sequence entry
// returnXml - XML return data
char* CSequence::toXml(sequence_t* p, char* returnXml)
{
    sprintf(
        returnXml,
        DEF_XML_RESPONSE_SEQUENCE,
        p->oid,
        p->key_hash,
        p->create_date,
        p->modify_date,
        p->delete_date,
        p->is_deleted,
        p->initial_value,
        p->max_value,
        p->current_value,
        p->sequence_name,
        p->key);
    return returnXml;
}

// parserXml(): xml data entry parser
// data - data reference
// xmlData - xml data
int CSequence::parserXml(sequence_t* p, char* xmlData)
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

    str_t str_initial_value;
    xmlNodeUtil(str_initial_value, xmlData, (char*)"InitialValue", 1);
    p->initial_value = atol(str_initial_value);       

    str_t str_max_value;
    xmlNodeUtil(str_max_value, xmlData, (char*)"MaxValue", 1);
    p->max_value = atol(str_max_value);       

    str_t str_current_value;
    xmlNodeUtil(str_current_value, xmlData, (char*)"CurrentValue", 1);
    p->current_value = atol(str_current_value);       

    str_t str_sequence_name;
    xmlNodeUtil(str_sequence_name, xmlData, (char*)"SequenceName", 1);
    strNCpyUtil(p->sequence_name, str_sequence_name, STRSZ);       

    str_t str_key;
    xmlNodeUtil(str_key, xmlData, (char*)"Key", 1);
    strNCpyUtil(p->key, str_key, STRSZ);       

    return RSOK;
}
