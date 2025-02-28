/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_sched.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CExtSched gExtSched(MAX_REGISTERED_MODULES);

CExtSched::CExtSched(int numMaxModules)
{
    m_numMaxModules = numMaxModules;
    m_pLsModules = (sched_t*)allocDataArray(sizeof(sched_t), m_numMaxModules);

    m_currNumModules = 0;
    m_numLoadedModules = 0;
    m_numRunningModules = 0;
}

CExtSched::~CExtSched()
{
    if(m_pLsModules != NULL)
        freeDataArray(m_pLsModules);    
}

/* Methodes */

int CExtSched::init()
{
    /* sample modules
    */
    //MODULE_1
    CExtModule* pModule1 = new CExtModule(
        MOD_MODULE_OID_1, 
        MOD_MODULE_NAME_1, 
        MOD_MODULE_FILENAME_1);

    sched_t *p = & m_pLsModules[m_currNumModules++];
    p->pModule = (void*)pModule1;
    p->threadHnd = -1;
    p->isLoaded = DBFALSE;
    p->isInitialized = DBFALSE;
    p->isRunning = DBFALSE;

    //MODULE_2
    CExtModule* pModule2 = new CExtModule(
        MOD_MODULE_OID_2, 
        MOD_MODULE_NAME_2, 
        MOD_MODULE_FILENAME_2);

    p = & m_pLsModules[m_currNumModules++];
    p->pModule = (void*)pModule2;
    p->threadHnd = -1;
    p->isLoaded = DBFALSE;
    p->isInitialized = DBFALSE;
    p->isRunning = DBFALSE;

    //MODULE_3
    CExtModule* pModule3 = new CExtModule(
        MOD_MODULE_OID_3, 
        MOD_MODULE_NAME_3, 
        MOD_MODULE_FILENAME_3);

    p = & m_pLsModules[m_currNumModules++];
    p->pModule = (void*)pModule3;
    p->threadHnd = -1;
    p->isLoaded = DBFALSE;
    p->isInitialized = DBFALSE;
    p->isRunning = DBFALSE;

    return RSOK;
}

/* Module Operations */

// loadModule(): function called when the module is loaded
// module_name - module register name in the server
int CExtSched::loadModule(char* module_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if(pSched->isLoaded == DBFALSE) {
                pModule->loadModule();    
                pSched->isLoaded = DBTRUE;   
            }                 
        }
    }

    return RSOK;
}

// initModule(): function called to initialize the module
// module_name - module register name in the server
int CExtSched::initModule(char* module_name, int numParms, char* parmNames[], char* parmValues[])
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBFALSE)) {
                pModule->initModule(numParms, parmNames, parmValues);       
                pSched->isInitialized = DBTRUE;
            }                 
        }
    }
    
    return RSOK;
}

// terminateModule(): function to terminate the model
// module_name - module register name in the server
int CExtSched::terminateModule(char* module_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if(pSched->isLoaded == DBTRUE) {
                pModule->terminateModule();
                pSched->isLoaded = DBFALSE;
                pSched->isInitialized = DBFALSE;
                pSched->isRunning = DBFALSE;
            }                     
        }
    }
    
    return RSOK;
}

// start(): function called when the module is started
// module_name - module register name in the server
int CExtSched::start(char* module_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE)) 
            {
                if(pSched->isRunning == DBFALSE) {
                    pSched->isRunning = DBTRUE;

                    int rscode = pthread_create(& pSched->threadHnd, NULL, ext_sched_start, pSched);    
                    if(rscode == -1)
                        errMsg(__HORUSWRK_EXT_SCHED_H, "start()", ERR_CANTMODULESTARTTHREAD);
                }
            }
        }
    }
    
    return RSOK;
}

// execute(): function called when the module is schedule for execution
// module_name - module register name in the server
int CExtSched::execute(char* module_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE)) 
            {
                if(pSched->isRunning == DBFALSE) {
                    pSched->isRunning = DBTRUE;

                    int rscode = pthread_create(& pSched->threadHnd, NULL, ext_sched_execute, pSched);    
                    if(rscode == -1)
                        errMsg(__HORUSWRK_EXT_SCHED_H, "start()", ERR_CANTMODULEEXECUTETHREAD);
                }
            }
        }
    }
    
    return RSOK;
}

// sleep(): function called when the module is put to sleep
// module_name - module register name in the server
int CExtSched::sleep(char* module_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE) && (pSched->isRunning == DBTRUE)) {
                pModule->sleep();       
                pSched->isRunning = DBFALSE;                      
            }                 
        }
    }
    
    return RSOK;
}

// trainModel(): function to train the model with data array
// module_name - module register name in the server
// data - array of data
// data_sz - size of data array
// val - data classification
int CExtSched::trainModel(char* module_name, unsigned char* data, int data_sz, double val)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE)) 
            {
                if(pSched->isRunning == DBFALSE) {
                    pSched->isRunning = DBTRUE;

                    int rscode = pthread_create(& pSched->threadHnd, NULL, ext_sched_train, pSched);    
                    if(rscode == -1)
                        errMsg(__HORUSWRK_EXT_SCHED_H, "start()", ERR_CANTMODULETRAINTHREAD);
                }
            }
        }
    }
    
    return RSOK;
}

