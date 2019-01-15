/**@NEW FILE***************************************************************************************
* @filename: StoneCKD.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_CKD_H
#define STONE_CKD_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_CKD_GLOBAL
#define STONE_CKD_EXT
#else
#define STONE_CKD_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdint.h>
#include "SecurityChipAPI.h"
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
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_CKD_EXT emRetType stone_CKD_prv2prv(SECP_PriKey *pParentPrvKey, uint8_t *bufChainCode, 
 		uint32_t index,  SECP_PriKey *pChildPrvKey, uint8_t *bufChildChainCode);
STONE_CKD_EXT emRetType stone_CKD_pub2pub(SECP_PubKey *pParentPubKey, uint8_t *bufChainCode, 
		uint32_t index, SECP_PubKey *pChildPubKey, uint8_t *bufChildChainCode);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
