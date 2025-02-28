/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/08/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_DISKMAN_H
#define __HORUSWRK_DSK_DISKMAN_H                "__HORUSWRK_DSK_DISKMAN_H"

class CDskDiskMan    
{
private:
    void* m_pRemoteUnit;
    void* m_pDispatch;

    str_t m_session;
    
    bigstr_t m_dirTableFile;
    pathname_t m_dirTableFilePath;

    CDskShMem* m_shMem;

    CDskPathMan* m_pathMan;
    int m_maxNumDskPath;

    CDskRoundRobin* m_roundRobin;
    int m_maxNumRoundRobinTable;

    CDskDiskGroupPtr_t* m_arrDiskGroup;
    int m_maxNumDiskGroup; 
    int m_currNumDiskGroup; 

    dsk_diskman_thread_t* m_arrDiskMainThreads;
    int m_maxNumDiskMainThreads;

    CDskDiskManExec* m_diskManExec;
    int m_maxNumThreads;

    long m_currDir;                // current directory

    // PATH TEST VARS 
    //
    long m_path_oid_01;
    long m_path_oid_01_01;
    long m_path_oid_01_01_01;
    long m_path_oid_01_01_02;
    long m_path_oid_01_01_03;

public:
    CDskDiskMan(
        void* pRemoteUnit,
        char* dirTableFile,
        char* dirTableFilePath,
        int maxNumDskPath, 
        int maxNumRoundRobinTable,
        int maxNumDiskGroup,
        int maxNumThreads);
    ~CDskDiskMan();

    // init(): initiate disk groups
    void init(
        char* dirTableFile,
        char* dirTableFilePath,
        int maxNumDskPath, 
        int maxNumRoundRobinTable,
        int maxNumDiskGroup,
        int maxNumThreads);

    // initDiskGroup(): initiate disk groups
    void initDiskGroup();

    // terminate(): terminate disk groups
    void terminate();

    /* Methodes */

    // addDiskGroup(): add new disk group
    // oid - disk group oid 
    // numOfDisks - number of disks
    // numOfCopies - number of copies
    // numOfSuperBlocks - number of superblocks
    // numOfBlocks - number of blocks 
    // blockSize - block size
    // name - disk group name
    // superBlockTableFile - superblock table file
    // superBlockTableFilePath - superblock table file path
    CDskDiskGroup* addDiskGroup(
        long oid,
        long numOfDisks,
        long numOfCopies,
        //long numOfSuperBlocks,
        //long numOfBlocks,
        //long blockSize,
        char* name,
        char* superBlockTableFile,
        char* superBlockTableFilePath);

    /* DISK MANAGER TEST */

    int testDiskMan_MakeDir(long* path_parent, long bWaitKey);
    int testDiskMan_WriteLocalFile(long path_parent, long bWaitKey);
    int testDiskMan_ReadLocalFile(long path_parent, long bWaitKey);
    int testDiskMan_DeleteLocalFile(long path_parent, long bWaitKey);
    int testDiskMan_UploadRemoteFile(long path_parent, long bWaitKey);
    int testDiskMan_DownloadRemoteFile(long path_parent, long bWaitKey);
    int testDiskMan_DeleteRemoteFile(long path_parent, long bWaitKey);
    int testDiskMan_RemoveDir(long bWaitKey);

    int testDiskMan();

    /* COMMANDS */

    //DIRECTORY_OPERATIONS

    int doChDir(long path_parent);

    int doMakeDir(long uid, long path_parent, char* path_name, long* path_oid);

    int doRemoveDir(long uid, long path_oid);
    
    int doRemoveDir(long uid, long path_parent, char* path_name);

    int doListDir(dsk_path_t** data, long* datasz, long path_parent, long bDeleted);
    
    int doListDir(dsk_path_t** data, long* datasz, long path_parent, char* path_name, long bDeleted);

    int showListDir(long path_parent, long bDeleted, long bWaitKey);

    //FILE_OPERATIONS

