/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_apptest.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 09/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_APPTEST_H
#define __HORUSWRK_IDX_APPTEST_H         "__HORUSWRK_IDX_APPTEST_H"

class CIdxAppTest
{
private:
 
    /* Test Descriptor Operations
    */

    // Crescent Order
    
    CIdxDescriptor* m_lngCrescDescrPtr;
    
    CIdxDescriptor* m_dblCrescDescrPtr;
    
    CIdxDescriptor* m_strCrescDescrPtr;
    
    // Decrescent Order
    
    CIdxDescriptor* m_lngDecrescDescrPtr;
    
    CIdxDescriptor* m_dblDecrescDescrPtr;
    
    CIdxDescriptor* m_strDecrescDescrPtr;

    /* Fifo Test Operations 
    */
    
    CIdxFifo* m_lngFifoPtr;
    
    CIdxFifo* m_dblFifoPtr;
    
    CIdxFifo* m_strFifoPtr;

    /* Stack Test Operations 
    */
    
    CIdxStack* m_lngStackPtr;
    
    CIdxStack* m_dblStackPtr;
    
    CIdxStack* m_strStackPtr;

    /* Double-Linked List Test Operations 
    */
    
    // Crescent Order
    
    CIdxDoubleLinkedList* m_lngCrescDblLinkedListPtr;

    CIdxDoubleLinkedList* m_dblCrescDblLinkedListPtr;

    CIdxDoubleLinkedList* m_strCrescDblLinkedListPtr;
    
    // Decrescent Order
    
    CIdxDoubleLinkedList* m_lngDecrescDblLinkedListPtr;

    CIdxDoubleLinkedList* m_dblDecrescDblLinkedListPtr;

    CIdxDoubleLinkedList* m_strDecrescDblLinkedListPtr;

public:

    CIdxAppTest();

    ~CIdxAppTest();

    /* Methodes */

    void init();

    void terminate();

    void execute();

    /* Show Data Entry
    */

    void showDataEntry();

    /* Descriptor Test Operations 
    */

    void executeTestKeyLng(char* strTestTitle, CIdxDescriptor* m_descrPtr);

    void executeTestKeyDbl(char* strTestTitle, CIdxDescriptor* m_descrPtr);

    void executeTestKeyStr(char* strTestTitle, CIdxDescriptor* m_descrPtr);

    /* Fifo Test Operations 
    */

    void executeFifoTestKeyLng(char* strTestTitle, CIdxFifo* m_fifoPtr);

    void executeFifoTestKeyDbl(char* strTestTitle, CIdxFifo* m_fifoPtr);

    void executeFifoTestKeyStr(char* strTestTitle, CIdxFifo* m_fifoPtr);

    /* Stack Test Operations 
    */

    void executeStackTestKeyLng(char* strTestTitle, CIdxStack* m_stackPtr);

    void executeStackTestKeyDbl(char* strTestTitle, CIdxStack* m_stackPtr);

    void executeStackTestKeyStr(char* strTestTitle, CIdxStack* m_stackPtr);

    /* Double-Linked List Test Operations 
    */
    
    void executeDblLinkedListTestKeyLng(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr);
    
    void executeDblLinkedListTestKeyDbl(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr);
    
    void executeDblLinkedListTestKeyStr(char* strTestTitle, CIdxDoubleLinkedList* m_listPtr);

};

/* APPLICATION TEST POINTER DEFINITION 
*/
typedef CIdxAppTest* CIdxAppTestPtr_t;

#endif
