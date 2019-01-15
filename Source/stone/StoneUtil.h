/**@NEW FILE***************************************************************************************
* @filename: StoneUtil.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_UTIL_H
#define STONE_UTIL_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_UTIL_GLOBAL
#define STONE_UTIL_EXT
#else
#define STONE_UTIL_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
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
#define TO_SHORT(H8,L8)	((uint16_t)(((uint16_t)H8<<8)||((uint16_t)L8)))
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
typedef enum
{
	ANSIX923,
	ISO10126,
	PKCS7,
	PKCS5,
	NoPadding
}emPaddingType;
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
void buf_xor(uint8_t* buf1, uint8_t* buf2, uint32_t len);
int atou8(uint8_t ascDat);
uint8_t u8toa(uint8_t dat);
void str_to_hex(uint8_t* bufBcd, uint32_t* bufBcdLen, uint8_t* str, int strLen);
void hex_to_str(uint8_t* str, uint32_t* strLen, uint8_t* bufBcd, uint32_t bufBcdLen);
void u16_to_buf(uint8_t* buf, uint16_t u16);
void u32_to_buf(uint8_t* buf, uint32_t u32);
void buf_to_u16(uint16_t *pu16, uint8_t* buf);
void buf_to_u32(uint32_t *pu32, uint8_t* buf);
uint16_t buf_return_u16(uint8_t* buf);
uint32_t buf_return_u32(uint8_t* buf);
void swap_fast(uint8_t* pNum1, uint8_t* pNum2);
uint8_t endian_exchange(uint8_t* buf, uint16_t bufLen, uint8_t alignLen);
void str_reverse(uint8_t *pStr, uint32_t strLen);
UINT32 * sequence_to_BN(uint8_t *pByte, uint32_t byteLen, UINT32 *BNLen);
uint8_t * BN_to_sequence(UINT32 *pBN, UINT32 BNLen, uint32_t *strLen);
void sequence32B_to_BN256b(uint8_t *pByte, UINT32 *pBN);
void BN256b_to_sequence32B(UINT32 *pBN, uint8_t *pByte);
int8_t sequence_compare_bit8(const uint8_t *pBuf1, const uint8_t *pBuf2, uint32_t bufLen);
bool memcmp_ATA(const uint8_t *buf1, const uint8_t *buf2, uint16_t len);
void zero_memory(void *src, size_t len);
bool sequence_all_zero(const uint8_t *pBuf, uint32_t bufLen);
uint32_t str_to_u32(const char* str);
void data_padding(uint8_t *pMsg, uint16_t* msgLen, emPaddingType emPadding);
void stone_util_gen_sha256(uint8_t *pBuf, uint16_t bufLen, 
		uint8_t *pCheckSum, uint8_t checkSumLen);
emRetType stone_util_check_sha256(uint8_t *pText, uint32_t textLen, uint32_t addrOffset);
void stone_util_gen_sha256sha256(uint8_t *pText, uint32_t textLen, 
		uint8_t *pCheckSum, uint8_t checkSumLen);
bool stone_util_check_sha256sha256(uint8_t *pText, uint32_t textLen, uint8_t *pCheckSum);
void stone_util_gen_hash160(uint8_t *pText, uint32_t textLen, uint8_t *pHash, uint8_t hashLen);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
