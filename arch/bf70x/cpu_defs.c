/*
 *  TOPPERS/JSP for Blackfin
 *
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
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
// DESTRUCTIVE_READ��sys_defs.h�Œ�`����B 

// �j�󐫓ǂݏo�����W�X�^�ɃA�N�Z�X����ꍇ��
// ���荞�݃��b�N��������

#include <kernel.h>
#include <s_services.h>

#define __SIL_LOCK_INTERRUPT( x ) \
	if (DESTRUCTIVE_READ(iop)){\
		SIL_PRE_LOC;\
		SIL_LOC_INT();\
		x;\
		SIL_UNL_INT();\
	}\
	else\
		x;

JSP_L1_CODE
 VB sil_reb_iop(VP iop)
{
	VH temp;
//	PROLOGUE
	
    __SIL_LOCK_INTERRUPT( temp = sil_reh_mem((VP)iop) );

//	EPILOGUE;
    return temp;
}

JSP_L1_CODE
 VH sil_reh_iop(VP iop)
{
	VH temp;

    __SIL_LOCK_INTERRUPT( temp = sil_reh_mem((VP)iop) );

    return temp;
}

JSP_L1_CODE
 VW sil_rew_iop(VP iop)
{
	VW temp;

    __SIL_LOCK_INTERRUPT( temp = sil_rew_mem((VP)iop) );

    return temp;
}

JSP_L1_CODE
 VH sil_reh_lep(VP iop)
{
	VH temp;
	
    __SIL_LOCK_INTERRUPT( temp = sil_reh_lem((VP)iop) );

    return temp;
}

JSP_L1_CODE
 VW sil_rew_lep(VP iop)
{
	VW temp;
	
    __SIL_LOCK_INTERRUPT( temp = sil_rew_lem((VP)iop) );

    return temp;
}

JSP_L1_CODE
 VH sil_reh_bep(VP iop)
{
	VH temp;
	
    __SIL_LOCK_INTERRUPT( temp = sil_reh_bem((VP)iop) );

    return temp;
}

JSP_L1_CODE
 VW sil_rew_bep(VP iop)
{
	VW temp;
	
    __SIL_LOCK_INTERRUPT( temp = sil_rew_bem((VP)iop) );

    return temp;
}

