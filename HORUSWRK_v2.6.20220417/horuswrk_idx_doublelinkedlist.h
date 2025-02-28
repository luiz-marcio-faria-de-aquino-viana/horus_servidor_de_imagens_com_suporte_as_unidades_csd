/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_doublelinkedlist.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_DOUBLELINKEDLIST_H
#define __HORUSWRK_IDX_DOUBLELINKEDLIST_H            "__HORUSWRK_IDX_DOUBLELINKEDLIST_H"

class CIdxDoubleLinkedList
{
private:
    CIdxDescriptor* m_descriptorPtr;

public:

    CIdxDoubleLinkedList(long keyType, long insertOrder);

    ~CIdxDoubleLinkedList();

    /* Methodes */

    void init(long keyType, long insertOrder);

    void terminate();

    // Find Operations

    CIdxEntry* findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyDbl(double keyDbl, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr);

    long findAll(CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    long findAll(long oid, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry);

    // Insert Operations

    CIdxEntry* insertNewEntry(CIdxEntry* newEntryPtr);

    // Remove Operations

    CIdxEntry* removeEntryByKeyLng(long keyLng);

    CIdxEntry* removeEntryByKeyDbl(long keyDbl);

    CIdxEntry* removeEntryByKeyStr(char* keyStr);

    CIdxEntry* removeEntry(CIdxEntry* entryPtr);

    void removeAll();

    /* Getters/Setters */

    CIdxDescriptor* getDescriptorPtr();

};

/* DOUBLE LINKED LIST POINTER DEFINITION 
*/
typedef CIdxDoubleLinkedList* CIdxDoubleLinkedListPtr_t;

#endif
