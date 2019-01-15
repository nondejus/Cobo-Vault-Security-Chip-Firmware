/**@NEW FILE***************************************************************************************
* @filename: StoneComm.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-23
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_COMM_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneComm.h"
#include "StoneHDW.h"
#include "StoneStorage.h"
#include "StoneUtil.h"
#include "StoneKeys.h"
#include "StoneECDSA.h"
#include "StoneRandom.h"
#include "StoneCKD.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
void stone_comm_handler(void)
{
	switch (gstCommStatus.emCommStatus)
	{
		case E_COMM_WAIT_CMD:
		{
/**
 * @note: This part is hidden for security reasons.
*/
			break;
		}
		case E_COMM_MANAGE_CMD:
		{
/**
 * @note: This part is hidden for security reasons.
*/
			break;
		}
		case E_COMM_MANAGE_ERR:
		{
/**
 * @note: This part is hidden for security reasons.
*/
			break;
		}
		default:
		{
/**
 * @note: This part is hidden for security reasons.
*/
			break;
		}
	}
}

/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
