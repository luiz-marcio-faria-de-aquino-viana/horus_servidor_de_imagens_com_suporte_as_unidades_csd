/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_response.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdResponse::CCmdResponse(long reqnum)
{
    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pRemoteUnit = pConfig->getCurrRemoteUnitPtr();

    m_remoteUnitOid = pRemoteUnit->getOid();
    m_reqnum = reqnum;
    m_reqtimestamp = getCurrentTimestamp();
    m_rescode = DEF_RESCODE_FAIL_UNKNOW;
    strNCpyUtil(m_resmsg, DEF_RESMSG_FAIL_UNKNOW, BIGSTRSZ);
    m_restype = DEF_RESTYPE_NONE;
    m_numval = 0;
    strSetEmptyUtil(m_strval);
    m_data = NULL;
    m_datasz = 0;
}

CCmdResponse::~CCmdResponse()
{
    if(m_data != NULL)
        free(m_data);
}

void CCmdResponse::doResponseSuccess(long numval)
{
    m_rescode = DEF_RESCODE_SUCCESS;
    strNCpyUtil(m_resmsg, DEF_RESMSG_SUCCESS, BIGSTRSZ);
    m_restype = DEF_RESTYPE_NUMBER_VAL;
    m_numval = numval;
}

void CCmdResponse::doResponseSuccess(char* strval)
{
    m_rescode = DEF_RESCODE_SUCCESS;
    strNCpyUtil(m_resmsg, DEF_RESMSG_SUCCESS, BIGSTRSZ);
    m_restype = DEF_RESTYPE_STRING_VAL;
    strNCpyUtil(m_resmsg, strval, BIGSTRSZ);
}

void CCmdResponse::doResponseSuccess(long restype, long numval)
{
    m_rescode = DEF_RESCODE_SUCCESS;
    strNCpyUtil(m_resmsg, DEF_RESMSG_SUCCESS, BIGSTRSZ);
    m_restype = restype;
    m_numval = numval;
}

void CCmdResponse::doResponseSuccess(long restype, char* strval)
{
    m_rescode = DEF_RESCODE_SUCCESS;
    strNCpyUtil(m_resmsg, DEF_RESMSG_SUCCESS, BIGSTRSZ);
    m_restype = restype;
    strNCpyUtil(m_resmsg, strval, BIGSTRSZ);
}

void CCmdResponse::doResponseSuccess(long restype, char* data, long datasz)
{
    m_rescode = DEF_RESCODE_SUCCESS;
    strNCpyUtil(m_resmsg, DEF_RESMSG_SUCCESS, BIGSTRSZ);
    m_restype = restype;
    m_datasz = datasz;
    strNCpyUtil(m_data, data, m_datasz);
}

void CCmdResponse::doResponseFail(long errcode, char* errmsg)
{
    m_rescode = errcode;
    strNCpyUtil(m_resmsg, errmsg, BIGSTRSZ);
    m_restype = DEF_RESTYPE_NONE;
}

char* CCmdResponse::toResultXml(char* resultXml)
{
    sprintf(resultXml, 
        (char*)DEF_XML_RESPONSE,
        m_remoteUnitOid,
        m_reqnum,
        m_reqtimestamp,
        m_rescode,
        m_resmsg,
        m_restype,
        m_numval,
        m_strval,
        ((m_data != NULL) ? m_data : (char*)"\0"),
        m_datasz);
    return resultXml;
}

void CCmdResponse::debug()
{
    printf("Response - RemoteUnit: %ld, ReqNum #%ld: timestamp=%ld,rescode=%ld,resmsg=%s,restype=%ld,numval=%ld,strval=%s,data=%s,datasz=%ld\n",
        m_remoteUnitOid,
        m_reqnum,
        m_reqtimestamp,
        m_rescode,
        m_resmsg,
        m_restype,
        m_numval,
        m_strval,
        ((m_data != NULL) ? m_data : (char*)"\0"),
        m_datasz);
}

long CCmdResponse::getRemoteUnitOid()
{
    return m_remoteUnitOid;
}

long CCmdResponse::getReqNum()
{
    return m_reqnum;
}

long CCmdResponse::getReqTimestamp()
{
    return m_reqtimestamp;
}

long CCmdResponse::getResCode()
{
    return m_rescode;
}

char* CCmdResponse::getResMsg()
{
    return m_resmsg;
}

long CCmdResponse::getResType()
{
    return m_restype;
}

long CCmdResponse::getNumVal()
{
    return m_numval;
}

char* CCmdResponse::getStrVal()
{
    return m_strval;
}

char* CCmdResponse::getData()
{
    return m_data;
}

long CCmdResponse::getDataSz()
{
    return m_datasz;
}
