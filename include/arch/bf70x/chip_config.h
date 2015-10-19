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
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 *
 *
 */


#ifndef _CHIP_CONFIG_H_
#define _CHIP_CONFIG_H_


/*
 *	�^�[�Q�b�g�V�X�e���ˑ����W���[���iADSP-BF531/2/3���p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Ct_config.h �݂̂���C���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���Ă͂Ȃ�Ȃ��D
*/

/*
 *  �^�[�Q�b�g�V�X�e���̃n�[�h�E�F�A�����̒�`
 *
 */

#define DEVICE_INTERRUPT_COUNT 105



/*
 *  PLL�N���b�N���g��
 */
#define PLLCLOCK (CLKIN*MSELVAL)
#define SYSCLOCK  (PLLCLOCK / SSELVAL)
#define CORECLOCK (PLLCLOCK / CSELVAL)



/*
 *  TIC�̊����݃n���h���̃x�N�^�ԍ�
 */
#ifdef USE_TIC_CORE
#define INHNO_TIMER	INHNO_CORE_TIMER
#else
#define INHNO_TIMER	INHNO_TIMER0_TMR7
#endif

/*
 *  Timer �p�@Clock �ݒ�}�N��
 */
#define TIMER_PER_MS(x)		(SYSCLOCK/1000*x)
#define TIMER_PER_US(x)		(SYSCLOCK/1000000*x)

/*
 *  �������ԑ҂��̂��߂̒�`
 *  sil_dly_nse�̌Ăяo���I�[�o�[�w�b�h�ƃ��[�v�{�f�B�[�T�C�N����
 *  nS�ŕ\���B�֐���cpu_support.asm�ɒ�`���Ă���B
 *  SIL_DLY_TIM1��24�T�C�N���B32nS( 750MHz ), 40nS( 600MHz )
 *  SIL_DLY_TIM2��12�T�C�N���B16nS( 750MHz ), 20nS( 600MHz )
 */


#define	SIL_DLY_TIM1	(24*1000000000/CORECLOCK)
#define	SIL_DLY_TIM2	(12*1000000000/CORECLOCK)

/*************************************************************************
 * uart.c�p�\���}�N��
 */

/*  �V���A���̊����݃n���h���̃x�N�^�ԍ� */
#define INHNO_SIO0_TX   INHNO_UART0_TXDMA
#define INHNO_SIO0_RX   INHNO_UART0_RXDMA
#define INHNO_SIO1_TX   INHNO_UART1_TXDMA
#define INHNO_SIO1_RX   INHNO_UART1_RXDMA

/*
 *  UART���W�X�^�̔z�u���E�BADSP-BF533�̓���UART��4�o�C�g�����Ń��W�X�^��
 *  ����ł���̂ŁA�����ɂ�4���w�肷��B
 */
#define UART_BOUNDARY 4

/*  UART���W�X�^��sil_xxb_iop()���g���ăA�N�Z�X����Ƃ��ɂ�UART_IOP_ACCESS�� �錾����B*/
#define UART_IOP_ACCESS

/*  �V���A���|�[�g�̃A�h���X�B */
#define UART0_ADDRESS 0x2005F000
#define UART1_ADDRESS 0x2005F400

/*  UART�̃{�[���[�g�W�F�l���[�^�ɐݒ肷�ׂ��l�D */
#define UART0_DIVISOR	SYSCLOCK/16/UART0_BAUD_RATE
#define UART1_DIVISOR	SYSCLOCK/16/UART1_BAUD_RATE

/*  ����UART���g���ꍇ�́AUARTx_BLACKFIN_UCEN��錾����UCEN�����������Ȃ���΂Ȃ�Ȃ��B*/
#define UART0_BLACKFIN_UCEN
#define UART1_BLACKFIN_UCEN


/*
 * uart.c�p�\���}�N���I���
 *************************************************************************/



/*
 *  ���荞�݃x�N�g���ԍ�
 *
 *  ���̒�`�̓R���t�B�O���[�V�����t�@�C����DEF_INH�̈����Ƃ��Ďg��
 *  SIC_ISR�ɂ�����r�b�g�ԍ��ł���B
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
 *  SIC_ISR�̊��荞�݂̃x�N�^�ԍ�
 *
 *  ���̒�`��ena_int, dis_int�̈����Ƃ��Ďg���B
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
* SIC_IARx����͂��āA�C�x���g���ʂ��ƂɊ��蓖�Ă��Ă��銄�荞��
* �̃r�b�g�}�b�v�����BSIC_IARx�̃t�B�[���h�l�͗D�揇��-7�Ȃ̂�
* ���̕��␳����B
*/
void make_priority_mask( void );

/*
 *  �^�[�Q�b�g�V�X�e���ˑ��̏�����
 */
extern void	sys_initialize(void);

/*
 *  �^�[�Q�b�g�V�X�e���̏I��
 *
 *  �V�X�e�����I�����鎞�Ɏg���DROM���j�^�^GDB STUB�ďo���Ŏ�������D
 */
extern void	sys_exit(void);

/*
 *  �^�[�Q�b�g�V�X�e���̕����o��
 *
 *  �V�X�e���̒჌�x���̕����o�̓��[�`���DROM���j�^�^GDB STUB�ďo���Ŏ�
 *  ������D
 */
extern void	sys_putc(char c);

/*
* SIC_IARx����͂��āA�C�x���g���ʂ��ƂɊ��蓖�Ă��Ă��銄�荞��
* �̃r�b�g�}�b�v�����BSIC_IARx�̃t�B�[���h�l�͗D�揇��-7�Ȃ̂�
* ���̕��␳����B
*/
void make_priority_mask( void );

/*
 * ���荞�݂̋��A�֎~
 *
 */
typedef unsigned int INTNO;
extern ER ena_int( INTNO intno );
extern ER dis_int( INTNO intno );

/*
 * ���荞�݃}�X�N�̑���
 *
 *
 */
typedef unsigned int IMS;
extern ER chg_ims( IMS ims );
extern ER get_ims( IMS * p_ims );

/*
 * ���荞�݂��N�������f�o�C�X�𒲂ׂ�
*/
extern void device_dispatcher(  unsigned int priority, unsigned int imask );

#endif /* _MACRO_ONLY */
#endif /* _CHIP_CONFIG_H_ */
