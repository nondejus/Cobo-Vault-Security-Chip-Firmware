/**@NEW FILE***************************************************************************************
* @filename: StoneApiTest.h
* @description: 
* @author&data: Andrew Zhang @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_API_TEST_H
#define STONE_API_TEST_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_API_TEST_GLOBAL
#define STONE_API_TEST_EXT
#else
#define STONE_API_TEST_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "StoneKeys.h"
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
typedef struct CKD_TEST_VECTOR
{
	uint8_t *pSeed;
	uint8_t *pStrHDPath;
	stHDPathType *pstHDPath;
	uint8_t *pExtKey;
}stCKDTestVectorType;
typedef struct SIG_TEST_VECTOR
{
	SECP_PriKey *pSecpPriKey;
	uint8_t *pHash;
	uint8_t *pSig;
}stSigTestVectorType;
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
void stone_api_test_CKD(void);
void stone_api_test_signature(void);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
