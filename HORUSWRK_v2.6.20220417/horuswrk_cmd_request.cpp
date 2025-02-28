/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_request.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 05/08/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdRequest::CCmdRequest(long reqnum, connection_t* pCon)
{
    initNewCmdRequest(reqnum, pCon);
}

CCmdRequest::CCmdRequest(long reqnum, char* cmd)
{
    initOldCmdRequest(reqnum, cmd);
}

CCmdRequest::~CCmdRequest()
{
    /* nothing todo! */
}

/* Methodes */

void CCmdRequest::initNewCmdRequest(long reqnum, connection_t* pCon)
{
    m_reqnum = reqnum;
    m_pCon = pCon;
    m_dataType = (byte)pCon->in_buf[0];
    
    reset();

    if( IS_DSK_DATATYPE_REQUEST(m_dataType) ) {
        printf("CCmdRequest::initNewCmdRequest()::IS_DSK_DATATYPE_REQUEST\n");

        if(m_dataType == DEF_DSK_DATATYPE_REQWRITE_BYTEARRAY) {
            //DATATYPE_REQWRITE_BYTEARRAY
            strNCpyUtil(m_actionName, DEF_REQ_ACTION_REQWRITEBLOCK, STRSZ);

            m_remoteunit_oid = -1;
            m_action = DEF_REQ_ACTION_REQWRITEBLOCK_I;
            m_currpart = -1;
            m_numparts = -1;

            memNCpyUtil((byte*) & m_reqBlockData, pCon->in_buf, sizeof(dsk_block_rwreq_t));
        }
        else if(m_dataType == DEF_DSK_DATATYPE_REQREAD_BYTEARRAY) {
            //DATATYPE_REQREAD_BYTEARRAY
            //TODO:
        }
    }
    else if( IS_DSK_DATATYPE_RESPONSE(m_dataType) ) {
        printf("CCmdRequest::initNewCmdRequest()::IS_DSK_DATATYPE_RESPONSE\n");

        if(m_dataType == DEF_DSK_DATATYPE_RESPWRITE_BYTEARRAY) {
            //DATATYPE_RESPWRITE_BYTEARRAY
            strNCpyUtil(m_actionName, DEF_REQ_ACTION_RESPWRITEBLOCK, STRSZ);

            m_remoteunit_oid = -1;
            m_action = DEF_REQ_ACTION_RESPWRITEBLOCK_I;
            m_currpart = -1;
            m_numparts = -1;

            memNCpyUtil((byte*) & m_respBlockData, pCon->in_buf, sizeof(dsk_block_rwresp_t));
        }
        else if(m_dataType == DEF_DSK_DATATYPE_RESPREAD_BYTEARRAY) {
            //DATATYPE_RESPREAD_BYTEARRAY
            //TODO:
        }
    }
    else {
        printf("CCmdRequest::initNewCmdRequest()::INVALID_DSK_DATATYPE\n");
    }
}

void CCmdRequest::initOldCmdRequest(long reqnum, char* cmd)
{
    m_reqnum = reqnum;
    m_dataType = DEF_DSK_DATATYPE_NONE;
    
    reset();

    //DATATYPE_OLD_STRING
    printf("CCmdRequest::initOldCmdRequest()::OLD_STRING(ReqNum #%ld): %s\n", reqnum, cmd);

    if(cmd != NULL) {
        CCmdParser cmdParser;

        int rscode = cmdParser.parser(cmd);
        if(rscode == RSOK) {
            strNCpyUtil(m_actionName, cmdParser.getActionName(), STRSZ);

            m_remoteunit_oid = cmdParser.getRemoteUnitOid();
            m_action = cmdParser.getAction();
            m_currpart = cmdParser.getCurrPart();
            m_numparts = cmdParser.getNumParts();
        }
    }
}

void CCmdRequest::reset()
{
    m_remoteunit_oid = -1;  //REQUEST FROM HOSTSERVER
    m_action = DEF_REQ_ACTION_UNKNOW_I;
    m_currpart = 0;
    m_numparts = 1;

    strNCpyUtil(m_actionName, DEF_REQ_ACTION_UNKNOW, STRSZ);
}

void CCmdRequest::debug()
{
    printf("Request #%ld: remoteunit_oid=%ld,action=%ld,actionName=%s,currpart=%ld,numparts=%ld\n",
        m_reqnum,
        m_remoteunit_oid,
        m_action,
        m_actionName,
        m_currpart,
        m_numparts);
}

/* Getters/Setters */

connection_t* CCmdRequest::getConnectionPtr()
{
    return m_pCon;
}

dsk_block_rwreq_t* CCmdRequest::getReqBlockDataPtr()
{
    return(& m_reqBlockData);
}

dsk_block_rwresp_t* CCmdRequest::getRespBlockDataPtr()
{
    return(& m_respBlockData);
}

byte CCmdRequest::getDataType()
{
    return m_dataType;
}

long CCmdRequest::getReqNum()
{
    return m_reqnum;
}

long CCmdRequest::getRemoteUnitOid()
{
    return m_remoteunit_oid;
}

long CCmdRequest::getAction()
{
    return m_action;
}

char* CCmdRequest::getActionName()
{
    return m_actionName;
}

long CCmdRequest::getCurrPart()
{
    return m_currpart;
}

long CCmdRequest::getNumParts()
{
    return m_numparts;
}
