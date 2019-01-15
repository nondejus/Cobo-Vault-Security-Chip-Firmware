/**@NEW FILE***************************************************************************************
* @filename: StoneUtil.c
* @description:
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_UTIL_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneUtil.h"
#include "RipeMD160.h"
#include "StoneStorage.h"
#include "SecurityChipAPI.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
void buf_xor(uint8_t* buf1, uint8_t* buf2, uint32_t len)
{
	uint32_t i = 0;
	for (i=0; i<len; i++)
	{
		buf1[i] ^= buf2[i];
	}
}

void u16_to_buf(uint8_t* buf, uint16_t u16)
{
	buf[0] = (uint8_t)(u16>>8);
	buf[1] = (uint8_t)(u16);
}

void u32_to_buf(uint8_t* buf, uint32_t u32)
{
	buf[0] = (uint8_t)(u32>>24);
	buf[1] = (uint8_t)(u32>>16);
	buf[2] = (uint8_t)(u32>>8);
	buf[3] = (uint8_t)(u32);
}

void buf_to_u16(uint16_t *pu16, uint8_t* buf)
{
	*pu16  = (uint16_t)buf[0] << 8;
	*pu16 |= (uint16_t)buf[1];
}

void buf_to_u32(uint32_t *pu32, uint8_t* buf)
{
	*pu32  = (uint32_t)buf[0] << 24;
	*pu32 |= (uint32_t)buf[1] << 16;
	*pu32 |= (uint32_t)buf[2] << 8;
	*pu32 |= (uint32_t)buf[3];
}

void swap_fast(uint8_t* pNum1, uint8_t* pNum2)
{
	if (pNum1 != pNum2)
	{
		*pNum1 ^= *pNum2;
		*pNum2 ^= *pNum1;
		*pNum1 ^= *pNum2;
	}
}

void str_reverse(uint8_t *pStr, uint32_t strLen)
{
	uint32_t start = 0;
	uint32_t end = strLen-1;
	
	while(start < end)
	{
		swap_fast(pStr+start++, pStr+end--);
	}
}

UINT32* sequence_to_BN(uint8_t *pByte, uint32_t byteLen, UINT32 *BNLen)
{
	uint8_t i=0;
	uint8_t *pDat = NULL;
	uint8_t offset = 0;
	UINT32 *pBN = NULL;
	uint8_t *pBufTmp = NULL;
	uint8_t remainder = 0;
	
	remainder = byteLen&3;
	
	if (remainder)
	{
		*BNLen = (byteLen>>2)+1;
		pBufTmp = (uint8_t*)malloc(*BNLen*sizeof(UINT32));
		if (NULL == pBufTmp)
		{
			return NULL;
		}
		memset(pBufTmp, 0x00, 4-remainder);
		memcpy(pBufTmp+4-remainder, pByte, byteLen);
	}
	else
	{
		*BNLen = byteLen>>2;
		pBufTmp = pByte;
	}
	pBN = (UINT32*)malloc(*BNLen*sizeof(UINT32));
	if (NULL == pBN)
	{
		return NULL;
	}
	
	for (i=0; i<*BNLen; i++)
	{
		offset = (*BNLen-1-i) << 2;
		pDat = (pBufTmp + offset);
		pBN[i] = ((*pDat)<<24)|((*(pDat+1))<<16)|((*(pDat+2))<<8)|(*(pDat+3));
	}
	
	if (NULL != pBufTmp)
	{
		free(pBufTmp);
	}
	
	return pBN;
}

uint8_t* BN_to_sequence(UINT32 *pBN, UINT32 BNLen, uint32_t *strLen)
{
	size_t size = BNLen<<2;
	uint8_t *pStr = NULL;
	
	uint8_t i=0;
	uint8_t offset = 0;

	pStr = (uint8_t*)malloc(size);
	if (NULL == pStr)
	{
		return NULL;
	}
	for (i=0; i<BNLen; i++)
	{
		offset = (BNLen-1-i) << 2;
		pStr[offset]		= (uint8_t)(pBN[i]>>24);
		pStr[offset + 1]	= (uint8_t)(pBN[i]>>16);
		pStr[offset + 2]	= (uint8_t)(pBN[i]>>8);
		pStr[offset + 3]	= (uint8_t)(pBN[i]);
	}
	*strLen = size;
	
	return pStr;
}

void sequence32B_to_BN256b(uint8_t *pByte, UINT32 *pBN)
{
	uint8_t i=0;
	uint8_t *pDat = NULL;
	uint8_t offset = 0;
	
	for (i=0; i<MAX_DIG_LEN; i++)
	{
		offset = (MAX_DIG_LEN-1-i) << 2;
		pDat = (pByte + offset);
		pBN[i] = ((*pDat)<<24)|((*(pDat+1))<<16)|((*(pDat+2))<<8)|(*(pDat+3));
	}
}

void BN256b_to_sequence32B(UINT32 *pBN, uint8_t *pByte)
{
	uint8_t i=0;
	uint8_t offset = 0;
	
	for (i=0; i<MAX_DIG_LEN; i++)
	{
		offset = (MAX_DIG_LEN-1-i) << 2;
		pByte[offset]			= (uint8_t)(pBN[i]>>24);
		pByte[offset + 1]	= (uint8_t)(pBN[i]>>16);
		pByte[offset + 2]	= (uint8_t)(pBN[i]>>8);
		pByte[offset + 3]	= (uint8_t)(pBN[i]);
	}
}

int8_t sequence_compare_bit8(const uint8_t *pBuf1, const uint8_t *pBuf2, uint32_t bufLen)
{
	uint32_t i = 0;
	
	for (i=0; i<bufLen; i++)
	{
		if (pBuf1[i] != pBuf2[i])
		{
			return (pBuf1[i] > pBuf2[i] ? 1 : -1);
		}
	}
	
	return 0;
}

/**memcmp Anti-Timing-Attack*/
bool memcmp_ATA(const uint8_t *buf1, const uint8_t *buf2, uint16_t len)
{
	uint16_t i = 0;
	bool bIsDiff = false;
	
	for (i=0; i<len; i++)
	{
		bIsDiff |= (buf1[i]^buf2[i]);
	}
	
	return bIsDiff;
}

