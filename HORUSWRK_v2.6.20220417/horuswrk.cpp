/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 26/06/2020
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

void parserParams(int argc, char** argv, cmdline_t* pCmdline)
{
    pCmdline->bDoRebuild = DBFALSE;
    pCmdline->bDoAnalisys = DBFALSE;
    pCmdline->bDoLocalExec = DBFALSE;
    pCmdline->bDoRemoteExec = DBFALSE;
    pCmdline->bDoStartListener = DBFALSE;
    pCmdline->bDoTestListener = DBFALSE;
    pCmdline->bDoTestDiskMan = DBFALSE;
    pCmdline->bDoTestIndex = DBFALSE;

    strNCpyUtil(pCmdline->cfgfile, argv[1], STRSZ);

    for(int i = 2; i < argc; i++)
    {
        if(strNCmpUtil(argv[i], DEF_CMDLINE_REBUILD, STRSZ) == 0) {
            pCmdline->bDoRebuild = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_ANALISYS, STRSZ) == 0) {
            pCmdline->bDoAnalisys = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_LOCALEXEC, STRSZ) == 0) {
            pCmdline->bDoLocalExec = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_REMOTEEXEC, STRSZ) == 0) {
            pCmdline->bDoRemoteExec = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_STARTLISTENER, STRSZ) == 0) {
            pCmdline->bDoStartListener = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_TESTLISTENER, STRSZ) == 0) {
            pCmdline->bDoStartListener = DBTRUE;
            pCmdline->bDoTestListener = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_TESTDISKMAN, STRSZ) == 0) {
            pCmdline->bDoTestDiskMan = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_TESTINDEX, STRSZ) == 0) {
            pCmdline->bDoTestIndex = DBTRUE;
        }
    }
}

void showParams(cmdline_t* pCmdline)
{
    printf("\nCommand line parameters:\n");
    printf("\nREBUILD = %ld", pCmdline->bDoRebuild);
    printf("\nANALISYS = %ld", pCmdline->bDoAnalisys);
    printf("\nLOCAL_EXEC = %ld", pCmdline->bDoLocalExec);
    printf("\nREMOTE_EXEC = %ld", pCmdline->bDoRemoteExec);
    printf("\nSTART_LISTENER = %ld", pCmdline->bDoStartListener);
    printf("\nTEST_LISTENER = %ld", pCmdline->bDoTestListener);
    printf("\nTEST_DISKMAN = %ld", pCmdline->bDoTestDiskMan);
    printf("\nTEST_INDEX = %ld", pCmdline->bDoTestIndex);
    printf("\n\n");
}

void showHeaderMessage()
{
    printf("\n");

    printf("=== %s %s\n\n", MOD_NAME, MOD_VERSION);

    printf("Partners:\n\t%s\n\t%s\n\n", MOD_PARTNER1, MOD_PARTNER2);

    printf("Author: %s\n", MOD_AUTHOR_NAME);
    printf("DRE: %s\n", MOD_AUTHOR_DRE);
    printf("CPF: %s\n", MOD_AUTHOR_CPF);
    printf("ID: %s\n", MOD_AUTHOR_ID);
    printf("Registro: %s\n", MOD_AUTHOR_PROFREG);
    printf("Phone: %s\n", MOD_AUTHOR_PHONE);
    printf("E-mail:\n");
    printf("\t%s\n", MOD_AUTHOR_EMAIL1);
    printf("\t%s\n", MOD_AUTHOR_EMAIL2);
    printf("\t%s\n\n", MOD_AUTHOR_EMAIL3);

    printf("===\n");
}

void showUsageMessage()
{
    printf("%s\n", HLP_TEXT_USAGE);

    printf("\t%s - %s\n", DEF_CMDLINE_REBUILD, HLP_TEXT_OPTION_REBUILD);
    printf("\t%s - %s\n", DEF_CMDLINE_ANALISYS, HLP_TEXT_OPTION_ANALISYS);
    printf("\t%s - %s\n", DEF_CMDLINE_LOCALEXEC, HLP_TEXT_OPTION_LOCALEXEC);
    printf("\t%s - %s\n", DEF_CMDLINE_REMOTEEXEC, HLP_TEXT_OPTION_REMOTEEXEC);
    printf("\t%s - %s\n", DEF_CMDLINE_STARTLISTENER, HLP_TEXT_OPTION_STARTLISTENER);
    printf("\t%s - %s\n", DEF_CMDLINE_TESTLISTENER, HLP_TEXT_OPTION_TESTLISTENER);
    printf("\t%s - %s\n", DEF_CMDLINE_TESTDISKMAN, HLP_TEXT_OPTION_TESTDISKMAN);
    printf("\t%s - %s\n", DEF_CMDLINE_TESTINDEX, HLP_TEXT_OPTION_TESTINDEX);
}

int main(int argc, char** argv)
{
    cmdline_t cmdline;

    showHeaderMessage();
    
    if(argc < 3) {
        showUsageMessage();
        exit(0);
    }

    parserParams(argc, argv, & cmdline);

    showParams(& cmdline);

    printf("START HORUSWRK...\n");
    gAppMain.init(cmdline.bDoRebuild, cmdline.cfgfile);

    if(cmdline.bDoRebuild == DBTRUE) {
        showMessage("TEST HORUSWRK", DBTRUE);
        gAppMain.test();
    }

    if(cmdline.bDoAnalisys == DBTRUE) {
        showMessage("DATA ANALISYS HORUSWRK", DBTRUE);
        gAppMain.dataAnalisys();
    }

    if(cmdline.bDoTestIndex == DBTRUE) {
        showMessage("TEST INDEX HORUSWRK", DBTRUE);
        gAppMain.testIndex();
    }

    if(cmdline.bDoLocalExec == DBTRUE) {
        showMessage("LOCAL EXECUTION HORUSWRK", DBTRUE);
        gAppMain.localExec();
    }

    if(cmdline.bDoRemoteExec == DBTRUE) {
        showMessage("REMOTE EXECUTION HORUSWRK", DBTRUE);
        gAppMain.remoteExec();
    }

    if(cmdline.bDoTestDiskMan == DBTRUE) {
        showMessage("TEST DISK MANAGER HORUSWRK", DBTRUE);
        gAppMain.testDiskMan();
    }

    if(cmdline.bDoStartListener == DBTRUE) {
        showMessage("START HORUSWRK LISTENER", DBTRUE);
        gCmdListener.start();

        if(cmdline.bDoTestListener == DBTRUE) {
            showMessage("TEST HORUSWRK LISTENER", DBTRUE);
            gCmdListener.test();
        }

        showMessageAndWaitForKey("TERMINATE HORUSWRK LISTENER");
        gCmdListener.stop();
    }

    printf("\nTERMINATE HORUSWRK...\n");
    gAppMain.terminate();

    return 0;
}
