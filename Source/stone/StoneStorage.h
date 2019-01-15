/**@NEW FILE***************************************************************************************
* @filename: StoneStorage.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-23
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_STORAGE_H
#define STONE_STORAGE_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_STORAGE_GLOBAL
#define STONE_STORAGE_EXT
#else
#define STONE_STORAGE_EXT	extern
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
#include "StoneFlashPartition.h"
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
typedef struct KEY_STORE
{
	uint16_t keyLen;
	uint32_t addrKeyOffset;
	uint32_t addrKeyCKSOffset;
	uint16_t ivLen;
	uint32_t addrIVOffset;
	uint32_t addrIVCKSOffset;
}stKSType;
STONE_STORAGE_EXT stKSType stKSRootKey, stKSTransKey;
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_STORAGE_EXT emRetType stone_storage_init(void);
STONE_STORAGE_EXT emRetType stone_storage_read(uint8_t *pBuf, uint16_t bufLen, uint32_t addrOffset);
STONE_STORAGE_EXT emRetType stone_storage_write(uint8_t *pBuf, uint16_t bufLen, uint32_t addrOffset);
STONE_STORAGE_EXT emRetType stone_storage_safe_read(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset);
STONE_STORAGE_EXT emRetType stone_storage_safe_write(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset);
STONE_STORAGE_EXT emRetType stone_storage_security_safe_read(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset);
STONE_STORAGE_EXT emRetType stone_storage_security_safe_write(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset);
STONE_STORAGE_EXT emRetType stone_storage_encryption(uint8_t nType, stKSType *pstKS, 
			uint8_t *pPlain, uint16_t len, uint8_t *pEncrypt);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
