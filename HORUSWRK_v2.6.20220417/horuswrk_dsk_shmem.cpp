/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_shmem.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/12/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskShMem::CDskShMem()
{
    init();
}

CDskShMem::~CDskShMem()
{
    terminate();
}

/* Methodes */

void CDskShMem::init()
{
    createShMemObject();
}

void CDskShMem::terminate()
{
    deleteShMemObject();

    freeData(m_shmobj);
    m_shmobj = NULL;
}

// createShMemObject(): create shared memory object
void CDskShMem::createShMemObject()
{
    m_shmobj = (dsk_shmem_t*)allocData(sizeof(dsk_shmem_t));
    if(m_shmobj != NULL) {
        strSetEmptyUtil(m_shmobj->name);
        m_shmobj->fd = -1;
        m_shmobj->shmbufsz = 0;
        m_shmobj->shmbuf = NULL;
    }
}

// deleteShMemObject(): delete shared memory object
void CDskShMem::deleteShMemObject()
{
    if(m_shmobj != NULL) {
        if(m_shmobj->shmbuf != NULL) 
            munmap(m_shmobj->shmbuf, m_shmobj->shmbufsz);
        m_shmobj->shmbuf = NULL;
        m_shmobj->shmbufsz = 0;

        if(m_shmobj->fd != -1) {
            close(m_shmobj->fd);
            m_shmobj->fd = -1;
        }

        if(strIsEmptyUtil(m_shmobj->name) != DBFALSE) {
            shm_unlink(m_shmobj->name);
            strSetEmptyUtil(m_shmobj->name);
        }
    }
}

// newShMemObjectForRead(): create a new shared memory object for read
// name - name of shared memory object
// data - data buffer to receive shared memory object buffer
// datasz - size of data buffer to receive shared memory object
int CDskShMem::newShMemObjectForRead(
    char* name,
    byte* data,
    int datasz)
{
    m_shmobj->fd = shm_open(name, O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if(m_shmobj->fd != -1) {
        strNCpyUtil(m_shmobj->name, name, STRSZ);

        m_shmobj->shmbufsz = datasz;
        m_shmobj->shmbuf = (byte*)mmap(NULL, m_shmobj->shmbufsz, PROT_READ, MAP_SHARED, m_shmobj->fd, 0);
        memNCpyUtil(data, m_shmobj->shmbuf, m_shmobj->shmbufsz);

        close(m_shmobj->fd);
        m_shmobj->fd = -1;

        return RSOK;
    }
    return RSERR;
}

// newShMemObjectForWrite(): create a new shared memory object for write
// name - name of shared memory object
// data - data to be copied to shared memory object buffer
// datasz - size of data to be copied to shared memory object
int CDskShMem::newShMemObjectForWrite(
    char* name,
    byte* data,
    long datasz)
{
    m_shmobj->fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO);
    if(m_shmobj->fd != -1) {
        strNCpyUtil(m_shmobj->name, name, STRSZ);

        ftruncate(m_shmobj->fd, datasz);

        m_shmobj->shmbufsz = datasz;
        m_shmobj->shmbuf = (byte*)mmap(NULL, datasz, PROT_READ | PROT_WRITE, MAP_SHARED, m_shmobj->fd, 0);
        memNCpyUtil(m_shmobj->shmbuf, data, datasz);

        close(m_shmobj->fd);
        m_shmobj->fd = -1;

        return RSOK;
    }
    return RSERR;
}

// readLocalFileToShMem(): copy local file to shared memory object
// localSrcFile - local file
// shmDstFile - shared memory object
int CDskShMem::readLocalFileToShMem(const char* localSrcFile, const char* shmDstFile)
{
    byte* data = NULL;
    long datasz = 0;

    int rscode = readFileUtil(localSrcFile, & data, & datasz);
    if(rscode == RSOK) {
        rscode = newShMemObjectForWrite(
            (char*)shmDstFile,
            data,
            datasz);
    }
    return rscode;
}
