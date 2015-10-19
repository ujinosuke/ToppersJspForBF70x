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


#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_


/*
 *  �J�[�l���̓������ʖ��̃��l�[��
 */
#include <sys_rename.h>


/* blackfin/_common_bf533����ǂݍ��� */
#include <chip_config.h>

/*
 *	�^�[�Q�b�g�V�X�e���ˑ����W���[���iKOBANZAME�p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Ct_config.h �݂̂���C���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���Ă͂Ȃ�Ȃ��D
*/

/*
 * �ǂ̂悤�ȃN���b�N���͂ɂ��Ή��ł���悤�A�ȉ���CSEL, SSEL, MSEL�̒l
 * �ƃN���b�N���͎��g��(Hz)���w�肷��BPLL�̃v���O������sys_config.c��
 * sys_initialize()�֐��ōs����B
 *
 * CSELVAL��1,2,4,8�̒�����I�ԁBCLKIN�̒P�ʂ�Hz
 */

#define CSELVAL 1
#define SSELVAL 4
#define MSELVAL 16
#define CLKIN 25000000


/*
 * �n�[�h�E�F�A�E�G���[���荞�݂̋���
 * QUICK_HW_ERROR��define����ƁA�n�[�h�E�F�A�E�G���[�E�C�x���g
 * �������Ɏ󗝂����Bdefine���Ȃ��ꍇ�ɂ́A���荞�ݑ҂���Ԃ�
 * �n�[�h�E�F�A�E�G���[�E���荞�݂����������ꍇ�A���̊��荞�݂܂�
 * �҂�����邱�ƂɂȂ�B
 *
 */
//#define QUICK_HW_ERROR


/*
 * ���s���������֐��̎g�p
 *
 * �}�N�� USE_RUNTIME_INIT ���`����ƁAstart.asm�̂Ȃ��� _mi_initialize
 * ���Ăяo���B���̊֐��̓m�[�u�[�g���[�h�ŋN������Ƃ��ɂ̂ݕK�v�ɂȂ�̂�
 * �ʏ�� USE_RUNTIME_INIT���g���K�v�͂Ȃ��B
 * �ڍׂ�ADI��EE239�ɏڂ����Bhttp://tinyurl.com/2hpbk (tinyURL)
 *
*/
//#define USE_RUNTIME_INIT

/*
 * �J�[�l���Ǘ��O���荞�݂̐錾
 *
 * �}�N��UNMANAGED_INT�̓J�[�l���Ǘ��O���荞�݂�錾����B����
 * �}�N����16�r�b�g�̃r�b�g�}�b�v�ɂȂ��Ă���A�ȉ��ɂ���p�^�[��
 * �̂����ЂƂ��g���B�Ȃ��A�ǂ̂悤�ȃp�^�[����I��ł�NMI�͊Ǘ��O
 * �����݂Ƃ��Ĉ�����B
 * UNMANAGED_INT��錾���Ȃ��ꍇ�ANMI�������Ǘ��O�����݂Ƃ��Ĉ�����B
 *
*/
//#define UNMANAGED_INT 0x0020			// IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x0060			// IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x00E0			// IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x01E0			// IVG8 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x03E0			// IVG9 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x07E0			// IVG10 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x0FE0			// IVG11 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x1FE0			// IVG12 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.
//#define UNMANAGED_INT 0x3FE0			// IVG13 ... IVG7, IVTMR��IVHW���J�[�l���Ǘ��O.

/*
 * C++�֘A������p�ӂ���
 *
 * �}�N��INIT_C_PLUS_PLUS���`����ƁAC++����p�̃e�[�u����
 * �������R�[�h�����s����B�܂��AC++����p�̃e�[�u����錾����
 *
*/
#define INIT_C_PLUS_PLUS

/*
 *  �N�����b�Z�[�W�̃^�[�Q�b�g�V�X�e����
 */
#define	TARGET_NAME	"KOBANZAME"


/*
 *  �V���A���|�[�g���̒�`
 *  TNUM_SIOP_XXX�́AUART�̎�ʂ��Ƃɐ錾����B
 *  TNUM_SIOP_UART��BF533����UART�̂����APDIC���g�p������́B
 *  BF533��UART���ЂƂ��������Ă��Ȃ��̂ŁA1��0��錾����B
 *  TNUM_PORT�́ATNUM_SIOP_XXX�̂����AGDIC���g�p������̂̑��a�B
 *  uart.c�Ŏg���B
 */
#define TNUM_PORT	1		/* GDIC���T�|�[�g����V���A���|�[�g�̐� */
#define TNUM_SIOP_UART	1	/* PIDC���T�|�[�g����V���A���|�[�g�̐� */

/*
 *  �V���A���|�[�g�ԍ��Ɋւ����`
 *  ���O�^�X�N���V���A���|�[�g���g��Ȃ��ꍇ�͖������Ă����B
 */
#define	LOGTASK_PORTID	1	/* �V�X�e�����O�ɗp����V���A���|�[�g�ԍ� */

/*  UART0�̃{�[���[�g�D */
#define UART0_BAUD_RATE 9600		/* 9600 baud */
#define UART1_BAUD_RATE 9600		/* 9600 baud */

/*
 * PLL�̏������̋���
 * PLL�́APLL_CTL���W�X�^���f�t�H���g�l�ŁA���ASDRAM�R���g���[����
 * �f�B�Z�[�u���̂Ƃ��Ɍ��菉�������s���悤�ɂȂ��Ă���B����́A�u�[�g
 * ���[�_�[�Ȃǂ̏������\�t�g��SDRAM�������������Ƃ��ɂ����ی삷�邽��
 * �ł���B�����VisualDSP++�̃f�o�b�K��SDRAM�������ŏ��������邽�߁A
 * ���̋@�\�Ƃ��܂��܂荇�������Ȃ��ꍇ������B
 * �󋵂Ɋւ�炸��ɏ��������������ɂ� FORCE_PLL_INITIALIZE �}�N����
 * �錾����B
 */
// #deinfe FORCE_PLL_INITIALIZE

#endif /* _SYS_CONFIG_H_ */
