/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_descriptor.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CIdxDescriptor::CIdxDescriptor(long keyType, long insertOrder)
{
    this->init(keyType, insertOrder);
}

CIdxDescriptor::~CIdxDescriptor()
{
    this->terminate();
}

/* Methodes */

void CIdxDescriptor::init(long keyType, long insertOrder)
{
    this->m_firstEntryPtr = NULL;
    this->m_lastEntryPtr = NULL;
    this->m_numberOfEntries = 0;

    this->m_keyType = keyType;
    this->m_insertOrder = insertOrder;

    this->m_currEntryId = DEF_IDX_SEQ_INIT_ENTRYID;
}

void CIdxDescriptor::terminate()
{
    this->removeAll();
}

// Next Sequence "EntryId"

long CIdxDescriptor::nextEntryId()
{
    long currVal = this->m_currEntryId++;
    return currVal;
}

// Locate Insert Position

CIdxEntry* CIdxDescriptor::locateInsertPosition(CIdxEntry* entryPtr)
{
    CIdxEntry* p = m_firstEntryPtr;
    while(p != NULL) {
        if( entryPtr->compare(p) <= 0 )
            return p;
        p = p->getEntryNextPtr();
    }
    return NULL;
}

// Find Operations

CIdxEntry* CIdxDescriptor::findFirst(CIdxEntry** entryPtr)
{
    (*entryPtr) = this->m_firstEntryPtr;
    return (*entryPtr);
}

CIdxEntry* CIdxDescriptor::findLast(CIdxEntry** entryPtr)
{
    (*entryPtr) = this->m_lastEntryPtr;
    return (*entryPtr);
}

CIdxEntry* CIdxDescriptor::findEntryByKeyLng(long keyLng, CIdxEntry** entryPtr)
{
    bigstr_t errmsg;

    CIdxEntry* p = this->m_firstEntryPtr;
    while(p != NULL) {
        if(p->getEntryKeyLng() == keyLng) {
            sprintf(
                errmsg, 
                "C.301) COMPARE: NewEntry Key=%ld;OldEntry Key=%ld;Result=0;\n", 
                p->getEntryKeyLng(),
                keyLng);
            warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_DESCRIPTOR_H, "compare()", errmsg);

            (*entryPtr) = p;
            return (*entryPtr);
        }
        p = p->getEntryNextPtr();
    }
    return NULL;
}

CIdxEntry* CIdxDescriptor::findEntryByKeyDbl(double keyDbl, CIdxEntry** entryPtr)
{
    bigstr_t errmsg;

    double minVal = keyDbl - DEF_IDX_COMPENTRY_PREC; 
    double maxVal = keyDbl + DEF_IDX_COMPENTRY_PREC; 

    CIdxEntry* p = this->m_firstEntryPtr;
    while(p != NULL) {
        sprintf(
            errmsg, 
            "C.302.1) COMPARE: EntryId=%ld;NewEntry Key=%lf;OldEntry Key=%lf;MinVal=%lf;MaxVal=%lf;\n", 
            p->getEntryId(),
            p->getEntryKeyDbl(),
            keyDbl,
            minVal,
            maxVal);
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_DESCRIPTOR_H, "compare()", errmsg);

        if( (p->getEntryKeyDbl() >= minVal) && (p->getEntryKeyDbl() <= maxVal) ) {
            sprintf(
                errmsg, 
                "C.302.2) COMPARE: NewEntry Key=%lf;OldEntry Key=%lf;MinVal=%lf;MaxVal=%lf;Result=0;\n", 
                p->getEntryKeyDbl(),
                keyDbl,
                minVal,
                maxVal);
            warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_DESCRIPTOR_H, "compare()", errmsg);

            (*entryPtr) = p;
            return (*entryPtr);
        }
        p = p->getEntryNextPtr();            
    }
    return NULL;
}

