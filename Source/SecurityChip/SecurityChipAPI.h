/**@NEW FILE***************************************************************************************
* @filename: SecurityChipAPI.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_TEMPLATE_H
#define STONE_TEMPLATE_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  security_chip_api_GLOBAL
#define security_chip_api_EXT
#else
#define security_chip_api_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "type.h"
#include "StoneErrno.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions*/
/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
void security_chip_api_chip_init(void);
void security_chip_api_wdt_clr(void);
void security_chip_api_sleep(void);
void security_chip_api_tamper_handler(void);
void security_chip_api_tamper_listen(void);
void security_chip_api_tamper_check(void);

uint8_t security_chip_trng_gen_random(uint8_t *pRandBuf,uint16_t nSize);
uint8_t security_chip_trng_gen_random_check(uint8_t *pRandBuf, uint16_t nSize);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/

#endif
/**@END OF FILE***********************************************************************************/

