/*
 * Copyright(C) 2020-2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_base_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_BASE_DEFS_H
#define __HORUSSRV_BASE_DEFS_H                  "__HORUSSRV_BASE_DEFS_H"

/* DEBUG MODE DEFINITIONS
 */
#define DEBUG_LEVEL_00                          0       //All Disable
#define DEBUG_LEVEL_01                          1
#define DEBUG_LEVEL_02                          2
#define DEBUG_LEVEL_03                          3
#define DEBUG_LEVEL_04                          4
#define DEBUG_LEVEL_05                          5
//
#define DEBUG_LEVEL_99                          99      //All enable

#define DEBUG_LEVEL                             99

#define DEBUG_MODE_SLEEPTIME                    3       // =3; seconds

#define DEBUG_CFGFILE                           "server_conf.cfg"

/* KEY VALUES
 */
#define K_CR                                    ((char)'\n')
#define K_LF                                    ((char)'\r')

/* DATA TYPES
 */
typedef unsigned char byte;

#define BUFSZ                                   4096

typedef byte buf_t[BUFSZ];

#define STRSZ                                   32

typedef char str_t[STRSZ];

#define BIGSTRSZ                                1024

typedef char bigstr_t[BIGSTRSZ];

#define SBIGSTRSZ                               16384

typedef char sbigstr_t[SBIGSTRSZ];

#define PATHNAMESZ                              2048

typedef char pathname_t[PATHNAMESZ];

/* COMMAND LINE SWITCHES
*/
#define DEF_CMDLINE_REBUILD                     ((char*)"-r")
#define DEF_CMDLINE_STARTLISTENER               ((char*)"-l")
#define DEF_CMDLINE_TESTLISTENER                ((char*)"-tl")
#define DEF_CMDLINE_EXECBENCHMARK               ((char*)"-e")
#define DEF_CMDLINE_REMOTEBENCHMARK1            ((char*)"-rb")      // Test MkDir 
                                                                    // Test Image Upload
                                                                    // Test Image Download
                                                                    // Test Image Convertion GeoTIFF to JPEG
                                                                    // Test Image Reprojection UTM to LL84
                                                                    // Test Image Simplification to 1/4 of the Original Size

#define DEF_CMDLINE_REMOTEBENCHMARK2            ((char*)"-r2")      // Test MkDir 
                                                                    // Test Image Upload
                                                                    // Test Image Download and Image Processing (one image per time)
                                                                    // - Convertion GeoTIFF to JPEG
                                                                    // - Reprojection UTM to LL84
                                                                    // - Simplification to 1/4 of the Original Size

/* REMOTEBENCHMARK1 STEPS (ENABLE/DISABLE) 
*/
#define DEF_REMOTEBENCHMARK1_STEP1_IMAGEMKDIR                   1
#define DEF_REMOTEBENCHMARK1_STEP2_IMAGEUPLOAD                  2
#define DEF_REMOTEBENCHMARK1_STEP3_IMAGEDOWNLOAD                4
#define DEF_REMOTEBENCHMARK1_STEP4_IMAGECONVERTION              8
#define DEF_REMOTEBENCHMARK1_STEP5_IMAGEREPROJECTION            16
#define DEF_REMOTEBENCHMARK1_STEP6_IMAGERESIMPLIFICATION        32

#define DEF_REMOTEBENCHMARK1_EXECUTION_STEPS                    63

/* REMOTEBENCHMARK2 STEPS (ENABLE/DISABLE) 
*/
#define DEF_REMOTEBENCHMARK2_STEP1_IMAGEMKDIR                   1
#define DEF_REMOTEBENCHMARK2_STEP2_IMAGEUPLOAD                  2
#define DEF_REMOTEBENCHMARK2_STEP3_IMAGEDOWNLOADANDPROCESS      4
#define DEF_REMOTEBENCHMARK2_STEP4_IMAGECONVERTION              8
#define DEF_REMOTEBENCHMARK2_STEP5_IMAGEREPROJECTION            16
#define DEF_REMOTEBENCHMARK2_STEP6_IMAGERESIMPLIFICATION        32

#define DEF_REMOTEBENCHMARK2_EXECUTION_STEPS                    63

typedef struct cmdline_struct {
    str_t cfgfile;
    long bDoRebuild;
    long bDoStartListener;
    long bDoTestListener;
    long bDoExecBenchmark;
    long bDoRemoteBenchmark1;
    long bDoRemoteBenchmark2;
} cmdline_t;

/* APPLICATION DEFINITIONS
 */
#define MOD_NAME                                ((char*)"HORUSSVR")

#define MOD_VERSION                             ((char*)"v2.6.20220417")

