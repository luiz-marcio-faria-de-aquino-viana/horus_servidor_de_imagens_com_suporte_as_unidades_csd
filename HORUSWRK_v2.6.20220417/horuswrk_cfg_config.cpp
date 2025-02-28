/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_config.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgConfig::CCfgConfig(int maxNumRemoteUnits, int maxNumModules, int maxNumDiskGroups)
{
    init(maxNumRemoteUnits, maxNumModules, maxNumDiskGroups);
}

CCfgConfig::~CCfgConfig()
{
    terminate();
}

/* Methodes */

void CCfgConfig::init(int maxNumRemoteUnits, int maxNumModules, int maxNumDiskGroups)
{
    m_arrRemoteUnits = (CCfgRemoteUnit*)allocDataArray(sizeof(CCfgRemoteUnit), maxNumRemoteUnits);
    m_maxNumRemoteUnits = maxNumRemoteUnits;
    m_currNumRemoteUnits = 0;

    m_arrModules = (CCfgModule*)allocDataArray(sizeof(CCfgModule), maxNumModules);
    m_maxNumModules = maxNumModules;
    m_currNumModules = 0;

    m_arrDiskGroups = (CCfgDiskGroup*)allocDataArray(sizeof(CCfgDiskGroup), maxNumDiskGroups);
    m_maxNumDiskGroups = maxNumDiskGroups; 
    m_currNumDiskGroups = 0; 
}

void CCfgConfig::terminate()
{
    freeDataArray(m_arrRemoteUnits);
    freeDataArray(m_arrModules);
    freeDataArray(m_arrDiskGroups);
}

void CCfgConfig::loadConfig(char* cfgfile)
{
    CCfgContext* pContext = gAppMain.getContextPtr();

    config_tag_t* p = NULL;

    bigstr_t strTmp;
    
    m_configTag.loadConfigTagsValue(cfgfile);

    p = m_configTag.findConfigTagByName((char*)DEF_TAGTXT_CURRENT_REMOTEUNIT_OID);
    if(p != NULL) {
        strNCpyUtil(strTmp, p->tag_value, BIGSTRSZ); 
        m_currRemoteUnitOid = atoi(strTmp);
    }

    p = m_configTag.findConfigTagByName((char*)DEF_TAGTXT_NUMOFREMOTEUNITS);
    if(p != NULL) {
        strNCpyUtil(strTmp, p->tag_value, BIGSTRSZ); 
        m_currNumRemoteUnits = atoi(strTmp);
    }

    p = m_configTag.findConfigTagByName((char*)DEF_TAGTXT_NUMOFMODULES);
    if(p != NULL) {
        strNCpyUtil(strTmp, p->tag_value, BIGSTRSZ); 
        m_currNumModules = atoi(strTmp);
    }

    p = m_configTag.findConfigTagByName((char*)DEF_TAGTXT_NUMOFDISKGROUPS);
    if(p != NULL) {
        strNCpyUtil(strTmp, p->tag_value, BIGSTRSZ); 
        m_currNumDiskGroups = atoi(strTmp);
    }

    m_hostServer.loadConfig(& m_configTag);

    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* pRemoteUnit = & m_arrRemoteUnits[i];
        pRemoteUnit->loadConfig(i, & m_configTag);
    }
    
    m_pCurrRemoteUnit = getRemoteUnitPtr(m_currRemoteUnitOid);
    errMsgIfNull(__HORUSWRK_CFG_CONFIG_H, "loadConfig()", ERR_CANTFINDREMOTEUNIT, m_pCurrRemoteUnit);

    pContext->resetDataLocation(m_pCurrRemoteUnit->getName());

    for(int i = 0; i < m_currNumModules; i++) {
        CCfgModule* pModule = & m_arrModules[i];
        pModule->loadConfig(i, & m_configTag);
    }

    for(int i = 0; i < m_currNumDiskGroups; i++) {
        CCfgDiskGroup* pDiskGroup = & m_arrDiskGroups[i];
        pDiskGroup->loadConfig(i, & m_configTag);
    }

}

