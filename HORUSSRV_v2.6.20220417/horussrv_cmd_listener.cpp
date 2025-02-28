/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cmd_listener.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 02/07/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCmdListener gCmdListener;

CCmdListener::CCmdListener()
{
    m_threadHnd = 0;
    m_isRunning = FALSE;

    resetAllConnections();
}

CCmdListener::~CCmdListener()
{
    stop();
}

void CCmdListener::start()
{
    int rscode = pthread_create(&m_threadHnd, NULL, cmd_listener_run, NULL);    
    if(rscode == -1)
        errMsg(__HORUSSRV_CMD_LISTENER_H, "start()", ERR_CANTCREATELISTNERTHREAD);
    sleep(3);
}

void CCmdListener::stop()
{
    if(m_threadHnd != 0)
    {
        sendStringMessageToListener((char*)DEF_DEFAULT_SERVERTERMMSG);

        while(gCmdListener.isRunning() == TRUE)
            sleep(DEBUG_MODE_SLEEPTIME);
        m_threadHnd = 0;
        m_isRunning = FALSE;

        //void* pThreadRet = NULL; 
        //pthread_join(m_threadHnd, &pThreadRet);
    }
}

void CCmdListener::test()
{
    CCmdTest cmdTest;
    cmdTest.test();    
}

void CCmdListener::exec()
{
    CCmdTest cmdTest;
    cmdTest.benchmark();    
}

void CCmdListener::remoteExec1()
{
    CCmdTest cmdTest;
    cmdTest.remoteBenchmark1();    
}

void CCmdListener::remoteExec2()
{
    CCmdTest cmdTest;
    cmdTest.remoteBenchmark2();    
}

/* Methodes */

int CCmdListener::sendStringMessageToHost(char* data)
{
    int n = (sizeof(char) * strlen(data)) + 1;
    int rscode = sendDataMessageToHost((byte*)data, n);
    return rscode;
}

int CCmdListener::sendDataMessageToHost(byte* data, int n)
{
    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgHostServer* pHostServer = pConfig->getHostServerPtr();

    int rscode = sendDataMessageToAny(pHostServer->getIpAddr(), pHostServer->getInPort(), (byte*)data, n);
    return rscode;
}

int CCmdListener::sendStringMessageToListener(char* data)
{
    int n = (sizeof(char) * strlen(data)) + 1;
    int rscode = sendDataMessageToListener((byte*)data, n);
    return rscode;
}

int CCmdListener::sendDataMessageToListener(byte* data, int n)
{
    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgListener* pListener = pConfig->getListenerPtr();

    int rscode = sendDataMessageToAny(pListener->getIpAddr(), pListener->getInPort(), (byte*)data, n);
    return rscode;
}

int CCmdListener::sendStringMessageToRemoteUnit(long remoteUnitOid, char* data)
{
    int n = (sizeof(char) * strlen(data)) + 1;
    int rscode = sendDataMessageToRemoteUnit(remoteUnitOid, (byte*)data, n);
    return rscode;
}

int CCmdListener::sendDataMessageToRemoteUnit(long remoteUnitOid, byte* data, int n)
{
    int rscode = RSERR;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgRemoteUnit* pRemoteUnit = pConfig->getRemoteUnitPtr(remoteUnitOid);
    if(pRemoteUnit != NULL)
        rscode = sendDataMessageToAny(pRemoteUnit->getIpAddr(), pRemoteUnit->getInPort(), (byte*)data, n);
    return rscode;
}

int CCmdListener::sendStringMessageToAny(char* dst_addr, int dst_port, char* data)
{
    int n = (sizeof(char) * strlen(data)) + 1;
    int rscode = sendDataMessageToAny(dst_addr, dst_port, (byte*)data, n);
    return rscode;
}

int CCmdListener::sendDataMessageToAny(char* dst_addr, int dst_port, byte* data, int n)
{
    struct sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(dst_port);
    inet_aton(dst_addr, &saddr.sin_addr);

    bigstr_t errmsg;
    sprintf(errmsg, "\nCCmdListener::sendDataMessageToAny: DstAddr=%s, DstPort=%d", dst_addr, dst_port);
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_LISTENER_H, "sendDataMessageToAny()", errmsg);

    int rscode = sendDataMessageToINET(&saddr, sizeof(saddr), data, n);
    return rscode;
}

