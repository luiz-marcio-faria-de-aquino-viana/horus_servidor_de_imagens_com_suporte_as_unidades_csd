/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_sched.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_EXT_SCHED_H
#define __HORUSWRK_EXT_SCHED_H                     "__HORUSWRK_EXT_SCHED_H"

class CExtSched
{
private:
    sched_t* m_pLsModules;
    int m_numMaxModules;

    int m_currNumModules;
    int m_numLoadedModules;
    int m_numRunningModules;

public:

    CExtSched(int numMaxModules);
    ~CExtSched();

    /* Methodes */

    int init();

    /* Module Operations */

    // loadModule(): function called when the module is loaded
    // module_name - module register name in the server
    int loadModule(char* module_name);

    // initModule(): function called to initialize the module
    // module_name - module register name in the server
    int initModule(char* module_name, int numParms, char* parmNames[], char* parmValues[]);

    // terminateModule(): function to terminate the model
    // module_name - module register name in the server
    int terminateModule(char* module_name);

    // start(): function called when the module is started
    // module_name - module register name in the server
    int start(char* module_name);

    // execute(): function called when the module is schedule for execution
    // module_name - module register name in the server
    int execute(char* module_name);

    // sleep(): function called when the module is put to sleep
    // module_name - module register name in the server
    int sleep(char* module_name);

    // trainModel(): function to train the model with data array
    // module_name - module register name in the server
    // data - array of data
    // data_sz - size of data array
    // val - data classification
    int trainModel(char* module_name, unsigned char* data, int data_sz, double val);

    // trainModelWithMask(): function to train the model with data and mask
    // module_name - module register name in the server
    // data - array of data
    // data_sz - size of data array
    // data_mask - array of data mask
    // data_mask_sz - size of data mask array
    // val - data classification
    int trainModelWithMask(char* module_name, unsigned char* data, int data_sz, unsigned char* data_mask, int data_mask_sz, double val);

    // classify(): function to classify the data
    // module_name - module register name in the server
    // data - array of data
    // data_sz - size of data array
    // resval - classification result value
    int classify(char* module_name, unsigned char* data, int data_sz, double* resval);

    // saveModel(): function to save data model
    // module_name - module register name in the server
    // model_name - model name
    // model_file_name - model file name
    int saveModel(char* module_name, char* model_name, char* model_file_name);

    // loadModel(): function to load data model
    // module_name - module register name in the server
    // model_name - model name
    // model_file_name - model file name
    int loadModel(char* module_name, char* model_name, char* model_file_name);

    /* Getters/Setters */

    sched_t* getSchedByModuleOid(long oid);

    sched_t* getSchedByModuleName(char* moduleName);

    // Management Of Sched List

    int getCurrNumModules();

    int getNumLoadedModules();

    int getNumRunningModules();

};

/* NEW_TYPE: CExtSched Pointer */

typedef CExtSched* CExtSchedPtr_t;

/* Extension Sched Global Declaration */

extern CExtSched gExtSched;

/* Extension Sched Threads */

extern void* ext_sched_start(void* _pArgs);

extern void* ext_sched_execute(void* _pArgs);

extern void* ext_sched_train(void* _pArgs);

extern void* ext_sched_train_with_mask(void* _pArgs);

extern void* ext_sched_classify(void* _pArgs);

#endif
