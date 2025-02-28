/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_dispatch.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 01/03/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdDispatch::CCmdDispatch(char* chname)
{
    bigstr_t errmsg;

    strNCpyUtil(m_chname, chname, STRSZ);
    m_reqnum = 0;

    sprintf(errmsg, "\nChannel Name: %s ", m_chname);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_DISPATCH_H, "CCmdDispatch::CCmdDispatch()", errmsg);
}

CCmdDispatch::~CCmdDispatch()
{
    /* nothing todo! */
}

/* Local Methodes */

int CCmdDispatch::serverConnect(char* username, char* passwd)
{
    bigstr_t cmd;
    sprintf(cmd, CMDSRV_CONNECT, username, passwd);
    int rscode = gCmdListener.sendStringMessageToListener((char*)cmd);
    return rscode;
}

int CCmdDispatch::serverTerminate()
{
    gCmdListener.stop();
    return RSOK;
}

int CCmdDispatch::listAllUsers(users_t** ret_datarows, long* ret_numrows, char* sessionId)
{
    bigstr_t cmd;
    sprintf(cmd, CMDSRV_LISTALL_USERS, sessionId);
    int rscode = gCmdListener.sendStringMessageToListener((char*)cmd);
    return rscode;
}

int CCmdDispatch::listAllTables(table_metadata_t** ret_datarows, long* ret_numrows, char* sessionId)
{
    bigstr_t cmd;
    sprintf(cmd, CMDSRV_LISTALL_TABLES, sessionId);
    int rscode = gCmdListener.sendStringMessageToListener((char*)cmd);
    return rscode;
}

/* Remote Unit Methodes */

int CCmdDispatch::serverTerminate(CCfgRemoteUnit* pRemoteUnit)
{
    bigstr_t cmd;
    sprintf(cmd, DEF_DEFAULT_SERVERTERMMSG);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//MKDIR
int CCmdDispatch::doActionTS1MkDir(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_MKDIR, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//UPLOAD
int CCmdDispatch::doActionTS1Upload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_UPLOAD, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//DOWNLOAD
int CCmdDispatch::doActionTS1Download(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_DOWNLOAD, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//DOWNLOAD_AND_PROCESS
int CCmdDispatch::doActionTS1DownloadAndProcess(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts, long mode)
{
    bigstr_t cmdAction;
    //sprintf(cmdAction, DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, mode);
    sprintf(cmdAction, DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS);

    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, cmdAction, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//CONVERT_MOD
int CCmdDispatch::doActionTS1Convert(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_CONVERT, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//REPROJ_MOD
int CCmdDispatch::doActionTS1Reproj(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_REPROJ, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

//SIMPL_MOD
int CCmdDispatch::doActionTS1Simpl(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts)
{
    bigstr_t cmd;
    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, DEF_REQ_ACTION_TS1_SIMPL, currpart, numparts);
    printf("CMD: %s\n", cmd);

    int rscode = gCmdListener.sendStringMessageToRemoteUnit(pRemoteUnit->getOid(), (char*)cmd);
    return rscode;
}

/* Getters/Setters */

char* CCmdDispatch::getChName()
{
    return m_chname;
}

int CCmdDispatch::getReqNum()
{
    return m_reqnum;
}