void CCfgConfig::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg, 
        "\nCCfgConfig::NumOfRemoteUnits=%d/%d,NumOfModules=%d/%d,NumOfDiskGroups=%d/%d\n",
        m_currNumRemoteUnits,
        m_maxNumRemoteUnits,
        m_currNumModules,
        m_maxNumModules,
        m_currNumDiskGroups,
        m_maxNumDiskGroups);
    warnMsg(debugLevel, className, methodName, errmsg);

    m_pCurrRemoteUnit->debug(debugLevel, className, methodName);

    m_hostServer.debug(debugLevel, className, methodName);

    for(int i = 0; i < m_currNumRemoteUnits; i++) {
        CCfgRemoteUnit* p = & m_arrRemoteUnits[i];
        p->debug(debugLevel, className, methodName);
    }

    for(int i = 0; i < m_currNumModules; i++) {
        CCfgModule* p = & m_arrModules[i];
        p->debug(debugLevel, className, methodName);
    }

    for(int i = 0; i < m_currNumDiskGroups; i++) {
        CCfgDiskGroup* p = & m_arrDiskGroups[i];
        p->debug(debugLevel, className, methodName);
    }
}

/* Getters/Settes */

// CURRENT REMOTE UNIT

CCfgRemoteUnit* CCfgConfig::getCurrRemoteUnitPtr()
{
    return m_pCurrRemoteUnit;
}

long CCfgConfig::getCurrRemoteUnitOid()
{
    return m_currRemoteUnitOid;
}

// HOST SERVER

CCfgHostServer* CCfgConfig::getHostServerPtr()
{
    return & m_hostServer;
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

// MODULES

CCfgModule* CCfgConfig::getModuleAtPtr(int pos)
{
    if(pos < m_currNumModules) {
        CCfgModule* p = & m_arrModules[pos];
        return p;
    }
    return NULL;
}

CCfgModule* CCfgConfig::getModulePtr(int oid)
{
    for(int i = 0; i < m_currNumModules; i++) {
        CCfgModule* p = & m_arrModules[i];
        if(p->getModuleOid() == oid)
            return p;
    }
    return NULL;
}

CCfgModule* CCfgConfig::getModulePtr(char* name)
{
    for(int i = 0; i < m_currNumModules; i++) {
        CCfgModule* p = & m_arrModules[i];
        if(strNCmpCaseUtil(p->getModuleName(), name, STRSZ, DEF_CASESENSITIVE_TOUPPER) == 0)
            return p;
    }
    return NULL;
}

int CCfgConfig::getMaxNumModules()
{
    return m_maxNumModules;
}

int CCfgConfig::getCurrNumModules()
{
    return m_currNumModules;
}

// DISK GROUPS

CCfgDiskGroup* CCfgConfig::getDiskGroupAtPtr(int pos)
{
    if(pos < m_currNumDiskGroups) {
        CCfgDiskGroup* p = & m_arrDiskGroups[pos];
        return p;
    }
    return NULL;
}

CCfgDiskGroup* CCfgConfig::getDiskGroupPtr(int oid)
{
    for(int i = 0; i < m_currNumDiskGroups; i++) {
        CCfgDiskGroup* p = & m_arrDiskGroups[i];
        if(p->getOid() == oid)
            return p;
    }
    return NULL;
}

CCfgDiskGroup* CCfgConfig::getDiskGroupPtr(char* name)
{
    for(int i = 0; i < m_currNumDiskGroups; i++) {
        CCfgDiskGroup* p = & m_arrDiskGroups[i];
        if(strNCmpCaseUtil(p->getName(), name, STRSZ, DEF_CASESENSITIVE_TOUPPER) == 0)
            return p;
    }
    return NULL;
}

int CCfgConfig::getMaxNumDiskGroups()
{
    return m_maxNumDiskGroups;
}

int CCfgConfig::getCurrNumDiskGroups()
{
    return m_currNumDiskGroups;
}
