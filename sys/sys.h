/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef SYS_H
#define SYS_H

#include "../userspace/ipc.h"
#include "../userspace/lib/types.h"

typedef enum {
    SYS_SET_STDOUT = IPC_SYSTEM + 1,                            //!< Will be called for objects, created before global stdout STREAM is set
    SYS_GET_INFO,                                               //!< Info about process
    SYS_GET_POWER,
    SYS_GET_TIMER,
    SYS_GET_UART,
    SYS_SET_POWER,
    SYS_SET_TIMER,
    SYS_SET_UART
}SYS_IPCS;

//temporaily struct, before root fs will be ready
typedef struct {
    HANDLE power;
    HANDLE timer;
    HANDLE uart;
}SYS_OBJECT;

#endif // SYS_H
