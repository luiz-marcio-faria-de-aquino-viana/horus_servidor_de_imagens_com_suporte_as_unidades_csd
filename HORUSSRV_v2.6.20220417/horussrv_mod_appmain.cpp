/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_appmain.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CAppMain gAppMain;

CAppMain::CAppMain()
{
    //TODO:
}

CAppMain::~CAppMain()
{
    //TODO:
}

void CAppMain::initConfig(char* cfgfile)
{
    bigstr_t errmsg;
    
    sprintf(errmsg, "=> Init(): Config\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initConfig()", errmsg);

    m_context = new CCfgContext();

    m_config = new CCfgConfig(DEF_TAGQTY_REMOTEUNITS);
    m_config->loadConfig(cfgfile);
    m_config->debug(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initConfig()");

    sprintf(errmsg, "<= CConfig...OK.\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initConfig()", errmsg);
}

void CAppMain::initSequences(int bDoRebuild)
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "=> Init(): Sequences\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

    m_sequence = new CSequence(MAX_ENTRIES_SEQUENCES);
    errMsgIfNull(__HORUSSRV_MOD_APPMAIN_H, "initSequences()", ERR_CANTALLOCATEMEMORY, m_sequence);

    sprintf(errmsg, "II.1.1) CSequence...Created!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

    if(m_sequence != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_SEQUENCE, PATHNAMESZ);
        sprintf(errmsg, "II.1.2.1) CSequence...FileName=%s\n", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

        if(m_sequence->loadFile(fileName) == RSOK)
        {
            sprintf(errmsg, "II.1.2.2.1) CSequence...Data Loaded!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

            sprintf(errmsg, "II.1.2.2.2) CSequence...List ALL Data!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

            m_sequence->debug(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()");
        }
        else
        {
            sprintf(errmsg, "II.1.2.3) CSequence...Data NOT Loaded! ERROR!!!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
        }
    }

    if(bDoRebuild == DBTRUE)
    {
        m_sequence->addItem(
            SEQ_USERS_OID,
            (char*)SEQ_USERS, 
            (char*)SEQ_USERS, 
            SEQ_INIT_VAL, 
            SEQ_MAX_VAL, 
            SEQ_CURR_VAL);
        sprintf(errmsg, "II.2.1) CSequence::AddItem(%s)...OK.\n", SEQ_USERS);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
        
        m_sequence->addItem(
            SEQ_SEQUENCE_OID,
            (char*)SEQ_SEQUENCE, 
            (char*)SEQ_SEQUENCE, 
            SEQ_INIT_VAL, 
            SEQ_MAX_VAL, 
            SEQ_CURR_VAL);
        sprintf(errmsg, "II.2.2) CSequence::AddItem(%s)...OK.\n", SEQ_SEQUENCE);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);

        m_sequence->addItem(
            SEQ_TABLESPACE_OID,
            (char*)SEQ_TABLESPACE, 
            (char*)SEQ_TABLESPACE, 
            SEQ_INIT_VAL, 
            SEQ_MAX_VAL, 
            SEQ_CURR_VAL);
        sprintf(errmsg, "II.2.3) CSequence::AddItem(%s)...OK.\n", SEQ_TABLESPACE);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
        
        m_sequence->addItem(
            SEQ_TABLE_METADATA_OID,
            (char*)SEQ_TABLE_METADATA, 
            (char*)SEQ_TABLE_METADATA, 
            SEQ_INIT_VAL, 
            SEQ_MAX_VAL, 
            SEQ_CURR_VAL);
        sprintf(errmsg, "II.2.4) CSequence::AddItem(%s)...OK.\n", SEQ_TABLE_METADATA);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
    }

    sprintf(errmsg, "II.3) CSequence::List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
    
    m_sequence->debug(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()");

    sprintf(errmsg, "<= CSequence...OK.\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initSequences()", errmsg);
}

void CAppMain::initUsers(int bDoRebuild)
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "=> Init(): Users\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);

    m_users = new CUsers(MAX_ENTRIES_USERS);
    errMsgIfNull(__HORUSSRV_MOD_APPMAIN_H, "initUsers()", ERR_CANTALLOCATEMEMORY, m_users);

    sprintf(errmsg, "III.1.1) CUsers...Created!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);

    if(m_users != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_USERS, PATHNAMESZ);
        m_users->loadFile(fileName);
    }

    if(bDoRebuild == DBTRUE)
    {
        m_users->addItem(
            USR_SYSTEM_UID, 
            (char*)USR_SYSTEM_USERNAME, 
            (char*)USR_SYSTEM_USERNAME, 
            (char*)USR_SYSTEM_PASSWD, 
            USR_SYSTEM_UTYPE);
        sprintf(errmsg, "III.2.1) CUsers::AddItem(%ld, %s)...OK.\n", USR_SYSTEM_UID, USR_SYSTEM_USERNAME);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);
    }

    sprintf(errmsg, "III.3) CUsers::List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);
    
    m_users->debug(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()");

    sprintf(errmsg, "<= CUsers...OK.\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);
}

void CAppMain::initTablespace(int bDoRebuild)
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "=> Init(): Tablespace\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);

    m_tablespace = new CTableSpace(MAX_ENTRIES_TABLESPACE);
    errMsgIfNull(__HORUSSRV_MOD_APPMAIN_H, "initTablespace()", ERR_CANTALLOCATEMEMORY, m_tablespace);

    sprintf(errmsg, "IV.1.1) CTableSpace...Created!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);

    if(m_tablespace != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_TABLESPACE, PATHNAMESZ);
        m_tablespace->loadFile(fileName);
    }

    sprintf(errmsg, "III.1.2) CTableSpace...Data Loaded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);

    if(bDoRebuild == DBTRUE)
    {
        m_tablespace->addItemEx(
            TBLSPC_USERS_OID, 
            (char*)TBLSPC_USERS_NAME, 
            (char*)TBLSPC_USERS_NAME, 
            (char*)TBLSPC_USERS_PATH, 
            TBLSPC_USERS_UID);
        sprintf(errmsg, "IV.2.1) CTableSpace::AddItem(%ld, %s)...OK.\n", TBLSPC_USERS_OID, TBLSPC_USERS_NAME);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);
        
        m_tablespace->addItemEx(
            TBLSPC_TEMP_OID, 
            (char*)TBLSPC_TEMP_NAME, 
            (char*)TBLSPC_TEMP_NAME, 
            (char*)TBLSPC_TEMP_PATH, 
            TBLSPC_TEMP_UID);
        sprintf(errmsg, "IV.2.2) CTableSpace::AddItem(%ld, %s)...OK.\n", TBLSPC_TEMP_OID, TBLSPC_TEMP_NAME);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);
    }

    sprintf(errmsg, "IV.3) CTableSpace::List All Entries\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);
    
    m_tablespace->debug(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()");

    sprintf(errmsg, "<= Tablespace...OK.\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTablespace()", errmsg);
}

void CAppMain::initTableMetadata()
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "=> Init(): TableMetadata\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTableMetadata()", errmsg);

    m_table_metadata = new CTableMetadata(MAX_ENTRIES_TABLE_METADATA);
    errMsgIfNull(__HORUSSRV_MOD_APPMAIN_H, "initTableMetadata()", ERR_CANTALLOCATEMEMORY, m_table_metadata);

    sprintf(errmsg, "IV.1) CTableMetadata...Created!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTableMetadata()", errmsg);

    if(m_table_metadata != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_TABLE_METADATA, PATHNAMESZ);
        m_table_metadata->loadFile(fileName);
    }

    sprintf(errmsg, "III.1.2) CTableMetadata...Data Loaded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initUsers()", errmsg);

    sprintf(errmsg, "<= TableMetadata...OK.\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "initTableMetadata()", errmsg);
}

void CAppMain::terminateConfig()
{
    if(m_config != NULL) 
        delete m_config;

    if(m_context != NULL) 
        delete m_context;
}

void CAppMain::terminateSequences()
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "LI.1) Terminate Sequence...\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateSequence()", errmsg);

    if(m_sequence != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_SEQUENCE, PATHNAMESZ);
        sprintf(errmsg, "LI.2) CSequence...FileName=%s\n", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateSequence()", errmsg);

        if(m_sequence->saveFile(fileName) == RSOK)
        {
            sprintf(errmsg, "LI.2.1) CSequence...Data Saved!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateSequence()", errmsg);
        }
        else
        {
            sprintf(errmsg, "LI.2.2) CSequence...Data NOT Saved! ERROR!!!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateSequence()", errmsg);
        }
    }

    sprintf(errmsg, "LI.3) Terminate Sequence... Endded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateSequence()", errmsg);
}

void CAppMain::terminateUsers()
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "LII.1) Terminate Users...\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateUsers()", errmsg);

    if(m_users != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_USERS, PATHNAMESZ);
        sprintf(errmsg, "LII.2) CUsers...FileName=%s\n", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateUsers()", errmsg);

        if(m_users->saveFile(fileName) == RSOK)
        {
            sprintf(errmsg, "LII.2.1) CUsers...Data Saved!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateUsers()", errmsg);
        }
        else
        {
            sprintf(errmsg, "LII.2.2) CUsers...Data NOT Saved! ERROR!!!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateUsers()", errmsg);
        }
    }

    sprintf(errmsg, "LII.2.3) Terminate Users... Endded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateUsers()", errmsg);
}

void CAppMain::terminateTablespace()
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "LIII.1) Terminate Tablespace...\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTablespace()", errmsg);

    if(m_tablespace != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_TABLESPACE, PATHNAMESZ);
        sprintf(errmsg, "LIII.2) CTablespace...FileName=%s\n", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTablespace()", errmsg);

        if(m_tablespace->saveFile(fileName) == RSOK)
        {
            sprintf(errmsg, "LIII.2.1) CTablespace...Data Saved!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTablespace()", errmsg);
        }
        else
        {
            sprintf(errmsg, "LIII.2.2) CTablespace...Data NOT Saved! ERROR!!!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTablespace()", errmsg);
        }
    }

    sprintf(errmsg, "LIII.3) Terminate Tablespace... Endded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTablespace()", errmsg);
}

