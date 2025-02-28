/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_all.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCfgListener::CCfgListener()
{
    init();
}

CCfgListener::~CCfgListener()
{
    terminate();
}

/* Methodes */

void CCfgListener::init()
{
    initDefaults();
}

void CCfgListener::terminate()
{
    /* nothing todo! */
}

void CCfgListener::initDefaults()
{
    strNCpyUtil(m_ipAddr, (char*)DEF_DEFAULT_LISTENER_IPADDR_1, BIGSTRSZ);

    m_inPort = DEF_DEFAULT_LISTENER_IN_PORT_1;
    m_outPort = DEF_DEFAULT_LISTENER_OUT_PORT_1;
}

void CCfgListener::loadConfig(CCfgConfigTag* pConfigTag)
{
    config_tag_t* p = NULL;
    bigstr_t tag;
    
    //LISTENER
    sprintf(tag, DEF_TAGTXT_LISTENER_IPADDR);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_ipAddr, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_LISTENER_REQUEST_SERVICE_PORT);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_inPort = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_LISTENER_RESPONSE_SERVICE_PORT);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_outPort = atol(p->tag_value);

}

void CCfgListener::setData(CCfgListener* pListener)
{
    strNCpyUtil(m_ipAddr, pListener->getIpAddr(), BIGSTRSZ);

    m_inPort = pListener->getInPort();
    m_outPort = pListener->getOutPort();
}

void CCfgListener::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgListener::IpAddr=%s,InPort=%ld,OutPort=%ld\n",
        m_ipAddr,
        m_inPort,
        m_outPort);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

char* CCfgListener::getIpAddr()
{
    return m_ipAddr;
}

long CCfgListener::getInPort()
{
    return m_inPort;
}

long CCfgListener::getOutPort()
{
    return m_outPort;
}
