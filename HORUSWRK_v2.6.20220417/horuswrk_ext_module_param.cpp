/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_module_param.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CExtModuleParam::CExtModuleParam(char* paramName, char* paramValue, int paramMode)
{
    strSetEmptyUtil(m_paramName);
    strNCpyUtil(m_paramName, paramName, STRSZ);

    strSetEmptyUtil(m_paramValue);
    strNCpyUtil(m_paramValue, paramValue, BIGSTRSZ);

    m_paramMode = paramMode;
}

CExtModuleParam::~CExtModuleParam()
{
    /* nothing todo! */
}

char* CExtModuleParam::getParamName()
{
    return m_paramName;
}

void CExtModuleParam::setParamName(char* paramName)
{
    strSetEmptyUtil(m_paramName);
    strNCpyUtil(m_paramName, paramName, STRSZ);
}

char* CExtModuleParam::getParamValue()
{
    return m_paramValue;
}

void CExtModuleParam::setParamValue(char* paramValue)
{
    strSetEmptyUtil(m_paramValue);
    strNCpyUtil(m_paramValue, paramValue, STRSZ);
}
