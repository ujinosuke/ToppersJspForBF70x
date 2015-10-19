/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 */

/*
 *   ADSP-BF533 UART�p �Ȉ�SIO�h���C�o
 *
 *   ���̃t�@�C���́ATOPPERS/JSP 1.4.2�� pdic/simple_sio/st16c2550.c��
 *   ���l�[�����A�����̎��ʎq��ύX�������̂ł���B
 */
#include <kernel.h>
#include <s_services.h>
#include "uart.h"

// UART bps define
//
#define UART_BPS		(9600)
//#define UART_BPS		(115200)



// UART registers
//
#define UART_CTL       (0x01 * UART_BOUNDARY)
#define UART_STAT      (0x02 * UART_BOUNDARY)
#define UART_SCR       (0x03 * UART_BOUNDARY)
#define UART_CLK       (0x04 * UART_BOUNDARY)
#define UART_IMSK      (0x05 * UART_BOUNDARY)
#define UART_IMSK_SET  (0x06 * UART_BOUNDARY)
#define UART_IMSK_CLR  (0x07 * UART_BOUNDARY)
#define UART_RBR       (0x08 * UART_BOUNDARY)
#define UART_THR       (0x09 * UART_BOUNDARY)
#define UART_TAIP      (0x0A * UART_BOUNDARY)
#define UART_TSR       (0x0B * UART_BOUNDARY)
#define UART_RSR       (0x0C * UART_BOUNDARY)
#define UART_TXCNT     (0x0F * UART_BOUNDARY)
#define UART_RXCNT     (0x0E * UART_BOUNDARY)

/*
 * ���W�X�^�̃r�b�g�}�X�N�B����@�\��ǉ����Ȃ�����A���������Ȃ��Ă悢�B
 */

#define ISR_TX            0x02       /* ���M���荞�ݔ��� */
#define IER_TX            0x02       /* ���M���荞�݋��� */
#define ISR_RX            0x01       /* ��M���荞�ݔ��� */
#define IER_RX            0x01       /* ��M���荞�݋��� */

#define LCR_DL_MODE       0x80       /* Divisor Enable */
#define LCR_NP_8_1        0x03       /* 8bit,1stop,Noparity,No break */
#define FCR_FIFO_DISABLE  0x00

#define LSR_RX_DATA_READY 0x01
#define LSR_TX_EMPTY      0x20

#define MCR_INT_ENABLE    0x08

#define GCTL_UCEN		  0x01		/* Blackfin�̂� */

/*
 * TNUM_SIOP_UART, UART0_ADDRESS, UART0_DIVISOR ��sys_config.h�Œ�`����B
 *	TNUM_SIOP_UART : PDIC���Ǘ�����UART�̌�
 *  �ȉ��APDIC���Ǘ�����ŏ���UART�̏��
 *  	UART0_ADDRESS : 		THR�̃A�h���X
 *  	UART0_DIVISOR : 		DLM, DLL�̏����l(16bit�\�L)
 *      UART0_14550_FIFO : 		14550�݊���FIFO�����Ƃ��Ƀ}�N����錾����
 *		UART0_BLACKFIN_UCEN : 	Blackfin��p�B�}�N����錾����Ə������R�[�h��UART_GCTL��UCEN��1�ɂ���B
 *	��ڈȍ~��UART������Ȃ�ȉ��̂悤�ɑ�����B
 *  	UART1_ADDRESS : 		THR�̃A�h���X
 *  	UART1_DIVISOR : 		DLM, DLL�̏����l(16bit�\�L)
 *      UART1_14550_FIFO : 		14550�݊���FIFO�����Ƃ��Ƀ}�N����錾����
 *		UART1_BLACKFIN_UCEN : 	Blackfin��p�B�}�N����錾����Ə������R�[�h��UART_GCTL��UCEN��1�ɂ���B
 *	...
 */

/******************************************************************************************
 * �V���A��I/O�|�[�g�������u���b�N
 */
#if TNUM_SIOP_UART == 0 
#error "If you don't use UART, please remove this file from your make file" 
#endif

#if TNUM_SIOP_UART > 3
#error "Only TNUM_SIOP_UART < 4 is supported" 
#endif /* TNUM_SIOP_UART >= 2 */    

/* �f�B�o�C�U�v�Z�}�N�� */
#define DLM(divisor) (divisor/256)
#define DLL(divisor) (divisor%256)

