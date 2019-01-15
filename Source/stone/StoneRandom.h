/**@NEW FILE***************************************************************************************
* @filename: StoneRandom.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_RANDOM_H
#define STONE_RANDOM_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_RANDOM_GLOBAL
#define STONE_RANDOM_EXT
#else
#define STONE_RANDOM_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdint.h>
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
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_RANDOM_EXT emRetType stone_get_random(uint8_t bufRandom[], uint16_t randomLen);
STONE_RANDOM_EXT void stone_get_strong_random(uint8_t bufRandom[], uint16_t randomLen);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
