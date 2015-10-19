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


/*
 *	�^�[�Q�b�g�V�X�e���Ɉˑ������`�iADSP-BF533�p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Ckernel.h �� sil.h �ŃC���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���邱�Ƃ͂Ȃ��D���̃t�@�C�����C��
 *  �N���[�h����O�ɁCt_stddef.h �� itron.h ���C���N���[�h�����̂ŁC
 *  �����Ɉˑ����Ă��悢�D
 */

#ifndef _CHIP_DEFS_H_
#define _CHIP_DEFS_H_

/*
 *	Section Define
 */

#include "hw_section.h"


/*
 * �V�X�e�� MMR�̒�`
 */
#define __PLL_CTL			0xFFC00000
#define __PLL_DIV			0xFFC00004

#define __SWRST				0xFFC00100
#define __SYSCR				0xFFC00104
#define __SIC_IMASK			0xFFC0010C
#define __SIC_IAR0			0xFFC00110
#define __SIC_IAR1			0xFFC00114
#define __SIC_IAR2			0xFFC00118
#define __SIC_ISR			0xFFC00120
#define __SIC_IWR			0xFFC00124

#define __TIMER2_CONFIG     0xFFC00620
#define __TIMER2_COUNTER    0xFFC00624
#define __TIMER2_PERIOD     0xFFC00628
#define __TIMER2_WIDTH      0xFFC0062C

#define __TIMER_ENABLE		0xFFC00640
#define __TIMER_DISABLE		0xFFC00644
#define __TIMER_STATUS		0xFFC00648

#define __EBIU_SDBCTL		0xFFC00A14

#define __pPLL_CTL 		((volatile unsigned short *)__PLL_CTL)
#define __pPLL_DIV 		((volatile unsigned short *)__PLL_DIV)

#define __pSWRST 			((volatile unsigned short *)__SWRST)
#define __pSYSCR 			((volatile unsigned short *)__SYSCR)
#define __pSIC_IMASK 		((volatile unsigned long *)__SIC_IMASK)
#define __pSIC_IAR0 		((volatile unsigned long *)__SIC_IAR0)
#define __pSIC_IAR1 		((volatile unsigned long *)__SIC_IAR1)
#define __pSIC_IAR2 		((volatile unsigned long *)__SIC_IAR2)
#define __pSIC_ISR 		((volatile unsigned long *)__SIC_ISR)
#define __pSIC_IWR 		((volatile unsigned long *)__SIC_IWR)

#define __pTIMER2_CONFIG 	((volatile unsigned short *)__TIMER2_CONFIG)
#define __pTIMER2_COUNTER ((volatile unsigned long *)__TIMER2_COUNTER)
#define __pTIMER2_PERIOD 	((volatile unsigned long *)__TIMER2_PERIOD)
#define __pTIMER2_WIDTH 	((volatile unsigned long *)__TIMER2_WIDTH)

#define __pTIMER_ENABLE 	((volatile unsigned short *)__TIMER_ENABLE)
#define __pTIMER_DISABLE 	((volatile unsigned short *)__TIMER_DISABLE)
#define __pTIMER_STATUS 	((volatile unsigned short *)__TIMER_STATUS)

#define __pEBIU_SDGCTL 	((volatile unsigned long *)__EBIU_SDGCTL)
#define __pEBIU_SDBCTL 	((volatile unsigned short *)__EBIU_SDBCTL)
#define __pEBIU_SDRRC 	((volatile unsigned short *)__EBIU_SDRRC)
#define __pEBIU_SDSTAT 	((volatile unsigned short *)__EBIU_SDSTAT)


/*
 *  �^�C���e�B�b�N�̒�`
 */
#define	TIC_NUME	1u	/* �^�C���e�B�b�N�̎����̕��q */
#define	TIC_DENO	1u	/* �^�C���e�B�b�N�̎����̕��� */

/*
 *  �j�󐫓ǂݏo�����W�X�^�̔��ʎ�
 *  �^����ꂽ�A�h���X iop ���j�󐫓ǂݏo�����W�X�^��
 *  �ꍇ�ɂ͐^��Ԃ��B
 */
#ifndef DESTRUCTIVE_READ
#define DESTRUCTIVE_READ( iop ) (iop<(VP)0xF0000000)
#endif

#ifndef _MACRO_ONLY

#include "cdefBF707.h"

/*
 *  �V�X�e���̒�~����
 */

Inline void
kernel_abort(void)
{
	asm volatile("emuexcpt;");
}

#endif /* _MACRO_ONLY */
#endif /* _CHIP_DEFS_H_ */
