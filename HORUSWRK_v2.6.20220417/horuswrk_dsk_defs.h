/*
 * Copyright(C) 2020-2021 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_dsk_defs.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 14/07/2021
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_DSK_DEFS_H
#define __HORUSWRK_DSK_DEFS_H                       "__HORUSWRK_DSK_DEFS_H"

#define DEF_DSK_NOWRITE_AND_NOREAD_THREADS                      0
#define DEF_DSK_WRITE_THREADS                                   1
#define DEF_DSK_READ_THREADS                                    2
#define DEF_DSK_WRITE_AND_READ_THREADS                          3

// NOT_USED
//#define DEF_DSK_SHMEM                                           4
//#define DEF_DSK_NOREAD_THREADS_WITH_SHMEM                       4
//#define DEF_DSK_READ_THREADS_WITH_SHMEM                         6
//#define DEF_DSK_WRITE_AND_READ_THREADS_WITH_SHMEM               7

#define DEF_DSK_MULTITHREAD_FILESYS_TYPE            3           // NOWRITE_AND_NOREAD=0; 
                                                                // WRITE=1; 
                                                                // READ=2; 
                                                                // WRITE_AND_READ = 3
                                                                
                                                                // NOT_USED
                                                                // SHMEM = 4; 
                                                                // NOWRITE_AND_NOREAD_WITH_SHMEM = 4
                                                                // WRITE_AND_READ_WITH_SHMEM = 7

#define DEF_DSK_MAX_DISKGROUPS                      12

#define DEF_DSK_MAX_DISKDEV                         6

#define DEF_DSK_MAX_DISKDEV_THREADS                 (12 * 6)    // MAX NUMBER OF THREADS = MAX_DISKGROUPS x MAX_DISKDEV

#define DEF_DSK_MAX_NUMOFDISKPATHS                  1024

#define DEF_DSK_MAX_NUMOFBLOCKS                     8192

#define DEF_DSK_MAX_NUMOFSUPERBLOCKS                49152       // 6 DISKDEV x 8192 BLOCKS PER DISKDEV = 49152 ENTRIES

#define DEF_DSK_MAX_NUMOFSUPERBLOCKSINDEX           1024        // =MAX_NUMOFDISKPATHS

#define DEF_DSK_MAX_NUMOFBLOCKSINDEX                1024        // =MAX_NUMOFDISKPATHS

#define DEF_DSK_MAX_BLOCKSIZE                       16384

#define DEF_DSK_MAX_NUMOFROUNDROBIN                 72          // 12 DISKGROUPS x 6 DISKDEVS = 72 ENTRIES

#define DEF_DSK_INIT_THREADID                       1000L       // INITIAL THREAD ID

//#define DEF_DSK_MAX_NUMOFTRHEADS_PER_DISKDEV      1           // ATENCAO: REVISAR PARA MAIS DE 1

#define DEF_DSK_MAX_NUMOFSHMEMOBJECTS               32          // MAX NUMBER OF SHARED MEMORY OPENED OBJECTS

/* DEFINING INITIAL CONSTANTS WHICH WILL BE EXCLUDED AT FINAL VERSION 
*/ 
#define DEF_DSK_NUMOFSUPERBLOCKS                    6291456
#define DEF_DSK_NUMOFBLOCKS                         2097152
#define DEF_DSK_BLOCKSIZE                           16384

/* THREAD TYPE */

#define DEF_DSK_THREAD_TYPE_NONE                    -1L
#define DEF_DSK_THREAD_TYPE_READ                    1L
#define DEF_DSK_THREAD_TYPE_WRITE                   2L

/* DISK PATH TYPE */

#define DEF_DSK_PATHTYPE_EMPTY                      -1L
#define DEF_DSK_PATHTYPE_DIR                        1L
#define DEF_DSK_PATHTYPE_FILE                       2L

/* LIST DIR FORMAT */

#define DEF_DSK_PATHFMT_DELETEDPATH                 ((char*)"Row[%d]:\t[Deleted]\tPath:\t%s\n")
#define DEF_DSK_PATHFMT_DELETEDFILE                 ((char*)"Row[%d]:\t[Deleted]\tFile:\t%s\t%ld\t%ld\n")
#define DEF_DSK_PATHFMT_ACTIVEPATH                  ((char*)"Row[%d]:\t[Active]\tPath:\t%s\n")
#define DEF_DSK_PATHFMT_ACTIVEFILE                  ((char*)"Row[%d]:\t[Active]\tFile:\t%s\t%ld\t%ld\n")

/* DATA BLOCK TYPE */

