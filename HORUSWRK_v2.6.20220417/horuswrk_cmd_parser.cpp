/*
 * Copyright(C) 2020-21 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_parser.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdParser::CCmdParser()
{
    strSetEmptyUtil(m_cmd);

    strNCpyUtil(m_actionName, DEF_REQ_ACTION_UNKNOW, STRSZ);

    m_remoteunit_oid = -1;      // DEFAULT HOSTSERVER
    m_action = DEF_REQ_ACTION_UNKNOW_I;
    m_currpart = 0;
    m_numparts = 1;
}

CCmdParser::~CCmdParser()
{
    /* nothing todo! */
}

long CCmdParser::getActionFromString(char* str)
{
    printf("\nCCmdParser::getActionFromString: %s", str);

    long ret_action = DEF_REQ_ACTION_UNKNOW_I;

    //CONVERT_MOD
    if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_CONVERT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_CONVERT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_CONVERT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_CONVERT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_CONVERT_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_CONVERT, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_CONVERT_I;
    }
    //REPROJ_MOD
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_REPROJ_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_REPROJ_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_REPROJ_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_REPROJ_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_REPROJ_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_REPROJ, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_REPROJ_I;
    }
    //SIMPL_MOD
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_SIMPL_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_SIMPL_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_SIMPL_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_SIMPL_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_SIMPL_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_SIMPL, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_SIMPL_I;
    }
    //UPLOAD
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_UPLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_UPLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_UPLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_UPLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_UPLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_UPLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_UPLOAD_I;
    }
    //DOWNLOAD
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_DOWNLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_DOWNLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_DOWNLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_DOWNLOAD_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_DOWNLOAD, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_DOWNLOAD_I;
    }
    //MKDIR
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_MKDIR_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS2_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS2_MKDIR_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS3_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS3_MKDIR_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS4_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS4_MKDIR_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS5_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS5_MKDIR_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS6_MKDIR, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS6_MKDIR_I;
    }
    //DOWNLOAD_AND_PROCESS
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }
    else if(strNCmpUtil(str, (char*)DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS, STRSZ) == 0) {
        ret_action = DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I;
    }

    if(ret_action != DEF_REQ_ACTION_UNKNOW_I)
        strNCpyUtil(m_actionName, str, STRSZ);
    return ret_action;
}

int CCmdParser::parser(char* cmd)
{
    strNCpyUtil(m_cmd, cmd, BIGSTRSZ);
    printf("\nCCmdParser::parser: %s", m_cmd);

    int result = RSERR;
    str_t tmp;

    char* tk = strtok(cmd, "^");
    int tknum = 0;
    while(tk != NULL) {
        printf("\nCCmdParser::Token=%s", tk);            

        if(tknum == 0) {
            strNCpyUtil(tmp, tk, STRSZ);
            m_remoteunit_oid = atol(tmp);
        }
        else {
            if(m_action == DEF_REQ_ACTION_UNKNOW_I) 
            {
                m_action = getActionFromString(tk);
                if(m_action == DEF_REQ_ACTION_UNKNOW_I)
                    return RSERR;
            }
            else if(m_action != DEF_REQ_ACTION_UNKNOW_I) 
            {
                if(tknum == 2) {
                    strNCpyUtil(tmp, tk, STRSZ);
                    m_currpart = atol(tmp);
                }
                else if(tknum == 3) {
                    strNCpyUtil(tmp, tk, STRSZ);
                    m_numparts = atol(tmp);
                    return RSOK;
                }
            }
        }
        tk = strtok(NULL, "^");
        tknum += 1;
    }

    return result;
}

char* CCmdParser::getCmd()
{
    return m_cmd;
}

char* CCmdParser::getActionName()
{
    return m_actionName;
}

long CCmdParser::getRemoteUnitOid()
{
    return m_remoteunit_oid;
}

long CCmdParser::getAction()
{
    return m_action;
}

long CCmdParser::getCurrPart()
{
    return m_currpart;
}

long CCmdParser::getNumParts()
{
    return m_numparts;
}