#define MOD_PARTNER1                            ((char*)"COPPE/UFRJ - Universidade Federal do Rio de Janeiro")
#define MOD_PARTNER2                            ((char*)"TLMV Consultoria e Sistemas EIRELI")

#define MOD_AUTHOR_NAME                         ((char*)"Luiz Marcio Faria de Aquino Viana, M.Sc.")
#define MOD_AUTHOR_DRE                          ((char*)"120048833")
#define MOD_AUTHOR_CPF                          ((char*)"024.723.347-10")
#define MOD_AUTHOR_ID                           ((char*)"08855128-8 IFP-RJ")
#define MOD_AUTHOR_PROFREG                      ((char*)"2000103581 CREA-RJ")
#define MOD_AUTHOR_PHONE                        ((char*)"(21)99983-7207")
#define MOD_AUTHOR_EMAIL1                       ((char*)"lmarcio@cos.ufrj.br")
#define MOD_AUTHOR_EMAIL2                       ((char*)"lmarcio@tlmv.com.br")

/* APPLICATION HELP
 */
#define HLP_TEXT_USAGE                          ((char*)"Usage: ./horussrv [cfgfile] -options")
//
#define HLP_TEXT_OPTION_REBUILD                 ((char*)"Rebuild database.")
#define HLP_TEXT_OPTION_STARTLISTENER           ((char*)"Start listener mode.")
#define HLP_TEXT_OPTION_TESTLISTENER            ((char*)"Run listener mode test (test only).")
#define HLP_TEXT_OPTION_EXECBENCHMARK           ((char*)"Execute Benchmark.")
#define HLP_TEXT_OPTION_REMOTEBENCHMARK1        ((char*)"Remote Benchmark (Type 1).")
#define HLP_TEXT_OPTION_REMOTEBENCHMARK2        ((char*)"Remote Benchmark (Type 2).")

/* BASIC DEFINITIONS
 */
#define EXT_DAT                                 ".dat"
#define EXT_IDX                                 ".idx"
#define EXT_LOG                                 ".log"
#define EXT_TMP                                 ".$"

#define RSERR                                   -1
#define RSOK                                    0

#define FALSE                                   0
#define TRUE                                    1 

#define DEF_CASESENSITIVE_NONE                  0
#define DEF_CASESENSITIVE_TOUPPER               1
#define DEF_CASESENSITIVE_TOLOWER               2

/* FILE MODES
 */
//ASCII
#define FILMODE_READ_ASCII                      "r"
#define FILMODE_WRITE_ASCII                     "w"
#define FILMODE_APPEND_ASCII                    "a"
//BINARY
#define FILMODE_READ                            "rb"
#define FILMODE_READ_WRITE                      "rb+"
#define FILMODE_WRITE                           "wb"
#define FILMODE_WRITE_TRUNCATE_DATA             "wb+"
#define FILMODE_APPEND                          "ab"
#define FILMODE_READ_APPEND                     "ab+"

/* CHECK FILE ACCESS RESULT
*/
#define FILE_ACCESS_RESULT(v)                   ((v == -1) ? RSERR : RSOK)

/* FILE MODES
 */
//ASCII
#define FILMODE_READ_ASCII                      "r"
#define FILMODE_WRITE_ASCII                     "w"
#define FILMODE_APPEND_ASCII                    "a"
//BINARY
#define FILMODE_READ                            "rb"
#define FILMODE_READ_WRITE                      "rb+"
#define FILMODE_WRITE                           "wb"
#define FILMODE_WRITE_TRUNCATE_DATA             "wb+"
#define FILMODE_APPEND                          "ab"
#define FILMODE_READ_APPEND                     "ab+"

/* AUXILIARY FUNCTIONS
 */
#define MIN(X,Y)                                ((X <= Y) ? X : Y)
#define MAX(X,Y)                                ((X >= Y) ? X : Y)

#define IFNULL(X,Y)                             ((X == NULL) ? Y : X)

/* DATABASE NULL VALUES
 */
#define DBNULL_LONG                             ((long)LONG_MIN)
#define DBNULL_DOUBLE                           ((double)LONG_MIN)
#define DBNULL_CHAR                             '\0'
#define DBNULL_STR                              "\0"

/* DATABASE TRUE/FALSE VALUES
 */
#define DBFALSE                                 ((long)0L)
#define DBTRUE                                  ((long)1L)

/* IMAGE TYPES
 */
#define IMGTYPE_TIF                             ((long)1001L)
#define IMGTYPE_JPG                             ((long)1002L)
#define IMGTYPE_BMP                             ((long)1003L)
#define IMGTYPE_PNG                             ((long)1004L)

#endif
