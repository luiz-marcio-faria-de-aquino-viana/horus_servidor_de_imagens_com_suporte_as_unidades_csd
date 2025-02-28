/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_DEFS_H
#define __HORUSSRV_MOD_DEFS_H                   "__HORUSSRV_MOD_DEFS_H"

// SIZE OF DATABASE ENTRIES
//
#define MAX_ENTRIES_USERS                       32

#define MAX_ENTRIES_TABLESPACE                  32

#define MAX_ENTRIES_TABLE_METADATA              1024

#define MAX_ENTRIES_SEQUENCES                   (32+1+1+1)  // 32=TABLESPACES + 1=METADATA TABLE + 1 USERS + 1=SEQUENCIE TABLE = 35

#define MAX_TBLSPC_COPIES                       8

#define UTYPE_SYSTEM                            ((long)0L)
#define UTYPE_ADMIN                             ((long)1L)
#define UTYPE_USER                              ((long)99L)

// DEFAULT RESPONSE HEADERS (STRING)
//
#define DEF_XML_HEADER                          ((char*)"<?xml version='1.0' encoding='UTF-8' ?>%s")
//RESPONSE
#define DEF_XML_RESPONSE                        ((char*)"<Result><RequestNumber>%ld</RequestNumber><RequestTimestamp>%ld</RequestTimestamp><ResultCode>%ld</ResultCode><ResultMessage>%s</ResultMessage><ResultType>%ld</ResultType><ResultNumberValue>%ld</ResultNumberValue><ResultStringValue>%s</ResultStringValue><ResultData>%s</ResultData><ResultDataSize>%ld</ResultDataSize></Result>")
//SEQUENCE
#define DEF_XML_RESPONSE_SEQUENCES              ((char*)"<Sequences>%s</Sequences>")
#define DEF_XML_RESPONSE_SEQUENCE               ((char*)"<Sequence><Oid>%ld</Oid><KeyHash>%ld</KeyHash><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><InitialValue>%ld</InitialValue><MaxValue>%ld</MaxValue><CurrentValue>%ld</CurrentValue><SequenceName><![CDATA[%s]]</SequenceName><Key><![CDATA[%s]]</Key>")
#define DEF_XML_RESPONSE_ADD_SEQUENCE           ((char*)"<AddUser><Oid>%ld</Oid></AddUser>")
#define DEF_XML_RESPONSE_REMOVE_SEQUENCE        ((char*)"<RemoveUser><Oid>%ld</Oid></RemoveUser>")
//USERS
#define DEF_XML_RESPONSE_USERS                  ((char*)"<Users>%s</Users>")
#define DEF_XML_RESPONSE_USER                   ((char*)"<User><Oid>%ld</Oid><KeyHash>%ld</KeyHash><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><UserType>%ld</UserType><Username><![CDATA[%s]]</Username><Passwd><![CDATA[%s]]</Passwd><Key><![CDATA[%s]]</Key></User>")
#define DEF_XML_RESPONSE_ADD_USER               ((char*)"<AddUser><Oid>%ld</Oid></AddUser>")
#define DEF_XML_RESPONSE_REMOVE_USER            ((char*)"<RemoveUser><Oid>%ld</Oid></RemoveUser>")
//TABLESPACE
#define DEF_XML_RESPONSE_TABLESPACES            ((char*)"<TableSpaces>%s</TableSpaces>")
#define DEF_XML_RESPONSE_TABLESPACE             ((char*)"<TableSpace><Oid>%ld</Oid><KeyHash>%ld</KeyHash><CreateUid>%ld</CreateUid><DeleteUid>%ld</DeleteUid><CreateDate>%ld</CreateDate><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><TableSpaceName><![CDATA[%s]]</TableSpaceName><TableSpacePath><![CDATA[%s]]</TableSpacePath><Key><![CDATA[%s]]</Key></TableSpace>")
#define DEF_XML_RESPONSE_ADD_TABLESPACE         ((char*)"<AddTableSpace><Oid>%ld</Oid></AddTableSpace>")
#define DEF_XML_RESPONSE_REMOVE_TABLESPACE      ((char*)"<RemoveTableSpace><Oid>%ld</Oid></RemoveTableSpace>")
//TABLEMETADATA
#define DEF_XML_RESPONSE_TABLEMETADATAS         ((char*)"<TableMetadatas>%s</TableMetadatas>")
#define DEF_XML_RESPONSE_TABLEMETADATA          ((char*)"<TableMetadata><Oid>%ld</Oid><KeyHash>%ld</KeyHash><TableSpaceOid>%ld</TableSpaceOid><NumTableSpaces>%ld</NumTableSpaces><NumEntries>%ld</NumEntries><CreateUid>%ld</CreateUid><ModifyUid>%ld</ModifyUid><DeleteUid>%ld</DeleteUid><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><DeleteDate>%ld</DeleteDate><IsModified>%ld</IsModified><IsDeleted>%ld</IsDeleted><TableType>%ld</TableType><ReferenceTableOid>%ld</ReferenceTableOid><ModuleName><![CDATA[%s]]</ModuleName><TableName><![CDATA[%s]]</TableName><TableFileName><![CDATA[%s]]</TableFileName><Idx1Name><![CDATA[%s]]</Idx1Name><Idx1FileName><![CDATA[%s]]</Idx1FileName><Idx2Name><![CDATA[%s]]</Idx2Name><Idx2FileName><![CDATA[%s]]</Idx2FileName><SeqName><![CDATA[%s]]</SeqName><Key><![CDATA[%s]]</Key></TableMetadata>")
#define DEF_XML_RESPONSE_ADD_TABLEMETADATA      ((char*)"<AddTableMetadata><Oid>%ld</Oid></AddTableMetadata>")
#define DEF_XML_RESPONSE_REMOVE_TABLEMETADATA   ((char*)"<RemoveTableMetadata><Oid>%ld</Oid></RemoveTableMetadata>")

