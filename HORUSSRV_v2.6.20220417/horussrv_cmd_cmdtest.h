/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_cmdtest.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 22/12/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_CMDTEST_H
#define __HORUSSRV_CMD_CMDTEST_H                 "__HORUSSRV_CMD_CMDTEST_H"

class CCmdTest
{
private:
    CCmdDispatch* m_pDispatch;
    str_t m_session;

    // Main Local Tests
    //
    void testConnect();
    void testUsers();
    void testTables();
    void testTerminate();

    // Local Test Actions
    //
    void testListAllUsers();
    void testListAllTables();

    // Main Remote Unit Tests
    //
    void testMkDir(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //
    void testUpload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    void testDownload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //
    void testDownloadAndProcess(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts, long mode);
    //
    void testConvert(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    void testReproj(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    void testSimpl(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //
    void testTerminateRemoteUnit(CCfgRemoteUnit* pRemoteUnit);

public:
    CCmdTest();
    ~CCmdTest();

    /* Methodes */

    void test();

    void benchmark();

    void remoteBenchmark1();

    void remoteBenchmark2();

    /* Test Barrier */

    void waitMessage(int numparts);

};

/* NEW_TYPE: CCmdTest Pointer */

typedef CCmdTest* CCmdTestPtr_t;

#endif
