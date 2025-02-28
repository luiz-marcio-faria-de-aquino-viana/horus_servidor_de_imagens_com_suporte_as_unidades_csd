/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_datatable.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/06/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CDataTable::CDataTable(char* dataSeqName, char* dataTableName, char* dataTableFileName, char* dataTableFullPath, int maxNumEntries)
{
    strNCpyUtil(m_dataSeqName, dataSeqName, STRSZ);
    strNCpyUtil(m_dataTableName, dataTableName, STRSZ);
    strNCpyUtil(m_dataTableFileName, dataTableFileName, STRSZ);
    strNCpyUtil(m_dataTableFullPath, dataTableFullPath, PATHNAMESZ);

    m_maxNumEntries = maxNumEntries; 
    m_currNumEntries = 0; 

    m_arrDataTable = (data_table_t*)allocDataArray(sizeof(data_table_t), m_maxNumEntries);
}

CDataTable::~CDataTable()
{
    freeDataArray(m_arrDataTable);
}

// saveFile(): save data table to file
// fileName - data table file name
int CDataTable::saveFile(char* fileName)
{
    bigstr_t errmsg;
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(data_table_t);
        for(int i = 0; i < m_currNumEntries; i++)
        {
            data_table_t* p = &m_arrDataTable[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_01, __HORUSDB_MOD_DATATABLE_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// loadFile(): load data table from file
// fileName - data table file name
int CDataTable::loadFile(char* fileName)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_READ);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(data_table_t);

        m_currNumEntries = 0;
        while(m_currNumEntries < m_maxNumEntries)
        {
            if(fread(&m_arrDataTable[m_currNumEntries], 1, size, f) == 0) break;
            m_currNumEntries += 1;
        }
        fclose(f);
    }
    return rscode;
}