    int doFileExist(long path_oid, dsk_path_t* pCurrPath);

    int doFileExist(long path_parent, char* path_name, dsk_path_t* pCurrPath);

    int doDeleteFile(long uid, long path_oid);

    int doDeleteFile(long uid, long path_parent, char* path_name);

    int doCopyFile(long uid, long spath_parent, char* spath_name, long dpath_parent, char* dpath_name, long* dpath_oid);

    int doMoveFile(long uid, long spath_parent, char* spath_name, long dpath_parent, char* dpath_name);

    int doRenameFile(long uid, long spath_parent, char* spath_name, char* dpath_name);

    int doWriteFile(byte* data, long datasz, long path_parent, char* path_name, long uid, long* path_oid);

    int doWriteFileMT(byte* data, long datasz, long path_parent, char* path_name, long uid, long* path_oid);

    int doReadFile(byte** data, long* datasz, long path_parent, char* path_name, long uid, long* path_oid);

    int doReadFileMT(byte** data, long* datasz, long path_parent, char* path_name, long uid, long* path_oid);

    //int doWriteFileData(CDskDiskDev* pDiskDev, long path_oid, long block_num, long block_size, byte* data, long datasz, dsk_block_t** p_block, long* block_oid, long* block_sector);

    //int doReadFileData(CDskDiskDev* pDiskDev, long path_oid, long block_num, long block_size, byte* data, long datasz, dsk_block_t** p_block, long* block_oid, long* block_sector);

    //FILE_OPERATIONS_REQUEST

    int doReqUploadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte* data, 
        long datasz, 
        long uid, 
        long* path_oid);

    int doReqDownloadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_oid, 
        byte** data, 
        long* datasz,
        long uid);

    int doReqDownloadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte** data, 
        long* datasz,
        long uid);

    int doReqWriteFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte* data, 
        long datasz, 
        long uid, 
        long* path_oid);

    int doReqReadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte** data, 
        long* datasz, 
        long uid);

    int doReqWriteBlock(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long block_sector,
        long block_num, 
        byte* data, 
        long datasz, 
        long uid);

    int doReqReadBlock(
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long block_sector,
        long block_num, 
        byte** data, 
        long* datasz, 
        long uid);

    //FILE_OPERATIONS_RESPONSE

    int doRespUploadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        long datasz, 
        long uid, 
        long* path_oid);

    int doRespDownloadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_oid, 
        byte* data, 
        long datasz,
        long uid);

    int doRespDownloadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte* data, 
        long datasz,
        long uid);

    int doRespWriteFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        long datasz, 
        long uid, 
        long* path_oid);

    int doRespReadFile(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long path_parent, 
        char* path_name, 
        byte* data, 
        long datasz, 
        long uid);

    int doRespWriteBlock(
        CCfgRemoteUnit* pCurrRemoteUnit, 
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long block_sector,
        long block_num, 
        long datasz, 
        long uid);

    int doRespReadBlock(
        CCfgRemoteUnit* pRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev,
        long block_sector,
        long block_num, 
        byte* data, 
        long datasz, 
        long uid);

    /* Getters/Setters */

    char* getDirTableFile();

    long getCurrDir();

    /* PATH MANAGER */

    CDskPathMan* getPathMan();

    /* SUPERBLOCK MANAGER */

    CDskSuperBlockMan* getSuperBlockMan();

    int getMaxNumDskPath();

    /* DISK MANAGER EXECUTION */

    CDskDiskManExec* getDiskManExecPtr();

    /* DISK GROUP */

    CDskDiskGroup* getDiskGroupAtPtr(long pos);

    CDskDiskGroup* getDiskGroupPtr(long oid);

    CDskDiskGroup* getDiskGroupPtr(char* groupName);

    int getMaxNumDiskGroup(); 
    
    int getCurrNumDiskGroup(); 

};

/* NEW_TYPE: CDskDiskMan Pointer */

typedef CDskDiskMan* CDskDiskManPtr_t;

#endif