// AUXILIARY_METHODS: sendStringMessageToCon() / sendDataMessageToCon()

int CCmdListener::sendStringMessageToCon(connection_t* pCon, char* data)
{
    int n = (sizeof(char) * strlen(data)) + 1;
    int rscode = sendDataMessageToCon(pCon, (byte*)data, n);
    return rscode; 
}

int CCmdListener::sendDataMessageToCon(connection_t* pCon, byte* data, int n)
{
    struct sockaddr_in saddr;

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgListener* pListener = pConfig->getListenerPtr();

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(pListener->getOutPort());
    saddr.sin_addr.s_addr = pCon->caddr.sin_addr.s_addr;

    int rscode = sendDataMessageToINET(& saddr, sizeof(saddr), (byte*)data, n);
    return rscode;
}

// MAIN_METHOD: sendDataMessageToINET()

int CCmdListener::sendDataMessageToINET(struct sockaddr_in* p_saddr, long saddrsz, byte* data, int n)
{
	int clientHnd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(clientHnd == -1) {
        errMsg(__HORUSSRV_CMD_LISTENER_H, "sendDataMessageToINET()", ERR_CANTCREATESOCKET);
        return RSERR;
    }

    if (connect(clientHnd, (struct sockaddr*) p_saddr, saddrsz) == -1) {
        errMsg(__HORUSSRV_CMD_LISTENER_H, "sendDataMessageToINET()", ERR_CANTCONNECTSOCKET);
        return RSERR;
    }

    if(send(clientHnd, data, n, MSG_DONTWAIT) == -1) {
        errMsg(__HORUSSRV_CMD_LISTENER_H, "sendDataMessageToINET()", ERR_CANTSENDMESSAGE);
        return RSERR;
    }

    return RSOK;
}

/* Getters/Setters */

connection_t* CCmdListener::getAvailableConnection()
{
    for(int i = 0; i < DEF_MAX_NUM_CONNECTION; i++)
    {
        connection_t* pCon = &m_arrClientCon[i];

        if(pCon->socketHnd == -1)
            return pCon;
    }
    return NULL;
}

void CCmdListener::resetConnection(connection_t* pCon)
{
    pCon->reqnum = -1;
    pCon->socketHnd = -1;
    memSetNullUtil((byte*) &(pCon->caddr), sizeof(struct sockaddr));
    pCon->caddr_len = 0;
    pCon->threadHnd = 0;
    memSetNullUtil(pCon->in_buf, BUFSZ);
    pCon->in_len = 0;
}

void CCmdListener::resetAllConnections()
{
    for(int i = 0; i < DEF_MAX_NUM_CONNECTION; i++)
    {
        connection_t* pCon = &m_arrClientCon[i];
        resetConnection(pCon);
    }
    m_currNumClientCon = 0;
}

int CCmdListener::isRunning()
{
    return m_isRunning;
}

void CCmdListener::setRunning(int bRunning)
{
    m_isRunning = bRunning;
}

char* CCmdListener::getIpAddr()
{
    return m_ipAddr;
}

void CCmdListener::setIpAddr(char* ipAddr)
{
    strNCpyUtil(m_ipAddr, ipAddr, STRSZ);
}

long CCmdListener::getInPort()
{
    return m_inPort;
}

void CCmdListener::setInPort(long inPort)
{
    m_inPort = inPort;
}

long CCmdListener::getOutPort()
{
    return m_outPort;
}

void CCmdListener::setOutPort(long outPort)
{
    m_outPort = outPort;
}

/* Command Listener Threads */

