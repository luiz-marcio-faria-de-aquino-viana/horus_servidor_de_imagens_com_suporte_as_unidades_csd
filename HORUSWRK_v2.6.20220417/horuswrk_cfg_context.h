/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_context.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_CONTEXT_H
#define __HORUSWRK_CFG_CONTEXT_H       "__HORUSWRK_CFG_CONTEXT_H"

class CCfgContext
{
private:
    pathname_t m_homeDir;                       // home directory
    pathname_t m_binDir;                        // executables directory
    pathname_t m_configDir;                     // config directory
    pathname_t m_dataDir;                       // data directory
    pathname_t m_logDir;                        // log directory
    pathname_t m_tempDir;                       // temp directory
    pathname_t m_tmpDir;                        // tmp directory
    //
    pathname_t m_imgSrcDir;                     // image source directory
    pathname_t m_imgDstDir;                     // image destination directory
    //
    pathname_t m_configFile;                    // configuration file path
    pathname_t m_defaultConfigFile;             // default configuration file path
    //
    pathname_t m_baseDirTableFile;              // directory table file path
    pathname_t m_baseSuperBlockTableFile;       // superblock table file path
    pathname_t m_baseBlockTableFile;            // block table file path
    pathname_t m_baseDataFile;                  // data file path
    //
    pathname_t m_baseDirTableFilePath;          // directory table file path
    pathname_t m_baseSuperBlockTableFilePath;   // superblock table file path
    pathname_t m_baseBlockTableFilePath;        // block table file path
    pathname_t m_baseDataFilePath;              // data file path
    //
    pathname_t m_logFile;                       // log file path

public:
    CCfgContext();
    ~CCfgContext();

    /* Methodes */

    void initDefaults();

    void resetDataLocation(char* currRemoteUnitName);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    char* getHomeDir();

    char* getBinDir();

    char* getConfigDir();

    char* getDataDir();

    char* getImgSrcDir();

    char* getImgDstDir();

    char* getLogDir();

    char* getModuleDir();

    char* getTempDir();

    char* getTmpDir();

    char* getConfigFile();

    char* getDefaultConfigFile();

    char* getBaseDirTableFile(char* data, int datasz);

    char* getBaseSuperBlockTableFile(char* data, int datasz, long diskGroupOid);

    char* getBaseBlockTableFile(char* data, int datasz, long diskGroupOid, long diskDevOid);

    char* getBaseDataFile(char* data, int datasz, long diskGroupOid, long diskDevOid);

    char* getBaseDirTableFilePath(char* data, int datasz);

    char* getBaseSuperBlockTableFilePath(char* data, int datasz, long diskGroupOid);

    char* getBaseBlockTableFilePath(char* data, int datasz, long diskGroupOid, long diskDevOid);

    char* getBaseDataFilePath(char* data, int datasz, long diskGroupOid, long diskDevOid);

    char* getLogFile();

};

/* NEW_TYPE: CCfgContext Pointer */

typedef CCfgContext* CCfgContextPtr_t;

#endif
