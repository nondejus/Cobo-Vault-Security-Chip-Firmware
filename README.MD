# Cobo Vault Secure Element Firmware

We are open sourcing a core part of our secure element firmware that is embedded in the Cobo Vault.

## Additional Declaration

Some pieces of code have been hidden as a security measure as they pertain to the secure element hardware and communication protocol of the device. As a result, this code cannot function independently.

# Support for BIPs

* Mnemonic code generation of deterministic wallets strictly conforms to the [BIP39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki) protocol.

* Key derivation implementation strictly conforms to the [BIP32](https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki) protocol.

* Multi-account hierarchy implementation for deterministic wallets strictly conforms to the [BIP44](https://github.com/bitcoin/bips/blob/master/bip-0044.mediawiki) protocol.

* In order to restrict signatures for stringent DER encoding, all changes implemented to Bitcoin's transaction validation rules strictly conform to the [BIP66](https://github.com/bitcoin/bips/blob/master/bip-0066.mediawiki) protocol.


# Entropy Source

The entropy comes from a [True-Random-Number-Generator](https://en.wikipedia.org/w/index.php?title=True_random_number_generator&redirect=no), which has passed the [FIPS140-2](https://en.wikipedia.org/wiki/FIPS_140-2) requirements, inside the secure element.
```
void stone_get_strong_random(uint8_t bufRandom[], uint16_t randomLen)
{
	UINT8 ret = RT_OK;
	
	do
	{
		ret = security_chip_trng_gen_random_check(bufRandom, randomLen);	//security_chip_api
	}while (RT_OK != ret);
}
```
