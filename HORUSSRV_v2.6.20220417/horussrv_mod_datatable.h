/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_datatable.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/06/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_DATATABLE_H
#define __HORUSSRV_MOD_DATATABLE_H       "__HORUSSRV_MOD_DATATABLE_H"

class CDataTable
{
private:
    str_t m_dataSeqName;

    str_t m_dataTableName;

    str_t m_dataTableFileName;
    
    pathname_t m_dataTableFullPath;

    data_table_t* m_arrDataTable;
    int m_maxNumEntries; 
    int m_currNumEntries; 

public:
    CDataTable(char* seqName, char* tableName, char* tableFileName, char* tableFullPath, int maxNumEntries);
    ~CDataTable();

    // loadFile(): load image table from file
    // fileName - image table file name
    int loadFile(char* fileName);

    // saveFile(): save image table to file
    // fileName - image table file name
    int saveFile(char* fileName);

    // addItem(): add item to data table
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
    int addItem(
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
        long ymax);

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
    int addItem(
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
        long ymax);

    // findAll(): find all items in data table
    // arr - item list data
    // arrsz - result data
    int findAll(data_table_t** arr, long* arrsz);

    // findItem(): find item in data table
    // oid - data table oid
    // resval - result data
    int findItem(long oid, data_table_t** resval);

    // findItem(): find item in data table
    // key - data table key
    // resval - result data
    int findItem(char* key, data_table_t** resval);

    // deleteItem(): mark item as deleted in data table
    // oid - data table oid
    // uid - user id
    int deleteItem(long oid, long uid);

    // deleteItem(): mark item as deleted in data table
    // key - data table key
    // uid - user id
    int deleteItem(char* key, long uid);

    // newItemData(): new item data
    // data - image table reference
    data_table_t* newItemData(data_table_t** data);

    // setItemData(): set item values in data table
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
    data_table_t* setItemData(
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
        char* key);

    /* Debug */

    // debugEntry(): show tablespace data
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debugEntry(): show tablespace data
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    // p - pointer to a tablespace entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, data_table_t* p);

    // toXml(): show tablespace data
    // p - pointer to a tablespace entry
    // returnXml - XML return data
    char* toXml(data_table_t* p, char* returnXml);

    // parserXml(): xml data entry parser
    // p - pointer reference
    // xmlData - xml data
    int parserXml(data_table_t* p, char* xmlData);

    /* Getters/Setters */

    char* getDataSeqName();

    char* getDataTableName();

    char* getDataTableFileName();
    
    char* getDataTableFullPath();

    data_table_t* getDataTable();

    int getMaxNumEntries();

    int getCurrNumEntries(); 

};

/* NEW_TYPE: CDataTable Pointer */

typedef CDataTable* CDataTablePtr_t;

#endif
