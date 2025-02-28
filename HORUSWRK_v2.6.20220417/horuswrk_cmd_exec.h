/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_exec.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_EXEC_H
#define __HORUSWRK_CMD_EXEC_H                       "__HORUSWRK_CMD_EXEC_H"

class CCmdExec
{
private:
    CCmdRequest* m_pRequest;
    CCmdResponse* m_pResponse;

    /* dataset query definition
    */
    double* m_ts1_scorels;
    long m_ts1_scoresz;

    double* m_ts2_scorels;
    long m_ts2_scoresz;

    double* m_ts3_scorels;
    long m_ts3_scoresz;

    double* m_ts4_scorels;
    long m_ts4_scoresz;

    double* m_ts5_scorels;
    long m_ts5_scoresz;

    double* m_ts6_scorels;
    long m_ts6_scoresz;

public:
    CCmdExec(CCmdRequest* pRequest, CCmdResponse* pResponse);
    ~CCmdExec();

    /* Methodes */

    int doExec();

    int doExecTest(long curr_part, long num_parts);

    /* COMMANDS
    */
    int doCmdActionReqWriteBlock(dsk_block_rwreq_t* reqBlockData, dsk_block_rwresp_t* respBlockData);
    int doCmdActionReqReadBlock(dsk_block_rwreq_t* reqBlockData, dsk_block_rwresp_t* respBlockData);
    //DIRECTORY_COMMANDS
    int doCmdActionMakeDir(long uid, long path_parent, char* path_name, long* path_oid);
    int doCmdActionRemoveDir(long uid, long path_oid);
    int doCmdActionRemoveDir(long uid, long path_parent, char* path_name);
    int doCmdActionListDir(dsk_path_t** data, long* datasz, long path_oid);
    int doCmdActionListDir(dsk_path_t** data, long* datasz, long path_parent, char* path_name);
    //FILE_COMMANDS
    int doCmdActionUploadFile(long uid, long path_parent, char* path_name, byte* data, long datasz, long* path_oid);
    int doCmdActionDownloadFile(long uid, long path_oid, byte** data, long* datasz);
    int doCmdActionDownloadFile(long uid, long path_parent, char* path_name, byte** data, long* datasz);
    int doCmdActionDeleteFile(long uid, long path_oid);
    int doCmdActionMoveFile(long uid, long spath_oid, long dpath_oid);
    int doCmdActionCopyFile(long uid, long spath_oid, long dpath_oid);

    //MKDIR
    int doCmdActionTSnMkDir(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //UPLOAD
    int doCmdActionTSnUpload(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //DOWNLOAD
    int doCmdActionTSnDownload(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //DOWNLOAD_AND_PROCESS
    int doCmdActionTSnDownloadAndProcess(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //CONVERT_MOD
    int doCmdActionTSnConvert(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //REPROJ_MOD
    int doCmdActionTSnReproj(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);
    //SIMPL_MOD
    int doCmdActionTSnSimpl(char* title, double* score_ls, long scoresz, long curr_part, long num_parts);

    /* Getters/Setters */

    CCmdRequest* getRequestPtr();

    CCmdResponse* getResponsePtr();

};

/* NEW_TYPE: CCmdExec Pointer */

typedef CCmdExec* CCmdExecPtr_t;

#endif
