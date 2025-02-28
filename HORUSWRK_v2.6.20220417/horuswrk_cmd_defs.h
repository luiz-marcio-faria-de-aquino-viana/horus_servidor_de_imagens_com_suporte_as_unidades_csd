/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_DEFS_H
#define __HORUSWRK_CMD_DEFS_H                   "__HORUSWRK_CMD_DEFS_H"

#define DEF_DEFAULT_PROTOCOL                    "UDP"

#define DEF_DEFAULT_SERVERTERMMSG               "\\."
#define DEF_DEFAULT_SERVERTERMMSGLEN            2

#define DEF_DEFAULT_WEBCONTEXT                  "horuswrk"

#define DEF_DEFAULT_REQBUFSIZE                  4096

#define DEF_DEFAULT_RESPBUFSIZE                 4096

#define DEF_MAX_NUM_CONNECTION                  40

#define DEF_MAX_NUM_EXEC_THREADS                4

#define BUFSZ                                   4096

typedef byte buf_t[BUFSZ];

//*** Request Actions (string)
#define DEF_REQ_ACTION_UNKNOW                           ((char*)"UNKNOW")
//BLOCK_READ_WRITE_REQUEST_ACTIONS
#define DEF_REQ_ACTION_REQWRITEBLOCK                    ((char*)"req-wblock")
#define DEF_REQ_ACTION_REQREADBLOCK                     ((char*)"req-rblock")
//BLOCK_READ_WRITE_RESPONSE_ACTIONS
#define DEF_REQ_ACTION_RESPWRITEBLOCK                   ((char*)"resp-wblock")
#define DEF_REQ_ACTION_RESPREADBLOCK                    ((char*)"resp-rblock")
//CONVERT_MOD
#define DEF_REQ_ACTION_TS1_CONVERT                      ((char*)"ts1-C")
#define DEF_REQ_ACTION_TS2_CONVERT                      ((char*)"ts2-C")
#define DEF_REQ_ACTION_TS3_CONVERT                      ((char*)"ts3-C")
#define DEF_REQ_ACTION_TS4_CONVERT                      ((char*)"ts4-C")
#define DEF_REQ_ACTION_TS5_CONVERT                      ((char*)"ts5-C")
#define DEF_REQ_ACTION_TS6_CONVERT                      ((char*)"ts6-C")
//REPROJ_MOD
#define DEF_REQ_ACTION_TS1_REPROJ                       ((char*)"ts1-R")
#define DEF_REQ_ACTION_TS2_REPROJ                       ((char*)"ts2-R")
#define DEF_REQ_ACTION_TS3_REPROJ                       ((char*)"ts3-R")
#define DEF_REQ_ACTION_TS4_REPROJ                       ((char*)"ts4-R")
#define DEF_REQ_ACTION_TS5_REPROJ                       ((char*)"ts5-R")
#define DEF_REQ_ACTION_TS6_REPROJ                       ((char*)"ts6-R")
//SIMPL_MOD
#define DEF_REQ_ACTION_TS1_SIMPL                        ((char*)"ts1-S")
#define DEF_REQ_ACTION_TS2_SIMPL                        ((char*)"ts2-S")
#define DEF_REQ_ACTION_TS3_SIMPL                        ((char*)"ts3-S")
#define DEF_REQ_ACTION_TS4_SIMPL                        ((char*)"ts4-S")
#define DEF_REQ_ACTION_TS5_SIMPL                        ((char*)"ts5-S")
#define DEF_REQ_ACTION_TS6_SIMPL                        ((char*)"ts6-S")
//UPLOAD
#define DEF_REQ_ACTION_TS1_UPLOAD                       ((char*)"ts1-U")
#define DEF_REQ_ACTION_TS2_UPLOAD                       ((char*)"ts2-U")
#define DEF_REQ_ACTION_TS3_UPLOAD                       ((char*)"ts3-U")
#define DEF_REQ_ACTION_TS4_UPLOAD                       ((char*)"ts4-U")
#define DEF_REQ_ACTION_TS5_UPLOAD                       ((char*)"ts5-U")
#define DEF_REQ_ACTION_TS6_UPLOAD                       ((char*)"ts6-U")
//DOWNLOAD
#define DEF_REQ_ACTION_TS1_DOWNLOAD                     ((char*)"ts1-D")
#define DEF_REQ_ACTION_TS2_DOWNLOAD                     ((char*)"ts2-D")
#define DEF_REQ_ACTION_TS3_DOWNLOAD                     ((char*)"ts3-D")
#define DEF_REQ_ACTION_TS4_DOWNLOAD                     ((char*)"ts4-D")
#define DEF_REQ_ACTION_TS5_DOWNLOAD                     ((char*)"ts5-D")
#define DEF_REQ_ACTION_TS6_DOWNLOAD                     ((char*)"ts6-D")
//MKDIR
#define DEF_REQ_ACTION_TS1_MKDIR                        ((char*)"ts1-M")
#define DEF_REQ_ACTION_TS2_MKDIR                        ((char*)"ts2-M")
#define DEF_REQ_ACTION_TS3_MKDIR                        ((char*)"ts3-M")
#define DEF_REQ_ACTION_TS4_MKDIR                        ((char*)"ts4-M")
#define DEF_REQ_ACTION_TS5_MKDIR                        ((char*)"ts5-M")
#define DEF_REQ_ACTION_TS6_MKDIR                        ((char*)"ts6-M")
//DOWNLOAD_AND_PROCESS
#define DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS         ((char*)"ts1-DP")
#define DEF_REQ_ACTION_TS2_DOWNLOAD_AND_PROCESS         ((char*)"ts2-DP")
#define DEF_REQ_ACTION_TS3_DOWNLOAD_AND_PROCESS         ((char*)"ts3-DP")
#define DEF_REQ_ACTION_TS4_DOWNLOAD_AND_PROCESS         ((char*)"ts4-DP")
#define DEF_REQ_ACTION_TS5_DOWNLOAD_AND_PROCESS         ((char*)"ts5-DP")
#define DEF_REQ_ACTION_TS6_DOWNLOAD_AND_PROCESS         ((char*)"ts6-DP")
//DOWNLOAD_AND_PROCESS (MODE=xx - ENABLE / DISABLE EXECUTION STEPS)
//#define DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS         ((char*)"ts1-DP(MODE=%ld)")
//#define DEF_REQ_ACTION_TS2_DOWNLOAD_AND_PROCESS         ((char*)"ts2-DP(MODE=%ld)")
//#define DEF_REQ_ACTION_TS3_DOWNLOAD_AND_PROCESS         ((char*)"ts3-DP(MODE=%ld)")
//#define DEF_REQ_ACTION_TS4_DOWNLOAD_AND_PROCESS         ((char*)"ts4-DP(MODE=%ld)")
//#define DEF_REQ_ACTION_TS5_DOWNLOAD_AND_PROCESS         ((char*)"ts5-DP(MODE=%ld)")
//#define DEF_REQ_ACTION_TS6_DOWNLOAD_AND_PROCESS         ((char*)"ts6-DP(MODE=%ld)")

