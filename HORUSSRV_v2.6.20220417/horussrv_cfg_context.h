/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_context.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CFG_CONTEXT_H
#define __HORUSSRV_CFG_CONTEXT_H        "__HORUSSRV_CFG_CONTEXT_H"

class CCfgContext
{
private:
    pathname_t m_homeDir;               // home directory
    pathname_t m_binDir;                // executables directory
    pathname_t m_configDir;             // config directory
    pathname_t m_dataDir;               // data directory
    pathname_t m_logDir;                // log directory
    pathname_t m_tempDir;               // temp directory
    pathname_t m_tmpDir;                // tmp directory
    //
    //pathname_t m_imgSrcDir;             // image source directory
    //pathname_t m_imgDstDir;             // image destination directory
    //
    pathname_t m_configFile;            // configuration file path
    pathname_t m_defaultConfigFile;     // default configuration file path
    //
    pathname_t m_logFile;               // log file path

public:
    CCfgContext();
    ~CCfgContext();

    /* Methodes */

    void initDefaults();

    void resetDataLocation(char* hostServerName);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    char* getHomeDir();

    char* getBinDir();

    char* getConfigDir();

    char* getDataDir();

    //char* getImgSrcDir();

    //char* getImgDstDir();

    char* getLogDir();

    char* getModuleDir();

    char* getTempDir();

    char* getTmpDir();

    char* getConfigFile();

    char* getDefaultConfigFile();

    char* getLogFile();

};

/* NEW_TYPE: CCfgContext Pointer */

typedef CCfgContext* CCfgContextPtr_t;

#endif
