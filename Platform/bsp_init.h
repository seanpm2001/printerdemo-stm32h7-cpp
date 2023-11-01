#ifndef BSP_INIT_H_
#define BSP_INIT_H_

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

void bsp_init(void);
uint32_t InitTouchScreen(void);

#if __cplusplus
}
#endif


#endif

