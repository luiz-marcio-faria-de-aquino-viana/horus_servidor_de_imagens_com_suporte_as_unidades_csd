/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_cfg_remoteunit.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 28/02/2021
 * revisoes: ...
 *
 */

#include"horussrv_base_all.h"

CCfgRemoteUnit::CCfgRemoteUnit()
{
    init();
}
    
CCfgRemoteUnit::~CCfgRemoteUnit()
{
    terminate();
}

/* Methodes */

void CCfgRemoteUnit::initDefaults()
{
    strNCpyUtil(m_name, (char*)DEF_DEFAULT_REMOTEUNIT_NAME_1, BIGSTRSZ);
    strNCpyUtil(m_ipAddr, (char*)DEF_DEFAULT_REMOTEUNIT_IPADDR_1, BIGSTRSZ);
    strNCpyUtil(m_tblSpcName, (char*)DEF_DEFAULT_REMOTEUNIT_TBLSPCNAME_1, BIGSTRSZ);
    strNCpyUtil(m_key, (char*)DEF_DEFAULT_REMOTEUNIT_KEY_1, BIGSTRSZ);

    m_oid = DEF_DEFAULT_REMOTEUNIT_OID_1;
    m_inPort = DEF_DEFAULT_REMOTEUNIT_IN_PORT_1;
    m_outPort = DEF_DEFAULT_REMOTEUNIT_OUT_PORT_1;
    m_enabled = DEF_DEFAULT_REMOTEUNIT_ENABLE_1;
    m_workNode = DEF_DEFAULT_REMOTEUNIT_WORKNODE_1;
    m_nameNode = DEF_DEFAULT_REMOTEUNIT_NAMENODE_1;
    m_dataNode = DEF_DEFAULT_REMOTEUNIT_DATANODE_1;
}

void CCfgRemoteUnit::init()
{
    initDefaults();    
}

void CCfgRemoteUnit::terminate()
{
    /* nothing todo! */
}

void CCfgRemoteUnit::loadConfig(int posRemoteUnit, CCfgConfigTag* pConfigTag)
{
    bigstr_t tagOid;
    bigstr_t tagName;
    bigstr_t tagIpAddr;
    bigstr_t tagTblSpcName;
    bigstr_t tagKey;
    bigstr_t tagInPort;
    bigstr_t tagOutPort;
    bigstr_t tagEnabled;
    bigstr_t tagWorkNode;
    bigstr_t tagNameNode;
    bigstr_t tagDataNode;

    sprintf(tagOid, DEF_TAGTXT_REMOTEUNIT_OID, posRemoteUnit);
    sprintf(tagName, DEF_TAGTXT_REMOTEUNIT_NAME, posRemoteUnit);
    sprintf(tagIpAddr, DEF_TAGTXT_REMOTEUNIT_IPADDR, posRemoteUnit);
    sprintf(tagTblSpcName, DEF_TAGTXT_REMOTEUNIT_TBLSPCNAME, posRemoteUnit);
    sprintf(tagKey, DEF_TAGTXT_REMOTEUNIT_KEY, posRemoteUnit);
    sprintf(tagInPort, DEF_TAGTXT_REMOTEUNIT_IN_PORT, posRemoteUnit);
    sprintf(tagOutPort, DEF_TAGTXT_REMOTEUNIT_OUT_PORT, posRemoteUnit);
    sprintf(tagEnabled, DEF_TAGTXT_REMOTEUNIT_ENABLED, posRemoteUnit);
    sprintf(tagWorkNode, DEF_TAGTXT_REMOTEUNIT_WORKNODE, posRemoteUnit);
    sprintf(tagNameNode, DEF_TAGTXT_REMOTEUNIT_NAMENODE, posRemoteUnit);
    sprintf(tagDataNode, DEF_TAGTXT_REMOTEUNIT_DATANODE, posRemoteUnit);

    //REMOTEUNIT
    config_tag_t* p = pConfigTag->findConfigTagByName(tagOid);
    if(p != NULL)
        m_oid = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagName);
    if(p != NULL)
        strNCpyUtil(m_name, p->tag_value, BIGSTRSZ);

    p = pConfigTag->findConfigTagByName(tagIpAddr);
    if(p != NULL)
        strNCpyUtil(m_ipAddr, p->tag_value, BIGSTRSZ);

    p = pConfigTag->findConfigTagByName(tagTblSpcName);
    if(p != NULL)
        strNCpyUtil(m_tblSpcName, p->tag_value, BIGSTRSZ);

    p = pConfigTag->findConfigTagByName(tagKey);
    if(p != NULL)
        strNCpyUtil(m_key, p->tag_value, BIGSTRSZ);

    p = pConfigTag->findConfigTagByName(tagInPort);
    if(p != NULL)
        m_inPort = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagOutPort);
    if(p != NULL)
        m_outPort = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagEnabled);
    if(p != NULL)
        m_enabled = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagWorkNode);
    if(p != NULL)
        m_workNode = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagNameNode);
    if(p != NULL)
        m_nameNode = atol(p->tag_value);

    p = pConfigTag->findConfigTagByName(tagDataNode);
    if(p != NULL)
        m_dataNode = atol(p->tag_value);

}