extern void* cmd_listener_exec(void* _pArgs)
{
    connection_t* pCon = (connection_t*)_pArgs;
    str_t strTmp;

    strNCpyUtil(strTmp, (char*)pCon->in_buf, STRSZ);
    printf("\n\nStarting Command Execution: %s...\n", strTmp);

    CCmdResponse* pResp = new CCmdResponse(pCon->reqnum);
    CCmdRequest* pReq = NULL;

    sbigstr_t resultXml;        
    sbigstr_t outputXml;        
    
    printf("\n => Processing Normal Data Request...\n");
    pReq = new CCmdRequest(pCon->reqnum, (char*)pCon->in_buf);

    if(pReq->getAction() != DEF_REQ_ACTION_UNKNOW_I)
    {
        pReq->debug();

        CCmdExec execWorker(pReq, pResp);
        if(execWorker.doExec() == RSOK) {
            pResp->debug();

            pResp->toResultXml(resultXml);
            sprintf(outputXml, DEF_XML_HEADER, resultXml);
            printf("ResultXml: %s\n", outputXml);

            int rscode = gCmdListener.sendStringMessageToCon(pCon, outputXml);
            if(rscode == RSERR)
                errMsg(__HORUSSRV_CMD_LISTENER_H, "cmd_listener_exec()", ERR_CANTSENDMESSAGE);
        }
    }

    if(pResp != NULL)
        delete(pResp);
    if(pReq != NULL)
        delete(pReq);

    close(pCon->socketHnd);

    gCmdListener.resetConnection(pCon);

    printf("\nCommand Execution... Completed!\n");
    pthread_exit(NULL);
}

extern void* cmd_listener_run(void* _pArgs)
{
    struct sockaddr_in saddr;
    str_t strTmp;

    gCmdListener.setRunning(TRUE);

    CCfgConfig* pConfig = gAppMain.getConfigPtr();

    CCfgListener* pListener = pConfig->getListenerPtr();

    gCmdListener.setIpAddr(pListener->getIpAddr());
    gCmdListener.setInPort(pListener->getInPort());
    gCmdListener.setOutPort(pListener->getOutPort());

    memSetNullUtil((byte*) &saddr, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons( gCmdListener.getInPort() );
    saddr.sin_addr.s_addr = htonl( INADDR_ANY );

    bigstr_t errmsg;
    sprintf(errmsg, "\nCCmdListener::Setting Listerner at: %ld", gCmdListener.getInPort());
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", errmsg);

	int serverHnd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(serverHnd == -1) 
        errMsg(__HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", ERR_CANTCREATESOCKET);

    int sockreuse = 1;
    if(setsockopt(serverHnd, SOL_SOCKET, SO_REUSEADDR, &sockreuse, sizeof(int)) == -1)
        errMsg(__HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", ERR_CANTSETSOCKETOPT);

    if(bind(serverHnd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
        errMsg(__HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", ERR_CANTBINDSOCKET);

    printf("\n\n=> Listener started...\n");

    int nummsg = 0;
    while(gCmdListener.isRunning() == TRUE)
    {
        nummsg += 1;

        socklen_t caddr_len = sizeof(sockaddr);
        struct sockaddr caddr;
        int in_len = -1;
        buf_t in_buf;

        memSetNullUtil((byte*)&caddr, caddr_len);
        memSetNullUtil(in_buf, BUFSZ);

        in_len = recvfrom(
            serverHnd, 
            in_buf, 
            BUFSZ, 
            0, 
            (struct sockaddr *) &caddr, 
            &caddr_len);
        printf("\n\nDataRecv: %s...\n", in_buf);

        if(in_len != -1) 
        {
            connection_t* pCon = gCmdListener.getAvailableConnection();
            if(pCon != NULL)
            {
                pCon->reqnum = nummsg;
                pCon->socketHnd = -1;   // udp - not used
                pCon->caddr_len = caddr_len;
                pCon->in_len = in_len;
                memNCpyUtil((byte*)&pCon->caddr, (byte*)&caddr, pCon->caddr_len);
                memNCpyUtil((byte*)&pCon->in_buf, (byte*)&in_buf, pCon->in_len);

                strNCpyUtil(strTmp, (char*)pCon->in_buf, STRSZ);
                printf("\nMessage #%d: %s...\n", nummsg, strTmp);

                if(strNCmpUtil((char*)pCon->in_buf, (char*)DEF_DEFAULT_SERVERTERMMSG, DEF_DEFAULT_SERVERTERMMSGLEN) == 0) {
                    gCmdListener.setRunning(FALSE);
                    continue;
                }

                int rscode = pthread_create(&pCon->threadHnd, NULL, cmd_listener_exec, pCon);    
                if(rscode == -1)
                    errMsg(__HORUSSRV_CMD_LISTENER_H, "cmd_listener_run()", ERR_CANTCREATELISTNERTHREAD);
            }
        }
    }

    printf("\n\n=> Listener terminated!\n\n");
    pthread_exit(NULL);
}
