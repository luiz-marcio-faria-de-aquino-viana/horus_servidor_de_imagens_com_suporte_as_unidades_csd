/*
 * Copyright(C) 2020-21 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_rescode.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_RESCODE_H
#define __HORUSSRV_CMD_RESCODE_H                        "__HORUSSRV_CMD_RESCODE_H"

//*** Result Codes
#define DEF_RESCODE_SUCCESS                             0
#define DEF_RESCODE_FAIL_UNKNOW                         1
#define DEF_RESCODE_FAIL_COMMAND_PARSER_ERROR           2
#define DEF_RESCODE_FAIL_INVALID_AUTHENTICATION         3
#define DEF_RESCODE_FAIL_CANT_LIST_ALL_USERS            4
#define DEF_RESCODE_FAIL_CANT_LIST_ALL_TABLES           5
#define DEF_RESCODE_FAIL_CANT_SELECT_ALL_ITEMS          6
#define DEF_RESCODE_FAIL_CANT_SELECT_ITEM               7
#define DEF_RESCODE_FAIL_CANT_ADD_ITEM                  8
#define DEF_RESCODE_FAIL_CANT_GET_ITEM                  9
#define DEF_RESCODE_FAIL_CANT_REMOVE_ITEM               10
#define DEF_RESCODE_FAIL_CANT_SELECT_ALL_IMAGE_ITEMS    11
#define DEF_RESCODE_FAIL_CANT_SELECT_IMAGE_ITEM         12
#define DEF_RESCODE_FAIL_CANT_ADD_IMAGE_ITEM            13
#define DEF_RESCODE_FAIL_CANT_GET_IMAGE_ITEM            14
#define DEF_RESCODE_FAIL_CANT_REMOVE_IMAGE_ITEM         15

//*** Result Messages
#define DEF_RESMSG_SUCCESS                              ((char*)"Success.")
#define DEF_RESMSG_FAIL_UNKNOW                          ((char*)"Unknow failure.")
#define DEF_RESMSG_FAIL_COMMAND_PARSER_ERROR            ((char*)"Command parser error.")
#define DEF_RESMSG_FAIL_INVALID_AUTHENTICATION          ((char*)"Invalid authentication.")
#define DEF_RESMSG_FAIL_CANT_LIST_ALL_USERS             ((char*)"List all users.")
#define DEF_RESMSG_FAIL_CANT_LIST_ALL_TABLES            ((char*)"List all tables.")
#define DEF_RESMSG_FAIL_CANT_SELECT_ALL_ITEMS           ((char*)"Can't select all items.")
#define DEF_RESMSG_FAIL_CANT_SELECT_ITEM                ((char*)"Can't select item.")
#define DEF_RESMSG_FAIL_CANT_ADD_ITEM                   ((char*)"Can't add item.")
#define DEF_RESMSG_FAIL_CANT_GET_ITEM                   ((char*)"Can't get item.")
#define DEF_RESMSG_FAIL_CANT_REMOVE_ITEM                ((char*)"Can't remove item.")
#define DEF_RESMSG_FAIL_CANT_SELECT_ALL_IMAGE_ITEMS     ((char*)"Can't select all image items.")
#define DEF_RESMSG_FAIL_CANT_SELECT_IMAGE_ITEM          ((char*)"Can't select image item.")
#define DEF_RESMSG_FAIL_CANT_ADD_IMAGE_ITEM             ((char*)"Can't add image item.")
#define DEF_RESMSG_FAIL_CANT_GET_IMAGE_ITEM             ((char*)"Can't get image item.")
#define DEF_RESMSG_FAIL_CANT_REMOVE_IMAGE_ITEM          ((char*)"Can't remove image item.")

//*** Result Types
#define DEF_RESTYPE_NONE                            -1
#define DEF_RESTYPE_SESSION_VAL                     1
#define DEF_RESTYPE_USER_ARRAY                      2
#define DEF_RESTYPE_TABLEMETADATA_ARRAY             4
#define DEF_RESTYPE_DATATABLE_ARRAY                 8
#define DEF_RESTYPE_DATATABLE_ROW                   16
#define DEF_RESTYPE_IMAGETABLE_ARRAY                32
#define DEF_RESTYPE_IMAGETABLE_ROW                  64
#define DEF_RESTYPE_NUMBER_VAL                      128
#define DEF_RESTYPE_STRING_VAL                      256
#define DEF_RESTYPE_BYTE_ARRAY                      512

#endif
