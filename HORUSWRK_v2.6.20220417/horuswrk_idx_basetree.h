/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_basetree.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_BASETREE_H
#define __HORUSWRK_IDX_BASETREE_H            "__HORUSWRK_IDX_BASETREE_H"

class CIdxBaseTree
{
private:
    CIdxTreeDescriptor* m_descriptorPtr;

public:

    CIdxBaseTree(long keyType, long insertOrder);

    ~CIdxBaseTree();

    /* Methodes */

    void init(long keyType, long insertOrder);

    void terminate();

    // Find Operations

    CIdxEntry* findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyDbl(double keyDbl, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr);

    long findAll(CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry, long treeSearchType);      // 1=Wide Search; 2=Deep Search

    // Insert Operations

    CIdxEntry* insertNewEntry(CIdxEntry* newEntryPtr);

    // Remove Operations

    CIdxEntry* removeEntryByKeyLng(long keyLng);

    CIdxEntry* removeEntryByKeyDbl(long keyDbl);

    CIdxEntry* removeEntryByKeyStr(char* keyStr);

    CIdxEntry* removeEntry(CIdxEntry* entryPtr);

    void removeAll();

    /* Getters/Setters */

    CIdxTreeDescriptor* getDescriptorPtr();

};

/* DOUBLE LINKED LIST POINTER DEFINITION 
*/
typedef CIdxBaseTree* CIdxBaseTreePtr_t;

#endif
