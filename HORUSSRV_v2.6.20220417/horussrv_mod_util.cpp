/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_util.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 16/05/2020
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

/* STRING UTILS
 */

int strIsEmptyUtil(char* src)
{
    if((*src) == '\0')
        return(DBTRUE);
    return(DBFALSE);
}

char* strSetEmptyUtil(char* src)
{
    (*src) = '\0';
    return(src);
}

int strLenUtil(char* src, int n)
{
    char* p_src = src;
    int n_src = 0;
    while(n_src < n) {
        if((*p_src) == '\0') break;
        p_src++;
        n_src += 1;
    }
    return(n_src);
}

int strCharCountUtil(char* src, int n, char c)
{
    char* p = src;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if((*p) == '\0') break;
        if((*p) == c)
            cnt += 1;
        p++;
    }
    return cnt;
}

char* strPiece(char* inPath, int inPathSz, char* outPath, int outPathSz, char c, int n)
{
    char* p_in = inPath;
    char* p_out = outPath;

    int n_in = 0;
    int n_last = n;

    if(n_in < n_last) {
        int i = 0;
        for( ; i < inPathSz; i++) {
            if((*p_in) == '\0') break;
            if((*p_in) == c) {
                n_in += 1;
                if(n_in >= n_last) {
                    p_in++;
                    break;
                }
            }
            p_in++;
        }
    }

    if(n_in >= n_last) {
        int j = 0;
        for( ; j < outPathSz; j++) {
            if((*p_in) == '\0') break;
            if((*p_in) == c) break;
            (*p_out) = (*p_in);
            p_out++;
            p_in++;
        }        
        (*p_out) = '\0';
        outPath[outPathSz - 1] = '\0';
    }
    return outPath;
}

char* strNCpyCaseUtil(char* dst, char* src, int n, int caseSensitive)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        if(caseSensitive == DEF_CASESENSITIVE_TOUPPER)
            (*p_dst) = toupper(*p_src);
        else if(caseSensitive == DEF_CASESENSITIVE_TOLOWER)
            (*p_dst) = tolower(*p_src);
        else 
            (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

char* strNCpyUtil(char* dst, char* src, int n)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

char* strNCatUtil(char* dst, char* src, int n)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        if((*p_dst) == '\0') break;

        p_dst++;       
        n_dst += 1;
    }

    while(n_dst < n)
    {
        (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

int strNCmpUtil(char* src1, char* src2, int n)          // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        if((*p_src1) < (*p_src2))
            return -1;

        if((*p_src1) > (*p_src2))
            return 1;

        p_src1++;
        p_src2++;

        n_src += 1;
    }

    if((*p_src1) < (*p_src2))
        return -1;

    if((*p_src1) > (*p_src2))
        return 1;

    return 0;
}

int strNCmpCaseUtil(char* src1, char* src2, int n, int caseSensitive)           // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        int c_src1 = (*p_src1);
        int c_src2 = (*p_src2);

        if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
            c_src1 = toupper(*p_src1);
            c_src2 = toupper(*p_src2);
        }
        else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
            c_src1 = tolower(*p_src1);
            c_src2 = tolower(*p_src2);
        }

        if(c_src1 < c_src2)
            return -1;

        if(c_src1 > c_src2)
            return 1;

        p_src1++;
        p_src2++;

        n_src += 1;
    }

    int c_src1 = (*p_src1);
    int c_src2 = (*p_src2);

    if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
        c_src1 = toupper(*p_src1);
        c_src2 = toupper(*p_src2);
    }
    else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
        c_src1 = tolower(*p_src1);
        c_src2 = tolower(*p_src2);
    }

    if(c_src1 < c_src2)
        return -1;

    if(c_src1 > c_src2)
        return 1;

    return 0;
}

char* strRemoveEolUtil(char* src, int n)
{
    char* p_src = src;
    int n_src = 0;
    while( (n_src < (n - 1)) && ((*p_src) != '\0') )
    {
        if( ((*p_src) == '\r') || ((*p_src) == '\n') )
            (*p_src) = '\0';
        p_src++;

        n_src += 1;
    }
    return 0;
}

/* MEM UTILS
 */

int memIsNullUtil(byte* src, int n)
{
    for(int i = 0; i < n; i++)
    {
        if((*src) != 0)
            return(DBFALSE);
        src++;
    }
    return(DBTRUE);
}

byte* memSetNullUtil(byte* src, int n)
{
    byte* p = src;
    for(int i = 0; i < n; i++)
    {
        (*p) = 0;
        p++;
    }
    return(src);
}

