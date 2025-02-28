/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_context.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgContext::CCfgContext()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I) CConfig::CConfig()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CConfig()", errmsg);

    /* home directory
     */
    char* p_home_env = getenv(HORUSWRK_HOME);
    if(p_home_env != NULL)
        strNCpyUtil(m_homeDir, p_home_env, PATHNAMESZ);
    else
        strNCpyUtil(m_homeDir, HOME_DIR, PATHNAMESZ);

    initDefaults();
}

CCfgContext::~CCfgContext()
{
    /* nothing todo! */    
}

void CCfgContext::initDefaults()
{
    sbigstr_t errmsg;

    sbigstr_t strTmp;

    sbigstr_t local_time_str;
    getLocalTimeStr(local_time_str);

    /* executables directory
     */
    strNCpyUtil(m_binDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_binDir, (char*)BIN_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.1) BinDir: %s\n", m_binDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* config directory
     */
    strNCpyUtil(m_configDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_configDir, (char*)CONFIG_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.2) ConfigDir: %s\n", m_configDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* data directory
     */
    strNCpyUtil(m_dataDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)DATA_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.3) DataDir: %s\n", m_dataDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* log directory
     */
    strNCpyUtil(m_logDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_logDir, (char*)LOG_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.4) LogDir: %s\n", m_logDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* temp directory
     */
    strNCpyUtil(m_tempDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_tempDir, (char*)TEMP_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.5) TempDir: %s\n", m_tempDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* tmp directory
     */
    strNCpyUtil(m_tmpDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_tmpDir, (char*)TMP_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.6) TmpDir: %s\n", m_tmpDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* config file
     */
    strNCpyUtil(m_configFile, m_configDir, PATHNAMESZ);
    strNCatUtil(m_configFile, (char*)CONFIG_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.7) ConfigFile: %s\n", m_configFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* default config file
     */
    strNCpyUtil(m_defaultConfigFile, m_configDir, PATHNAMESZ);
    strNCatUtil(m_defaultConfigFile, (char*)DEFAULT_CONFIG_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.8) DefaultConfigFile: %s\n", m_defaultConfigFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* log file
     */
    strNCpyUtil(strTmp, m_logDir, PATHNAMESZ);
    strNCatUtil(strTmp, (char*)LOG_FILE, PATHNAMESZ);
    sprintf(m_logFile, strTmp, local_time_str);

    sprintf(errmsg, "I.13) LogFile: %s\n", m_logFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base dir table file
     */
    strNCpyUtil(m_baseDirTableFile, (char*)DEFAULT_DIR_TABLE_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.9) BaseDirTableFile: %s\n", m_baseDirTableFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base superblock table file
     */
    strNCpyUtil(m_baseSuperBlockTableFile, (char*)DEFAULT_SUPERBLOCK_TABLE_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.10) BaseSuperBlockTableFile: %s\n", m_baseSuperBlockTableFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base block table file
     */
    strNCpyUtil(m_baseBlockTableFile, (char*)DEFAULT_BLOCK_TABLE_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.11) BaseBlockTableFile: %s\n", m_baseBlockTableFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base data file
     */
    strNCpyUtil(m_baseDataFile, (char*)DEFAULT_DATA_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.12) BaseDataFile: %s\n", m_baseDataFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base dir table file path
     */
    //strNCpyUtil(m_baseDirTableFilePath, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_baseDirTableFilePath, m_baseDirTableFile, PATHNAMESZ);
    //sprintf(errmsg, "I.9) BaseDirTableFilePath: %s\n", m_baseDirTableFilePath);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base superblock table file path
     */
    //strNCpyUtil(m_baseSuperBlockTableFilePath, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_baseSuperBlockTableFilePath, m_baseSuperBlockTableFile, PATHNAMESZ);
    //sprintf(errmsg, "I.10) BaseSuperBlockTableFilePath: %s\n", m_baseSuperBlockTableFilePath);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base block table file path
     */
    //strNCpyUtil(m_baseBlockTableFilePath, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_baseBlockTableFilePath, m_baseBlockTableFile, PATHNAMESZ);
    //sprintf(errmsg, "I.11) BaseBlockTableFilePath: %s\n", m_baseBlockTableFilePath);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base data file path
     */
    //strNCpyUtil(m_baseDataFilePath, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_baseDataFilePath, m_baseDataFile, PATHNAMESZ);
    //sprintf(errmsg, "I.12) BaseDataFilePath: %s\n", m_baseDataFilePath);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image source
     */
    //strNCpyUtil(m_imgSrcDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgSrcDir, IMGSRC_DIR, PATHNAMESZ);
    //sprintf(errmsg, "I.14) ImgSrcDir: %s\n", m_imgSrcDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image destination
     */
    //strNCpyUtil(m_imgDstDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgDstDir, IMGDST_DIR, PATHNAMESZ);
    //sprintf(errmsg, "I.15) ImgDstDir: %s\n", m_imgDstDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

}

