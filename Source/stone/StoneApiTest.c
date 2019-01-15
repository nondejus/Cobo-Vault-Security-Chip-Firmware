/**@NEW FILE***************************************************************************************
* @filename: StoneApiTest.c
* @description:
* @author&data: Andrew Zhang @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_API_TEST_GLOBAL
/**@END SECTION**/

#ifndef STONE_API_TEST_ENABLE

/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneApiTest.h"
#include "StoneUtil.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
stHDPathType stHDPathTV = 
{
		/*.verBytes = */0x00000000,
		/*.value[] = */{ 0x00 },
		/*.depth = */0x00
};

stCKDTestVectorType stCKDTestVectors[]=
{
	{
		/*.pSeed = */(uint8_t*)"\x01\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
		/*.pStrHDPath = */(uint8_t*)"m/0'/1/2'/2/1000000000",
		/*.pstHDPath = */&stHDPathTV,
		/*.pExtKey = */(uint8_t*)"xprvA3B4gJVznc6JWUNwu2UxoDULNjQrSba5UoEdLPTYUVbqB1Z9hx4uQ6NkAZQEi1gmKC5YALNhUg562V3aDbZchtUsbjTvdA6XS25zBtARgSp"
	},
	{
		/*.pSeed = */(uint8_t*)"\xFF\xFC\xF9\xF6\xF3\xF0\xED\xEA\xE7\xE4\xE1\xDE\xDB\xD8\xD5\xD2\xCF\xCC\xC9\xC6\xC3\xC0\xBD\xBA\xB7\xB4\xB1\xAE\xAB\xA8\xA5\xA2\x9F\x9C\x99\x96\x93\x90\x8D\x8A\x87\x84\x81\x7E\x7B\x78\x75\x72\x6F\x6C\x69\x66\x63\x60\x5D\x5A\x57\x54\x51\x4E\x4B\x48\x45\x42",
		/*.pStrHDPath = */(uint8_t*)"M/0/2147483647'/1/2147483646'/2",
		/*.pstHDPath = */&stHDPathTV,
		/*.pExtKey = */(uint8_t*)"xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9rXpVGyy3bdW6EEgAtqt",
	},
	{
		/*.pSeed = */(uint8_t*)"\x4B\x38\x15\x41\x58\x3B\xE4\x42\x33\x46\xC6\x43\x85\x0D\xA4\xB3\x20\xE4\x6A\x87\xAE\x3D\x2A\x4E\x6D\xA1\x1E\xBA\x81\x9C\xD4\xAC\xBA\x45\xD2\x39\x31\x9A\xC1\x4F\x86\x3B\x8D\x5A\xB5\xA0\xD0\xC6\x4D\x2E\x8A\x1E\x7D\x14\x57\xDF\x2E\x5A\x3C\x51\xC7\x32\x35\xBE",
		/*.pStrHDPath = */(uint8_t*)"m/0'",
		/*.pstHDPath = */&stHDPathTV,
		/*.pExtKey = */(uint8_t*)"xprv9uPDJpEQgRQfDcW7BkF7eTya6RPxXeJCqCJGHuCJ4GiRVLzkTXBAJMu2qaMWPrS7AANYqdq6vcBcBUdJCVVFceUvJFjaPdGZ2y9WACViL4L"
	}
};