//*** Request Actions (intval)
#define DEF_REQ_ACTION_UNKNOW_I                         -1
//BLOCK_READ_WRITE_REQUEST_ACTIONS
#define DEF_REQ_ACTION_REQWRITEBLOCK_I                  101
#define DEF_REQ_ACTION_REQREADBLOCK_I                   102
//BLOCK_READ_WRITE_RESPONSE_ACTIONS
#define DEF_REQ_ACTION_RESPWRITEBLOCK_I                 201
#define DEF_REQ_ACTION_RESPREADBLOCK_I                  202
//CONVERT_MOD
#define DEF_REQ_ACTION_TS1_CONVERT_I                    1001
#define DEF_REQ_ACTION_TS2_CONVERT_I                    1002
#define DEF_REQ_ACTION_TS3_CONVERT_I                    1003
#define DEF_REQ_ACTION_TS4_CONVERT_I                    1004
#define DEF_REQ_ACTION_TS5_CONVERT_I                    1005
#define DEF_REQ_ACTION_TS6_CONVERT_I                    1006
//REPROJ_MOD
#define DEF_REQ_ACTION_TS1_REPROJ_I                     2001
#define DEF_REQ_ACTION_TS2_REPROJ_I                     2002
#define DEF_REQ_ACTION_TS3_REPROJ_I                     2003
#define DEF_REQ_ACTION_TS4_REPROJ_I                     2004
#define DEF_REQ_ACTION_TS5_REPROJ_I                     2005
#define DEF_REQ_ACTION_TS6_REPROJ_I                     2006
//SIMPL_MOD
#define DEF_REQ_ACTION_TS1_SIMPL_I                      3001
#define DEF_REQ_ACTION_TS2_SIMPL_I                      3002
#define DEF_REQ_ACTION_TS3_SIMPL_I                      3003
#define DEF_REQ_ACTION_TS4_SIMPL_I                      3004
#define DEF_REQ_ACTION_TS5_SIMPL_I                      3005
#define DEF_REQ_ACTION_TS6_SIMPL_I                      3006
//UPLOAD
#define DEF_REQ_ACTION_TS1_UPLOAD_I                     9011
#define DEF_REQ_ACTION_TS2_UPLOAD_I                     9012
#define DEF_REQ_ACTION_TS3_UPLOAD_I                     9013
#define DEF_REQ_ACTION_TS4_UPLOAD_I                     9014
#define DEF_REQ_ACTION_TS5_UPLOAD_I                     9015
#define DEF_REQ_ACTION_TS6_UPLOAD_I                     9016
//DOWNLOAD
#define DEF_REQ_ACTION_TS1_DOWNLOAD_I                   9021
#define DEF_REQ_ACTION_TS2_DOWNLOAD_I                   9022
#define DEF_REQ_ACTION_TS3_DOWNLOAD_I                   9023
#define DEF_REQ_ACTION_TS4_DOWNLOAD_I                   9024
#define DEF_REQ_ACTION_TS5_DOWNLOAD_I                   9025
#define DEF_REQ_ACTION_TS6_DOWNLOAD_I                   9026
//MKDIR
#define DEF_REQ_ACTION_TS1_MKDIR_I                      9031
#define DEF_REQ_ACTION_TS2_MKDIR_I                      9032
#define DEF_REQ_ACTION_TS3_MKDIR_I                      9033
#define DEF_REQ_ACTION_TS4_MKDIR_I                      9034
#define DEF_REQ_ACTION_TS5_MKDIR_I                      9035
#define DEF_REQ_ACTION_TS6_MKDIR_I                      9036
//DOWNLOAD_AND_PROCESS
#define DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I       9041
#define DEF_REQ_ACTION_TS2_DOWNLOAD_AND_PROCESS_I       9042
#define DEF_REQ_ACTION_TS3_DOWNLOAD_AND_PROCESS_I       9043
#define DEF_REQ_ACTION_TS4_DOWNLOAD_AND_PROCESS_I       9044
#define DEF_REQ_ACTION_TS5_DOWNLOAD_AND_PROCESS_I       9045
#define DEF_REQ_ACTION_TS6_DOWNLOAD_AND_PROCESS_I       9046

