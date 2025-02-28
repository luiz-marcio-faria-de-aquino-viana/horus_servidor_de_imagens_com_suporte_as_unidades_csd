/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_cmdtest.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/12/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdTest::CCmdTest()
{
    //CCfgConfig* pConfig = gAppMain.getConfigPtr();

    //CCfgRemoteUnit* pRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    m_pDispatch = new CCmdDispatch((char*)"CCmdTest");
}

CCmdTest::~CCmdTest()
{
    //TODO:
}

// Main Tests
//
void CCmdTest::testMkDir()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 MkDir\n");
    warnMsg(DEBUG_LEVEL_09, __HORUSWRK_CMD_CMDTEST_H, "testMkDir()", errmsg);

    int rscode = m_pDispatch->doActionTS1MkDir();
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 MkDir: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testMkDir()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 MkDir: OK!\n");
        warnMsg(DEBUG_LEVEL_09, __HORUSWRK_CMD_CMDTEST_H, "testMkDir()", errmsg);
    }

}

void CCmdTest::testUpload()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Upload\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testUpload()", errmsg);

    int rscode = m_pDispatch->doActionTS1Upload();
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Upload: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testUpload()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 Upload: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testUpload()", errmsg);
    }

}

void CCmdTest::testDownload()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Download\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testDownload()", errmsg);

    int rscode = m_pDispatch->doActionTS1Download();
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Download: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testDownload()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 Download: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testDownload()", errmsg);
    }

}

void CCmdTest::testConvert()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I.1) Run Test TS-1 Convert\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testConvert()", errmsg);

    int rscode = m_pDispatch->doActionTS1Convert();
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Convert: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testConvert()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 Convert: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testConvert()", errmsg);
    }

}

void CCmdTest::testReproj()
{
    bigstr_t errmsg;

    sprintf(errmsg, "II.1) Run Test TS-1 Reproj\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testReproj()", errmsg);

    int rscode = m_pDispatch->doActionTS1Reproj();
    if(rscode != RSOK) {
        sprintf(errmsg, "I.1.1) Test TS-1 Reproj: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testReproj()", errmsg);
    }
    else {
        sprintf(errmsg, "II.1.1) Test TS-1 Reproj: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testReproj()", errmsg);
    }

}

void CCmdTest::testSimpl()
{
    bigstr_t errmsg;

    sprintf(errmsg, "III.1) Run Test TS-1 Simpl\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testSimpl()", errmsg);

    int rscode = m_pDispatch->doActionTS1Simpl();
    if(rscode != RSOK) {
        sprintf(errmsg, "II.1.1) Test TS-1 Simpl: FAIL!\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testSimpl()", errmsg);
    }
    else {
        sprintf(errmsg, "III.1.1) Test TS-1 Simpl: OK!\n");
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testSimpl()", errmsg);
    }

}

void CCmdTest::testTerminate()
{
    bigstr_t errmsg;

    sprintf(errmsg, "M.1) Test Command: serverTerminate()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_MOD_APPTEST_H, "testTerminate()", errmsg);

    int rscode = m_pDispatch->serverTerminate();
    if(rscode != RSOK) {
        sprintf(errmsg, "Send terminate message fail. Check if you can connect the server.\n");
        errMsg(__HORUSWRK_CMD_CMDTEST_H, "testTerminate()", errmsg);
    }

    sprintf(errmsg, "M.2) Test Command: serverTerminate() - OK!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_CMDTEST_H, "testTerminate()", errmsg);
}

/* Methodes */

void CCmdTest::execute()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    showMessage("START MKDIR TEST", DBTRUE);
    testMkDir();

    showMessage("START UPLOAD TEST", DBTRUE);
    testUpload();

    showMessage("START DOWNLOAD TEST", DBTRUE);
    testDownload();

    showMessage("START CONVERT TEST", DBTRUE);
    testConvert();

    showMessage("START REPROJ TEST", DBTRUE);
    testReproj();

    showMessage("START SIMPL TEST", DBTRUE);
    testSimpl();

    printf("TEST COMPLETED!");
}
