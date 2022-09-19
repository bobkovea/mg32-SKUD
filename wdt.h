#ifndef IWDT_H
#define IWDT_H
#include "MG32x02z_DRV.h"

#define WDTO_7MS   IWDT_DIV_1
#define WDTO_15MS   IWDT_DIV_2
#define WDTO_30MS   IWDT_DIV_4
#define WDTO_60MS   IWDT_DIV_8
#define WDTO_125MS  IWDT_DIV_16
#define WDTO_250MS  IWDT_DIV_32
#define WDTO_500MS  IWDT_DIV_64
#define WDTO_1S     IWDT_DIV_128
#define WDTO_2S     IWDT_DIV_256
#define WDTO_4S     IWDT_DIV_512
#define WDTO_8S     IWDT_DIV_1024
#define WDTO_16S    IWDT_DIV_2048
#define WDTO_32S    IWDT_DIV_4096

extern void wdt_enable(IWDT_DIVS_TypeDef divider);
extern void wdt_disable(void);
extern void wdt_reset(void);

#endif // IWDT_H