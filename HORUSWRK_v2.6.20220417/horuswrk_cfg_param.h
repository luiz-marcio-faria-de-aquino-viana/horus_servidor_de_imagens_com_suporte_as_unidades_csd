/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_param.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_PARAM_H
#define __HORUSWRK_CFG_PARAM_H                 "__HORUSWRK_CFG_PARAM_H"

class CCfgParam
{
private:
    bigstr_t m_paramName;
    bigstr_t m_paramValue;
    long m_paramMode;

public:
    CCfgParam();
    ~CCfgParam();

    /* Methodes */

    void init();

    void terminate();

    void initDefaults();

    void loadConfig(int modulePos, int paramPos, CCfgConfigTag* pConfigTag);

    void setData(CCfgParam* pParam);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    char* getParamName();

    char* getParamValue();

    long getParamMode();

};

/* NEW_TYPE: CCfgParam Pointer */

typedef CCfgParam* CCfgParamPtr_t;

#endif
