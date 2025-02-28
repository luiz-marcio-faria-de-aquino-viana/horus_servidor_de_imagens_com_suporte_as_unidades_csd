/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_metadata.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_TABLEMETADATA_H
#define __HORUSSRV_MOD_TABLEMETADATA_H      "__HORUSSRV_MOD_TABLEMETADATA_H"

class CTableMetadata
{
private:
    table_metadata_t* m_arrTableMetadata;
    int m_maxNumEntries; 
    int m_currNumEntries; 

public:
    CTableMetadata(int maxNumEntries);
    ~CTableMetadata();

    // loadFile(): load table metadata from file
    // fileName - table metadata file name
    int loadFile(char* fileName);

    // saveFile(): save table metadata to file
    // fileName - table metadata file name
    int saveFile(char* fileName);

    // addItem(): add item to table metadata
    // key - table metadata key
    // tablespace_oid - pointer tablespace identifier array
    // num_tablespaces - number of tablespaces in array
    // num_entries - number of entries
    // table_type - table type (1=TBTYPE_DATATABLE/2=TBTYPE_IMAGETABLE)
    // reference_table_oid - referencied table oid
    // module_name - module name for data classification
    // image_table_name - image table name
    // image_table_filename - image table filename
    // table_name - table name
    // table_filename - table filename
    // idx1_name - index IDX1 name
    // idx1_filename - index IDX1 filename
    // idx2_name - index IDX2 name
    // idx2_filename - index IDX2 filename
    // seq_name - sequence name
    // uid - user identifier
    int addItem(
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
        long uid);

    // addItem(): add item to table metadata
    // oid - table matadata oid
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
    int addItem(
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
        long uid);

    // findItem(): find item in table matadata
    // oid - table matadata oid
    // resval - result data
    int findItem(long oid, table_metadata_t** resval);

    // findItem(): find item in table matadata
    // key - table metadata key
    // resval - result data
    int findItem(char* key, table_metadata_t** resval);

    // findAll(): find all item in table metadata
    // arr - result data (array of table metadata)
    // arrsz - return the number of rows in the array
    int findAll(table_metadata_t** arr, long* arrsz);

    // findItemByModuleName(): find item in table matadata
    // module_name - name of module to search
    // resval - result data
    int findItemByModuleName(char* module_name, table_metadata_t** resval);

    // deleteItem(): mark item as deleted in table matadata
    // oid - table matadata oid
    // uid - user id
    int deleteItem(long oid, long uid);

    // deleteItem(): mark item as deleted in table matadata
    // key - table matadata key
    // uid - user id
    int deleteItem(char* key, long uid);

    // newItemData(): mark item as deleted in table matadata
    // data - data reference
    table_metadata_t* newItemData(table_metadata_t** data);

    // setItemData(): mark item as deleted in tablespace
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
    // is_modified - record is modified
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
    table_metadata_t* setItemData(
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
        char* key);

    /* Debug */

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
    void debugEntry(int debugLevel, const char* className, const char* methodName, table_metadata_t* p);

    // showAll(): show the list of all tables in table metadata
    void showAll();

    // showEntry(): show the list of all tables metadata
    // p - pointer to a users entry
    void showEntry(table_metadata_t* p);

    // toXml(): return XML data
    // p - pointer to a users entry
    // returnXml - XML return data
    char* toXml(table_metadata_t* p, char* returnXml);

    // parserXml(): xml data entry parser
    // data - data reference
    // xmlData - xml data
    int parserXml(table_metadata_t* p, char* xmlData);

    /* Getters/Setters */

    table_metadata_t* getDataTable();

    table_metadata_t* getItemAt(int pos);

    int getMaxNumEntries(); 
    
    int getCurrNumEntries(); 

};

/* NEW_TYPE: CTableMetadata Pointer */

typedef CTableMetadata* CTableMetadataPtr_t;

#endif
