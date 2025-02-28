/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_diskman_exec.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 15/08/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskDiskManExec::CDskDiskManExec(void* pDiskMan, int maxNumThreads)
{
    init(pDiskMan, maxNumThreads);
}

CDskDiskManExec::~CDskDiskManExec()
{
    terminate();
}

// init(): initiate disk groups
// pDiskMan - pointer to disk manager thread
// maxNumThreads - maximum number of threads
void CDskDiskManExec::init(void* pDiskMan, int maxNumThreads)
{
    m_pDiskMan = pDiskMan;

    m_maxNumThreads = maxNumThreads;
    m_arrThreads = (dsk_diskman_thread_t*)allocDataArray(sizeof(dsk_diskman_thread_t), m_maxNumThreads);;

    for(int i = 0; i < m_maxNumThreads; i++) {
        dsk_diskman_thread_t* p = & m_arrThreads[i];
        initThread(p);
    }
}

// initThread(): initiate disk manager thread
// p - pointer to disk manager thread
void CDskDiskManExec::initThread(dsk_diskman_thread_t* p)
{
    bigstr_t errmsg;

    if(pthread_mutex_init(& p->thread_data_mutex, NULL) != 0)  {
        sprintf(errmsg, ERR_CANTCREATEMUTEX, __HORUSWRK_DSK_DISKMAN_EXEC_H); 
        errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "initThread()", errmsg);
    }
    resetThread(p);
}

// destroyThread(): destroy disk manager thread
// p - pointer to disk manager thread
void CDskDiskManExec::destroyThread(dsk_diskman_thread_t* p)
{
    resetThread(p);
    pthread_mutex_destroy(& p->thread_data_mutex);
}

// resetThread(): reset disk manager thread
// p - pointer to disk manager thread
void CDskDiskManExec::resetThread(dsk_diskman_thread_t* p)
{
    pthread_mutex_lock(& p->thread_data_mutex);

    p->thread_hnd = DBNULL_LONG;
    p->pDiskMan = m_pDiskMan;
    p->pRemoteUnit = NULL;
    p->pDiskGroup = NULL;
    p->pDiskDev = NULL;
    p->thread_group = DBNULL_LONG;
    p->thread_id = DBNULL_LONG;
    p->thread_type = DEF_DSK_THREAD_TYPE_NONE;
    p->is_valid = DBFALSE;
    p->is_running = DBFALSE;
    p->path_parent = DBNULL_LONG;
    p->path_oid = DBNULL_LONG;
    p->uid = DBNULL_LONG;
    p->start_block = 0;
    p->num_blocks = 0;   
    p->sblock_data = NULL;
    p->sblock_datasz = 0;
    p->data = NULL;
    p->datasz = 0L;
    p->resval = RSERR;

    pthread_mutex_unlock(& p->thread_data_mutex);
}

// resetAllThreadsByGroup(): reset all disk manager threads by group
// thread_group - thread group identifier
void CDskDiskManExec::resetAllThreadsByGroup(long thread_group)
{
    dsk_diskman_thread_t* p_result = NULL;
    for(int i = 0; i < m_maxNumThreads; i++) {
        p_result = & m_arrThreads[i];

        pthread_mutex_lock(& p_result->thread_data_mutex);
        long p_thread_group = p_result->thread_group;
        pthread_mutex_unlock(& p_result->thread_data_mutex);

        if(p_thread_group == thread_group)
            resetThread(p_result);
    }
}

// resetAllThreads(): reset all disk manager threads
void CDskDiskManExec::resetAllThreads()
{
    for(int i = 0; i < m_maxNumThreads; i++) {
        dsk_diskman_thread_t* p = & m_arrThreads[i];
        resetThread(p);
    }
}

// freeAllThreads(): free all disk manager threads
void CDskDiskManExec::freeAllThreads()
{
    for(int i = 0; i < m_maxNumThreads; i++) {
        dsk_diskman_thread_t* p = & m_arrThreads[i];
        destroyThread(p);
    }
}

