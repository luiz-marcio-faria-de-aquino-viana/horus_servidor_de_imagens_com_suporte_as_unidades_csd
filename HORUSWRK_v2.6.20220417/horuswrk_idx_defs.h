/*
 * Copyright (C) 2022 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_idx_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/02/2022
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_IDX_DEFS_H
#define __HORUSWRK_IDX_DEFS_H                   "__HORUSWRK_IDX_DEFS_H"

/* NULL KEY DEFINITIONS
*/
#define DEF_IDX_NULLKEY_LNG                     -1 
#define DEF_IDX_NULLKEY_DBL                     -1.0 
#define DEF_IDX_NULLKEY_STR                     ((char*)"-1") 

/* ENTRY COMPARATOR
*/
#define DEF_IDX_COMPENTRY_BEFORE                -1 
#define DEF_IDX_COMPENTRY_EQUAL                 0 
#define DEF_IDX_COMPENTRY_AFTER                 1 

/* DOUBLE KEY ENTRY PRECISION
*/
#define DEF_IDX_COMPENTRY_PREC                  0.0001

/* ENTRY IDENTIFY SEQUENCE
*/
#define DEF_IDX_SEQ_INIT_ENTRYID                100000001 

/* KEY TYPE DEFINITIONS 
*/
#define DEF_IDX_KEYLNG                          1001
#define DEF_IDX_KEYDBL                          1002
#define DEF_IDX_KEYSTR                          1003

/* INSERT ORDER DEFINITIONS 
*/
#define DEF_IDX_KEYORDER_NONE                   2001
#define DEF_IDX_KEYORDER_CRESCENT               2002
#define DEF_IDX_KEYORDER_DECRESCENT             2003

/* TREE SEARCH TYPE 
*/
#define DEF_IDX_TREESEARCHTYPE_WIDESEARCH       1
#define DEF_IDX_TREESEARCHTYPE_DEEPSEARCH       2

#endif
