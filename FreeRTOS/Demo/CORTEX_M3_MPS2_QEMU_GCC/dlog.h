#ifndef __APP_DLOG_H__
#define __APP_DLOG_H__

#include <stdio.h>
#define d(s, ...)                                                                 \
    do                                                                            \
    {                                                                             \
        printf("%s(%d) %s " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif