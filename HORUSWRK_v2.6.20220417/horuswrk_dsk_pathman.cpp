/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_pathman.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#include"horuswrk_base_all.h"

CDskPathMan::CDskPathMan(int maxNumDskPath, char* dirTableFile, char* dirTableFilePath)
{
    init(maxNumDskPath, dirTableFile, dirTableFilePath);
}

CDskPathMan::~CDskPathMan()
{
    terminate();
}

// init(): initiate path manager
void CDskPathMan::init(int maxNumDskPath, char* dirTableFile, char* dirTableFilePath)
{
    strNCpyUtil(m_dirTableFile, dirTableFile, PATHNAMESZ);
    strNCpyUtil(m_dirTableFilePath, dirTableFilePath, PATHNAMESZ);
    m_maxNumDskPath = maxNumDskPath; 
    m_currNumDskPath = 0; 

    m_arrDskPath = (dsk_path_t*)allocDataArray(sizeof(dsk_path_t), m_maxNumDskPath);

    loadFile(m_dirTableFilePath);
}

// term(): terminate path manager
void CDskPathMan::terminate()
{
    saveFile(m_dirTableFilePath);
    if(m_arrDskPath != NULL)
        freeDataArray(m_arrDskPath);
}

/* Methodes */

// loadFile(): load table of paths from file
// fileName - path's table file name
int CDskPathMan::loadFile(char* fileName)
{
    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_READ, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_path_t);

        m_currNumDskPath = 0;
        while(m_currNumDskPath < m_maxNumDskPath)
        {
            if(fread(&m_arrDskPath[m_currNumDskPath], 1, size, f) == 0) break;
            m_currNumDskPath += 1;
        }
        fclose(f);
    }
    return rscode;
}

// saveFile(): save table of paths to file
// fileName - path's table file name
int CDskPathMan::saveFile(char* fileName)
{
    bigstr_t errmsg;

    FILE* f = NULL;

    int rscode = openFileUtil(&f, fileName, FILMODE_WRITE_TRUNCATE_DATA, DBTRUE);
    if(rscode == RSOK) 
    {
        size_t size = sizeof(dsk_path_t);
        for(int i = 0; i < m_currNumDskPath; i++)
        {
            dsk_path_t* p = &m_arrDskPath[i];

            long num_write = fwrite(p, 1, size, f);
            sprintf(errmsg, "NumWrite=%ld\n", num_write);
            warnMsg(DEBUG_LEVEL_03, __HORUSWRK_DSK_PATHMAN_H, "saveFile()", errmsg);
        }
        fclose(f);
    }
    return rscode;
}

// addItem(): add item to tablespace
// path_name - path name
// path_ext - path extension
// path_type - path type (-1=EMPTY / 1=DIR / 2=FILE)
// path_parent - parent path identity
// block_start - start block
// block_qty - block quantity
// data_size - data size
// uid - user identifier
int CDskPathMan::addItem(
    char* path_name,
    char* path_ext,
    long path_type,
    long disk_group,
    long path_parent,
    long block_start,
    long block_qty,
    long data_size,
    long uid,
    long* oid)
{
    CSequence* seq = gAppMain.getSequencePtr();

    long currTimestamp = getCurrentTimestamp();

    dsk_path_t* data = NULL;

    if(findItem(path_parent, path_name, & data) != RSOK)
    {
        data = &(m_arrDskPath[m_currNumDskPath]);

        (*oid) = seq->nextVal((char*)SEQ_TABLE_PATH);

        str_t key;
        sprintf(key, "%ld", (*oid));

        long keyHash = getHash(key);

        /* Add new item
         */
        setItemData(
            & data, 
            (*oid),
            keyHash,
            path_type,
            disk_group,
            path_parent,
            currTimestamp,
            uid,
            currTimestamp,
            uid,
            DBTRUE,
            DBNULL_LONG,
            DBNULL_LONG,
            DBFALSE,
            block_start,
            block_qty,
            data_size,
            path_name,
            path_ext,
            key);
            
        m_currNumDskPath += 1;
    }
    else
    {
        /* Update existent item
         */
        data->modify_date = currTimestamp;
        data->modify_uid = uid;
        data->is_modified = DBTRUE;
        data->block_start = block_start;
        data->block_qty = block_qty;
        data->data_size = data_size;
        strNCpyUtil(data->path_name, path_name, STRSZ);
        strNCpyUtil(data->path_ext, path_ext, STRSZ);

        (*oid) = data->oid;
    }

    return(RSOK);
}