// terminate(): terminate disk groups
void CDskDiskManExec::terminate()
{
    if(m_arrThreads != NULL) {
        freeAllThreads();
        freeDataArray(m_arrThreads);
        m_maxNumThreads = 0;
    }
}

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
dsk_diskman_thread_t* CDskDiskManExec::addWriteThread(
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
    long datasz)
{
    dsk_diskman_thread_t* p = NULL;

    p = getNextThreadPtr(thread_group, DEF_DSK_THREAD_TYPE_WRITE);
    if(p == NULL) {
        errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "addWriteThread()", ERR_CANTFINDFREETHREADENTRY);
    }

    p->pRemoteUnit = pRemoteUnit;
    p->pDiskGroup = pDiskGroup;
    p->pDiskDev = pDiskDev;
    p->path_parent = path_parent;
    p->path_oid = path_oid;
    p->uid = uid; 
    p->start_block = start_block;
    p->num_blocks = num_blocks;
    p->sblock_data = NULL;
    p->sblock_datasz = 0;
    p->data = data;
    p->datasz = datasz;

    int rscode = pthread_create(& p->thread_hnd, NULL, dsk_diskman_write, p);
    if(rscode != 0) {
        errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "addWriteThread()", ERR_CANTDISPATCHWRITETHREAD);
    }

    debugEntry(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_EXEC_H, "addWriteThread()", p, DBFALSE);

    return p;    
}

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
dsk_diskman_thread_t* CDskDiskManExec::addReadThread(
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
    long datasz)
{
    dsk_diskman_thread_t* p = NULL;

    p = getNextThreadPtr(thread_group, DEF_DSK_THREAD_TYPE_READ);
    if(p == NULL) {
        errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "addReadThread()", ERR_CANTFINDFREETHREADENTRY);
    }

    p->pRemoteUnit = pRemoteUnit;
    p->pDiskGroup = pDiskGroup;
    p->pDiskDev = pDiskDev;
    p->path_parent = path_parent;
    p->path_oid = path_oid;
    p->uid = uid; 
    p->start_block = DBNULL_LONG;
    p->num_blocks = DBNULL_LONG;
    p->sblock_data = sblock_data;
    p->sblock_datasz = sblock_datasz;
    p->data = data;
    p->datasz = datasz;

    int rscode = pthread_create(& p->thread_hnd, NULL, dsk_diskman_read, p);
    if(rscode != 0) {
        errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "addReadThread()", ERR_CANTDISPATCHWRITETHREAD);
    }

    debugEntry(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_EXEC_H, "addReadThread()", p, DBFALSE);

    return p;    
}

// waitThreadGroup(): wait for thread group complete
// thread_group - thread group identifier
// thread_type - thread type (READ/WRITE OPERATION)
int CDskDiskManExec::waitThreadGroup(long thread_group, long thread_type)
{
    bigstr_t errmsg;

    for(long i = 0; i < m_maxNumThreads; i++) {
        dsk_diskman_thread_t* p = getThreadAtPtr(i);

        pthread_mutex_lock(& p->thread_data_mutex);    
        pthread_t p_thread_hnd = p->thread_hnd;
        long p_thread_group = p->thread_group;
        //long p_thread_id = p->thread_id;
        long p_thread_type = p->thread_type;
        pthread_mutex_unlock(& p->thread_data_mutex);

        if( (p_thread_group == thread_group) && (p_thread_type == thread_type) ) 
        {
            int rscode = pthread_join(p_thread_hnd, NULL);
            if(rscode == 0) {
                //TODO
            }
            else {
                if(rscode == EDEADLK)
                    strNCpyUtil(errmsg, (char*)ERR_DISKMANTHREADDEADLOCK, BIGSTRSZ);
                else if(rscode == EINVAL)
                    strNCpyUtil(errmsg, (char*)ERR_DISKMANTHREADINVALID, BIGSTRSZ);
                else if(rscode == ESRCH)
                    strNCpyUtil(errmsg, (char*)ERR_DISKMANTHREADNOTEXIST, BIGSTRSZ);
                else
                    strNCpyUtil(errmsg, (char*)ERR_DISKMANTHREADUNKNOW, BIGSTRSZ);

                errMsg(__HORUSWRK_DSK_DISKMAN_EXEC_H, "waitThreadGroup()", errmsg);
            }
        }
    }
    return RSOK;
}

/* Debug */

