/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_apptest.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 09/02/2022
 * revisoes: ...
 *
 */

#include "horuswrk_base_all.h"

CIdxAppTest::CIdxAppTest()
{
    this->init();
}

CIdxAppTest::~CIdxAppTest()
{
    this->terminate();
}

/* Methodes */

void CIdxAppTest::init()
{
    // Init Sample Data

    init_arrIdxSampleData();

    // Crescent Order
    
    m_lngCrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_CRESCENT);
    
    m_dblCrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYDBL, DEF_IDX_KEYORDER_CRESCENT);
    
    m_strCrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYSTR, DEF_IDX_KEYORDER_CRESCENT);
    
    // Decrescent Order
    
    m_lngDecrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_DECRESCENT);
    
    m_dblDecrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYDBL, DEF_IDX_KEYORDER_DECRESCENT);
    
    m_strDecrescDescrPtr = new CIdxDescriptor(DEF_IDX_KEYSTR, DEF_IDX_KEYORDER_DECRESCENT);

    /* Fifo Test Operations 
    */
    
    m_lngFifoPtr = new CIdxFifo(DEF_IDX_KEYLNG);
    
    m_dblFifoPtr = new CIdxFifo(DEF_IDX_KEYDBL);

    m_strFifoPtr = new CIdxFifo(DEF_IDX_KEYSTR);

    /* Stack Test Operations 
    */
    
    m_lngStackPtr = new CIdxStack(DEF_IDX_KEYLNG);
    
    m_dblStackPtr = new CIdxStack(DEF_IDX_KEYDBL);

    m_strStackPtr = new CIdxStack(DEF_IDX_KEYSTR);

    /* Double-Linked List Test Operations 
    */

    // Crescent Order
    
    m_lngCrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_CRESCENT);
    
    m_dblCrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYDBL, DEF_IDX_KEYORDER_CRESCENT);
    
    m_strCrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYSTR, DEF_IDX_KEYORDER_CRESCENT);
    
    // Decrescent Order
    
    m_lngDecrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYLNG, DEF_IDX_KEYORDER_DECRESCENT);
    
    m_dblDecrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYDBL, DEF_IDX_KEYORDER_DECRESCENT);
    
    m_strDecrescDblLinkedListPtr = new CIdxDoubleLinkedList(DEF_IDX_KEYSTR, DEF_IDX_KEYORDER_DECRESCENT);

}

void CIdxAppTest::terminate()
{
    /* Descriptor Test Operations 
    */
    
    // Crescent Order
    
    delete(m_lngCrescDescrPtr);
    
    delete(m_dblCrescDescrPtr);
    
    delete(m_strCrescDescrPtr);
    
    // Decrescent Order
    
    delete(m_lngDecrescDescrPtr);
    
    delete(m_dblDecrescDescrPtr);
    
    delete(m_strDecrescDescrPtr);

    /* Fifo Test Operations 
    */
    
    delete(m_lngFifoPtr);
    
    delete(m_dblFifoPtr);

    delete(m_strFifoPtr);

    /* Stack Test Operations 
    */
    
    delete(m_lngStackPtr);
    
    delete(m_dblStackPtr);

    delete(m_strStackPtr);

    /* Double-Linked List Test Operations 
    */

    // Crescent Order
    
    delete(m_lngCrescDblLinkedListPtr);
    
    delete(m_dblCrescDblLinkedListPtr);
    
    delete(m_strCrescDblLinkedListPtr);
    
    // Decrescent Order
    
    delete(m_lngDecrescDblLinkedListPtr);
    
    delete(m_dblDecrescDblLinkedListPtr);
    
    delete(m_strDecrescDblLinkedListPtr);

    // Terminate Sample Data

    term_arrIdxSampleData();

}