void CCfgContext::resetDataLocation(char* currRemoteUnitName)
{
    sbigstr_t errmsg;

    /* data directory
     */
    strNCpyUtil(m_dataDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)DATA_DIR, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)currRemoteUnitName, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)"/", PATHNAMESZ);
    sprintf(errmsg, "II.1) DataDir: %s\n", m_dataDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "resetDataLocation()", errmsg);

    /* base dir table file path
     */
    strNCpyUtil(m_baseDirTableFilePath, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_baseDirTableFilePath, m_baseDirTableFile, PATHNAMESZ);
    sprintf(errmsg, "II.6) BaseDirTableFilePath: %s\n", m_baseDirTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base superblock table file path
     */
    strNCpyUtil(m_baseSuperBlockTableFilePath, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_baseSuperBlockTableFilePath, m_baseSuperBlockTableFile, PATHNAMESZ);
    sprintf(errmsg, "II.7) BaseSuperBlockTableFilePath: %s\n", m_baseSuperBlockTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base block table file path
     */
    strNCpyUtil(m_baseBlockTableFilePath, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_baseBlockTableFilePath, m_baseBlockTableFile, PATHNAMESZ);
    sprintf(errmsg, "II.8) BaseBlockTableFilePath: %s\n", m_baseBlockTableFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* base data file path
     */
    strNCpyUtil(m_baseDataFilePath, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_baseDataFilePath, m_baseDataFile, PATHNAMESZ);
    sprintf(errmsg, "II.9) BaseDataFilePath: %s\n", m_baseDataFilePath);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image source
     */
    strNCpyUtil(m_imgSrcDir, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_imgSrcDir, IMGSRC_DIR, PATHNAMESZ);
    sprintf(errmsg, "II.10) ImgSrcDir: %s\n", m_imgSrcDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "resetDataLocation()", errmsg);

    /* image destination
     */
    strNCpyUtil(m_imgDstDir, m_dataDir, PATHNAMESZ);
    strNCatUtil(m_imgDstDir, IMGDST_DIR, PATHNAMESZ);
    sprintf(errmsg, "II.11) ImgDstDir: %s\n", m_imgDstDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSWRK_CFG_CONTEXT_H, "resetDataLocation()", errmsg);

}

void CCfgContext::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\n- HomeDir=%s\n- BinDir=%s\n- ConfigDir=%s\n- DataDir=%s\n- LogDir=%s\n- TempDir=%s\n- TmpDir=%s\n- ImgSrcDir=%s\n- ImgDstDir=%s\n- ConfigFile=%s\n- DefaultConfigFile=%s\n- BaseDirTableFile=%s\n- BaseSuperBlockTableFile=%s\n- BaseBlockTableFile=%s\n- BaseDataFile=%s\n- BaseDirTableFilePath=%s\n- BaseSuperBlockTableFilePath=%s\n- BaseBlockTableFilePath=%s\n- BaseDataFilePath=%s\n- LogFile=%s\n\n",
        m_homeDir,
        m_binDir,
        m_configDir,
        m_dataDir,
        m_logDir,
        m_tempDir,
        m_tmpDir,
        m_imgSrcDir,
        m_imgDstDir,
        m_configFile,
        m_defaultConfigFile,
        m_baseDirTableFile,
        m_baseSuperBlockTableFile,
        m_baseBlockTableFile,
        m_baseDataFile,
        m_baseDirTableFilePath,
        m_baseSuperBlockTableFilePath,
        m_baseBlockTableFilePath,
        m_baseDataFilePath,
        m_logFile);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

char* CCfgContext::getHomeDir()
{
    return m_homeDir;
}

char* CCfgContext::getBinDir()
{
    return m_binDir;
}

char* CCfgContext::getConfigDir()
{
    return m_configDir;
}

char* CCfgContext::getDataDir()
{
    return m_dataDir;
}

char* CCfgContext::getImgSrcDir()
{
    return m_imgSrcDir;
}

char* CCfgContext::getImgDstDir()
{
    return m_imgDstDir;
}

char* CCfgContext::getLogDir()
{
    return m_logDir;
}

char* CCfgContext::getTempDir()
{
    return m_tempDir;
}

char* CCfgContext::getTmpDir()
{
    return m_tmpDir;
}

char* CCfgContext::getConfigFile()
{
    return m_configFile;
}

char* CCfgContext::getDefaultConfigFile()
{
    return m_defaultConfigFile;
}

char* CCfgContext::getBaseDirTableFile(char* data, int datasz)
{
    strNCpyUtil(data, m_baseDirTableFile, datasz);
    return data;
}

char* CCfgContext::getBaseSuperBlockTableFile(char* data, int datasz, long diskGroupOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseSuperBlockTableFile, diskGroupOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getBaseBlockTableFile(char* data, int datasz, long diskGroupOid, long diskDevOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseBlockTableFile, diskGroupOid, diskDevOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getBaseDataFile(char* data, int datasz, long diskGroupOid, long diskDevOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseDataFile, diskGroupOid, diskDevOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getBaseDirTableFilePath(char* data, int datasz)
{
    strNCpyUtil(data, m_baseDirTableFilePath, datasz);
    return data;
}

char* CCfgContext::getBaseSuperBlockTableFilePath(char* data, int datasz, long diskGroupOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseSuperBlockTableFilePath, diskGroupOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getBaseBlockTableFilePath(char* data, int datasz, long diskGroupOid, long diskDevOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseBlockTableFilePath, diskGroupOid, diskDevOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getBaseDataFilePath(char* data, int datasz, long diskGroupOid, long diskDevOid)
{
    bigstr_t strTmp;
    sprintf(strTmp, m_baseDataFilePath, diskGroupOid, diskDevOid);
    strNCpyUtil(data, strTmp, datasz);
    return data;
}

char* CCfgContext::getLogFile()
{
    return m_logFile;
}