// debug(): show all disk groups
// debugLevel - debug level
// className - class name
// methodName - method name
// bUseMutex - use mutex to lock critical section
void CDskDiskManExec::debug(int debugLevel, const char* className, const char* methodName, long bUseMutex)
{
    if(debugLevel != DEBUG_LEVEL) return;

    dsk_diskman_thread_t* p = NULL;
    for(int i = 0; i < m_maxNumThreads; i++)
    {
        p = &m_arrThreads[i];
        debugEntry(debugLevel, className, methodName, p, bUseMutex);
    }  
}

// debugEntry(): show disk manager thread entry
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a disk manager thread entry
// bUseMutex - use mutex to lock critical section
void CDskDiskManExec::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_diskman_thread_t* p, long bUseMutex)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;

    if(bUseMutex == DBTRUE)
        pthread_mutex_lock(& p->thread_data_mutex);

    long p_remoteunit_oid = (p->pRemoteUnit != NULL) ? ((CCfgRemoteUnit*)p->pRemoteUnit)->getOid() : DBNULL_LONG;
    long p_diskgroup_oid = (p->pDiskGroup != NULL) ? ((CDskDiskGroup*)p->pDiskGroup)->getOid() : DBNULL_LONG;
    long p_diskdev_oid = (p->pDiskDev != NULL) ? ((CDskDiskDev*)p->pDiskDev)->getOid() : DBNULL_LONG;

    sprintf(
        errmsg, 
        "\nThreadHnd=%ld,RemoteUnitOid=%ld,DiskGroupOid=%ld,DiskDevOid=%ld,ThreadGroup=%ld,ThreadId=%ld,ThreadType=%ld,IsValid=%ld,IsRunning=%ld,PathParent=%ld,PathOid=%ld,Uid=%ld,StartBlock=%ld,NumBlocks=%ld,DataSz=%ld,ResVal=%ld\n",
        p->thread_hnd,
        p_remoteunit_oid,
        p_diskgroup_oid,
        p_diskdev_oid,
        p->thread_group,
        p->thread_id,
        p->thread_type,
        p->is_valid,
        p->is_running,
        p->path_parent,
        p->path_oid,
        p->uid, 
        p->start_block,
        p->num_blocks,
        p->datasz,
        p->resval);

    if(bUseMutex == DBTRUE)
        pthread_mutex_unlock(& p->thread_data_mutex);

    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Setters */

dsk_diskman_thread_t* CDskDiskManExec::getThreadAtPtr(long pos)
{
    dsk_diskman_thread_t* p_result = NULL;
    if(pos < m_maxNumThreads)
        p_result = & m_arrThreads[pos];
    return p_result;
}

dsk_diskman_thread_t* CDskDiskManExec::getThreadByThreadIdPtr(long thread_id)
{
    dsk_diskman_thread_t* p_result = NULL;
    for(int i = 0; i < m_maxNumThreads; i++) {
        p_result = getThreadAtPtr(i);
    
        pthread_mutex_lock(& p_result->thread_data_mutex);
        long tid = p_result->thread_id;
        pthread_mutex_unlock(& p_result->thread_data_mutex);

        if(tid == thread_id)
            return p_result;
    }
    return NULL;
}

dsk_diskman_thread_t* CDskDiskManExec::getNextThreadPtr(long thread_group, long thread_type)
{
    bigstr_t errmsg;

    dsk_diskman_thread_t* p_result = NULL;
    for(int i = 0; i < m_maxNumThreads; i++) {
        dsk_diskman_thread_t* p = getThreadAtPtr(i);

        sprintf(
            errmsg, 
            "\nSearching for Avaliable Thread Entry: ThreadNum=%d,MaxNumThread=%d... \n", 
            i, 
            m_maxNumThreads);
        warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_EXEC_H, "getNextThreadPtr()", errmsg);

        pthread_mutex_lock(& p->thread_data_mutex);

        if( (p->is_valid == DBFALSE) && (p->is_running == DBFALSE) ) {
            p->thread_hnd = DBNULL_LONG;
            p->pDiskMan = m_pDiskMan;
            p->thread_group = thread_group;
            p->thread_id = i;
            p->thread_type = thread_type;
            p->is_valid = DBTRUE;
            p->is_running = DBFALSE;
            p->resval = RSERR;
            p_result = p;
        }

        if(p_result != NULL) {
            sprintf(
                errmsg,
                "\nValid Thread Entry [ FOUND ]: ThreadNum=%d,MaxNumThread=%d,ThreadGroup=%ld,ThreadId=%ld,ThreadType=%ld,IsValid=%ld,IsRunning=%ld!\n",
                i, 
                m_maxNumThreads,
                p->thread_group,
                p->thread_id,
                p->thread_type,
                p->is_valid,
                p->is_running);
        }

        pthread_mutex_unlock(& p->thread_data_mutex);

        warnMsg(DEBUG_LEVEL_07, __HORUSWRK_DSK_DISKMAN_EXEC_H, "getNextThreadPtr()", errmsg);

        if(p_result != NULL) 
            break;
    }

    return p_result;
}

