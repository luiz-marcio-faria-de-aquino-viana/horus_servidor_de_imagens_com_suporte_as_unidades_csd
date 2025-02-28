/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_diskgroup.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_DISKGROUP_H
#define __HORUSWRK_CFG_DISKGROUP_H        "__HORUSWRK_CFG_DISKGROUP_H"

class CCfgDiskGroup
{
private:
    void* m_pRemoteUnit;                        // point to remote disk device unit

    long m_oid;                                 // diskgroup oid
    long m_remoteUnitOid;                       // remote disk device unit id
	long m_numOfDisks;                          // number disk device
    long m_numOfCopies;                         // number copies
    //long m_numOfSuperBlocks;                    // number of superblocks
    //long m_numOfBlocks;                         // number of blocks
	//long m_blockSize;                           // block size
    bigstr_t m_name;                            // diskgroup name
    bigstr_t m_superBlockTableFile;             // superblock table file

    pathname_t m_superBlockTableFilePath;       // superblock table file path

    CCfgDiskDev* m_arrDiskDev;
    int m_szArrDiskDev; 

public:
    CCfgDiskGroup();
    ~CCfgDiskGroup();

    /* Methodes */

    void initDefaults();

    void init();

    void terminate();

    void loadConfig(int posDiskGroup, CCfgConfigTag* pConfigTag);

    void setData(CCfgDiskGroup* pDiskGroup);

    void debug(int debugLevel, const char* className, const char* methodName);

    /* Getters/Settes */

    void* getRemoteUnitPtr();

    long getOid();

    long getRemoteUnitOid();

    long getNumOfDisks();

    long getNumOfCopies();

    //long getNumOfSuperBlocks();

    //long getNumOfBlocks();

	//long getBlockSize();

    char* getName();

    char* getSuperBlockTableFile();

    char* getSuperBlockTableFilePath();

    CCfgDiskDev* getArrDiskDevPtr();

    int getSzArrDiskDev(); 

    /* GET_DISK_DEV */

    CCfgDiskDev* getDiskDevAtPtr(int pos);

    CCfgDiskDev* getDiskDevPtr(long oid);

    CCfgDiskDev* getDiskDevPtr(char* name);

};

/* NEW_TYPE: CCfgDiskGroup Pointer */

typedef CCfgDiskGroup* CCfgDiskGroupPtr_t;

#endif