void CCfgRemoteUnit::setData(CCfgRemoteUnit* pRemoteUnit)
{
    strNCpyUtil(m_name, (char*)pRemoteUnit->getName(), BIGSTRSZ);
    strNCpyUtil(m_ipAddr, (char*)pRemoteUnit->getIpAddr(), BIGSTRSZ);
    strNCpyUtil(m_tblSpcName, (char*)pRemoteUnit->getTblSpcName(), BIGSTRSZ);
    strNCpyUtil(m_key, (char*)pRemoteUnit->getKey(), BIGSTRSZ);

    m_oid = pRemoteUnit->getOid();
    m_inPort = pRemoteUnit->getInPort();
    m_outPort = pRemoteUnit->getOutPort();
    m_enabled = pRemoteUnit->getEnabled();
    m_workNode = pRemoteUnit->getWorkNode();
    m_nameNode = pRemoteUnit->getNameNode();
    m_dataNode = pRemoteUnit->getDataNode();
}

void CCfgRemoteUnit::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    sbigstr_t errmsg;
    sprintf(
        errmsg,
        "\nCCfgRemoteUnit::Oid=%ld,Name:%s,IpAddr=%s,TblSpcName=%s,Key=%s,InPort=%ld,OutPort=%ld,Enabled=%ld,WorkNode=%ld,NameNode=%ld,DataNode=%ld\n",
        m_oid,
        m_name, 
        m_ipAddr, 
        m_tblSpcName, 
        m_key, 
        m_inPort,
        m_outPort,
        m_enabled,
        m_workNode,
        m_nameNode,
        m_dataNode);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Settes */

long CCfgRemoteUnit::getOid()
{
    return m_oid;
}

char* CCfgRemoteUnit::getName()
{
    return m_name;
}

char* CCfgRemoteUnit::getIpAddr()
{
    return m_ipAddr;
}

long CCfgRemoteUnit::getInPort()
{
    return m_inPort;
}

long CCfgRemoteUnit::getOutPort()
{
    return m_outPort;
}

char* CCfgRemoteUnit::getTblSpcName()
{
    return m_tblSpcName;
}

long CCfgRemoteUnit::getEnabled()
{
    return m_enabled;
}

char* CCfgRemoteUnit::getKey()
{
    return m_key;
}

long CCfgRemoteUnit::getWorkNode()
{
    return m_workNode;
}

long CCfgRemoteUnit::getNameNode()
{
    return m_nameNode;
}

long CCfgRemoteUnit::getDataNode()
{
    return m_dataNode;
}
