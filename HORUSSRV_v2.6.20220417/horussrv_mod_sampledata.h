/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_sampledata.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/05/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_SAMPLEDATA_H
#define __HORUSSRV_MOD_SAMPLEDATA_H          "__HORUSSRV_MOD_SAMPLEDATA_H"

/* sample sequences
 */
//IMGRIO
#define SEQ_IMGRIO_OID                              ((long)111L)
#define SEQ_IMGRIO                                  "SEQ_IMGRIO"
//PATSAND
#define SEQ_PATSAND_OID                             ((long)112L)
#define SEQ_PATSAND                                 "SEQ_PATSAND"
//PATGRASS
#define SEQ_PATGRASS_OID                            ((long)113L)
#define SEQ_PATGRASS                                "SEQ_PATGRASS"
//PATEARTH
#define SEQ_PATEARTH_OID                            ((long)114L)
#define SEQ_PATEARTH                                "SEQ_PATEARTH"
//PATWATTER
#define SEQ_PATWATTER_OID                           ((long)115L)
#define SEQ_PATWATTER                               "SEQ_PATWATTER"
//PATPARCEL
#define SEQ_PATPARCEL_OID                           ((long)116L)
#define SEQ_PATPARCEL                               "SEQ_PATPARCEL"

/* sample users
 */
//LMARCIO - TEST USER (AUTOR: LUIZ MARCIO FARIA DE AQUINO VIANA, M.SC.)
#define USR_LMARCIO_UID                     ((long)2L)
#define USR_LMARCIO_UTYPE                   UTYPE_SYSTEM             
#define USR_LMARCIO_USERNAME                "LMARCIO"
#define USR_LMARCIO_PASSWD                  "LMARCIO"
//FELIPE - TEST USER (ORIENTADOR: FELIPE FRANÇA, Ph.D.)
#define USR_FELIPE_UID                      ((long)3L)
#define USR_FELIPE_UTYPE                    UTYPE_SYSTEM             
#define USR_FELIPE_USERNAME                 "FELIPE"
#define USR_FELIPE_PASSWD                   "FELIPE"
//DIEGO - TEST USER (ORIENTADOR: DIEGO, D.Sc.)
#define USR_DIEGO_UID                       ((long)4L)
#define USR_DIEGO_UTYPE                     UTYPE_SYSTEM             
#define USR_DIEGO_USERNAME                  "DIEGO"
#define USR_DIEGO_PASSWD                    "DIEGO"
//TIAGO - TEST USER (ORIENTADOR: TIAGO, D.Sc.)
#define USR_TIAGO_UID                       ((long)5L)
#define USR_TIAGO_UTYPE                     UTYPE_SYSTEM             
#define USR_TIAGO_USERNAME                  "TIAGO"
#define USR_TIAGO_PASSWD                    "TIAGO"

/* sample table metadata
 */
