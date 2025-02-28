/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_remoteunit.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_REMOTEUNIT_H
#define __HORUSWRK_CFG_REMOTEUNIT_H             "__HORUSWRK_CFG_REMOTEUNIT_H"

class CCfgRemoteUnit
{
private:
    bigstr_t m_name;                            // remote unit name
    bigstr_t m_ipAddr;                          // remote unit ip address
    bigstr_t m_tblSpcName;                      // remote unit table space name
    bigstr_t m_key;                             // remote unit key
    long m_oid;                                 // remote unit id
    long m_inPort;                              // remote unit in port
    long m_outPort;                             // remote unit out port
    long m_enabled;                             // remote unit enabled (0=disabled / 1=enabled)
    long m_workNode;                            // remote unit type work node (0=disabled / 1=enabled)
    long m_nameNode;                            // remote unit type name node (0=disabled / 1=enabled)
    long m_dataNode;                            // remote unit type data node (0=disabled / 1=enabled)
    long m_runLocal;                            // remote unit local execution

public:
    CCfgRemoteUnit();
    ~CCfgRemoteUnit();

    /* Methodes */

    void initDefaults();

    void init();

    void terminate();

    void loadConfig(int posRemoteUnit, CCfgConfigTag* pConfigTag);

    void setData(CCfgRemoteUnit* pRemoteUnit);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    long getOid();

    char* getName();

    char* getIpAddr();

    long getInPort();

    long getOutPort();

    char* getTblSpcName();

    long getEnabled();

    char* getKey();

    long getWorkNode();

    long getNameNode();
    
    long getDataNode();

    long getRunLocal();

};

/* NEW_TYPE: CCfgRemoteUnit Pointer */

typedef CCfgRemoteUnit* CCfgRemoteUnitPtr_t;

#endif
