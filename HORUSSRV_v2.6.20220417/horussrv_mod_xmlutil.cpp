/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_xmlutil.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

/* STRING XMLUTILS
 */
int xmlTokenUtil(char* ret_data, char* xmlData, char* iTagName, char* fTagName, int n)
{
    int len_iTagName = strlen(iTagName);
    int len_fTagName = strlen(fTagName);

    char* p = xmlData;
    while((*p) != '\0') {
        if(strNCmpCaseUtil(p, iTagName, len_iTagName, DEF_CASESENSITIVE_TOUPPER) == 0) {
            p += len_iTagName;
            
            char* q = ret_data;
            while((*p) != '\0') {
                (*q) = (*p);            
                q++;
                p++;

                if(strNCmpCaseUtil(p, fTagName, len_fTagName, DEF_CASESENSITIVE_TOUPPER) == 0) {
                    (*q) = '\0';
                    return RSOK;
                }
            }
            return RSERR;
        }
        p++;
    }
    return RSERR;
}

int xmlNodeUtil(char* ret_data, char* xmlData, char* tagName, int n)
{
    str_t iTagName;
    str_t fTagName;

    sprintf(iTagName, "<%s>", tagName);
    sprintf(fTagName, "</%s>", tagName);

    int rscode = xmlTokenUtil(ret_data, xmlData, iTagName, fTagName, n);
    return rscode;
}
