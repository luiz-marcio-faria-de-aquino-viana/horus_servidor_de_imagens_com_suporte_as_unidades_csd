/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_context.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCfgContext::CCfgContext()
{
    bigstr_t errmsg;

    sprintf(errmsg, "I) CConfig::CConfig()\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CConfig()", errmsg);

    /* home directory
     */
    char* p_home_env = getenv(HORUSSRV_HOME);
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
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* config directory
     */
    strNCpyUtil(m_configDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_configDir, (char*)CONFIG_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.2) ConfigDir: %s\n", m_configDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* data directory
     */
    strNCpyUtil(m_dataDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)DATA_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.3) DataDir: %s\n", m_dataDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* log directory
     */
    strNCpyUtil(m_logDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_logDir, (char*)LOG_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.4) LogDir: %s\n", m_logDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* temp directory
     */
    strNCpyUtil(m_tempDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_tempDir, (char*)TEMP_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.5) TempDir: %s\n", m_tempDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* tmp directory
     */
    strNCpyUtil(m_tmpDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_tmpDir, (char*)TMP_DIR, PATHNAMESZ);
    sprintf(errmsg, "I.6) TmpDir: %s\n", m_tmpDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* config file
     */
    strNCpyUtil(m_configFile, m_configDir, PATHNAMESZ);
    strNCpyUtil(m_configFile, (char*)CONFIG_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.7) ConfigFile: %s\n", m_configFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* default config file
     */
    strNCpyUtil(m_defaultConfigFile, m_configDir, PATHNAMESZ);
    strNCpyUtil(m_defaultConfigFile, (char*)DEFAULT_CONFIG_FILE, PATHNAMESZ);
    sprintf(errmsg, "I.8) DefaultConfigFile: %s\n", m_defaultConfigFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* log file
     */
    strNCpyUtil(strTmp, m_logDir, PATHNAMESZ);
    strNCatUtil(strTmp, (char*)LOG_FILE, PATHNAMESZ);
    sprintf(m_logFile, strTmp, local_time_str);

    sprintf(errmsg, "I.9) LogFile: %s\n", m_logFile);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image source
     */
    //strNCpyUtil(m_imgSrcDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgSrcDir, IMGSRC_DIR, PATHNAMESZ);
    //sprintf(errmsg, "I.10) ImgSrcDir: %s\n", m_imgSrcDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image destination
     */
    //strNCpyUtil(m_imgDstDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgDstDir, IMGDST_DIR, PATHNAMESZ);
    //sprintf(errmsg, "I.11) ImgDstDir: %s\n", m_imgDstDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

}

void CCfgContext::resetDataLocation(char* hostServerName)
{
    sbigstr_t errmsg;

    /* data directory
     */
    strNCpyUtil(m_dataDir, m_homeDir, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)DATA_DIR, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)hostServerName, PATHNAMESZ);
    strNCatUtil(m_dataDir, (char*)"/", PATHNAMESZ);
    sprintf(errmsg, "II.1) DataDir: %s\n", m_dataDir);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image source
     */
    //strNCpyUtil(m_imgSrcDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgSrcDir, IMGSRC_DIR, PATHNAMESZ);
    //sprintf(errmsg, "II.2) ImgSrcDir: %s\n", m_imgSrcDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

    /* image destination
     */
    //strNCpyUtil(m_imgDstDir, m_dataDir, PATHNAMESZ);
    //strNCatUtil(m_imgDstDir, IMGDST_DIR, PATHNAMESZ);
    //sprintf(errmsg, "II.3) ImgDstDir: %s\n", m_imgDstDir);
    //warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CFG_CONTEXT_H, "CCfgContext()", errmsg);

}

void CCfgContext::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\n- HomeDir=%s\n- BinDir=%s\n- ConfigDir=%s\n- DataDir=%s\n- LogDir=%s\n- TempDir=%s\n- TmpDir=%s\n- ConfigFile=%s\n- DefaultConfigFile=%s\n- LogFile=%s\n\n",
        m_homeDir,
        m_binDir,
        m_configDir,
        m_dataDir,
        m_logDir,
        m_tempDir,
        m_tmpDir,
        m_configFile,
        m_defaultConfigFile,
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

//char* CCfgContext::getImgSrcDir()
//{
//    return m_imgSrcDir;
//}

//char* CCfgContext::getImgDstDir()
//{
//    return m_imgDstDir;
//}

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

char* CCfgContext::getLogFile()
{
    return m_logFile;
}
