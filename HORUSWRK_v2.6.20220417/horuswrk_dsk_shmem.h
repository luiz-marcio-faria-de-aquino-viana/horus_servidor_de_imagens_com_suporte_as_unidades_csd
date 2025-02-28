/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_shmem.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/12/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_SHMEM_H
#define __HORUSWRK_DSK_SHMEM_H               "__HORUSWRK_DSK_SHMEM_H"

class CDskShMem
{
private:
    dsk_shmem_t* m_shmobj;

public:
    CDskShMem();
    ~CDskShMem();

    /* Methodes */

    // init(): initialization methode
    void init();    

    // terminate(): terminate methode
    void terminate();

    // createShMemObject(): create shared memory object
    void createShMemObject();

    // deleteShMemObject(): delete shared memory object
    void deleteShMemObject();

    // newShMemObjectForRead(): create a new shared memory object for read
    // name - name of shared memory object
    // data - data buffer to receive shared memory object buffer
    // datasz - size of data buffer to receive shared memory object
    int newShMemObjectForRead(
        char* name,
        byte* data,
        int datasz);

    // newShMemObjectForWrite(): create a new shared memory object for write
    // name - name of shared memory object
    // data - data to be copied to shared memory object buffer
    // datasz - size of data to be copied to shared memory object
    int newShMemObjectForWrite(
        char* name,
        byte* data,
        long datasz);

    // readLocalFileToShMem(): copy local file to shared memory object
    // localSrcFile - local file
    // shmDstFile - shared memory object
    int readLocalFileToShMem(
        const char* localSrcFile, 
        const char* shmDstFile);
        
};

/* NEW_TYPE: CDskShMem Pointer */

typedef CDskShMem* CDskShMemPtr_t;

#endif
