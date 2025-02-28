/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskgroup.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskDiskGroup::CDskDiskGroup(
    void* pRemoteUnit,
    long oid,
    long remoteUnitOid,
    long numOfDisks,
    long numOfCopies,
    //long numOfSuperBlocks,
    //long numOfBlocks,
    //long blockSize,
    char* name,
    char* superBlockTableFile,
    char* superBlockTableFilePath)
{
    m_pRemoteUnit = pRemoteUnit;

    init(oid,
         remoteUnitOid,
         numOfDisks,
         numOfCopies,
         //numOfSuperBlocks,
         //numOfBlocks,
         //blockSize,
         name,
         superBlockTableFile,
         superBlockTableFilePath);
}

CDskDiskGroup::~CDskDiskGroup()
{
    terminate();
}

// init(): initiate disk group
void CDskDiskGroup::init(
    long oid,
    long remoteUnitOid,
    long numOfDisks,
    long numOfCopies,
    //long numOfSuperBlocks,
    //long numOfBlocks,
    //long blockSize,
    char* name,
    char* superBlockTableFile,
    char* superBlockTableFilePath)
{
    m_oid = oid;
    m_remoteUnitOid = remoteUnitOid;
    m_numOfDisks = numOfDisks;
    m_numOfCopies = numOfCopies;
    //m_numOfSuperBlocks = numOfSuperBlocks;
    //m_numOfBlocks = numOfBlocks;
    //m_blockSize = blockSize;
    strNCpyUtil(m_name, name, BIGSTRSZ);
    strNCpyUtil(m_superBlockTableFile, superBlockTableFile, BIGSTRSZ);
    
    sprintf(m_key, "%ld", m_oid);

    strNCpyUtil(m_superBlockTableFilePath, superBlockTableFilePath, PATHNAMESZ);

    //m_maxNumDskSuperBlock = (int)numOfSuperBlocks;
    m_superBlockMan = new CDskSuperBlockMan(
        DEF_DSK_NUMOFSUPERBLOCKS, 
        m_superBlockTableFile, 
        m_superBlockTableFilePath);

    m_maxNumDiskDev = (int)m_numOfDisks; 
    m_currNumDiskDev = 0; 
    m_arrDiskDev = (CDskDiskDevPtr_t*)allocDataArray(sizeof(CDskDiskDevPtr_t), m_maxNumDiskDev);
}

// terminate(): terminate disk group
void CDskDiskGroup::terminate()
{
    if(m_superBlockMan != NULL)
        delete(m_superBlockMan);

    if(m_arrDiskDev != NULL) {
        for(int i = 0; i < m_currNumDiskDev; i++) {
            CDskDiskDev* p = m_arrDiskDev[i];
            p->terminate();
        } 
        freeDataArray(m_arrDiskDev);
    }
}

/* Methodes */

// addDiskDev(): add new disk group
// oid - disk device oid
// name - disk device name
// blockTableFile - disk device block table file
// dataFile - disk device data file
// blockTableFilePath - disk device block table file path
// dataFilePath - disk device data file path
CDskDiskDev* CDskDiskGroup::addDiskDev(
    long oid,
    char* name,
    char* blockTableFile,
    char* dataFile,
    char* blockTableFilePath,
    char* dataFilePath)
{
    CDskDiskDev* pDiskDev = NULL;

    long currTimestamp = getCurrentTimestamp();

    if(m_currNumDiskDev < m_maxNumDiskDev) 
    {
        long posDiskDev = m_currNumDiskDev;

        pDiskDev = new CDskDiskDev(
            m_pRemoteUnit,
            this,
            oid,
            ((CCfgRemoteUnit*)m_pRemoteUnit)->getOid(),
            this->getOid(),
            posDiskDev,
            currTimestamp,
            name,
            blockTableFile,
            dataFile,
            blockTableFilePath,
            dataFilePath);
        m_arrDiskDev[m_currNumDiskDev] = pDiskDev;
        m_currNumDiskDev += 1;
    }
    return pDiskDev;
}

/* Getters/Setters */

void* CDskDiskGroup::getRemoteUnitPtr()
{
    return m_pRemoteUnit;
}

long CDskDiskGroup::getOid()
{
    return m_oid;
}

long CDskDiskGroup::getRemoteUnitOid()
{
    return m_remoteUnitOid;
}

long CDskDiskGroup::getNumOfDisks()
{
    return m_numOfDisks;    
}

long CDskDiskGroup::getNumOfCopies()
{
    return m_numOfCopies;        
}

//long CDskDiskGroup::getNumOfSuperBlocks()
//{
//    return m_numOfSuperBlocks;
//}

//long CDskDiskGroup::getNumOfBlocks()
//{
//    return m_numOfBlocks;
//}

//long CDskDiskGroup::getBlockSize()
//{
//    return m_blockSize;
//}

char* CDskDiskGroup::getName()
{
    return m_name;    
}

char* CDskDiskGroup::getSuperBlockTableFile()
{
    return m_superBlockTableFile;    
}

char* CDskDiskGroup::getKey()
{
    return m_key;    
}

char* CDskDiskGroup::getSuperBlockTableFilePath()
{
    return m_superBlockTableFilePath;    
}

CDskSuperBlockMan* CDskDiskGroup::getSuperBlockMan()
{
    return m_superBlockMan;    
}

//int CDskDiskGroup::getMaxNumDskSuperBlock()
//{
//    return m_maxNumDskSuperBlock;    
//}

// DISKDEV
//
CDskDiskDev* CDskDiskGroup::getDiskDevAtPtr(int pos)
{
    if(pos < m_currNumDiskDev) {
        CDskDiskDev* p = m_arrDiskDev[pos];
        return p;
    }   
    return NULL; 
}

CDskDiskDev* CDskDiskGroup::getDiskDevPtr(long oid)
{
    for(int i = 0; i < m_currNumDiskDev; i++) {
        CDskDiskDev* p = m_arrDiskDev[i];
        if(p->getOid() == oid)
            return p;
    }   
    return NULL; 
}

CDskDiskDev* CDskDiskGroup::getDiskDevPtr(char* name)
{
    for(int i = 0; i < m_currNumDiskDev; i++) {
        CDskDiskDev* p = m_arrDiskDev[i];
        if( strNCmpCaseUtil(p->getName(), name, STRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 )
            return p;
    }   
    return NULL;     
}

int CDskDiskGroup::getMaxNumDiskDev()
{
    return m_maxNumDiskDev;
}

int CDskDiskGroup::getCurrNumDiskDev()
{
    return m_currNumDiskDev;
}
