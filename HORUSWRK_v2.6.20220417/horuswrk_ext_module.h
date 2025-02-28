/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_module.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_EXT_MODULE_H
#define __HORUSWRK_EXT_MODULE_H                     "__HORUSWRK_EXT_MODULE_H"

class CExtModule
{
private:
    long m_moduleOid;
    str_t m_moduleName;
    str_t m_moduleFileName;

    void* m_libHnd;

    //IHorusModule
    double (*m_pHmiLoadModule)(int, char*, char*);
    double (*m_pHmiInitModule)(int, char**, char**);
    double (*m_pHhmiTerminateModule)();
    double (*m_pHmiStart)();
    double (*m_pHmiExecute)();
    double (*m_pHmiSleep)();
    double (*m_pHmiTrainModel)(unsigned char*, int, double);
    double (*m_pHmiTrainModelWithMask)(unsigned char*, int, unsigned char*, int, double);
    double (*m_pHmiClassify)(unsigned char*, int, double*);
    double (*m_pHmiSaveModel)(char*, char*);
    double (*m_pHmiLoadModel)(char*, char*);
    double (*m_pHmiCallback)(int, char*, int, void*, long);

public:

    CExtModule(long moduleOid, char* moduleName, char* moduleFileName);
    ~CExtModule();

    /* Methodes */

    // loadModule(): function called when the module is loaded
    void loadModule();

    // initModule(): function called to initialize the module
    // numParms - number of parameters passed to the initialization
    // parmNames - name of parameters passed to the initialization
    // parmValues - value of parameters passed to the initialization
    void initModule(int numParms, char* parmNames[], char* parmValues[]);

    // hmiTerminateModule(): function to terminate the model
    void terminateModule();

    // hmiStart(): function called when the module is started
    void start();

    // hmiExecute(): function called when the module is schedule for execution
    void execute();

    // hmiSleep(): function called when the module is put to sleep
    void sleep();

    // hmiTrainModel(): function to train the model with data array
    // data - array of data
    // data_sz - size of data array
    // val - data classification
    void trainModel(unsigned char* data, int data_sz, double val);

    // hmiTrainModelWithMask(): function to train the model with data and mask
    // data - array of data
    // data_sz - size of data array
    // data_mask - array of data mask
    // data_mask_sz - size of data mask array
    // val - data classification
    void trainModelWithMask(unsigned char* data, int data_sz, unsigned char* data_mask, int data_mask_sz, double val);

    // hmiClassify(): function to classify the data
    // data - array of data
    // data_sz - size of data array
    // resval - classification result value
    void classify(unsigned char* data, int data_sz, double* resval);

    // hmiSaveModel(): function to save data model
    // moduleId - module identification in the server
    // modelName - model name
    // modelFileName - model file name
    void saveModel(char* modelName, char* modelFileName);

    // hmiLoadModel(): function to load data model
    // moduleId - module identification in the server
    // modelName - model name
    // modelFileName - model file name
    void loadModel(char* modelName, char* modelFileName);

    // hmiCallback(): callback function
    // moduleId - module identification in the server
    // modelName - model name
    // returnData - pointer to return data
    void callback(int moduleId, char* modelName, int returnType, void* returnData, long returnDataSz);

    /* Getters/Setters */

    long getModuleOid();

    char* getModuleName();

    char* getModuleFileName();

};

/* NEW_TYPE: CExtModule Pointer */

typedef CExtModule* CExtModulePtr_t;

#endif
