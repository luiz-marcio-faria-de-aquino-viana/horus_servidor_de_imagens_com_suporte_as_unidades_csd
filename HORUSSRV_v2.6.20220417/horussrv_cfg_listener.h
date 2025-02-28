/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horusdata_cfg_listener.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 30/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CFG_LISTENER_H
#define __HORUSSRV_CFG_LISTENER_H            "__HORUSSRV_CFG_LISTENER_H"

class CCfgListener
{
private:
    bigstr_t m_ipAddr;                  // ip address
    long m_inPort;                      // in port
    long m_outPort;                     // out port

public:
    CCfgListener();
    ~CCfgListener();

    /* Methodes */

    void init();

    void terminate();

    void initDefaults();

    void loadConfig(CCfgConfigTag* pConfigTag);

    void setData(CCfgListener* pListener);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    char* getIpAddr();

    long getInPort();

    long getOutPort();

};

/* NEW_TYPE: CCfgListener Pointer */

typedef CCfgListener* CCfgListenerPtr_t;

#endif
