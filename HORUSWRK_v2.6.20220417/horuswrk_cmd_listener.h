/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_listener.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 31/01/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_LISTENER_H
#define __HORUSWRK_CMD_LISTENER_H                           "__HORUSWRK_CMD_LISTENER_H"

class CCmdListener
{
private:
    pthread_t m_threadHnd;
    int m_isRunning;

    str_t m_ipAddr;
    long m_inPort;
    long m_outPort;

    connection_t m_arrClientCon[DEF_MAX_NUM_CONNECTION];
    int m_currNumClientCon;

public:
    CCmdListener();
    ~CCmdListener();

    void start();
    void stop();

    void test();

    /* Methodes */

    int sendStringMessageToHost(char* data);

    int sendDataMessageToHost(byte* data, int n);

    int sendStringMessageToCurrRemoteUnit(char* data);

    int sendDataMessageToCurrRemoteUnit(byte* data, int n);

    int sendStringMessageToRemoteUnit(long remoteUnitOid, char* data);

    int sendDataMessageToRemoteUnit(long remoteUnitOid, byte* data, int n);

    int sendStringMessageToAny(char* dst_addr, int dst_port, char* data);

    int sendDataMessageToAny(char* dst_addr, int dst_port, byte* data, int n);

    // AUXILIARY_METHODS: sendStringMessageToCon() / sendDataMessageToCon()

    int sendStringMessageToCon(connection_t* pCon, char* data);

    int sendDataMessageToCon(connection_t* pCon, byte* data, int n);

    // MAIN_METHOD: sendDataMessageToINET()

    int sendDataMessageToINET(struct sockaddr_in* p_saddr, long saddrsz, byte* data, int n);

    /* Getters/Setters */

    connection_t* getAvailableConnection();
    void resetConnection(connection_t* pCon);
    void resetAllConnections();

    int isRunning();

    void setRunning(int bRunning);

    char* getIpAddr();

    void setIpAddr(char* ipAddr);

    long getInPort();

    void setInPort(long inPort);

    long getOutPort();

    void setOutPort(long outPort);

};

/* NEW_TYPE: CCmdListener Pointer */

typedef CCmdListener* CCmdListenerPtr_t;

/* Command Listener Threads */

extern CCmdListener gCmdListener;

extern void* cmd_listener_exec(void* _pArgs);

extern void* cmd_listener_run(void* _pArgs);

#endif