SIOPINIB siopinib_table[TNUM_SIOP_UART] = {
/*-----------------------------------------------------------------
 *			PDIC���Ǘ�����ŏ���UART�̏������p�����[�^ 
 */
#ifdef BLACKFIN707_BLIP2
{ UART1_ADDRESS, DLM(UART1_DIVISOR), DLL(UART1_DIVISOR),
#else
{ UART0_ADDRESS, DLM(UART0_DIVISOR), DLL(UART0_DIVISOR),
#endif
#ifdef UART0_BLACKFIN_UCEN
		1 /* �}�N��UART0_BLACKFIN_UCEN����`����Ă�����AGCTL��UCEN��1�ɂ��ăN���b�N�𓮂��� */
#else
		0
#endif
		}

/*-----------------------------------------------------------------
 *			PDIC���Ǘ�����2�Ԗڂ�UART�̏������p�����[�^ 
 */

#if TNUM_SIOP_UART > 1
		, {	UART1_ADDRESS, DLM(UART1_DIVISOR), DLL(UART1_DIVISOR),
#ifdef UART1_BLACKFIN_UCEN
		1 /* �}�N��UART1_BLACKFIN_UCEN����`����Ă�����AGCTL��UCEN��1�ɂ��ăN���b�N�𓮂��� */
#else
		0
#endif

	}
#endif /* if TNUM_SIOP_UART > 1*/

		/*-----------------------------------------------------------------
		 *			PDIC���Ǘ�����3�Ԗڂ�UART�̏������p�����[�^
		 */
#if TNUM_SIOP_UART > 2
		, {	UART2_ADDRESS, DLM(UART2_DIVISOR), DLL(UART2_DIVISOR),
#ifdef UART2_BLACKFIN_UCEN
		1 /* �}�N��UART2_BLACKFIN_UCEN����`����Ă�����AGCTL��UCEN��1�ɂ��ăN���b�N�𓮂��� */
#else
		0
#endif

	}
#endif /* if TNUM_SIOP_UART > 2*/

}		;

/*
 * �V���A��I/O�|�[�g�������u���b�N�����܂ŁB
 ******************************************************************************************/

/*
 *  �V���A��I/O�|�[�g�������u���b�N�̎�o��
 */
#define INDEX_SIOPINIB(siopid)  ((UINT)((siopid) - 1))
#define get_siopinib(siopid)  (&(siopinib_table[INDEX_SIOPINIB(siopid)]))

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̃G���A
 */
JSP_L1_DATA
SIOPCB siopcb_table[TNUM_SIOP_UART];

/*
 *  �V���A��I/O�|�[�gID����Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_SIOP(siopid)  ((UINT)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))

#if 1
JSP_L1_CODE
/*Inline*/ void uart_write(UW addr, UW offset, UW val) {
	*((UW*) (addr + offset)) = val;
	asm volatile("ssync;");
}
JSP_L1_CODE
/*Inline*/ UW uart_read(UW addr, UW offset) {
	UW ret=  *((UW*) (addr + offset));
	asm volatile("ssync;");
	return ret;
}

#else
Inline void
uart_write(UW addr, UW offset, UB val)
{
#ifdef UART_IOP_ACCESS
	sil_wrb_iop((VP)(addr + offset),val);
#else
	sil_wrb_mem((VP)(addr + offset),val);
#endif
}

Inline UB
uart_read(UW addr, UW offset)
{
#ifdef UART_IOP_ACCESS
	return(sil_reb_iop((VP)(addr + offset)));
#else
	return(sil_reb_mem((VP)(addr + offset)));
#endif
}
#endif

/*
 * ��������M������?
 */
JSP_L1_CODE
Inline BOOL uart_getready(SIOPCB *siopcb) {
#if 1
	UW status;
	status = uart_read(siopcb->siopinib->reg_base, UART_STAT);
	return (status & (1 << 0));

#else
	UH status;

	status = uart_read(siopcb->siopinib->reg_base, UART_LSR);

	return((status & LSR_RX_DATA_READY));
#endif
}

/*
 * �����𑗐M�ł��邩?
 */
JSP_L1_CODE
Inline BOOL uart_putready(SIOPCB *siopcb) {
#if 1
	UW status;
	status = uart_read(siopcb->siopinib->reg_base, UART_STAT);
	return (status & (1 << 5));
#else
	UH status;

	status = uart_read(siopcb->siopinib->reg_base, UART_LSR);

	return (status & LSR_TX_EMPTY);
#endif
}

/*
 *  ��M���������̎��o��
 */
JSP_L1_CODE
Inline UB uart_getchar(SIOPCB *siopcb) {
#if 1
	return (UB) (uart_read(siopcb->siopinib->reg_base, UART_RBR));
#else
	return(uart_read(siopcb->siopinib->reg_base,UART_RBR));
#endif
}

/*
 *  ���M���镶���̏�������
 */
JSP_L1_CODE
Inline void uart_putchar(SIOPCB *siopcb, UB c) {
#if 1
	uart_write(siopcb->siopinib->reg_base, UART_THR, c);
#else
	uart_write(siopcb->siopinib->reg_base, UART_THR, c);
#endif
}

/*
 *  ���M�����݋���
 */
JSP_L1_CODE
Inline void uart_enable_send(SIOPCB *siopcb) {
#if 1
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_SET, (1 << 1));
#else
	uart_write(siopcb->siopinib->reg_base, UART_IER,
			(uart_read(siopcb->siopinib->reg_base,UART_IER) | IER_TX));
#endif
}

