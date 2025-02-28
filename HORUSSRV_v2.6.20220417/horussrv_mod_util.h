/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_util.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 16/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_UTIL_H
#define __HORUSSRV_MOD_UTIL_H                            "__HORUSSRV_MOD_UTIL_H"

/* STRING UTILS
 */

int strIsEmptyUtil(char* src);

char* strSetEmptyUtil(char* src);

int strLenUtil(char* src, int n);

int strCharCountUtil(char* src, int n, char c);

char* strPiece(char* inPath, int inPathSz, char* outPath, int outPathSz, char c, int n);

char* strNCpyCaseUtil(char* dst, char* src, int n, int caseSensitive);

char* strNCpyUtil(char* dst, char* src, int n);

char* strNCatUtil(char* dst, char* src, int n);

int strNCmpUtil(char* src1, char* src2, int n);                             // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

int strNCmpCaseUtil(char* src1, char* src2, int n, int caseSensitive);      // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

char* strRemoveEolUtil(char* src, int n);

/* MEM UTILS
 */

int memIsNullUtil(byte* src, int n);

byte* memSetNullUtil(byte* src, int n);

byte* memNCpyUtil(byte* dst, byte* src, int n);

byte* memNCatUtil(byte* dst, byte* src, int pos, int n);

int memNCmpUtil(byte* src1, byte* src2, int n);     // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

/* FILE NAME AND PATH OPERATIONS
 */

char* getFileName(char* inFileName, int inFileNameSz, char* outFileName, int outFileNameSz);

char* getFileNameWithoutExt(char* inFileName, int inFileNameSz, char* outFileName, int outFileNameSz);

char* getFileExt(char* inFileName, int inFileNameSz, char* outFileExt, int outFileExtSz);

int getPathLen(char* inPath, int inPathSz);

char* getPathAt(char* inPath, int inPathSz, char* outPath, int outPathSz, int n);

/* FILE OPERATIONS
 */

int existFileUtil(const char* fileName);

int openFileUtil(FILE** f, const char* fileName, const char* fileMode, long bSeekBegin);

int writeFileUtil(const char* fileName, byte* data, long datasz);

int readFileUtil(const char* fileName, byte** data, long* datasz);

/* ALLOC DATA OPERATIONS
 */
 
void* allocData(int dataSize);

void* allocDataArray(int dataSize, int numItens);

void freeData(void* data);

void freeDataArray(void* data);

/* HASH OPERATIONS
 */

long getHash(char* s);

/* TIME OPERATIONS
 */

void getLocalTimeStr(char* local_time_str);

long getCurrentTimestamp();

/* GENERATE RANDOM OID
 */

long generateRandomOid();

/* ENCODE/DECODE (HEX)
 */

int encodeHex(byte* in_data, long in_datasz, char** out_data, long* out_datalen);

int decodeHex(char* in_data, long in_datalen, byte** out_data, long* out_datasz);

/* WAIT MESSAGE */

void showMessage(const char* str, long bWaitKey);

void showMessageAndWaitForKey(const char* str);

#endif