byte* memNCpyUtil(byte* dst, byte* src, int n)
{
    byte* p_src = src;
    byte* p_dst = dst;

    for(int i = 0; i < n; i++)
    {
        (*p_dst) = (*p_src);

        p_src++;
        p_dst++;       
    }
    return(dst);
}

byte* memNCatUtil(byte* dst, byte* src, int n_i, int n)
{
    byte* p_src = src;
    byte* p_dst = dst;

    for(int i = 0; i < n_i; i++)
        p_dst++;       

    int n_sz = n - n_i + 1;
    for(int i = n_i; i < n_sz; i++)
    {
        (*p_dst) = (*p_src);

        p_src++;
        p_dst++;       
    }
    return(dst);
}

int memNCmpUtil(byte* src1, byte* src2, int n)      // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    byte* p_src1 = src1;
    byte* p_src2 = src2;

    for(int i = 0; i < n; i++)
    {
        if((*p_src1) < (*p_src2))
            return -1;

        if((*p_src1) > (*p_src2))
            return 1;

        p_src1++;
        p_src2++;
    }

    return 0;
}

/* FILE OPERATIONS
 */

/* FILE NAME AND PATH OPERATIONS
 */

char* getFileName(char* inFileName, int inFileNameSz, char* outFileName, int outFileNameSz)
{
    int path_len = getPathLen(inFileName, inFileNameSz);
    getPathAt(inFileName, inFileNameSz, outFileName, outFileNameSz, path_len);
    return outFileName;
}

char* getFileNameWithoutExt(char* inFileName, int inFileNameSz, char* outFileName, int outFileNameSz)
{
    bigstr_t strTmp;
    int n = strCharCountUtil(inFileName, inFileNameSz, '.');
    strPiece(inFileName, inFileNameSz, strTmp, BIGSTRSZ, '.', n - 1);
    getFileName(inFileName, inFileNameSz, outFileName, outFileNameSz);
    return outFileName;
}

char* getFileExt(char* inFileName, int inFileNameSz, char* outFileExt, int outFileExtSz)
{
    int n = strCharCountUtil(inFileName, inFileNameSz, '.');
    strPiece(inFileName, inFileNameSz, outFileExt, outFileExtSz, '.', n);
    return outFileExt;
}

int getPathLen(char* inPath, int inPathSz)
{
    int n = strCharCountUtil(inPath, inPathSz, '/');
    return n;
}

char* getPathAt(char* inPath, int inPathSz, char* outPath, int outPathSz, int n)
{
    strPiece(inPath, inPathSz, outPath, outPathSz, '/', n);
    return outPath;
}

/* FILE OPERATIONS
 */

int existFileUtil(const char* fileName)
{
    FILE* f = fopen(fileName, FILMODE_READ);
    if(f == NULL)
        return(RSERR);
    return(RSOK);
}

int openFileUtil(FILE** f, const char* fileName, const char* fileMode, long bSeekBegin)
{
    int rscode = RSERR;

    (*f) = fopen(fileName, fileMode);
    if((*f) == NULL) {
        warnMsg(DEBUG_LEVEL_01, __HORUSSRV_MOD_UTIL_H, "openFile()", ERR_CANTOPENFILE);
        return(RSERR);
    }

    if(bSeekBegin == DBTRUE) {
        if(fseek((*f), 0L, SEEK_SET) != -1)
            rscode = RSOK;
    }
    else {
        rscode = RSOK;
    }
    return(rscode);
}

int writeFileUtil(const char* fileName, byte* data, long datasz)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, (char*)FILMODE_WRITE, DBTRUE);
    if(rscode == RSOK) {
        fwrite(data, sizeof(byte), datasz, f);
        fclose(f);
    }
    return rscode;
}

int readFileUtil(const char* fileName, byte** data, long* datasz)
{
    FILE* f = NULL;
    long numread;

    //printf("\nFileName: %s", fileName);
    int rscode = openFileUtil(&f, fileName, (char*)FILMODE_READ, DBTRUE);
    if(rscode == RSOK) {

        //printf("\nFileName: %s... OPENED_FOR_READ!", fileName);
        rscode = FILE_ACCESS_RESULT( fseek(f, 0L, SEEK_END) );
        if(rscode == RSOK) {
            //printf("\nFileName: %s... SEEK_TO_END!", fileName);
            (*datasz) = ftell(f);

            //printf("\nFileName: %s... Size: %ld", fileName, (*datasz));
            (*data) = (byte*)allocData(*datasz);
            if((*data) != NULL) {
                //printf("\nFileName: %s... Size: %ld... DATA_ALLOCATED!", fileName, (*datasz));
                rscode = FILE_ACCESS_RESULT( fseek(f, 0L, SEEK_SET) );
                if(rscode == RSOK) {
                    //printf("\nFileName: %s... Size: %ld... SEEK_TO_BEGIN!", fileName, (*datasz));

                    long pos = 0;
                    byte* p = & (*data)[pos];
                    while((numread = fread(p, sizeof(byte), BUFSZ, f)) > 0) {
                        pos += numread;
                        p = & (*data)[pos];
                    }
                    //printf("\nFileName: %s... Size: %ld... CurrPos: %ld... NumRead: %ld... EOF! ", fileName, (*datasz), pos, numread);
                }
            }
        }
        fclose(f);
    }
    return rscode;
}

