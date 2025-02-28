/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 26/06/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

void parserParams(int argc, char** argv, cmdline_t* pCmdline)
{
    pCmdline->bDoRebuild = DBFALSE;
    pCmdline->bDoStartListener = DBFALSE;
    pCmdline->bDoTestListener = DBFALSE;
    pCmdline->bDoExecBenchmark = DBFALSE;
    pCmdline->bDoRemoteBenchmark1 = DBFALSE;
    pCmdline->bDoRemoteBenchmark2 = DBFALSE;

    strNCpyUtil(pCmdline->cfgfile, argv[1], STRSZ);

    for(int i = 0; i < argc; i++)
    {
        if(strNCmpUtil(argv[i], DEF_CMDLINE_REBUILD, STRSZ) == 0)
            pCmdline->bDoRebuild = DBTRUE;
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_STARTLISTENER, STRSZ) == 0)
            pCmdline->bDoStartListener = DBTRUE;
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_TESTLISTENER, STRSZ) == 0)
            pCmdline->bDoTestListener = DBTRUE;
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_EXECBENCHMARK, STRSZ) == 0) {
            pCmdline->bDoStartListener = DBTRUE;
            pCmdline->bDoExecBenchmark = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_REMOTEBENCHMARK1, STRSZ) == 0) {
            pCmdline->bDoStartListener = DBTRUE;
            pCmdline->bDoRemoteBenchmark1 = DBTRUE;
        }
        else if(strNCmpUtil(argv[i], DEF_CMDLINE_REMOTEBENCHMARK2, STRSZ) == 0) {
            pCmdline->bDoStartListener = DBTRUE;
            pCmdline->bDoRemoteBenchmark2 = DBTRUE;
        }
    }
}

void showParams(cmdline_t* pCmdline)
{
    printf("\n");
    printf("\nCommand line parameters:\n");
    printf("\nREBUILD = %ld", pCmdline->bDoRebuild);
    printf("\nSTART_LISTENER = %ld", pCmdline->bDoStartListener);
    printf("\nTEST_LISTENER = %ld", pCmdline->bDoTestListener);
    printf("\nEXEC_BENCHMARK = %ld", pCmdline->bDoExecBenchmark);
    printf("\nREMOTE_BENCHMARK (TYPE 1) = %ld", pCmdline->bDoRemoteBenchmark1);
    printf("\nREMOTE_BENCHMARK (TYPE 2) = %ld", pCmdline->bDoRemoteBenchmark2);
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
    printf("E-mails: %s / %s\n\n", MOD_AUTHOR_EMAIL1, MOD_AUTHOR_EMAIL2);

    printf("===\n\n");
}

void showUsageMessage()
{
    printf("%s\n", HLP_TEXT_USAGE);

    printf("\t%s - %s\n", DEF_CMDLINE_REBUILD, HLP_TEXT_OPTION_REBUILD);
    printf("\t%s - %s\n", DEF_CMDLINE_STARTLISTENER, HLP_TEXT_OPTION_STARTLISTENER);
    printf("\t%s - %s\n", DEF_CMDLINE_TESTLISTENER, HLP_TEXT_OPTION_TESTLISTENER);
    printf("\t%s - %s\n", DEF_CMDLINE_EXECBENCHMARK, HLP_TEXT_OPTION_EXECBENCHMARK);
    printf("\t%s - %s\n", DEF_CMDLINE_REMOTEBENCHMARK1, HLP_TEXT_OPTION_REMOTEBENCHMARK1);
    printf("\t%s - %s\n", DEF_CMDLINE_REMOTEBENCHMARK2, HLP_TEXT_OPTION_REMOTEBENCHMARK2);

    printf("\n");
}

int main(int argc, char** argv)
{
    cmdline_t cmdline;

    showHeaderMessage();

    if(argc < 2) {
        showUsageMessage();
        exit(0);
    }

    parserParams(argc, argv, & cmdline);

    showParams(& cmdline);

    printf("START HORUSSRV...\n");
    gAppMain.init(cmdline.bDoRebuild, cmdline.cfgfile);

    if(cmdline.bDoRebuild == DBTRUE)
    {
        printf("TEST HORUSSRV...\n");
        gAppMain.test();
    }

    if(cmdline.bDoStartListener == DBTRUE)
    {
        printf("START HORUSSRV LISTENER...\n");
        gCmdListener.start();

        if(cmdline.bDoTestListener == DBTRUE)
        {
            showMessage("TEST HORUSSRV LISTENER", DBTRUE);
            gCmdListener.test();

            showMessage("TERMINATE HORUSSRV LISTENER", DBTRUE);
            gCmdListener.stop();
        }

        if(cmdline.bDoExecBenchmark == DBTRUE)
        {
            showMessage("EXEC HORUSSRV BENCHMARK", DBTRUE);
            gCmdListener.exec();

            printf("TERMINATE HORUSSRV LISTENER...\n");
            gCmdListener.stop();
        }

        if(cmdline.bDoRemoteBenchmark1 == DBTRUE)
        {
            showMessage("REMOTE HORUSSRV BENCHMARK (TYPE 1)", DBTRUE);
            gCmdListener.remoteExec1();

            printf("TERMINATE HORUSSRV LISTENER...\n");
            gCmdListener.stop();
        }

        if(cmdline.bDoRemoteBenchmark2 == DBTRUE)
        {
            showMessage("REMOTE HORUSSRV BENCHMARK (TYPE 2)", DBTRUE);
            gCmdListener.remoteExec2();

            printf("TERMINATE HORUSSRV LISTENER...\n");
            gCmdListener.stop();
        }

        while(gCmdListener.isRunning() == TRUE)
            sleep(DEBUG_MODE_SLEEPTIME);

        printf("FINISH HORUSSRV LISTENER... \n");
    }

    printf("TERMINATE HORUSSRV...\n");
    gAppMain.terminate();

    return 0;
}