/*
 *  ���M�����݋֎~
 */
JSP_L1_CODE
Inline void uart_disable_send(SIOPCB *siopcb) {
#if 1
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_CLR, (1 << 1));
#else
	uart_write(siopcb->siopinib->reg_base, UART_IER,
			(uart_read(siopcb->siopinib->reg_base, UART_IER) & ~IER_TX));

#endif
}

/*
 *  ��M�����݋���
 */
JSP_L1_CODE
Inline void uart_enable_rcv(SIOPCB *siopcb) {
#if 1
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_SET, (1 << 0));
#else
	uart_write(siopcb->siopinib->reg_base, UART_IER,
			(uart_read(siopcb->siopinib->reg_base,UART_IER) | IER_RX));
#endif
}

/*
 *  ��M�����݋֎~
 */
JSP_L1_CODE
Inline void uart_disable_rcv(SIOPCB *siopcb) {
#if 1
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_CLR, (1 << 0));
#else
	uart_write(siopcb->siopinib->reg_base, UART_IER,
			(uart_read(siopcb->siopinib->reg_base, UART_IER) & ~IER_RX));
#endif

}

/*
 *  SIO�h���C�o�̏��������[�`��
 */
void uart_initialize() {
	SIOPCB *siopcb;
	UINT i;

	/*
	 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̏�����
	 */
	for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP_UART; siopcb++, i++) {
		siopcb->siopinib = &(siopinib_table[i]);
		siopcb->openflag = FALSE;
		siopcb->sendflag = FALSE;
	}
}

/*
 *
 */
void uart_init_siopinib(const SIOPINIB *siopinib) {

	/* �����݋֎~ */
	uart_write(siopinib->reg_base, UART_IMSK_CLR, 0xFFFF);

	/*
	 *  ������̐ݒ�
	 *  regval = SCLK /  bps
	 */
	uart_write(siopinib->reg_base, UART_CLK, 0x800028B1); // 96000bps
	//uart_write(siopinib->reg_base, UART_CLK, (SYSCLOCK / UART_BPS) | (1<<31) );

	/* ���[�h�ݒ�, �p���e�B���� 8bit data, 1 stop bit */
	uart_write(siopinib->reg_base, UART_CTL, 0x00000301);

}

/*
 *  �J�[�l���N�����̃o�i�[�o�͗p�̏�����
 */
void uart_init(void) {
	int i;
	/*
	 * ���ׂĂ�uart������������Bid ��1����TNUM_SIOP_UART�܂ŁB
	 */
	for (i = 1; i <= TNUM_SIOP_UART; i++)
		uart_init_siopinib(get_siopinib(i));
}

/*
 * �I�[�v�����Ă���|�[�g�����邩
 */
BOOL uart_openflag(void) {
	int i;

	/*
	 * �J���Ă���|�[�g�������0��Ԃ��B�Ȃ����0��Ԃ��B
	 */
	for (i = 0; i < TNUM_SIOP_UART; i++)
		if (siopcb_table[0].openflag)
			return (1);
	return (0);
}

