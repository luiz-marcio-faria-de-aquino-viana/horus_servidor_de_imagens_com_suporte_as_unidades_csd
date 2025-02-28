/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_apptest.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 23/06/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CAppTest::CAppTest()
{
    //TODO:
}

CAppTest::~CAppTest()
{
    //TODO:
}

void CAppTest::testSequences()
{
    bigstr_t errmsg;

    sprintf(errmsg, "XI.1) Sequence Test: %s\n", (char*)SEQ_USERS);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);
    
    //IMGRIO
    CSequence* pSequence = gAppMain.getSequencePtr();
    pSequence->addItem(
        SEQ_IMGRIO_OID,
        (char*)SEQ_IMGRIO, 
        (char*)SEQ_IMGRIO, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.1) CSequence::AddItem(%s)...OK.\n", SEQ_IMGRIO);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    //PATSAND
    pSequence->addItem(
        SEQ_PATSAND_OID,
        (char*)SEQ_PATSAND, 
        (char*)SEQ_PATSAND, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.2) CSequence::AddItem(%s)...OK.\n", SEQ_PATEARTH);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    //PATGRASS
    pSequence->addItem(
        SEQ_PATGRASS_OID,
        (char*)SEQ_PATGRASS, 
        (char*)SEQ_PATGRASS, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.3) CSequence::AddItem(%s)...OK.\n", SEQ_PATEARTH);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    //PATEARTH
    pSequence->addItem(
        SEQ_PATEARTH_OID,
        (char*)SEQ_PATEARTH, 
        (char*)SEQ_PATEARTH, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.4) CSequence::AddItem(%s)...OK.\n", SEQ_PATEARTH);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    //PATWATTER
    pSequence->addItem(
        SEQ_PATWATTER_OID,
        (char*)SEQ_PATWATTER, 
        (char*)SEQ_PATWATTER, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.5) CSequence::AddItem(%s)...OK.\n", SEQ_PATWATTER);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    //PATPARCEL
    pSequence->addItem(
        SEQ_PATPARCEL_OID,
        (char*)SEQ_PATPARCEL, 
        (char*)SEQ_PATPARCEL, 
        SEQ_INIT_VAL, 
        SEQ_MAX_VAL, 
        SEQ_CURR_VAL);
    sprintf(errmsg, "XI.1.6) CSequence::AddItem(%s)...OK.\n", SEQ_PATPARCEL);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    long val = pSequence->nextVal((char*)SEQ_USERS); 
    sprintf(errmsg, "XI.2.1) Seq: %s, NextUid: %ld\n", (char*)SEQ_USERS, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_USERS); 
    sprintf(errmsg, "XI.2.2) Seq: %s, NextUid: %ld\n", (char*)SEQ_USERS, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_USERS); 
    sprintf(errmsg, "XI.2.3) Seq: %s, NextUid: %ld\n", (char*)SEQ_USERS, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    sprintf(errmsg, "XI.3) Sequence Test: %s\n", (char*)SEQ_TABLESPACE);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_TABLESPACE); 
    sprintf(errmsg, "XI.3.1) Seq: %s, NextUid: %ld\n", (char*)SEQ_TABLESPACE, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_TABLESPACE); 
    sprintf(errmsg, "XI.3.2) Seq: %s, NextUid: %ld\n", (char*)SEQ_TABLESPACE, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_TABLESPACE); 
    sprintf(errmsg, "XI.3.3) Seq: %s, NextUid: %ld\n", (char*)SEQ_TABLESPACE, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_IMGRIO); 
    sprintf(errmsg, "XI.4.1) Seq: %s, NextUid: %ld\n", (char*)SEQ_IMGRIO, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_IMGRIO); 
    sprintf(errmsg, "XI.4.2) Seq: %s, NextUid: %ld\n", (char*)SEQ_IMGRIO, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

    val = pSequence->nextVal((char*)SEQ_IMGRIO); 
    sprintf(errmsg, "XI.4.3) Seq: %s, NextUid: %ld\n", (char*)SEQ_IMGRIO, val);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testSequences()", errmsg);

}