//*** REQUEST COMMANDS
#define CMDWRK_REQUEST_COMMAND_1                "%ld^%s^%ld^%ld"            //Ex: [remote_unit_oid]^ts1-C^1^4

//*** NULL VALUES
#define DEF_REQ_OID_NULL                        -1
#define DEF_REQ_ROWID_NULL                      -1

//*** Connection
typedef struct connection_struct {
    int reqnum;
    int socketHnd;
    struct sockaddr_in caddr;
    socklen_t caddr_len;
    pthread_t threadHnd;
    buf_t in_buf;
    int in_len;
} connection_t;

//*** Event Data
typedef struct event_data_struct {
    //RET-Event Type
    int type;
    //RET-Result Code
    int rscode;
    //RET-Connect
    char* ret_session;
    long ret_sessionlen;
    //RET-ListAll Users
    users_t* ret_users;
    long ret_nusers;
    //RET-ListAll Tables
    table_metadata_t* ret_tables;
    long ret_ntables;
    //RET-Datatable
    data_table_t* ret_datarows;
    long ret_ndatarows;
    //RET-Imagetable
    data_table_t* ret_imagerows;
    long ret_nimagerows;
    //RET-Image
    byte* ret_imagedata;
    long ret_imagesz;
} event_data_t;

#endif