/*
 * �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB *
uart_opn_por(ID siopid, VP_INT exinf) {
	SIOPCB *siopcb;
	const SIOPINIB *siopinib;

	siopcb = get_siopcb(siopid);
	siopinib = siopcb->siopinib;

	/*
	 * ������
	 */
	uart_init_siopinib(siopcb->siopinib);

	/* ��M�����݋��� */
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_SET, (1 << 0));

	siopcb->exinf = exinf;
	siopcb->getready = siopcb->putready = FALSE;
	siopcb->openflag = TRUE;

	return (siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void uart_cls_por(SIOPCB *siopcb) {
	/* �����݋֎~ */
	uart_write(siopcb->siopinib->reg_base, UART_IMSK_CLR, 0x03);
	siopcb->openflag = FALSE;
}

/*
 *  �V���A��I/O�|�[�g�ւ̃|�[�����O�ł̏o��
 */
void uart_pol_putc(char c, ID siopid) {
	const SIOPINIB *siopinib;

	siopinib = get_siopinib(siopid);

	while (!(uart_read(siopinib->reg_base, UART_STAT) & (1 << 5)))
		;
	uart_write(siopinib->reg_base, UART_THR, c);
}

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
JSP_L1_CODE
BOOL uart_snd_chr(SIOPCB *siopcb, char c) {
	if (uart_putready(siopcb)) {
		uart_putchar(siopcb, c);
		return (TRUE);
	}
	return (FALSE);
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
JSP_L1_CODE
INT uart_rcv_chr(SIOPCB *siopcb) {
	if (uart_getready(siopcb)) {
		return ((INT) (UB) uart_getchar(siopcb));
	}
	return (-1);
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn) {

	switch (cbrtn) {
	case SIO_ERDY_SND:
		uart_enable_send(siopcb);
		break;
	case SIO_ERDY_RCV:
		uart_enable_rcv(siopcb);
		break;
	}
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn) {
	switch (cbrtn) {
	case SIO_ERDY_SND:
		uart_disable_send(siopcb);
		break;
	case SIO_ERDY_RCV:
		uart_disable_rcv(siopcb);
		break;
	}
}

/*
 *  �V���A��I/O�|�[�g�ɑ΂��銄���ݏ���
 */
JSP_L1_CODE
static void uart_rx_isr_siop(SIOPCB *siopcb) {
	if (uart_getready(siopcb)) {
		/*
		 *  ��M�ʒm�R�[���o�b�N���[�`�����Ăяo���D
		 */
		uart_ierdy_rcv(siopcb->exinf);
	}
}
JSP_L1_CODE
static void uart_tx_isr_siop(SIOPCB *siopcb) {
	if (uart_putready(siopcb)) {
		/*
		 *  ���M�\�R�[���o�b�N���[�`�����Ăяo���D
		 */
		uart_ierdy_snd(siopcb->exinf);
	}
}

/*
 *  SIO�̊����݃T�[�r�X���[�`��
 *	ADSP-BF533�̓���UART�͑���ɕʁX�̊����ݗv�����o�����߁A
 *  ISR�������Ă���B�܂��AADSP-BF537�̂悤�ɓ�ȏ��
 *  UART�����ꍇ���l�����āAuart0�̂悤�Ƀ|�[�g�ԍ���
 *  ���O�Ƀn�[�h�R�[�h���Ă���B
 *  �������A���̃|�[�g�ԍ��Ƃ́ASIO�̃|�[�g�ԍ��ł����āA
 *  �n�[�h�E�F�A��UART�ԍ��Ɠ������Ƃ͌���Ȃ��B
 */

/*
 ***** UART0
 */
JSP_L1_CODE
void uart0_rx_isr() {
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[0]));
}

JSP_L1_CODE
void uart0_tx_isr() {
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[0]));
}

/*
 ***** UART1
 */
JSP_L1_CODE
void uart1_rx_isr() {
	/* ���ʂ̎�M�������Ă� */
#ifdef BLACKFIN707_BLIP2
	uart_rx_isr_siop(&(siopcb_table[0]));
#else
	uart_rx_isr_siop(&(siopcb_table[1]));
#endif
}
JSP_L1_CODE
void uart1_tx_isr() {
	/* ���ʂ̑��M�������Ă� */
#ifdef BLACKFIN707_BLIP2
	uart_tx_isr_siop(&(siopcb_table[0]));
#else
	uart_tx_isr_siop(&(siopcb_table[1]));
#endif
}

/*
 ***** UART2
 */
JSP_L1_CODE
void uart2_rx_isr() {
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[2]));
}
JSP_L1_CODE
void uart2_tx_isr() {
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[2]));
}

/*
 * UART�̑���Ŋ����݂����L����ꍇ�i������̂ق�����ʓI�j�́A
 * ��̃��[�`���ł͂Ȃ�������������݃T�[�r�X���[�`���Ƃ��Ďg���B
 */
JSP_L1_CODE
void uart0_isr() {
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[0]));
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[0]));
}
JSP_L1_CODE
void uart1_isr() {
#ifdef BLACKFIN707_BLIP2
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[0]));
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[0]));
#else
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[1]));
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[1]));
#endif
}
JSP_L1_CODE
void uart2_isr() {
	/* ���ʂ̎�M�������Ă� */
	uart_rx_isr_siop(&(siopcb_table[2]));
	/* ���ʂ̑��M�������Ă� */
	uart_tx_isr_siop(&(siopcb_table[2]));
}
