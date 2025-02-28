/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cfg_configtag.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 27/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CCfgConfigTag::CCfgConfigTag()
{
    init(DEF_TAGQTY_MAXNUMTAGS, NULL);
}

CCfgConfigTag::~CCfgConfigTag()
{
    terminate();
}

/* Methodes */

void CCfgConfigTag::init(int maxNumConfigTags, char* cfgfile)
{
    m_arrConfigTags = (config_tag_t*)allocDataArray(sizeof(config_tag_t), maxNumConfigTags);
    m_maxNumConfigTags = maxNumConfigTags; 
    m_currNumConfigTags = 0; 

    buildConfigTags();

    if(cfgfile != NULL)
        loadConfigTagsValue(cfgfile);
}

void CCfgConfigTag::terminate()
{
    freeDataArray(m_arrConfigTags);
}

void CCfgConfigTag::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    for(int i = 0; i < m_currNumConfigTags; i++) {
        config_tag_t* p = & m_arrConfigTags[i];
        debugEntry(debugLevel, className, methodName, p);
    }
}

void CCfgConfigTag::debugEntry(int debugLevel, const char* className, const char* methodName, config_tag_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg, 
        "* ConfigTag: Id=%ld,Name=%s,Value=%s\n", 
        p->tag_id,
        p->tag_name,
        p->tag_value);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Config Tags */

config_tag_t* CCfgConfigTag::addNewConfigTag(int n, int tagId, char* tagName)
{
    config_tag_t* p = & m_arrConfigTags[n];
    strNCpyCaseUtil(p->tag_name, tagName, BIGSTRSZ, DEF_CASESENSITIVE_TOUPPER);
    strSetEmptyUtil(p->tag_value);
    p->tag_id = tagId;

    debugEntry(DEBUG_LEVEL_03, __HORUSWRK_CFG_CONFIG_H, "addNewConfigTag()", p);
    return p;
}

config_tag_t* CCfgConfigTag::setConfigTagValue(char* tagName, char* tagValue)
{
    for(long i = 0; i < m_currNumConfigTags; i++) {
        config_tag_t* p = & m_arrConfigTags[i];
        if( strNCmpCaseUtil(p->tag_name, tagName, BIGSTRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 ) {
            strNCpyUtil(p->tag_value, tagValue, BIGSTRSZ);       

            debugEntry(DEBUG_LEVEL_03, __HORUSWRK_CFG_CONFIG_H, "setConfigTagValue()", p);
            return p;
        }
    }
    return NULL;
}

config_tag_t* CCfgConfigTag::findConfigTagByOid(long tagId) 
{
    for(long i = 0; i < m_currNumConfigTags; i++) {
        config_tag_t* p = & m_arrConfigTags[i];
        if(p->tag_id == tagId)
            return p;
    }
    return NULL;
}

config_tag_t* CCfgConfigTag::findConfigTagByName(char* tagName) 
{
    for(long i = 0; i < m_currNumConfigTags; i++) {
        config_tag_t* p = & m_arrConfigTags[i];
        if( strNCmpCaseUtil(p->tag_name, tagName, BIGSTRSZ, DEF_CASESENSITIVE_TOUPPER) == 0 )
            return p;
    }
    return NULL;
}

void CCfgConfigTag::buildConfigTags()
{
    long tagId = 1;
    long n = 0;

    bigstr_t strTmp;

    //CURR_REMOTEUNIT
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_CURRENT_REMOTEUNIT_OID);

    //HOSTSERVER
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_OID);
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_NAME);
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_IPADDR);
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_IN_PORT);
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_OUT_PORT);
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_HOSTSERVER_KEY);

    //REMOTEUNITS
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_NUMOFREMOTEUNITS);

    //REMOTEUNIT
    for(int i = 0; i < DEF_TAGQTY_REMOTEUNITS; i++) {
        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_OID, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_NAME, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_IPADDR, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_IN_PORT, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_OUT_PORT, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_TBLSPCNAME, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_ENABLED, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_KEY, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_WORKNODE, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_NAMENODE, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_REMOTEUNIT_DATANODE, i);
        addNewConfigTag(n++, tagId++, strTmp);
    }

    //MODULES
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_NUMOFMODULES);

    //MODULE
    for(int i = 0; i < DEF_TAGQTY_MODULES; i++) {
        sprintf(strTmp, (char*)DEF_TAGTXT_MODULE_OID, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_MODULE_NAME, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_MODULE_FILE_NAME, i);
        addNewConfigTag(n++, tagId++, strTmp);

        //PARAMETERS
        sprintf(strTmp, (char*)DEF_TAGTXT_NUMOFPARAMS, i);
        addNewConfigTag(n++, tagId++, strTmp);

        //PARAMETER
        for(int j = 0; j < DEF_TAGQTY_PARAMS_PER_MODULE; j++) {
            sprintf(strTmp, (char*)DEF_TAGTXT_PARAM_NAME, i, j);
            addNewConfigTag(n++, tagId++, strTmp);

            sprintf(strTmp, (char*)DEF_TAGTXT_PARAM_VALUE, i, j);
            addNewConfigTag(n++, tagId++, strTmp);

            sprintf(strTmp, (char*)DEF_TAGTXT_PARAM_MODE, i, j);
            addNewConfigTag(n++, tagId++, strTmp);

        }

    }

    //DISKGROUPS
    addNewConfigTag(n++, tagId++, (char*)DEF_TAGTXT_NUMOFDISKGROUPS);

    //DISKGROUP
    for(int i = 0; i < DEF_TAGQTY_DISKGROUPS; i++) {
        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_OID, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_NAME, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_REMOTEUNIT_OID, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_NUMOFDISKS, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_NUMOFCOPIES, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_NUMBEROFSUPERBLOCKS, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_NUMBEROFBLOCKS, i);
        addNewConfigTag(n++, tagId++, strTmp);

        sprintf(strTmp, (char*)DEF_TAGTXT_DISKGROUP_BLOCKSIZE, i);
        addNewConfigTag(n++, tagId++, strTmp);

        //DISKDEVICE
        for(int j = 0; j < DEF_TAGQTY_DISKDEV_PER_DISKGROUP; j++) {
            sprintf(strTmp, (char*)DEF_TAGTXT_DISKDEV_OID, i, j);
            addNewConfigTag(n++, tagId++, strTmp);

            sprintf(strTmp, (char*)DEF_TAGTXT_DISKDEV_NAME, i, j);
            addNewConfigTag(n++, tagId++, strTmp);

            sprintf(strTmp, (char*)DEF_TAGTXT_DISKDEV_REMOTEUNIT_OID, i, j);
            addNewConfigTag(n++, tagId++, strTmp);
            
        }

    }

    m_currNumConfigTags = n;
}