void CIdxAppTest::execute()
{
    str_t strTestTitle;

    // Data Entry

    showDataEntry();

    /* Descriptor Test Operations 
    */
    
    // Crescent Order
    
    sprintf(strTestTitle, "Execute Descriptor Test: KeyLng, Crescent");
    executeTestKeyLng(strTestTitle, m_lngCrescDescrPtr);
    
    sprintf(strTestTitle, "Execute Descriptor Test: KeyDbl, Crescent");
    executeTestKeyDbl(strTestTitle, m_dblCrescDescrPtr);
    
    sprintf(strTestTitle, "Execute Descriptor Test: KeyStr, Crescent");
    executeTestKeyStr(strTestTitle, m_strCrescDescrPtr);

    // Decrescent Order

    sprintf(strTestTitle, "Execute Descriptor Test: KeyLng, Decrescent");
    executeTestKeyLng(strTestTitle, m_lngDecrescDescrPtr);
    
    sprintf(strTestTitle, "Execute Descriptor Test: KeyDbl, Decrescent");
    executeTestKeyDbl(strTestTitle, m_dblDecrescDescrPtr);
    
    sprintf(strTestTitle, "Execute Descriptor Test: KeyStr, Decrescent");
    executeTestKeyStr(strTestTitle, m_strDecrescDescrPtr);

    /* Fifo Test Operations 
    */

    sprintf(strTestTitle, "Execute FIFO Test: KeyLng");
    executeFifoTestKeyLng(strTestTitle, m_lngFifoPtr);
    
    sprintf(strTestTitle, "Execute FIFO Test: KeyDbl");
    executeFifoTestKeyDbl(strTestTitle, m_dblFifoPtr);
    
    sprintf(strTestTitle, "Execute FIFO Test: KeyStr");
    executeFifoTestKeyStr(strTestTitle, m_strFifoPtr);    

    /* Stack Test Operations 
    */

    sprintf(strTestTitle, "Execute STACK Test: KeyLng");
    executeStackTestKeyLng(strTestTitle, m_lngStackPtr);
    
    sprintf(strTestTitle, "Execute STACK Test: KeyDbl");
    executeStackTestKeyDbl(strTestTitle, m_dblStackPtr);
    
    sprintf(strTestTitle, "Execute STACK Test: KeyStr");
    executeStackTestKeyStr(strTestTitle, m_strStackPtr);    

    /* Double-Linked List Test Operations 
    */

    // Crescent Order
    
    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyLng");
    executeDblLinkedListTestKeyLng(strTestTitle, m_lngCrescDblLinkedListPtr);

    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyDbl");
    executeDblLinkedListTestKeyDbl(strTestTitle, m_dblCrescDblLinkedListPtr);

    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyStr");
    executeDblLinkedListTestKeyStr(strTestTitle, m_strCrescDblLinkedListPtr);
    
    // Decrescent Order

    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyLng");
    executeDblLinkedListTestKeyLng(strTestTitle, m_lngDecrescDblLinkedListPtr);

    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyDbl");
    executeDblLinkedListTestKeyDbl(strTestTitle, m_dblDecrescDblLinkedListPtr);

    sprintf(strTestTitle, "Execute Double-Linked List Test: KeyStr");
    executeDblLinkedListTestKeyStr(strTestTitle, m_strDecrescDblLinkedListPtr);

}

/* Show Data Entry
*/

