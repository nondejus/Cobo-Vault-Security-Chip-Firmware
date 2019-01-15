/**@NEW FILE***************************************************************************************
* @filename: StoneHDW.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_HDW_H
#define STONE_HDW_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_HDW_GLOBAL
#define STONE_HDW_EXT
#else
#define STONE_HDW_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
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
STONE_HDW_EXT uint32_t stone_HDW_get_app_version_code(void);
STONE_HDW_EXT uint8_t* stone_HDW_get_app_version_name(void);
STONE_HDW_EXT emRetType stone_HDW_get_SN(uint8_t bufSN[], uint16_t* snLen);
STONE_HDW_EXT emHDWStatusType stone_HDW_get_status(void);
STONE_HDW_EXT emRetType stone_HDW_set_status(const volatile stHDWStatusType stHDWStatus);
STONE_HDW_EXT emRetType stone_HDW_init_rootkey(void);
STONE_HDW_EXT emRetType stone_HDW_init_transkey(void);
STONE_HDW_EXT emRetType stone_HDW_init_authentication_key(void);
STONE_HDW_EXT emRetType stone_HDW_init_android_key(void);
STONE_HDW_EXT emRetType stone_HDW_init_SN(uint8_t bufSN[], uint16_t SNLen);
STONE_HDW_EXT emRetType stone_HDW_init_upgrade_key(void);
STONE_HDW_EXT emRetType stone_HDW_create_wallet(uint8_t *pMnemonic, uint16_t mnemonicLen);
STONE_HDW_EXT emRetType stone_HDW_add_wallet(uint8_t *pPassphrase, uint16_t passphraseLen);
STONE_HDW_EXT emRetType stone_HDW_delete_wallet(void);
STONE_HDW_EXT emRetType stone_HDW_mnemonic_verify(uint8_t *pMnemonicParam, uint16_t mnemonicLenParam);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
