/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_cmdtest.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/12/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdTest::CCmdTest()
{
    m_pDispatch = new CCmdDispatch((char*)"CCmdTest");
}

CCmdTest::~CCmdTest()
{
    //TODO:
}

// Main Local Tests
//

void CCmdTest::testConnect()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Test Command: serverConnect()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPTEST_H, "testConnect()", errmsg);

    int rscode = m_pDispatch->serverConnect((char*)USR_SYSTEM_USERNAME, (char*)USR_SYSTEM_PASSWD);
    if(rscode != RSOK) {
        sprintf(errmsg, "Connection failure. Check if the server is running, and verify the username and password.\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testConnect()", errmsg);
    }

    sprintf(errmsg, "I.2) Test Command: serverConnect() - OK!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testConnect()", errmsg);

    strNCpyUtil(m_session, (char*)"0123456789", STRSZ);
}

void CCmdTest::testUsers()
{
    testListAllUsers();
}

void CCmdTest::testTables()
{
    testListAllTables();
}

void CCmdTest::testTerminate()
{
    bigstr_t errmsg;

    sprintf(errmsg, "M.1) Test Command: serverTerminate()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPTEST_H, "testTerminate()", errmsg);

    int rscode = m_pDispatch->serverTerminate();
    if(rscode != RSOK) {
        sprintf(errmsg, "Send terminate message fail. Check if you can connect the server.\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testTerminate()", errmsg);
    }

    sprintf(errmsg, "M.2) Test Command: serverTerminate() - OK!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testTerminate()", errmsg);
}

// Local Test Actions
//
void CCmdTest::testListAllUsers()
{
    bigstr_t errmsg;

    CUsers* pUsers = gAppMain.getUsersPtr();

    users_t* arr = NULL;
    long arrsz = -1;

    sprintf(errmsg, "II.1) Test Command: listAllUsers()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPTEST_H, "testListAllUsers()", errmsg);

    int rscode = m_pDispatch->listAllUsers(&arr, &arrsz, m_session);
    if(rscode != RSOK) {
        sprintf(errmsg, "Connection failure. Check if the server is running, and verify the username and password.\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testListAllUsers()", errmsg);
    }

    sprintf(errmsg, "II.2) Test Command: listAllUsers() - OK!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testListAllUsers()", errmsg);

    users_t* p = arr;
    for(int i = 0; i < arrsz; i++) {
        pUsers->debugEntry(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testListAllUsers()", p);
        p++;
    }

    if(arr != NULL)
        free(arr);
}

void CCmdTest::testListAllTables()
{
    bigstr_t errmsg;

    CTableMetadata* pTables = gAppMain.getTableMetadataPtr();

    table_metadata_t* arr = NULL;
    long arrsz = -1;

    sprintf(errmsg, "II.1) Metadata's Table\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testListAllTables()", errmsg);

    int rscode = m_pDispatch->listAllTables(&arr, &arrsz, m_session);
    if(rscode != RSOK) {
        sprintf(errmsg, "List all tables failure.\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testListAllTables()", errmsg);
    }

    table_metadata_t* p = arr;
    for(int i = 0; i < arrsz; i++) {
        pTables->debugEntry(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testListAllTables()", p);
        p++;
    }

    sprintf(errmsg, "II.2) Test Command: testListAllTables() - OK!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testListAllTables()", errmsg);
}

// Main Remote Unit Tests
//
void CCmdTest::testMkDir(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 MkDir\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testMkDir()", errmsg);

    int rscode = m_pDispatch->doActionTS1MkDir(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 MkDir: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testMkDir()", errmsg);
    }
    else {
        sprintf(errmsg, "I.1.1) Test TS-1 MkDir: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testMkDir()", errmsg);
    }

}

void CCmdTest::testUpload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Image Upload\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testUpload()", errmsg);

    int rscode = m_pDispatch->doActionTS1Upload(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Upload: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testUpload()", errmsg);
    }
    else {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Upload: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testUpload()", errmsg);
    }

}

void CCmdTest::testDownload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Image Download\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testDownload()", errmsg);

    int rscode = m_pDispatch->doActionTS1Download(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Download: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testDownload()", errmsg);
    }
    else {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Download: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testDownload()", errmsg);
    }

}

void CCmdTest::testDownloadAndProcess(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts, long mode)
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Image Download and Process\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testDownloadAndProcess()", errmsg);

    int rscode = m_pDispatch->doActionTS1DownloadAndProcess(pRemoteUnit, currpart, numparts, mode);
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Download and Process: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testDownloadAndProcess()", errmsg);
    }
    else {
        sprintf(errmsg, "I.1.1) Test TS-1 Image Download and Process: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testDownloadAndProcess()", errmsg);
    }

}

