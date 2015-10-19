/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 *  Copyright (C) 2004 by Ujinosuke
 *
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 *
 *
 */


#ifndef _CHIP_CONFIG_H_
#define _CHIP_CONFIG_H_


/*
 *	ターゲットシステム依存モジュール（ADSP-BF531/2/3共用）
 *
 *  このインクルードファイルは，t_config.h のみからインクルードされる．
 *  他のファイルから直接インクルードしてはならない．
*/

/*
 *  ターゲットシステムのハードウェア資源の定義
 *
 */

#define DEVICE_INTERRUPT_COUNT 105



/*
 *  PLLクロック周波数
 */
#define PLLCLOCK (CLKIN*MSELVAL)
#define SYSCLOCK  (PLLCLOCK / SSELVAL)
#define CORECLOCK (PLLCLOCK / CSELVAL)



/*
 *  TICの割込みハンドラのベクタ番号
 */
#ifdef USE_TIC_CORE
#define INHNO_TIMER	INHNO_CORE_TIMER
#else
#define INHNO_TIMER	INHNO_TIMER0_TMR7
#endif

/*
 *  Timer 用　Clock 設定マクロ
 */
#define TIMER_PER_MS(x)		(SYSCLOCK/1000*x)
#define TIMER_PER_US(x)		(SYSCLOCK/1000000*x)

/*
 *  微少時間待ちのための定義
 *  sil_dly_nseの呼び出しオーバーヘッドとループボディーサイクルを
 *  nSで表す。関数はcpu_support.asmに定義してある。
 *  SIL_DLY_TIM1は24サイクル。32nS( 750MHz ), 40nS( 600MHz )
 *  SIL_DLY_TIM2は12サイクル。16nS( 750MHz ), 20nS( 600MHz )
 */


#define	SIL_DLY_TIM1	(24*1000000000/CORECLOCK)
#define	SIL_DLY_TIM2	(12*1000000000/CORECLOCK)

/*************************************************************************
 * uart.c用構成マクロ
 */

/*  シリアルの割込みハンドラのベクタ番号 */
#define INHNO_SIO0_TX   INHNO_UART0_TXDMA
#define INHNO_SIO0_RX   INHNO_UART0_RXDMA
#define INHNO_SIO1_TX   INHNO_UART1_TXDMA
#define INHNO_SIO1_RX   INHNO_UART1_RXDMA

/*
 *  UARTレジスタの配置境界。ADSP-BF533の内蔵UARTは4バイト周期でレジスタが
 *  並んでいるので、ここには4を指定する。
 */
#define UART_BOUNDARY 4

/*  UARTレジスタにsil_xxb_iop()を使ってアクセスするときにはUART_IOP_ACCESSを 宣言する。*/
#define UART_IOP_ACCESS

/*  シリアルポートのアドレス。 */
#define UART0_ADDRESS 0x2005F000
#define UART1_ADDRESS 0x2005F400

/*  UARTのボーレートジェネレータに設定すべき値． */
#define UART0_DIVISOR	SYSCLOCK/16/UART0_BAUD_RATE
#define UART1_DIVISOR	SYSCLOCK/16/UART1_BAUD_RATE

/*  内蔵UARTを使う場合は、UARTx_BLACKFIN_UCENを宣言してUCENを初期化しなければならない。*/
#define UART0_BLACKFIN_UCEN
#define UART1_BLACKFIN_UCEN


/*
 * uart.c用構成マクロ終わり
 *************************************************************************/



/*
 *  割り込みベクトル番号
 *
 *  この定義はコンフィグレーションファイルでDEF_INHの引数として使う
 *  SIC_ISRにおけるビット番号である。
 *
 */
