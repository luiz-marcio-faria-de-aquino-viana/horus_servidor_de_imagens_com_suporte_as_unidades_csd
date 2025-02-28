/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_request.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 01/07/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_REQUEST_H
#define __HORUSWRK_CMD_REQUEST_H       "__HORUSWRK_CMD_REQUEST_H"

class CCmdRequest
{
private:
    connection_t* m_pCon;

    dsk_block_rwreq_t m_reqBlockData;
    dsk_block_rwresp_t m_respBlockData;

    byte m_dataType;

    long m_reqnum;
    long m_remoteunit_oid;
    long m_action;
    long m_currpart;
    long m_numparts;

    str_t m_actionName;

public:
    CCmdRequest(long reqnum, connection_t* pCon);

    CCmdRequest(long reqnum, char* cmd);

    ~CCmdRequest();

    /* Methodes */

    void initNewCmdRequest(long reqnum, connection_t* pCon);

    void initOldCmdRequest(long reqnum, char* cmd);

    void reset();

    void debug();

    /* Getters/Setters */

    connection_t* getConnectionPtr();

    dsk_block_rwreq_t* getReqBlockDataPtr();

    dsk_block_rwresp_t* getRespBlockDataPtr();

    byte getDataType();

    long getReqNum();

    long getRemoteUnitOid();

    long getAction();

    long getCurrPart();

    long getNumParts();

    char* getActionName();

};

/* NEW_TYPE: CCmdRequest Pointer */

typedef CCmdRequest* CCmdRequestPtr_t;

#endif