void CIdxAppTest::showDataEntry()
{
    bigstr_t errmsg;

    // Data Entry

    sprintf(errmsg, "A.101) List Sample Data\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "showDataEntry()", errmsg);

    debug_arrIdxSampleData(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "showDataEntry()");

}

/* Descriptor Test Operations 
*/

void CIdxAppTest::executeTestKeyLng(char* strTestTitle, CIdxDescriptor* m_descrPtr)
{
    bigstr_t errmsg;

    long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "A.201) Index Test: Insert First - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    long sKeyLng = DEF_IDX_NULLKEY_LNG;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();
        if(sKeyLng == DEF_IDX_NULLKEY_LNG)
            sKeyLng = keyLng;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyLng, entryObjPtr);
        m_descrPtr->insertFirst(newEntryPtr);
    }

    sprintf(errmsg, "A.202) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "A.203) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.204) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.205) Find Entry By Key (KEY=%ld)\n", sKeyLng);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->findEntryByKeyLng(sKeyLng, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.206) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->removeAll();

    // Insert Last
    //
    sprintf(errmsg, "A.301) Index Test: Insert Last - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    sKeyLng = DEF_IDX_NULLKEY_LNG;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();
        if(sKeyLng == DEF_IDX_NULLKEY_LNG)
            sKeyLng = keyLng;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyLng, entryObjPtr);
        m_descrPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "A.302) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "A.303) Find First\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "findFirst()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.304) Find Last\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "findLast()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.305) Find Entry By Key (KEY=%ld)\n", sKeyLng);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->findEntryByKeyLng(sKeyLng, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.306) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->removeAll();

    // Insert Ordered
    //
    sprintf(errmsg, "A.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    sKeyLng = DEF_IDX_NULLKEY_LNG;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();
        if(sKeyLng == DEF_IDX_NULLKEY_LNG)
            sKeyLng = keyLng;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyLng, entryObjPtr);
        m_descrPtr->insertNewEntry(newEntryPtr);

        if(DEBUG_LEVEL == DEBUG_LEVEL_13) {
            sprintf(errmsg, "\n\nA.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

            newEntryPtr->debugEntry(DEBUG_LEVEL_13);

            sprintf(errmsg, "\n\nA.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

            m_descrPtr->debug(DEBUG_LEVEL_13);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "A.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "A.404) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.405) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.406) Find Entry By Key (KEY=%ld)\n", sKeyLng);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->findEntryByKeyLng(sKeyLng, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "A.407) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyLng()", errmsg);

    m_descrPtr->removeAll();

}

void CIdxAppTest::executeTestKeyDbl(char* strTestTitle, CIdxDescriptor* m_descrPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "B.201) Index Test: Insert First - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    double sKeyDbl = DEF_IDX_NULLKEY_DBL;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();
        if(sKeyDbl == DEF_IDX_NULLKEY_DBL)
            sKeyDbl = keyDbl;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyDbl, entryObjPtr);
        m_descrPtr->insertFirst(newEntryPtr);
    }

    sprintf(errmsg, "B.202) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "B.203) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.204) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.205) Find Entry By Key (KEY=%lf)\n", sKeyDbl);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findEntryByKeyDbl(sKeyDbl, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.206) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->removeAll();

    // Insert Last
    //
    sprintf(errmsg, "B.301) Index Test: Insert Last - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    sKeyDbl = DEF_IDX_NULLKEY_DBL;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();
        if(sKeyDbl == DEF_IDX_NULLKEY_DBL)
            sKeyDbl = keyDbl;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyDbl, entryObjPtr);
        m_descrPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "B.302) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "B.303) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.304) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.305) Find Entry By Key (KEY=%lf)\n", sKeyDbl);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findEntryByKeyDbl(sKeyDbl, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.306) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->removeAll();

    // Insert Ordered
    //
    sprintf(errmsg, "B.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    sKeyDbl = DEF_IDX_NULLKEY_DBL;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();
        if(sKeyDbl == DEF_IDX_NULLKEY_DBL)
            sKeyDbl = keyDbl;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyDbl, entryObjPtr);
        m_descrPtr->insertNewEntry(newEntryPtr);

        if(DEBUG_LEVEL == DEBUG_LEVEL_13) {
            sprintf(errmsg, "\n\nB.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

            newEntryPtr->debugEntry(DEBUG_LEVEL_13);

            sprintf(errmsg, "\n\nB.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

            m_descrPtr->debug(DEBUG_LEVEL_13);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "B.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "B.404) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.405) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.406) Find Entry By Key (KEY=%lf)\n", sKeyDbl);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->findEntryByKeyDbl(sKeyDbl, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "B.407) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyDbl()", errmsg);

    m_descrPtr->removeAll();

}