/*#define INHNO_RESERVED				0*/
#define INHNO_SEC0_ERR					1
#define INHNO_CGU0_EVT					2
#define INHNO_WDOG0_EXP					3
#define INHNO_L2CTL0_ECC_ERR			4
/*#define INHNO_RESERVED				5*/
#define INHNO_C0_DBL_FAULT				6
#define INHNO_C0_HW_ERR					7
#define INHNO_C_NMI_L1_PARITY_ERR		8
#define INHNO_L2CTL0_EVT				9
/*#define INHNO_RESERVED				10*/
#define INHNO_TIMER0_TMR0				11
#define INHNO_TIMER0_TMR1				12
#define INHNO_TIMER0_TMR2				13
#define INHNO_TIMER0_TMR3				14
#define INHNO_TIMER0_TMR4				15
#define INHNO_TIMER0_TMR5				16
#define INHNO_TIMER0_TMR6				17
#define INHNO_TIMER0_TMR7				18
#define INHNO_TIMER0_STAT				19
#define INHNO_PINT0_BLOCK				20
#define INHNO_PINT1_BLOCK				21
#define INHNO_PINT2_BLOCK				22
#define INHNO_EPPI0_STAT				23
#define	INHNO_EPPI0_CH0_DMA				24
#define	INHNO_EPPI0_CH1_DMA				25
#define	INHNO_DMAC_ERR					26
#define	INHNO_CNT0_STAT					27
#define	INHNO_SPORT0_A_STAT				28
#define	INHNO_SPORT0_A_DMA				29
#define	INHNO_SPORT0_B_STAT				30
#define	INHNO_SPORT0_B_DMA				31
#define	INHNO_SPORT1_A_STAT				32
#define	INHNO_SPORT1_A_DMA				33
#define	INHNO_SPORT1_B_STAT				34
#define	INHNO_SPORT1_B_DMA				35
#define	INHNO_SPI0_ERR					36
#define	INHNO_SPI0_STAT					37
#define	INHNO_SPI0_TXDMA				38
#define	INHNO_SPI0_RXDMA				39
#define	INHNO_SPI1_ERR					40
#define	INHNO_SPI1_STAT					41
#define	INHNO_SPI1_TXDMA				42
#define	INHNO_SPI1_RXDMA				43
#define	INHNO_SPI2_ERR					44
#define	INHNO_SPI2_STAT					45
#define	INHNO_SPI2_TXDMA				46
#define	INHNO_SPI2_RXDMA				47
#define	INHNO_UART0_STAT				48
#define	INHNO_UART0_TXDMA				49
#define	INHNO_UART0_RXDMA				50
#define	INHNO_UART1_STAT				51
#define	INHNO_UART1_TXDMA				52
#define	INHNO_UART1_RXDMA				53
#define	INHNO_MDMA0_SRC					54
#define	INHNO_MDMA0_DST					55
#define	INHNO_MDMA1_SRC					56
#define	INHNO_MDMA1_DST					57
#define	INHNO_MDMA2_SRC					58
#define	INHNO_MDMA2_DST					59
#define	INHNO_HADC0_EVT					60
#define	INHNO_RTC0_EVT					61
#define	INHNO_TWI0_DATA					62
#define	INHNO_CRC0_DCNTEXP				63
#define	INHNO_CRC0_ERR					64
#define	INHNO_CRC1_DCNTEXP				65
#define	INHNO_CRC1_ERR					66
#define	INHNO_PKTE0_IRQ					67
#define	INHNO_PKIC0_IRQ					68
/*#define	INHNO_RESERVED					69*/
/*#define	INHNO_RESERVED					70*/
#define	INHNO_OTPC0_ERR					71
#define	INHNO_MSI0_STAT					72
#define	INHNO_SMPU0_ERR					73
#define	INHNO_SMPU1_ERR					74
/*#define	INHNO_RESERVED				75*/
#define	INHNO_SPU0_INT					76
#define	INHNO_USB0_STAT					77
#define	INHNO_USB0_DATA					78
#define	INHNO_TRU0_SLV0					79
#define	INHNO_TRU0_SLV1					80
#define	INHNO_TRU0_SLV2					81
#define	INHNO_TRU0_SLV3					82
#define	INHNO_CGU0_ERR					83
#define	INHNO_DPM0_EVT					84
#define	INHNO_SPIHP0_ERR				85
#define	INHNO_SYS_SOFT0_INT				86
#define	INHNO_SYS_SOFT1_INT				87
#define	INHNO_SYS_SOFT2_INT				88
#define	INHNO_SYS_SOFT3_INT				89
#define	INHNO_CAN0_RX					90
#define	INHNO_CAN0_TX					91
#define	INHNO_CAN0_STAT					92
#define	INHNO_CAN1_RX					93
#define	INHNO_CAN1_TX					94
#define	INHNO_CAN1_STAT					95
#define	INHNO_CTI0_C0_EVT				96
#define	INHNO_SWU0_EVT					97
#define	INHNO_SWU1_EVT					98
#define	INHNO_SWU2_EVT					99
#define	INHNO_SWU3_EVT					100
#define	INHNO_SWU4_EVT					101
#define	INHNO_SWU5_EVT					102
#define	INHNO_SWU6_EVT					103
#define	INHNO_SWU7_EVT					104
#define	INHNO_TAPC0_KEYFAIL				105

