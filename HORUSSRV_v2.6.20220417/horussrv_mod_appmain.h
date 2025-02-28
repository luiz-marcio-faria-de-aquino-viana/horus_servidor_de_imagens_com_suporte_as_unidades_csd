/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_appmain.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_APPMAIN_H
#define __HORUSSRV_MOD_APPMAIN_H     "__HORUSSRV_MOD_APPMAIN_H"

class CAppMain
{
private:
    CCfgContext* m_context;

    CCfgConfig* m_config;

    CSequence* m_sequence;

    CUsers* m_users;

    CTableSpace* m_tablespace;

    CTableMetadata* m_table_metadata;
    
    void initConfig(char* cfgfile);
    void terminateConfig();

    void initSequences(int bDoRebuild);
    void initUsers(int bDoRebuild);
    void initTablespace(int bDoRebuild);
    void initTableMetadata();

    void terminateSequences();
    void terminateUsers();
    void terminateTablespace();
    void terminateTableMetadata();

public:
    CAppMain();
    ~CAppMain();

    void init(int bDoRebuild, char* cfgfile);
    void terminate();

    void test();

    void localExec();

    void remoteExec();

    /* Getters/Setters */
    
    CCfgContext* getContextPtr();
    CCfgConfig* getConfigPtr();

    CSequence* getSequencePtr();
    CUsers* getUsersPtr();
    CTableSpace* getTableSpacePtr();
    CTableMetadata* getTableMetadataPtr();

};

/* NEW_TYPE: CAppMain Pointer */

typedef CAppMain* CAppMainPtr_t;

/* App Main Thread */

extern CAppMain gAppMain;

#endif
