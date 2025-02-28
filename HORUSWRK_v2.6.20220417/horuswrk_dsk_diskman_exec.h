/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskman_exec.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 15/09/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_DISKMAN_EXEC_H
#define __HORUSWRK_DSK_DISKMAN_EXEC_H                "__HORUSWRK_DSK_DISKMAN_EXEC_H"

class CDskDiskManExec
{
private:
    void* m_pDiskMan;

    dsk_diskman_thread_t* m_arrThreads;
    int m_maxNumThreads;

public:
    CDskDiskManExec(void* pDiskMan, int maxNumThreads);
    ~CDskDiskManExec();

// init(): initiate disk groups
// pDiskMan - pointer to disk manager thread
// maxNumThreads - maximum number of threads
void init(void* pDiskMan, int maxNumThreads);

// initThread(): initiate disk manager thread
// p - pointer to disk manager thread
void initThread(dsk_diskman_thread_t* p);

// destroyThread(): destroy disk manager thread
// p - pointer to disk manager thread
void destroyThread(dsk_diskman_thread_t* p);

// resetThread(): reset disk manager thread
// p - pointer to disk manager thread
void resetThread(dsk_diskman_thread_t* p);

// resetAllThreadsByGroup(): reset all disk manager threads by group
// thread_group - thread group identifier
void resetAllThreadsByGroup(long thread_group);

// resetAllThreads(): reset all disk manager threads
void resetAllThreads();

// freeAllThreads(): free all disk manager threads
void freeAllThreads();

// terminate(): terminate disk groups
void terminate();

/* Methodes */

// addWriteThread(): add disk manager thread
// pRemoteUnit - pointer to remote unit
// pDiskGroup - pointer to disk group
// pDiskDev - pointer to disk device
// path_parent - parent path oid
// path_oid - path oid
// thread_group - thread group identifier
// thread_id - thread identifier
// uid - user oid
// start_block - start block number
// num_blocks - number of blocks
// data - pointer to data
// datasz - data size 
dsk_diskman_thread_t* addWriteThread(
    void* pRemoteUnit,
    void* pDiskGroup,
    void* pDiskDev,
    long path_parent,
    long path_oid,
    long thread_group,
    long thread_id,
    long uid,
    long start_block,
    long num_blocks,
    byte* data,
    long datasz);

// addReadThread(): add disk manager thread
// pRemoteUnit - pointer to remote unit
// pDiskGroup - pointer to disk group
// pDiskDev - pointer to disk device
// path_parent - parent path oid
// path_oid - path oid
// thread_group - thread group identifier
// thread_id - thread identifier
// uid - user oid
// sblock_data - superblock entry array
// sblock_datasz - superblock entry array size
// data - pointer to data
// datasz - data size 
dsk_diskman_thread_t* addReadThread(
    void* pRemoteUnit,
    void* pDiskGroup,
    void* pDiskDev,
    long path_parent,
    long path_oid,
    long thread_group,
    long thread_id,
    long uid,
    dsk_superblock_t* sblock_data,
    long sblock_datasz,
    byte* data,
    long datasz);

// waitThreadGroup(): wait for thread group complete
// thread_group - thread group identifier
// thread_type - thread type (READ/WRITE OPERATION)
int waitThreadGroup(long thread_group, long thread_type);

/* Debug */

// debug(): show all disk groups
// debugLevel - debug level
// className - class name
// methodName - method name
// bUseMutex - use mutex to lock critical section
void debug(int debugLevel, const char* className, const char* methodName, long bUseMutex);

// debugEntry(): show disk manager thread entry
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a disk manager thread entry
// bUseMutex - use mutex to lock critical section
void debugEntry(int debugLevel, const char* className, const char* methodName, dsk_diskman_thread_t* p, long bUseMutex);

/* Getters/Setters */

dsk_diskman_thread_t* getThreadAtPtr(long pos);

dsk_diskman_thread_t* getThreadByThreadIdPtr(long thread_id);

dsk_diskman_thread_t* getNextThreadPtr(long thread_group, long thread_type);

int getMaxNumTreads();

};

/* NEW_TYPE: CDskDiskExec Pointer */

typedef CDskDiskManExec* CDskDiskManExecPtr_t;

/* Disk Manager Threads */

extern void* dsk_diskman_write(void* _pArgs);

extern void* dsk_diskman_read(void* _pArgs);

#endif