void CIdxAppTest::executeTestKeyStr(char* strTestTitle, CIdxDescriptor* m_descrPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    str_t keyStr;
    strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    str_t sKeyStr;

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "C.201) Index Test: Insert First - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    strNCpyUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ);
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        if(strNCmpUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ) == 0)
            strNCpyUtil(sKeyStr, keyStr, STRSZ);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyStr, entryObjPtr);
        m_descrPtr->insertFirst(newEntryPtr);
    }

    sprintf(errmsg, "C.202) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "C.203) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.204) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.205) Find Entry By Key (KEY=%s)\n", sKeyStr);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findEntryByKeyStr(sKeyStr, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.206) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->removeAll();

    // Insert Last
    //
    sprintf(errmsg, "C.301) Index Test: Insert Last - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    strNCpyUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ);
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        if(strNCmpUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ) == 0)
            strNCpyUtil(sKeyStr, keyStr, STRSZ);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyStr, entryObjPtr);
        m_descrPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "C.302) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "C.303) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.304) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.305) Find Entry By Key (KEY=%s)\n", sKeyStr);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findEntryByKeyStr(sKeyStr, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.306) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->removeAll();

    // Insert Ordered
    //
    sprintf(errmsg, "C.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    strNCpyUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ);
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        if(strNCmpUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ) == 0)
            strNCpyUtil(sKeyStr, keyStr, STRSZ);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_descrPtr, keyStr, entryObjPtr);
        m_descrPtr->insertNewEntry(newEntryPtr);

        if(DEBUG_LEVEL == DEBUG_LEVEL_13) {
            sprintf(errmsg, "\n\nC.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

            newEntryPtr->debugEntry(DEBUG_LEVEL_13);

            sprintf(errmsg, "\n\nC.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

            m_descrPtr->debug(DEBUG_LEVEL_13);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "C.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "C.404) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    ptrEntry = NULL;
    m_descrPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.405) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.406) Find Entry By Key (KEY=%s)\n", sKeyStr);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->findEntryByKeyStr(sKeyStr, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "C.407) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeTestKeyStr()", errmsg);

    m_descrPtr->removeAll();

}

/* Fifo Test Operations 
*/

void CIdxAppTest::executeFifoTestKeyLng(char* strTestTitle, CIdxFifo* m_fifoPtr)
{
    bigstr_t errmsg;

    long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "D.201) Index Test - FIFO - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_fifoPtr->getDescriptorPtr(), keyLng, entryObjPtr);
        m_fifoPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "D.202) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    (m_fifoPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "D.203) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "D.204) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "D.205) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "D.206) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    m_fifoPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "D.207) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    m_fifoPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "D.208) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyLng()", errmsg);

    m_fifoPtr->removeAll();

}

void CIdxAppTest::executeFifoTestKeyDbl(char* strTestTitle, CIdxFifo* m_fifoPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "E.301) Index Test - FIFO - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_fifoPtr->getDescriptorPtr(), keyDbl, entryObjPtr);
        m_fifoPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "E.302) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    (m_fifoPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "E.303) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "E.304) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "E.305) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "E.306) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    m_fifoPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "E.307) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    m_fifoPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "E.308) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyDbl()", errmsg);

    m_fifoPtr->removeAll();

}

void CIdxAppTest::executeFifoTestKeyStr(char* strTestTitle, CIdxFifo* m_fifoPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    str_t keyStr;
    strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "F.401) Index Test - FIFO - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_fifoPtr->getDescriptorPtr(), keyStr, entryObjPtr);
        m_fifoPtr->insertLast(newEntryPtr);
    }

    sprintf(errmsg, "F.402) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    (m_fifoPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "F.403) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "F.404) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "F.405) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    m_fifoPtr->removeFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "F.406) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    m_fifoPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "F.407) Find Last Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    m_fifoPtr->findLast(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "F.408) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeFifoTestKeyStr()", errmsg);

    m_fifoPtr->removeAll();

}

/* Stack Test Operations 
*/

void CIdxAppTest::executeStackTestKeyLng(char* strTestTitle, CIdxStack* m_stackPtr)
{
    bigstr_t errmsg;

    long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "G.201) Index Test - STACK - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_stackPtr->getDescriptorPtr(), keyLng, entryObjPtr);
        m_stackPtr->push(newEntryPtr);
    }

    sprintf(errmsg, "G.202) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    (m_stackPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "G.203) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "G.204) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "G.205) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "G.206) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    m_stackPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "G.207) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyLng()", errmsg);

    m_stackPtr->removeAll();

}

