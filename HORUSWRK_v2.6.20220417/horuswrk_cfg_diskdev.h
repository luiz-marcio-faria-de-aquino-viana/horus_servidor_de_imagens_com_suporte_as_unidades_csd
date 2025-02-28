/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_diskdev.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 26/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_DISKDEV_H
#define __HORUSWRK_CFG_DISKDEV_H        "__HORUSWRK_CFG_DISKDEV_H"

class CCfgDiskDev
{
private:
    void* m_pRemoteUnit;                // point to remote disk device unit
    void* m_pDiskGroup;                 // point to disk group

    long m_oid;                         // disk device unit id
    long m_remoteUnitOid;               // remote disk device unit id
    long m_diskGroupOid;                // disk group oid
    //long m_numOfBlocks;                 // number of blocks
	//long m_blockSize;                   // block size
    long m_lastUpdate;                  // last disk device initialization
    str_t m_name;                       // disk device name
    str_t m_blockTableFile;             // superblock table file
    str_t m_dataFile;                   // data file

    pathname_t m_blockTableFilePath;    // superblock table file path
    pathname_t m_dataFilePath;          // data file path

    int m_maxNumDskBlock;               // maximum number of disk blocks

public:
    CCfgDiskDev();
    ~CCfgDiskDev();

    /* Methodes */

    void initDefaults();

    void init();

    void terminate();

    void loadConfig(void* pRemoteUnit, void* pDiskGroup, int posDiskGroup, int posDiskDev, CCfgConfigTag* pConfigTag);

    void setData(CCfgDiskDev* pDiskDev);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    void* getRemoteUnitPtr();

    void* getDiskGroupPtr();

    long getOid();

    long getRemoteUnitOid();

    long getDiskGroupOid();

    //long getNumOfBlocks();
    
	//long getBlockSize();

    long getLastUpdate();

    char* getName();

    char* getBlockTableFile();

    char* getDataFile();

    char* getBlockTableFilePath();

    char* getDataFilePath();

    int getMaxNumDskBlock();

};

/* NEW_TYPE: CCfgDiskDev Pointer */

typedef CCfgDiskDev* CCfgDiskDevPtr_t;

#endif
