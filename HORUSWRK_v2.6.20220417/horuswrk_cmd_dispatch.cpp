/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_dispatch.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 23/12/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdDispatch::CCmdDispatch(char* chname)
{
    bigstr_t errmsg;

    strNCpyUtil(m_chname, chname, STRSZ);
    m_reqnum = 0;

    sprintf(errmsg, "\nChannel Name: %s ", m_chname);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CMD_DISPATCH_H, "CCmdDispatch::CCmdDispatch()", errmsg);
}

CCmdDispatch::~CCmdDispatch()
{
    /* nothing todo! */
}

/* Local Methodes */

int CCmdDispatch::serverTerminate()
{
    gCmdListener.stop();
    return RSOK;
}

/* Remote Unit Methodes 
*/
//MKDIR
int CCmdDispatch::doActionTS1MkDir()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_MKDIR, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
    return rscode;
}

//UPLOAD
int CCmdDispatch::doActionTS1Upload()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_UPLOAD, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
    return rscode;
}

//DOWNLOAD
int CCmdDispatch::doActionTS1Download()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_DOWNLOAD, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
    return rscode;
}

//CONVERT_MOD
int CCmdDispatch::doActionTS1Convert()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_CONVERT, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
    return rscode;
}

//REPROJ_MOD
int CCmdDispatch::doActionTS1Reproj()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_REPROJ, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
    return rscode;
}

//SIMPL_MOD
int CCmdDispatch::doActionTS1Simpl()
{
    int rscode = RSERR;
    bigstr_t cmd;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pCurrRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    sprintf(cmd, CMDWRK_REQUEST_COMMAND_1, pCurrRemoteUnit->getOid(), DEF_REQ_ACTION_TS1_SIMPL, 0L, 1L);
    printf("CMD: %s\n", cmd);

    rscode = gCmdListener.sendStringMessageToCurrRemoteUnit((char*)cmd);
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
