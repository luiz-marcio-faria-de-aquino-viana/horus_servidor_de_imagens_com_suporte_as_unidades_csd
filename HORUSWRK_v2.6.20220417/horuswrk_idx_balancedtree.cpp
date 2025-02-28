/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_all.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 09/02/2022
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CIdxBalancedTree::CIdxBalancedTree(long keyType, long insertOrder)
{
    this->init(keyType, insertOrder);
}

CIdxBalancedTree::~CIdxBalancedTree()
{
    this->terminate();
}

/* Methodes */

void CIdxBalancedTree::init(long keyType, long insertOrder)
{
    //TODO:
}

void CIdxBalancedTree::terminate()
{
    //TODO:
}

// Find Operations

CIdxEntry* CIdxBalancedTree::findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::findEntryByKeyDbl(double keyLng, CIdxEntry** entryPtr)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::findAll(CIdxEntry** arrEntryPtr)
{
    return NULL;
}

// Graphs Operations - SearchWide...

long CIdxBalancedTree::searchWideByKeyLng(long keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

long CIdxBalancedTree::searchWideByKeyDbl(double keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

long CIdxBalancedTree::searchWideByKeyStr(char* keyStr, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

// Graphs Operations - SearchDeep...

long CIdxBalancedTree::searchDeepByKeyLng(long keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

long CIdxBalancedTree::searchDeepByKeyDbl(double keyLng, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

long CIdxBalancedTree::searchDeepByKeyStr(char* keyStr, CIdxDescriptor** arrEntryPtr, long* srArrEntry)
{
    return -1;
}

// Insert Operations

CIdxEntry* CIdxBalancedTree::insertNewEntry(CIdxEntry* entryPtr)
{
    return NULL;
}

// Remove Operations

CIdxEntry* CIdxBalancedTree::removeEntryByKeyLng(long keyVal)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::removeEntryByKeyDbl(long keyVal)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::removeEntryByKeyStr(char* keyStr)
{
    return NULL;
}

CIdxEntry* CIdxBalancedTree::removeEntry(CIdxEntry* entryPtr)
{
    return NULL;
}

void CIdxBalancedTree::removeAll()
{
    // TODO:
}

// Balanced Operations

void CIdxBalancedTree::makeBalancedTree()
{
    //TODO:
}

/* Getters/Setters */

CIdxDescriptor* CIdxBalancedTree::getDescriptorPtr()
{
    return m_descriptorPtr;
}
