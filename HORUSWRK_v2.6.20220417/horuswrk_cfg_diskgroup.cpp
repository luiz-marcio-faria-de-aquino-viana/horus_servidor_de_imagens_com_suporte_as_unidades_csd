/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_diskgroup.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 26/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgDiskGroup::CCfgDiskGroup()
{
    init();
}

CCfgDiskGroup::~CCfgDiskGroup()
{
    terminate();
}

/* Methodes */

void CCfgDiskGroup::init()
{
    m_pRemoteUnit = NULL;

    initDefaults();
}

void CCfgDiskGroup::terminate()
{
    if(m_arrDiskDev != NULL)
        freeDataArray(m_arrDiskDev);
}

void CCfgDiskGroup::initDefaults()
{
    m_oid = DBNULL_LONG;
    m_remoteUnitOid = DBNULL_LONG;
	m_numOfDisks = DBNULL_LONG;
    m_numOfCopies = DBNULL_LONG;
    //m_numOfSuperBlocks = DBNULL_LONG;
    //m_numOfBlocks = DBNULL_LONG;
    //m_blockSize = DBNULL_LONG;

    strSetEmptyUtil(m_name);
    strSetEmptyUtil(m_superBlockTableFile);
    strSetEmptyUtil(m_superBlockTableFilePath);

    m_arrDiskDev = NULL;
    m_szArrDiskDev = 0;
}

void CCfgDiskGroup::loadConfig(int posDiskGroup, CCfgConfigTag* pConfigTag)
{
    CCfgContext* pContext = gAppMain.getContextPtr();

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    config_tag_t* p = NULL;

    bigstr_t tag;

    //DISKGROUP
    sprintf(tag, DEF_TAGTXT_DISKGROUP_OID, posDiskGroup);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_oid = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_DISKGROUP_REMOTEUNIT_OID, posDiskGroup);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_remoteUnitOid = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_DISKGROUP_NUMOFDISKS, posDiskGroup);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_numOfDisks = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_DISKGROUP_NUMOFCOPIES, posDiskGroup);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        m_numOfCopies = atol(p->tag_value);

    //sprintf(tag, DEF_TAGTXT_DISKGROUP_NUMBEROFSUPERBLOCKS, posDiskGroup);
    //p = pConfigTag->findConfigTagByName(tag);
    //if(p != NULL)
    //    m_numOfSuperBlocks = atol(p->tag_value);

    //sprintf(tag, DEF_TAGTXT_DISKGROUP_NUMBEROFBLOCKS, posDiskGroup);
    //p = pConfigTag->findConfigTagByName(tag);
    //if(p != NULL)
    //    m_numOfBlocks = atol(p->tag_value);

    //sprintf(tag, DEF_TAGTXT_DISKGROUP_BLOCKSIZE, posDiskGroup);
    //p = pConfigTag->findConfigTagByName(tag);
    //if(p != NULL)
    //    m_blockSize = atol(p->tag_value);

    sprintf(tag, DEF_TAGTXT_DISKGROUP_NAME, posDiskGroup);
    p = pConfigTag->findConfigTagByName(tag);
    if(p != NULL)
        strNCpyUtil(m_name, p->tag_value, BIGSTRSZ);

    //REMOTE UNIT DATA
    m_pRemoteUnit = pConfig->getRemoteUnitPtr(m_remoteUnitOid);

    //SUPERBLOCK TABLE FILE
    pContext->getBaseSuperBlockTableFile(m_superBlockTableFile, BIGSTRSZ, m_oid);
    pContext->getBaseSuperBlockTableFilePath(m_superBlockTableFilePath, PATHNAMESZ, m_oid);

    //DISKDEV
    m_szArrDiskDev = (int)m_numOfDisks;
    m_arrDiskDev = (CCfgDiskDev*)allocDataArray(sizeof(CCfgDiskDev), m_szArrDiskDev);
    for(int i = 0; i < m_szArrDiskDev; i++) {
        CCfgDiskDev* p = & m_arrDiskDev[i];
        p->loadConfig(m_pRemoteUnit, this, posDiskGroup, i, pConfigTag);
    }
}

