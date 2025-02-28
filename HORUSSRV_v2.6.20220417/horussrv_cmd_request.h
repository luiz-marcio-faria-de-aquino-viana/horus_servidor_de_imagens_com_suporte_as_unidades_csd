/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_request.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 01/07/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_REQUEST_H
#define __HORUSSRV_CMD_REQUEST_H       "__HORUSSRV_CMD_REQUEST_H"

class CCmdRequest
{
private:
    long m_reqnum;
    long m_action;
    long m_objtype;
    str_t m_username;
    str_t m_password;
    str_t m_session;
    long m_oid;
    str_t m_table_name;
    long m_rowid;
    bigstr_t m_data;
    long m_datasz;

public:
    CCmdRequest(long reqnum, char* cmd);

    ~CCmdRequest();

    /* Methodes */

    void reset();

    void debug();

    /* Getters/Setters */

    long getReqNum();
    long getAction();
    long getObjtype();
    char* getUsername();
    char* getPassword();
    char* getSession();
    long getOid();
    char* getTableName();
    long getRowid();
    char* getData();
    long getDataSz();

};

/* NEW_TYPE: CCmdRequest Pointer */

typedef CCmdRequest* CCmdRequestPtr_t;

#endif