void CIdxAppTest::executeStackTestKeyDbl(char* strTestTitle, CIdxStack* m_stackPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "H.301) Index Test - STACK - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_stackPtr->getDescriptorPtr(), keyDbl, entryObjPtr);
        m_stackPtr->push(newEntryPtr);
    }

    sprintf(errmsg, "H.302) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    (m_stackPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "H.303) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "H.304) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "H.305) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "H.306) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    m_stackPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "H.307) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyDbl()", errmsg);

    m_stackPtr->removeAll();

}

void CIdxAppTest::executeStackTestKeyStr(char* strTestTitle, CIdxStack* m_stackPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    str_t keyStr;
    strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert First
    //
    sprintf(errmsg, "I.401) Index Test - STACK - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_stackPtr->getDescriptorPtr(), keyStr, entryObjPtr);
        m_stackPtr->push(newEntryPtr);
    }

    sprintf(errmsg, "I.402) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    (m_stackPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "I.403) Remove 1st Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    CIdxEntry* ptrEntry = NULL;
    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "I.404) Remove 2nd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "I.405) Remove 3rd Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    m_stackPtr->pop(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "I.406) Find First Entry\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    m_stackPtr->findFirst(& ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "I.407) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeStackTestKeyStr()", errmsg);

    m_stackPtr->removeAll();

}

/* Double-Linked List Test Operations 
*/