SECP_PriKey secpPriKey1 = {(UINT8*)"\xE2\x84\x12\x9C\xC0\x92\x25\x79\xA5\x35\xBB\xF4\xD1\xA3\xB2\x57\x73\x09\x0D\x28\xC9\x09\xBC\x0F\xED\x73\xB5\xE0\x22\x2C\xC3\x72"};
SECP_PriKey secpPriKey2 = {(UINT8*)"\x5C\x11\x41\xF6\x0E\xDD\x30\x95\x57\x95\x29\xDB\x7E\x88\xD9\x64\xCB\x0A\x9E\xC0\xF8\x14\xF6\xA1\x0C\xD5\xCB\xD7\x63\x07\x8A\x0C"};
stSigTestVectorType stSigTestVectors[] = 
{
	{
		/*.pSecpPriKey = */&secpPriKey1,
		/*.pHash = */(uint8_t*)"\xF9\x1D\xA2\x9D\x3D\x46\xA7\xCB\xEB\x41\x23\xA2\x4F\x95\x29\x29\x98\xCC\x82\x6F\x41\x92\x2D\x00\x7F\x51\x57\x2E\xF7\xB5\x42\xB7",
		/*.pSig = */(uint8_t*)"\x0B\x98\xBB\x0C\x25\xFB\x0B\x00\x33\x5D\x3E\x7B\x64\x7F\xAE\x04\xBE\x9C\x3A\x54\x4B\xED\xC6\xA4\x52\x6E\xBB\x91\x84\x1C\x32\x60\x65\x3A\xE5\x23\xA8\xD7\x55\x42\x74\xBA\xB1\x2E\x69\x24\x41\x2C\x06\x81\x6E\xEA\x19\x75\x65\x27\x37\x80\x78\x6C\xED\x19\x5F\x6D",
	},
	{
		/*.pSecpPriKey = */&secpPriKey1,
		/*.pHash = */(uint8_t*)"\xD6\x23\x79\x1C\xF7\xD0\x2A\xB0\x95\x49\x79\xE9\xA5\x2B\xBD\x6D\xD2\x94\x77\xD8\x6F\xE5\x97\x98\x37\x32\xD7\x5F\xB5\x46\x09\xD2",
		/*.pSig = */(uint8_t*)"\x63\x97\x5D\x1D\x71\xF8\xA2\x94\x95\x42\xAB\xC5\xE7\x41\xD1\x77\x00\xF7\xF9\x94\xB3\x5F\x42\x90\xDD\x8E\x92\xAB\xB8\x54\xA5\x76\x17\xD9\xEA\xD5\xBE\xA4\xD3\x34\xBD\x03\xB6\xA8\x74\xC8\x59\x6F\x3E\x69\xEB\xCB\x7B\x84\xF3\xF0\xA3\xB1\x0D\xD3\x09\x55\x67\x59",
	},
	{
		/*.pSecpPriKey = */&secpPriKey2,
		/*.pHash = */(uint8_t*)"\xF9\x1D\xA2\x9D\x3D\x46\xA7\xCB\xEB\x41\x23\xA2\x4F\x95\x29\x29\x98\xCC\x82\x6F\x41\x92\x2D\x00\x7F\x51\x57\x2E\xF7\xB5\x42\xB7",
		/*.pSig = */(uint8_t*)"\x39\x02\xC5\x9F\xF4\xA3\xDF\x13\x9D\xAA\x3F\x8F\x78\x26\x33\x22\xAF\x51\x80\x4B\xEB\x66\xF8\x2D\x03\x4B\x8C\x95\x5F\xA3\xE3\x2D\x7F\xB1\xE7\x3C\x68\x99\xD5\xE8\x79\xE9\xC2\xC3\xB9\xB1\xF7\x55\xBD\xB7\xB7\x77\xD6\x5A\x82\x64\x54\x29\x68\xB7\xA7\xA5\x58\x59",
	}
};
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
void stone_api_test_CKD(void)
{
	emRetType emRet = ERT_OK;
	uint8_t i = 0, j = 0;
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
	uint8_t *pExtKey = NULL;
	uint32_t extKeyLen = 0;
	
	secpParentPriKey.PrivateKey = bufParentPrvKey;
	secpChildPriKey.PrivateKey = bufChildPrvKey;
	secpPubKeyC.key = bufPubKeyC;
	
	printf("\r\n----CKD Vectors Test Start----\r\n");
	for (i=0; i<sizeof(stCKDTestVectors)/sizeof(stCKDTestVectorType); i++)
	{
		emRet = stone_keys_str_to_hdpath(stCKDTestVectors[i].pStrHDPath, 
				strlen((const char*)stCKDTestVectors[i].pStrHDPath), 
				stCKDTestVectors[i].pstHDPath);
		if (ERT_OK != emRet)
		{
			printf("Error, %s() failed with code = %d[%04X], depth=%d\r\n", __FUNCTION__, emRet, emRet, 
					stCKDTestVectors[i].pstHDPath->depth+1);
			return;
		}
		
		emRet = stone_keys_gen_master_key_bip32(stCKDTestVectors[i].pSeed, 
				strlen((const char*)stCKDTestVectors[i].pSeed), (UINT8*)"Bitcoin seed", 
				strlen((const char*)"Bitcoin seed"), &secpParentPriKey, bufParentChainCode);
		if (ERT_OK != emRet)
		{
			printf("Error, %s() failed with code = %d[%04X]\r\n", __FUNCTION__, emRet, emRet);
			return;
		}
		
		for (j=0; j<stCKDTestVectors[i].pstHDPath->depth; j++)
		{
			emRet = stone_keys_get_compressed_pubkey(&secpParentPriKey, &secpPubKeyC);
			if (ERT_OK != emRet)
			{
				printf("Error, %s() failed with code = %d[%04X]\r\n", __FUNCTION__, emRet, emRet);
				return;
			}
			emRet = stone_CKD_prv2prv(&secpParentPriKey, bufParentChainCode, 
					stCKDTestVectors[i].pstHDPath->value[j], 
					&secpChildPriKey, bufChildChainCode);
			if (ERT_OK != emRet)
			{
				printf("Error, %s() failed with code = %d[%04X]\r\n", __FUNCTION__, emRet, emRet);
				return;
			}
			memcpy(secpParentPriKey.PrivateKey, secpChildPriKey.PrivateKey, 32);
			memcpy(bufParentChainCode, bufChildChainCode, 32);
			stone_keys_gen_key_fingerprint(&secpPubKeyC, bufFingerPrint, sizeof(bufFingerPrint));
			stone_keys_gen_child_number(bufChildNum, stCKDTestVectors[i].pstHDPath->value[j]);
		}
		
		emRet = stone_keys_get_extended_key(stCKDTestVectors[i].pstHDPath->verBytes, 
				stCKDTestVectors[i].pstHDPath->depth, bufFingerPrint, bufChildNum, 
				bufParentChainCode, secpParentPriKey.PrivateKey, &pExtKey, &extKeyLen);
		if (ERT_OK != emRet)
		{
			printf("Error, %s() failed with code = %d[%04X]\r\n", __FUNCTION__, emRet, emRet);
			if(NULL != pExtKey)
			{
				free(pExtKey);
			}
			return;
		}
		
		if(memcmp_ATA(stCKDTestVectors[i].pExtKey, pExtKey, extKeyLen))
		{
			printf("Error, ExtKey[%d] not macth! pExtKey = %s\r\n", i, pExtKey);
		}
		else
		{
			printf("stCKDTestVectors[%d] pass!\r\n", i);
		}
		
		if(NULL != pExtKey)
		{
			free(pExtKey);
		}
	}
	
	if(NULL != pExtKey)
	{
		free(pExtKey);
	}
	printf("----CKD Vectors Test End----\r\n");
}

