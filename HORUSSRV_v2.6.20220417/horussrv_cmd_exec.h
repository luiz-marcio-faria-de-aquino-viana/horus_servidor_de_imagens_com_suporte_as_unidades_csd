/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_exec.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_EXEC_H
#define __HORUSSRV_CMD_EXEC_H       "__HORUSSRV_CMD_EXEC_H"

class CCmdExec
{
private:
    CCmdRequest* m_pRequest;
    CCmdResponse* m_pResponse;

    //*** COMMANDS
    //
    int doCmdConnect();
    //
    int doCmdListAllUsers();
    int doCmdListAllTables();

public:
    CCmdExec(CCmdRequest* pRequest, CCmdResponse* pResponse);
    ~CCmdExec();

    /* Methodes */

    int doExec();

    int doExecTest();

    /* Getters/Setters */

    CCmdRequest* getRequestPtr();

    CCmdResponse* getResponsePtr();

};

/* NEW_TYPE: CCmdExec Pointer */

typedef CCmdExec* CCmdExecPtr_t;

#endif
