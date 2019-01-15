/**@NEW FILE***************************************************************************************
* @filename: StoneKeys.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/

/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_KEYS_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneKeys.h"
#include "SecurityChipAPI.h"
#include "StoneRandom.h"
#include "StoneStorage.h"
#include "StoneUtil.h"
#include "RipeMD160.h"
#include "base58.h"
#include "StoneCKD.h"
#include "StoneHDW.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/*STONE_KEYS_EXT const UINT32 gcu32_secp256k1_n[8] = {
		0xD0364141, 0xBFD25E8C, 0xAF48A03B, 0xBAAEDCE6, 
		0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};*/	//ECC_secp256k1_n
STONE_KEYS_EXT const UINT8 gcu8_secp256k1_n[32] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 
		0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B, 
		0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41};	//ECC_secp256k1_n
/*STONE_KEYS_EXT const UINT32 gcu32_secp256k1_n_half[8] = {
		0x681B20A1, 0xDFE92F46, 0x57A4501D, 0x5D576E73, 
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF};	//ECC_secp256k1_n half+1
STONE_KEYS_EXT const UINT8 gcu8_secp256k1_n_half[32] = {
		0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0x5D, 0x57, 0x6E, 0x73, 0x57, 0xA4, 0x50, 0x1D, 
		0xDF, 0xE9, 0x2F, 0x46, 0x68, 0x1B, 0x20, 0xA1};	//ECC_secp256k1_n half+1
STONE_KEYS_EXT const UINT32 gcu32_secp256k1_p[8] = {
		0xFFFFFC2F, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};	//ECC_secp256k1_p
STONE_KEYS_EXT const UINT8 gcu8_secp256k1_p[32] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
		0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFC, 0x2F};*/	//ECC_secp256k1_p	
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
static emRetType PBKDF2_HMAC_SHA512(uint8_t *pPassword, uint32_t passwordLen,
						uint8_t *pSalt, uint32_t saltLen,
						uint32_t iterC, uint8_t *pOut, int32_t outLen);

/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
static void stone_keys_set_hdpath_ver(uint8_t *pStrTmp, stHDPathType *pstHDPath)
{
	if ('m' == pStrTmp[0])
	{
		pstHDPath->verBytes = SF_VB_INT_MNET_PRV;
	}
	else if ('M' == pStrTmp[0])
	{
		pstHDPath->verBytes = SF_VB_INT_MNET_PUB;
	}
}

static emRetType stone_keys_skip_non_numeric(uint8_t *pStrTmp, uint32_t strLen, uint32_t *pIndex)
{
	emRetType emRet = ERT_OK;

	/*skip non-numeric characters*/
	while (!isdigit(pStrTmp[*pIndex])){(*pIndex)++;}
	if ((*pIndex) >= strLen)
	{
		if (NULL != pStrTmp)
		{
			free(pStrTmp);
		}
		return ERT_STR_END;
	}

	return emRet;
}

static emRetType stone_keys_check_digit_len(uint8_t *pStrTmp, uint32_t *pIndex)
{
	emRetType emRet = ERT_OK;
	uint32_t count = 0;

	while (isdigit(pStrTmp[*pIndex]))
	{
		(*pIndex)++;
		if (count++ > 10)
		{
			if (NULL != pStrTmp)
			{
				free(pStrTmp);
			}
			return ERT_FuncParamInvalid;
		}
	}

	return emRet;
}

static emRetType stone_keys_check_harden(uint8_t *pStrTmp, uint32_t *pIndex, stHDPathType *pstHDPath)
{
	emRetType emRet = ERT_OK;
	char cApostrophe = '\'';

	if (cApostrophe == pStrTmp[*pIndex])
	{
		(*pIndex)++;
		if (pstHDPath->value[pstHDPath->depth] < 0x80000000)
		{
			pstHDPath->value[pstHDPath->depth] += 0x80000000;
		}
		else
		{
			if (NULL != pStrTmp)
			{
				free(pStrTmp);
			}
			return ERT_FuncParamInvalid;
		}
	}

	return emRet;
}

