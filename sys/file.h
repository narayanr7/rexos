/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef FILE_H
#define FILE_H

#include "sys.h"
#include "../userspace/direct.h"
#include "../userspace/block.h"

/** \addtogroup file file
    \{
 */


/**
    \brief open file
    \param process: process handle
    \param file: file handle
    \retval handle on success, INVALID_HANDLE on error
*/

__STATIC_INLINE HANDLE fopen(HANDLE process, HANDLE file)
{
    IPC ipc;
    ipc.cmd = IPC_OPEN;
    ipc.process = process;
    ipc.param1 = file;
    if (call(&ipc))
        return ipc.param1;
    return INVALID_HANDLE;
}

/**
    \brief open file with custom initialization data
    \param process: process handle
    \param file: file handle
    \param addr: address of direct read
    \param size: size of direct read
    \retval handle on success, INVALID_HANDLE on error
*/

__STATIC_INLINE HANDLE fopen_ex(HANDLE process, HANDLE file, void* ptr, unsigned int size)
{
    IPC ipc;
    direct_enable_read(process, ptr, size);
    ipc.cmd = IPC_OPEN;
    ipc.process = process;
    ipc.param1 = file;
    if (call(&ipc))
        return ipc.param1;
    return INVALID_HANDLE;
}

/**
    \brief close file
    \param process: process handle
    \param file: file handle
    \retval true on success
*/

__STATIC_INLINE bool fclose(HANDLE process, HANDLE file)
{
    IPC ipc;
    ipc.cmd = IPC_CLOSE;
    ipc.process = process;
    ipc.param1 = file;
    return call(&ipc);
}

/**
    \brief read from file (async)
    \param process: process handle
    \param file: file handle
    \param block: file block
    \param size: size of transfer
    \retval none. Check corresponding IPC.
*/

__STATIC_INLINE void fread(HANDLE process, HANDLE file, HANDLE block, unsigned int size)
{
    IPC ipc;
    ipc.cmd = IPC_READ;
    ipc.process = process;
    ipc.param1 = file;
    ipc.param2 = block;
    ipc.param3 = size;
    block_send_ipc(block, process, &ipc);
}

/**
    \brief read from file (async) with no data
    \param process: process handle
    \param file: file handle
    \retval none. Check corresponding IPC.
*/

__STATIC_INLINE void fread_null(HANDLE process, HANDLE file)
{
    IPC ipc;
    ipc.cmd = IPC_READ;
    ipc.process = process;
    ipc.param1 = file;
    ipc.param2 = INVALID_HANDLE;
    ipc.param3 = 0;
    ipc_post(&ipc);
}

/**
    \brief write to file (async)
    \param process: process handle
    \param file: file handle
    \param block: file block
    \param size: size of transfer
    \retval none. Check corresponding IPC.
*/

__STATIC_INLINE void fwrite(HANDLE process, HANDLE file, HANDLE block, unsigned int size)
{
    IPC ipc;
    ipc.cmd = IPC_WRITE;
    ipc.process = process;
    ipc.param1 = file;
    ipc.param2 = block;
    ipc.param3 = size;
    block_send_ipc(block, process, &ipc);
}

/**
    \brief write to file (async) with no data
    \param process: process handle
    \param file: file handle
    \retval none. Check corresponding IPC.
*/

__STATIC_INLINE void fwrite_null(HANDLE process, HANDLE file)
{
    IPC ipc;
    ipc.cmd = IPC_WRITE;
    ipc.process = process;
    ipc.param1 = file;
    ipc.param2 = INVALID_HANDLE;
    ipc.param3 = 0;
    ipc_post(&ipc);
}

/**
    \brief flush file
    \param process: process handle
    \param file: file handle
    \retval true on success
*/

__STATIC_INLINE bool fflush(HANDLE process, HANDLE file)
{
    IPC ipc;
    ipc.cmd = IPC_FLUSH;
    ipc.process = process;
    ipc.param1 = file;
    return call(&ipc);
}

/** \} */ // end of file group

#endif // FILE_H