void CCfgConfigTag::loadConfigTagsValue(char* cfgfile)
{
    FILE* f = NULL;
    bigstr_t sbuf;

    bigstr_t tagName;
    bigstr_t tagValue;

    char* tk = NULL;

    sbigstr_t errmsg;

    int rscode = openFileUtil(&f, cfgfile, (char*)FILMODE_READ_ASCII, DBFALSE);
    if(rscode == RSOK)
    {
        long rowNum = 0;
        while(fgets(sbuf, BIGSTRSZ, f) != NULL) {
            sbuf[BIGSTRSZ - 1] = '\0';
            strRemoveEolUtil(sbuf, BIGSTRSZ);

            if(sbuf[0] == '#') continue;

            tk = strtok(sbuf, "=");
            if(tk != NULL) {
                strNCpyUtil(tagName, tk, BIGSTRSZ);

                sprintf(errmsg, "* Token: RowNum=%ld,RowStr=%s,ParamName=%s\n", rowNum, sbuf, tagName);
                warnMsg(DEBUG_LEVEL_03, __HORUSWRK_CFG_CONFIG_H, "loadConfigTagsValue()", errmsg);

                tk = strtok(NULL, "=");
                if(tk != NULL) {
                    strNCpyUtil(tagValue, tk, STRSZ);

                    sprintf(errmsg, "* Token: RowNum=%ld,RowStr=%s,ParamName=%s,ParamValue=%s\n", rowNum, sbuf, tagName, tagValue);
                    warnMsg(DEBUG_LEVEL_03, __HORUSWRK_CFG_CONFIG_H, "loadConfigTagsValue()", errmsg);

                    setConfigTagValue(tagName, tagValue);
                }
            } 
            rowNum++;
        }
        fclose(f);
    }
}

/* Getters/Settes */

config_tag_t* CCfgConfigTag::getConfigTagAt(int pos)
{
    config_tag_t* p = NULL;
    if(pos < m_currNumConfigTags)
        p = & m_arrConfigTags[pos];
    return p;
}

int CCfgConfigTag::getMaxNumConfigTags()
{
    return m_maxNumConfigTags;
}

int CCfgConfigTag::getCurrNumConfigTags()
{
    return m_currNumConfigTags;
}
