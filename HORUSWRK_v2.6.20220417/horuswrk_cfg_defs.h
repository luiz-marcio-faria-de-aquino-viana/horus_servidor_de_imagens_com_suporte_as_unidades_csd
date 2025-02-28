/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 25/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_DEFS_H
#define __HORUSWRK_CFG_DEFS_H                           "__HORUSWRK_CFG_DEFS_H"

#define HORUSWRK_HOME                                   ((char*)"HORUSWRK_HOME")       // application enviroment variable

/* DEFAULT DIRECTORIES AND FILES
 */
#define HOME_DIR                                        ((char*)"../../../")
//
#define BIN_DIR                                         ((char*)"Bin/")
#define CONFIG_DIR                                      ((char*)"Config/")
#define DATA_DIR                                        ((char*)"Data/")
#define LOG_DIR                                         ((char*)"Log/")
#define MODULE_DIR                                      ((char*)"Modules/")
#define TEMP_DIR                                        ((char*)"Temp/")
#define TMP_DIR                                         ((char*)"Tmp/")
//
#define IMGSRC_DIR                                      ((char*)"U211_DAT/tbl_imgrio/")
#define IMGDST_DIR                                      ((char*)"U211_DAT/tbl_imgrio_temp/")
//
#define CONFIG_FILE                                     ((char*)"config.xml")
#define DEFAULT_CONFIG_FILE                             ((char*)"default-config.xml")
//
#define DEFAULT_DIR_TABLE_FILE                          ((char*)"DirTableFile.dat")
#define DEFAULT_SUPERBLOCK_TABLE_FILE                   ((char*)"SuperBlockTableFile_%ld.dat")
#define DEFAULT_BLOCK_TABLE_FILE                        ((char*)"BlockTableFile_%ld_%ld.dat")
#define DEFAULT_DATA_FILE                               ((char*)"DataFile_%ld_%ld.hdi")
//
#define LOG_FILE                                        ((char*)"horussrv-%s.log")

/* DEFAULT MAXIMUM NUMBER OF REMOTE UNITS
 */
#define DEF_MAX_NUM_REMOTEUNIT                          32

/* DEFAULT CONFIG DATA
 */
//REMOTEUNIT
#define DEF_DEFAULT_REMOTEUNIT_OID_1                    211
#define DEF_DEFAULT_REMOTEUNIT_NAME_1                   "U211"
#define DEF_DEFAULT_REMOTEUNIT_IPADDR_1                 "192.168.55.11"
#define DEF_DEFAULT_REMOTEUNIT_IN_PORT_1                8184
#define DEF_DEFAULT_REMOTEUNIT_OUT_PORT_1               8183
#define DEF_DEFAULT_REMOTEUNIT_TBLSPCNAME_1             "U211"
#define DEF_DEFAULT_REMOTEUNIT_ENABLE_1                 1
#define DEF_DEFAULT_REMOTEUNIT_KEY_1                    "ABACABA_U211"
#define DEF_DEFAULT_REMOTEUNIT_WORKNODE_1               1
#define DEF_DEFAULT_REMOTEUNIT_NAMENODE_1               1
#define DEF_DEFAULT_REMOTEUNIT_DATANODE_1               1
#define DEF_DEFAULT_REMOTEUNIT_RUNLOCAL_1               1
//HOSTSERVER
#define DEF_DEFAULT_HOSTSERVER_OID_1                    11
#define DEF_DEFAULT_HOSTSERVER_NAME_1                   "HORUSSRV211"
#define DEF_DEFAULT_HOSTSERVER_IPADDR_1                 "192.168.55.11"
#define DEF_DEFAULT_HOSTSERVER_IN_PORT_1                8183
#define DEF_DEFAULT_HOSTSERVER_OUT_PORT_1               8184
#define DEF_DEFAULT_HOSTSERVER_KEY_1                    "ABACABA_S211"

/* CONFIG FILE TAGS XML
 */
