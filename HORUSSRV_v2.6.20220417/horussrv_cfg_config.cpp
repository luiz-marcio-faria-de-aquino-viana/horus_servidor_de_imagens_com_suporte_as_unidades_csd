/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_config.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCfgConfig::CCfgConfig(int maxNumRemoteUnits)
{
    init(maxNumRemoteUnits);
}

CCfgConfig::~CCfgConfig()
{
    terminate();
}

/* Methodes */

void CCfgConfig::init(int maxNumRemoteUnits)
{
    m_arrRemoteUnits = (CCfgRemoteUnit*)allocDataArray(sizeof(CCfgRemoteUnit), maxNumRemoteUnits);
    m_maxNumRemoteUnits = maxNumRemoteUnits;
    m_currNumRemoteUnits = 0;
}

void CCfgConfig::terminate()
{
    freeDataArray(m_arrRemoteUnits);
}

void CCfgConfig::loadConfig(char* cfgfile)
{
    CCfgContext* pContext = gAppMain.getContextPtr();

    config_tag_t* p = NULL;

    bigstr_t strTmp;
    
    m_configTag.loadConfigTagsValue(cfgfile);

    p = m_configTag.findConfigTagByName((char*)DEF_TAGTXT_NUMOFREMOTEUNITS);
    if(p != NULL) {
        strNCpyUtil(strTmp, p->tag_value, BIGSTRSZ); 
        m_currNumRemoteUnits = atoi(strTmp);
    }

    m_hostServer.loadConfig(& m_configTag);

    pContext->resetDataLocation(m_hostServer.getName());

    m_listener.loadConfig(& m_configTag);

    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* pRemoteUnit = & m_arrRemoteUnits[i];
        pRemoteUnit->loadConfig(i, & m_configTag);
    }
}

void CCfgConfig::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg, 
        "\nCCfgConfig::NumOfRemoteUnits=%d/%d\n",
        m_currNumRemoteUnits,
        m_maxNumRemoteUnits);
    warnMsg(debugLevel, className, methodName, errmsg);

    m_hostServer.debug(debugLevel, className, methodName);

    m_listener.debug(debugLevel, className, methodName);

    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* p = & m_arrRemoteUnits[i];
        p->debug(debugLevel, className, methodName);
    }
}

/* Getters/Settes */

// HOST SERVER

CCfgHostServer* CCfgConfig::getHostServerPtr()
{
    return & m_hostServer;
}

// LISTENER

CCfgListener* CCfgConfig::getListenerPtr()
{
    return & m_listener;
}

// REMOTE UNIT

CCfgRemoteUnit* CCfgConfig::getRemoteUnitAtPtr(int pos)
{
    if(pos < m_currNumRemoteUnits) {
        CCfgRemoteUnit* p = & m_arrRemoteUnits[pos];
        return p;
    }
    return NULL;
}

CCfgRemoteUnit* CCfgConfig::getRemoteUnitPtr(int oid)
{
    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* p = & m_arrRemoteUnits[i];
        if(p->getOid() == oid)
            return p;
    }
    return NULL;
}

CCfgRemoteUnit* CCfgConfig::getRemoteUnitPtr(char* name)
{
    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* p = & m_arrRemoteUnits[i];
        if(strNCmpCaseUtil(p->getName(), name, STRSZ, DEF_CASESENSITIVE_TOUPPER) == 0)
            return p;
    }
    return NULL;
}

int CCfgConfig::getMaxNumRemoteUnits()
{
    return m_maxNumRemoteUnits;
}

int CCfgConfig::getCurrNumRemoteUnits()
{
    return m_currNumRemoteUnits;
}
