/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_descriptor.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_DESCRIPTOR_H
#define __HORUSWRK_IDX_DESCRIPTOR_H         "__HORUSWRK_IDX_DESCRIPTOR_H"

class CIdxDescriptor
{
private:
    CIdxEntry* m_firstEntryPtr;
    CIdxEntry* m_lastEntryPtr;
    long m_numberOfEntries;

    long m_keyType;
    long m_insertOrder;

    long m_currEntryId;             // Current Sequence Value for "EntryId"

public:

    CIdxDescriptor(long keyType, long insertOrder);

    ~CIdxDescriptor();

    /* Methodes */

    void init(long keyType, long insertOrder);

    void terminate();

    // Next Sequence "EntryId"

    long nextEntryId();

    // Locate Insert Position

    CIdxEntry* locateInsertPosition(CIdxEntry* entryPtr);

    // Find Operations

    CIdxEntry* findFirst(CIdxEntry** entryPtr);

    CIdxEntry* findLast(CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyDbl(double keyDbl, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr);

    long findAll(CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    long findAll(long keyLng, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    long findAll(double keyDbl, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    long findAll(char* keyStr, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    // Stack Operations

    CIdxEntry* push(CIdxEntry* entryPtr);

    CIdxEntry* pop(CIdxEntry** entryPtr);

    // Fifo Operations

    CIdxEntry* insertFirst(CIdxEntry* entryPtr);

    CIdxEntry* insertLast(CIdxEntry* entryPtr);

    CIdxEntry* removeFirst(CIdxEntry** entryPtr);

    CIdxEntry* removeLast(CIdxEntry** entryPtr);

    // Insert Operations

    CIdxEntry* insertNewEntry(CIdxEntry* newEntryPtr);

    // Remove Operations

    CIdxEntry* removeEntryByKeyLng(long keyLng);

    CIdxEntry* removeEntryByKeyDbl(double keyDbl);

    CIdxEntry* removeEntryByKeyStr(char* keyStr);

    CIdxEntry* removeEntry(CIdxEntry* entryPtr);

    void removeAll();

    // Link Entry Operations

    CIdxEntry* linkEntryAfter(CIdxEntry* newEntryPtr, CIdxEntry* currEntryPtr);

    CIdxEntry* linkEntryBefore(CIdxEntry* newEntryPtr, CIdxEntry* currEntryPtr);

    // Unlink Entry Operations

    CIdxEntry* unlinkEntry(CIdxEntry* entryPtr);

    /* Debug */

    // debug(): show all entry data
    // debugLevel - debug level
    void debug(int debugLevel);

    /* Getters/Setters */

    CIdxEntry* getFirstEntryPtr();

    CIdxEntry* getLastEntryPtr();

    long getNumberOfEntries();

    long getKeyType();

    long getInsertOrder();

    long getCurrEntryId();

};

/* DESCRIPTOR POINTER DEFINITION 
*/
typedef CIdxDescriptor* CIdxDescriptorPtr_t;

#endif