// trainModelWithMask(): function to train the model with data and mask
// module_name - module register name in the server
// data - array of data
// data_sz - size of data array
// data_mask - array of data mask
// data_mask_sz - size of data mask array
// val - data classification
int CExtSched::trainModelWithMask(char* module_name, unsigned char* data, int data_sz, unsigned char* data_mask, int data_mask_sz, double val)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE)) 
            {
                if(pSched->isRunning == DBFALSE) {
                    pSched->isRunning = DBTRUE;

                    int rscode = pthread_create(& pSched->threadHnd, NULL, ext_sched_train_with_mask, pSched);    
                    if(rscode == -1)
                        errMsg(__HORUSWRK_EXT_SCHED_H, "start()", ERR_CANTMODULETRAINWITHMASKTHREAD);
                }
            }
        }
    }
    
    return RSOK;
}

// classify(): function to classify the data
// module_name - module register name in the server
// data - array of data
// data_sz - size of data array
// resval - classification result value
int CExtSched::classify(char* module_name, unsigned char* data, int data_sz, double* resval)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE)) 
            {
                if(pSched->isRunning == DBFALSE) {
                    pSched->isRunning = DBTRUE;

                    int rscode = pthread_create(& pSched->threadHnd, NULL, ext_sched_classify, pSched);    
                    if(rscode == -1)
                        errMsg(__HORUSWRK_EXT_SCHED_H, "start()", ERR_CANTMODULECLASSIFYTHREAD);
                }
            }
        }
    }
    
    return RSOK;
}

// saveModel(): function to save data model
// module_name - module register name in the server
// model_name - model name
// model_file_name - model file name
int CExtSched::saveModel(char* module_name, char* model_name, char* model_file_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE) && (pSched->isRunning == DBFALSE)) 
            {
                pModule->saveModel(model_name, model_file_name);                        
            }
        }
    }
    
    return RSOK;
}

// loadModel(): function to load data model
// module_name - module register name in the server
// model_name - model name
// model_file_name - model file name
int CExtSched::loadModel(char* module_name, char* model_name, char* model_file_name)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(strNCmpUtil(pModule->getModuleName(), module_name, STRSZ) == 0)
        {
            if((pSched->isLoaded == DBTRUE) && (pSched->isInitialized == DBTRUE) && (pSched->isRunning == DBFALSE)) 
            {
                pModule->loadModel(model_name, model_file_name);                        
            }
        }
    }
    
    return RSOK;
}

/* Getters/Setters */

sched_t* CExtSched::getSchedByModuleOid(long oid)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        if(pModule->getModuleOid() == oid)
            return pSched;
    }

    return NULL;
}

sched_t* CExtSched::getSchedByModuleName(char* moduleName)
{
    for(long i = 0; i < m_currNumModules; i++) {
        sched_t *pSched = & m_pLsModules[i];
        CExtModule* pModule = (CExtModule*)pSched->pModule;

        int rscode = strNCmpUtil(pModule->getModuleName(), moduleName, STRSZ);
        if(rscode == 0)
            return pSched;
    }

    return NULL;
}

// Management Of Sched List

int CExtSched::getCurrNumModules()
{
    return m_currNumModules;
}

int CExtSched::getNumLoadedModules()
{
    return m_numLoadedModules;
}

int CExtSched::getNumRunningModules()
{
    return m_numRunningModules;
}

/* Extension Sched Threads */

void* ext_sched_start(void* _pArgs)
{
    sched_t* pSched = (sched_t*)_pArgs;
    CExtModule* pModule = (CExtModule*)pSched->pModule;

    printf("Started: %s\n", (char*)pModule->getModuleName());
    pModule->start();

    pSched->isRunning = DBFALSE;                      

    pthread_exit(NULL);
}

void* ext_sched_execute(void* _pArgs)
{
    sched_t* pSched = (sched_t*)_pArgs;
    CExtModule* pModule = (CExtModule*)pSched->pModule;

    printf("Module Execute: %s\n", (char*)pModule->getModuleName());
    pModule->execute();

    pSched->isRunning = DBFALSE;                      

    printf("Module: %s... Completed!\n", (char*)pModule->getModuleName());
    pthread_exit(NULL);
}

void* ext_sched_train(void* _pArgs)
{
    sched_t* pSched = (sched_t*)_pArgs;
    CExtModule* pModule = (CExtModule*)pSched->pModule;

    printf("Module Train: %s\n", (char*)pModule->getModuleName());
    pModule->trainModel((byte*)pSched->pData, pSched->dataSz, pSched->val);

    pSched->isRunning = DBFALSE;                      

    printf("Module: %s... Completed!\n", (char*)pModule->getModuleName());
    pthread_exit(NULL);
}

void* ext_sched_train_with_mask(void* _pArgs)
{
    sched_t* pSched = (sched_t*)_pArgs;
    CExtModule* pModule = (CExtModule*)pSched->pModule;

    printf("Module Train with Mask: %s\n", (char*)pModule->getModuleName());
    pModule->trainModelWithMask((byte*)pSched->pData, pSched->dataSz, (byte*)pSched->pDataMask, pSched->dataMaskSz, pSched->val);

    pSched->isRunning = DBFALSE;                      

    printf("Module: %s... Completed!\n", (char*)pModule->getModuleName());
    pthread_exit(NULL);
}

void* ext_sched_classify(void* _pArgs)
{
    sched_t* pSched = (sched_t*)_pArgs;
    CExtModule* pModule = (CExtModule*)pSched->pModule;

    printf("Module Classify: %s\n", (char*)pModule->getModuleName());
    pModule->classify((byte*)pSched->pData, pSched->dataSz, & pSched->resval);

    pSched->isRunning = DBFALSE;                      

    printf("Module: %s... Completed!\n", (char*)pModule->getModuleName());
    pthread_exit(NULL);
}
