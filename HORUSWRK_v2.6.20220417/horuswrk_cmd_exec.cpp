/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_exec.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCmdExec::CCmdExec(CCmdRequest* pRequest, CCmdResponse* pResponse)
{
    m_pRequest = pRequest;
    m_pResponse = pResponse;

    /* dataset query definition
    */
    m_ts1_scoresz = 1;
    m_ts1_scorels = new double[m_ts1_scoresz];
    m_ts1_scorels[0] = DEF_VALSCORE_45;

    m_ts2_scoresz = 1;
    m_ts2_scorels = new double[m_ts2_scoresz];
    m_ts2_scorels[0] = DEF_VALSCORE_05;

    m_ts3_scoresz = 2;
    m_ts3_scorels = new double[m_ts3_scoresz];
    m_ts3_scorels[0] = DEF_VALSCORE_05;
    m_ts3_scorels[1] = DEF_VALSCORE_95;

    m_ts4_scoresz = 1;
    m_ts4_scorels = new double[m_ts4_scoresz];
    m_ts4_scorels[0] = DEF_VALSCORE_50;

    m_ts5_scoresz = 2;
    m_ts5_scorels = new double[m_ts5_scoresz];
    m_ts5_scorels[0] = DEF_VALSCORE_05;
    m_ts5_scorels[1] = DEF_VALSCORE_50;

    m_ts6_scoresz = 7;
    m_ts6_scorels = new double[m_ts6_scoresz]; 
    m_ts6_scorels[0] = DEF_VALSCORE_05; 
    m_ts6_scorels[1] = DEF_VALSCORE_25; 
    m_ts6_scorels[2] = DEF_VALSCORE_45; 
    m_ts6_scorels[3] = DEF_VALSCORE_50;
    m_ts6_scorels[4] = DEF_VALSCORE_55; 
    m_ts6_scorels[5] = DEF_VALSCORE_75; 
    m_ts6_scorels[6] = DEF_VALSCORE_95;

}

CCmdExec::~CCmdExec()
{
    /* nothing todo! */
}

/* COMMANDS
*/

int CCmdExec::doCmdActionReqWriteBlock(dsk_block_rwreq_t* reqBlockData, dsk_block_rwresp_t* respBlockData)
{
    return RSERR;
}

int CCmdExec::doCmdActionReqReadBlock(dsk_block_rwreq_t* reqBlockData, dsk_block_rwresp_t* respBlockData)
{
    return RSERR;
}

//DIRECTORY_COMMANDS
int CCmdExec::doCmdActionMakeDir(long uid, long path_parent, char* path_name, long* path_oid)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doMakeDir(uid, path_parent, path_name, path_oid);
    return rscode;
}

int CCmdExec::doCmdActionRemoveDir(long uid, long path_oid)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doRemoveDir(uid, path_oid);
    return rscode;
}

int CCmdExec::doCmdActionRemoveDir(long uid, long path_parent, char* path_name)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doRemoveDir(uid, path_parent, path_name);
    return rscode;
}

int CCmdExec::doCmdActionListDir(dsk_path_t** data, long* datasz, long path_oid)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doListDir(data, datasz, path_oid, DBFALSE);
    return rscode;
}

int CCmdExec::doCmdActionListDir(dsk_path_t** data, long* datasz, long path_parent, char* path_name)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doListDir(data, datasz, path_parent, path_name, DBFALSE);
    return rscode;
}

//FILE_COMMANDS
int CCmdExec::doCmdActionUploadFile(long uid, long path_parent, char* path_name, byte* data, long datasz, long* path_oid)
{
    return RSERR;
}

int CCmdExec::doCmdActionDownloadFile(long uid, long path_oid, byte** data, long* datasz)
{
    return RSERR;
}

int CCmdExec::doCmdActionDownloadFile(long uid, long path_parent, char* path_name, byte** data, long* datasz)
{
    return RSERR;
}

int CCmdExec::doCmdActionDeleteFile(long uid, long path_oid)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    int rscode = pDiskMan->doDeleteFile(uid, path_oid);
    return rscode;
}