int CDskDiskManExec::getMaxNumTreads()
{
    return m_maxNumThreads;
}

/* NEW_TYPE: CDskDiskExec Pointer */

typedef CDskDiskManExec* CDskDiskManExecPtr_t;

/* Disk Manager Threads */

extern void* dsk_diskman_write(void* _pArgs)
{
    bigstr_t errmsg;

    int rscode = RSERR;

    dsk_diskman_thread_t* pThreadArgs = (dsk_diskman_thread_t*)_pArgs;    
    pThreadArgs->is_running = DBTRUE;

    CDskDiskGroup* pDiskGroup = (CDskDiskGroup*)pThreadArgs->pDiskGroup;
    CDskDiskDev* pDiskDev = (CDskDiskDev*)pThreadArgs->pDiskDev;

    CDskSuperBlockMan* pCurrSuperBlockMan = (CDskSuperBlockMan*)pDiskGroup->getSuperBlockMan();

    long path_oid = pThreadArgs->path_oid;
    long uid = pThreadArgs->uid;

    long start_block = pThreadArgs->start_block;
    long num_blocks = pThreadArgs->num_blocks;

    byte* data = pThreadArgs->data;
    long datasz = pThreadArgs->datasz;

    long resval = RSERR;

    long blockSize = DEF_DSK_BLOCKSIZE;
    byte* blockbuf = (byte*)allocDataArray(sizeof(byte), blockSize);

    sprintf(errmsg, "\nM.1) DskDiskManWrite - Started! ");
    warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);

    if(blockbuf != NULL) 
    {
        sprintf(errmsg, "\nM.2) DskDiskManWrite - BLOCKBUF ALLOCATED! ");
        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);

        long i = 0;
        for( ; i < num_blocks; i++) 
        {
            dsk_superblock_t* p_sblock = NULL;
            long sblock_oid = DBNULL_LONG;

            dsk_block_t* p_block = NULL;
            long block_oid = DBNULL_LONG;
            long block_sector = DBNULL_LONG;

            long block_num = start_block + i;

            long pos_I = block_num * blockSize;
            long pos_F = pos_I + blockSize;
            if(pos_F > datasz)
                pos_F = datasz;

            byte* tmp_data = & data[pos_I];
            long tmp_datasz = pos_F - pos_I;

            memSetNullUtil(blockbuf, blockSize);
            memNCpyUtil(blockbuf, tmp_data, tmp_datasz);

            sprintf(
                errmsg, 
                "\nM.3) DskDiskManWrite - PathOid: %ld; BlockNum: %ld; StartPos: %ld; EndPos: %ld; BlockSize: %ld... ",
                path_oid,
                block_num,
                pos_I,
                pos_F, 
                blockSize);
            warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);

            rscode = pDiskDev->writeBlock(
                path_oid,
                block_num, 
                blockSize,
                blockbuf, 
                & p_block,
                & block_oid,
                & block_sector);                    
            if(rscode == RSOK) {
                rscode = pCurrSuperBlockMan->findFirstFreeSuperBlock(
                        pDiskGroup->getOid(), 
                        pDiskDev->getOid(), 
                        path_oid, 
                        block_num,
                        block_sector,
                        uid, 
                        & p_sblock, 
                        & sblock_oid);
                if(rscode == RSERR) {
                    sprintf(
                        errmsg, 
                        "\nM.4) ERROR: DskDiskManWrite - PathOid: %ld; BlockNum: %ld; StartPos: %ld; EndPos: %ld; BlockSize: %ld... CAN'T FIND ANY FREE SUPERBLOCK!",
                        path_oid,
                        block_num, 
                        pos_I,
                        pos_F, 
                        blockSize);
                    warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);
                    break;
                }                    
            }
            else {
                sprintf(
                    errmsg, 
                    "\nM.5) ERROR: DskDiskManWrite - PathOid: %ld; BlockNum: %ld; StartPos: %ld; EndPos: %ld; BlockSize: %ld... WRITE BLOCK FAILURE!",
                    path_oid,
                    block_num, 
                    pos_I,
                    pos_F, 
                    blockSize);
                warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);
            }
        }
        freeDataArray(blockbuf);

        if(i == num_blocks)
            resval = RSOK;
    }

    sprintf(errmsg, "\nM.6) DskDiskManWrite - Finished! ");
    warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_write()", errmsg);

    pThreadArgs->is_running = DBFALSE;
    pThreadArgs->resval = resval;
    
    pthread_exit(NULL);
}

