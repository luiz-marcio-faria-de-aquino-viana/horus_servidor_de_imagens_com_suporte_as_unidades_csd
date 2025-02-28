/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_module.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CExtModule::CExtModule(long moduleOid, char* moduleName, char* moduleFileName)
{
    m_moduleOid = moduleOid;
    strNCpyUtil(m_moduleName, moduleName, STRSZ);
    strNCpyUtil(m_moduleFileName, moduleFileName, BIGSTRSZ);
}

CExtModule::~CExtModule()
{
    dlclose(m_libHnd);
}

/* Methodes */

// loadModule(): function called when the module is loaded
void CExtModule::loadModule()
{
    char* err;

    //LOAD_MODULE_FILE
    //
    m_libHnd = dlopen(m_moduleFileName, RTLD_LAZY);
    if( !m_libHnd ) {
        err = dlerror();
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);
    }

	m_pHmiLoadModule = (double (*)(int, char*, char*))dlsym(m_libHnd, "hmiLoadModule");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiInitModule = (double (*)(int, char**, char**))dlsym(m_libHnd, "hmiInitModule");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHhmiTerminateModule = (double (*)())dlsym(m_libHnd, "hmiTerminateModule");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiStart = (double (*)())dlsym(m_libHnd, "hmiStart");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiExecute = (double (*)())dlsym(m_libHnd, "hmiExecute");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiSleep = (double (*)())dlsym(m_libHnd, "hmiSleep");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiTrainModel = (double (*)(unsigned char*, int, double))dlsym(m_libHnd, "hmiTrainModel");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiTrainModelWithMask = (double (*)(unsigned char*, int, unsigned char*, int, double))dlsym(m_libHnd, "hmiTrainModelWithMask");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiClassify = (double (*)(unsigned char*, int, double*))dlsym(m_libHnd, "hmiClassify");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiSaveModel = (double (*)(char*, char*))dlsym(m_libHnd, "hmiSaveModel");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiLoadModel = (double (*)(char*, char*))dlsym(m_libHnd, "hmiLoadModel");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    m_pHmiCallback = (double (*)(int, char*, int, void*, long))dlsym(m_libHnd, "hmiCallback");
	if((err = dlerror()) != NULL) 
        errMsg(__HORUSWRK_EXT_MODULE_H, "loadModuleFile()", err);

    (*m_pHmiLoadModule)(m_moduleOid, m_moduleName, m_moduleFileName);
}

// initModule(): function called to initialize the module
// numParms - number of parameters passed to the initialization
// parmNames - name of parameters passed to the initialization
// parmValues - value of parameters passed to the initialization
void CExtModule::initModule(int numParms, char* parmNames[], char* parmValues[])
{
    (*m_pHmiInitModule)(numParms, parmNames, parmValues);    
}

// hmiTerminateModule(): function to terminate the model
void CExtModule::terminateModule()
{
    (*m_pHhmiTerminateModule)();    
}

// hmiStart(): function called when the module is started
void CExtModule::start()
{
    (*m_pHmiStart)();    
}

// hmiExecute(): function called when the module is schedule for execution
void CExtModule::execute()
{
    (*m_pHmiExecute)();
}

// hmiSleep(): function called when the module is put to sleep
void CExtModule::sleep()
{
    (*m_pHmiSleep)();
}

// hmiTrainModel(): function to train the model with data array
// data - array of data
// data_sz - size of data array
// val - data classification
void CExtModule::trainModel(unsigned char* data, int data_sz, double val)
{
    (*m_pHmiTrainModel)(data, data_sz, val);
}

// hmiTrainModelWithMask(): function to train the model with data and mask
// data - array of data
// data_sz - size of data array
// data_mask - array of data mask
// data_mask_sz - size of data mask array
// val - data classification
void CExtModule::trainModelWithMask(unsigned char* data, int data_sz, unsigned char* data_mask, int data_mask_sz, double val)
{
    (*m_pHmiTrainModelWithMask)(data, data_sz, data_mask, data_mask_sz, val);
}

// hmiClassify(): function to classify the data
// data - array of data
// data_sz - size of data array
// resval - classification result value
void CExtModule::classify(unsigned char* data, int data_sz, double* resval)
{
    (*m_pHmiClassify)(data, data_sz, resval);
}

// hmiSaveModel(): function to save data model
// moduleId - module identification in the server
// modelName - model name
// modelFileName - model file name
void CExtModule::saveModel(char* modelName, char* modelFileName)
{
    (*m_pHmiSaveModel)(modelName, modelFileName);
}

// hmiLoadModel(): function to load data model
// moduleId - module identification in the server
// modelName - model name
// modelFileName - model file name
void CExtModule::loadModel(char* modelName, char* modelFileName)
{
    (*m_pHmiLoadModel)(modelName, modelFileName);    
}

// hmiCallback(): callback function
// moduleId - module identification in the server
// modelName - model name
// returnData - pointer to return data
void CExtModule::callback(int moduleId, char* modelName, int returnType, void* returnData, long returnDataSz)
{
    (*m_pHmiCallback)(moduleId, modelName, returnType, returnData, returnDataSz);        
}

/* Getters/Setters */

long CExtModule::getModuleOid()
{
    return m_moduleOid;
}

char* CExtModule::getModuleName()
{
    return m_moduleName;    
}

char* CExtModule::getModuleFileName()
{
    return m_moduleFileName;    
}
