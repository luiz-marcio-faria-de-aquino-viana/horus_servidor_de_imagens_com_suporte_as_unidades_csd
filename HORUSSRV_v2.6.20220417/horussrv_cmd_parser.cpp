/*
 * Copyright(C) 2020-21 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_parser.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdParser::CCmdParser()
{
    m_action = DEF_REQ_ACTION_UNKNOW_I;
    m_objtype = DEF_REQ_OBJTYPE_UNKNOW_I;
    strSetEmptyUtil(m_username);
    strSetEmptyUtil(m_password);
    strSetEmptyUtil(m_session);
    m_oid = DEF_REQ_OID_NULL;
    strSetEmptyUtil(m_table_name);
    m_rowid = DEF_REQ_ROWID_NULL;
    strSetEmptyUtil(m_data);
    m_datasz = 0;
}

CCmdParser::~CCmdParser()
{
    /* nothing todo! */
}

long CCmdParser::getActionFromString(char* str)
{
    long ret_action = DEF_REQ_ACTION_UNKNOW_I;

    if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_CONNECT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_CONNECT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_LISTALL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_LISTALL_I;
    }

    return ret_action;
}

long CCmdParser::getObjtypeFromString(char* str)
{
    long ret_objtype = DEF_REQ_OBJTYPE_UNKNOW_I;

    if(strNCmpUtil(str, (char*)DEF_REQ_OBJTYPE_SESSION, STRSZ) == 0) {
        ret_objtype = DEF_REQ_OBJTYPE_SESSION_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_OBJTYPE_USERS, STRSZ) == 0) {
        ret_objtype = DEF_REQ_OBJTYPE_USERS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_OBJTYPE_TABLES, STRSZ) == 0) {
        ret_objtype = DEF_REQ_OBJTYPE_TABLES_I;
    }

    return ret_objtype;
}

int CCmdParser::parser(char* cmd)
{
    int result = RSERR;

    char* tk = strtok(cmd, "^");
    int tknum = 0;
    while(tk != NULL) {
        printf("CCmdParser::Token=%s\n", tk);            

        if(m_action == DEF_REQ_ACTION_UNKNOW_I) 
        {
            m_action = getActionFromString(tk);

            if(m_action == DEF_REQ_ACTION_UNKNOW_I)
                return RSERR;
        }
        else if(m_action == DEF_REQ_ACTION_CONNECT_I) 
        {
            //connect^[username]^[password]

            if(tknum == 1) {
                strNCpyUtil(m_username, tk, STRSZ);
            }
            else if(tknum == 2) {
                strNCpyUtil(m_password, tk, STRSZ);
                return RSOK;
            }
        }
        else if(m_action == DEF_REQ_ACTION_LISTALL_I) 
        {
            //listall^users^[session]
            //listall^tables^[session]"

            if(tknum == 1) {
                m_objtype = getObjtypeFromString(tk);

                if(m_objtype == DEF_REQ_OBJTYPE_UNKNOW_I)
                    return RSERR;
            }
            else if(tknum == 2) {
                strNCpyUtil(m_session, tk, STRSZ);
                return RSOK;
            }
        }

        tk = strtok(NULL, "^");
        tknum += 1;
    }

    return result;
}

long CCmdParser::getAction()
{
    return m_action;
}

long CCmdParser::getObjtype()
{
    return m_objtype;
}

char* CCmdParser::getUsername()
{
    return m_username;
}

char* CCmdParser::getPassword()
{
    return m_password;
}

char* CCmdParser::getSession()
{
    return m_session;
}

char* CCmdParser::getTableName()
{
    return m_table_name;
}

long CCmdParser::getOid()
{
    return m_oid;
}

long CCmdParser::getRowid()
{
    return m_rowid;
}

char* CCmdParser::getData()
{
    return m_data;
}

long CCmdParser::getDataSz()
{
    return m_datasz;
}