/*
 *  SIC_ISRの割り込みのベクタ番号
 *
 *  この定義はena_int, dis_intの引数として使う。
 */

/*#define INTNO_RESERVED				0*/
#define INTNO_SEC0_ERR					1
#define INTNO_CGU0_EVT					2
#define INTNO_WDOG0_EXP					3
#define INTNO_L2CTL0_ECC_ERR			4
/*#define INTNO_RESERVED				5*/
#define INTNO_C0_DBL_FAULT				6
#define INTNO_C0_HW_ERR					7
#define INTNO_C_NMI_L1_PARITY_ERR		8
#define INTNO_L2CTL0_EVT				9
/*#define INTNO_RESERVED				10*/
#define INTNO_TIMER0_TMR0				11
#define INTNO_TIMER0_TMR1				12
#define INTNO_TIMER0_TMR2				13
#define INTNO_TIMER0_TMR3				14
#define INTNO_TIMER0_TMR4				15
#define INTNO_TIMER0_TMR5				16
#define INTNO_TIMER0_TMR6				17
#define INTNO_TIMER0_TMR7				18
#define INTNO_TIMER0_STAT				19
#define INTNO_PINT0_BLOCK				20
#define INTNO_PINT1_BLOCK				21
#define INTNO_PINT2_BLOCK				22
#define INTNO_EPPI0_STAT				23
#define	INTNO_EPPI0_CH0_DMA				24
#define	INTNO_EPPI0_CH1_DMA				25
#define	INTNO_DMAC_ERR					26
#define	INTNO_CNT0_STAT					27
#define	INTNO_SPORT0_A_STAT				28
#define	INTNO_SPORT0_A_DMA				29
#define	INTNO_SPORT0_B_STAT				30
#define	INTNO_SPORT0_B_DMA				31
#define	INTNO_SPORT1_A_STAT				32
#define	INTNO_SPORT1_A_DMA				33
#define	INTNO_SPORT1_B_STAT				34
#define	INTNO_SPORT1_B_DMA				35
#define	INTNO_SPI0_ERR					36
#define	INTNO_SPI0_STAT					37
#define	INTNO_SPI0_TXDMA				38
#define	INTNO_SPI0_RXDMA				39
#define	INTNO_SPI1_ERR					40
#define	INTNO_SPI1_STAT					41
#define	INTNO_SPI1_TXDMA				42
#define	INTNO_SPI1_RXDMA				43
#define	INTNO_SPI2_ERR					44
#define	INTNO_SPI2_STAT					45
#define	INTNO_SPI2_TXDMA				46
#define	INTNO_SPI2_RXDMA				47
#define	INTNO_UART0_STAT				48
#define	INTNO_UART0_TXDMA				49
#define	INTNO_UART0_RXDMA				50
#define	INTNO_UART1_STAT				51
#define	INTNO_UART1_TXDMA				52
#define	INTNO_UART1_RXDMA				53
#define	INTNO_MDMA0_SRC					54
#define	INTNO_MDMA0_DST					55
#define	INTNO_MDMA1_SRC					56
#define	INTNO_MDMA1_DST					57
#define	INTNO_MDMA2_SRC					58
#define	INTNO_MDMA2_DST					59
#define	INTNO_HADC0_EVT					60
#define	INTNO_RTC0_EVT					61
#define	INTNO_TWI0_DATA					62
#define	INTNO_CRC0_DCNTEXP				63
#define	INTNO_CRC0_ERR					64
#define	INTNO_CRC1_DCNTEXP				65
#define	INTNO_CRC1_ERR					66
#define	INTNO_PKTE0_IRQ					67
#define	INTNO_PKIC0_IRQ					68
/*#define	INTNO_RESERVED					69*/
/*#define	INTNO_RESERVED					70*/
#define	INTNO_OTPC0_ERR					71
#define	INTNO_MSI0_STAT					72
#define	INTNO_SMPU0_ERR					73
#define	INTNO_SMPU1_ERR					74
/*#define	INTNO_RESERVED				75*/
#define	INTNO_SPU0_INT					76
#define	INTNO_USB0_STAT					77
#define	INTNO_USB0_DATA					78
#define	INTNO_TRU0_SLV0					79
#define	INTNO_TRU0_SLV1					80
#define	INTNO_TRU0_SLV2					81
#define	INTNO_TRU0_SLV3					82
#define	INTNO_CGU0_ERR					83
#define	INTNO_DPM0_EVT					84
#define	INTNO_SPIHP0_ERR				85
#define	INTNO_SYS_SOFT0_INT				86
#define	INTNO_SYS_SOFT1_INT				87
#define	INTNO_SYS_SOFT2_INT				88
#define	INTNO_SYS_SOFT3_INT				89
#define	INTNO_CAN0_RX					90
#define	INTNO_CAN0_TX					91
#define	INTNO_CAN0_STAT					92
#define	INTNO_CAN1_RX					93
#define	INTNO_CAN1_TX					94
#define	INTNO_CAN1_STAT					95
#define	INTNO_CTI0_C0_EVT				96
#define	INTNO_SWU0_EVT					97
#define	INTNO_SWU1_EVT					98
#define	INTNO_SWU2_EVT					99
#define	INTNO_SWU3_EVT					100
#define	INTNO_SWU4_EVT					101
#define	INTNO_SWU5_EVT					102
#define	INTNO_SWU6_EVT					103
#define	INTNO_SWU7_EVT					104
#define	INTNO_TAPC0_KEYFAIL				105