void CCmdTest::testConvert(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Convert\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testConvert()", errmsg);

    int rscode = m_pDispatch->doActionTS1Convert(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Convert: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testConvert()", errmsg);
    }
    else {
        sprintf(errmsg, "I.1.1) Test TS-1 Convert: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testConvert()", errmsg);
    }

}

void CCmdTest::testReproj(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "II.1) Run Test TS-1 Reproj\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testReproj()", errmsg);

    int rscode = m_pDispatch->doActionTS1Reproj(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "II.1.1) Test TS-1 Reproj: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testReproj()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 Reproj: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testReproj()", errmsg);
    }

}

void CCmdTest::testSimpl(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t errmsg;

    sprintf(errmsg, "III.1) Run Test TS-1 Simpl\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testSimpl()", errmsg);

    int rscode = m_pDispatch->doActionTS1Simpl(pRemoteUnit, currpart, numparts);
    if(rscode != RSOK) {
        sprintf(errmsg, "III.1.1) Test TS-1 Simpl: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testSimpl()", errmsg);
    }
    else {
        sprintf(errmsg, "III.1.1) Test TS-1 Simpl: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testSimpl()", errmsg);
    }

}

void CCmdTest::testTerminateRemoteUnit(CCfgRemoteUnit* pRemoteUnit)
{
    bigstr_t errmsg;

    sprintf(errmsg, "IV.1) Send Terminate Signal to Remote Unit...\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testTerminateRemoteUnit()", errmsg);

    int rscode = m_pDispatch->serverTerminate(pRemoteUnit);
    if(rscode != RSOK) {
        sprintf(errmsg, "IV.1.1) Terminate Remote Unit: FAIL!\n");
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "testTerminateRemoteUnit()", errmsg);
    }
    else {
        sprintf(errmsg, "IV.1.1) Terminate Remote Unit: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "testTerminateRemoteUnit()", errmsg);
    }
}

/* Methodes */

void CCmdTest::test()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    testConnect();
    sleep(DEBUG_MODE_SLEEPTIME);

    testUsers();
    sleep(DEBUG_MODE_SLEEPTIME);

    testTables();
    sleep(DEBUG_MODE_SLEEPTIME);

    //testTerminate();
    //sleep(DEBUG_MODE_SLEEPTIME);
}

void CCmdTest::benchmark()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    long currNumRemoteUnits = pConfig->getCurrNumRemoteUnits();

    long numparts = 0;
    for(long i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0)
            numparts += 1;
    }

    showMessage("BENCHMARK: Test Image Convertion GeoTIFF to JPEG", DBTRUE);

    long currpart = 0;
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testConvert(pRemoteUnit, currpart, numparts);
            currpart += 1;
        }
    }
    waitMessage(numparts);

    showMessage("BENCHMARK: Test Image Reprojection UTM to LL84", DBTRUE);

    currpart = 0;
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testReproj(pRemoteUnit, currpart, numparts);
            currpart += 1;
        }
    }
    waitMessage(numparts);

    showMessage("BENCHMARK: Test Image Simplification to 1/4 of the Original Size", DBTRUE);

    currpart = 0;
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testSimpl(pRemoteUnit, currpart, numparts);
            currpart += 1;
        }
    }
    waitMessage(numparts);

    showMessage("BENCHMARK: Terminate!", DBTRUE);

    sleep(DEBUG_MODE_SLEEPTIME);
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testTerminateRemoteUnit(pRemoteUnit);
        }
    }
}

void CCmdTest::remoteBenchmark1()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    long currNumRemoteUnits = pConfig->getCurrNumRemoteUnits();

    long currpart = 0;

    bigstr_t strmsg;

    long numparts = 0;
    for(long i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0)
            numparts += 1;
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP1_IMAGEMKDIR) == DEF_REMOTEBENCHMARK1_STEP1_IMAGEMKDIR) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test MkDir");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testMkDir(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP2_IMAGEUPLOAD) == DEF_REMOTEBENCHMARK1_STEP2_IMAGEUPLOAD) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test Image Upload");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testUpload(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP3_IMAGEDOWNLOAD) == DEF_REMOTEBENCHMARK1_STEP3_IMAGEDOWNLOAD) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test Image Download");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testDownload(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP4_IMAGECONVERTION) == DEF_REMOTEBENCHMARK1_STEP4_IMAGECONVERTION) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test Image Convertion GeoTIFF to JPEG");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testConvert(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP5_IMAGEREPROJECTION) == DEF_REMOTEBENCHMARK1_STEP5_IMAGEREPROJECTION) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test Image Reprojection UTM to LL84");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testReproj(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK1_EXECUTION_STEPS & DEF_REMOTEBENCHMARK1_STEP6_IMAGERESIMPLIFICATION) == DEF_REMOTEBENCHMARK1_STEP6_IMAGERESIMPLIFICATION) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Test Image Simplification to 1/4 of the Original Size");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testSimpl(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    sprintf(strmsg, "REMOTE BENCHMARK (TYPE 1): Terminate!");
    showMessage(strmsg, DBTRUE);

    sleep(DEBUG_MODE_SLEEPTIME);
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testTerminateRemoteUnit(pRemoteUnit);
        }
    }
}

