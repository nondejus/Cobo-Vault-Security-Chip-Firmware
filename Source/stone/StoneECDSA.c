/**@NEW FILE***************************************************************************************
* @filename: StoneECDSA.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_ECDSA_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdlib.h>
#include <string.h>
#include "StoneECDSA.h"
#include "StoneCoinType.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
STONE_ECDSA_EXT int is_canonical(uint8_t sig[64])
{
	return (	!(sig[0] & 0x80) &&
				!(sig[0] == 0 && !(sig[1] & 0x80)) &&
				!(sig[32] & 0x80) &&
				!(sig[32] == 0 && !(sig[33] & 0x80)));
}

STONE_ECDSA_EXT emRetType stone_ECDSA_sign(SECP_PriKey* pSecpPriKey, 
		UINT8 *pHash, UINT32 HashLen, UINT8 *pResult, UINT32 *pResultLen, uint32_t coinType)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;
	
	switch (coinType)
	{
		case 0:
		{
			return ERT_CoinTypeInvalid;
		}
		default:
		{
			ret = SECP_Sign(pSecpPriKey, pHash, HashLen, pResult, pResultLen, is_canonical);	//security_chip_api
			if (RT_OK != ret)
			{
				return ERT_ECDSASignFail;
			}
			break;
		}
	}
	
 	return emRet;
}

STONE_ECDSA_EXT emRetType stone_ECDSA_verify(SECP_PubKey* pSecpPubKey,  
		UINT8 *pHash, UINT32 hashLen, UINT8 *pSig, UINT32 sigLen)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;

	ret = SECP_Verify(pSecpPubKey, pHash, hashLen, pSig, sigLen);	//security_chip_api
	if (RT_OK != ret)
	{
		return ERT_ECDSAVerifyFail;
	}
	
	return emRet;
}

STONE_ECDSA_EXT emRetType stone_secp_encrypt(SECP_PubKey* pSecpPubKey,  
		UINT8 *pPlainMsg, UINT32 msgLen, UINT8 *pOut, UINT32 *pOutLen)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;
	UINT32 paddingLen = 64 - (msgLen&63);
	UINT32 totalLen = msgLen + paddingLen;
	
	uint8_t *pMsg = (uint8_t*)malloc(totalLen);
	if (NULL == pMsg)
	{
		return ERT_MallocFail;
	}
	
	memcpy(pMsg, pPlainMsg, msgLen);
	memset(pMsg+msgLen, paddingLen, paddingLen);
	
	*pOutLen = totalLen<<1;
	
	ret = SECP_PubKeyEncrypt(pSecpPubKey, pOut, pOutLen, pMsg, totalLen);	//security_chip_api
	if (RT_OK != ret)
	{
		if (NULL != pMsg)
		{
			free(pMsg);
		}
		return ERT_SecpEncryptFail;
	}
	
	if (NULL != pMsg)
	{
		free(pMsg);
	}
	
	return emRet;
}

STONE_ECDSA_EXT emRetType stone_secp_decrypt(SECP_PriKey* pSecpPrvKey,  
		UINT8 *pEncryptMsg, UINT32 msgLen, UINT8 *pOut, UINT32 *pOutLen)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;
	
	if (msgLen & 127)
	{
		return ERT_FuncParamInvalid;
	}
		
	*pOutLen = msgLen>>1;
	ret = SECP_PriKeyDecrypt(pSecpPrvKey, pOut, pOutLen, pEncryptMsg, msgLen);	//security_chip_api
	if (RT_OK != ret)
	{
		return ERT_SecpDecryptFail;
	}
	
	*pOutLen -= pOut[(*pOutLen)-1];
	
	return emRet;
}

STONE_ECDSA_EXT emRetType stone_ED25519_sign(UINT8 *pMsg, UINT32 msgLen, 
		ED25519_PriKey* pEd25519PriKey, ED25519_PubKey* pEd25519PubKey, UINT8 *pResult)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;
	
	do
	{
		ret = ED25519_sign(pMsg, msgLen, pEd25519PriKey, pEd25519PubKey, pResult);	//security_chip_api
		if (RT_OK != ret)
		{
			return ERT_ED25519SignFail;
		}
	}while(!is_canonical(pResult));

	return emRet;
}

STONE_ECDSA_EXT emRetType stone_ED25519_verify(UINT8 *pMsg, UINT32 msgLen, 
		ED25519_PubKey* pEd25519PubKey, UINT8 *pResult)
{
	UINT8 ret = 0;
	emRetType emRet = ERT_OK;

	ret = ED25519_verify(pMsg, msgLen, pEd25519PubKey, pResult);	//security_chip_api
	if (RT_OK != ret)
	{
		return ERT_ED25519VerifyFail;
	}
	
	return emRet;
}
/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
