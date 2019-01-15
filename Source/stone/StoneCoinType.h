/**@NEW FILE***************************************************************************************
* @filename: StoneCoinType.h
* @description: 
* @author&data: Andrew Zhang  @2018-03-14
* @note: any questions, please contact yzhang@cobo.com
* @copyright:The sole ownership of this file belongs to SHANGHAI NANQIAN TECHNOLOGY CO., LTD!
* All rights reserved! All material contained within this file should NOT be copied, reproduced, 
* or used elsewhere without proper authorization.
**************************************************************************************************/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifndef STONE_COINTYPE_H
#define STONE_COINTYPE_H
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Avoid duplicate definitions */
#ifdef  STONE_COINTYPE_GLOBAL
#define STONE_COINTYPE_EXT
#else
#define STONE_COINTYPE_EXT	extern
#endif
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Header file reference */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Macro definitions*/
#define COIN_TYPE_BTC    0x80000000
#define COIN_TYPE_TESTN    0x80000001
#define COIN_TYPE_LTC    0x80000002
#define COIN_TYPE_DOGE    0x80000003
#define COIN_TYPE_RDD    0x80000004
#define COIN_TYPE_DSH    0x80000005
#define COIN_TYPE_PPC    0x80000006
#define COIN_TYPE_NMC    0x80000007
#define COIN_TYPE_FTC    0x80000008
#define COIN_TYPE_XCP    0x80000009
#define COIN_TYPE_BLK    0x8000000a
#define COIN_TYPE_NSR    0x8000000b
#define COIN_TYPE_NBT    0x8000000c
#define COIN_TYPE_MZC    0x8000000d
#define COIN_TYPE_VIA    0x8000000e
#define COIN_TYPE_XCH    0x8000000f
#define COIN_TYPE_RBY    0x80000010
#define COIN_TYPE_GRS    0x80000011
#define COIN_TYPE_DGC    0x80000012
#define COIN_TYPE_CCN    0x80000013
#define COIN_TYPE_DGB    0x80000014
#define COIN_TYPE_OPA    0x80000015
#define COIN_TYPE_MONA    0x80000016
#define COIN_TYPE_CLAM    0x80000017
#define COIN_TYPE_XPM    0x80000018
#define COIN_TYPE_NEOS    0x80000019
#define COIN_TYPE_JBS    0x8000001a
#define COIN_TYPE_ZRC    0x8000001b
#define COIN_TYPE_VTC    0x8000001c
#define COIN_TYPE_NXT    0x8000001d
#define COIN_TYPE_BURST    0x8000001e
#define COIN_TYPE_MUE    0x8000001f
#define COIN_TYPE_ZOOM    0x80000020
#define COIN_TYPE_VASH    0x80000021
#define COIN_TYPE_CDN    0x80000022
#define COIN_TYPE_SDC    0x80000023
#define COIN_TYPE_PKB    0x80000024
#define COIN_TYPE_PND    0x80000025
#define COIN_TYPE_START    0x80000026
#define COIN_TYPE_MOIN    0x80000027
#define COIN_TYPE_EXP    0x80000028
#define COIN_TYPE_EMC2    0x80000029
#define COIN_TYPE_DCR    0x8000002a
#define COIN_TYPE_XEM    0x8000002b
#define COIN_TYPE_PART    0x8000002c
#define COIN_TYPE_ARG    0x8000002d
#define COIN_TYPE_LBT    0x8000002e
#define COIN_TYPE_POC    0x8000002f
#define COIN_TYPE_SHR    0x80000030
#define COIN_TYPE_GCR    0x80000031
#define COIN_TYPE_NVC    0x80000032
#define COIN_TYPE_AC    0x80000033
#define COIN_TYPE_BTCD    0x80000034
#define COIN_TYPE_DOPE    0x80000035
#define COIN_TYPE_TPC    0x80000036
#define COIN_TYPE_AIB    0x80000037
#define COIN_TYPE_EDRC    0x80000038
#define COIN_TYPE_SYS    0x80000039
#define COIN_TYPE_SLR    0x8000003a
#define COIN_TYPE_SMLY    0x8000003b
#define COIN_TYPE_ETH    0x8000003c
#define COIN_TYPE_ETC    0x8000003d
#define COIN_TYPE_PSB    0x8000003e
#define COIN_TYPE_LDCN    0x8000003f
#define COIN_TYPE_OPC    0x80000040
#define COIN_TYPE_XBC    0x80000041
#define COIN_TYPE_IOP    0x80000042
#define COIN_TYPE_NXS    0x80000043
#define COIN_TYPE_INSN    0x80000044
#define COIN_TYPE_OK    0x80000045
#define COIN_TYPE_BRIT    0x80000046
#define COIN_TYPE_CMP    0x80000047
#define COIN_TYPE_CRW    0x80000048
#define COIN_TYPE_BELA    0x80000049
#define COIN_TYPE_    0x8000004a
#define COIN_TYPE_FJC    0x8000004b
#define COIN_TYPE_MIX    0x8000004c
#define COIN_TYPE_XVG    0x8000004d
#define COIN_TYPE_EFL    0x8000004e
#define COIN_TYPE_CLUB    0x8000004f
#define COIN_TYPE_RICHX    0x80000050
#define COIN_TYPE_POT    0x80000051
#define COIN_TYPE_QRK    0x80000052
#define COIN_TYPE_TRC    0x80000053
#define COIN_TYPE_GRC    0x80000054
#define COIN_TYPE_AUR    0x80000055
#define COIN_TYPE_IXC    0x80000056
#define COIN_TYPE_NLG    0x80000057
#define COIN_TYPE_BITB    0x80000058
#define COIN_TYPE_BTA    0x80000059
#define COIN_TYPE_XMY    0x8000005a
#define COIN_TYPE_BSD    0x8000005b
#define COIN_TYPE_UNO    0x8000005c
#define COIN_TYPE_MTR    0x8000005d
#define COIN_TYPE_GB    0x8000005e
#define COIN_TYPE_SHM    0x8000005f
#define COIN_TYPE_CRX    0x80000060
#define COIN_TYPE_BIQ    0x80000061
#define COIN_TYPE_EVO    0x80000062
#define COIN_TYPE_STO    0x80000063
#define COIN_TYPE_BIGUP    0x80000064
#define COIN_TYPE_GAME    0x80000065
#define COIN_TYPE_DLC    0x80000066
#define COIN_TYPE_ZYD    0x80000067
#define COIN_TYPE_DBIC    0x80000068
#define COIN_TYPE_STRAT    0x80000069
#define COIN_TYPE_SH    0x8000006a
#define COIN_TYPE_MARS    0x8000006b
#define COIN_TYPE_UBQ    0x8000006c
#define COIN_TYPE_PTC    0x8000006d
#define COIN_TYPE_NRO    0x8000006e
#define COIN_TYPE_ARK    0x8000006f
#define COIN_TYPE_USC    0x80000070
#define COIN_TYPE_THC    0x80000071
#define COIN_TYPE_LINX    0x80000072
#define COIN_TYPE_ECN    0x80000073
#define COIN_TYPE_DNR    0x80000074
#define COIN_TYPE_PINK    0x80000075
#define COIN_TYPE_PIGGY    0x80000076
#define COIN_TYPE_PIVX    0x80000077
#define COIN_TYPE_FLASH    0x80000078
#define COIN_TYPE_ZEN    0x80000079
#define COIN_TYPE_PUT    0x8000007a
#define COIN_TYPE_ZNY    0x8000007b
#define COIN_TYPE_UNIFY    0x8000007c
#define COIN_TYPE_XST    0x8000007d
#define COIN_TYPE_BRK    0x8000007e
#define COIN_TYPE_VC    0x8000007f
#define COIN_TYPE_XMR    0x80000080
#define COIN_TYPE_VOX    0x80000081
#define COIN_TYPE_NAV    0x80000082
#define COIN_TYPE_FCT    0x80000083
#define COIN_TYPE_EC    0x80000084
#define COIN_TYPE_ZEC    0x80000085
#define COIN_TYPE_LSK    0x80000086
#define COIN_TYPE_STEEM    0x80000087
#define COIN_TYPE_XZC    0x80000088
#define COIN_TYPE_SBTC    0x80000089
#define COIN_TYPE_GBK    0x8000008a
#define COIN_TYPE_RPT    0x8000008b
#define COIN_TYPE_LBC    0x8000008c
#define COIN_TYPE_KMD    0x8000008d
#define COIN_TYPE_BSQ    0x8000008e
#define COIN_TYPE_RIC    0x8000008f
#define COIN_TYPE_XRP    0x80000090
#define COIN_TYPE_BCH    0x80000091
#define COIN_TYPE_NEBL    0x80000092
#define COIN_TYPE_ZCL    0x80000093
#define COIN_TYPE_XLM    0x80000094
#define COIN_TYPE_NLC2    0x80000095
#define COIN_TYPE_WHL    0x80000096
#define COIN_TYPE_ERC    0x80000097
#define COIN_TYPE_DMD    0x80000098
#define COIN_TYPE_BTM    0x80000099
#define COIN_TYPE_BIO    0x8000009a
#define COIN_TYPE_XWC    0x8000009b
#define COIN_TYPE_BTG    0x8000009c
#define COIN_TYPE_BTC2X    0x8000009d
#define COIN_TYPE_SSN    0x8000009e
#define COIN_TYPE_TOA    0x8000009f
#define COIN_TYPE_BTX    0x800000a0
#define COIN_TYPE_ACC    0x800000a1
#define COIN_TYPE_BCO    0x800000a2
#define COIN_TYPE_ELLA    0x800000a3
#define COIN_TYPE_PIRL    0x800000a4
#define COIN_TYPE_XRB    0x800000a5
#define COIN_TYPE_VIVO    0x800000a6
#define COIN_TYPE_FRST    0x800000a7
#define COIN_TYPE_HNC    0x800000a8
#define COIN_TYPE_BUZZ    0x800000a9
#define COIN_TYPE_MBRS    0x800000aa
#define COIN_TYPE_HSR    0x800000ab
#define COIN_TYPE_HTML    0x800000ac
#define COIN_TYPE_ODN    0x800000ad
#define COIN_TYPE_ONX    0x800000ae
#define COIN_TYPE_RVN    0x800000af
#define COIN_TYPE_GBX    0x800000b0
#define COIN_TYPE_BTCZ    0x800000b1
#define COIN_TYPE_POA    0x800000b2
#define COIN_TYPE_NYC    0x800000b3
#define COIN_TYPE_MXT    0x800000b4
#define COIN_TYPE_WC    0x800000b5
#define COIN_TYPE_MNX    0x800000b6
#define COIN_TYPE_BTCP    0x800000b7
#define COIN_TYPE_MUSIC    0x800000b8
#define COIN_TYPE_BCA    0x800000b9
#define COIN_TYPE_CRAVE    0x800000ba
#define COIN_TYPE_STAK    0x800000bb
#define COIN_TYPE_WBTC    0x800000bc
#define COIN_TYPE_LCH    0x800000bd
#define COIN_TYPE_EXCL    0x800000be
#define COIN_TYPE_LYNX    0x800000bf
#define COIN_TYPE_LCC    0x800000c0
#define COIN_TYPE_XFE    0x800000c1
#define COIN_TYPE_EOS    0x800000c2
#define COIN_TYPE_TRX    0x800000c3
#define COIN_TYPE_KOBO    0x800000c4
#define COIN_TYPE_HUSH    0x800000c5
#define COIN_TYPE_BANANO    0x800000c6
#define COIN_TYPE_ETF    0x800000c7
#define COIN_TYPE_OMNI    0x800000c8
#define COIN_TYPE_BIFI    0x800000c9
#define COIN_TYPE_UFO    0x800000ca
#define COIN_TYPE_CNMC    0x800000cb
#define COIN_TYPE_NRG    0x800000cc
#define COIN_TYPE_RIN    0x800000cd
#define COIN_TYPE_ATP    0x800000ce
#define COIN_TYPE_EVT    0x800000cf
#define COIN_TYPE_ATN    0x800000d0
#define COIN_TYPE_BIS    0x800000d1
#define COIN_TYPE_NEET    0x800000d2
#define COIN_TYPE_BOPO    0x800000d3
#define COIN_TYPE_BOXY    0x800000d7
#define COIN_TYPE_FLO    0x800000d8
#define COIN_TYPE_BITG    0x800000de
#define COIN_TYPE_ASK    0x800000df
#define COIN_TYPE_SMART    0x800000e0
#define COIN_TYPE_XUEZ    0x800000e1
#define COIN_TYPE_HLM    0x800000e2
#define COIN_TYPE_VAR    0x800000e9
#define COIN_TYPE_NIM    0x800000f2
#define COIN_TYPE_UC    0x800000f7
#define COIN_TYPE_NPW    0x800000fd
#define COIN_TYPE_SMH    0x800000ff
#define COIN_TYPE_NANO    0x80000100
#define COIN_TYPE_BTCC    0x80000101
#define COIN_TYPE_ZPTL    0x80000102
#define COIN_TYPE_ZEST    0x80000103
#define COIN_TYPE_ONE    0x8000010e
#define COIN_TYPE_SBC    0x8000010f
#define COIN_TYPE_NUKO    0x8000012b
#define COIN_TYPE_GNX    0x8000012c
#define COIN_TYPE_ARA    0x80000138
#define COIN_TYPE_RAP    0x80000141
#define COIN_TYPE_BLOCK    0x80000148
#define COIN_TYPE_MEM    0x8000014d
#define COIN_TYPE_AION    0x800001a9
#define COIN_TYPE_PHR    0x800001bc
#define COIN_TYPE_KOTO    0x800001fe
#define COIN_TYPE_XRD    0x80000200
#define COIN_TYPE_YAP    0x80000210
#define COIN_TYPE_BCS    0x8000022b
#define COIN_TYPE_EAST    0x80000271
#define COIN_TYPE_ACT    0x8000029a
#define COIN_TYPE_SSC    0x8000029c
#define COIN_TYPE_BTW    0x80000309
#define COIN_TYPE_BEET    0x80000320
#define COIN_TYPE_DST    0x80000321
#define COIN_TYPE_QVT    0x80000328
#define COIN_TYPE_VET    0x80000332
#define COIN_TYPE_CLO    0x80000334
#define COIN_TYPE_ADF    0x80000376
#define COIN_TYPE_NEO    0x80000378
#define COIN_TYPE_XSEL    0x8000037a
#define COIN_TYPE_LBTC    0x800003e6
#define COIN_TYPE_BCD    0x800003e7
#define COIN_TYPE_BTN    0x800003e8
#define COIN_TYPE_BKT    0x800003ea
#define COIN_TYPE_ONT    0x80000400
#define COIN_TYPE_BBC    0x80000457
#define COIN_TYPE_CMT    0x80000462
#define COIN_TYPE_ETSC    0x80000468
#define COIN_TYPE_CDY    0x80000479
#define COIN_TYPE_DFC    0x80000539
#define COIN_TYPE_HYC    0x80000575
#define COIN_TYPE_TALER    0x800005f4
#define COIN_TYPE_ATH    0x80000654
#define COIN_TYPE_BCX    0x80000698
#define COIN_TYPE_XTZ    0x800006c1
#define COIN_TYPE_ADA    0x80000717
#define COIN_TYPE_TES    0x80000743
#define COIN_TYPE_CLC    0x8000076d
#define COIN_TYPE_VIPS    0x8000077f
#define COIN_TYPE_XMX    0x800007b9
#define COIN_TYPE_EGEM    0x800007c3
#define COIN_TYPE_HODL    0x800007c5
#define COIN_TYPE_POLIS    0x800007cd
#define COIN_TYPE_EOSC    0x800007e2
#define COIN_TYPE_QTUM    0x800008fd
#define COIN_TYPE_ETP    0x800008fe
#define COIN_TYPE_GXC    0x800008ff
#define COIN_TYPE_SSC2    0x80000900
#define COIN_TYPE_ELA    0x80000901
#define COIN_TYPE_AOA    0x80000a0a
#define COIN_TYPE_DEO    0x80000de0
#define COIN_TYPE_NAS    0x80000a9e
#define COIN_TYPE_ROI    0x80000d31
#define COIN_TYPE_IOTA    0x8000107a
#define COIN_TYPE_AXE    0x80001092
#define COIN_TYPE_FIC    0x00001480
#define COIN_TYPE_STAKS    0x8000167d
#define COIN_TYPE_GO    0x800017ac
#define COIN_TYPE_BPA    0x80001a0a
#define COIN_TYPE_SAFE    0x80001a20
#define COIN_TYPE_ROGER    0x80001b39
#define COIN_TYPE_BTV    0x80001e61
#define COIN_TYPE_BTQ    0x80002093
#define COIN_TYPE_SUBTC    0x800022b8
#define COIN_TYPE_BTP    0x80002327
#define COIN_TYPE_BTF    0x800026a0
#define COIN_TYPE_GOD    0x8000270f
#define COIN_TYPE_BTR    0x80002833
#define COIN_TYPE_PWR    0x800057e8
#define COIN_TYPE_ESN    0x8000797e
#define COIN_TYPE_TPIO    0x80007a69
#define COIN_TYPE_BTCS    0x80008456
#define COIN_TYPE_RSKT    0x800091be
#define COIN_TYPE_KETH    0x80010000
#define COIN_TYPE_WICC    0x8001869f
#define COIN_TYPE_AKA    0x80030fb1
#define COIN_TYPE_X42    0x80067932
#define COIN_TYPE_ETHO    0x8014095a
#define COIN_TYPE_LAX    0x801a2010
#define COIN_TYPE_BTCO    0x80501949
#define COIN_TYPE_BHD    0x8050194a
#define COIN_TYPE_WAN    0x8057414e
#define COIN_TYPE_WAVES    0x80579bfc
#define COIN_TYPE_kUSD    0x857ab1e1

/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Variable declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Function declarations */
/**@END SECTION**/


/**@NEW SECTION***********************************************************************************/
/** Compatibility with the cplusplus*/
#ifdef __cplusplus
} /* Extern C */
#endif
/**@END SECTION**/


#endif
/**@END OF FILE***********************************************************************************/