// addItem(): add item to table metadata
// key - image table key
// image_oid - referenced image identifier
// is_train_data - identify if is train data
// train_score - score of train data
// is_test_data - identify if is test data
// test_score - score of test data
// is_classified_data - identify if is classified data
// classification_score - score of classified data
// xmin - x of lower left corner of image area
// ymin - y of lower left corner of image area
// xmax - x of upper right corner of image area
// ymax - y of upper right corner of image area
int CDataTable::addItem(
    char* key,
    long image_oid,
    long is_train_data,
    double train_score,
    long is_test_data,
    double test_score,
    long is_classified_data,
    double classification_score,
    long xmin,
    long ymin,
    long xmax,
    long ymax)
{
    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    data_table_t* data = NULL;

    long keyHash = getHash(key);

    long ret_oid = -1;
    
    if(findItem(key, &data) != RSOK)
    {
        data = &(m_arrDataTable[m_currNumEntries]);

        ret_oid = seq->nextVal(m_dataSeqName);

        /* Add new item
         */
        setItemData(
            &data, 
            ret_oid,
            keyHash,
            image_oid,
            currTimestamp,
            currTimestamp,
            DBTRUE,
            currTimestamp,
            DBTRUE,
            DBNULL_LONG,
            DBFALSE,
            is_train_data,
            train_score,
            is_test_data,
            test_score,
            is_classified_data,
            classification_score,
            xmin,
            ymin,
            xmax,
            ymax,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        ret_oid = data->oid;

        data->image_oid = image_oid;
        data->modify_date = currTimestamp;
        data->is_modified = DBTRUE;
        data->update_date = currTimestamp;
        data->is_updated = DBTRUE;
        data->is_train_data = is_train_data;
        data->train_score = train_score;
        data->is_test_data = is_test_data;
        data->test_score = test_score;
        data->is_classified_data = is_classified_data;
        data->classification_score = classification_score;
        data->xmin = xmin;
        data->ymin = ymin;
        data->xmax = xmax;
        data->ymax = ymax;
    }

    return(ret_oid);
}

// addItem(): add item to data table
// oid - image table oid
// key - image table key
// image_oid - referenced image identifier
// is_train_data - identify if is train data
// train_score - score of train data
// is_test_data - identify if is test data
// test_score - score of test data
// is_classified_data - identify if is classified data
// classification_score - score of classified data
// xmin - x of lower left corner of image area
// ymin - y of lower left corner of image area
// xmax - x of upper right corner of image area
// ymax - y of upper right corner of image area
int CDataTable::addItem(
    long oid,
    char* key,
    long image_oid,
    long is_train_data,
    double train_score,
    long is_test_data,
    double test_score,
    long is_classified_data,
    double classification_score,
    long xmin,
    long ymin,
    long xmax,
    long ymax)
{
    long currTimestamp = getCurrentTimestamp();

    data_table_t* data;

    long keyHash = getHash(key);
    
    long ret_oid = -1;

    if(findItem(oid, &data) != RSOK)
    {
        data = &(m_arrDataTable[m_currNumEntries]);

        /* Add new item
         */
        ret_oid = oid;

        setItemData(
            &data, 
            ret_oid,
            keyHash,
            image_oid,
            currTimestamp,
            currTimestamp,
            DBTRUE,
            currTimestamp,
            DBTRUE,
            DBNULL_LONG,
            DBFALSE,
            is_train_data,
            train_score,
            is_test_data,
            test_score,
            is_classified_data,
            classification_score,
            xmin,
            ymin,
            xmax,
            ymax,
            key);

        m_currNumEntries += 1;
    }
    else
    {
        /* Update existent item
         */
        ret_oid = data->oid;

        data->image_oid = image_oid;
        data->modify_date = currTimestamp;
        data->is_modified = DBTRUE;
        data->update_date = currTimestamp;
        data->is_updated = DBTRUE;
        data->is_train_data = is_train_data;
        data->train_score = train_score;
        data->is_test_data = is_test_data;
        data->test_score = test_score;
        data->is_classified_data = is_classified_data;
        data->classification_score = classification_score;
        data->xmin = xmin;
        data->ymin = ymin;
        data->xmax = xmax;
        data->ymax = ymax;
    }

    return(ret_oid);
}

// findAllItems(): find all items in data table
// arr - result data (array of items)
// arrsz - return the number of rows in the array
int CDataTable::findAll(data_table_t** arr, long* arrsz)
{
    (*arrsz) = m_currNumEntries;
    (*arr) = (data_table_t*)allocDataArray(sizeof(data_table_t), (*arrsz));
    if((*arr) == NULL) return RSERR;

    data_table_t* p = (*arr);
    for(int i = 0; i < m_currNumEntries; i++) {
        memNCpyUtil((byte*)p, (byte*)&m_arrDataTable[i], sizeof(data_table_t));
        debugEntry(DEBUG_LEVEL_01, __HORUSDB_MOD_DATATABLE_H, "findAll()", p);
        p++;
    }  
    return RSOK;
}

// findItem(): find item in data table
// oid - data table oid
// resval - result data
int CDataTable::findItem(long oid, data_table_t** resval)
{
    for(int i = 0; i < m_currNumEntries; i++)
    {
        data_table_t* p = &m_arrDataTable[i];    
        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in data table
// key - data table key
// resval - result data
int CDataTable::findItem(char* key, data_table_t** resval)
{
    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumEntries; i++)
    {
        data_table_t* p = &m_arrDataTable[i];    
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

// deleteItem(): mark item as deleted in data table
// oid - data table oid
// uid - user id
int CDataTable::deleteItem(long oid, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    data_table_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSDB_MOD_TABLEMETADATA_H, "deleteItem()", ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in data table
// key - data table key
// uid - user id
int CDataTable::deleteItem(char* key, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    data_table_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSDB_MOD_TABLEMETADATA_H, "deleteItem()", ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): new item data
// data - data table reference
data_table_t* CDataTable::newItemData(data_table_t** data)
{
    if((*data) == NULL)
        (*data) = (data_table_t*)allocData(sizeof(data_table_t));
        
    (*data)->oid                  = DBNULL_LONG;
    (*data)->key_hash             = DBNULL_LONG;
    (*data)->image_oid            = DBNULL_LONG;
    (*data)->create_date          = DBNULL_LONG;
    (*data)->modify_date          = DBNULL_LONG;
    (*data)->is_modified          = DBNULL_LONG;
    (*data)->update_date          = DBNULL_LONG;
    (*data)->is_updated           = DBNULL_LONG;
    (*data)->delete_date          = DBNULL_LONG;
    (*data)->is_deleted           = DBNULL_LONG;
    (*data)->is_train_data        = DBNULL_LONG;
    (*data)->train_score          = DBNULL_DOUBLE;
    (*data)->is_test_data         = DBNULL_LONG;
    (*data)->test_score           = DBNULL_DOUBLE;
    (*data)->is_classified_data   = DBNULL_LONG;
    (*data)->classification_score = DBNULL_DOUBLE;
    (*data)->xmin                 = DBNULL_LONG;
    (*data)->ymin                 = DBNULL_LONG;
    (*data)->xmax                 = DBNULL_LONG;
    (*data)->ymax                 = DBNULL_LONG;
    strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): mark item as deleted in data table
// data - data reference
// oid - object id
// key_hash - record key hash
// image_oid - referenced image identifier
// create_date - create timestamp
// modify_date - modify timestamp
// is_modified - record is modified
// update_date - update timestamp
// is_updated - record is updated
// delete_date - delete timestamp
// is_deleted - record is deleted
// is_train_data - identify if is train data
// train_score - score of train data
// is_test_data - identify if is test data
// test_score - score of test data
// is_classified_data - identify if is classified data
// classification_score - score of classified data
// xmin - x of lower left corner of image area
// ymin - y of lower left corner of image area
// xmax - x of upper right corner of image area
// ymax - y of upper right corner of image area
// key - record key
data_table_t* CDataTable::setItemData(
    data_table_t** data, 
    long oid,
    long key_hash,
    long image_oid,
    long create_date,
    long modify_date,
    long is_modified,
    long update_date,
    long is_updated,
    long delete_date,
    long is_deleted,
    long is_train_data,
    double train_score,
    long is_test_data,
    double test_score,
    long is_classified_data,
    double classification_score,
    long xmin,
    long ymin,
    long xmax,
    long ymax,
    char* key)
{
    if((*data) == NULL)
        (*data) = (data_table_t*)allocData(sizeof(data_table_t));
        
    (*data)->oid = oid;
    (*data)->key_hash = key_hash;
    (*data)->image_oid = image_oid;
    (*data)->create_date = create_date;
    (*data)->modify_date = modify_date;
    (*data)->is_modified = is_modified;
    (*data)->update_date = update_date;
    (*data)->is_updated = is_updated;
    (*data)->delete_date = delete_date;
    (*data)->is_deleted = is_deleted;
    (*data)->is_train_data = is_train_data;
    (*data)->train_score = train_score;
    (*data)->is_test_data = is_test_data;
    (*data)->test_score = test_score;
    (*data)->is_classified_data = is_classified_data;
    (*data)->classification_score = classification_score;
    (*data)->xmin = xmin;
    (*data)->ymin = ymin;
    (*data)->xmax = xmax;
    (*data)->ymax = ymax;
    strNCpyUtil((*data)->key, key, STRSZ);

    return (*data);
}

/* Debug */

// debugEntry(): show tablespace data
// debugLevel - debug level
// className - class name
// methodName - method name
void CDataTable::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    data_table_t* p = NULL;
    for(int i = 0; i < m_currNumEntries; i++)
    {
        p = &m_arrDataTable[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show tablespace data
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a tablespace entry
void CDataTable::debugEntry(int debugLevel, const char* className, const char* methodName, data_table_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "DataTable: Oid=%ld,KeyHash=%ld,ImageOid=%ld,CreateDate=%ld,ModifyDate=%ld,IsModified=%ld,UpdateDate=%ld,IsUpdated=%ld,DeleteDate=%ld,IsDeleted=%ld,IsTrainData=%ld,TrainScore=%lf,IsTestData=%ld,TestScore=%lf,IsClassifiedData=%ld,ClassificationScore=%lf,XMin=%ld,YMin=%ld,XMax=%ld,YMax=%ld,Key=%s\n",
        p->oid,
        p->key_hash,
        p->image_oid,
        p->create_date,
        p->modify_date,
        p->is_modified,
        p->update_date,
        p->is_updated,
        p->delete_date,
        p->is_deleted,
        p->is_train_data,
        p->train_score,
        p->is_test_data,
        p->test_score,
        p->is_classified_data,
        p->classification_score,
        p->xmin,
        p->ymin,
        p->xmax,
        p->ymax,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

// toXml(): show tablespace data
// p - pointer to a tablespace entry
// returnXml - XML return data
char* CDataTable::toXml(data_table_t* p, char* returnXml)
{
    sprintf(
        returnXml,
        DEF_XML_RESPONSE_ITEM,
        p->oid,
        p->key_hash,
        p->image_oid,
        p->create_date,
        p->modify_date,
        p->is_modified,
        p->update_date,
        p->is_updated,
        p->delete_date,
        p->is_deleted,
        p->is_train_data,
        p->train_score,
        p->is_test_data,
        p->test_score,
        p->is_classified_data,
        p->classification_score,
        p->xmin,
        p->ymin,
        p->xmax,
        p->ymax,
        p->key);
    return returnXml;
}

// parserXml(): xml data entry parser
// p - pointer reference
// xmlData - xml data
int CDataTable::parserXml(data_table_t* p, char* xmlData)
{
    str_t str_oid;
    xmlNodeUtil(str_oid, xmlData, (char*)"Oid", 1);
    p->oid = atol(str_oid);       

    str_t str_key_hash;
    xmlNodeUtil(str_key_hash, xmlData, (char*)"KeyHash", 1);
    p->key_hash = atol(str_key_hash);       

    str_t str_image_oid;
    xmlNodeUtil(str_image_oid, xmlData, (char*)"ImageOid", 1);
    p->oid = atol(str_image_oid);       

    str_t str_create_date;
    xmlNodeUtil(str_create_date, xmlData, (char*)"CreateDate", 1);
    p->create_date = atol(str_create_date);       

    str_t str_modify_date;
    xmlNodeUtil(str_modify_date, xmlData, (char*)"ModifyDate", 1);
    p->modify_date = atol(str_modify_date);       

    str_t str_is_modified;
    xmlNodeUtil(str_is_modified, xmlData, (char*)"IsModified", 1);
    p->is_deleted = atol(str_is_modified);       

    str_t str_update_date;
    xmlNodeUtil(str_update_date, xmlData, (char*)"UpdateDate", 1);
    p->update_date = atol(str_update_date);       

    str_t str_is_updated;
    xmlNodeUtil(str_is_updated, xmlData, (char*)"IsUpdated", 1);
    p->is_updated = atol(str_is_updated);       

    str_t str_delete_date;
    xmlNodeUtil(str_delete_date, xmlData, (char*)"DeleteDate", 1);
    p->delete_date = atol(str_delete_date);       

    str_t str_is_deleted;
    xmlNodeUtil(str_is_deleted, xmlData, (char*)"IsDeleted", 1);
    p->is_deleted = atol(str_is_deleted);       

    str_t str_is_train_data;
    xmlNodeUtil(str_is_train_data, xmlData, (char*)"IsTrainData", 1);
    p->is_deleted = atol(str_is_train_data);       

    str_t str_train_score;
    xmlNodeUtil(str_train_score, xmlData, (char*)"TrainScore", 1);
    p->train_score = atof(str_train_score);       

    str_t str_is_test_data;
    xmlNodeUtil(str_is_test_data, xmlData, (char*)"IsTestData", 1);
    p->is_test_data = atol(str_is_test_data);       

    str_t str_test_score;
    xmlNodeUtil(str_test_score, xmlData, (char*)"TestScore", 1);
    p->test_score = atof(str_test_score);       

    str_t str_is_classified_data;
    xmlNodeUtil(str_is_classified_data, xmlData, (char*)"IsClassifiedData", 1);
    p->is_classified_data = atof(str_is_classified_data);       

    str_t str_classification_score;
    xmlNodeUtil(str_classification_score, xmlData, (char*)"ClassificationScore", 1);
    p->classification_score = atof(str_classification_score);       

    str_t str_xmin;
    xmlNodeUtil(str_xmin, xmlData, (char*)"XMin", 1);
    p->xmin = atof(str_xmin);       

    str_t str_ymin;
    xmlNodeUtil(str_ymin, xmlData, (char*)"YMin", 1);
    p->ymin = atof(str_ymin);       

    str_t str_xmax;
    xmlNodeUtil(str_xmax, xmlData, (char*)"XMax", 1);
    p->xmax = atof(str_xmax);       

    str_t str_ymax;
    xmlNodeUtil(str_ymax, xmlData, (char*)"YMax", 1);
    p->ymax = atof(str_ymax);       

    str_t str_key;
    xmlNodeUtil(str_key, xmlData, (char*)"Key", 1);
    strNCpyUtil(p->key, str_key, STRSZ);       

    return RSOK;
}

/* Getters/Setters */

char* CDataTable::getDataSeqName()
{
    return m_dataTableName;
}

char* CDataTable::getDataTableName()
{
    return m_dataTableName;
}

char* CDataTable::getDataTableFileName()
{
    return m_dataTableFileName;
}

char* CDataTable::getDataTableFullPath()
{
    return m_dataTableFullPath;
}

data_table_t* CDataTable::getDataTable()
{
    return m_arrDataTable;
}

int CDataTable::getMaxNumEntries()
{
    return m_maxNumEntries;
}

int CDataTable::getCurrNumEntries()
{
    return m_currNumEntries;
}
