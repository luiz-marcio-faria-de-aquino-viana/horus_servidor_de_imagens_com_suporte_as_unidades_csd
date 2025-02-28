/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_configtag.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CFG_CONFIGTAG_H
#define __HORUSWRK_CFG_CONFIGTAG_H              "__HORUSWRK_CFG_CONFIGTAG_H"

class CCfgConfigTag
{
private:
    config_tag_t* m_arrConfigTags;
    int m_maxNumConfigTags; 
    int m_currNumConfigTags; 

public:
    CCfgConfigTag();
    ~CCfgConfigTag();

    /* Methodes */

    void init(int maxNumConfigTags, char* cfgfile);

    void terminate();

    void debug(int debugLevel, const char* className, const char* methodName);

    void debugEntry(int debugLevel, const char* className, const char* methodName, config_tag_t* p);

    /* Config Tags */

    config_tag_t* addNewConfigTag(int n, int tagId, char* tagName);
    
    config_tag_t* setConfigTagValue(char* tagName, char* tagValue);

    config_tag_t* findConfigTagByOid(long tagId);

    config_tag_t* findConfigTagByName(char* tagName);

    void buildConfigTags();

    void loadConfigTagsValue(char* cfgfile);

    /* Getters/Settes */

    config_tag_t* getConfigTagAt(int pos);

    int getMaxNumConfigTags();

    int getCurrNumConfigTags(); 

};

/* NEW_TYPE: CCfgConfigTag Pointer */

typedef CCfgConfigTag* CCfgConfigTagPtr_t;

#endif