//TABLE: IMGRIO
#define TBLMETA_IMGRIO_OID                 ((long)301L)
#define TBLMETA_IMGRIO_TBLSPC_OID_0        ((long)201L)
#define TBLMETA_IMGRIO_TBLSPC_OID_1        ((long)211L)
#define TBLMETA_IMGRIO_TBLSPC_OID_2        ((long)212L)
#define TBLMETA_IMGRIO_TBLSPC_OID_3        ((long)213L)
#define TBLMETA_IMGRIO_TBLSPC_OID_4        ((long)214L)
#define TBLMETA_IMGRIO_TBLSPC_OID_5        ((long)215L)
#define TBLMETA_IMGRIO_NUM_TBLSPC          ((long)6L)
#define TBLMETA_IMGRIO_UID                 ((long)1L)
#define TBLMETA_IMGRIO_TBTYPE              ((long)2L)
#define TBLMETA_IMGRIO_MODNAME             "\0"
#define TBLMETA_IMGRIO_REF_TABLE_OID       ((long)LONG_MIN)    
#define TBLMETA_IMGRIO_TABLE_NAME          "tbl_imgrio"
#define TBLMETA_IMGRIO_TABLE_FILENAME      "tbl_imgrio.dat"
#define TBLMETA_IMGRIO_IDX1_NAME           "ix1_imgrio"
#define TBLMETA_IMGRIO_IDX1_FILENAME       "ix1_imgrio.idx"
#define TBLMETA_IMGRIO_IDX2_NAME           "ix2_imgrio"
#define TBLMETA_IMGRIO_IDX2_FILENAME       "ix2_imgrio.idx"
#define TBLMETA_IMGRIO_SEQ_NAME            "SEQ_IMGRIO"
//TABLE: PATSAND
#define TBLMETA_PATSAND_OID                ((long)311L)
#define TBLMETA_PATSAND_TBLSPC_OID_0       ((long)201L)
#define TBLMETA_PATSAND_TBLSPC_OID_1       ((long)211L)
#define TBLMETA_PATSAND_TBLSPC_OID_2       ((long)212L)
#define TBLMETA_PATSAND_TBLSPC_OID_3       ((long)213L)
#define TBLMETA_PATSAND_TBLSPC_OID_4       ((long)214L)
#define TBLMETA_PATSAND_TBLSPC_OID_5       ((long)215L)
#define TBLMETA_PATSAND_NUM_TBLSPC         ((long)6L)
#define TBLMETA_PATSAND_UID                ((long)1L)
#define TBLMETA_PATSAND_TBTYPE             ((long)1L)
#define TBLMETA_PATSAND_MODNAME            "patsand_mod"
#define TBLMETA_PATSAND_REF_TABLE_OID      ((long)301L)    
#define TBLMETA_PATSAND_TABLE_NAME         "tbl_patsand"
#define TBLMETA_PATSAND_TABLE_FILENAME     "tbl_patsand.dat"
#define TBLMETA_PATSAND_IDX1_NAME          "ix1_patsand"
#define TBLMETA_PATSAND_IDX1_FILENAME      "ix1_patsand.idx"
#define TBLMETA_PATSAND_IDX2_NAME          "ix2_patsand"
#define TBLMETA_PATSAND_IDX2_FILENAME      "ix2_patsand.idx"
#define TBLMETA_PATSAND_SEQ_NAME           "SEQ_PATSAND"
//TABLE: PATGRASS
#define TBLMETA_PATGRASS_OID               ((long)312L)
#define TBLMETA_PATGRASS_TBLSPC_OID_0      ((long)201L)
#define TBLMETA_PATGRASS_TBLSPC_OID_1      ((long)211L)
#define TBLMETA_PATGRASS_TBLSPC_OID_2      ((long)212L)
#define TBLMETA_PATGRASS_TBLSPC_OID_3      ((long)213L)
#define TBLMETA_PATGRASS_TBLSPC_OID_4      ((long)214L)
#define TBLMETA_PATGRASS_TBLSPC_OID_5      ((long)215L)
#define TBLMETA_PATGRASS_NUM_TBLSPC        ((long)6L)
#define TBLMETA_PATGRASS_UID               ((long)1L)
#define TBLMETA_PATGRASS_TBTYPE            ((long)1L)
#define TBLMETA_PATGRASS_MODNAME           "patgrass_mod"
#define TBLMETA_PATGRASS_REF_TABLE_OID     ((long)301L)    
#define TBLMETA_PATGRASS_TABLE_NAME        "tbl_patgrass"
#define TBLMETA_PATGRASS_TABLE_FILENAME    "tbl_patgrass.dat"
#define TBLMETA_PATGRASS_IDX1_NAME         "ix1_patgrass"
#define TBLMETA_PATGRASS_IDX1_FILENAME     "ix1_patgrass.idx"
#define TBLMETA_PATGRASS_IDX2_NAME         "ix2_patgrass"
#define TBLMETA_PATGRASS_IDX2_FILENAME     "ix2_patgrass.idx"
#define TBLMETA_PATGRASS_SEQ_NAME          "SEQ_PATGRASS"
//TABLE: PATEARTH
#define TBLMETA_PATEARTH_OID               ((long)313L)
#define TBLMETA_PATEARTH_TBLSPC_OID_0      ((long)201L)
#define TBLMETA_PATEARTH_TBLSPC_OID_1      ((long)211L)
#define TBLMETA_PATEARTH_TBLSPC_OID_2      ((long)212L)
#define TBLMETA_PATEARTH_TBLSPC_OID_3      ((long)213L)
#define TBLMETA_PATEARTH_TBLSPC_OID_4      ((long)214L)
#define TBLMETA_PATEARTH_TBLSPC_OID_5      ((long)215L)
#define TBLMETA_PATEARTH_NUM_TBLSPC        ((long)6L)
#define TBLMETA_PATEARTH_UID               ((long)1L)
#define TBLMETA_PATEARTH_TBTYPE            ((long)1L)
#define TBLMETA_PATEARTH_MODNAME           "patearth_mod"
#define TBLMETA_PATEARTH_REF_TABLE_OID     ((long)301L)    
#define TBLMETA_PATEARTH_TABLE_NAME        "tbl_patearth"
#define TBLMETA_PATEARTH_TABLE_FILENAME    "tbl_patearth.dat"
#define TBLMETA_PATEARTH_IDX1_NAME         "ix1_patearth"
#define TBLMETA_PATEARTH_IDX1_FILENAME     "ix1_patearth.idx"
#define TBLMETA_PATEARTH_IDX2_NAME         "ix2_patearth"
#define TBLMETA_PATEARTH_IDX2_FILENAME     "ix2_patearth.idx"
#define TBLMETA_PATEARTH_SEQ_NAME          "SEQ_PATEARTH"
//TABLE: PATWATTER
#define TBLMETA_PATWATTER_OID              ((long)314L)
#define TBLMETA_PATWATTER_TBLSPC_OID_0     ((long)201L)
#define TBLMETA_PATWATTER_TBLSPC_OID_1     ((long)211L)
#define TBLMETA_PATWATTER_TBLSPC_OID_2     ((long)212L)
#define TBLMETA_PATWATTER_TBLSPC_OID_3     ((long)213L)
#define TBLMETA_PATWATTER_TBLSPC_OID_4     ((long)214L)
#define TBLMETA_PATWATTER_TBLSPC_OID_5     ((long)215L)
#define TBLMETA_PATWATTER_NUM_TBLSPC       ((long)6L)
#define TBLMETA_PATWATTER_UID              ((long)1L)
#define TBLMETA_PATWATTER_TBTYPE           ((long)1L)
#define TBLMETA_PATWATTER_MODNAME          "patwatter_mod"
#define TBLMETA_PATWATTER_REF_TABLE_OID    ((long)301L)    
#define TBLMETA_PATWATTER_TABLE_NAME       "tbl_patwatter"
#define TBLMETA_PATWATTER_TABLE_FILENAME   "tbl_patwatter.dat"
#define TBLMETA_PATWATTER_IDX1_NAME        "ix1_patwatter"
#define TBLMETA_PATWATTER_IDX1_FILENAME    "ix1_patwatter.idx"
#define TBLMETA_PATWATTER_IDX2_NAME        "ix2_patwatter"
#define TBLMETA_PATWATTER_IDX2_FILENAME    "ix2_patwatter.idx"
#define TBLMETA_PATWATTER_SEQ_NAME         "SEQ_PATWATTER"
//TABLE: PATPARCEL
#define TBLMETA_PATPARCEL_OID              ((long)315L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_0     ((long)201L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_1     ((long)211L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_2     ((long)212L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_3     ((long)213L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_4     ((long)214L)
#define TBLMETA_PATPARCEL_TBLSPC_OID_5     ((long)215L)
#define TBLMETA_PATPARCEL_NUM_TBLSPC       ((long)6L)
#define TBLMETA_PATPARCEL_UID              ((long)1L)
#define TBLMETA_PATPARCEL_TBTYPE           ((long)1L)
#define TBLMETA_PATPARCEL_MODNAME          "patparcel_mod"
#define TBLMETA_PATPARCEL_REF_TABLE_OID    ((long)301L)    
#define TBLMETA_PATPARCEL_TABLE_NAME       "tbl_patparcel"
#define TBLMETA_PATPARCEL_TABLE_FILENAME   "tbl_patparcel.dat"
#define TBLMETA_PATPARCEL_IDX1_NAME        "ix1_patparcel"
#define TBLMETA_PATPARCEL_IDX1_FILENAME    "ix1_patparcel.idx"
#define TBLMETA_PATPARCEL_IDX2_NAME        "ix2_patparcel"
#define TBLMETA_PATPARCEL_IDX2_FILENAME    "ix2_patparcel.idx"
#define TBLMETA_PATPARCEL_SEQ_NAME         "SEQ_PATPARCEL"

#endif
