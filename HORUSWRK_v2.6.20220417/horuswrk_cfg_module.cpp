/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_module.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgModule::CCfgModule()
{
    init();
}

CCfgModule::~CCfgModule()
{
    terminate();
}

/* Methodes */

void CCfgModule::init()
{
    initDefaults();
}

void CCfgModule::terminate()
{
    /* nothing todo! */
}

void CCfgModule::initDefaults()
{
    strSetEmptyUtil(m_moduleName);
    strSetEmptyUtil(m_moduleFileName);

    m_moduleOid = DBNULL_LONG;
}

void CCfgModule::loadConfig(int modulePos, CCfgConfigTag* pConfigTag)
{
    config_tag_t* p = NULL;

    bigstr_t tag;

    //MODULE
    sprintf(tag, DEF_TAGTXT_MODULE_OID, modulePos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_moduleOid = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_MODULE_NAME, modulePos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_moduleName, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_MODULE_FILE_NAME, modulePos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_moduleFileName, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_NUMOFPARAMS, modulePos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL) {
        m_numOfParams = atol(p->tag_value);

        //PARAM
        m_szArrParam = (int)m_numOfParams;
        m_arrParam = (CCfgParam*)allocDataArray(sizeof(CCfgParam), m_szArrParam);
        for(int i = 0; i < m_szArrParam; i++) {
            CCfgParam* p = & m_arrParam[i];
            p->loadConfig(modulePos, i, pConfigTag);
        }
    }
}

void CCfgModule::setData(CCfgModule* pModule)
{
    strNCpyUtil(m_moduleName, pModule->getModuleName(), BIGSTRSZ);
    strNCpyUtil(m_moduleFileName, pModule->getModuleFileName(), BIGSTRSZ);

    m_moduleOid = pModule->getModuleOid();
}

void CCfgModule::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgModule: ModuleOid=%ld,ModuleName=%s,ModuleFileName=%s,NumOfParams=%ld\n",
        m_moduleOid,
        m_moduleName,
        m_moduleFileName,
        m_numOfParams);
    warnMsg(debugLevel, className, methodName, errmsg);

    for(int i = 0; i < m_szArrParam; i++) {
        CCfgParam* p = & m_arrParam[i];
        p->debug(debugLevel, className, methodName);
    }        
}

/* Getters/Settes */

long CCfgModule::getModuleOid()
{
    return m_moduleOid;
}

char* CCfgModule::getModuleName()
{
    return m_moduleName;
}

char* CCfgModule::getModuleFileName()
{
    return m_moduleFileName;
}

long CCfgModule::getNumOfParams()
{
    return m_numOfParams;
}

CCfgParam* CCfgModule::getParamPtrAt(int pos)
{
    if(pos < m_szArrParam) {
        CCfgParam* p = & m_arrParam[pos];
        return p;
    }
    return NULL;
}

CCfgParam* CCfgModule::getParamPtr(char* paramName)
{
    for(int i = 0; i < m_szArrParam; i++) {
        CCfgParam* p = & m_arrParam[i];
        if( strNCmpCaseUtil(paramName, p->getParamName(), BIGSTRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 )
            return p;
    }
    return NULL;
}
