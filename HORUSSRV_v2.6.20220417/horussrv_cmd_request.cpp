/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_request.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 05/08/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdRequest::CCmdRequest(long reqnum, char* cmd)
{
    m_reqnum = reqnum;
    reset();

    CCmdParser cmdParser;
    int rscode = cmdParser.parser(cmd);
    if(rscode == RSOK) {
        m_action = cmdParser.getAction();
        m_objtype = cmdParser.getObjtype();
        strNCpyUtil(m_username, cmdParser.getUsername(), STRSZ);
        strNCpyUtil(m_password, cmdParser.getPassword(), STRSZ);
        strNCpyUtil(m_session, cmdParser.getSession(), STRSZ);
        m_oid = cmdParser.getOid();
        strNCpyUtil(m_table_name, cmdParser.getTableName(), STRSZ);
        m_rowid = cmdParser.getRowid();
        m_datasz = cmdParser.getDataSz();
        strNCpyUtil(m_data, cmdParser.getData(), m_datasz);
    }
}

CCmdRequest::~CCmdRequest()
{
    /* nothing todo! */
}

void CCmdRequest::reset()
{
    m_action = DEF_REQ_ACTION_UNKNOW_I;
    m_objtype = DEF_REQ_OBJTYPE_UNKNOW_I;
    strSetEmptyUtil(m_username);
    strSetEmptyUtil(m_password);
    strSetEmptyUtil(m_session);
    m_oid = DEF_REQ_OID_NULL;
    strSetEmptyUtil(m_table_name);
    m_rowid = DEF_REQ_ROWID_NULL;
    m_datasz = 0;
    strSetEmptyUtil(m_data);
}

void CCmdRequest::debug()
{
    printf("Request #%ld: action=%ld,objtype=%ld,username=%s,password=%s,session=%s,oid=%ld,table_name=%s,rowid=%ld,data=%s,datasz=%ld\n",
        m_reqnum,
        m_action,
        m_objtype,
        m_username,
        m_password,
        m_session,
        m_oid,
        m_table_name,
        m_rowid,
        ((m_data != NULL) ? m_data : (char*)"\0"),
        m_datasz);
}

long CCmdRequest::getReqNum()
{
    return m_reqnum;
}

long CCmdRequest::getAction()
{
    return m_action;
}

long CCmdRequest::getObjtype()
{
    return m_objtype;
}

char* CCmdRequest::getUsername()
{
    return m_username;
}

char* CCmdRequest::getPassword()
{
    return m_password;
}

char* CCmdRequest::getSession()
{
    return m_session;
}

long CCmdRequest::getOid()
{
    return m_oid;
}

char* CCmdRequest::getTableName()
{
    return m_table_name;
}

long CCmdRequest::getRowid()
{
    return m_rowid;
}

char* CCmdRequest::getData()
{
    return m_data;
}

long CCmdRequest::getDataSz()
{
    return m_datasz;
}