STONE_KEYS_EXT emRetType stone_keys_str_to_hdpath(uint8_t *pStr, uint32_t strLen, stHDPathType *pstHDPath)
{
	emRetType emRet = ERT_OK;
	char cSlash = '/';
	uint32_t index = 0;
	uint8_t *pStrTmp = NULL;
	
	//HDPath max len: "m/2147483647'/2147483647'/2147483647'/2147483647'/2147483647'"
	if ((NULL == pStr)|| (('m' != pStr[0]) && ('M' != pStr[0])) || (0 == strLen) || (strLen > 61))
	{
		return ERT_FuncParamInvalid;
	}
	
	pStrTmp = (uint8_t*)malloc(strLen+1);
	if (NULL == pStrTmp)
	{
		return ERT_MallocFail;
	}
	memcpy(pStrTmp, pStr, strLen);
	pStrTmp[strLen]  = '\0';
	
	stone_keys_set_hdpath_ver(pStrTmp, pstHDPath);
	pstHDPath->depth = 0;
	index++;
	
	while ((index < strLen) && (cSlash == pStrTmp[index++]) && (pstHDPath->depth <= 5))
	{
		emRet = stone_keys_skip_non_numeric(pStrTmp, strLen, &index);
		if (ERT_STR_END == emRet) 
		{
			return ERT_OK;
		}

		pstHDPath->value[pstHDPath->depth] = str_to_u32((const char*)pStrTmp+index);

		emRet = stone_keys_check_digit_len(pStrTmp, &index);
		if (ERT_OK != emRet) 
		{
			return emRet;
		}
		emRet = stone_keys_check_harden(pStrTmp, &index, pstHDPath);
		if (ERT_OK != emRet) 
		{
			return emRet;
		}
		
		pstHDPath->depth++;
	}
	
	if (NULL != pStrTmp)
	{
		free(pStrTmp);
	}
	
	return emRet;
}

STONE_KEYS_EXT emRetType stone_keys_check_key_valid(uint8_t *pKey, uint32_t keyLen)
{
	if (32 != keyLen)
	{
		return ERT_InvalidKey;
	}
	
	if (sequence_all_zero(pKey, keyLen))
	{
		return ERT_InvalidKey;
	}
	
	if (sequence_compare_bit8(pKey, gcu8_secp256k1_n, keyLen)>=0)
	{
		return ERT_InvalidKey;
	}
	
	return ERT_OK;
}

STONE_KEYS_EXT void stone_keys_pubkey_compress(SECP_PubKey *pPubKey, SECP_PubKeyCompressed *pPubKeyC)
{
	if (pPubKey->Y[31] & 0x01)
	{
		pPubKeyC->key[0] = 0x03;
	}
	else
	{
		pPubKeyC->key[0] = 0x02;
	}
	memcpy(pPubKeyC->key+1, pPubKey->X, 32);
}

STONE_KEYS_EXT emRetType stone_keys_get_pubkey(SECP_PriKey *pPriKey, SECP_PubKey *pPubKey)
{
	emRetType emRet = ERT_OK;
	uint8_t ret = 0;
	
	ret = SECP_GenKey(pPriKey, pPubKey, 256, 1);
	if(RT_OK != ret)
	{
		return ERT_GenKeyFail;
	}
	
	return emRet;
}

STONE_KEYS_EXT emRetType stone_keys_get_compressed_pubkey(SECP_PriKey *pPriKey, SECP_PubKeyCompressed *pPubKeyC)
{
	emRetType emRet = ERT_OK;
	uint8_t ret = 0;
	uint8_t bufPubKey[64] = {0};
	SECP_PubKey secpPubKey;
	
	secpPubKey.X = bufPubKey;
	secpPubKey.Y = bufPubKey+32;
	
	ret = SECP_GenKey(pPriKey, &secpPubKey, 256, 1);
	if(RT_OK != ret)
	{
		return ERT_GenKeyFail;
	}
	
	stone_keys_pubkey_compress(&secpPubKey, pPubKeyC);
	
	return emRet;
}

STONE_KEYS_EXT void stone_keys_gen_key_fingerprint(SECP_PubKeyCompressed *psecpPubKeyC, 
		uint8_t *pFingerPrint, uint8_t fingerPrintLen)
{
	UINT8 hash256[SHA256_LEN] = {0};
	UINT8 RPMD160[RPMD160_LEN] = {0};
	
	SHA256(psecpPubKeyC->key, 33, hash256);
	
	RipeMD160(hash256, SHA256_LEN, RPMD160);
	
	memcpy(pFingerPrint, RPMD160, fingerPrintLen);
}

STONE_KEYS_EXT void stone_keys_gen_child_number(uint8_t *pChildNum, uint32_t u32ChildNum)
{
	u32_to_buf(pChildNum, u32ChildNum);
}

