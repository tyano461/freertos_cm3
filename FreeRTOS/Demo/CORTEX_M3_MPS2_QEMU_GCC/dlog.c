#include "dlog.h"

#define BUF_SIZE 200
#define d2c(d) \
    (d < 0xa) ? d + '0' : ((d < 0x10) ? d - 0xa + 'a' : '.')

#ifndef min
#define min(a, b) ((a) > (b)) ? (b) : (a)
#endif

static char buf[BUF_SIZE];
char *b2s(const void *data, int maxlen)
{
    int i;
    int len = min(maxlen, (BUF_SIZE - 1) / 4);
    uint8_t *o = (uint8_t *)data;
    char *p = buf;
    char u, l;
    for (i = 0; i < len; i++)
    {
        u = ((*o) & 0xf0) >> 4;
        l = ((*o) & 0x0f) >> 0;
        *p++ = d2c(u);
        *p++ = d2c(l);
        if ((i % 16) == 15)
        {
            *p++ = '\n';
        }
        else
        {
            *p++ = ' ';
        }
        o++;
    }
    if ((*(p - 1)) != '\n')
        *p++ = '\n';
    *p++ = '\0';
    return buf;
}