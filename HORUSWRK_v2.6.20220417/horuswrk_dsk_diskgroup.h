/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskgroup.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_DISKGROUP_H
#define __HORUSWRK_DSK_DISKGROUP_H                      "__HORUSWRK_DSK_DISKGROUP_H"

class CDskDiskGroup
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
    bigstr_t m_key;                             // diskgorup key

    pathname_t m_superBlockTableFilePath;       // superblock table file path

    CDskSuperBlockMan* m_superBlockMan;         // superblock manager class
    //int m_maxNumDskSuperBlock;                  // maximum number of disk superblocks

    CDskDiskDevPtr_t* m_arrDiskDev;             // point to a disk device array
    int m_maxNumDiskDev;                        // maximum number of disk devices
    int m_currNumDiskDev;                       // current number of disk devices

public:

    CDskDiskGroup(
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
        char* superBlockTableFilePath);
    ~CDskDiskGroup();

    // init(): initiate disk group
    void init(
        long oid,
        long remoteUnitOid,
        long numOfDisks,
        long numOfCopies,
        //long numOfSuperBlocks,
        //long numOfBlocks,
        //long blockSize,
        char* name,
        char* superBlockTableFile,
        char* superBlockTableFilePath);

    // term(): terminate disk group
    void terminate();

    /* Methodes */

    // addDiskDev(): add new disk device
    // oid - disk device oid
    // remoteUnitOid - remote unit oid
    // name - disk device name
    // dataFile - disk device data file
    // blockTableFile - block table file
    // blockTableFilePath - block table file path
    // dataFilePath - disk device data file path
    // maxNumDskBlock - max number of blocks
    CDskDiskDev* addDiskDev(
        long oid,
        char* name,
        char* dataFile,
        char* blockTableFile,
        char* blockTableFilePath,
        char* dataFilePath);

    /* Debug */

    // debug(): show all disk groups
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    void debug(int debugLevel, const char* className, const char* methodName);

    // debugEntry(): show disk group
    // debugLevel - debug level
    // className - class name
    // methodName - method name
    // p - pointer to a disk group entry
    void debugEntry(int debugLevel, const char* className, const char* methodName, CDskDiskGroup* p);

    /* Getters/Setters */

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

    char* getKey();

    char* getSuperBlockTableFilePath();

    CDskSuperBlockMan* getSuperBlockMan();

    //int getMaxNumDskSuperBlock();

    // DISKDEV
    //
    CDskDiskDev* getDiskDevAtPtr(int pos);

    CDskDiskDev* getDiskDevPtr(long oid);

    CDskDiskDev* getDiskDevPtr(char* name);

    int getMaxNumDiskDev();

    int getCurrNumDiskDev();

};

/* NEW_TYPE: CDskDiskGroup Pointer */

typedef CDskDiskGroup* CDskDiskGroupPtr_t;

#endif