STONE_KEYS_EXT emRetType stone_keys_gen_entropy(uint8_t *bufEntropy, 
		emEntropyBitsType emEBits, uint8_t needCKS)
{
	emRetType emRet = ERT_OK;
	uint16_t bits = emEBits;
	uint8_t *pRandom = bufEntropy;
	uint16_t randomLen = bits >> 3;
	uint16_t checkSumLen = 1;
	uint8_t bufHash256[32] = {0};
	
	stone_get_strong_random(pRandom, randomLen);
	
	if (needCKS)
	{
		SHA256(pRandom, randomLen, bufHash256);
		
		memcpy(pRandom+randomLen, bufHash256, checkSumLen);
	}
	
	return emRet;
}

/*
*BIP39:
*To create a binary seed from the mnemonic, we use the PBKDF2 function 
*with a mnemonic sentence (in UTF-8 NFKD) used as the password 
*and the string "mnemonic" + passphrase (again in UTF-8 NFKD) used as the salt. 
*The iteration count is set to 2048 and HMAC-SHA512 is used as the pseudo-random function. 
*The length of the derived key is 512 bits (= 64 bytes).
*/
emRetType PBKDF2_HMAC_SHA512(uint8_t *pPassword, uint32_t passwordLen,
						uint8_t *pSalt, uint32_t saltLen,
						uint32_t iterC, uint8_t *pOut, int32_t outLen)
{
	uint32_t i = 0, j = 0;
	uint8_t *pKey = pPassword;
	uint32_t keyLen = passwordLen;
	char *pPassphrase_prefix = PASSPHRASE_PREFIX;
	uint8_t *pText = NULL;
	uint32_t textLen = 0;
	
	uint8_t bufSHA512Key[SHA512_LEN] = {0x00};
	uint8_t bufSHA512[SHA512_LEN] = {0x00};
	uint8_t bufSHA512Tmp[SHA512_LEN] = {0x00};
	uint32_t I = 1;
	uint8_t bufI[4] = {0x00};
	uint32_t outOffset = 0;
	
 	memset(bufSHA512, 0x00, SHA512_LEN);
	memset(bufSHA512Tmp, 0x00, SHA512_LEN);
	textLen = strlen(pPassphrase_prefix);
	pText = (uint8_t*)malloc(textLen + saltLen + 4);
	if (NULL == pText)
	{
		return ERT_MallocFail;
	}
	memcpy(pText, pPassphrase_prefix, textLen);
	if (saltLen > 0)
	{
		memcpy(pText+textLen, pSalt, saltLen);
		textLen += saltLen;
	}
	
	if (keyLen > 128)
	{
		SHA512(pKey, keyLen, bufSHA512Key);
		pKey = bufSHA512Key;
		keyLen = SHA512_LEN;
	}
	
	while(outLen > 0)
	{
		u32_to_buf(bufI, I);
		memcpy(pText+textLen, bufI, 4);
		
		HMAC_SHA512(pText, textLen + 4, pKey, keyLen, bufSHA512Tmp);

		memcpy(bufSHA512, bufSHA512Tmp, SHA512_LEN);
		for (i=1; i<iterC; i++)
		{
			security_chip_api_wdt_clr();
			HMAC_SHA512(bufSHA512Tmp, SHA512_LEN, pKey, keyLen, bufSHA512Tmp);
			buf_xor(bufSHA512, bufSHA512Tmp, SHA512_LEN);
		}
		memcpy(pOut+outOffset, bufSHA512, outLen>=SHA512_LEN?SHA512_LEN:outLen);
		outOffset += SHA512_LEN;
		outLen -= SHA512_LEN;
		I++;
	}
	if (NULL != pText)
	{
		free(pText);
	}
	
	return ERT_OK;
}

STONE_KEYS_EXT emRetType stone_keys_gen_seed_bip39(uint8_t *pMnemonic, uint32_t mnemonicLen, 
		uint8_t *pPassphrase, uint32_t passphraseLen, uint8_t *pSeed, int32_t seedLen)
{
	emRetType emRet = ERT_OK;
	
	SCM_SetSysClk(SYS_CLK_48M);
	emRet = PBKDF2_HMAC_SHA512(pMnemonic, mnemonicLen, pPassphrase, passphraseLen, 
			2048, pSeed, seedLen);
	SCM_SetSysClk(SYS_CLK_12M);
	
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	return emRet;
}

STONE_KEYS_EXT void stone_keys_gen_root_seed_bip32(uint8_t *pSeed, uint32_t seedLen, 
		uint8_t *pKey, uint32_t keyLen, uint8_t *pRootSeed)
{
	UINT8 *pDefaultKey = (UINT8*)"Bitcoin seed";
	UINT32 defaultKeyLen = strlen((const char*)pDefaultKey);
	
	if ((NULL == pKey) || (0 == keyLen))
	{
		pKey = pDefaultKey;
		keyLen = defaultKeyLen;
	}
	HMAC_SHA512(pSeed, seedLen, pKey, keyLen, pRootSeed);
}

