#define ISEOL(C) ((C) == '\n' || (C) == '\r')
#define BUFSIZE 4

#define typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));

#define PS_NORMAL 0
#define PS_EOL 1
#define PS_QUOTED 2
#define PS_PAREN 3
#define PS_ESC 4

