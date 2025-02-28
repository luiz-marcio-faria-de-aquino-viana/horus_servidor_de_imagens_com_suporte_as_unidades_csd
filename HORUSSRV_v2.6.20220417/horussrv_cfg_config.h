/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_config.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CFG_CONFIG_H
#define __HORUSSRV_CFG_CONFIG_H              "__HORUSSRV_CFG_CONFIG_H"

class CCfgConfig
{
private:
    
    CCfgConfigTag m_configTag;

    // HOST SERVER

    CCfgHostServer m_hostServer;
    
    // LISTENER

    CCfgListener m_listener;

    // REMOTE UNIT

    CCfgRemoteUnit* m_arrRemoteUnits;
    int m_maxNumRemoteUnits; 
    int m_currNumRemoteUnits; 

public:
    CCfgConfig(int maxNumRemoteUnits);

    ~CCfgConfig();

    /* Methodes */

    void init(int maxNumRemoteUnits);

    void terminate();

    void loadConfig(char* cfgfile);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    // HOST SERVER

    CCfgHostServer* getHostServerPtr();
    
    // LISTENER

    CCfgListener* getListenerPtr();

    // REMOTE UNIT

    CCfgRemoteUnit* getRemoteUnitAtPtr(int pos);

    CCfgRemoteUnit* getRemoteUnitPtr(int oid);

    CCfgRemoteUnit* getRemoteUnitPtr(char* name);

    int getMaxNumRemoteUnits();

    int getCurrNumRemoteUnits(); 

};

/* NEW_TYPE: CCfgConfig Pointer */

typedef CCfgConfig* CCfgConfigPtr_t;

#endif