STONE_KEYS_EXT emRetType stone_keys_gen_master_key_bip32(uint8_t *pSeed, uint32_t seedLen, 
		uint8_t *pKey, uint32_t keyLen, SECP_PriKey *pPrvKey, uint8_t *pChainCode)
{
	emRetType emRet = ERT_OK;
	uint8_t bufRootSeed[SHA512_LEN] = {0};
	
	stone_keys_gen_root_seed_bip32(pSeed, seedLen, pKey, keyLen, bufRootSeed);
	emRet = stone_keys_check_key_valid(bufRootSeed, 32);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	memcpy(pPrvKey->PrivateKey, bufRootSeed, 32);
	memcpy(pChainCode, bufRootSeed + 32, 32);
	
	return emRet;
}

STONE_KEYS_EXT emRetType stone_keys_get_master_key_pairs(SECP_PriKey *pMasterPrvKey, 
		uint8_t *pMasterChainCode)
{
	emRetType emRet = ERT_OK;
	uint8_t bufSeed[SEED_LEN] = {0x00};
	
	emRet = stone_storage_security_safe_read(bufSeed, SEED_LEN, SF_ADDR_SEED, SF_ADDR_SEED_CKS);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	return stone_keys_gen_master_key_bip32(bufSeed, SEED_LEN, (UINT8*)"Bitcoin seed", 
			strlen((const char*)"Bitcoin seed"), pMasterPrvKey, pMasterChainCode);
}

STONE_KEYS_EXT uint8_t* stone_keys_pubKey_to_address(SECP_PubKey *psecpPubKey, uint32_t *pAddrLen)
{
	UINT8 hash160[25] = {0x00};
	UINT8 bufKey[64] = {0x00};
	
	memcpy(bufKey, psecpPubKey->X, 32);
	memcpy(bufKey+32, psecpPubKey->Y, 32);
	
	stone_util_gen_hash160(bufKey, sizeof(bufKey), hash160+1, 20);
	stone_util_gen_sha256sha256(hash160, 21, hash160+21, 4);
	
	return EncodeBase58(hash160, sizeof(hash160), pAddrLen);
}

STONE_KEYS_EXT uint8_t* stone_keys_pubKeyC_to_addressC(SECP_PubKeyCompressed *psecpPubKeyC, 
		uint32_t *pAddrLen)
{
	UINT8 hash160[25] = {0x00};

	stone_util_gen_hash160(psecpPubKeyC->key, 33, hash160+1, 20);
	stone_util_gen_sha256sha256(hash160, 21, hash160+21, 4);
	
	return EncodeBase58(hash160, sizeof(hash160), pAddrLen);
}

STONE_KEYS_EXT uint8_t* stone_keys_pubKey_to_addressC(SECP_PubKey *psecpPubKey, uint32_t *pAddrLen)
{
	uint8_t bufTmpPubKeyC[33];
	SECP_PubKeyCompressed secpPubKeyC;
	
	secpPubKeyC.key = bufTmpPubKeyC;
	
	stone_keys_pubkey_compress(psecpPubKey, &secpPubKeyC);
	
	return stone_keys_pubKeyC_to_addressC(&secpPubKeyC, pAddrLen);
}

STONE_KEYS_EXT uint8_t* stone_keys_prvkey_to_WIF(SECP_PriKey *psecpPrvKey, uint32_t *pWIFLen)
{
	UINT8 bufData[37] = {0};
	
	bufData[0] = 0x80;
	memcpy(bufData + 1, psecpPrvKey->PrivateKey, 32);
	
	stone_util_gen_sha256sha256(bufData, 33, bufData + 33, 4);
	
	return EncodeBase58(bufData, sizeof(bufData), pWIFLen);
}

STONE_KEYS_EXT uint8_t* stone_keys_prvkey_to_compressed_WIF(SECP_PriKey *psecpPrvKey, 
		uint32_t *pWIFLen)
{
	UINT8 bufData[38] = {0};
	
	bufData[0] = 0x80;
	memcpy(bufData + 1, psecpPrvKey->PrivateKey, 32);
	bufData[33] = 0x01;
	
	stone_util_gen_sha256sha256(bufData, 34, bufData + 34, 4);
	
	return EncodeBase58(bufData, sizeof(bufData), pWIFLen);
}

