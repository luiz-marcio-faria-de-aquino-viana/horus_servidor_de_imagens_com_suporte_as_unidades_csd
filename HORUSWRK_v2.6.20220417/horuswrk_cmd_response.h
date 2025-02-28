/*
 * Copyright(C) 2020-21 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_response.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_RESPONSE_H
#define __HORUSWRK_CMD_RESPONSE_H                   "__HORUSWRK_CMD_RESPONSE_H"

class CCmdResponse
{
private:
    long m_remoteUnitOid;
    long m_reqnum;
    long m_reqtimestamp;
    long m_rescode;
    bigstr_t m_resmsg;
    long m_restype;
    long m_numval;
    bigstr_t m_strval;
    char* m_data;
    long m_datasz;

public:
    CCmdResponse(long reqnum);

    ~CCmdResponse();

    /* Methodes */

    void doResponseSuccess(long numval);

    void doResponseSuccess(char* strval);

    void doResponseSuccess(long restype, long numval);

    void doResponseSuccess(long restype, char* strval);

    void doResponseSuccess(long restype, char* data, long datasz);

    void doResponseFail(long errcode, char* errmsg);

    char* toResultXml(char* resultXml);

    void debug();

    /* Getters/Setters */

    long getRemoteUnitOid();

    long getReqNum();

    long getReqTimestamp();

    long getResCode();

    char* getResMsg();

    long getResType();
    
    long getNumVal();
    
    char* getStrVal();

    char* getData();

    long getDataSz();

};

/* NEW_TYPE: CCmdResponse Pointer */

typedef CCmdResponse* CCmdResponsePtr_t;

#endif
