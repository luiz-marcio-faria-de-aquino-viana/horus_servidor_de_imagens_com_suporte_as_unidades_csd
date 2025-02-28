/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_doublelinkedlist.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#include "horuswrk_base_all.h"

CIdxDoubleLinkedList::CIdxDoubleLinkedList(long keyType, long insertOrder)
{
    this->init(keyType, insertOrder);
}

CIdxDoubleLinkedList::~CIdxDoubleLinkedList()
{
    this->terminate();
}

/* Methodes */

void CIdxDoubleLinkedList::init(long keyType, long insertOrder)
{
    m_descriptorPtr = new CIdxDescriptor(keyType, insertOrder);
}

void CIdxDoubleLinkedList::terminate()
{
    delete(m_descriptorPtr);
}

// Find Operations

CIdxEntry* CIdxDoubleLinkedList::findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr)
{
    m_descriptorPtr->findEntryByKeyLng(keyLng, entryPtr);
    return(*entryPtr);    
}

CIdxEntry* CIdxDoubleLinkedList::findEntryByKeyDbl(double keyDbl, CIdxEntry** entryPtr)
{
    m_descriptorPtr->findEntryByKeyDbl(keyDbl, entryPtr);
    return(*entryPtr);    
}

CIdxEntry* CIdxDoubleLinkedList::findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr)
{
    m_descriptorPtr->findEntryByKeyStr(keyStr, entryPtr);
    return(*entryPtr);
}

long CIdxDoubleLinkedList::findAll(CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry)
{
    m_descriptorPtr->findAll(arrEntryPtr, szArrEntry);
    return(*szArrEntry);
}

long CIdxDoubleLinkedList::findAll(long oid, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry)
{
    m_descriptorPtr->findAll(arrEntryPtr, szArrEntry);
    return(*szArrEntry);
}

// Insert Operations

CIdxEntry* CIdxDoubleLinkedList::insertNewEntry(CIdxEntry* newEntryPtr)
{
    m_descriptorPtr->insertNewEntry(newEntryPtr);
    return(newEntryPtr);
}

// Remove Operations

CIdxEntry* CIdxDoubleLinkedList::removeEntryByKeyLng(long keyLng)
{
    CIdxEntry* entryPtr = m_descriptorPtr->removeEntryByKeyLng(keyLng);
    return(entryPtr);
}

CIdxEntry* CIdxDoubleLinkedList::removeEntryByKeyDbl(long keyDbl)
{
    CIdxEntry* entryPtr = m_descriptorPtr->removeEntryByKeyDbl(keyDbl);
    return(entryPtr);
}

CIdxEntry* CIdxDoubleLinkedList::removeEntryByKeyStr(char* keyStr)
{
    CIdxEntry* entryPtr = m_descriptorPtr->removeEntryByKeyStr(keyStr);
    return(entryPtr);
}

CIdxEntry* CIdxDoubleLinkedList::removeEntry(CIdxEntry* entryPtr)
{
    m_descriptorPtr->removeEntry(entryPtr);
    return(entryPtr);
}

void CIdxDoubleLinkedList::removeAll()
{
    m_descriptorPtr->removeAll();    
}

/* Getters/Setters */

CIdxDescriptor* CIdxDoubleLinkedList::getDescriptorPtr() {
    return m_descriptorPtr;
}
