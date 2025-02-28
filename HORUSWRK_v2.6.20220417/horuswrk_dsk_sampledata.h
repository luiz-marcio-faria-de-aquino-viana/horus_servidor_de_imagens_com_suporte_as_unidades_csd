/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_sampledata.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 12/08/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_SAMPLEDATA_H
#define __HORUSWRK_DSK_SAMPLEDATA_H                 "__HORUSWRK_DSK_SAMPLEDATA_H"

/* default sample image directory
*/
#define DSK_IMAGE_DAT_SRCDIR            ((char*)"/home/lmarcio/101-UFRJ/999-Tese_Doutorado-Projeto_Horus-Luiz_Marcio_Faria_Aquino_Viana/HORUSWRK_v2.0/Data/U211/U211_DAT/tbl_imgrio/")
#define DSK_IMAGE_DAT_DSTDIR            ((char*)"/home/lmarcio/101-UFRJ/999-Tese_Doutorado-Projeto_Horus-Luiz_Marcio_Faria_Aquino_Viana/HORUSWRK_v2.0/Data/U211/U211_DAT/tbl_imgrio_temp/")

/* default sample remote directories
*/
#define DSK_IMAGE_DAT_DSTDIR_01         ((char*)"_DATASETS")        // _DATASETS
#define DSK_IMAGE_DAT_DSTDIR_01_01      ((char*)"IBGE-1_25000")     // _DATASETS/IBGE-1_25000
#define DSK_IMAGE_DAT_DSTDIR_01_01_01   ((char*)"Rio_de_Janeiro")   // _DATASETS/IBGE-1_25000/Rio_de_Janeiro
#define DSK_IMAGE_DAT_DSTDIR_01_01_02   ((char*)"Sao_Paulo")        // _DATASETS/IBGE-1_25000/Sao_Paulo
#define DSK_IMAGE_DAT_DSTDIR_01_01_03   ((char*)"Belo_Horizonte")   // _DATASETS/IBGE-1_25000/Belo_Horizonte

/* number of image files
 */
#define DSK_NUMOFIMAGES                 17

#define DSK_NUMOFIMAGES_IN_DEBUGMODE    5

/* sample image files
 */
#define DSK_IMAGE_DAT_FILE_01           ((char*)"ofm_rj25_26124se_v1.tif")
#define DSK_IMAGE_DAT_FILE_02           ((char*)"ofm_rj25_26124so_v1.tif")
#define DSK_IMAGE_DAT_FILE_03           ((char*)"ofm_rj25_26133ne_v1.tif")
#define DSK_IMAGE_DAT_FILE_04           ((char*)"ofm_rj25_26133no_v1.tif")
#define DSK_IMAGE_DAT_FILE_05           ((char*)"ofm_rj25_26133se_v1.tif")
#define DSK_IMAGE_DAT_FILE_06           ((char*)"ofm_rj25_26133so_v1.tif")
#define DSK_IMAGE_DAT_FILE_07           ((char*)"ofm_rj25_26134no_v1.tif")
#define DSK_IMAGE_DAT_FILE_08           ((char*)"ofm_rj25_26134so_v1.tif")
#define DSK_IMAGE_DAT_FILE_09           ((char*)"ofm_rj25_26482ne_v1.tif")
#define DSK_IMAGE_DAT_FILE_10           ((char*)"ofm_rj25_26482no_v1.tif")
#define DSK_IMAGE_DAT_FILE_11           ((char*)"ofm_rj25_26482se_v1.tif")
#define DSK_IMAGE_DAT_FILE_12           ((char*)"ofm_rj25_26482so_v1.tif")
#define DSK_IMAGE_DAT_FILE_13           ((char*)"ofm_rj25_26483se_v1.tif")
#define DSK_IMAGE_DAT_FILE_14           ((char*)"ofm_rj25_26484ne_v1.tif")
#define DSK_IMAGE_DAT_FILE_15           ((char*)"ofm_rj25_26484no_v1.tif")
#define DSK_IMAGE_DAT_FILE_16           ((char*)"ofm_rj25_26484se_v1.tif")
#define DSK_IMAGE_DAT_FILE_17           ((char*)"ofm_rj25_26484so_v1.tif")

/* array of sample image files
 */
extern const char* ARR_DSK_IMAGE_DAT_FILES[];

#endif