// SYSTEM SEQUENCES
//
//USERS
#define SEQ_USERS_OID                           ((long)101L)
#define SEQ_USERS                               "SEQ_USERS"
//SEQUENCE
#define SEQ_SEQUENCE_OID                        ((long)102L)
#define SEQ_SEQUENCE                            "SEQ_SEQUENCE"
//TABLESPACE
#define SEQ_TABLESPACE_OID                      ((long)103L)
#define SEQ_TABLESPACE                          "SEQ_TABLESPACE"
//TABLE_METADATA
#define SEQ_TABLE_METADATA_OID                  ((long)104L)
#define SEQ_TABLE_METADATA                      "SEQ_TABLE_METADATA"

// SYSTEM SEQUENCES INITIAL VALUES
//
#define SEQ_INIT_VAL                            ((long)5001)
#define SEQ_MAX_VAL                             ((long)1000001)
#define SEQ_CURR_VAL                            ((long)5001)

// DEFAULT SYSTEM USERS
//
//SYSTEM USER
#define USR_SYSTEM_UID                          ((long)1L)
#define USR_SYSTEM_UTYPE                        UTYPE_SYSTEM             
#define USR_SYSTEM_USERNAME                     "SYSTEM"
#define USR_SYSTEM_PASSWD                       "SYSTEM"

// DEFAULT SYSTEM TABLESPACE
//
//USERS TABLESPACE
#define TBLSPC_USERS_OID                        ((long)201L)
#define TBLSPC_USERS_NAME                       "USERS"
#define TBLSPC_USERS_PATH                       "USERS_DAT/"
#define TBLSPC_USERS_UID                        ((long)1L)
//TEMP TABLESPACE
#define TBLSPC_TEMP_OID                         ((long)202L)
#define TBLSPC_TEMP_NAME                        "TEMP"
#define TBLSPC_TEMP_PATH                        "TEMP_DAT/"
#define TBLSPC_TEMP_UID                         ((long)1L)
//U11 TABLESPACE
#define TBLSPC_U211_OID                         ((long)211L)
#define TBLSPC_U211_NAME                        "U211"
#define TBLSPC_U211_PATH                        "U211_DAT/"
#define TBLSPC_U211_UID                         ((long)1L)
//U101 TABLESPACE
#define TBLSPC_U212_OID                         ((long)212L)
#define TBLSPC_U212_NAME                        "U212"
#define TBLSPC_U212_PATH                        "U212_DAT/"
#define TBLSPC_U212_UID                         ((long)1L)
//U102 TABLESPACE
#define TBLSPC_U213_OID                         ((long)213L)
#define TBLSPC_U213_NAME                        "U213"
#define TBLSPC_U213_PATH                        "U213_DAT/"
#define TBLSPC_U213_UID                         ((long)1L)
//U103 TABLESPACE
#define TBLSPC_U214_OID                         ((long)214L)
#define TBLSPC_U214_NAME                        "U214"
#define TBLSPC_U214_PATH                        "U214_DAT/"
#define TBLSPC_U214_UID                         ((long)1L)
//U104 TABLESPACE
#define TBLSPC_U215_OID                         ((long)215L)
#define TBLSPC_U215_NAME                        "U215"
#define TBLSPC_U215_PATH                        "U215_DAT/"
#define TBLSPC_U215_UID                         ((long)1L)

/* MAIN DATA FILES
 */
#define DFILE_USERS                             "tbl_users.dat"
#define DFILE_SEQUENCE                          "tbl_sequence.dat"
#define DFILE_TABLESPACE                        "tbl_tablespace.dat"
#define DFILE_TABLE_METADATA                    "tbl_table_metadata.dat"

/* TABLE TYPES
 */