void CAppMain::terminateTableMetadata()
{
    pathname_t fileName;
    bigstr_t errmsg;

    sprintf(errmsg, "LIV.1) Terminate Table Metadata...\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTableMetadata()", errmsg);

    if(m_table_metadata != NULL)
    {
        strNCpyUtil(fileName, m_context->getDataDir(), PATHNAMESZ);
        strNCatUtil(fileName, (char*)DFILE_TABLE_METADATA, PATHNAMESZ);
        sprintf(errmsg, "LIV.2) CTableMetadata...FileName=%s\n", fileName);
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTableMetadata()", errmsg);

        if(m_table_metadata->saveFile(fileName) == RSOK)
        {
            sprintf(errmsg, "LIV.2.1) CTableMetadata...Data Saved!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTableMetadata()", errmsg);
        }
        else
        {
            sprintf(errmsg, "LIV.2.2) CTableMetadata...Data NOT Saved! ERROR!!!\n");
            warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTableMetadata()", errmsg);
        }
    }

    sprintf(errmsg, "LIV.3) Terminate TableMetadata... Endded!\n");
    warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_APPMAIN_H, "terminateTableMetadata()", errmsg);
}

void CAppMain::init(int bDoRebuild, char* cfgfile)
{
    initConfig(cfgfile);
    
    initSequences(bDoRebuild);
    initUsers(bDoRebuild);
    initTablespace(bDoRebuild);
    initTableMetadata();
}

void CAppMain::test()
{
    CAppTest appTest;
    appTest.execute();    
}

void CAppMain::remoteExec()
{
    CCmdExec cmdExec(NULL, NULL);
    cmdExec.doExecTest();    
}

void CAppMain::terminate()
{
    terminateTableMetadata();
    terminateTablespace();
    terminateUsers();
    terminateSequences();

    terminateConfig();
}

/* Getters/Setters */
        
CCfgContext* CAppMain::getContextPtr()
{
    return m_context;
}

CCfgConfig* CAppMain::getConfigPtr()
{
    return m_config;
}
    
CSequence* CAppMain::getSequencePtr()
{
    return m_sequence;
}

CUsers* CAppMain::getUsersPtr()
{
    return m_users;
}

CTableSpace* CAppMain::getTableSpacePtr()
{
    return m_tablespace;
}

CTableMetadata* CAppMain::getTableMetadataPtr()
{
    return m_table_metadata;
}