#ifndef _MACRO_ONLY

/*
* SIC_IARxを解析して、イベント順位ごとに割り当てられている割り込み
* のビットマップを作る。SIC_IARxのフィールド値は優先順位-7なので
* その分補正する。
*/
void make_priority_mask( void );

/*
 *  ターゲットシステム依存の初期化
 */
extern void	sys_initialize(void);

/*
 *  ターゲットシステムの終了
 *
 *  システムを終了する時に使う．ROMモニタ／GDB STUB呼出しで実現する．
 */
extern void	sys_exit(void);

/*
 *  ターゲットシステムの文字出力
 *
 *  システムの低レベルの文字出力ルーチン．ROMモニタ／GDB STUB呼出しで実
 *  現する．
 */
extern void	sys_putc(char c);

/*
* SIC_IARxを解析して、イベント順位ごとに割り当てられている割り込み
* のビットマップを作る。SIC_IARxのフィールド値は優先順位-7なので
* その分補正する。
*/
void make_priority_mask( void );

/*
 * 割り込みの許可、禁止
 *
 */
typedef unsigned int INTNO;
extern ER ena_int( INTNO intno );
extern ER dis_int( INTNO intno );

/*
 * 割り込みマスクの操作
 *
 *
 */
typedef unsigned int IMS;
extern ER chg_ims( IMS ims );
extern ER get_ims( IMS * p_ims );

/*
 * 割り込みを起こしたデバイスを調べる
*/
extern void device_dispatcher(  unsigned int priority, unsigned int imask );

#endif /* _MACRO_ONLY */
#endif /* _CHIP_CONFIG_H_ */