//#define DEF_TAGXML_VERSION                      "<?xml version='1.0' encoding='ISO-8859-1'?>"
//CONFIG
//#define DEF_TAGXML_CONFIG                       "Config"
//REMOTEUNIT
//#define DEF_TAGXML_REMOTEUNIT                   "RemoteUnit"
//#define DEF_TAGXML_REMOTEUNIT_OID               "Oid"
//#define DEF_TAGXML_REMOTEUNIT_NAME              "Name"
//#define DEF_TAGXML_REMOTEUNIT_IPADDR            "IPAddr"
//#define DEF_TAGXML_REMOTEUNIT_PORT              "Port"
//#define DEF_TAGXML_REMOTEUNIT_TBLSPCNAME        "TableSpaceName"
//#define DEF_TAGXML_REMOTEUNIT_ENABLED           "Enabled"
//#define DEF_TAGXML_REMOTEUNIT_KEY               "Key"
//HOSTSERVER
//#define DEF_TAGXML_HOSTSERVER                   "HostServer"
//#define DEF_TAGXML_HOSTSERVER_OID               "Oid"
//#define DEF_TAGXML_HOSTSERVER_NAME              "Name"
//#define DEF_TAGXML_HOSTSERVER_IPADDR            "IPAddr"
//#define DEF_TAGXML_HOSTSERVER_PORT              "Port"
//#define DEF_TAGXML_HOSTSERVER_KEY               "Key"
//MODULES
//#define DEF_TAGXML_MODULES                      "Modules"
//MODULE
//#define DEF_TAGXML_MODULE                       "Module"
//#define DEF_TAGXML_MODULE_OID                   "ModuleOid"
//#define DEF_TAGXML_MODULE_NAME                  "ModuleName"
//#define DEF_TAGXML_MODULE_FILE_NAME             "ModuleFileName"
//PARAMETERS
//#define DEF_TAGXML_PARAMETERS                   "Parameters"
//PARAMETER
//#define DEF_TAGXML_PARAMETER                    "Parameter"
//#define DEF_TAGXML_PARAMETER_NAME               "ParameterName"
//#define DEF_TAGXML_PARAMETER_VALUE              "ParameterValue"
//#define DEF_TAGXML_PARAMETER_MODE               "ParameterMode"
//DISKGROUPS
//#define DEF_TAGXML_DISKGROUPS                   "DiskGroups"
//DISKGROUP
//#define DEF_TAGXML_DISKGROUP                    "DiskGroup"
//#define DEF_TAGXML_DISKGROUP_UID                "Uid"
//#define DEF_TAGXML_DISKGROUP_NAME               "Name"
//#define DEF_TAGXML_DISKGROUP_NUMOFDISKS         "NumOfDisks"
//#define DEF_TAGXML_DISKGROUP_NUMOFCOPIES        "NumOfCopies"
//DISKDEVICES
//#define DEF_TAGXML_DISKDEVICES                  "DiskDevices"
//DISKDEVICE
//#define DEF_TAGXML_DISKDEVICE                   "DiskDevice"
//#define DEF_TAGXML_DISKDEVICE_UID               "UID"
//#define DEF_TAGXML_DISKDEVICE_NAME              "Name"
//#define DEF_TAGXML_DISKDEVICE_DIRTABLEFILE      "DirTableFile"
//#define DEF_TAGXML_DISKDEVICE_DATAFILE          "DataFile"
//#define DEF_TAGXML_DISKDEVICE_NUMBEROFBLOCKS    "NumOfBlocks"
//#define DEF_TAGXML_DISKDEVICE_BLOCKSIZE         "BlockSize"

/* CONFIG FILE TAGS TXT FILE
 */
//CURRENT UNIT
#define DEF_TAGTXT_CURRENT_REMOTEUNIT_OID               "CURRENT_REMOTEUNIT_OID"
//HOSTSERVER
#define DEF_TAGTXT_HOSTSERVER_OID                       "HOSTSERVER_OID"
#define DEF_TAGTXT_HOSTSERVER_NAME                      "HOSTSERVER_NAME"
#define DEF_TAGTXT_HOSTSERVER_IPADDR                    "HOSTSERVER_IPADDR"
#define DEF_TAGTXT_HOSTSERVER_IN_PORT                   "HOSTSERVER_IN_PORT"
#define DEF_TAGTXT_HOSTSERVER_OUT_PORT                  "HOSTSERVER_OUT_PORT"
#define DEF_TAGTXT_HOSTSERVER_KEY                       "HOSTSERVER_KEY"
//REMOTEUNITS
#define DEF_TAGTXT_NUMOFREMOTEUNITS                     "NUMOFREMOTEUNITS"
//REMOTEUNIT
#define DEF_TAGTXT_REMOTEUNIT_OID                       "REMOTEUNIT%d_OID"
#define DEF_TAGTXT_REMOTEUNIT_NAME                      "REMOTEUNIT%d_NAME"
#define DEF_TAGTXT_REMOTEUNIT_IPADDR                    "REMOTEUNIT%d_IPADDR"
#define DEF_TAGTXT_REMOTEUNIT_IN_PORT                   "REMOTEUNIT%d_IN_PORT"
#define DEF_TAGTXT_REMOTEUNIT_OUT_PORT                  "REMOTEUNIT%d_OUT_PORT"
#define DEF_TAGTXT_REMOTEUNIT_TBLSPCNAME                "REMOTEUNIT%d_TBLSPCNAME"
#define DEF_TAGTXT_REMOTEUNIT_ENABLED                   "REMOTEUNIT%d_ENABLED"
#define DEF_TAGTXT_REMOTEUNIT_KEY                       "REMOTEUNIT%d_KEY"
#define DEF_TAGTXT_REMOTEUNIT_WORKNODE                  "REMOTEUNIT%d_WORKNODE"
#define DEF_TAGTXT_REMOTEUNIT_NAMENODE                  "REMOTEUNIT%d_NAMENODE"
#define DEF_TAGTXT_REMOTEUNIT_DATANODE                  "REMOTEUNIT%d_DATANODE"
#define DEF_TAGTXT_REMOTEUNIT_RUNLOCAL                  "REMOTEUNIT%d_RUNLOCAL"
//MODULES
#define DEF_TAGTXT_NUMOFMODULES                         "NUMOFMODULES"
//MODULE
#define DEF_TAGTXT_MODULE_OID                           "MODULE%d_OID"
#define DEF_TAGTXT_MODULE_NAME                          "MODULE%d_NAME"
#define DEF_TAGTXT_MODULE_FILE_NAME                     "MODULE%d_FILE_NAME"
//PARAMETERS
#define DEF_TAGTXT_NUMOFPARAMS                          "MODULE%d_NUMOFPARAMS"
//PARAMETER
#define DEF_TAGTXT_PARAM_NAME                           "MODULE%d_PARAM%d_NAME"
#define DEF_TAGTXT_PARAM_VALUE                          "MODULE%d_PARAM%d_VALUE"
#define DEF_TAGTXT_PARAM_MODE                           "MODULE%d_PARAM%d_MODE"
//DISKGROUPS
#define DEF_TAGTXT_NUMOFDISKGROUPS                      "NUMOFDISKGROUPS"
//DISKGROUP
#define DEF_TAGTXT_DISKGROUP_OID                        "DISKGROUP%d_OID"
#define DEF_TAGTXT_DISKGROUP_REMOTEUNIT_OID             "DISKGROUP%d_REMOTEUNIT_OID"
#define DEF_TAGTXT_DISKGROUP_NAME                       "DISKGROUP%d_NAME"
#define DEF_TAGTXT_DISKGROUP_NUMOFDISKS                 "DISKGROUP%d_NUMOFDISKS"
#define DEF_TAGTXT_DISKGROUP_NUMOFCOPIES                "DISKGROUP%d_NUMOFCOPIES"
#define DEF_TAGTXT_DISKGROUP_NUMBEROFSUPERBLOCKS        "DISKGROUP%d_NUMOFSUPERBLOCKS"
#define DEF_TAGTXT_DISKGROUP_NUMBEROFBLOCKS             "DISKGROUP%d_NUMOFBLOCKS"
#define DEF_TAGTXT_DISKGROUP_BLOCKSIZE                  "DISKGROUP%d_BLOCKSIZE"
//DISKDEVICE
#define DEF_TAGTXT_DISKDEV_OID                          "DISKGROUP%d_DISKDEV%d_OID"
#define DEF_TAGTXT_DISKDEV_NAME                         "DISKGROUP%d_DISKDEV%d_NAME"
#define DEF_TAGTXT_DISKDEV_REMOTEUNIT_OID               "DISKGROUP%d_DISKDEV%d_REMOTEUNIT_OID"

/* CONFIG TAGS QUANTITY
*/
#define DEF_TAGQTY_CURR_REMOTEUNIT                      1           //1 PARAMS
#define DEF_TAGQTY_HOSTSERVER                           1           //1x6=6 PARAMS
#define DEF_TAGQTY_REMOTEUNITS                          24          //1+24x12=279 PARAMS
#define DEF_TAGQTY_MODULES                              10          //10x4=40 PARAMS
#define DEF_TAGQTY_PARAMS_PER_MODULE                    10          //10x3=30 PARAMS
#define DEF_TAGQTY_DISKGROUPS                           12          //12x7=72 PARAMS
#define DEF_TAGQTY_DISKDEV_PER_DISKGROUP                6           //6x3=18 PARAMS
//
#define DEF_TAGQTY_MAXNUMTAGS                           1500        //TOTAL=998 PARAMS

/* CONFIG TAGS STRUCT
 */
typedef struct config_tag_struct {
    long tag_id;
    bigstr_t tag_name;
    bigstr_t tag_value;
} config_tag_t;

#endif
