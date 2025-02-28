/*
 * Copyright(C) 2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_parser.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_PARSER_H
#define __HORUSSRV_CMD_PARSER_H          "__HORUSSRV_CMD_PARSER_H"

class CCmdParser
{
private:
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

    long getActionFromString(char* str);
    long getObjtypeFromString(char* str);

public:

    CCmdParser();

    ~CCmdParser();

    /* Methodes */

    int parser(char* cmd);

    /* Getters/Setters */

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

/* NEW_TYPE: CCmdParser Pointer */

typedef CCmdParser* CCmdParserPtr_t;

#endif
