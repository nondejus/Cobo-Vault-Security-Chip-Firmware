/**@NEW FILE***************************************************************************************
* @filename: main.c
* @description:
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_MAIN_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "SecurityChipAPI.h"
#include "StoneHDW.h"
#include "StoneComm.h"
#include "StoneStorage.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
void stone_powerup_handler(void);
void stone_firmware_upgrade_handler(void);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
int main(void)
{
	security_chip_api_chip_init();
	stone_powerup_handler();
	stone_firmware_upgrade_handler();
		
	while (1)
	{
		security_chip_api_wdt_clr();
		security_chip_api_tamper_handler();
		stone_comm_handler();
	}
}

void stone_powerup_handler(void)
{
	emRetType emRet = ERT_OK;
	
	gemHDWStatus = stone_HDW_get_status();
	switch(gemHDWStatus)
	{
		case E_HDWS_CHIP:
		{
			emRet = stone_HDW_init_rootkey();
			if (ERT_OK == emRet)
			{
				//initialize other keys here
				emRet = stone_HDW_init_upgrade_key();
			}
			if (ERT_OK == emRet)
			{
				emRet = stone_HDW_set_status(gstHDWStatus[HDW_STATUS_EMPTY]);
			}
			break;
		}
		case E_HDWS_ATTACK:
		{
			security_chip_api_sleep();
			break;
		}
		default:
		{
			security_chip_api_tamper_listen();
			security_chip_api_tamper_check();
			break;
		}
	}
}

void stone_firmware_upgrade_handler(void)
{
	emRetType emRet = ERT_OK;
	uint8_t fwUpgradeFlag = FW_UNCHANGED;
	
	emRet = stone_storage_read(&fwUpgradeFlag, 1, SF_ADDR_FW_UPGRADE_FLAG);
	if (ERT_OK == emRet)
	{
		if (FW_CHANGED == fwUpgradeFlag)
		{
			//do things here after firmware upgrade
			
#warning "if any key changed, u should uncommment the codes below!"
#if 0
			emRet = stone_HDW_init_authentication_key();
			if (ERT_OK == emRet)
			{
				emRet = stone_HDW_init_android_key();
			}
			if (ERT_OK == emRet)
			{
				emRet = stone_HDW_init_upgrade_key();
				if (ERT_OK == emRet)
				{
					fwUpgradeFlag = FW_UNCHANGED;
					emRet = stone_storage_write(&fwUpgradeFlag, 1, SF_ADDR_FW_UPGRADE_FLAG);
				}
			}
#endif		
		}
	}
}
/**@END SECTION**/

/**@END OF FILE***********************************************************************************/
