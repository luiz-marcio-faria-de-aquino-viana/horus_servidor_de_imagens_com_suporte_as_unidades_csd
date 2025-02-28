/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_sequence.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 17/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_SEQUENCE_H
#define __HORUSSRV_MOD_SEQUENCE_H      "__HORUSSRV_MOD_SEQUENCE_H"

class CSequence
{
private:
    sequence_t* m_arrSequence;
    int m_maxNumEntries; 
    int m_currNumEntries; 

public:
    CSequence(int maxNumEntries);
    ~CSequence();

    // loadFile(): load table of sequence from file
    // fileName - sequence's table file name
    int loadFile(char* fileName);

    // saveFile(): save table of sequence to file
    // fileName - sequence's table file name
    int saveFile(char* fileName);

    // currVal(): current value in sequence
    // key - sequence key
    long currVal(char* key);

    // nextVal(): next value in sequence
    // key - sequence key
    long nextVal(char* key);

    // addItem(): add item to tablespace
    // oid - sequence oid
    // key - sequence key
    // name - tablespace name
    // path - tablespace path
    int addItem(long oid, char* key, char* name, long initialVal, long maxVal, long currVal);

    // addItem(): add item to tablespace
    // key - sequence key
    // name - tablespace name
    // path - tablespace path
    int addItem(char* key, char* name, long initialVal, long maxVal, long currVal);

    // findItem(): find item in sequence
    // oid - sequence oid
    // resval - result data
    int findItem(long oid, sequence_t** resval);

    // findItem(): find item in sequence
    // key - sequence key
    // resval - result data
    int findItem(char* key, sequence_t** resval);

    // deleteItem(): mark item as deleted in sequence
    // oid - sequence oid
    int deleteItem(long oid);

    // deleteItem(): mark item as deleted in sequence
    // key - sequence key
    int deleteItem(char* key);

    // newItemData(): set new item
    // data - sequence data
    sequence_t* newItemData(sequence_t** data);

    // setItemData(): set existent item
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
    sequence_t* setItemData(
        sequence_t** data, 
        long oid,
        long key_hash,
        long create_date,
        long modifty_date,
        long delete_date,
        long is_deleted,
        long initial_value,
        long max_value,
        long current_value,
        char* name,
        char* key);

    void debug(int debugLevel, const char* className, const char* methodName);

    void debugEntry(int debugLevel, const char* className, const char* methodName, sequence_t* p);

    // toXml(): return XML representing the sequence
    // p - pointer to a sequence entry
    // returnXml - XML return data
    char* toXml(sequence_t* p, char* returnXml);

    // parserXml(): xml data entry parser
    // data - data reference
    // xmlData - xml data
    int parserXml(sequence_t* p, char* xmlData);

};

/* NEW_TYPE: CSequence Pointer */

typedef CSequence* CSequencePtr_t;

#endif