void CAppTest::testUsers()
{
    bigstr_t errmsg;

    users_t* user;

    sprintf(errmsg, "XII.1) Users' Table\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
 
    sprintf(errmsg, "XII.1.1) Add New Users\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);

    CUsers* pUsers = gAppMain.getUsersPtr();
    pUsers->addItem(
        USR_LMARCIO_UID, 
        (char*)USR_LMARCIO_USERNAME, 
        (char*)USR_LMARCIO_USERNAME, 
        (char*)USR_LMARCIO_PASSWD, 
        USR_LMARCIO_UTYPE);
    sprintf(errmsg, "XII.1.1.1) Add User: Uid=%ld,Username=%s\n", USR_LMARCIO_UID, USR_LMARCIO_USERNAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
 
    pUsers->addItem(
        USR_FELIPE_UID, 
        (char*)USR_FELIPE_USERNAME, 
        (char*)USR_FELIPE_USERNAME, 
        (char*)USR_FELIPE_PASSWD, 
        USR_FELIPE_UTYPE);
    sprintf(errmsg, "XII.1.1.2) Add User: Uid=%ld,Username=%s\n", USR_FELIPE_UID, USR_FELIPE_USERNAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
  
    pUsers->addItem(
        USR_DIEGO_UID, 
        (char*)USR_DIEGO_USERNAME, 
        (char*)USR_DIEGO_USERNAME, 
        (char*)USR_DIEGO_PASSWD, 
        USR_DIEGO_UTYPE);
    sprintf(errmsg, "XII.1.1.3) Add User: Uid=%ld,Username=%s\n", USR_DIEGO_UID, USR_DIEGO_USERNAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
  
    pUsers->addItem(
        USR_TIAGO_UID, 
        (char*)USR_TIAGO_USERNAME, 
        (char*)USR_TIAGO_USERNAME, 
        (char*)USR_TIAGO_PASSWD, 
        USR_TIAGO_UTYPE);
    sprintf(errmsg, "XII.1.1.4) Add User: Uid=%ld,Username=%s\n", USR_TIAGO_UID, USR_TIAGO_USERNAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);

    sprintf(errmsg, "XII.1.2) List Selected Users\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
 
    if(pUsers->findItem(USR_SYSTEM_UID, &user) == RSOK)
        sprintf(errmsg, "XII.1.2.1) Oid: %ld, Username: %s, Passwd: %s\n", user->oid, user->username, user->passwd);
    else
        sprintf(errmsg, "XII.1.2.1) ERR: Can't find Oid: %ld\n", USR_SYSTEM_UID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);

    if(pUsers->findItem(USR_LMARCIO_UID, &user) == RSOK)
        sprintf(errmsg, "XII.1.2.2) Oid: %ld, Username: %s, Passwd: %s\n", user->oid, user->username, user->passwd);
    else
        sprintf(errmsg, "XII.1.2.2) ERR: Can't find Oid: %ld\n", USR_LMARCIO_UID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
 
    if(pUsers->findItem(USR_FELIPE_UID, &user) == RSOK)
        sprintf(errmsg, "XII.1.2.3) Oid: %ld, Username: %s, Passwd: %s\n", user->oid, user->username, user->passwd);
    else
        sprintf(errmsg, "XII.1.2.3) ERR: Can't find Oid: %ld\n", USR_FELIPE_UID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);

    if(pUsers->findItem(USR_DIEGO_UID, &user) == RSOK)
        sprintf(errmsg, "XII.1.2.4) Oid: %ld, Username: %s, Passwd: %s\n", user->oid, user->username, user->passwd);
    else
        sprintf(errmsg, "XII.1.2.4) ERR: Can't find Oid: %ld\n", USR_DIEGO_UID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);

    if(pUsers->findItem(USR_TIAGO_UID, &user) == RSOK)
        sprintf(errmsg, "XII.1.2.5) Oid: %ld, Username: %s, Passwd: %s\n", user->oid, user->username, user->passwd);
    else
        sprintf(errmsg, "XII.1.2.5) ERR: Can't find Oid: %ld\n", USR_TIAGO_UID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testUsers()", errmsg);
}

void CAppTest::testTableSpace()
{
    bigstr_t errmsg;

    tablespace_t* tablespace;

    sprintf(errmsg, "XIII.1) List TableSpace\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableSpace()", errmsg);
 
    CTableSpace* pTableSpace = gAppMain.getTableSpacePtr();
    if(pTableSpace->findItem(TBLSPC_USERS_OID, &tablespace) == RSOK) 
        sprintf(errmsg, "XIII.1.1) Oid: %ld, Tablespace: %s, Path: %s\n", tablespace->oid, tablespace->tablespace_name, tablespace->tablespace_path);
    else
        sprintf(errmsg, "XIII.1.1) ERR: Can't find Oid: %ld\n", TBLSPC_USERS_OID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTablespace()", errmsg);

    if(pTableSpace->findItem(TBLSPC_TEMP_OID, &tablespace) == RSOK)
        sprintf(errmsg, "XIII.1.2) Oid: %ld, Tablespace: %s, Path: %s\n", tablespace->oid, tablespace->tablespace_name, tablespace->tablespace_path);
    else
        sprintf(errmsg, "XIII.1.2) ERR: Can't find Oid: %ld\n", TBLSPC_TEMP_OID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTablespace()", errmsg);
}

void CAppTest::testTableMetadata()
{
    bigstr_t errmsg;

    table_metadata_t* table_metadata;

    sprintf(errmsg, "XIV.1) Metadata Table\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    sprintf(errmsg, "XIV.1.1) Add New Table Metadata\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    long imgrio_tblspc[] = {
        TBLMETA_IMGRIO_TBLSPC_OID_0,
        TBLMETA_IMGRIO_TBLSPC_OID_1,
        TBLMETA_IMGRIO_TBLSPC_OID_2,
        TBLMETA_IMGRIO_TBLSPC_OID_3,
        TBLMETA_IMGRIO_TBLSPC_OID_4,
        TBLMETA_IMGRIO_TBLSPC_OID_5
    };

    CTableMetadata* pTableMetadata = gAppMain.getTableMetadataPtr();
    pTableMetadata->addItem(
        TBLMETA_IMGRIO_OID,
        (char*)TBLMETA_IMGRIO_TABLE_NAME, 
        imgrio_tblspc,
        TBLMETA_IMGRIO_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_IMGRIO_TBTYPE,
        TBLMETA_IMGRIO_REF_TABLE_OID,
        (char*)TBLMETA_IMGRIO_MODNAME,
        (char*)TBLMETA_IMGRIO_TABLE_NAME,
        (char*)TBLMETA_IMGRIO_TABLE_FILENAME,
        (char*)TBLMETA_IMGRIO_IDX1_NAME,
        (char*)TBLMETA_IMGRIO_IDX1_FILENAME,
        (char*)TBLMETA_IMGRIO_IDX2_NAME,
        (char*)TBLMETA_IMGRIO_IDX2_FILENAME,
        (char*)TBLMETA_IMGRIO_SEQ_NAME,
        TBLMETA_IMGRIO_UID);
    sprintf(errmsg, "XIV.1.1.1) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_IMGRIO_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    long patsand_tblspc[] = {
        TBLMETA_PATSAND_TBLSPC_OID_0,
        TBLMETA_PATSAND_TBLSPC_OID_1,
        TBLMETA_PATSAND_TBLSPC_OID_2,
        TBLMETA_PATSAND_TBLSPC_OID_3,
        TBLMETA_PATSAND_TBLSPC_OID_4,
        TBLMETA_PATSAND_TBLSPC_OID_5
    };

    pTableMetadata->addItem(
        TBLMETA_PATSAND_OID,
        (char*)TBLMETA_PATSAND_TABLE_NAME, 
        patsand_tblspc,
        TBLMETA_PATSAND_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_PATSAND_TBTYPE,
        TBLMETA_PATSAND_REF_TABLE_OID,
        (char*)TBLMETA_PATSAND_MODNAME,
        (char*)TBLMETA_PATSAND_TABLE_NAME,
        (char*)TBLMETA_PATSAND_TABLE_FILENAME,
        (char*)TBLMETA_PATSAND_IDX1_NAME,
        (char*)TBLMETA_PATSAND_IDX1_FILENAME,
        (char*)TBLMETA_PATSAND_IDX2_NAME,
        (char*)TBLMETA_PATSAND_IDX2_FILENAME,
        (char*)TBLMETA_PATSAND_SEQ_NAME,
        TBLMETA_PATSAND_UID);
    sprintf(errmsg, "XIV.1.1.2) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_PATSAND_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

   long patgrass_tblspc[] = {
        TBLMETA_PATGRASS_TBLSPC_OID_0,
        TBLMETA_PATGRASS_TBLSPC_OID_1,
        TBLMETA_PATGRASS_TBLSPC_OID_2,
        TBLMETA_PATGRASS_TBLSPC_OID_3,
        TBLMETA_PATGRASS_TBLSPC_OID_4,
        TBLMETA_PATGRASS_TBLSPC_OID_5
    };

    pTableMetadata->addItem(
        TBLMETA_PATGRASS_OID,
        (char*)TBLMETA_PATGRASS_TABLE_NAME, 
        patgrass_tblspc,
        TBLMETA_PATGRASS_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_PATGRASS_TBTYPE,
        TBLMETA_PATGRASS_REF_TABLE_OID,
        (char*)TBLMETA_PATGRASS_MODNAME,
        (char*)TBLMETA_PATGRASS_TABLE_NAME,
        (char*)TBLMETA_PATGRASS_TABLE_FILENAME,
        (char*)TBLMETA_PATGRASS_IDX1_NAME,
        (char*)TBLMETA_PATGRASS_IDX1_FILENAME,
        (char*)TBLMETA_PATGRASS_IDX2_NAME,
        (char*)TBLMETA_PATGRASS_IDX2_FILENAME,
        (char*)TBLMETA_PATGRASS_SEQ_NAME,
        TBLMETA_PATGRASS_UID);
    sprintf(errmsg, "XIV.1.1.3) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_PATGRASS_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

   long patearth_tblspc[] = {
        TBLMETA_PATEARTH_TBLSPC_OID_0,
        TBLMETA_PATEARTH_TBLSPC_OID_1,
        TBLMETA_PATEARTH_TBLSPC_OID_2,
        TBLMETA_PATEARTH_TBLSPC_OID_3,
        TBLMETA_PATEARTH_TBLSPC_OID_4,
        TBLMETA_PATEARTH_TBLSPC_OID_5
    };

    pTableMetadata->addItem(
        TBLMETA_PATEARTH_OID,
        (char*)TBLMETA_PATEARTH_TABLE_NAME, 
        patearth_tblspc,
        TBLMETA_PATEARTH_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_PATEARTH_TBTYPE,
        TBLMETA_PATEARTH_REF_TABLE_OID,
        (char*)TBLMETA_PATEARTH_MODNAME,
        (char*)TBLMETA_PATEARTH_TABLE_NAME,
        (char*)TBLMETA_PATEARTH_TABLE_FILENAME,
        (char*)TBLMETA_PATEARTH_IDX1_NAME,
        (char*)TBLMETA_PATEARTH_IDX1_FILENAME,
        (char*)TBLMETA_PATEARTH_IDX2_NAME,
        (char*)TBLMETA_PATEARTH_IDX2_FILENAME,
        (char*)TBLMETA_PATEARTH_SEQ_NAME,
        TBLMETA_PATEARTH_UID);
    sprintf(errmsg, "XIV.1.1.4) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_PATEARTH_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

   long patwatter_tblspc[] = {
        TBLMETA_PATWATTER_TBLSPC_OID_0,
        TBLMETA_PATWATTER_TBLSPC_OID_1,
        TBLMETA_PATWATTER_TBLSPC_OID_2,
        TBLMETA_PATWATTER_TBLSPC_OID_3,
        TBLMETA_PATWATTER_TBLSPC_OID_4,
        TBLMETA_PATWATTER_TBLSPC_OID_5
    };

    pTableMetadata->addItem(
        TBLMETA_PATWATTER_OID,
        (char*)TBLMETA_PATWATTER_TABLE_NAME, 
        patwatter_tblspc,
        TBLMETA_PATWATTER_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_PATWATTER_TBTYPE,
        TBLMETA_PATWATTER_REF_TABLE_OID,
        (char*)TBLMETA_PATWATTER_MODNAME,
        (char*)TBLMETA_PATWATTER_TABLE_NAME,
        (char*)TBLMETA_PATWATTER_TABLE_FILENAME,
        (char*)TBLMETA_PATWATTER_IDX1_NAME,
        (char*)TBLMETA_PATWATTER_IDX1_FILENAME,
        (char*)TBLMETA_PATWATTER_IDX2_NAME,
        (char*)TBLMETA_PATWATTER_IDX2_FILENAME,
        (char*)TBLMETA_PATWATTER_SEQ_NAME,
        TBLMETA_PATWATTER_UID);
    sprintf(errmsg, "XIV.1.1.5) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_PATWATTER_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

   long patparcel_tblspc[] = {
        TBLMETA_PATPARCEL_TBLSPC_OID_0,
        TBLMETA_PATPARCEL_TBLSPC_OID_1,
        TBLMETA_PATPARCEL_TBLSPC_OID_2,
        TBLMETA_PATPARCEL_TBLSPC_OID_3,
        TBLMETA_PATPARCEL_TBLSPC_OID_4,
        TBLMETA_PATPARCEL_TBLSPC_OID_5
    };

    pTableMetadata->addItem(
        TBLMETA_PATPARCEL_OID,
        (char*)TBLMETA_PATPARCEL_TABLE_NAME, 
        patparcel_tblspc,
        TBLMETA_PATPARCEL_NUM_TBLSPC,
        ((long)0L),
        TBLMETA_PATPARCEL_TBTYPE,
        TBLMETA_PATPARCEL_REF_TABLE_OID,
        (char*)TBLMETA_PATPARCEL_MODNAME,
        (char*)TBLMETA_PATPARCEL_TABLE_NAME,
        (char*)TBLMETA_PATPARCEL_TABLE_FILENAME,
        (char*)TBLMETA_PATPARCEL_IDX1_NAME,
        (char*)TBLMETA_PATPARCEL_IDX1_FILENAME,
        (char*)TBLMETA_PATPARCEL_IDX2_NAME,
        (char*)TBLMETA_PATPARCEL_IDX2_FILENAME,
        (char*)TBLMETA_PATPARCEL_SEQ_NAME,
        TBLMETA_PATPARCEL_UID);
    sprintf(errmsg, "XIV.1.1.6) CTableMetadata::AddItem(%s)...OK.\n", TBLMETA_PATPARCEL_TABLE_NAME);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

    sprintf(errmsg, "XIV.2) CTableMetadata::List All Entries\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
    
    pTableMetadata->debug(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "initTableMetadata()");

    sprintf(errmsg, "XIV.3) List Table Metadata\n");
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    if(pTableMetadata->findItem(TBLMETA_IMGRIO_OID, &table_metadata) == RSOK) 
        sprintf(errmsg, "XIV.3.1) Oid: %ld, TableMetadata: %s, FileName: %s\n", table_metadata->oid, table_metadata->table_name, table_metadata->table_filename);
    else
        sprintf(errmsg, "XIV.3.1) ERR: Can't find Oid: %ld\n", TBLMETA_IMGRIO_OID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    if(pTableMetadata->findItem(TBLMETA_PATSAND_OID, &table_metadata) == RSOK) 
        sprintf(errmsg, "XIV.3.2) Oid: %ld, TableMetadata: %s, FileName: %s\n", table_metadata->oid, table_metadata->table_name, table_metadata->table_filename);
    else
        sprintf(errmsg, "XIV.3.2) ERR: Can't find Oid: %ld\n", TBLMETA_PATSAND_OID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);
 
    if(pTableMetadata->findItem(TBLMETA_PATGRASS_OID, &table_metadata) == RSOK) 
        sprintf(errmsg, "XIV.3.3) Oid: %ld, TableMetadata: %s, FileName: %s\n", table_metadata->oid, table_metadata->table_name, table_metadata->table_filename);
    else
        sprintf(errmsg, "XIV.3.3) ERR: Can't find Oid: %ld\n", TBLMETA_PATGRASS_OID);
    warnMsg(DEBUG_LEVEL_99, __HORUSSRV_MOD_APPTEST_H, "testTableMetadata()", errmsg);

}

void CAppTest::execute()
{
    if(DEBUG_LEVEL == DEBUG_LEVEL_00) return;

    testSequences();
    testUsers();
    testTableSpace();
    testTableMetadata();
}
