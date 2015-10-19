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
 *	�v���Z�b�T�Ɉˑ�����A�v���P�[�V�����p�����̒�`�iBLACKfin�p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Ckernel.h �� sil.h �ŃC���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���邱�Ƃ͂Ȃ��D���̃t�@�C�����C��
 *  �N���[�h����O�ɁCt_stddef.h �� itron.h ���C���N���[�h�����̂ŁC
 *  �����Ɉˑ����Ă��悢�D
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define BLACKFIN			/* �v���Z�b�T���� */

/*
 * Core MMR
 */

#define __IMASK	0xFFE02104
#define __IPEND	0xFFE02108
#define __EVT0     0xFFE02000

#define __TCNTL    0xFFE03000
#define __TPERIOD  0xFFE03004


#define __pIMASK ((volatile unsigned long *)__IMASK)
#define __pIPEND ((volatile unsigned long *)__IPEND)
#define __pEVT0 ((volatile void * volatile) __EVT0)

#define __pTCNTL ((volatile unsigned long *)__TCNTL)
#define __pTPERIOD ((volatile unsigned long *)__TPERIOD)
/*
 *  �V�X�e���E�C���^�[�t�F�[�X�E���C���[
 */

/*
 *  �v���Z�b�T�̃G���f�B�A��
 */
#define	SIL_ENDIAN	SIL_ENDIAN_LITTLE	/* ���g���G���f�B�A�� */


/*
* ���荞�݃��b�N����
*/

#define SIL_PRE_LOC		UINT _intmask_
#define SIL_LOC_INT()	asm volatile ( "cli %0;": "=d"(_intmask_) )
#define SIL_UNL_INT()	asm volatile ( "sti %0;": :"d"(_intmask_) )





#ifndef _MACRO_ONLY

/*
 *  �����݁^CPU��O�n���h���ԍ��̌^
 */
typedef	UINT	INHNO;		/* �����݃n���h���ԍ� */
typedef	UINT	EXCNO;		/* CPU��O�n���h���ԍ� */



/*
 *  �������ԑ҂�
 *  �V�X�e���ˑ����� SIL_DLY_TIM1��SIL_DLY_TIM2���`���Ă����B
 *  SIL_DLY_TIM1��sil_dly_nse�̌Ăяo���I�[�o�[�w�b�h(nS)
 *  SIL_DLY_TIM2��sil_dly_nse�̃��[�v�̒���(nS)
 */
void sil_dly_nse(UINT dlytim);



/*
 *  ���\�]���p�V�X�e�������̎Q��
 *  cycle�J�E���^����64�r�b�g�̒l�����o���B
 */
typedef	long long	SYSUTIM;	/* ���\�]���p�V�X�e������ */

Inline  ER	vxget_tim(SYSUTIM *p_sysutim)
{
	unsigned int lo, hi;

	Asm( "%0=CYCLES; %1=CYCLES2;" :"=d"(lo), "=d"(hi) );
	((unsigned int *)p_sysutim)[0] = lo;
	((unsigned int *)p_sysutim)[1] = hi;
	return(0);
}

/*
* �V�X�e���E�������E�A�N�Z�X
*/

#define sil_wrb_iop(iop, data)	sil_wrh_mem( iop, (UB)data )
#define sil_wrh_iop	sil_wrh_mem
#define sil_wrw_iop	sil_wrw_mem
#define sil_wrh_lep sil_wrh_lem
#define sil_wrw_lep sil_wrw_lem
#define sil_wrh_bep sil_wrh_bem
#define sil_wrw_bep sil_wrw_bem

VB sil_reb_iop(VP iop);
VH sil_reh_iop(VP iop);
VW sil_rew_iop(VP iop);
VH sil_reh_lep(VP iop);
VW sil_rew_lep(VP iop);
VH sil_reh_bep(VP iop);
VW sil_rew_bep(VP iop);


#endif /* _MACRO_ONLY */




#endif /* _CPU_DEFS_H_ */
