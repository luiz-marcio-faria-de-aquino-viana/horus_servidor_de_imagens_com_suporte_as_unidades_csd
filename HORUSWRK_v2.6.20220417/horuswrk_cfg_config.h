/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_config.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_CONFIG_H
#define __HORUSWRK_CFG_CONFIG_H                 "__HORUSWRK_CFG_CONFIG_H"

class CCfgConfig
{
private:
    
    CCfgConfigTag m_configTag;

    // CURRENT REMOTE UNIT

    CCfgRemoteUnit* m_pCurrRemoteUnit;
    long m_currRemoteUnitOid;

    // HOST SERVER

    CCfgHostServer m_hostServer;
    
    // REMOTE UNIT

    CCfgRemoteUnit* m_arrRemoteUnits;
    int m_maxNumRemoteUnits; 
    int m_currNumRemoteUnits; 
    
    // MODULES

    CCfgModule* m_arrModules;
    int m_maxNumModules; 
    int m_currNumModules; 

    // DISK GROUPS

    CCfgDiskGroup* m_arrDiskGroups;
    int m_maxNumDiskGroups; 
    int m_currNumDiskGroups; 

public:
    CCfgConfig(int maxNumRemoteUnits, int maxNumModules, int maxNumDiskGroups);

    ~CCfgConfig();

    /* Methodes */

    void init(int maxNumRemoteUnits, int maxNumModules, int maxNumDiskGroups);

    void terminate();

    void loadConfig(char* cfgfile);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */
    
    // CURRENT REMOTE UNIT

    CCfgRemoteUnit* getCurrRemoteUnitPtr();

    long getCurrRemoteUnitOid();

    // HOST SERVER

    CCfgHostServer* getHostServerPtr();
    
    // REMOTE UNIT

    CCfgRemoteUnit* getRemoteUnitAtPtr(int pos);

    CCfgRemoteUnit* getRemoteUnitPtr(int oid);

    CCfgRemoteUnit* getRemoteUnitPtr(char* name);

    int getMaxNumRemoteUnits();

    int getCurrNumRemoteUnits(); 
    
    // MODULES

    CCfgModule* getModuleAtPtr(int pos);

    CCfgModule* getModulePtr(int oid);

    CCfgModule* getModulePtr(char* name);

    int getMaxNumModules();

    int getCurrNumModules();

    // DISK GROUPS

    CCfgDiskGroup* getDiskGroupAtPtr(int pos);

    CCfgDiskGroup* getDiskGroupPtr(int oid);

    CCfgDiskGroup* getDiskGroupPtr(char* name);

    int getMaxNumDiskGroups();

    int getCurrNumDiskGroups();

};

/* NEW_TYPE: CCfgConfig Pointer */

typedef CCfgConfig* CCfgConfigPtr_t;

#endif
