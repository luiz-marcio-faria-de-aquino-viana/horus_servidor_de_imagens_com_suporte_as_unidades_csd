/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_param.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgParam::CCfgParam()
{
    initDefaults();
}
    
CCfgParam::~CCfgParam()
{
    /* nothing todo! */
}

/* Methodes */

void CCfgParam::init()
{
    initDefaults();
}

void CCfgParam::terminate()
{
    /* nothing todo! */
}

void CCfgParam::initDefaults()
{
    strSetEmptyUtil(m_paramName);
    strSetEmptyUtil(m_paramValue);

    m_paramMode = DBNULL_LONG;
}

void CCfgParam::loadConfig(int modulePos, int paramPos, CCfgConfigTag* pConfigTag)
{
    config_tag_t* p = NULL;

    bigstr_t tag;

    //PARAM
    sprintf(tag, DEF_TAGTXT_PARAM_NAME, modulePos, paramPos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_paramName, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_PARAM_VALUE, modulePos, paramPos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_paramValue, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_PARAM_MODE, modulePos, paramPos);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_paramMode = atol(p->tag_value);

}

void CCfgParam::setData(CCfgParam* pParam)
{
    strNCpyUtil(m_paramName, pParam->getParamName(), BIGSTRSZ);
    strNCpyUtil(m_paramValue, pParam->getParamValue(), BIGSTRSZ);
    
    m_paramMode = pParam->getParamMode();
}

void CCfgParam::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgParam::ParamName=%s,ParamValue=%s,ParamMode=%ld\n",
        m_paramName,
        m_paramValue,
        m_paramMode);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

char* CCfgParam::getParamName()
{
    return m_paramName;
}

char* CCfgParam::getParamValue()
{
    return m_paramValue;
}

long CCfgParam::getParamMode()
{
    return m_paramMode;
}