CIdxEntry* CIdxDescriptor::findEntryByKeyStr(char* keyStr, CIdxEntry** entryPtr)
{
    bigstr_t errmsg;

    CIdxEntry* p = this->m_firstEntryPtr;
    str_t tmpStr;
    while(p != NULL) {
        p->getEntryKeyStr((char*) & tmpStr);
        if(strNCmpUtil(tmpStr, keyStr, STRSZ) == 0) {
            sprintf(
                errmsg, 
                "C.303) COMPARE: NewEntry Key=%s;OldEntry Key=%s;Result=0;\n", 
                tmpStr,
                keyStr);
            warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_DESCRIPTOR_H, "compare()", errmsg);

            (*entryPtr) = p;
            return (*entryPtr);
        }
        p = p->getEntryNextPtr();
    }
    return NULL;
}

long CIdxDescriptor::findAll(CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry) 
{
    (*szArrEntry) = this->m_numberOfEntries;
    (*arrEntryPtr) = (CIdxEntryPtr_t*)allocDataArray(sizeof(CIdxEntryPtr_t), (*szArrEntry));

    CIdxEntry* p_src = this->m_firstEntryPtr;    
    CIdxEntryPtr_t* p_dst = (*arrEntryPtr);
    while(p_src != NULL) {
        (*p_dst) = p_src;
        p_dst++;

        p_src = p_src->getEntryNextPtr();
    }
    return (*szArrEntry);
}

long CIdxDescriptor::findAll(long keyLng, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry)
{
    (*szArrEntry) = this->m_numberOfEntries;
    (*arrEntryPtr) = (CIdxEntryPtr_t*)allocDataArray(sizeof(CIdxEntryPtr_t), (*szArrEntry));

    CIdxEntry* p_src = this->m_firstEntryPtr;    
    CIdxEntryPtr_t* p_dst = (*arrEntryPtr);
    while(p_src != NULL) {
        if(p_src->getEntryKeyLng() == keyLng) {
            (*p_dst) = p_src;
            p_dst++;
        }
        p_src = p_src->getEntryNextPtr();
    }
    return (*szArrEntry);
}

long CIdxDescriptor::findAll(double keyDbl, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry)
{
    (*szArrEntry) = this->m_numberOfEntries;
    (*arrEntryPtr) = (CIdxEntryPtr_t*)allocDataArray(sizeof(CIdxEntryPtr_t), (*szArrEntry));

    CIdxEntry* p_src = this->m_firstEntryPtr;    
    CIdxEntryPtr_t* p_dst = (*arrEntryPtr);
    while(p_src != NULL) {
        if(p_src->getEntryKeyDbl() == keyDbl) {
            (*p_dst) = p_src;
            p_dst++;
        }
        p_src = p_src->getEntryNextPtr();
    }
    return (*szArrEntry);
}

long CIdxDescriptor::findAll(char* keyStr, CIdxEntryPtr_t** arrEntryPtr, long* szArrEntry)
{
    str_t tmpKeyStr;        

    (*szArrEntry) = this->m_numberOfEntries;
    (*arrEntryPtr) = (CIdxEntryPtr_t*)allocDataArray(sizeof(CIdxEntryPtr_t), (*szArrEntry));

    CIdxEntry* p_src = this->m_firstEntryPtr;    
    CIdxEntryPtr_t* p_dst = (*arrEntryPtr);
    while(p_src != NULL) {
        p_src->getEntryKeyStr(tmpKeyStr);
        if(strNCmpUtil(tmpKeyStr, tmpKeyStr, STRSZ) == 0) {
            (*p_dst) = p_src;
            p_dst++;
        }
        p_src = p_src->getEntryNextPtr();
    }
    return (*szArrEntry);
}

// Stack Operations

CIdxEntry* CIdxDescriptor::push(CIdxEntry* entryPtr)
{
    return this->insertFirst(entryPtr);
}

CIdxEntry* CIdxDescriptor::pop(CIdxEntry** entryPtr)
{
    return this->removeFirst(entryPtr);
}

// Fifo Operations

