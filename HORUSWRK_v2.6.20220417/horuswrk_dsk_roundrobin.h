/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_roundrobin.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 06/08/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_ROUNDROBIN_H
#define __HORUSWRK_DSK_ROUNDROBIN_H                      "__HORUSWRK_DSK_ROUNDROBIN_H"

class CDskRoundRobin
{
private:
    dsk_roundrobin_t* m_arrRoundRobinTable;
    int m_maxNumRoundRobinTable;
    int m_currNumRoundRobinTable;

public:
    CDskRoundRobin(int maxNumRoundRobinTable);
    ~CDskRoundRobin();

    // init(): initiate disk groups
    void init(int maxNumRoundRobinTable);

    // terminate(): terminate disk groups
    void terminate();

    /* Methodes */

    // addRoundRobinTableItem(): add new round robin table item
    // pCfgRemoteUnit - remote unit configutation pointer 
    // pDiskGroup - disk droup pointer
    // pDiskDev - disk device pointer
    dsk_roundrobin_t* addRoundRobinTableItem(
        CCfgRemoteUnit* pCfgRemoteUnit, 
        CDskDiskGroup* pDiskGroup, 
        CDskDiskDev* pDiskDev);

    /* Getters/Setters */

    dsk_roundrobin_t* getRoundRobinTablePtrAt(long pos);

    dsk_roundrobin_t* getRoundRobinTablePtr(long oid);

    dsk_roundrobin_t* getEntryWithMinNumBlocksByRemoteUnitOidPtr(long remoteUnitOid);

    dsk_roundrobin_t* getEntryWithMinNumBlocksByDiskGroupOidPtr(int group_oid);

    int getDiskGroupWithMinNumBlocksByRemoteUnitOid(int remoteUnitOid);

    int getArrRoundRobinTablePtr(dsk_roundrobin_t** data, long* datasz, long maxBlocks);

    int getArrRoundRobinTablePtr(dsk_roundrobin_t** data, long* datasz, long maxBlocks, int group_oid);

    int getMaxNumRoundRobinTable();

    int getCurrNumRoundRobinTable();

};

/* NEW_TYPE: CDskRoundRobin Pointer */

typedef CDskRoundRobin* CDskRoundRobinPtr_t;

#endif
