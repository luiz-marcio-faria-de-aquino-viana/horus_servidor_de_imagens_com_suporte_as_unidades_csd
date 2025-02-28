/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskdev.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_DISKDEV_H
#define __HORUSWRK_DSK_DISKDEV_H               "__HORUSWRK_DSK_DISKDEV_H"

class CDskDiskDev
{
private:
    //pthread_mutex_t dsk_diskdev_mutex;  // disk device read/write mutext

    void* m_pRemoteUnit;                // point to remote disk device unit
    void* m_pDiskGroup;                 // point to disk group

    long m_oid;                         // disk device unit id
    long m_posDiskDev;                  // disk device pos
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

    CDskBlockMan* m_blockMan;           // point to disk blocks manager 
    //int m_maxNumDskBlock;               // maximum number of disk blocks

public:
    CDskDiskDev(
        void* pRemoteUnit,
        void* pDiskGroup,
        long oid,
        long posDiskDev,
        long remoteUnitOid,
        long diskGroupOid,
        //long numOfBlocks,
	    //long blockSize,
        long lastUpdate,
        char* name,
        char* blockTableFile,
        char* dataFile,
        char* blockTableFilePath,
        char* dataFilePath);
    ~CDskDiskDev();

    // init(): initiate disk device
    void init(
        void* pRemoteUnit,
        void* pDiskGroup,
        long oid,
        long posDiskDev,
        long remoteUnitOid,
        long diskGroupOid,
        //long numOfBlocks,
	    //long blockSize,
        long lastUpdate,
        char* name,
        char* blockTableFile,
        char* dataFile,
        char* blockTableFilePath,
        char* dataFilePath);

    // terminate(): terminate disk device
    void terminate();

    /* Methodes */

    int writeBlock(
        long path_oid,
        long block_num,
        long block_size,
        byte* blockbuf,
        dsk_block_t** p_block,
        long* block_oid,
        long* block_sector);

    int readBlock(
        long path_oid,
        long block_num,
        long block_size,
        byte* blockbuf,
        dsk_block_t** p_block,
        long* block_oid,
        long* block_sector);

    /* Getters/Setters */

    void* getRemoteUnitPtr();

    void* getDiskGroupPtr();

    long getOid();

    long getPosDiskDev();

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

    CDskBlockMan* getDskBlockMan();

    //int getMaxNumDskBlock();

};

/* NEW_TYPE: CDskDiskDev Pointer */

typedef CDskDiskDev* CDskDiskDevPtr_t;

#endif