void zero_memory(void *src, size_t len)
{
	memset(src, 0, len);
}

bool sequence_all_zero(const uint8_t *pBuf, uint32_t bufLen)
{
	uint32_t i = 0;
	
	for (i=0; i<bufLen; i++)
	{
		if (pBuf[i])
		{
			return false;
		}
	}
	
	return true;
}

uint32_t str_to_u32(const char* str)
{
    uint32_t n = 0;
    uint32_t c = 0;

    while (!isdigit(*str))
        ++str;

    while (isdigit(*str))
    {
        c = *str - '0';
        if (n > UINT_MAX/10 || (n == UINT_MAX/10 && c >= UINT_MAX%10))
        {
            return UINT_MAX;
        }
        n = n * 10 + c;
        ++str;
    }
	
    return n;
}

void data_padding(uint8_t *pMsg, uint16_t* msgLen, emPaddingType emPadding)
{
	uint16_t paddingLen = 8 - ((*msgLen) & 7);
	
	switch (emPadding)
	{
		case ANSIX923:
		{
			break;
		}
		case ISO10126:
		{
			break;
		}
		case PKCS7:
		{
			memset(pMsg+*msgLen, 0x00, paddingLen);	//PKCS7Padding
			*msgLen += paddingLen;
			break;
		}
		case PKCS5:
		{
			memset(pMsg+*msgLen, paddingLen, paddingLen);	//PKCS7Padding
			*msgLen += paddingLen;
			break;
		}
		case NoPadding:
		{
			break;
		}
		default:break;
	}
}

void stone_util_gen_sha256(uint8_t *pBuf, uint16_t bufLen, 
		uint8_t *pCheckSum, uint8_t checkSumLen)
{	
	uint8_t bufSha256[SHA256_LEN];
	
	SHA256(pBuf, bufLen, bufSha256);
	
	memcpy(pCheckSum, bufSha256, checkSumLen);
}

emRetType stone_util_check_sha256(uint8_t *pText, uint32_t textLen, uint32_t addrOffset)
{
	emRetType emRet = ERT_OK;
	uint8_t bufCheckSumRead[CHECKSUM_LEN];
	uint8_t bufSha256[32];
	
	emRet = stone_storage_read(bufCheckSumRead, CHECKSUM_LEN, addrOffset);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	SHA256(pText, textLen, bufSha256);
	
	if (0 != memcmp(bufCheckSumRead, bufSha256, CHECKSUM_LEN))
	{
		return ERT_CheckSumFail;
	}
	
	return emRet;
}

void stone_util_gen_sha256sha256(uint8_t *pText, uint32_t textLen, 
		uint8_t *pCheckSum, uint8_t checkSumLen)
{
	UINT8 bufSHA256[SHA256_LEN] = {0};

	SHA256(pText, textLen, bufSHA256);
	SHA256(bufSHA256, SHA256_LEN, bufSHA256);
	
	if (checkSumLen > SHA256_LEN)
	{
		checkSumLen = SHA256_LEN;
	}
	memcpy(pCheckSum, bufSHA256, checkSumLen);
}

bool stone_util_check_sha256sha256(uint8_t *pText, uint32_t textLen, uint8_t *pCheckSum)
{
	uint8_t bufCheckSum[CHECKSUM_LEN];
	
	stone_util_gen_sha256sha256(pText, textLen, bufCheckSum, CHECKSUM_LEN);
	
	if (0 != memcmp(pCheckSum, bufCheckSum, CHECKSUM_LEN))
	{
		memcpy(pCheckSum, bufCheckSum, CHECKSUM_LEN);
		return false;
	}
	
	return true;
}

void stone_util_gen_hash160(uint8_t *pText, uint32_t textLen, uint8_t *pHash, uint8_t hashLen)
{
	UINT8 bufSHA256[SHA256_LEN] = {0};
	UINT8 bufRPMD160[RPMD160_LEN] = {0};
	
	SHA256(pText, textLen, bufSHA256);
	
	RipeMD160(bufSHA256, SHA256_LEN, bufRPMD160);
	
	if (hashLen > RPMD160_LEN)
	{
		hashLen = RPMD160_LEN;
	}
	memcpy(pHash, bufRPMD160, hashLen);
}

/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
