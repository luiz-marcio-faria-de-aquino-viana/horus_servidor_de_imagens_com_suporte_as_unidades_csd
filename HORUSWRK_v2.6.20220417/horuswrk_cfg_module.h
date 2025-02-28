/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_module.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_MODULE_H
#define __HORUSWRK_CFG_MODULE_H              "__HORUSWRK_CFG_MODULE_H"

class CCfgModule
{
private:
    long m_moduleOid;
    bigstr_t m_moduleName;
    bigstr_t m_moduleFileName;
    long m_numOfParams;

    CCfgParam* m_arrParam;
    int m_szArrParam;

public:
    CCfgModule();
    CCfgModule(char* cfgfile);
    ~CCfgModule();

    /* Methodes */

    void init();

    void terminate();

    void initDefaults();

    void loadConfig(int modulePos, CCfgConfigTag* pConfigTag);

    void setData(CCfgModule* pModule);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    long getModuleOid();

    char* getModuleName();

    char* getModuleFileName();

    long getNumOfParams();

    CCfgParam* getParamPtrAt(int pos);

    CCfgParam* getParamPtr(char* paramName);

};

/* NEW_TYPE: CCfgModule Pointer */

typedef CCfgModule* CCfgModulePtr_t;

#endif