CIdxEntry* CIdxDescriptor::insertFirst(CIdxEntry* entryPtr)
{
    CIdxEntry* p_prev = NULL;
    CIdxEntry* p_next = NULL;
    
    if(this->m_firstEntryPtr == NULL) {
        this->m_firstEntryPtr = entryPtr;
        this->m_lastEntryPtr = entryPtr;
    }
    else {
        p_next = this->m_firstEntryPtr;

        (this->m_firstEntryPtr)->setEntryPrevPtr(entryPtr);
        this->m_firstEntryPtr = entryPtr;
    }    

    entryPtr->setEntryPrevPtr(p_prev);
    entryPtr->setEntryNextPtr(p_next);

    this->m_numberOfEntries += 1;

    return entryPtr;
}

CIdxEntry* CIdxDescriptor::insertLast(CIdxEntry* entryPtr)
{
    CIdxEntry* p_next = NULL;
    CIdxEntry* p_prev = NULL;
    
    if(this->m_lastEntryPtr == NULL) {
        this->m_lastEntryPtr = entryPtr;
        this->m_firstEntryPtr = entryPtr;
    }
    else {
        p_prev = this->m_lastEntryPtr;

        (this->m_lastEntryPtr)->setEntryNextPtr(entryPtr);
        this->m_lastEntryPtr = entryPtr;
    }    

    entryPtr->setEntryNextPtr(p_next);
    entryPtr->setEntryPrevPtr(p_prev);

    this->m_numberOfEntries += 1;

    return entryPtr;
}

CIdxEntry* CIdxDescriptor::removeFirst(CIdxEntry** entryPtr)
{
    (*entryPtr) = this->m_firstEntryPtr;
    this->unlinkEntry(*entryPtr);
    return (*entryPtr);
}

CIdxEntry* CIdxDescriptor::removeLast(CIdxEntry** entryPtr)
{
    (*entryPtr) = this->m_lastEntryPtr;
    this->unlinkEntry(*entryPtr);
    return (*entryPtr);
}

// Insert Operations

CIdxEntry* CIdxDescriptor::insertNewEntry(CIdxEntry* newEntryPtr)
{
    CIdxEntry* currEntryPtr = this->locateInsertPosition(newEntryPtr);
    if(currEntryPtr == NULL)
        this->insertLast(newEntryPtr);
    else
        this->linkEntryBefore(newEntryPtr, currEntryPtr);
    return newEntryPtr;
}

// Remove Operations

CIdxEntry* CIdxDescriptor::removeEntryByKeyLng(long keyLng)
{
    CIdxEntry* entryPtr = NULL;
    if(this->findEntryByKeyLng(keyLng, & entryPtr) != NULL) {
        this->unlinkEntry(entryPtr);
        return entryPtr;
    }
    return NULL;
}

CIdxEntry* CIdxDescriptor::removeEntryByKeyDbl(double keyDbl)
{
    CIdxEntry* entryPtr = NULL;
    if(this->findEntryByKeyDbl(keyDbl, & entryPtr) != NULL) {
        this->unlinkEntry(entryPtr);
        return entryPtr;
    }
    return NULL;
}

CIdxEntry* CIdxDescriptor::removeEntryByKeyStr(char* keyStr)
{
    CIdxEntry* entryPtr = NULL;
    if(this->findEntryByKeyStr(keyStr, & entryPtr) != NULL) {
        this->unlinkEntry(entryPtr);
        return entryPtr;
    }
    return NULL;
}

CIdxEntry* CIdxDescriptor::removeEntry(CIdxEntry* entryPtr)
{
    CIdxEntry* p = entryPtr;
    if(p != NULL)
        this->unlinkEntry(p);
    return p;
}

void CIdxDescriptor::removeAll()
{
    CIdxEntry* p = m_firstEntryPtr;
    while(p != NULL) {
        CIdxEntry* p_next = p->getEntryNextPtr();
        this->unlinkEntry(p);
        p = p_next;
    }
}

// Link Entry Operations

