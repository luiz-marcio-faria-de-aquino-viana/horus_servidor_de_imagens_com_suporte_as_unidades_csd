/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_module_param.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_EXT_MODULE_PARAM_H
#define __HORUSWRK_EXT_MODULE_PARAM_H               "__HORUSWRK_EXT_MODULE_PARAM_H"

class CExtModuleParam
{
private:
    str_t m_paramName;
    bigstr_t m_paramValue;
    int m_paramMode;            // 1=fixed parameter; 2=variable parameter

public:

    CExtModuleParam(char* paramName, char* paramValue, int paramMode);
    ~CExtModuleParam();

    /* Getters/Setters */

    char* getParamName();

    void setParamName(char* paramName);

    char* getParamValue();

    void setParamValue(char* paramValue);

};

/* NEW_TYPE: CExtModuleParam Pointer */

typedef CExtModuleParam* CExtModuleParamPtr_t;

#endif