extern void* dsk_diskman_read(void* _pArgs)
{
    bigstr_t errmsg;

    int rscode = RSERR;

    dsk_diskman_thread_t* pThreadArgs = (dsk_diskman_thread_t*)_pArgs;    
    pThreadArgs->is_running = DBTRUE;

    //CDskDiskGroup* pDiskGroup = (CDskDiskGroup*)pThreadArgs->pDiskGroup;
    CDskDiskDev* pDiskDev = (CDskDiskDev*)pThreadArgs->pDiskDev;

    //long thread_id = pThreadArgs->thread_id;

    long path_oid = pThreadArgs->path_oid;
    //long uid = pThreadArgs->uid;

    dsk_superblock_t* sblock_data = pThreadArgs->sblock_data;
    long sblock_datasz = pThreadArgs->sblock_datasz;

    byte* data = pThreadArgs->data;
    long datasz = pThreadArgs->datasz;

    long resval = RSERR;

    long blockSize = DEF_DSK_BLOCKSIZE;
    byte* blockbuf = (byte*)allocDataArray(sizeof(byte), blockSize);

    sprintf(errmsg, "\nN.1) DskDiskManRead - Started! ");
    warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_read()", errmsg);

    if(blockbuf != NULL) 
    {
        sprintf(errmsg, "\nN.2) DskDiskManRead - BLOCKBUF ALLOCATED! ");
        warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_read()", errmsg);

        long i = 0;
        for( ; i < sblock_datasz; i++) 
        {
            dsk_superblock_t* p_sblock = & sblock_data[i];

            long block_num = p_sblock->block_num;

            long pos_I = block_num * blockSize;
            long pos_F = pos_I + blockSize;
            if(pos_F > datasz)
                pos_F = datasz;

            byte* tmp_data = & data[pos_I];
            long tmp_datasz = pos_F - pos_I;

            dsk_block_t* p_block = NULL;
            long block_oid = DBNULL_LONG;
            long block_sector = DBNULL_LONG;

            memSetNullUtil(blockbuf, blockSize);

            sprintf(
                errmsg, 
                "\nN.3) DskDiskManRead - PathOid: %ld; BlockNum: %ld; StartPos: %ld; EndPos: %ld; BlockSize: %ld... ",
                path_oid,
                block_num,
                pos_I,
                pos_F, 
                blockSize);
            warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_read()", errmsg);

            rscode = pDiskDev->readBlock(
                path_oid,
                block_num, 
                blockSize,
                blockbuf, 
                & p_block,
                & block_oid,
                & block_sector); 
                                   
            if(rscode == RSOK) {
                memNCpyUtil(tmp_data, blockbuf, tmp_datasz);
            }
            else {
                sprintf(
                    errmsg, 
                    "\nN.4) ERROR: DskDiskManRead - PathOid: %ld; BlockNum: %ld; StartPos: %ld; EndPos: %ld; BlockSize: %ld... READ BLOCK FAILURE!",
                    path_oid,
                    block_num, 
                    pos_I,
                    pos_F, 
                    blockSize);
                warnMsgAndWaitForKey(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_read()", errmsg);
                break;
            }
        }
        freeDataArray(blockbuf);

        resval = RSOK;
    }

    sprintf(errmsg, "\nN.5) DskDiskManRead - Finished! ");
    warnMsg(DEBUG_LEVEL_11, __HORUSWRK_DSK_DISKMAN_EXEC_H, "dsk_diskman_read()", errmsg);

    pThreadArgs->is_running = DBFALSE;
    pThreadArgs->resval = resval;
    
    pthread_exit(NULL);
}