void CCfgDiskGroup::setData(CCfgDiskGroup* pDiskGroup)
{
    m_pRemoteUnit = pDiskGroup->getRemoteUnitPtr();

    m_oid = pDiskGroup->getOid();
    m_remoteUnitOid = pDiskGroup->getRemoteUnitOid();
	m_numOfDisks = pDiskGroup->getNumOfDisks();
    m_numOfCopies = pDiskGroup->getNumOfCopies();
    //m_numOfSuperBlocks = pDiskGroup->getNumOfSuperBlocks();
    //m_numOfBlocks = pDiskGroup->getNumOfBlocks();
    //m_blockSize = pDiskGroup->getBlockSize();
    strNCpyUtil(m_name, pDiskGroup->getName(), BIGSTRSZ);
    strNCpyUtil(m_superBlockTableFile, pDiskGroup->getSuperBlockTableFile(), BIGSTRSZ);

    strNCpyUtil(m_superBlockTableFilePath, pDiskGroup->getSuperBlockTableFilePath(), PATHNAMESZ);

    //DISKDEV
    m_szArrDiskDev = (int)m_numOfDisks;
    m_arrDiskDev = (CCfgDiskDev*)allocDataArray(sizeof(CCfgDiskDev), m_szArrDiskDev);
    for(int i = 0; i < m_szArrDiskDev; i++) {
        CCfgDiskDev* pSrc = pDiskGroup->getDiskDevAtPtr(i);

        CCfgDiskDev* pDst = & m_arrDiskDev[i];
        pDst->setData(pSrc);
    }
}

void CCfgDiskGroup::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgDiskGroup::Oid=%ld,RemoteUnitOid=%ld,NumOfDisks=%ld,NumOfCopies=%ld,Name=%s,SuperBlockTableFile=%s,SuperBlockTableFilePath=%s,szArrDiskDev=%d\n",
        m_oid,
        m_remoteUnitOid,
	    m_numOfDisks,
        m_numOfCopies,
        m_name,
        m_superBlockTableFile,
        m_superBlockTableFilePath,
        m_szArrDiskDev); 
    warnMsg(debugLevel, className, methodName, errmsg);

    /*
    sprintf(
        errmsg,
        "\nCCfgDiskGroup::Oid=%ld,RemoteUnitOid=%ld,NumOfDisks=%ld,NumOfCopies=%ld,NumOfSuperBlocks=%ld,NumOfBlocks=%ld,BlockSize=%ld,Name=%s,SuperBlockTableFile=%s,SuperBlockTableFilePath=%s,szArrDiskDev=%d\n",
        m_oid,
        m_remoteUnitOid,
	    m_numOfDisks,
        m_numOfCopies,
        m_numOfSuperBlocks,
        m_numOfBlocks,
	    m_blockSize,
        m_name,
        m_superBlockTableFile,
        m_superBlockTableFilePath,
        m_szArrDiskDev); 
    warnMsg(debugLevel, className, methodName, errmsg);
    */

    for(int i = 0; i < m_szArrDiskDev; i++) {
        CCfgDiskDev* p = & m_arrDiskDev[i];
        p->debug(debugLevel, className, methodName);
    }        
}

/* Getters/Settes */

void* CCfgDiskGroup::getRemoteUnitPtr()
{
    return m_pRemoteUnit;
}

long CCfgDiskGroup::getOid()
{
    return m_oid;
}

long CCfgDiskGroup::getRemoteUnitOid()
{
	return m_remoteUnitOid;
}

long CCfgDiskGroup::getNumOfDisks()
{
	return m_numOfDisks;
}

long CCfgDiskGroup::getNumOfCopies()
{
    return m_numOfCopies;
}

//long CCfgDiskGroup::getNumOfSuperBlocks()
//{
//    return m_numOfSuperBlocks;
//}

//long CCfgDiskGroup::getNumOfBlocks()
//{
//    return m_numOfBlocks;
//}

//long CCfgDiskGroup::getBlockSize()
//{
//    return m_blockSize;
//}

char* CCfgDiskGroup::getName()
{
    return m_name;
}

char* CCfgDiskGroup::getSuperBlockTableFile()
{
    return m_superBlockTableFile;
}

char* CCfgDiskGroup::getSuperBlockTableFilePath()
{
    return m_superBlockTableFilePath;
}

CCfgDiskDev* CCfgDiskGroup::getArrDiskDevPtr()
{
    return m_arrDiskDev;
}

int CCfgDiskGroup::getSzArrDiskDev()
{
    return m_szArrDiskDev; 
}

/* GET_DISK_DEV */

CCfgDiskDev* CCfgDiskGroup::getDiskDevAtPtr(int pos)
{
    if(pos < m_szArrDiskDev) {
        CCfgDiskDev* p = & m_arrDiskDev[pos];
        return p;
    }
    return NULL;
}

CCfgDiskDev* CCfgDiskGroup::getDiskDevPtr(long oid)
{
    for(int i = 0; i < m_szArrDiskDev; i++) {
        CCfgDiskDev* p = & m_arrDiskDev[i];
        if(p->getOid() == oid)
            return p;
    }
    return NULL;
}

CCfgDiskDev* CCfgDiskGroup::getDiskDevPtr(char* name)
{
    for(int i = 0; i < m_szArrDiskDev; i++) {
        CCfgDiskDev* p = & m_arrDiskDev[i];
        if( strNCmpCaseUtil(p->getName(), name, BIGSTRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 ) 
            return p;
    }
    return NULL;
}
