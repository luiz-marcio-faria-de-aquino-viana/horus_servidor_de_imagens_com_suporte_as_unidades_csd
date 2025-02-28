/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horusdata_cfg_hostserver.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSDATA_CFG_HOSTSERVER_H
#define __HORUSDATA_CFG_HOSTSERVER_H            "__HORUSDATA_CFG_HOSTSERVER_H"

class CCfgHostServer
{
private:
    bigstr_t m_name;                    // name
    bigstr_t m_ipAddr;                  // ip address
    bigstr_t m_key;                     // key
    long m_inPort;                      // in port
    long m_outPort;                     // out port
    long m_oid;                         // oid

public:
    CCfgHostServer();
    ~CCfgHostServer();

    /* Methodes */

    void init();

    void terminate();

    void initDefaults();

    void loadConfig(CCfgConfigTag* pConfigTag);

    void setData(CCfgHostServer* pHostServer);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    long getOid();

    char* getName();

    char* getIpAddr();

    long getInPort();

    long getOutPort();

    char* getKey();

};

/* NEW_TYPE: CCfgHostServer Pointer */

typedef CCfgHostServer* CCfgHostServerPtr_t;

#endif
