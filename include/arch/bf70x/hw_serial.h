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
 *  �V���A��I/O�f�o�C�X�iSIO�j�h���C�o�iBlackfin UART�p�j
 *
 *   ���̃t�@�C���́ATOPPERS/JSP 1.4.2�� config/sh3/ms7727cp01/hw_serial.h��
 *   ���l�[�����A�����̎��ʎq��ύX�������̂ł���B
 *
 *   ���̃t�@�C���͉��ʂ̃f�o�C�X�E�A�N�Z�X�E���[�`���𑩂˂ď�ʂ̑w�ɓn��
 *   ���߂̂��̂ł���BBlackfin�̊O���ɂ���V���A����TOPPERS/JSP�ŊǗ����Ȃ�
 *   �̂Ȃ�A�ύX����K�v�͂Ȃ��B
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include <s_services.h>

#include "uart.h"

/*
 * Serial �����̐錾
 */
typedef struct {
	ID		semid_rx1;
	ID		semid_tx1;
} hw_serial_RSC_t;

/*
 *  SIO�h���C�o�̏��������[�`��
 */
#define sio_initialize  uart_initialize

#ifndef _MACRO_ONLY
/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
Inline SIOPCB *
sio_opn_por(ID siopid, VP_INT exinf)
{
    SIOPCB  *siopcb;

    /*
     *  �f�o�C�X�ˑ��̃I�[�v�������D
     */
    siopcb = uart_opn_por(siopid, exinf);

	/*
	* Enable Corrensponding Interrupt at IMASK
	* Note that, this implementation has only 1 SIO in a system
	*/
#ifdef BLACKFIN707_BLIP2		// BLIP2 �� UART1�ɐڑ�����Ă���
	ena_int( INTNO_UART1_TXDMA );
	ena_int( INTNO_UART1_RXDMA );
#else
	ena_int( INTNO_UART0_TXDMA );
	ena_int( INTNO_UART0_RXDMA );
#endif

    return(siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
Inline void
sio_cls_por(SIOPCB *siopcb)
{

	/*
	 * �����ł�SIC_IMASK�̑Ή��r�b�g���N���A���Ȃ��BSIC_IMASK�̃N���A��
	 * �댯�ł���BUART����̊��荞�݂� uart_cls_por�����ŋ֎~����̂�
	 * �[���ł���B
	 */

    /*
     *  �f�o�C�X�ˑ��̃N���[�Y�����D
     */
    uart_cls_por(siopcb);
}


/*
 *  SIO�̊����݃n���h��
 */
#define sio0_rx_handler uart0_rx_isr
#define sio0_tx_handler uart0_tx_isr
#define sio1_rx_handler uart1_rx_isr
#define sio1_tx_handler uart1_tx_isr

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
#define sio_snd_chr uart_snd_chr

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
#define sio_rcv_chr uart_rcv_chr

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
#define sio_ena_cbr uart_ena_cbr

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
#define sio_dis_cbr uart_dis_cbr

/*
 *  �V���A��I/O�|�[�g����̑��M�\�R�[���o�b�N
 */
#define sio_ierdy_snd   uart_ierdy_snd

/*
 *  �V���A��I/O�|�[�g����̎�M�ʒm�R�[���o�b�N
 */
#define sio_ierdy_rcv   uart_ierdy_rcv

#endif /* _MACRO_ONLY */
#endif /* _HW_SERIAL_H_ */
