/**@NEW FILE***************************************************************************************
* @filename: StoneCKD.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_CKD_GLOBAL
/**@END SECTION***********************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneCKD.h"
#include "SecurityChipAPI.h"
#include "StoneUtil.h"
#include "StoneKeys.h"
#include "StoneComm.h"
/**@END SECTION***********************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**@END SECTION***********************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
static void stone_CKD_get_child_chaincode(uint8_t *bufHMACSHA512, uint8_t *bufChildChainCode);
static void stone_CKD_get_child_prvkey(SECP_PriKey *pParentPrvKey, uint8_t *bufHMACSHA512, 
		SECP_PriKey *pChildPrvKey);
static emRetType stone_CKD_get_child_pubkey_point(SECP_PubKey *pParentPubKey, uint8_t *bufHMACSHA512, 
		Ep_Curve *pEC, Ep_Point *pChildPubKeyPoint);
/**@END SECTION***********************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
STONE_CKD_EXT void pubkey_to_point(SECP_PubKey *pPubKey, Ep_Point *pPoint)
{
	uint8_t i=0;
	uint8_t *pDatX = NULL;
	uint8_t *pDatY = NULL;
	uint8_t offset = 0;
	
	for (i=0; i<MAX_DIG_LEN; i++)
	{
		offset = (MAX_DIG_LEN-1-i) << 2;
		pDatX = (pPubKey->X + offset);
		pDatY = (pPubKey->Y + offset);
		pPoint->x[i] = ((*pDatX)<<24)|((*(pDatX+1))<<16)|((*(pDatX+2))<<8)|(*(pDatX+3));
		pPoint->y[i] = ((*pDatY)<<24)|((*(pDatY+1))<<16)|((*(pDatY+2))<<8)|(*(pDatY+3));
	}
}

STONE_CKD_EXT void point_to_pubkey(Ep_Point *pPoint, SECP_PubKey *pPubKey)
{
	uint8_t i=0;
	uint8_t offset = 0;
	
	for (i=0; i<MAX_DIG_LEN; i++)
	{
		offset = (MAX_DIG_LEN-1-i) << 2;
		pPubKey->X[offset]		= (uint8_t)(pPoint->x[i]>>24);
		pPubKey->X[offset + 1]	= (uint8_t)(pPoint->x[i]>>16);
		pPubKey->X[offset + 2]	= (uint8_t)(pPoint->x[i]>>8);
		pPubKey->X[offset + 3]	= (uint8_t)(pPoint->x[i]);
		pPubKey->Y[offset]		= (uint8_t)(pPoint->y[i]>>24);
		pPubKey->Y[offset + 1]	= (uint8_t)(pPoint->y[i]>>16);
		pPubKey->Y[offset + 2]	= (uint8_t)(pPoint->y[i]>>8);
		pPubKey->Y[offset + 3]	= (uint8_t)(pPoint->y[i]);
	}
}

STONE_CKD_EXT emRetType stone_CKD_prv2prv_hmac_data(SECP_PriKey *pPriKey, 
		uint32_t index, uint8_t *dataOut)
{
	emRetType emRet = ERT_OK;
	uint8_t bufTmpPubKeyC[33];
	SECP_PubKeyCompressed secpPubKeyC;
	
	secpPubKeyC.key = bufTmpPubKeyC;

	if (index >= 0x80000000)	//harden child
	{
		dataOut[0] = 0x00;
		memcpy(dataOut + 1, pPriKey->PrivateKey, 32);
	}
	else	//normal child
	{
		emRet = stone_keys_get_compressed_pubkey(pPriKey, &secpPubKeyC);
		if(ERT_OK != emRet)
		{
			return emRet;
		}
		
		memcpy(dataOut, secpPubKeyC.key, 33);
	}
	
	u32_to_buf(dataOut+33, index);
	
	return emRet;
}

STONE_CKD_EXT uint8_t stone_CKD_pub2pub_hmac_data(SECP_PubKey *pPubKey, 
		uint32_t index, uint8_t *dataOut)
{
	uint8_t ret = 0;
	uint8_t bufTmpPubKeyC[33];
	SECP_PubKeyCompressed secpPubKeyC;
	
	if (index >= 0x80000000)	//harden child
	{
		ret = 1;
	}
	else	//normal child
	{
		secpPubKeyC.key = bufTmpPubKeyC;
		
		stone_keys_pubkey_compress(pPubKey, &secpPubKeyC);
		
		memcpy(dataOut, secpPubKeyC.key, 33);
		
		u32_to_buf(dataOut+33, index);
	}		
	
	return ret;
}

static void stone_CKD_get_child_chaincode(uint8_t *bufHMACSHA512, uint8_t *bufChildChainCode)
{
	memcpy(bufChildChainCode, bufHMACSHA512 + 32, 32);
}

static void stone_CKD_get_child_prvkey(SECP_PriKey *pParentPrvKey, uint8_t *bufHMACSHA512, 
		SECP_PriKey *pChildPrvKey)
{
	uint8_t ret = RT_OK;
	uint8_t bufIL[32] = {0};
	uint32_t a[8] = {0};
	uint32_t b[8] = {0};
	uint32_t sum[9] = {0};
	uint32_t n[8] = {	0xD0364141, 0xBFD25E8C, 0xAF48A03B, 0xBAAEDCE6, 
						0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };	//ECC_secp256k1_n
	uint32_t div[8] = {0};
	uint32_t ki[8] = {0};

	memcpy(bufIL, bufHMACSHA512, 32);
		
	if (sequence_compare_bit8(bufIL, pParentPrvKey->PrivateKey, 32) >= 0)
	{
		sequence32B_to_BN256b(bufIL, a);
		sequence32B_to_BN256b(pParentPrvKey->PrivateKey, b);
	}
	else
	{
		sequence32B_to_BN256b(bufIL, b);
		sequence32B_to_BN256b(pParentPrvKey->PrivateKey, a);
	}
	
	ret = BN_Add(sum, a, 8, b, 8);
	if (0 == ret)
	{
		BN_Div(div, ki, sum, 8, n, 8);
	}
	else if (1 == ret)
	{
		sum[8] = 0x00000001;
		BN_Div(div, ki, sum, 9, n, 8);
	}
	
	BN256b_to_sequence32B(ki, pChildPrvKey->PrivateKey);
}

STONE_CKD_EXT emRetType stone_CKD_prv2prv(SECP_PriKey *pParentPrvKey, uint8_t *bufChainCode, 
		uint32_t index, SECP_PriKey *pChildPrvKey, uint8_t *bufChildChainCode)
{
	emRetType emRet = ERT_OK;
	uint8_t bufHmacTmp[37] = {0};
	uint8_t bufSHA512Tmp[64] = {0};
	uint8_t bufChainCodeTmp[32] = {0};
	
	while (1)
	{
		memcpy(bufChainCodeTmp, bufChainCode, 32);
				
		emRet = stone_CKD_prv2prv_hmac_data(pParentPrvKey, index, bufHmacTmp);
		if (ERT_OK != emRet)
		{
			return ERT_CKD_Fail;
		}

		HMAC_SHA512(bufHmacTmp, sizeof(bufHmacTmp), bufChainCodeTmp, 32, bufSHA512Tmp);

		if (sequence_compare_bit8(bufSHA512Tmp, gcu8_secp256k1_n, 32)>=0)
		{
			index++;
			continue;
		}

		stone_CKD_get_child_prvkey(pParentPrvKey, bufSHA512Tmp, pChildPrvKey);
			
		if (sequence_all_zero(pChildPrvKey->PrivateKey, 32))
		{
			index++;
			continue;
		}
		
		stone_CKD_get_child_chaincode(bufSHA512Tmp, bufChildChainCode);
				
		return emRet;
	}
}

static emRetType stone_CKD_get_child_pubkey_point(SECP_PubKey *pParentPubKey, uint8_t *bufHMACSHA512, 
		Ep_Curve *pEC, Ep_Point *pChildPubKeyPoint)
{
	emRetType emRet = ERT_OK;
	uint8_t ret = RT_OK;
	uint8_t bufTmpPrvKey[32] = {0};
	uint8_t bufTmpPubKeyX[32] = {0};
	uint8_t bufTmpPubKeyY[32] = {0};
	SECP_PriKey secpTmpPriKey;
	SECP_PubKey secpTmpPubKey;
	Ep_Point Q,P;

	secpTmpPriKey.PrivateKey = bufTmpPrvKey;
	secpTmpPubKey.X = bufTmpPubKeyX;
	secpTmpPubKey.Y = bufTmpPubKeyY;
		
	memcpy(secpTmpPriKey.PrivateKey, bufHMACSHA512, 32);
	
	emRet = stone_keys_get_pubkey(&secpTmpPriKey, &secpTmpPubKey);
	if(ERT_OK != emRet)
	{
		return ERT_GenKeyFail;
	}
	
	pubkey_to_point(pParentPubKey, &Q);
	pubkey_to_point(&secpTmpPubKey, &P);

	ret = Ep_Point_Add(EC, pChildPubKeyPoint, &Q, &P); //pChildPubKeyPoint = Q+P
	if(ret != RT_OK)
	{
		return ERT_CKD_Fail;
	}
	
	return emRet;
}

STONE_CKD_EXT emRetType stone_CKD_pub2pub(SECP_PubKey *pParentPubKey, uint8_t *bufChainCode, 
		uint32_t index, SECP_PubKey *pChildPubKey, uint8_t *bufChildChainCode)
{
	emRetType emRet = ERT_OK;
	uint8_t ret = RT_OK;
	uint8_t bufHmacTmp[37] = {0};
	uint8_t bufSHA512Tmp[64] = {0};
	Ep_Curve *EC;
	Ep_Point childPubKeyPoint;
	
	while (1)
	{
		ret = stone_CKD_pub2pub_hmac_data(pParentPubKey, index, bufHmacTmp);
		if (RT_OK != ret)
		{
			return ERT_CKD_Fail;
		}
		
		HMAC_SHA512(bufHmacTmp, sizeof(bufHmacTmp), bufChainCode, 32, bufSHA512Tmp);
		
		if (sequence_compare_bit8(bufSHA512Tmp, gcu8_secp256k1_n, 32)>=0)
		{
			index++;
			continue;
		}
		
		ret = InitCurveSecp(256, &EC);
		if (RT_OK != ret)
		{
			return ERT_CKD_Fail;
		}
		
		emRet = stone_CKD_get_child_pubkey_point(pParentPubKey, bufSHA512Tmp, EC, &childPubKeyPoint);
		if (ERT_OK != emRet)
		{
			return emRet;
		}

		ret = Ep_Is_Zero(EC, &childPubKeyPoint);
		if (RT_OK != ret)
		{
			index++;
			continue;
		}
		
		ret = Ep_On_Curve(EC, &childPubKeyPoint);
		if (RT_OK != ret)
		{
			index++;
			continue;
		}
		
		point_to_pubkey(&childPubKeyPoint, &pChildPubKey);
		stone_CKD_get_child_chaincode(bufSHA512Tmp, bufChildChainCode);
		
		return emRet;
	}
}

/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