void CCmdTest::remoteBenchmark2()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    long currNumRemoteUnits = pConfig->getCurrNumRemoteUnits();

    long currpart = 0;

    bigstr_t strmsg;

    long numparts = 0;
    for(long i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0)
            numparts += 1;
    }

    if((DEF_REMOTEBENCHMARK2_EXECUTION_STEPS & DEF_REMOTEBENCHMARK2_STEP1_IMAGEMKDIR) == DEF_REMOTEBENCHMARK2_STEP1_IMAGEMKDIR) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 2): Test MkDir");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testMkDir(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK2_EXECUTION_STEPS & DEF_REMOTEBENCHMARK2_STEP2_IMAGEUPLOAD) == DEF_REMOTEBENCHMARK2_STEP2_IMAGEUPLOAD) {
        sprintf(strmsg, "REMOTE BENCHMARK (TYPE 2): Test Image Upload");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testUpload(pRemoteUnit, currpart, numparts);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    if((DEF_REMOTEBENCHMARK2_EXECUTION_STEPS & DEF_REMOTEBENCHMARK2_STEP3_IMAGEDOWNLOADANDPROCESS) == DEF_REMOTEBENCHMARK2_STEP3_IMAGEDOWNLOADANDPROCESS) {
        sprintf(
            strmsg,
            "%s\n\t%s\n\t%s\n\t%s\n\t%s",
            "REMOTE BENCHMARK (TYPE 2): Test Image Download and Process (one image per time)",
            "Step 1: Image Download",
            "Step 2: Convertion GeoTIFF to JPEG",
            "Step 3: Reprojection UTM to LL84",
            "Step 4: Simplification to 1/4 of the Original Size");
        showMessage(strmsg, DBTRUE);

        currpart = 0;
        for(int i = 0; i < currNumRemoteUnits; i++)
        {
            CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
            if(pRemoteUnit->getEnabled() != 0) {
                testDownloadAndProcess(pRemoteUnit, currpart, numparts, (long)DEF_REMOTEBENCHMARK2_EXECUTION_STEPS);
                currpart += 1;
            }
        }
        waitMessage(numparts);
    }

    sprintf(strmsg, "REMOTE BENCHMARK (TYPE 2): Terminate!");
    showMessage(strmsg, DBTRUE);

    sleep(DEBUG_MODE_SLEEPTIME);
    for(int i = 0; i < currNumRemoteUnits; i++)
    {
        CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitAtPtr(i);
        if(pRemoteUnit->getEnabled() != 0) {
            testTerminateRemoteUnit(pRemoteUnit);
        }
    }
}

/* Test Barrier */

void CCmdTest::waitMessage(int numparts)
{
    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgHostServer* pHostServer = (CCfgHostServer*)pConfig->getHostServerPtr();

    struct sockaddr_in saddr;

    memSetNullUtil((byte*) &saddr, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons( pHostServer->getInPort() );
    saddr.sin_addr.s_addr = htonl( INADDR_ANY );

    bigstr_t errmsg;
    sprintf(errmsg, "\nCCmdTest::Setting Barrier Listener at: %ld", pHostServer->getInPort());
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", errmsg);

	int serverHnd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(serverHnd == -1) 
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "cmd_listener_run()", ERR_CANTCREATESOCKET);

    int sockreuse = 1;
    if(setsockopt(serverHnd, SOL_SOCKET, SO_REUSEADDR, &sockreuse, sizeof(int)) == -1)
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "cmd_listener_run()", ERR_CANTSETSOCKETOPT);

    if(bind(serverHnd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
        errMsg(__HORUSSRV_CMD_CMDTEST_H, "cmd_listener_run()", ERR_CANTBINDSOCKET);

    printf("\n\n=> Waiting for Remote Units...\n");

    int currpart = 0;
    while(currpart < numparts)
    {
        socklen_t caddr_len = sizeof(sockaddr);
        struct sockaddr caddr;
        int in_len = -1;
        buf_t in_buf;

        memSetNullUtil((byte*)&caddr, caddr_len);
        memSetNullUtil(in_buf, BUFSZ);

        in_len = recvfrom(
            serverHnd, 
            in_buf, 
            BUFSZ, 
            0, 
            (struct sockaddr *) &caddr, 
            &caddr_len);

        if(in_len != -1) 
        {
            printf("Message #%d: %s\n", currpart, in_buf);

            //TODO:

            currpart++;
        }
    }

    printf("\n\n=> Waiting for Remote Units... Completed!\n\n");
}
