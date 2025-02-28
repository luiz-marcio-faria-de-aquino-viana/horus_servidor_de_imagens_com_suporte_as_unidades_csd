/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_error.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 16/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

void warnMsg(int debugLevel, const char* className, const char* methodName, const char* errorMessage)
{
    if(debugLevel != DEBUG_LEVEL) return;

    //bigstr_t local_time_str;
    //getLocalTimeStr(local_time_str);
    //printf("%s WARN(%s_%s): %s\n", local_time_str, className, methodName, errorMessage);

    printf("WARN(%s_%s): %s\n", className, methodName, errorMessage);
}

void warnMsgIfNull(int debugLevel, const char* className, const char* methodName, const char* errorMessage, void* data)
{
    if(debugLevel != DEBUG_LEVEL) return;

    if(data == NULL) {
        warnMsg(debugLevel, className, methodName, errorMessage);
    }
}

void errMsg(const char* className, const char* methodName, const char* errorMessage)
{
    //bigstr_t local_time_str;
    //getLocalTimeStr(local_time_str);
    //printf("%s ERR(%s_%s): %s\n", local_time_str, className, methodName, errorMessage);
 
    printf("ERR(%s_%s): %s\n", className, methodName, errorMessage);
    exit(1);
}

void errMsgIfNull(const char* className, const char* methodName, const char* errorMessage, void* data)
{
    if(data == NULL) {
        errMsg(className, methodName, errorMessage);
    }
}
