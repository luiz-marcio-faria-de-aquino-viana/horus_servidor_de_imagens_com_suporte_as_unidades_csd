/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_balancedtree.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_BALANCEDTREE_H
#define __HORUSWRK_IDX_BALANCEDTREE_H            "__HORUSWRK_IDX_BALANCEDTREE_H"

class CIdxBalancedTree
{
private:
    CIdxDescriptor* m_descriptorPtr;

public:

    CIdxBalancedTree(long keyType, long insertOrder);
    
    ~CIdxBalancedTree();

    /* Methodes */

    void init(long keyType, long insertOrder);

    void terminate();

    // Find Operations

    CIdxEntry* findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyDbl(double keyLng, CIdxEntry** entryPtr);

    CIdxEntry* findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr);

    CIdxEntry* findAll(CIdxEntry** arrEntryPtr);

    // Graphs Operations - SearchWide...

    long searchWideByKeyLng(long keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    long searchWideByKeyDbl(double keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    long searchWideByKeyStr(char* keyStr, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    // Graphs Operations - SearchDeep...

    long searchDeepByKeyLng(long keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    long searchDeepByKeyDbl(double keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    long searchDeepByKeyStr(char* keyStr, CIdxDescriptor** arrEntryPtr, long* srArrEntry);

    // Insert Operations

    CIdxEntry* insertNewEntry(CIdxEntry* entryPtr);

    // Remove Operations

    CIdxEntry* removeEntryByKeyLng(long keyVal);

    CIdxEntry* removeEntryByKeyDbl(long keyVal);

    CIdxEntry* removeEntryByKeyStr(char* keyStr);

    CIdxEntry* removeEntry(CIdxEntry* entryPtr);

    void removeAll();

    // Balanced Operations

    void makeBalancedTree();

    /* Getters/Setters */

    CIdxDescriptor* getDescriptorPtr();

};

/* BALANCED TREE POINTER DEFINITION 
*/
typedef CIdxBalancedTree* CIdxBalancedTreePtr_t;

#endif