#define TBTYPE_NDEF                             ((long)0L)
#define TBTYPE_DATATABLE                        ((long)1L)
#define TBTYPE_IMAGETABLE                       ((long)2L)

// USER TABLE
//
typedef struct users_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long create_date;                           // 4B
    long modify_date;                           // 4B
    long delete_date;                           // 4B
    long is_deleted;                            // 4B
    long user_type;                             // 4B
    str_t username;                             // 32B
    str_t passwd;                               // 32B
    str_t key;                                  // 32B
} users_t;                                      // TOTAL = 124B

// SEQUENCE STRUCTURES
//
typedef struct sequence_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long create_date;                           // 4B
    long modify_date;                           // 4B
    long delete_date;                           // 4B
    long is_deleted;                            // 4B
    long initial_value;                         // 4B
    long max_value;                             // 4B
    long current_value;                         // 4B
    str_t sequence_name;                        // 32B
    str_t key;                                  // 32B
} sequence_t;                                   // TOTAL = 100B

// TABLESPACE STRUCTURES
//
typedef struct tablespace_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long create_uid;                            // 4B
    long delete_uid;                            // 4B
    long create_date;                           // 4B
    long delete_date;                           // 4B
    long is_deleted;                            // 4B
    str_t tablespace_name;                      // 32B
    str_t tablespace_path;                      // 32B
    str_t key;                                  // 32B
} tablespace_t;                                 // TOTAL = 124B

// TABLE STRUCTURES
//
// TABLE METADATA
typedef struct table_metadata_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long tablespace_oid[MAX_TBLSPC_COPIES];     // 4B x MAX_TABLESPACE_COPIES (8) = 32B
    long num_tablespaces;                       // 4B
    long num_entries;                           // 4B
    long create_uid;                            // 4B
    long modify_uid;                            // 4B
    long delete_uid;                            // 4B
    long create_date;                           // 4B
    long modify_date;                           // 4B
    long delete_date;                           // 4B
    long is_modified;                           // 4B
    long is_deleted;                            // 4B
    long table_type;                            // 4B
    long reference_table_oid;                   // 4B
    str_t module_name;                          // 32B
    str_t table_name;                           // 32B
    str_t table_filename;                       // 32B
    str_t idx1_name;                            // 32B
    str_t idx1_filename;                        // 32B
    str_t idx2_name;                            // 32B
    str_t idx2_filename;                        // 32B
    str_t seq_name;                             // 32B
    str_t key;                                  // 32B
} table_metadata_t;                             // TOTAL = 376B

// TABLE DATA
typedef struct data_table_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long image_oid;                             // 4B
    long create_date;                           // 4B
    long modify_date;                           // 4B
    long is_modified;                           // 4B
    long update_date;                           // 4B
    long is_updated;                            // 4B
    long delete_date;                           // 4B
    long is_deleted;                            // 4B
    long is_train_data;                         // 4B
    double train_score;                         // 4B
    long is_test_data;                          // 4B
    double test_score;                          // 4B
    long is_classified_data;                    // 4B
    double classification_score;                // 4B
    long xmin;                                  // 4B
    long ymin;                                  // 4B
    long xmax;                                  // 4B
    long ymax;                                  // 4B
    str_t key;                                  // 32B
} data_table_t;                                 // TOTAL = 112B

/* FILETABLE STRUCTURES
 */
// IMAGE TABLE DATA
typedef struct image_table_struct {
    long oid;                                   // 4B
    long key_hash;                              // 4B
    long image_type;                            // 4B
    long image_size;                            // 4B
    long has_background;                        // 4B
    long background_type;                       // 4B
    long background_size;                       // 4B
    long create_date;                           // 4B
    long create_uid;                            // 4B
    long modify_date;                           // 4B
    long modify_uid;                            // 4B
    long is_modified;                           // 4B
    long delete_date;                           // 4B
    long delete_uid;                            // 4B
    long is_deleted;                            // 4B
    str_t image_name;                           // 32B
    str_t image_filename;                       // 32B
    str_t image_fileext;                        // 32B
    str_t image_discname;                       // 32B
    str_t image_discext;                        // 32B
    str_t background_filename;                  // 32B
    str_t background_fileext;                   // 32B
    str_t background_discname;                  // 32B
    str_t background_discext;                   // 32B
    str_t key;                                  // 32B
} image_table_t;                                // TOTAL = 380B

/* INDEX STRUCTURES
 */
typedef struct index_struct {
    long oid;                                   // 4B
    long table_oid;                             // 4B
    long data_table_oid;                        // 4B
    long image_table_oid;                       // 4B
    long create_date;                           // 4B
    long delete_date;                           // 4B
    long is_deleted;                            // 4B
    long key_hash;                              // 4B
    str_t key;                                  // 32B
} index_t;                                      // TOTAL = 64B

#endif
