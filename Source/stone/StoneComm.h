/**@NEW FILE***************************************************************************************
* @filename: StoneComm.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-23
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_COMM_H
#define STONE_COMM_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_COMM_GLOBAL
#define STONE_COMM_EXT
#else
#define STONE_COMM_EXT	extern
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
#include "SecurityChipAPI.h"
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
/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_COMM_EXT void stone_comm_handler(void);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
