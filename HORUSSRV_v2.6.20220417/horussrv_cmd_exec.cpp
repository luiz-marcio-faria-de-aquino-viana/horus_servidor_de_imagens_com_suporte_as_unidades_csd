/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_exec.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdExec::CCmdExec(CCmdRequest* pRequest, CCmdResponse* pResponse)
{
    m_pRequest = pRequest;
    m_pResponse = pResponse;
}

CCmdExec::~CCmdExec()
{
    /* nothing todo! */
}

/* Exec Commands */

int CCmdExec::doCmdConnect()
{
    int rscode = RSERR;

    CUsers* pUsers = gAppMain.getUsersPtr();

    users_t* resval = NULL;
    int rscode_tmp = pUsers->findItem(m_pRequest->getUsername(), &resval);
    if(rscode_tmp == RSOK) {
        if(strNCmpUtil(resval->passwd, m_pRequest->getPassword(), STRSZ) == 0) {
            long sessionId = getCurrentTimestamp();
            m_pResponse->doResponseSuccess(DEF_RESTYPE_SESSION_VAL, sessionId);
            rscode = RSOK;
        }
        else {
            m_pResponse->doResponseFail(
                DEF_RESCODE_FAIL_INVALID_AUTHENTICATION, 
                DEF_RESMSG_FAIL_INVALID_AUTHENTICATION);
            rscode = RSERR;
        }
    }
    return rscode;
}

int CCmdExec::doCmdListAllUsers()
{
    int rscode = RSERR;

    CUsers* pUsers = gAppMain.getUsersPtr();

    bigstr_t returnXml;
    strSetEmptyUtil(returnXml);

    users_t* arr = NULL;
    long arrsz = -1;

    int rscode_tmp = pUsers->findAll(&arr, &arrsz);

    printf("RETURN (N=%ld)\n\n", arrsz);

    users_t* p = arr;
    for(int i = 0; i < arrsz; i++) {
        pUsers->debugEntry(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "doCmdListAllUsers()", p);
        p++;
    }

    if(rscode_tmp == RSOK) {
        bigstr_t lsUserXml;
        strSetEmptyUtil(lsUserXml);

        users_t* p = arr;
        for(int i = 0; i < arrsz; i++) {
            bigstr_t userXml;
            strSetEmptyUtil(userXml);
            
            pUsers->toXml(p, userXml);
            printf("User XML: %s\n", userXml);

            strNCatUtil(lsUserXml, userXml, BIGSTRSZ);
            p++;
        }

        sprintf(returnXml, 
            DEF_XML_RESPONSE_USERS, 
            lsUserXml);
        m_pResponse->doResponseSuccess(DEF_RESTYPE_STRING_VAL, returnXml);
        rscode = RSOK;
    }
    else {
        m_pResponse->doResponseFail(
            DEF_RESCODE_FAIL_CANT_LIST_ALL_USERS, 
            DEF_RESMSG_FAIL_CANT_LIST_ALL_USERS);
        rscode = RSERR;
    }

    if(arr != NULL)
        free(arr);

    return rscode;
}

int CCmdExec::doCmdListAllTables()
{
    int rscode = RSERR;

    CTableMetadata* pTables = gAppMain.getTableMetadataPtr();

    bigstr_t returnXml;
    strSetEmptyUtil(returnXml);

    table_metadata_t* arr = NULL;
    long arrsz = -1;

    int rscode_tmp = pTables->findAll(&arr, &arrsz);

    printf("RETURN (N=%ld)\n\n", arrsz);

    table_metadata_t* p = arr;
    for(int i = 0; i < arrsz; i++) {
        pTables->debugEntry(DEBUG_LEVEL_01, __HORUSSRV_CMD_CMDTEST_H, "doCmdListAllTables()", p);
        p++;
    }

    if(rscode_tmp == RSOK) {
        bigstr_t lsTableXml;
        strSetEmptyUtil(lsTableXml);

        table_metadata_t* p = arr;
        for(int i = 0; i < arrsz; i++) {
            bigstr_t tableXml;
            strSetEmptyUtil(tableXml);
            
            pTables->toXml(p, tableXml);
            printf("Table XML: %s\n", tableXml);

            strNCatUtil(lsTableXml, tableXml, BIGSTRSZ);
            p++;
        }

        sprintf(
            returnXml, 
            DEF_XML_RESPONSE_TABLEMETADATAS, 
            lsTableXml);
        m_pResponse->doResponseSuccess(DEF_RESTYPE_STRING_VAL, returnXml);
        rscode = RSOK;
    }
    else {
        m_pResponse->doResponseFail(
            DEF_RESCODE_FAIL_CANT_LIST_ALL_TABLES, 
            DEF_RESMSG_FAIL_CANT_LIST_ALL_TABLES);
        rscode = RSERR;
    }

    if(arr != NULL)
        free(arr);

    return rscode;
}

/* Main Exec */

int CCmdExec::doExec()
{
    int rscode = RSERR;

    int action = m_pRequest->getAction();

    if(action == DEF_REQ_ACTION_CONNECT_I) {
        printf("EXEC: doCmdConnect()\n");
        rscode = doCmdConnect();
    }
    else if(action == DEF_REQ_ACTION_LISTALL_I) {
        printf("EXEC: doCmdListAll()\n");

        int objtype = m_pRequest->getObjtype();

        if(objtype == DEF_REQ_OBJTYPE_USERS_I) {
            rscode = doCmdListAllUsers();
        }
        else if(objtype == DEF_REQ_OBJTYPE_TABLES_I) {
            rscode = doCmdListAllTables();
        }
    }

    return rscode;
}

int CCmdExec::doExecTest()
{
    int rscode = RSERR;

    printf("EXEC_TEST: doCmdConnect()\n");
    rscode = doCmdConnect();
    if(rscode == RSERR) return RSERR;

    printf("EXEC_TEST: doCmdListAllUsers()\n");
    rscode = doCmdListAllUsers();
    if(rscode == RSERR) return RSERR;

    printf("EXEC_TEST: doCmdListAllTables()\n");
    rscode = doCmdListAllTables();
    if(rscode == RSERR) return RSERR;

    return rscode;
}

/* Getters/Setters */

CCmdRequest* CCmdExec::getRequestPtr()
{
    return m_pRequest;
}

CCmdResponse* CCmdExec::getResponsePtr()
{
    return m_pResponse;    
}