/* ALLOC DATA OPERATIONS
 */

void* allocData(int dataSize)
{
    void* data = malloc(dataSize);
    errMsgIfNull(__HORUSSRV_MOD_UTIL_H, "allocData()", ERR_CANTALLOCATEMEMORY, data);
    return data;
}

void* allocDataArray(int dataSize, int numItens)
{
    int size = dataSize * numItens;
    void* data = malloc(size);
    errMsgIfNull(__HORUSSRV_MOD_UTIL_H, "allocDataArray()", ERR_CANTALLOCATEMEMORY, data);
    return data;
}

void freeData(void* data)
{
    if(data != NULL) {
        free(data);
        data = NULL;
    }
}

void freeDataArray(void* data)
{
    if(data != NULL) {
        free(data);
        data = NULL;
    }
}

/* HASH OPERATIONS
 */

long getHash(char* p)
{
    long hashVal = 0;

    long maxVal = 1000009;

    long q = 31;
    long q_memb = 1;

    while((*p) != '\0')
    {
        int c = (*p) - '@' + 1;

        hashVal = hashVal + ((c * q_memb) % maxVal);
        q_memb = (q_memb * q) % maxVal;
        p++;
    }
    return hashVal;
}

/* TIME OPERATIONS
 */

void getLocalTimeStr(char* local_time_str)
{
    time_t t = time(NULL);

    struct tm local_time = *localtime(&t);

    sprintf(local_time_str, 
            "%04d%02d%02d_%02d%02d%02d", 
            local_time.tm_year + 1900, 
            local_time.tm_mon + 1, 
            local_time.tm_mday, 
            local_time.tm_hour, 
            local_time.tm_min, 
            local_time.tm_sec);
}

long getCurrentTimestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}

/* GENERATE RANDOM OID
 */

long generateRandomOid()
{
    long rndVal = random() % 1000;

    long currTimestamp = getCurrentTimestamp();
    currTimestamp = (currTimestamp * 1000) + rndVal;
    return currTimestamp;
}

/* ENCODE/DECODE (HEX)
 */

int encodeHex(byte* in_data, long in_datasz, char** out_data, long* out_datalen)
{
    (*out_datalen) = (2 * in_datasz) + 1;
    (*out_data) = (char*)allocData( (*out_datalen) );

    byte* p_in = in_data;
    char* p_out = (*out_data);

    for(int i = 0; i < in_datasz; i++)
    {
        (*p_out) = ((*p_in) / 16) + 64;
        p_out++;

        (*p_out) = ((*p_in) % 16) + 64;
        p_out++;

        p_in++;
    }
    (*p_out) = '\0';

    return RSOK;
}

int decodeHex(char* in_data, long in_datalen, byte** out_data, long* out_datasz)
{
    long in_datasz = in_datalen - 1;

    (*out_datasz) = in_datasz / 2;
    if((in_datasz % 2) != 0)
        (*out_datasz) += 1;

    (*out_data) = (byte*)allocData( (*out_datasz) );

    char* p_in = in_data;
    byte* p_out = (*out_data);

    for(int i = 0; i < in_datasz; i += 2)
    {
        byte hb = ((*p_in) - 64) * 16;
        p_in++;

        byte lb = ((*p_in) - 64);
        p_in++;

        (*p_out) = hb + lb;
        p_out++;
    }

    return RSOK;
}

/* WAIT MESSAGE */

void showMessage(const char* str, long bWaitKey)
{
    if( (DEBUG_LEVEL == DEBUG_LEVEL_00) || (DEBUG_LEVEL == DEBUG_LEVEL_99) ) return;

    if(bWaitKey == DBTRUE) {
        printf("\n%s... press [ENTER] to continue.", str);
        while(getchar() != K_CR) {
            printf("\n%s... press [ENTER] to continue.", str);
        }
    }
    else {
        printf("\n%s... ", str);
    }
}

void showMessageAndWaitForKey(const char* str)
{
    printf("\n%s... press [ENTER] to continue.", str);
    while(getchar() != K_CR) {
        printf("\n%s... press [ENTER] to continue.", str);
    }
}