void CIdxAppTest::executeDblLinkedListTestKeyLng(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr)
{
    bigstr_t errmsg;

    long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert Ordered
    //
    sprintf(errmsg, "J.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

    long sKeyLng = DEF_IDX_NULLKEY_LNG;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyLng = generateRandomVal();
        if(sKeyLng == DEF_IDX_NULLKEY_LNG)
            sKeyLng = keyLng;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_listPtr->getDescriptorPtr(), keyLng, entryObjPtr);
        m_listPtr->insertNewEntry(newEntryPtr);

        int debugLevel = DEBUG_LEVEL_13;
        if(DEBUG_LEVEL == debugLevel) {
            sprintf(errmsg, "\n\nJ.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(debugLevel, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

            newEntryPtr->debugEntry(debugLevel);

            sprintf(errmsg, "\n\nJ.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(debugLevel, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

            (m_listPtr->getDescriptorPtr())->debug(debugLevel);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "J.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

    (m_listPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "J.404) Find Entry By Key (KEY=%ld)\n", sKeyLng);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

    CIdxEntry* ptrEntry = NULL;

    m_listPtr->findEntryByKeyLng(sKeyLng, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "J.405) Find All\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

    CIdxEntryPtr_t* arrEntryPtr = NULL;
    long szArrEntry = 0;

    m_listPtr->findAll(& arrEntryPtr, & szArrEntry);
    if(arrEntryPtr != NULL) {
        for(int i = 0; i < szArrEntry; i++) {
            ptrEntry = arrEntryPtr[i];
            ptrEntry->debugEntry(DEBUG_LEVEL_01);
        }
        freeDataArray(arrEntryPtr);
    }

    sprintf(errmsg, "J.406) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyLng()", errmsg);

    m_listPtr->removeAll();

}

void CIdxAppTest::executeDblLinkedListTestKeyDbl(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    double keyDbl = DEF_IDX_NULLKEY_DBL;

    //str_t keyStr;
    //strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert Ordered
    //
    sprintf(errmsg, "K.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

    double sKeyDbl = DEF_IDX_NULLKEY_DBL;
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        keyDbl = (double)generateRandomVal();
        if(sKeyDbl == DEF_IDX_NULLKEY_DBL)
            sKeyDbl = keyDbl;

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_listPtr->getDescriptorPtr(), keyDbl, entryObjPtr);
        m_listPtr->insertNewEntry(newEntryPtr);

        int debugLevel = DEBUG_LEVEL_13;
        if(DEBUG_LEVEL == debugLevel) {
            sprintf(errmsg, "\n\nK.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(debugLevel, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

            newEntryPtr->debugEntry(debugLevel);

            sprintf(errmsg, "\n\nK.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(debugLevel, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

            (m_listPtr->getDescriptorPtr())->debug(debugLevel);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "K.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

    (m_listPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "K.404) Find Entry By Key (KEY=%lf)\n", sKeyDbl);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

    CIdxEntry* ptrEntry = NULL;

    m_listPtr->findEntryByKeyDbl(sKeyDbl, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "K.405) Find All\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

    CIdxEntryPtr_t* arrEntryPtr = NULL;
    long szArrEntry = 0;

    m_listPtr->findAll(& arrEntryPtr, & szArrEntry);
    if(arrEntryPtr != NULL) {
        for(int i = 0; i < szArrEntry; i++) {
            ptrEntry = arrEntryPtr[i];
            ptrEntry->debugEntry(DEBUG_LEVEL_01);
        }
        freeDataArray(arrEntryPtr);
    }

    sprintf(errmsg, "K.406) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyDbl()", errmsg);

    m_listPtr->removeAll();

}

void CIdxAppTest::executeDblLinkedListTestKeyStr(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr)
{
    bigstr_t errmsg;

    //long keyLng = DEF_IDX_NULLKEY_LNG;
    //double keyDbl = DEF_IDX_NULLKEY_DBL;

    str_t keyStr;
    strNCpyUtil(keyStr, DEF_IDX_NULLKEY_STR, STRSZ);

    str_t sKeyStr;

    idx_sampledata_t* entryObjPtr = NULL;

    // Insert Operations

    // Insert Ordered
    //
    sprintf(errmsg, "L.401) Index Test: Insert Ordered - %s\n", strTestTitle);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

    strNCpyUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ);
    for(int i = 0; i < IDX_MAX_NUMBER_OF_IMAGES; i++)
    {
        long tempKey = generateRandomVal();
        sprintf(keyStr, "CDG:%09ld", tempKey);

        if(strNCmpUtil(sKeyStr, DEF_IDX_NULLKEY_STR, STRSZ) == 0)
            strNCpyUtil(sKeyStr, keyStr, STRSZ);

        entryObjPtr = & ARR_IDX_SAMPLEDATA[i];

        CIdxEntry* newEntryPtr = new CIdxEntry(m_listPtr->getDescriptorPtr(), keyStr, entryObjPtr);
        m_listPtr->insertNewEntry(newEntryPtr);

        if(DEBUG_LEVEL == DEBUG_LEVEL_13) {
            sprintf(errmsg, "\n\nL.402.1) Show New Entry (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

            newEntryPtr->debugEntry(DEBUG_LEVEL_13);

            sprintf(errmsg, "\n\nL.402.2) List All Entries (STEP=%d):\n", i);
            warnMsg(DEBUG_LEVEL_13, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

            (m_listPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_13);
            showMessageAndWaitForKey("\n");
        }
    }

    sprintf(errmsg, "L.403) List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

    (m_listPtr->getDescriptorPtr())->debug(DEBUG_LEVEL_01);

    sprintf(errmsg, "L.404) Find Entry By Key (KEY=%s)\n", sKeyStr);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

    CIdxEntry* ptrEntry = NULL;

    m_listPtr->findEntryByKeyStr(sKeyStr, & ptrEntry);
    if(ptrEntry != NULL) {
        ptrEntry->debugEntry(DEBUG_LEVEL_01);
    }

    sprintf(errmsg, "L.405) Find All\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

    CIdxEntryPtr_t* arrEntryPtr = NULL;
    long szArrEntry = 0;

    m_listPtr->findAll(& arrEntryPtr, & szArrEntry);
    if(arrEntryPtr != NULL) {
        for(int i = 0; i < szArrEntry; i++) {
            ptrEntry = arrEntryPtr[i];
            ptrEntry->debugEntry(DEBUG_LEVEL_01);
        }
        freeDataArray(arrEntryPtr);
    }

    sprintf(errmsg, "L.406) Delete All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_IDX_APPTEST_H, "executeDblLinkedListTestKeyStr()", errmsg);

    m_listPtr->removeAll();

}
