/**@NEW FILE***************************************************************************************
* @filename: StoneStorage.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-23
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_STORAGE_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneStorage.h"
#include "StoneFlashPartition.h"
#include "StoneUtil.h"
#include "StoneHDW.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
STONE_STORAGE_EXT uint8_t gu8BufPaddedMax[SF_DATA_LEN_MAX] = {0x00};
STONE_STORAGE_EXT stKSType stKSRootKey=
{
	ROOT_KEY_LEN,
	SF_ADDR_HDW_ROOTKEY,
	SF_ADDR_HDW_ROOTKEY_CKS,
	ROOT_IV_LEN,
	SF_ADDR_HDW_ROOTIV,
	SF_ADDR_HDW_ROOTIV_CKS
};
STONE_STORAGE_EXT stKSType stKSTransKey=
{
	TRANS_KEY_LEN,
	SF_ADDR_TRANS_KEY,
	SF_ADDR_TRANS_KEY_CKS,
	TRANS_IV_LEN,
	SF_ADDR_TRANS_IV,
	SF_ADDR_TRANS_IV_CKS
};
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
STONE_STORAGE_EXT emRetType stone_storage_init(void)
{
	emRetType emRet = ERT_OK;
	UINT8 ret = 0;
	UINT32 startPage = 0;
	UINT32 endPage = 0;
	
	startPage = (SAFE_FLASH_ADDR_START & 0x0FFFFFFF) >> 10;
	endPage = (SAFE_FLASH_ADDR_END & 0x0FFFFFFF) >> 10;
	
 	ret = SF_Init((UINT16)startPage, (UINT16)endPage);
	if (RT_OK != ret)
	{
		return ERT_SFlashFail;
	}
	
	return emRet;
}

STONE_STORAGE_EXT emRetType stone_storage_read(uint8_t *pBuf, uint16_t bufLen, uint32_t addrOffset)
{
	emRetType emRet = ERT_OK;
	UINT8 ret = 0;
	
	ret = SF_ReadData(pBuf, addrOffset, bufLen);
	if (RT_OK != ret)
	{
		return ERT_SFlashFail;
	}
    
	return emRet;
}

STONE_STORAGE_EXT emRetType stone_storage_write(uint8_t *pBuf, uint16_t bufLen, uint32_t addrOffset)
{
	emRetType emRet = ERT_OK;
	UINT8 ret = 0;

	ret = SF_WriteData(pBuf, addrOffset, bufLen);
	if (RT_OK != ret)
	{
		return ERT_SFlashFail;
	}
	
	return emRet;
}

STONE_STORAGE_EXT emRetType stone_storage_safe_read(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset)
{
	emRetType emRet = ERT_OK;
	
	emRet = stone_storage_read(pBuf, bufLen, addrOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	return stone_util_check_sha256(pBuf, bufLen, addrCKOffset);
}

STONE_STORAGE_EXT emRetType stone_storage_safe_write(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset)
{
	emRetType emRet = ERT_OK;
	uint8_t bufCKM[CHECKSUM_LEN] = {0};
	
	emRet = stone_storage_write(pBuf, bufLen, addrOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	stone_util_gen_sha256(pBuf, bufLen, bufCKM, sizeof(bufCKM));
		
	return stone_storage_write(bufCKM, CHECKSUM_LEN, addrCKOffset);
}

STONE_STORAGE_EXT emRetType stone_storage_security_safe_read(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset)
{
	emRetType emRet = ERT_OK;
	uint16_t bufLenPadded = bufLen - (bufLen&7) + 8;

	if (bufLen > SF_DATA_LEN_MAX)
	{
		return ERT_LenTooLong;
	}
	
	emRet = stone_storage_read(gu8BufPaddedMax, bufLenPadded, addrOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}

	emRet = stone_util_check_sha256(gu8BufPaddedMax, bufLenPadded, addrCKOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	emRet = stone_storage_encryption(DES_DECRYPT, &stKSRootKey, gu8BufPaddedMax, 
			bufLenPadded, gu8BufPaddedMax);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	memcpy(pBuf, gu8BufPaddedMax, bufLen);
		
	return emRet;
}

STONE_STORAGE_EXT emRetType stone_storage_security_safe_write(uint8_t *pBuf, uint16_t bufLen, 
		uint32_t addrOffset, uint32_t addrCKOffset)
{
	emRetType emRet = ERT_OK;
	uint8_t bufCKS[CHECKSUM_LEN] = {0};
	uint16_t bufLenPadded = bufLen - (bufLen&7) + 8;

	if (bufLenPadded > SF_DATA_LEN_MAX)
	{
		return ERT_LenTooLong;
	}
	
	memcpy(gu8BufPaddedMax, pBuf, bufLen);
	data_padding(gu8BufPaddedMax, &bufLen, PKCS5);
	if (bufLen != bufLenPadded)
	{
		return ERT_UnexpectedFail;
	}
	
	emRet = stone_storage_encryption(DES_ENCRYPT, &stKSRootKey, gu8BufPaddedMax, 
			bufLenPadded, gu8BufPaddedMax);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	emRet = stone_storage_write(gu8BufPaddedMax, bufLenPadded, addrOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	stone_util_gen_sha256(gu8BufPaddedMax, bufLenPadded, bufCKS, sizeof(bufCKS));

	return stone_storage_write(bufCKS, CHECKSUM_LEN, addrCKOffset);
}

STONE_STORAGE_EXT emRetType stone_storage_encryption(uint8_t nType, stKSType *pstKS, 
			uint8_t *pIn, uint16_t len, uint8_t *pOut)
{
	emRetType emRet = ERT_OK;
	uint8_t bufDESKey[TDES_KEY_LEN] = {0x00};
	uint8_t bufDESIV[TDES_IV_LEN] = {0x00};
	
	emRet = stone_storage_safe_read(bufDESKey, pstKS->keyLen, 
			pstKS->addrKeyOffset, pstKS->addrKeyCKSOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	emRet = stone_storage_safe_read(bufDESIV, pstKS->ivLen, 
			pstKS->addrIVOffset, pstKS->addrIVCKSOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	if (RT_OK != DES_Init(bufDESKey, sizeof(bufDESKey)))
	{
		return ERT_3DESFail;
	}
	
	if (RT_OK != DES_Run(nType, DES3_CBC, pIn, pOut, len, bufDESIV))
	{
		return ERT_3DESFail;
	}
	
	return emRet;
}
/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
