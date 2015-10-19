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
 *	�^�[�Q�b�g�V�X�e���ˑ����W���[���iADSP-BF70x�p�j
 */

#include "jsp_kernel.h"
#include <sil.h>


#define SYSCFG_VALUE 0x36

/*
 *  �^�[�Q�b�g�V�X�e���ˑ��̏�����
 */
void
sys_initialize()
{

}



/*
* SIC_IARx����͂��āA�C�x���g���ʂ��ƂɊ��蓖�Ă��Ă��銄�荞��
* �̃r�b�g�}�b�v�����BSIC_IARx�̃t�B�[���h�l�͗D�揇��-7�Ȃ̂�
* ���̕��␳����B
*/
#define INSTALL_PRIORITY    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                         /* IAR����D�揇�ʂ����o�� */ \
        priority_mask[priority + 7] |= device;        /* ���o�����D�揇�ʂɊ�Â��f�o�C�X��o�^ */ \
        device <<= 1;                                 /* ���̃f�o�C�X */ \
        iar >>= 4;                                    /* ����IAR�t�B�[���h */ \
    }

JSP_L1_CODE
void make_priority_mask( void )
{

}


/*
 * ���荞�݂̋��A�֎~
 *
 */
JSP_L1_CODE
ER ena_int( INTNO intno )
{
	volatile uint32_t *reg = pREG_SEC0_SCTL0;
	reg += intno*2;
	*reg |= (1<<BITP_SEC_SCTL_IEN) | (1<<BITP_SEC_SCTL_SEN);
	Asm("ssync;");
	return E_OK;
}

/*
 * dis_int()�́A���̎����ł�SIC_IMASK�̎w��r�b�g���N���A����B
 *
 * �������ASIC_IMASK�̃N���A�̓A�v���P�[�V�������s���ɂ͊댯�ł���A
 * Blackfin�̃}�j���A���ł��U�ȓI�ɋ֎~����Ă���B���̂��߁ATOPPERS/JSP for Blackfin
 * �ł́A���̊֐����������Ȃ��B
 *
 */
JSP_L1_CODE
ER dis_int( INTNO intno )
{
	volatile uint32_t *reg = pREG_SEC0_SCTL0;
	reg += intno*2;
	*reg &= ~((1<<BITP_SEC_SCTL_IEN) || (1<<BITP_SEC_CCTL_EN));
	Asm("ssync;");
	return E_OK;
}

/*
 * chg_ims()�́A���̎����ł�SIC_IMASK��ύX����B
 *
 * �������ASIC_IMASK�̃r�b�g�̃N���A�̓A�v���P�[�V�������s���ɂ͊댯�ł���A
 * Blackfin�̃}�j���A���ł��U�ȓI�ɋ֎~����Ă���B���̂��߁ATOPPERS/JSP for
 * Blackfin�ł́A���̊֐����������Ȃ��B
 *
ER chg_ims( IMS ims )
{
	*__pSIC_IMASK = ims;
	return( 0 );
}
*/

JSP_L1_CODE
extern ER get_ims( IMS * p_ims )
{
	*p_ims = *__pSIC_IMASK;
	return( 0 );;
}


/*
 *  ���荞�݂��f�o�C�X�Ɋ��蓖�Ă�
 */
JSP_L1_CODE
void sec_device_dispatcher( unsigned int devno )
{
}



/*
 *  �^�[�Q�b�g�V�X�e���̏I��
 */
void
sys_exit()
{
	while(1)
		;
}
/*
 *  �^�[�Q�b�g�V�X�e���̕����o��
 */
JSP_L1_CODE
void
sys_putc(char c)
{
}



