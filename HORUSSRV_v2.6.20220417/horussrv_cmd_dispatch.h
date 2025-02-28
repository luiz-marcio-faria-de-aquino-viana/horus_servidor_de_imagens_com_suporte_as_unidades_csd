/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_dispatch.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 01/03/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_CMD_DISPATCH_H
#define __HORUSSRV_CMD_DISPATCH_H                    "__HORUSSRV_CMD_DISPATCH_H"

class CCmdDispatch
{
private:
    str_t m_chname;
    int m_reqnum;

public:
    CCmdDispatch(char* chname);

    ~CCmdDispatch();

    /* Local Methodes */

    int serverConnect(char* username, char* passwd);

    int serverTerminate();

    int listAllUsers(users_t** ret_datarows, long* ret_numrows, char* sessionId);
    int listAllTables(table_metadata_t** ret_datarows, long* ret_numrows, char* sessionId);

    /* Remote Unit Methodes */

    int serverTerminate(CCfgRemoteUnit* pRemoteUnit);

    //MKDIR
    int doActionTS1MkDir(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //UPLOAD
    int doActionTS1Upload(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //DOWNLOAD
    int doActionTS1Download(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //DOWNLOAD_AND_PROCESS
    int doActionTS1DownloadAndProcess(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts, long mode);
    //CONVERT_MOD
    int doActionTS1Convert(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //REPROJ_MOD
    int doActionTS1Reproj(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);
    //SIMPL_MOD
    int doActionTS1Simpl(CCfgRemoteUnit* pRemoteUnit, long currpart, long numparts);

    /* Getters/Setters */

    char* getChName();

    int getReqNum();

};

/* NEW_TYPE: CCmdDispatch Pointer */

typedef CCmdDispatch* CCmdDispatchPtr_t;

#endif