// findItem(): find item in path
// oid - path oid
// resval - result data
int CDskPathMan::findItem(long oid, dsk_path_t** resval)
{
    for(int i = 0; i < m_currNumDskPath; i++)
    {
        dsk_path_t* p = & m_arrDskPath[i];    

        if(p->is_deleted == DBTRUE) continue;

        if(p->oid == oid)
        {
            (*resval) = p;
            return(RSOK);
        }
    }

    (*resval) = NULL;
    return(RSERR);    
}

// findItem(): find item in path
// key - path key
// resval - result data
int CDskPathMan::findItem(char* key, dsk_path_t** resval)
{
    long keyHash = getHash(key);

    for(int i = 0; i < m_currNumDskPath; i++)
    {
        dsk_path_t* p = & m_arrDskPath[i];    

        if(p->is_deleted == DBTRUE) continue;

        if(p->key_hash == keyHash)
        {
            if(strNCmpUtil(p->key, key, STRSZ) == 0)
            {
                (*resval) = p;
                return(RSOK);
            }
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findItem(): find item in path
// path_parent - path parent oid
// path_name - path name
// resval - result data
int CDskPathMan::findItem(long path_parent, char* path_name, dsk_path_t** resval)
{
    for(int i = 0; i < m_currNumDskPath; i++) {
        dsk_path_t* p = & m_arrDskPath[i];   

        if(p->is_deleted == DBTRUE) continue;

        if(p->path_parent == path_parent) 
        {
            if(strNCmpUtil(p->path_name, path_name, STRSZ) == 0) 
            {
                (*resval) = p;
                return(RSOK);
            }
        }
    }

    (*resval) = NULL;
    return(RSERR);
}

// findAll(): find all paths
// arr - result data (array of paths)
// arrsz - return the number of rows in the array
int CDskPathMan::findAll(dsk_path_t** arr, long* arrsz)
{
    (*arrsz) = m_currNumDskPath;
    (*arr) = (dsk_path_t*)allocDataArray(sizeof(dsk_path_t), (*arrsz));
    if((*arr) == NULL) return RSERR;

    dsk_path_t* p = (*arr);
    for(int i = 0; i < m_currNumDskPath; i++) 
    {
        if(p->is_deleted == DBTRUE) continue;

        memNCpyUtil((byte*)p, (byte*)& m_arrDskPath[i], sizeof(dsk_path_t));
        debugEntry(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "findAll()", p);
        p++;
    }  
    return RSOK;
}

// findAllChildByPathParent(): find all paths at path parent
// arr - result data (array of paths)
// arrsz - return the number of rows in the array
// path_parent - path parent to be searched
// bDeleted - retrieve deleted items
int CDskPathMan::findAllChildByPathParent(dsk_path_t** arr, long* arrsz, long path_parent, long bDeleted)
{
    if(getNumEntriesByPathParent(arrsz, path_parent, bDeleted) == RSOK) {
        (*arr) = (dsk_path_t*)allocDataArray(sizeof(dsk_path_t), (*arrsz));
        if((*arr) == NULL) return RSERR;

        dsk_path_t* p_dst = (*arr);
        for(int i = 0; i < m_currNumDskPath; i++) {
            dsk_path_t* p_src = & m_arrDskPath[i];

            if((bDeleted != DBTRUE) && (p_src->is_deleted == DBTRUE)) continue;

            if(p_src->path_parent == path_parent) 
            {
                memNCpyUtil((byte*)p_dst, (byte*)p_src, sizeof(dsk_path_t));
                debugEntry(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "findAllChildByPathParent()", p_dst);
                p_dst++;
            }
        }  
    }
    return RSOK;
}

// getNumEntriesByPathParent(): return number of entries at path parent
// num_entries - result number of entries
// path_parent - path parent to be searched
// bDeleted - count deleted items
int CDskPathMan::getNumEntriesByPathParent(long* num_entries, long path_parent, long bDeleted)
{
    (*num_entries) = 0;

    for(int i = 0; i < m_currNumDskPath; i++) {
        dsk_path_t* p = & m_arrDskPath[i];

        if((bDeleted != DBTRUE) && (p->is_deleted == DBTRUE)) continue;

        if(p->path_parent == path_parent) 
        {
            (*num_entries) += 1;
            debugEntry(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "getNumEntriesByPathParent()", p);
        }
    }  
    return RSOK;
}

// deleteItem(): mark item as deleted in path
// oid - path oid
// uid - user id
int CDskPathMan::deleteItem(long oid, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    dsk_path_t* data = NULL;
    
    if(findItem(oid, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "deleteItem()", ERR_CANTFINDOBJECTID);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// deleteItem(): mark item as deleted in path
// key - path key
// uid - user id
int CDskPathMan::deleteItem(char* key, long uid)
{
    long currTimestamp = getCurrentTimestamp();

    dsk_path_t* data = NULL;
    
    if(findItem(key, &data) != RSOK)
    {
        warnMsg(DEBUG_LEVEL_01, __HORUSWRK_DSK_PATHMAN_H, "deleteItem()", ERR_CANTFINDKEY);
        return(RSERR);
    }

    data->delete_uid  = uid;
    data->delete_date = currTimestamp;
    data->is_deleted  = DBTRUE;

    return(RSOK);
}

// newItemData(): mark item as deleted in path
// data - data reference
dsk_path_t* CDskPathMan::newItemData(dsk_path_t** data)
{
    if((*data) == NULL)
        (*data) = (dsk_path_t*)allocData(sizeof(dsk_path_t));

    (*data)->oid          = DBNULL_LONG;
    (*data)->key_hash     = DBNULL_LONG;
    (*data)->path_type    = DBNULL_LONG;
    (*data)->data_size    = DBNULL_LONG;
    (*data)->disk_group   = DBNULL_LONG;
    (*data)->path_parent  = DBNULL_LONG;
    (*data)->create_date  = DBNULL_LONG;
    (*data)->create_uid   = DBNULL_LONG;
    (*data)->modify_date  = DBNULL_LONG;
    (*data)->modify_uid   = DBNULL_LONG;
    (*data)->is_modified  = DBFALSE;
    (*data)->delete_date  = DBNULL_LONG;
    (*data)->delete_uid   = DBNULL_LONG;
    (*data)->is_deleted   = DBFALSE;
    (*data)->block_start  = DBNULL_LONG;
    (*data)->block_qty    = DBNULL_LONG;
    (*data)->data_size    = DBNULL_LONG;
    strNCpyUtil((*data)->path_name, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->path_ext, (char*)DBNULL_CHAR, STRSZ);
    strNCpyUtil((*data)->key, (char*)DBNULL_CHAR, STRSZ);

    return (*data);
}

// setItemData(): mark item as deleted in path
// oid - path oid
// key_hash - path name hash value
// disk_group - disk group oid
// path_parent - parent path identity
// path_type - path type (-1=EMPTY / 1=DIR / 2=FILE)
// create_date - create date
// create_uid - user creator uid
// modify_date - modify date
// modify_uid - user modifier uid
// is_modified - file was modified
// delete_date - delete data
// delete_uid - user delete uid
// is_deleted - file was deleted
// block_start - start block
// block_qty - block quantity
// data_size - data size
// path_name - path name
// path_ext - path extension
// key - path key
dsk_path_t* CDskPathMan::setItemData(
    dsk_path_t** data, 
    long oid,
    long key_hash,
    long path_type,
    long disk_group,
    long path_parent,
    long create_date,
    long create_uid,
    long modify_date,
    long modify_uid,
    long is_modified,
    long delete_date,
    long delete_uid,
    long is_deleted,
    long block_start,
    long block_qty,
    long data_size,
    char* path_name,
    char* path_ext,
    char* key)
{
    if((*data) == NULL)
        (*data) = (dsk_path_t*)allocData(sizeof(dsk_path_t));

    (*data)->oid = oid;
    (*data)->key_hash = key_hash;
    (*data)->path_type = path_type;
    (*data)->disk_group = disk_group;
    (*data)->path_parent = path_parent;
    (*data)->create_date = create_date;
    (*data)->create_uid = create_uid;
    (*data)->modify_date = modify_date;
    (*data)->modify_uid = modify_uid;
    (*data)->is_modified = is_modified;
    (*data)->delete_date = delete_date;
    (*data)->delete_uid = delete_uid;
    (*data)->is_deleted = is_deleted;
    (*data)->block_start = block_start;
    (*data)->block_qty = block_qty;
    (*data)->data_size = data_size;
    strNCpyUtil((*data)->path_name, path_name, STRSZ);
    strNCpyUtil((*data)->path_ext, path_ext, STRSZ);
    strNCpyUtil((*data)->key, key, STRSZ);

    return (*data);
}

/* Debug */

// debug(): show all disk groups
// debugLevel - debug level
// className - class name
// methodName - method name
void CDskPathMan::debug(int debugLevel, const char* className, const char* methodName)
{
    if(debugLevel != DEBUG_LEVEL) return;

    dsk_path_t* p = NULL;
    for(int i = 0; i < m_currNumDskPath; i++)
    {
        p = &m_arrDskPath[i];
        debugEntry(debugLevel, className, methodName, p);
    }  
}

// debugEntry(): show disk group
// debugLevel - debug level
// className - class name
// methodName - method name
// p - pointer to a disk path entry
void CDskPathMan::debugEntry(int debugLevel, const char* className, const char* methodName, dsk_path_t* p)
{
    if(debugLevel != DEBUG_LEVEL) return;

    bigstr_t errmsg;
    sprintf(
        errmsg, 
        "DskPath: Oid=%ld,KeyHash=%ld,PathType=%ld,DiskGroup=%ld,PathParent=%ld,CreateDate=%ld,CreateUid=%ld,ModifyDate=%ld,ModifyUid=%ld,IsModified=%ld,DeleteDate=%ld,DeleteUid=%ld,IsDeleted=%ld,BlockStart=%ld,BlockQty=%ld,DataSize=%ld,PathName=%s,PathExt=%s,Key=%s\n",
        p->oid,
        p->key_hash,
        p->path_type,
        p->disk_group,
        p->path_parent,
        p->create_date,
        p->create_uid,
        p->modify_date,
        p->modify_uid,
        p->is_modified,
        p->delete_date,
        p->delete_uid,
        p->is_deleted,
        p->block_start,
        p->block_qty,
        p->data_size,
        p->path_name,
        p->path_ext,
        p->key);
    warnMsg(debugLevel, className, methodName, errmsg);
}

/* Getters/Setters */

char* CDskPathMan::getDirTableFile()
{
    return m_dirTableFile;
}

char* CDskPathMan::getDirTableFilePath()
{
    return m_dirTableFilePath;
}

int CDskPathMan::getMaxNumDskPath()
{
    return m_maxNumDskPath;    
}

int CDskPathMan::getCurrNumDskPath()
{
    return m_currNumDskPath;
}
