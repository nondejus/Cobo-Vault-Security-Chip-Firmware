/**@NEW FILE***************************************************************************************
* @filename: StoneHDW.c
* @description: 
* @author&data: Andrew Zhang  @2018-03-23
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/* Avoid duplicate definitions */
#define STONE_HDW_GLOBAL
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
#include "StoneHDW.h"
#include "StoneECDSA.h"
#include "StoneStorage.h"
#include "StoneKeys.h"
#include "StoneCKD.h"
#include "StoneUtil.h"
#include "base58.h"
#include "StoneRandom.h"
#include "StoneComm.h"
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable definitions */
/**
 * @note: This part is hidden for security reasons.
*/
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function implementations */
STONE_HDW_EXT uint32_t stone_HDW_get_app_version_code(void)
{
	return HDW_APP_VERSION;
}

STONE_HDW_EXT uint8_t* stone_HDW_get_app_version_name(void)
{
	return HDW_APP_VER_STRING;
}

STONE_HDW_EXT emRetType stone_HDW_init_SN(uint8_t bufSN[], uint16_t SNLen)
{
	emRetType emRet = ERT_OK;
	
	if (SN_LEN != SNLen)
	{
		return ERT_SNLenInvalid;
	}
			
	emRet = stone_storage_safe_write(bufSN, SNLen, 
			SF_ADDR_SN, SF_ADDR_SN_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_get_SN(uint8_t bufSN[], uint16_t* snLen)
{
	emRetType emRet = ERT_OK;
	
	*snLen = SN_LEN;
	emRet = stone_storage_safe_read(bufSN, *snLen, 
			SF_ADDR_SN, SF_ADDR_SN_CKS);
	
	return emRet;
}

STONE_HDW_EXT emHDWStatusType stone_HDW_get_status(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufHDWStatus[HDW_STATUS_LEN];
	UINT32 addr = (SF_ADDR_HDW_STATUS+SAFE_FLASH_ADDR_START-FLASH_ADDR_START)/1024;
	
	if (EFC_IsEraseOK(addr, addr))
	{
		return E_HDWS_CHIP;
	}
	else
	{
		emRet = stone_storage_read(bufHDWStatus, HDW_STATUS_LEN, SF_ADDR_HDW_STATUS);
		if (ERT_OK != emRet)
		{
			gstCommStatus.emRet = emRet;
			return E_HDWS_UNKNOWN;
		}
		
		if (0 == memcmp(bufHDWStatus, HDW_STATUS_SYMBOL_CHIP, HDW_STATUS_LEN))
		{
			return E_HDWS_CHIP;
		}
		else if (0 == memcmp(bufHDWStatus, HDW_STATUS_SYMBOL_FACTORY, HDW_STATUS_LEN))
		{
			if (ERT_OK == stone_util_check_sha256(bufHDWStatus, HDW_STATUS_LEN, 
					SF_ADDR_HDW_STATUS_CKS))
			{
				return E_HDWS_FACTORY;
			}
		}
		else if (0 == memcmp(bufHDWStatus, HDW_STATUS_SYMBOL_ATTACK, HDW_STATUS_LEN))
		{
			if (ERT_OK == stone_util_check_sha256(bufHDWStatus, HDW_STATUS_LEN, 
					SF_ADDR_HDW_STATUS_CKS))
			{
				return E_HDWS_ATTACK;
			}
		}
		else if (0 == memcmp(bufHDWStatus, HDW_STATUS_SYMBOL_EMPTY, HDW_STATUS_LEN))
		{
			if (ERT_OK == stone_util_check_sha256(bufHDWStatus, HDW_STATUS_LEN, 
					SF_ADDR_HDW_STATUS_CKS))
			{
				return E_HDWS_EMPTY;
			}
		}
		else if (0 == memcmp(bufHDWStatus, HDW_STATUS_SYMBOL_WALLET, HDW_STATUS_LEN))
		{
			if (ERT_OK == stone_util_check_sha256(bufHDWStatus, HDW_STATUS_LEN, 
					SF_ADDR_HDW_STATUS_CKS))
			{
				return E_HDWS_WALLET;
			}
		}
		else
		{
			emRet = stone_HDW_set_status(gstHDWStatus[HDW_STATUS_EMPTY]);
			if (ERT_OK == emRet)
			{
				stone_HDW_delete_wallet();
				return E_HDWS_EMPTY;
			}
		}
	}
	
	return E_HDWS_UNKNOWN;
}

STONE_HDW_EXT emRetType stone_HDW_set_status(const volatile stHDWStatusType stHDWStatus)
{
	emRetType emRet = ERT_OK;

	emRet = stone_storage_safe_write(stHDWStatus.pSymbol, HDW_STATUS_LEN, 
			SF_ADDR_HDW_STATUS, SF_ADDR_HDW_STATUS_CKS);
	if (ERT_OK == emRet)
	{
		gemHDWStatus = stHDWStatus.emHDWStatus;
	}
	
	return emRet;
}

/**FUNCTION****************************************************************************************
* @functionname: stone_HDW_init_rootkey()
* @description: generate a random sequence as the ROOT KEY when the security chip first powers up, 
				the ROOT KEY is used to encryt/decrypt data stored inside the security chip.
* @para: none
* @return: emRetType
*/
STONE_HDW_EXT emRetType stone_HDW_init_rootkey(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufRootKey[ROOT_KEY_LEN] = {0x00};
	uint8_t bufRootIV[ROOT_IV_LEN] = {0x00};

	stone_get_strong_random(bufRootKey, ROOT_KEY_LEN);

	emRet = stone_storage_safe_write(bufRootKey, ROOT_KEY_LEN, 
			SF_ADDR_HDW_ROOTKEY, SF_ADDR_HDW_ROOTKEY_CKS);
	if (ERT_OK != emRet)
	{
		return emRet;
	}

	stone_get_strong_random(bufRootIV, ROOT_IV_LEN);
	
	emRet = stone_storage_safe_write(bufRootIV, ROOT_IV_LEN, 
			SF_ADDR_HDW_ROOTIV, SF_ADDR_HDW_ROOTIV_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_init_transkey(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufTransKey[TRANS_KEY_LEN] = {	0x74, 0x65, 0x73, 0x74 };
	uint8_t bufTransIV[TRANS_IV_LEN] = {	0x74, 0x65, 0x73, 0x74 };

	emRet = stone_storage_safe_write(bufTransKey, TRANS_KEY_LEN, 
			SF_ADDR_TRANS_KEY, SF_ADDR_TRANS_KEY_CKS);
	emRet = stone_storage_safe_write(bufTransIV, TRANS_IV_LEN, 
			SF_ADDR_TRANS_IV, SF_ADDR_TRANS_IV_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_init_authentication_key(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufPrvKey1[PRV_KEY_LEN] = {	0x74, 0x65, 0x73, 0x74 };
	uint8_t bufPubKey2[PUB_KEY_LEN] = {	0x74, 0x65, 0x73, 0x74 };

	emRet = stone_storage_safe_write(bufPrvKey1, PRV_KEY_LEN, 
			SF_ADDR_PRV_KEY1, SF_ADDR_PRV_KEY1_CKS);
	emRet = stone_storage_safe_write(bufPubKey2, PUB_KEY_LEN, 
			SF_ADDR_PUB_KEY2, SF_ADDR_PUB_KEY2_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_init_android_key(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufPubKey4[PUB_KEY_LEN] = {	0x74, 0x65, 0x73, 0x74 };

	emRet = stone_storage_safe_write(bufPubKey4, PUB_KEY_LEN, 
			SF_ADDR_PUB_KEY4, SF_ADDR_PUB_KEY4_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_init_upgrade_key(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufUpgradeKeyLen[2] = {0x00};
	uint8_t bufUpgradeKey[] = {	0x74, 0x65, 0x73, 0x74 };

	u16_to_buf(bufUpgradeKeyLen, sizeof(bufUpgradeKeyLen));
	emRet = stone_storage_write(bufUpgradeKeyLen, sizeof(bufUpgradeKeyLen), SF_ADDR_UPGRADE_KEY_LEN);
	if (ERT_OK == emRet)
	{
		emRet = stone_storage_security_safe_write(bufUpgradeKey, sizeof(bufUpgradeKey), 
				SF_ADDR_UPGRADE_KEY, SF_ADDR_UPGRADE_KEY_CKS);
	}
										
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_create_wallet(uint8_t *pMnemonic, uint16_t mnemonicLen)
{
	emRetType emRet = ERT_OK;
	uint8_t bufMnemonicLen[2] = {0x00};
	uint8_t bufSeed[SEED_LEN] = {0x00};
	uint8_t bufRootSeed[SHA512_LEN] = {0};

	emRet = stone_keys_gen_seed_bip39(pMnemonic, mnemonicLen, NULL, 0, bufSeed, SEED_LEN);
	
	stone_keys_gen_root_seed_bip32(bufSeed, SEED_LEN, (UINT8*)"Bitcoin seed", 
			strlen((const char*)"Bitcoin seed"), bufRootSeed);
	emRet = stone_keys_check_key_valid(bufRootSeed, 32);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	u16_to_buf(bufMnemonicLen, mnemonicLen);
	
	emRet = stone_storage_write(bufMnemonicLen, sizeof(bufMnemonicLen), SF_ADDR_MNEMONIC_LEN);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	emRet = stone_storage_security_safe_write(pMnemonic, mnemonicLen, 
			SF_ADDR_MNEMONIC, SF_ADDR_MNEMONIC_CKS);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	
	emRet = stone_storage_security_safe_write(bufSeed, SEED_LEN, SF_ADDR_SEED, SF_ADDR_SEED_CKS);
	
	zero_memory(bufSeed, SEED_LEN);

	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_add_wallet(uint8_t *pPassphrase, uint16_t passphraseLen)
{
	emRetType emRet = ERT_OK;
	uint8_t bufMnemonicLen[2] = {0x00};
	uint16_t mnemonicLen = 0;
	uint8_t *pMnemonic = NULL;
	uint8_t bufSeed[SEED_LEN] = {0x00};

	emRet = stone_storage_read(bufMnemonicLen, 2, SF_ADDR_MNEMONIC_LEN);
	if (ERT_OK != emRet)
	{
		return emRet;
	}

	buf_to_u16(&mnemonicLen, bufMnemonicLen);
	
	pMnemonic = (uint8_t*)malloc(mnemonicLen);
	if (NULL == pMnemonic)
	{
		return ERT_MallocFail;
	}

	emRet = stone_storage_security_safe_read(pMnemonic, mnemonicLen, 
			SF_ADDR_MNEMONIC, SF_ADDR_MNEMONIC_CKS);
	if (ERT_OK != emRet)
	{
		if (NULL != pMnemonic)
		{
			free(pMnemonic);
		}
		return emRet;
	}
	
	stone_keys_gen_seed_bip39(pMnemonic, mnemonicLen, pPassphrase, 
			passphraseLen, bufSeed, SEED_LEN);
	
	zero_memory(pMnemonic, mnemonicLen);
	if (NULL != pMnemonic)
	{
		free(pMnemonic);
	}
	
	emRet = stone_storage_security_safe_write(bufSeed, SEED_LEN, SF_ADDR_SEED, SF_ADDR_SEED_CKS);
		
	zero_memory(bufSeed, SEED_LEN);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_delete_wallet(void)
{
	emRetType emRet = ERT_OK;
	uint8_t bufRandom[256] = {0x00};

	stone_get_strong_random(bufRandom, MAX_MNEMONIC_LEN);
	
	emRet = stone_storage_safe_write(bufRandom, MAX_MNEMONIC_LEN, 
			SF_ADDR_MNEMONIC, SF_ADDR_MNEMONIC_CKS);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	emRet = stone_storage_safe_write(bufRandom, MAX_SEED_LEN, 
			SF_ADDR_SEED, SF_ADDR_SEED_CKS);
	
	return emRet;
}

STONE_HDW_EXT emRetType stone_HDW_mnemonic_verify(uint8_t *pMnemonic, uint16_t mnemonicLen)
{
	emRetType emRet = ERT_OK;
	uint8_t bufMnemonicLen[2] = {0x00};
	uint16_t mnemonicLenTmp = 0;
	uint8_t *pMnemonicTmp = NULL;
	
	emRet = stone_storage_read(bufMnemonicLen, 2, SF_ADDR_MNEMONIC_LEN);
	if (ERT_OK != emRet)
	{
		return emRet;
	}
	buf_to_u16(&mnemonicLenTmp, bufMnemonicLen);
	
	if (mnemonicLenTmp != mnemonicLen)
	{
		return ERT_MnemonicNotMatch;
	}
		
	pMnemonicTmp = (uint8_t*)malloc(mnemonicLenTmp);
	if (NULL == pMnemonicTmp)
	{
		return ERT_MallocFail;
	}
	
	emRet = stone_storage_security_safe_read(pMnemonicTmp, mnemonicLenTmp, 
			SF_ADDR_MNEMONIC, SF_ADDR_MNEMONIC_CKS);
	if (ERT_OK != emRet)
	{
		if (NULL != pMnemonicTmp)
		{
			free(pMnemonicTmp);
		}
		return emRet;
	}
	
	if (memcmp_ATA(pMnemonicTmp, pMnemonic, mnemonicLenTmp))
	{
		emRet = ERT_MnemonicNotMatch;
	}
	
	zero_memory(pMnemonicTmp, mnemonicLenTmp);
	if (NULL != pMnemonicTmp)
	{
		free(pMnemonicTmp);
	}
	
	return emRet;
}
/**@END SECTION**/


/**@END OF FILE***********************************************************************************/