CIdxEntry* CIdxDescriptor::linkEntryAfter(CIdxEntry* newEntryPtr, CIdxEntry* currEntryPtr)
{
    CIdxEntry* p_prev = NULL;
    CIdxEntry* p_next = NULL;

    if(this->m_firstEntryPtr == NULL) {
        this->m_firstEntryPtr = newEntryPtr;
        this->m_lastEntryPtr = newEntryPtr;
    }
    else {

        if(currEntryPtr != NULL) {
            p_prev = currEntryPtr;
            p_next = currEntryPtr->getEntryNextPtr();

            if(p_next == NULL)
                this->m_lastEntryPtr = newEntryPtr;

            currEntryPtr->setEntryNextPtr(newEntryPtr);
        }
        else {
            p_prev = NULL;
            p_next = this->m_firstEntryPtr;

            (this->m_firstEntryPtr)->setEntryPrevPtr(newEntryPtr);

            this->m_firstEntryPtr = newEntryPtr;
        }
    }

    newEntryPtr->setEntryPrevPtr(p_prev);
    newEntryPtr->setEntryNextPtr(p_next);

    this->m_numberOfEntries += 1;

    return newEntryPtr;
}

CIdxEntry* CIdxDescriptor::linkEntryBefore(CIdxEntry* newEntryPtr, CIdxEntry* currEntryPtr)
{
    CIdxEntry* p_prev = NULL;
    CIdxEntry* p_next = NULL;

    if(this->m_lastEntryPtr == NULL) {
        this->m_firstEntryPtr = newEntryPtr;
        this->m_lastEntryPtr = newEntryPtr;
    }
    else {

        if(currEntryPtr != NULL) {
            p_next = currEntryPtr;
            p_prev = currEntryPtr->getEntryPrevPtr();

            if(p_prev == NULL)
                this->m_firstEntryPtr = newEntryPtr;

            if(p_prev != NULL)
                p_prev->setEntryNextPtr(newEntryPtr);

            currEntryPtr->setEntryPrevPtr(newEntryPtr);
        }
        else {
            p_next = NULL;
            p_prev = this->m_lastEntryPtr;

            (this->m_lastEntryPtr)->setEntryNextPtr(newEntryPtr);

            this->m_lastEntryPtr = newEntryPtr;
        }

    }

    newEntryPtr->setEntryPrevPtr(p_prev);
    newEntryPtr->setEntryNextPtr(p_next);

    this->m_numberOfEntries += 1;

    return newEntryPtr;
}

// Unlink Entry Operations

CIdxEntry* CIdxDescriptor::unlinkEntry(CIdxEntry* entryPtr)
{
    CIdxEntry* p_prev = entryPtr->getEntryPrevPtr();
    CIdxEntry* p_next = entryPtr->getEntryNextPtr();

    if(p_prev != NULL)    
        p_prev->setEntryNextPtr(p_next);
    else
        this->m_firstEntryPtr = p_next;

    if(p_next != NULL)
        p_next->setEntryPrevPtr(p_prev);
    else
        this->m_lastEntryPtr = p_prev;

    entryPtr->setEntryNextPtr(NULL);
    entryPtr->setEntryPrevPtr(NULL);

    this->m_numberOfEntries -= 1;

    return entryPtr;
}

/* Debug */

// debug(): show all entry data
// debugLevel - debug level
void CIdxDescriptor::debug(int debugLevel)
{
    if(debugLevel != DEBUG_LEVEL) return;

    CIdxEntry* p = m_firstEntryPtr;
    while(p != NULL) {
        p->debugEntry(debugLevel);
        p = p->getEntryNextPtr();
    }
}

/* Getters/Setters */

CIdxEntry* CIdxDescriptor::getFirstEntryPtr() {
    return m_firstEntryPtr;
}

CIdxEntry* CIdxDescriptor::getLastEntryPtr() {
    return m_lastEntryPtr;
}

long CIdxDescriptor::getNumberOfEntries() {
    return m_numberOfEntries;
}

long CIdxDescriptor::getKeyType() {
    return m_keyType;
}

long CIdxDescriptor::getInsertOrder() {
    return m_insertOrder;
}

long CIdxDescriptor::getCurrEntryId()
{
    return m_currEntryId;
}
