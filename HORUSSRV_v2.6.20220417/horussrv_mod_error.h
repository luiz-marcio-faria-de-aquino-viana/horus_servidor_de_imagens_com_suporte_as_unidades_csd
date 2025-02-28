/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_error.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 16/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_ERROR_H
#define __HORUSSRV_MOD_ERROR_H       "__HORUSSRV_MOD_ERROR_H"

/* ERROR MESSAGES
 */
#define ERR_CANTALLOCATEMEMORY                  "Can't allocate memory"
#define ERR_FILENOTFOUND                        "File not found"
#define ERR_CANTOPENFILE                        "Can't open file"
#define ERR_SEQUENCEVALUEOVERFLOW               "Sequence value overflow"
#define ERR_INVALIDUSERNAMEPASSWORD             "Invalid username password"
#define ERR_CURRENTUSERDONTHAVERIGHTS           "Current user don't have sufficient rights"
#define ERR_INVALIDTABLENAME                    "Invalid table name"
#define ERR_CANTFINDOBJECTID                    "Can't find object id"
#define ERR_CANTFINDKEY                         "Can't find key"
#define ERR_MAXNUMBERENTRIESREACHED             "Number maximum of entries reached"
#define ERR_CANTCREATESOCKET                    "Can't create socket"
#define ERR_CANTBINDSOCKET                      "Can't bind socket"
#define ERR_CANTLISTENPORT                      "Can't listen, port in use"
#define ERR_CANTCREATELISTNERTHREAD             "Can't create listening thread"
#define ERR_CANTSENDMESSAGE                     "Can't send message"
#define ERR_CANTCONNECTSOCKET                   "Can't open socket connection"
#define ERR_CANTRECVMESSAGE                     "Can't receive message"
#define ERR_CANTSETSOCKETOPT                    "Can't set socket options"

/* ERROR FUNCTIONS
 */

void warnMsg(int debugLevel, const char* className, const char* methodName, const char* errorMessage);

void warnMsgIfNull(int debugLevel, const char* className, const char* methodName, const char* errorMessage, void* data);

void errMsg(const char* className, const char* methodName, const char* errorMessage);

void errMsgIfNull(const char* className, const char* methodName, const char* errorMessage, void* data);

#endif
