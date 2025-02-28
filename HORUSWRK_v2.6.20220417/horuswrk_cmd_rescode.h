/*
 * Copyright(C) 2020-21 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_rescode.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 29/01/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_RESCODE_H
#define __HORUSWRK_CMD_RESCODE_H                        "__HORUSWRK_CMD_RESCODE_H"

//*** Result Codes
#define DEF_RESCODE_SUCCESS                             0
#define DEF_RESCODE_FAIL_UNKNOW                         1
#define DEF_RESCODE_FAIL_COMMAND_PARSER_ERROR           2
#define DEF_RESCODE_FAIL_CANT_SELECT_ALL_ITEMS          6
#define DEF_RESCODE_FAIL_CANT_SELECT_IMAGE_ITEM         12
#define DEF_RESCODE_FAIL_CANT_EXECUTE_MODULE            16
#define DEF_RESCODE_FAIL_CANT_WRITE_BLOCK               32
#define DEF_RESCODE_FAIL_CANT_READ_BLOCK                64

//*** Result Messages
#define DEF_RESMSG_SUCCESS                              ((char*)"Success.")
#define DEF_RESMSG_FAIL_UNKNOW                          ((char*)"Unknow failure.")
#define DEF_RESMSG_FAIL_COMMAND_PARSER_ERROR            ((char*)"Command parser error.")
#define DEF_RESMSG_FAIL_CANT_SELECT_ALL_ITEMS           ((char*)"Can't select all items.")
#define DEF_RESMSG_FAIL_CANT_SELECT_IMAGE_ITEM          ((char*)"Can't select image item.")
#define DEF_RESMSG_FAIL_CANT_EXECUTE_MODULE             ((char*)"Can't execute module.")
#define DEF_RESMSG_FAIL_CANT_WRITE_BLOCK                ((char*)"Can't write block.")
#define DEF_RESMSG_FAIL_CANT_READ_BLOCK                 ((char*)"Can't read block.")

//*** Result Types
#define DEF_RESTYPE_NONE                                -1
#define DEF_RESTYPE_SESSION_VAL                         1
#define DEF_RESTYPE_USER_ARRAY                          2
#define DEF_RESTYPE_TABLEMETADATA_ARRAY                 4
#define DEF_RESTYPE_DATATABLE_ARRAY                     8
#define DEF_RESTYPE_DATATABLE_ROW                       16
#define DEF_RESTYPE_IMAGETABLE_ARRAY                    32
#define DEF_RESTYPE_IMAGETABLE_ROW                      64
#define DEF_RESTYPE_NUMBER_VAL                          128
#define DEF_RESTYPE_STRING_VAL                          256
#define DEF_RESTYPE_BYTE_ARRAY                          512

//* defaults response headers (string)
#define DEF_XML_HEADER                                  ((char*)"<?xml version='1.0' encoding='UTF-8' ?>%s")
//RESPONSE
#define DEF_XML_RESPONSE                                ((char*)"<Result><RemoteUnitOid>%ld</RemoteUnitOid><RequestNumber>%ld</RequestNumber><RequestTimestamp>%ld</RequestTimestamp><ResultCode>%ld</ResultCode><ResultMessage>%s</ResultMessage><ResultType>%ld</ResultType><ResultNumberValue>%ld</ResultNumberValue><ResultStringValue>%s</ResultStringValue><ResultData>%s</ResultData><ResultDataSize>%ld</ResultDataSize></Result>")
//RESPONSE: SEQUENCE
#define DEF_XML_RESPONSE_SEQUENCES                      ((char*)"<Sequences>%s</Sequences>")
#define DEF_XML_RESPONSE_SEQUENCE                       ((char*)"<Sequence><Oid>%ld</Oid><KeyHash>%ld</KeyHash><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><InitialValue>%ld</InitialValue><MaxValue>%ld</MaxValue><CurrentValue>%ld</CurrentValue><SequenceName><![CDATA[%s]]</SequenceName><Key><![CDATA[%s]]</Key>")
#define DEF_XML_RESPONSE_ADD_SEQUENCE                   ((char*)"<AddUser><Oid>%ld</Oid></AddUser>")
#define DEF_XML_RESPONSE_REMOVE_SEQUENCE                ((char*)"<RemoveUser><Oid>%ld</Oid></RemoveUser>")
//RESPONSE: TABLESPACE
#define DEF_XML_RESPONSE_TABLESPACES                    ((char*)"<TableSpaces>%s</TableSpaces>")
#define DEF_XML_RESPONSE_TABLESPACE                     ((char*)"<TableSpace><Oid>%ld</Oid><KeyHash>%ld</KeyHash><CreateUid>%ld</CreateUid><DeleteUid>%ld</DeleteUid><CreateDate>%ld</CreateDate><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><TableSpaceName><![CDATA[%s]]</TableSpaceName><TableSpacePath><![CDATA[%s]]</TableSpacePath><Key><![CDATA[%s]]</Key></TableSpace>")
#define DEF_XML_RESPONSE_ADD_TABLESPACE                 ((char*)"<AddTableSpace><Oid>%ld</Oid></AddTableSpace>")
#define DEF_XML_RESPONSE_REMOVE_TABLESPACE              ((char*)"<RemoveTableSpace><Oid>%ld</Oid></RemoveTableSpace>")
//RESPONSE: TABLEMETADATA
#define DEF_XML_RESPONSE_TABLEMETADATAS                 ((char*)"<TableMetadatas>%s</TableMetadatas>")
#define DEF_XML_RESPONSE_TABLEMETADATA                  ((char*)"<TableMetadata><Oid>%ld</Oid><KeyHash>%ld</KeyHash><TableSpaceOid>%ld</TableSpaceOid><NumEntries>%ld</NumEntries><CreateUid>%ld</CreateUid><ModifyUid>%ld</ModifyUid><DeleteUid>%ld</DeleteUid><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><DeleteDate>%ld</DeleteDate><IsModified>%ld</IsModified><IsDeleted>%ld</IsDeleted><TableType>%ld</TableType><ReferenceTableOid>%ld</ReferenceTableOid><ModuleName><![CDATA[%s]]</ModuleName><TableName><![CDATA[%s]]</TableName><TableFileName><![CDATA[%s]]</TableFileName><Idx1Name><![CDATA[%s]]</Idx1Name><Idx1FileName><![CDATA[%s]]</Idx1FileName><Idx2Name><![CDATA[%s]]</Idx2Name><Idx2FileName><![CDATA[%s]]</Idx2FileName><SeqName><![CDATA[%s]]</SeqName><Key><![CDATA[%s]]</Key></TableMetadata>")
#define DEF_XML_RESPONSE_ADD_TABLEMETADATA              ((char*)"<AddTableMetadata><Oid>%ld</Oid></AddTableMetadata>")
#define DEF_XML_RESPONSE_REMOVE_TABLEMETADATA           ((char*)"<RemoveTableMetadata><Oid>%ld</Oid></RemoveTableMetadata>")
//RESPONSE: DATA_ITEM
#define DEF_XML_RESPONSE_ITEMS                          ((char*)"<Items>%s</Items>")
#define DEF_XML_RESPONSE_ITEM                           ((char*)"<Item><Oid>%ld</Oid><KeyHash>%ld</KeyHash><ImageOid>%ld</ImageOid><CreateDate>%ld</CreateDate><ModifyDate>%ld</ModifyDate><IsModified>%ld</IsModified><UpdateDate>%ld</UpdateDate><IsUpdated>%ld</IsUpdated><DeleteDate>%ld</DeleteDate><IsDeleted>%ld</IsDeleted><IsTrainData>%ld</IsTrainData><TrainScore>%lf</TrainScore><IsTestData>%ld</IsTestData><TestScore>%lf</TestScore><IsClassifiedData>%ld</IsClassifiedData><ClassificationScore>%lf</ClassificationScore><XMin>%ld</XMin><YMin>%ld</YMin><XMax>%ld</XMax><YMax>%ld</YMax><Key><![CDATA[%s]]</Key></Item>")
#define DEF_XML_RESPONSE_ADD_ITEM                       ((char*)"<AddItem><Oid>%ld</Oid></AddItem>")
#define DEF_XML_RESPONSE_REMOVE_ITEM                    ((char*)"<RemoveItem><Oid>%ld</Oid></RemoveItem>")
//RESPONSE: IMAGE_ITEM
#define DEF_XML_RESPONSE_IMAGE_ITEMS                    ((char*)"<ImageItems>%s</ImageItems>")
#define DEF_XML_RESPONSE_IMAGE_ITEM                     ((char*)"<ImageItem><Oid>%ld</Oid><KeyHash>%ld</KeyHash><ImageType>%ld</ImageType><ImageSize>%ld</ImageSize><HasBackground>%ld</HasBackground><BackgroundType>%ld</BackgroundType><BackgroundSize>%ld</BackgroundSize><CreateDate>%ld</CreateDate><CreateUid>%ld</CreateUid><ModifyDate>%ld</ModifyDate><ModifyUid>%ld</ModifyUid><IsModified>%ld</IsModified><DeleteDate>%ld</DeleteDate><DeleteUid>%ld</DeleteUid><IsDeleted>%ld</IsDeleted><XPixels>%ld</XPixels><YPixels>%ld</YPixels><XOrigin>%lf</XOrigin><YOrigin>%lf</YOrigin><XPixelSz>%lf</XPixelSz><YPixelSz>%lf</YPixelSz><XMin>%lf</XMin><YMin>%lf</YMin><XMax>%lf</XMax><YMax>%lf</YMax><XCenter>%lf</XCenter><YCenter>%lf</YCenter><SRS><![CDATA[%s]]</SRS><ImageName><![CDATA[%s]]</ImageName><ImageFilename><![CDATA[%s]]</ImageFilename><ImageFileExt><![CDATA[%s]]</ImageFileExt><ImageDiscName><![CDATA[%s]]</ImageDiscName><ImageDiscExt><![CDATA[%s]]</ImageDiscExt><BackgroundFileName><![CDATA[%s]]</BackgroundFileName><BackgroundFileExt><![CDATA[%s]]</BackgroundFileExt><BackgroundDiscName><![CDATA[%s]]</BackgroundDiscName><BackgroundDiscExt><![CDATA[%s]]</BackgroundDiscExt><Key><![CDATA[%s]]</Key></ImageItem>")
#define DEF_XML_RESPONSE_ADD_IMAGE_ITEM                 ((char*)"<AddImageItem><Oid>%ld</Oid></AddImageItem>")
#define DEF_XML_RESPONSE_REMOVE_IMAGE_ITEM              ((char*)"<RemoveImageItem><Oid>%ld</Oid></RemoveImageItem>")
//RESPONSE: ACTION RESULT
#define DEF_XML_RESPONSE_ACTION                         ((char*)"<Action>%s</Action><ActionNumber>%ld</ActionNumber><NumberOfWorkThreads>%ld</NumberOfWorkThreads><StartTime>%ld</StartTime><EndTime>%ld</EndTime><TotalDataRowsSelected>%ld</TotalDataRowsSelected><TotalDataRowsSelectTime>%ld</TotalDataRowsSelectTime><TotalImagesProcessed>%ld</TotalImagesProcessed><TotalImagesProcessSize>%ld</TotalImagesProcessSize><TotalImagesProcessTime>%ld</TotalImagesProcessTime><ResultsPerThread>%s</ResultsPerThread>")
//RESPONSE: ACTION RESULT PER THREAD
#define DEF_XML_RESPONSE_ACTION_PER_THREAD              ((char*)"<ThreadNumber>%ld</ThreadNumber><StartTime>%ld</StartTime><EndTime>%ld</EndTime><DataRowsSelected>%ld</DataRowsSelected><DataRowsSelectTime>%ld</DataRowsSelectTime><ImagesProcessed>%ld</ImagesProcessed><ImagesProcessSize>%ld</ImagesProcessSize><ImagesProcessTime>%ld</ImagesProcessTime>")

//* definition of result structures

typedef struct resp_action_struct {
    str_t action;
    long acttion_namber;
    long num_threads;
    long start_time;
    long end_time;
    long num_data_selected;
    long data_select_time;
    long num_image_processed;
    long image_process_size;
    long image_process_time;
} resp_action_t;

typedef struct resp_action_per_thread_struct {
    long thread_id;
    long start_time;
    long end_time;
    long num_data_selected;
    long data_select_time;
    long num_image_processed;
    long image_process_size;
    long image_process_time;
} resp_action_per_thread_t;

#endif
