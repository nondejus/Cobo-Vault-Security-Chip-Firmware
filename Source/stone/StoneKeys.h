/**@NEW FILE***************************************************************************************
* @filename: StoneKeys.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_KEYS_H
#define STONE_KEYS_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_KEYS_GLOBAL
#define STONE_KEYS_EXT
#else
#define STONE_KEYS_EXT	extern
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
#include "type.h"
#include "StoneErrno.h"
#include "secp256k1.h"

/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions*/
#define PASSPHRASE_PREFIX		("mnemonic")					//BIP39

//Serialization format-version bytes
#define SF_VB_INT_MNET_PUB		0x0488B21E
#define SF_VB_INT_MNET_PRV		0x0488ADE4
#define SF_VB_INT_TNET_PUB		0x043587CF
#define SF_VB_INT_TNET_PRV		0x04358394
#define SF_VB_BUF_MNET_PUB		(0x04, 0x88��0xB2��0x1E)
#define SF_VB_BUF_MNET_PRV		(0x04, 0x88��0xAD��0xE4)
#define SF_VB_BUF_TNET_PUB		(0x04, 0x35, 0x87, 0xCF)
#define SF_VB_BUF_TNET_PRV		(0x04, 0x35, 0x83, 0x94)
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
STONE_KEYS_EXT const UINT32 gcu32_secp256k1_n[8];
STONE_KEYS_EXT const UINT8 gcu8_secp256k1_n[32];
//STONE_KEYS_EXT const UINT8 gcu8_secp256k1_n_half[32];
/****************************************************************************
//Mnemonic codes: entropy and word length
//Entropy(bits)	Checksum(bits)	Entropy+checksum(bits)	MnemonicLength(words)
128				4				132						12
160				5				165						15
192				6				198						18
224				7				231						21
256				8				264						24
 * *************************************************************************/ 
typedef enum
{
	emEntropy128Bits = 128,
	emEntropy160Bits = 160,
	emEntropy192Bits = 192,
	emEntropy224Bits = 224,
	emEntropy256Bits = 256
}emEntropyBitsType;

/**This 78 byte structure can be encoded like other Bitcoin data in Base58, 
 by first adding 32 checksum bits (derived from the double SHA-256 checksum), 
 and then converting to the Base58 representation. 
 This results in a Base58-encoded string of up to 112 characters. 
 Because of the choice of the version bytes, the Base58 representation 
 will start with "xprv" or "xpub" on mainnet, "tprv" or "tpub" on testnet.**/
typedef struct
{
	/**@versionbytes 
	mainnet: 0x0488B21E public		0x0488ADE4 private
	testnet: 0x043587CF public 		0x04358394 private */
	uint8_t version[4];
	/**@depth: 0x00 for master nodes, 0x01 for level-1 derived keys, .... */
	uint8_t depth;
	/**@fingerprint of the parent's key (0x00000000 if master key) */
	uint8_t fingerPrint[4];
	/**@childnumber
	This is ser32(i) for i in xi = xpar/i, 
	with xi the key being serialized. (0x00000000 if master key) */
	uint8_t childNumber[4];
	uint8_t chainCode[32];
	/**the public key or private key data
	(serP(K) for public keys, 0x00 || ser256(k) for private keys) */
	uint8_t key[33];
	uint8_t checkSum[4];
} __attribute__((packed)) stExtKeyType;

typedef struct
{
	uint32_t verBytes;
	uint32_t value[5];
	uint8_t depth;
}stHDPathType;
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
STONE_KEYS_EXT emRetType stone_keys_str_to_hdpath(uint8_t *pStr, uint32_t strLen, 
		stHDPathType *pstHDPath);
STONE_KEYS_EXT emRetType stone_keys_check_key_valid(uint8_t *pKey, uint32_t keyLen);
STONE_KEYS_EXT void stone_keys_pubkey_compress(SECP_PubKey *pPubKey, SECP_PubKeyCompressed *pPubKeyC);
STONE_KEYS_EXT emRetType stone_keys_get_pubkey(SECP_PriKey *pPriKey, SECP_PubKey *pPubKey);
STONE_KEYS_EXT emRetType stone_keys_get_compressed_pubkey(SECP_PriKey *pPriKey, 
		SECP_PubKeyCompressed *pPubKeyC);
STONE_KEYS_EXT void stone_keys_gen_key_fingerprint(SECP_PubKeyCompressed *psecpPubKeyC, 
		uint8_t *pFingerPrint, uint8_t fingerPrintLen);
STONE_KEYS_EXT void stone_keys_gen_child_number(uint8_t *pChildNum, uint32_t u32ChildNum);
STONE_KEYS_EXT emRetType stone_keys_gen_entropy(uint8_t *bufEntropy, 
		emEntropyBitsType emEBits, uint8_t needCKS);
STONE_KEYS_EXT emRetType stone_keys_gen_seed_bip39(uint8_t *pMnemonic, uint32_t mnemonicLen, 
		uint8_t *pPassphrase, uint32_t passphraseLen, uint8_t *pSeed, int32_t seedLen);
STONE_KEYS_EXT void stone_keys_gen_root_seed_bip32(uint8_t *pSeed, uint32_t seedLen, 
		uint8_t *pKey, uint32_t keyLen, uint8_t *pRootSeed);
STONE_KEYS_EXT emRetType stone_keys_gen_master_key_bip32(uint8_t *pSeed, uint32_t seedLen, 
		uint8_t *pKey, uint32_t keyLen, SECP_PriKey *pPrvKey, uint8_t *pChainCode);
STONE_KEYS_EXT emRetType stone_keys_get_master_key_pairs(SECP_PriKey *pMasterPrvKey, 
		uint8_t *pMasterChainCode);
STONE_KEYS_EXT uint8_t* stone_keys_pubKey_to_address(SECP_PubKey *psecpPubKey, uint32_t *pAddrLen);
STONE_KEYS_EXT uint8_t* stone_keys_pubKeyC_to_addressC(SECP_PubKeyCompressed *psecpPubKeyC, 
		uint32_t *pAddrLen);
STONE_KEYS_EXT uint8_t* stone_keys_pubKey_to_addressC(SECP_PubKey *psecpPubKey, uint32_t *pAddrLen);
STONE_KEYS_EXT uint8_t* stone_keys_prvkey_to_WIF(SECP_PriKey *psecpPrvKey, uint32_t *pWIFLen);
STONE_KEYS_EXT uint8_t* stone_keys_prvkey_to_compressed_WIF(SECP_PriKey *psecpPrvKey, 
		uint32_t *pWIFLen);
STONE_KEYS_EXT emRetType stone_keys_get_extended_key(uint32_t version, uint8_t depth, 
		uint8_t *pFingerPrint, uint8_t *pChildNum,
		uint8_t *pChainCode, uint8_t *pKey, 
		uint8_t **pExtKey, uint32_t *extKeyLen);
STONE_KEYS_EXT emRetType stone_keys_derive_key(stHDPathType *pstHDPathParam, 
		SECP_PriKey *pPrvKey, SECP_PubKey *pPubKey,
        uint8_t **pExtKey, uint32_t *pExtKeyLen);
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