void stone_api_test_signature(void)
{
	emRetType emRet = ERT_OK;
	uint8_t i = 0, j = 0;
	uint8_t bufSig[SIG_LEN] = { 0x00 };
	UINT32 sigLen = 0x00000000;
	
	printf("\r\n----Signature Vectors Test Start----\r\n");
	for (i=0; i<sizeof(stSigTestVectors)/sizeof(stSigTestVectorType); i++)
	{
		emRet = stone_ECDSA_sign(stSigTestVectors[i].pSecpPriKey, stSigTestVectors[i].pHash, 
				strlen((const char*)stSigTestVectors[i].pHash), bufSig, &sigLen, COIN_TYPE_BTC);
		if (ERT_OK != emRet)
		{
			printf("Error, %s() failed with code = %d[%04X]\r\n", __FUNCTION__, emRet, emRet);
		}
		
		if(memcmp_ATA(stSigTestVectors[i].pSig, bufSig, sigLen))
		{
			printf("Error, signature[%d] not macth! bufSig = \r\n", i);
			for (j=0; j<sigLen; j++)
			{
				printf("%02X", bufSig[j]);
			}
			printf("\r\n");
		}
		else
		{
			printf("stSigTestVectors[%d] pass!\r\n", i);
		}
	}
	printf("----Signature Vectors Test End----\r\n");
}
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
