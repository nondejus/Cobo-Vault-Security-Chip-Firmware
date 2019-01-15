/**@NEW FILE***************************************************************************************
* @filename: StoneRandom.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#define STONE_RANDOM_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneRandom.h"
#include "SecurityChipAPI.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
STONE_RANDOM_EXT emRetType stone_get_random(uint8_t bufRandom[], uint16_t randomLen)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;
	
	ret = security_chip_trng_gen_random(bufRandom, randomLen);
	if (RT_OK != ret)
	{
		return ERT_RngFail;
	}

	return emRet;
}

STONE_RANDOM_EXT void stone_get_strong_random(uint8_t bufRandom[], uint16_t randomLen)
{
	UINT8 ret = RT_OK;
	
	do
	{
		ret = security_chip_trng_gen_random_check(bufRandom, randomLen);	//security_chip_api
	}while (RT_OK != ret);
}
/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
