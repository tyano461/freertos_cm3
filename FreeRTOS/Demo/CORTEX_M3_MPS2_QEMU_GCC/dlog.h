#ifndef __APP_DLOG_H__
#define __APP_DLOG_H__

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define d(s, ...)                                                                     \
    do                                                                                \
    {                                                                                 \
        printf("%s(%d) %s " s "\n", __FILENAME__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif