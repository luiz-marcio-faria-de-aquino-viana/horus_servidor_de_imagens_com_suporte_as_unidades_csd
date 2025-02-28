/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_all.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgHostServer::CCfgHostServer()
{
    init();
}

CCfgHostServer::~CCfgHostServer()
{
    terminate();
}

/* Methodes */

void CCfgHostServer::init()
{
    initDefaults();
}

void CCfgHostServer::terminate()
{
    /* nothing todo! */
}

void CCfgHostServer::initDefaults()
{
    strNCpyUtil(m_name, (char*)DEF_DEFAULT_HOSTSERVER_NAME_1, BIGSTRSZ);
    strNCpyUtil(m_ipAddr, (char*)DEF_DEFAULT_HOSTSERVER_IPADDR_1, BIGSTRSZ);
    strNCpyUtil(m_key, (char*)DEF_DEFAULT_HOSTSERVER_KEY_1, BIGSTRSZ);

    m_oid = DEF_DEFAULT_HOSTSERVER_OID_1;
    m_inPort = DEF_DEFAULT_HOSTSERVER_IN_PORT_1;
    m_outPort = DEF_DEFAULT_HOSTSERVER_OUT_PORT_1;
}

void CCfgHostServer::loadConfig(CCfgConfigTag* pConfigTag)
{
    config_tag_t* p = NULL;
    
    bigstr_t tag;
    
    //HOSTSERVER
    sprintf(tag, DEF_TAGTXT_HOSTSERVER_OID);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_oid = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_HOSTSERVER_NAME);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_name, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_HOSTSERVER_IPADDR);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_ipAddr, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_HOSTSERVER_IN_PORT);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_inPort = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_HOSTSERVER_OUT_PORT);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_outPort = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_HOSTSERVER_KEY);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_key, p->tag_value, BIGSTRSZ);

}

void CCfgHostServer::setData(CCfgHostServer* pHostServer)
{
    strNCpyUtil(m_name, pHostServer->getName(), BIGSTRSZ);
    strNCpyUtil(m_ipAddr, pHostServer->getIpAddr(), BIGSTRSZ);
    strNCpyUtil(m_key, pHostServer->getKey(), BIGSTRSZ);

    m_oid = pHostServer->getOid();
    m_inPort = pHostServer->getInPort();
    m_outPort = pHostServer->getOutPort();
}

void CCfgHostServer::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgHostServer::Oid=%ld,Name=%s,IpAddr=%s,InPort=%ld,OutPort=%ld,Key=%s\n",
        m_oid,
        m_name,
        m_ipAddr,
        m_inPort,
        m_outPort,
        m_key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

long CCfgHostServer::getOid()
{
    return m_oid;
}

char* CCfgHostServer::getName()
{
    return m_name;
}

char* CCfgHostServer::getIpAddr()
{
    return m_ipAddr;
}

long CCfgHostServer::getInPort()
{
    return m_inPort;
}

long CCfgHostServer::getOutPort()
{
    return m_outPort;
}

char* CCfgHostServer::getKey()
{
    return m_key;
}