#define IS_DSK_DATATYPE(v)                          ((v >= 0xF0)&&(v <= 0xFF))
//
#define IS_DSK_DATATYPE_REQUEST(v)                  ((v >= 0xF0)&&(v <= 0xF7))
#define IS_DSK_DATATYPE_RESPONSE(v)                 ((v >= 0xF8)&&(v <= 0xFF))

#define DEF_DSK_DATATYPE_NONE                       0x00
//REQUEST
#define DEF_DSK_DATATYPE_REQWRITE_BYTEARRAY         0xF0
#define DEF_DSK_DATATYPE_REQREAD_BYTEARRAY          0xF1
#define DEF_DSK_DATATYPE_REQWRITE_STRING            0xF2
#define DEF_DSK_DATATYPE_REQREAD_STRING             0xF3
//RESPONSE
#define DEF_DSK_DATATYPE_RESPWRITE_BYTEARRAY        0xF8
#define DEF_DSK_DATATYPE_RESPREAD_BYTEARRAY         0xF9
#define DEF_DSK_DATATYPE_RESPWRITE_STRING           0xFA
#define DEF_DSK_DATATYPE_RESPREAD_STRING            0xFB

/* DEFINE SHARED MEMORY DIRECTORY
*/ 
#define DEF_SRC_IMAGE_SHMDIR                        ((char*)"/dev/shm/")

/* DISK DEVICES STRUCTURES
*/

// BLOCK READ/WRITE REQUEST STRUCT
typedef struct dsk_block_rwreq_struct {
    byte dataType;                                  // 1B 
    long oid;                                       // 4B
    long src_remoteunit_oid;                        // 4B
    long dst_remoteunit_oid;                        // 4B
    long disk_group_oid;                            // 4B
    long disk_dev_oid;                              // 4B
    long block_sector;                              // 4B
    long block_num;                                 // 4B
    long uid;                                       // 4B
    long reqnum;                                    // 4B
    long reqtimestamp;                              // 4B
    long datasz;                                    // 4B (TOTAL = 45B)
    byte data[DEF_DSK_MAX_BLOCKSIZE];               // BLOCKSIZE = 16384 
} dsk_block_rwreq_t;                                // TOTAL = 16429B

// BLOCK READ/WRITE RESPONSE STRUCT
typedef struct dsk_block_rwresp_struct {
    byte dataType;                                  // 1B 
    long oid;                                       // 4B
    long src_remoteunit_oid;                        // 4B
    long dst_remoteunit_oid;                        // 4B
    long disk_group_oid;                            // 4B
    long disk_dev_oid;                              // 4B
    long block_sector;                              // 4B
    long block_num;                                 // 4B
    long uid;                                       // 4B
    long reqnum;                                    // 4B
    long reqtimestamp;                              // 4B
    long datasz;                                    // 4B
    long rescode;                                   // 4B
    str_t resmsg;                                   // 32B (TOTAL = 81B)
    byte data[DEF_DSK_MAX_BLOCKSIZE];               // BLOCKSIZE = 16384 
} dsk_block_rwresp_t;                               // TOTAL = 16465B

// ROUND ROBIN STRUCTURE
typedef struct dsk_roundrobin_struct {
    long oid;                                       // 4B
    long remoteunit_oid;                            // 4B
    long diskgroup_oid;                             // 4B
    long diskdev_oid;                               // 4B
    long diskdev_sector;                            // 4B
    long last_update;                               // 4B
    long num_blocks;                                // 4B
} dsk_roundrobin_t;                                 // TOTAL = 28B

// PATH STRUCTURE
typedef struct dsk_path_struct {
    long oid;                                       // 4B
    long key_hash;                                  // 4B
    long disk_group;                                // 4B
    long path_parent;                               // 4B
    long path_type;                                 // 4B   (001=Directory / 002=File)
    long create_date;                               // 4B
    long create_uid;                                // 4B
    long modify_date;                               // 4B
    long modify_uid;                                // 4B
    long is_modified;                               // 4B
    long delete_date;                               // 4B
    long delete_uid;                                // 4B
    long is_deleted;                                // 4B
    long block_start;                               // 4B
    long block_qty;                                 // 4B
    long data_size;                                 // 4B
    str_t path_name;                                // 32B
    str_t path_ext;                                 // 32B
    str_t key;                                      // 32B
} dsk_path_t;                                       // TOTAL = 160B