int CCmdExec::doCmdActionMoveFile(long uid, long spath_oid, long dpath_oid)
{
    return RSERR;
}

int CCmdExec::doCmdActionCopyFile(long uid, long spath_oid, long dpath_oid)
{
    return RSERR;
}

//MKDIR
int CCmdExec::doCmdActionTSnMkDir(char* title, double* score_ls, long scoresz, long curr_part, long num_parts)
{
    CDskDiskMan* pDiskMan = gAppMain.getDiskManPtr();

    long path_parent = DBNULL_LONG;

    //TSn_MkDir

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();
    
    pDiskMan->testDiskMan_MakeDir(& path_parent, DBFALSE);
    pDiskMan->doChDir(path_parent);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);

    return RSOK;
}

//UPLOAD
int CCmdExec::doCmdActionTSnUpload(char* title, double* score_ls, long scoresz, long curr_part, long num_parts) 
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_Upload

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_Upload(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);

    return RSOK;
}

//DOWNLOAD
int CCmdExec::doCmdActionTSnDownload(char* title, double* score_ls, long scoresz, long curr_part, long num_parts)
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_Download

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_Download(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Upload(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);

    return RSOK;
}

//DOWNLOAD_AND_PROCESS
int CCmdExec::doCmdActionTSnDownloadAndProcess(char* title, double* score_ls, long scoresz, long curr_part, long num_parts)
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_DownloadAndProcess

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_DownloadAndProcess(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_DownloadAndProcess(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_DownloadAndProcess(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_DownloadAndProcess(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_DownloadAndProcess(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);

    return RSOK;
}

//CONVERT_MOD
int CCmdExec::doCmdActionTSnConvert(char* title, double* score_ls, long scoresz, long curr_part, long num_parts) 
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_Convert

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_Convert(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Convert(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Convert(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Convert(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Convert(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);

    return RSOK;
}

//REPROJ_MOD
int CCmdExec::doCmdActionTSnReproj(char* title, double* score_ls, long scoresz, long curr_part, long num_parts) 
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_Reproj

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_Reproj(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Reproj(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Reproj(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Reproj(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Reproj(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    for(int i = 0; i < n; i++) {
        printf("Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
        tm[i].tm_title,
        tm[i].tm_subtitle,
        tm[i].tm_start,
        tm[i].tm_end,
        tm[i].tm_diff);
    }

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);
        
    return RSOK;
}

//SIMPL_MOD
int CCmdExec::doCmdActionTSnSimpl(char* title, double* score_ls, long scoresz, long curr_part, long num_parts) 
{ 
    CAppExec appExec;

    data_table_t* arr = NULL;
    long arrsz = 0;

    //TSn_Simpl

    tm_result_t tm[6];
    int n = 0;

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TBLPATSAND", STRSZ);
    tm[n].tm_start = getCurrentTimestamp();

    appExec.execTSn_TBLPATSAND(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    tm[n].tm_nrows = arrsz;
    appExec.doProcessImage_Simpl(arr, arrsz);
    freeDataArray(arr);

    tm[n].tm_end = getCurrentTimestamp();
    tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATGRASS";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATGRASS(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Simpl(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATEARTH";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATEARTH(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Simpl(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATWATTER";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATWATTER(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Simpl(arr, arrsz);
    //freeDataArray(arr);

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    //tm[n].tm_title = title;
    //tm[n].tm_subtitle = (char*)"TBLPATPARCEL";
    //tm[n].tm_start = getCurrentTimestamp();

    //appExec.execTSn_TBLPATPARCEL(&arr, &arrsz, score_ls, scoresz, curr_part, num_parts);
    //tm[n].tm_nrows = arrsz;
    //appExec.doProcessImage_Simpl(arr, arrsz);
    //freeDataArray(arr);    

    //tm[n].tm_end = getCurrentTimestamp();
    //tm[n].tm_diff = tm[n].tm_end - tm[n].tm_start;
    //n += 1;

    //

    strSetEmptyUtil(tm[n].tm_title);
    strSetEmptyUtil(tm[n].tm_subtitle);

    strNCpyUtil(tm[n].tm_title, title, STRSZ);
    strNCpyUtil(tm[n].tm_subtitle, (char*)"TOTAL", STRSZ);
    tm[n].tm_start = tm[0].tm_start;
    tm[n].tm_nrows = 0;
    for(int i = 0; i < n; i++)
        tm[n].tm_nrows += tm[i].tm_nrows;
    tm[n].tm_end = tm[n - 1].tm_end;
    tm[n].tm_diff = tm[n - 1].tm_end - tm[0].tm_start;
    n += 1;

    for(int i = 0; i < n; i++) {
        printf("Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
        tm[i].tm_title,
        tm[i].tm_subtitle,
        tm[i].tm_start,
        tm[i].tm_end,
        tm[i].tm_diff);
    }

    //Response Data
    //
    bigstr_t sout, tmpout;
    strSetEmptyUtil(sout);
    strSetEmptyUtil(tmpout);

    for(int i = 0; i < n; i++) {
        sprintf( tmpout,
                 "Title: %s; Subtitle: %s; StartTime: %ld; EndTime: %ld; Diff: %ld\n",
                 tm[i].tm_title,
                 tm[i].tm_subtitle,
                 tm[i].tm_start,
                 tm[i].tm_end,
                 tm[i].tm_diff );
        strNCatUtil(sout, tmpout, BIGSTRSZ);
    }
    printf(sout);

    if(m_pResponse != NULL)
        m_pResponse->doResponseSuccess(sout);
        
    return RSOK;
}

/* Main Exec */

int CCmdExec::doExec()
{
    int rscode = RSERR;

    long action = m_pRequest->getAction();
    long currpart = m_pRequest->getCurrPart();
    long numparts = m_pRequest->getNumParts();

    dsk_block_rwreq_t reqBlockData;
    dsk_block_rwresp_t respBlockData;

    if(action == DEF_REQ_ACTION_REQWRITEBLOCK_I) {
        printf("EXEC: doCmdActionReqWriteBlock()\n");
        rscode = doCmdActionReqWriteBlock(& reqBlockData, & respBlockData);
    }
    else if(action == DEF_REQ_ACTION_REQREADBLOCK_I) {
        printf("EXEC: doCmdActionReqReadBlock()\n");
        rscode = doCmdActionReqReadBlock(& reqBlockData, & respBlockData);
    }
    //CONVERT_MOD
    else if(action == DEF_REQ_ACTION_TS1_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-1C", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-2C", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-3C", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-4C", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-5C", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_CONVERT_I) {
        printf("EXEC: doCmdActionTSnConvert()\n");
        rscode = doCmdActionTSnConvert((char*)"TS-6C", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //REPROJ_MOD
    else if(action == DEF_REQ_ACTION_TS1_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-1R", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-2R", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-3R", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-4R", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-5R", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_REPROJ_I) {
        printf("EXEC: doCmdActionTSnReproj()\n");
        rscode = doCmdActionTSnReproj((char*)"TS-6R", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //SIMPL_MOD
    else if(action == DEF_REQ_ACTION_TS1_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-1S", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-2S", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-3S", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-4S", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-5S", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_SIMPL_I) {
        printf("EXEC: doCmdActionTSnSimpl()\n");
        rscode = doCmdActionTSnSimpl((char*)"TS-6S", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //UPLOAD
    else if(action == DEF_REQ_ACTION_TS1_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-1U", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-2U", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-3U", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-4U", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-5U", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_UPLOAD_I) {
        printf("EXEC: doCmdActionTSnUpload()\n");
        rscode = doCmdActionTSnUpload((char*)"TS-6U", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //DOWNLOAD
    else if(action == DEF_REQ_ACTION_TS1_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-1D", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-2D", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-3D", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-4D", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-5D", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_DOWNLOAD_I) {
        printf("EXEC: doCmdActionTSnDownload()\n");
        rscode = doCmdActionTSnDownload((char*)"TS-6D", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //MKDIR
    else if(action == DEF_REQ_ACTION_TS1_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-1M", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-2M", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-3M", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-4M", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-5M", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_MKDIR_I) {
        printf("EXEC: doCmdActionTSnMkDir()\n");
        rscode = doCmdActionTSnMkDir((char*)"TS-6M", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }
    //DOWNLOAD_AND_PROCESS
    else if(action == DEF_REQ_ACTION_TS1_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-1DP", m_ts1_scorels, m_ts1_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS2_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-2DP", m_ts2_scorels, m_ts2_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS3_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-3DP", m_ts3_scorels, m_ts3_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS4_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-4DP", m_ts4_scorels, m_ts4_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS5_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-5DP", m_ts5_scorels, m_ts5_scoresz, currpart, numparts);
    }
    else if(action == DEF_REQ_ACTION_TS6_DOWNLOAD_AND_PROCESS_I) {
        printf("EXEC: doCmdActionTSnDownloadAndProcess()\n");
        rscode = doCmdActionTSnDownloadAndProcess((char*)"TS-6DP", m_ts6_scorels, m_ts6_scoresz, currpart, numparts);
    }

    return rscode;
}

int CCmdExec::doExecTest(long curr_part, long num_parts)
{
    //MKDIR
    doCmdActionTSnMkDir((char*)"TS-1M", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnMkDir((char*)"TS-2M", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnMkDir((char*)"TS-3M", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnMkDir((char*)"TS-4M", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnMkDir((char*)"TS-5M", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnMkDir((char*)"TS-6M", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    //UPLOAD
    doCmdActionTSnUpload((char*)"TS-1U", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnUpload((char*)"TS-2U", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnUpload((char*)"TS-3U", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnUpload((char*)"TS-4U", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnUpload((char*)"TS-5U", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnUpload((char*)"TS-6U", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    //DOWNLOAD
    doCmdActionTSnDownload((char*)"TS-1D", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnDownload((char*)"TS-2D", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnDownload((char*)"TS-3D", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnDownload((char*)"TS-4D", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnDownload((char*)"TS-5D", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnDownload((char*)"TS-6D", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    //CONVERT_MOD
    doCmdActionTSnConvert((char*)"TS-1C", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnConvert((char*)"TS-2C", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnConvert((char*)"TS-3C", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnConvert((char*)"TS-4C", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnConvert((char*)"TS-5C", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnConvert((char*)"TS-6C", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    //REPROJ_MOD
    doCmdActionTSnReproj((char*)"TS-1R", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnReproj((char*)"TS-2R", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnReproj((char*)"TS-3R", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnReproj((char*)"TS-4R", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnReproj((char*)"TS-5R", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnReproj((char*)"TS-6R", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    //SIMPL_MOD
    doCmdActionTSnSimpl((char*)"TS-1S", m_ts1_scorels, m_ts1_scoresz, curr_part, num_parts);
    //doCmdActionTSnSimpl((char*)"TS-2S", m_ts2_scorels, m_ts2_scoresz, curr_part, num_parts);
    //doCmdActionTSnSimpl((char*)"TS-3S", m_ts3_scorels, m_ts3_scoresz, curr_part, num_parts);
    //doCmdActionTSnSimpl((char*)"TS-4S", m_ts4_scorels, m_ts4_scoresz, curr_part, num_parts);
    //doCmdActionTSnSimpl((char*)"TS-5S", m_ts5_scorels, m_ts5_scoresz, curr_part, num_parts);
    //doCmdActionTSnSimpl((char*)"TS-6S", m_ts6_scorels, m_ts6_scoresz, curr_part, num_parts);

    return RSOK;
}

/* Getters/Setters */

CCmdRequest* CCmdExec::getRequestPtr()
{
    return m_pRequest;
}

CCmdResponse* CCmdExec::getResponsePtr()
{
    return m_pResponse;    
}
