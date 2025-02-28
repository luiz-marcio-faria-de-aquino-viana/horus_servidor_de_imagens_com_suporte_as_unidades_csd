/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_xmlutil.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_mod_all.h"

/* STRING XMLUTILS
 */
int xmlTokenUtil(char* ret_data, char* xmlData, char* iTagName, char* fTagName, int n);

int xmlNodeUtil(char* ret_data, char* xmlData, char* tagName, int n);
