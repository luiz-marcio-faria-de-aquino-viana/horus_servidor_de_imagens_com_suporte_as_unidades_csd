/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_diskdev.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgDiskDev::CCfgDiskDev()
{
    init();
}
    
CCfgDiskDev::~CCfgDiskDev()
{
    terminate();
}

/* Methodes */

void CCfgDiskDev::initDefaults()
{
    m_oid = DBNULL_LONG;
    m_remoteUnitOid = DBNULL_LONG;
    m_diskGroupOid = DBNULL_LONG;
    //m_numOfBlocks = DBNULL_LONG;
    //m_blockSize = DBNULL_LONG;
    m_lastUpdate = DBNULL_LONG;

    strSetEmptyUtil(m_name);
    strSetEmptyUtil(m_blockTableFile);
    strSetEmptyUtil(m_dataFile);

    strSetEmptyUtil(m_blockTableFilePath);
    strSetEmptyUtil(m_dataFilePath);

    m_maxNumDskBlock = 0;
}

void CCfgDiskDev::init()
{
    m_pRemoteUnit = NULL;
    m_pDiskGroup = NULL;

    initDefaults();
}

void CCfgDiskDev::terminate()
{
    /* nothing todo! */
}

void CCfgDiskDev::loadConfig(void* pRemoteUnit, void* pDiskGroup, int posDiskGroup, int posDiskDev, CCfgConfigTag* pConfigTag)
{
    CCfgContext* pContext = gAppMain.getContextPtr();

    long currentTimestamp = getCurrentTimestamp();

    config_tag_t* p = NULL;

    bigstr_t tag;

    m_pRemoteUnit = pRemoteUnit;
    m_pDiskGroup = pDiskGroup;

    //DISKDEV
    sprintf(tag, DEF_TAGTXT_DISKDEV_OID, posDiskGroup, posDiskDev);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_oid = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_DISKDEV_NAME, posDiskGroup, posDiskDev);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_name, p->tag_value, BIGSTRSZ);

    sprintf(tag, DEF_TAGTXT_DISKDEV_REMOTEUNIT_OID, posDiskGroup, posDiskDev);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_remoteUnitOid = atol(p->tag_value);

    //DISK GROUP DATA
    m_diskGroupOid = ((CCfgDiskGroup*)m_pDiskGroup)->getOid();
    //m_numOfBlocks = ((CCfgDiskGroup*)m_pDiskGroup)->getNumOfBlocks();
    //m_blockSize = ((CCfgDiskGroup*)m_pDiskGroup)->getBlockSize();        
    m_lastUpdate = currentTimestamp;        

    //BLOCK TABLE FILE
    pContext->getBaseBlockTableFile(m_blockTableFile, BIGSTRSZ, m_diskGroupOid, m_oid);
    pContext->getBaseBlockTableFilePath(m_blockTableFilePath, PATHNAMESZ, m_diskGroupOid, m_oid);

    //DATA FILE
    pContext->getBaseDataFile(m_dataFile, BIGSTRSZ, m_diskGroupOid, m_oid);
    pContext->getBaseDataFilePath(m_dataFilePath, PATHNAMESZ, m_diskGroupOid, m_oid);

    this->debug(DEBUG_LEVEL_05, __HORUSWRK_CFG_DISKDEV_H, (char*)"loadConfig()");
}

void CCfgDiskDev::setData(CCfgDiskDev* pDiskDev)
{
    m_pRemoteUnit = pDiskDev->getRemoteUnitPtr();
    m_pDiskGroup = pDiskDev->getDiskGroupPtr();

    m_oid = pDiskDev->getOid();
    m_remoteUnitOid = pDiskDev->getRemoteUnitOid();
    m_diskGroupOid = pDiskDev->getDiskGroupOid();
    //m_numOfBlocks = pDiskDev->getNumOfBlocks();
    //m_blockSize = pDiskDev->getBlockSize();
    m_lastUpdate = pDiskDev->getLastUpdate();

    strNCpyUtil(m_name, (char*)pDiskDev->getName(), STRSZ);
    strNCpyUtil(m_blockTableFile, (char*)pDiskDev->getBlockTableFile(), STRSZ);
    strNCpyUtil(m_dataFile, (char*)pDiskDev->getDataFile(), STRSZ);

    strNCpyUtil(m_blockTableFilePath, (char*)pDiskDev->getBlockTableFilePath(), PATHNAMESZ);
    strNCpyUtil(m_dataFilePath, (char*)pDiskDev->getDataFilePath(), PATHNAMESZ);

    m_maxNumDskBlock = pDiskDev->getMaxNumDskBlock();
}

void CCfgDiskDev::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgDiskDev::Oid=%ld,RemoteUnitOid=%ld,DiskGroupOid=%ld,LastUpdate=%ld,Name=%s,BlockTableFile=%s,DataFile=%s,BlockTableFilePath=%s,DataFilePath=%s,MaxNumDskBlock=%d,\n",
        m_oid,
        m_remoteUnitOid,
        m_diskGroupOid,
        m_lastUpdate,
        m_name,
        m_blockTableFile,
        m_dataFile,
        m_blockTableFilePath,
        m_dataFilePath,
        m_maxNumDskBlock);
    //sprintf(
    //    errmsg,
    //    "\nCCfgDiskDev::Oid=%ld,RemoteUnitOid=%ld,DiskGroupOid=%ld,NumOfBlocks=%ld,BlockSize=%ld,LastUpdate=%ld,Name=%s,BlockTableFile=%s,DataFile=%s,BlockTableFilePath=%s,DataFilePath=%s,MaxNumDskBlock=%d,\n",
    //    m_oid,
    //    m_remoteUnitOid,
    //    m_diskGroupOid,
    //    m_numOfBlocks,
	//    m_blockSize,
    //    m_lastUpdate,
    //    m_name,
    //    m_blockTableFile,
    //    m_dataFile,
    //    m_blockTableFilePath,
    //    m_dataFilePath,
    //    m_maxNumDskBlock);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

void* CCfgDiskDev::getRemoteUnitPtr()
{
    return m_pRemoteUnit;
}

void* CCfgDiskDev::getDiskGroupPtr()
{
    return m_pDiskGroup;
}

long CCfgDiskDev::getOid()
{
    return m_oid;
}

long CCfgDiskDev::getRemoteUnitOid()
{
    return m_remoteUnitOid;
}

long CCfgDiskDev::getDiskGroupOid()
{
    return m_diskGroupOid;
}

//long CCfgDiskDev::getNumOfBlocks()
//{
//    return m_numOfBlocks;
//}

//long CCfgDiskDev::getBlockSize()
//{
//	return m_blockSize;
//}

long CCfgDiskDev::getLastUpdate()
{
    return m_lastUpdate;
}

char* CCfgDiskDev::getName()
{
    return m_name;
}

char* CCfgDiskDev::getBlockTableFile()
{
    return m_blockTableFile;
}

char* CCfgDiskDev::getDataFile()
{
    return m_dataFile;
}

char* CCfgDiskDev::getBlockTableFilePath()
{
    return m_blockTableFilePath;
}

char* CCfgDiskDev::getDataFilePath()
{
    return m_dataFilePath;
}

int CCfgDiskDev::getMaxNumDskBlock()
{
    return m_maxNumDskBlock;
}
