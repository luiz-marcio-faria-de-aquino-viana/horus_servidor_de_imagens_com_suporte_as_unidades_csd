/*
 * Copyright(C) 2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_parser.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_PARSER_H
#define __HORUSWRK_CMD_PARSER_H          "__HORUSWRK_CMD_PARSER_H"

class CCmdParser
{
private:
    bigstr_t m_cmd;

    str_t m_actionName;

    long m_remoteunit_oid;
    long m_action;
    long m_currpart;
    long m_numparts;

    long getActionFromString(char* str);

public:
    CCmdParser();
    ~CCmdParser();

    /* Methodes */

    int parser(char* cmd);

    /* Getters/Setters */

    char* getCmd();

    char* getActionName();

    long getRemoteUnitOid();
    long getAction();
    long getCurrPart();
    long getNumParts();
};

/* NEW_TYPE: CCmdParser Pointer */

typedef CCmdParser* CCmdParserPtr_t;

#endif
