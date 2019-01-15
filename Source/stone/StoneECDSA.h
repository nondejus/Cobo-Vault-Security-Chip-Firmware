/**@NEW FILE***************************************************************************************
* @filename: StoneECDSA.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_ECDSA_H
#define STONE_ECDSA_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_ECDSA_GLOBAL
#define STONE_ECDSA_EXT
#else
#define STONE_ECDSA_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdint.h>
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
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_ECDSA_EXT int is_canonical(uint8_t sig[64]);
STONE_ECDSA_EXT emRetType stone_ECDSA_sign(SECP_PriKey* pSecpPriKey, 
		UINT8 *pHash, UINT32 HashLen, UINT8 *pResult, UINT32 *pResultLen, uint32_t coinType);
STONE_ECDSA_EXT emRetType stone_ECDSA_verify(SECP_PubKey* pSecpPubKey,  
		UINT8 *pHash, UINT32 HashLen, UINT8 *pResult, UINT32 ResultLen);
STONE_ECDSA_EXT emRetType stone_secp_encrypt(SECP_PubKey* pSecpPubKey,  
		UINT8 *pPlainMsg, UINT32 msgLen, UINT8 *pOut, UINT32 *pOutLen);
STONE_ECDSA_EXT emRetType stone_secp_decrypt(SECP_PriKey* pSecpPrvKey,  
		UINT8 *pEncryptMsg, UINT32 msgLen, UINT8 *pOut, UINT32 *pOutLen);
STONE_ECDSA_EXT emRetType stone_ED25519_sign(UINT8 *pMsg, UINT32 msgLen, 
		ED25519_PriKey* pEd25519PriKey, ED25519_PubKey* pEd25519PubKey, UINT8 *pResult);
STONE_ECDSA_EXT emRetType stone_ED25519_verify(UINT8 *pMsg, UINT32 msgLen, 
		ED25519_PubKey* pEd25519PubKey, UINT8 *pResult);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