// SUPERBLOCK STRUCTURE
typedef struct dsk_superblock_struct {
    long oid;                                       // 4B
    long disk_group;                                // 4B
    long disk_dev;                                  // 4B
    long path_oid;                                  // 4B
    long block_num;                                 // 4B
    long block_sector;                              // 4B
    long read_count;                                // 4B
    long write_count;                               // 4B
    long create_date;                               // 4B
    long create_uid;                                // 4B
    long modify_date;                               // 4B
    long modify_uid;                                // 4B
    long is_modified;                               // 4B
    long delete_date;                               // 4B
    long delete_uid;                                // 4B
    long is_deleted;                                // 4B
    str_t key;                                      // 32B
} dsk_superblock_t;                                 // TOTAL = 92B

// SUPERBLOCK INDEX STRUCTURE
typedef struct dsk_superblock_index_struct {
    long oid;                                       // 4B - KEY: path_oid, block_num
    long is_valid;                                  // 4B
    CIdxDoubleLinkedList* pLsSuperblock;            // 4B
} dsk_superblock_index_t;                           // TOTAL = 12B

// BLOCK STRUCTURE
typedef struct dsk_block_struct {
    long oid;                                       // 4B
    long path_oid;                                  // 4B
    long block_num;                                 // 4B
    long block_sector;                              // 4B
    long is_valid;                                  // 4B
    str_t key;                                      // 32B
} dsk_block_t;                                      // TOTAL = 52B

typedef dsk_block_t* dsk_block_ptr_t;

// PATH_OID BLOCK IDX STRUCT
typedef struct dsk_block_idx_struct {
    long oid;                                       // 4B - KEY: path_oid, block_num
    long is_valid;                                  // 4B
    CIdxDoubleLinkedList* pLsBlock;                 // 4B
} dsk_block_idx_t;                                  // TOTAL = 12B

// DISK MANAGER OLD THREAD STRUCTURE
//
//typedef struct dsk_diskman_thread_struct {
//    void* pDiskMan;                                 // 4B
//    long oid;                                       // 4B
//    long thread_id;                                 // 4B
//    pthread_t thread_hnd;                           // 4B
//    pthread_mutex_t thread_data_mutex;              // 4B
//    long thread_group;                              // 4B
//    long is_valid;                                  // 4B
//    long is_running;                                // 4B
//    long remoteunit_oid;                            // 4B
//    long diskgroup_oid;                             // 4B
//    long diskgroup_pos;                             // 4B
//    long diskdev_oid;                               // 4B
//    long diskdev_pos;                               // 4B
//    long path_oid;                                  // 4B
//    long num_diskdev;                               // 4B
//    long num_threads;                               // 4B
//    byte* blockbuf;                                 // 4B
//    long block_size;                                // 4B
//    long num_blocks;                                // 4B
//    byte* data;                                     // 4B
//    long datasz;                                    // 4B
//    long uid;                                       // 4B 
//    long resval;                                    // 4B
//} dsk_diskman_thread_t;                             // TOTAL = 84B
//
//typedef dsk_diskman_thread_t* dsk_diskman_thread_ptr_t;

// DISK MANAGER THREAD STRUCTURE
//
typedef struct dsk_diskman_thread_struct {
    pthread_t thread_hnd;                           // 4B
    pthread_mutex_t thread_data_mutex;              // 4B
    void* pDiskMan;                                 // 4B
    void* pRemoteUnit;                              // 4B
    void* pDiskGroup;                               // 4B
    void* pDiskDev;                                 // 4B
    long thread_group;                              // 4B
    long thread_id;                                 // 4B
    long thread_type;                               // 4B
    long is_valid;                                  // 4B
    long is_running;                                // 4B
    long path_parent;                               // 4B
    long path_oid;                                  // 4B
    long uid;                                       // 4B
    long start_block;                               // 4B
    long num_blocks;                                // 4B
    dsk_superblock_t* sblock_data;                  // 4B
    long sblock_datasz;                             // 4B
    byte* data;                                     // 4B
    long datasz;                                    // 4B
    long resval;                                    // 4B
} dsk_diskman_thread_t;                             // TOTAL = 84B

typedef dsk_diskman_thread_t* dsk_diskman_thread_ptr_t;

/* DISKMAN SHARED MEMORY SUPPORT STRUCTURES
*/

// SHARED MEMORY STRUCT
typedef struct dsk_shmem_struct {
    str_t name;                                     // name of shared memory object (32B)
    long fd;                                        // file descriptor (4B)
    long shmbufsz;                                  // shared memory buffer size (4B)
    byte* shmbuf;                                   // shared memory buffer (4B)
} dsk_shmem_t;                                      // TOTAL = 44B

#endif
