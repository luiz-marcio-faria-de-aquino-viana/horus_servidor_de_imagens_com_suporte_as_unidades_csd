/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_ext_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 21/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_EXT_DEFS_H
#define __HORUSWRK_EXT_DEFS_H                   "__HORUSWRK_EXT_DEFS_H"

/* DEFINITIONS
 */

#define MAX_REGISTERED_MODULES      32

#define MAX_RUNNING_MODULES         4

/* PARAM MODE
*/
#define DEF_PARAMMODE_FIXED         1
#define DEF_PARAMMODE_VARIABLE      2

//MODULES
#define DEF_XML_MODULES                       ((char*)"<Modules>%s</Modules>")
#define DEF_XML_MODULE                        ((char*)"<Module><ModuleOid>%ld</ModuleOid><ModuleName>%s</ModuleName><ModuleFileName>%s</ModuleFileName><Parameters>%s</Parameters></Module>")
#define DEF_XML_MODULE_PARAM                  ((char*)"<Parameter><ParameterName>%ld</ParameterName><ParameterValue>%ld</ParameterValue><ParameterMode>%ld</ParameterMode></Parameter>")

/* SCHED TABLE
 */
typedef struct sched_struct {
    void* pModule;                  // 4B
    pthread_t threadHnd;            // 4B
    long isLoaded;                  // 4B
    long isInitialized;             // 4B
    long isRunning;                 // 4B
    void* pData;                    // 4B
    long dataSz;                    // 4B
    void* pDataMask;                // 4B
    long dataMaskSz;                // 4B
    double val;                     // 4B
    double resval;                  // 4B
} sched_t;                          // TOTAL = 44B

#endif