STONE_KEYS_EXT emRetType stone_keys_get_extended_key(uint32_t version, uint8_t depth, 
		uint8_t *pFingerPrint, uint8_t *pChildNum,
		uint8_t *pChainCode, uint8_t *pKey, 
		uint8_t **pExtKey, uint32_t *extKeyLen)
{	
	emRetType emRet = ERT_OK;
	stExtKeyType stExtKey;
	uint8_t *pExtKeyTmp = NULL;
	uint8_t bufPubKeyC[33] = {0};
	SECP_PriKey secpPriKey;
	SECP_PubKeyCompressed secpPubKeyC;
	
	u32_to_buf(stExtKey.version, version);
	stExtKey.depth = depth;
	memcpy(stExtKey.fingerPrint, pFingerPrint, 4);
	memcpy(stExtKey.childNumber, pChildNum, 4);
	memcpy(stExtKey.chainCode, pChainCode, 32);
	
	switch(version)
	{
		case SF_VB_INT_MNET_PRV:
		case SF_VB_INT_TNET_PRV:
		{
			stExtKey.key[0] = 0x00;
			memcpy(stExtKey.key+1, pKey, 32);
			break;
		}
		case SF_VB_INT_MNET_PUB:
		case SF_VB_INT_TNET_PUB:
		{
			secpPriKey.PrivateKey = pKey;
			secpPubKeyC.key = bufPubKeyC;
			stone_keys_get_compressed_pubkey(&secpPriKey, &secpPubKeyC);

			memcpy(stExtKey.key, secpPubKeyC.key, 33);
			break;
		}
	}
	stone_util_gen_sha256sha256((uint8_t*)&stExtKey, 
			sizeof(stExtKeyType)-sizeof(stExtKey.checkSum), stExtKey.checkSum, 4);
	
	pExtKeyTmp = EncodeBase58((uint8_t*)&stExtKey, sizeof(stExtKeyType), extKeyLen);
	
	*pExtKey = pExtKeyTmp;
	
	return emRet;
}

STONE_KEYS_EXT emRetType stone_keys_derive_key(stHDPathType *pstHDPathParam, 
		SECP_PriKey *pPrvKey, SECP_PubKey *pPubKey,
        uint8_t **pExtKey, uint32_t *pExtKeyLen)
{
	emRetType emRet = ERT_OK;
	uint8_t i = 0;
	stHDPathType *pstPath = pstHDPathParam;
	uint8_t bufParentPrvKey[32] = {0};
	uint8_t bufParentChainCode[32] = {0};
	uint8_t bufChildPrvKey[32] = {0};
	uint8_t bufChildChainCode[32] = {0};
	uint8_t bufPubKeyC[33] = {0};
	uint8_t bufFingerPrint[4] = {0};
	uint8_t bufChildNum[4] = {0};
	SECP_PriKey secpParentPriKey;
	SECP_PriKey secpChildPriKey;
	SECP_PubKeyCompressed secpPubKeyC;

	secpParentPriKey.PrivateKey = bufParentPrvKey;
	secpChildPriKey.PrivateKey = bufChildPrvKey;
	secpPubKeyC.key = bufPubKeyC;
	
	emRet = stone_keys_get_master_key_pairs(&secpParentPriKey, bufParentChainCode);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	for (i=0; i<pstPath->depth; i++)
	{
		emRet = stone_keys_get_compressed_pubkey(&secpParentPriKey, &secpPubKeyC);
		if (ERT_OK != emRet)
		{
			return emRet;
		}
		
		//BIP32: In case parse256(IL) �� n or ki = 0, the resulting key is invalid, 
		//and one should proceed with the next value for i. 
		//(Note: this has probability lower than 1 in 2^127.)
		emRet = stone_CKD_prv2prv(&secpParentPriKey, bufParentChainCode, pstPath->value[i], 
				&secpChildPriKey, bufChildChainCode);
		if (ERT_OK != emRet)
		{
			return emRet;
		}
		memcpy(secpParentPriKey.PrivateKey, secpChildPriKey.PrivateKey, 32);
		memcpy(bufParentChainCode, bufChildChainCode, 32);
		stone_keys_gen_key_fingerprint(&secpPubKeyC, bufFingerPrint, sizeof(bufFingerPrint));
		stone_keys_gen_child_number(bufChildNum, pstPath->value[i]);
	}
	
	memcpy(pPrvKey->PrivateKey, secpParentPriKey.PrivateKey, 32);
	emRet = stone_keys_get_pubkey(&secpParentPriKey, pPubKey);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	emRet = stone_keys_get_extended_key(pstPath->verBytes, pstPath->depth, bufFingerPrint, bufChildNum, 
			bufParentChainCode, secpParentPriKey.PrivateKey, pExtKey, pExtKeyLen);
	
	return emRet;
}
/**@END SECTION**/

/**@END OF FILE***********************************************************************************/
