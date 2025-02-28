/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_roundrobin.cpp
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskRoundRobin::CDskRoundRobin(int maxNumRoundRobinTable)
{
    init(maxNumRoundRobinTable);
}

CDskRoundRobin::~CDskRoundRobin()
{
    terminate();
}

// init(): initiate disk groups
void CDskRoundRobin::init(int maxNumRoundRobinTable)
{
    m_maxNumRoundRobinTable = maxNumRoundRobinTable; 
    m_arrRoundRobinTable = (dsk_roundrobin_t*)allocDataArray(sizeof(dsk_roundrobin_t), m_maxNumRoundRobinTable);
    m_currNumRoundRobinTable = 0; 
}

// terminate(): terminate disk groups
void CDskRoundRobin::terminate()
{
    if(m_arrRoundRobinTable != NULL)
       freeDataArray(m_arrRoundRobinTable);
}

/* Methodes */

// addRoundRobinTableItem(): add new round robin table item
// pCfgRemoteUnit - remote unit configutation pointer 
// pDiskGroup - disk droup pointer
// pDiskDev - disk device pointer
dsk_roundrobin_t* CDskRoundRobin::addRoundRobinTableItem(
    CCfgRemoteUnit* pCfgRemoteUnit, 
    CDskDiskGroup* pDiskGroup, 
    CDskDiskDev* pDiskDev)
{
    dsk_roundrobin_t* p = NULL;

    if(m_currNumRoundRobinTable < m_maxNumRoundRobinTable) {
        p = & m_arrRoundRobinTable[m_currNumRoundRobinTable];
        m_currNumRoundRobinTable += 1;

        p->oid = m_currNumRoundRobinTable;
        p->remoteunit_oid = pCfgRemoteUnit->getOid();
        p->diskgroup_oid = pDiskGroup->getOid();
        p->diskdev_oid = pDiskDev->getOid();
        p->diskdev_sector = DBNULL_LONG;
        p->last_update = DBNULL_LONG;
        p->num_blocks = DBNULL_LONG;
    }
    return p;
}

/* Getters/Setters */

dsk_roundrobin_t* CDskRoundRobin::getRoundRobinTablePtrAt(long pos)
{
    if(pos < m_currNumRoundRobinTable) {
        dsk_roundrobin_t* p = & m_arrRoundRobinTable[pos];
        return p;
    }
    return NULL;
}

dsk_roundrobin_t* CDskRoundRobin::getRoundRobinTablePtr(long oid)
{
    for(int i = 0; i < m_currNumRoundRobinTable; i++) {
        dsk_roundrobin_t* p = & m_arrRoundRobinTable[i];
        if(p->oid == oid)
            return p;
    }
    return NULL;   
}

dsk_roundrobin_t* CDskRoundRobin::getEntryWithMinNumBlocksByRemoteUnitOidPtr(long remoteUnitOid)
{
    dsk_roundrobin_t* p_min = NULL;

    if(m_currNumRoundRobinTable > 0) {
        p_min = & m_arrRoundRobinTable[0];
        
        for(int i = 1; i < m_currNumRoundRobinTable; i++) {
            dsk_roundrobin_t* p = & m_arrRoundRobinTable[i];
            if( (remoteUnitOid == DBNULL_LONG) || 
                ( (p->remoteunit_oid == remoteUnitOid) && 
                  (p->num_blocks < p_min->num_blocks) ) )
                p_min = p;
        }
    }
    return p_min;   
}

dsk_roundrobin_t* CDskRoundRobin::getEntryWithMinNumBlocksByDiskGroupOidPtr(int group_oid)
{
    dsk_roundrobin_t* p_min = NULL;

    if(m_currNumRoundRobinTable > 0) {
        p_min = & m_arrRoundRobinTable[0];
        
        for(int i = 1; i < m_currNumRoundRobinTable; i++) {
            dsk_roundrobin_t* p = & m_arrRoundRobinTable[i];
            if( (group_oid == DBNULL_LONG) ||
                ( (p->diskgroup_oid == group_oid) && 
                  (p->num_blocks < p_min->num_blocks) ) )
                p_min = p;
        }
    }

    if(p_min != NULL) {
        p_min->last_update = getCurrentTimestamp();
        p_min->num_blocks = p_min->num_blocks + 1;
    }
    return p_min;   
}

int CDskRoundRobin::getDiskGroupWithMinNumBlocksByRemoteUnitOid(int remoteUnitOid)
{
    dsk_roundrobin_t* p = getEntryWithMinNumBlocksByRemoteUnitOidPtr(remoteUnitOid);
    if(p != NULL)
        return(p->diskgroup_oid);
    return(-1);
}

int CDskRoundRobin::getArrRoundRobinTablePtr(dsk_roundrobin_t** data, long* datasz, long maxBlocks)
{
    (*datasz) = maxBlocks; 
    (*data) = (dsk_roundrobin_t*)allocDataArray(sizeof(dsk_roundrobin_t), maxBlocks);

    if((*data) == NULL) return RSERR;

    long currTimestamp = getCurrentTimestamp();

    dsk_roundrobin_t* p = (*data);
    for(int i = 0; i < maxBlocks; i++) {
        p = getEntryWithMinNumBlocksByRemoteUnitOidPtr(DBNULL_LONG);

        p->last_update = currTimestamp;
        p->num_blocks += 1;
    }
    return RSOK;
}

int CDskRoundRobin::getArrRoundRobinTablePtr(dsk_roundrobin_t** data, long* datasz, long maxBlocks, int group_oid)
{
    (*datasz) = maxBlocks; 
    (*data) = (dsk_roundrobin_t*)allocDataArray(sizeof(dsk_roundrobin_t), maxBlocks);

    if((*data) == NULL) return RSERR;

    long currTimestamp = getCurrentTimestamp();

    dsk_roundrobin_t* p = (*data);
    for(int i = 0; i < maxBlocks; i++) {
        p = getEntryWithMinNumBlocksByDiskGroupOidPtr(group_oid);

        p->last_update = currTimestamp;
        p->num_blocks += 1;
    }
    return RSOK;
}

int CDskRoundRobin::getMaxNumRoundRobinTable()
{
    return m_maxNumRoundRobinTable;
}

int CDskRoundRobin::getCurrNumRoundRobinTable()
{
    return m_currNumRoundRobinTable;    
}
