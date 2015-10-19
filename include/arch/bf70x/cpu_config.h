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
 *	�v���Z�b�T�ˑ��̃J�[�l�������iBLACKfin�p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Ct_config.h �݂̂���C���N���[�h�����D
 *  ���̃t�@�C�����璼�ڃC���N���[�h���Ă͂Ȃ�Ȃ��D
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_


/*
 * Managed Interrupt IVG (14/13/12�̂ǂꂩ)
 */
#define MANAGED_INT_IVG		12

/*
 * 	Interrupt Group MASK( pREG_SEC0_CGMSK0 )
 */

#define	IntGroupBit_Managed				(0)
#define	IntGroupBit_Unmanaged_HLNG		(1)
#define	IntGroupBit_Unmanaged_ASM		(2)

/*
 * Interrupt Group Define ( for REG_SEC0_SCTL[n] )
 */
#define INTGROUP_MANAGE					0x00010000
#define INTGROUP_UNMANAGE_HLNG			0x00020000
#define INTGROUP_UNMANAGE_ASM			0x00040000

/*
 *  �T�[�r�X�R�[���I���}�N���̓ǂݍ���
 */
#ifdef __GNUC__
/*
 * �T�[�r�X�R�[���I���́Aconfigure�X�N���v�g�������Ȃ��̂ŁAgnu���ł͕s�v
 */
//#include <api.h>
#elif defined(__ECC__)
/*
 * �T�[�r�X�R�[���I���́AIPA���s���̂ŁAVisualDSP++���ł͂��ׂđI�����Ă���
 */
#include <api.h>
#else
#error "Compiler is not supported"
#endif

/*
 *  �C�x���g�v���C�I���e�B�錾. sys_config.h �� device_dispatcher()�Ŏg���B
 */
#ifndef ik_timer
#define ik_timer 6
#endif

#ifndef ik_hardware
#define ik_hardware_err 5
#endif

/*
 *  �J�[�l���̓������ʖ��̃��l�[��
 */
#include <cpu_rename.h>

/*
 *	BLACKfin�̃r�b�g�}�b�v�����@�\���g��
 *   BLACKfin��MSB���琔����B
 */
#define	CPU_BITMAP_SEARCH
#define	PRIMAP_BIT(pri)		(0x40000000u >> (pri))

/*
 *  TCB ���̃t�B�[���h�̃r�b�g���̒�`
 *
 *  cpu_context.h �ɓ��������G���K���g�����C�Q�Ƃ̈ˑ����̊֌W�ŁC
 *  cpu_context.h �ɂ͓�����Ȃ��D
 */
#define	TBIT_TCB_TSTAT		8	/* tstat �t�B�[���h�̃r�b�g�� */
#define	TBIT_TCB_PRIORITY	8	/* priority �t�B�[���h�̃r�b�g�� */

/*
 *	BLACKfin��IMASK�ւ̐ݒ�p�^�[��
 *
 */
#define IMASK_LOCK   0xc01f
#define IMASK_UNLOCK 0xffff

#ifndef _MACRO_ONLY
/*
 *  �v���Z�b�T�̓��ꖽ�߂̃C�����C���֐���`
 */
/*
 *  ���f�B�L���[�T�[�`�̂��߂̃r�b�g�}�b�v�T�[�`�֐�
 *
 *  �r�b�g�}�b�v�̉���16�r�b�g���g�p���C�ŉ��ʃr�b�g���Œ�D��x�ɑΉ�
 *  ������D
 */

JSP_L1_CODE
Inline UINT
bitmap_search(UINT bitmap) {
	UINT numOfSign;

	/*
	 *  ���̃R�[�h�́Cbitmap�iUINT�^�j��32�r�b�g�ł��邱�Ƃ����肵
	 *  �Ă���DSignbits ���߂�32�r�b�g�����������MSB����A������
	 *  �����r�b�g - 1 ��Ԃ��Ball 0�̂Ƃ���31��Ԃ��BLSB�݂̂�1��
	 *  �Ƃ���30��Ԃ��B
	 */
#ifdef __GNUC__			// gcc
	// gcc 3.4.1 �̎��_�ł́A�I�y�����h�ɉ��ʃn�[�t���W�X�^���w��
	// �ł��Ȃ����߁A�]�v�ȃR�[�h���K�v�ɂȂ�B
	Asm( "r0.L=signbits %1; %0 = r0.L;": "=d"(numOfSign) : "d"(bitmap) : "R0" );
#elif defined(__ECC__)	// visualdsp
	Asm( "%0=signbits %1;": "=l"(numOfSign) : "d"(bitmap) );
#else
#error "Compiler is not supported"
#endif
	return (numOfSign);
}


/*
 *  �^�X�N�R���e�L�X�g�u���b�N�̒�`
 */
typedef struct task_context_block {
	VP sp; /* �X�^�b�N�|�C���^ */
	FP pc; /* �v���O�����J�E���^ */
} CTXB;

/*
 *  �V�X�e����ԎQ��
 *	�Ԃ��l�͈ȉ��̂Ƃ���
 *	TRUE : ��^�X�N�R���e�L�X�g
 *	FALSE: �^�X�N�R���e�L�X�g
 *				IPEND��$8000��$8010�̎��A�^�X�N�R���e�L�X�g�ł���B����ȊO�̂Ƃ��͔�^�X�N�R���e�L�X�g�B
 */

JSP_L1_CODE
Inline BOOL
sense_context(void) {
	return (*pIPEND & 0x7FEF);
}

/*
 * ���݂̃��b�N��Ԃ𒲂ׂ�B�Ǘ��O���荞�݂܂Ń��b�N����sil_loc_int()��
 * ��郍�b�N��Ԃ́A����sense_lock()�ł͖�������B
 */
JSP_L1_CODE
Inline BOOL
sense_lock(void) {
	return((*pIMASK & (1<<MANAGED_INT_IVG ))== 0 );
}
#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU���b�N�Ƃ��̉����i�^�X�N�R���e�L�X�g�p�j
 *
 *  task_intmask �́Cchg_ipm ���T�|�[�g���邽�߂̕ϐ��Dchg_ipm ���T�|�[
 *  �g���Ȃ��ꍇ�ɂ́Ctask_intmask ����� 0 �ɂȂ��Ă���ƍl����΂悢�D
 *
 */

#ifdef SUPPORT_CHG_IPM
extern UH task_intmask; /* �^�X�N�R���e�L�X�g�ł̊����݃}�X�N */
#endif /* SUPPORT_CHG_IPM */

// BLACKfin�ł�IMASK��0xC01F�����������CPU�����b�N����B
JSP_L1_CODE
Inline void t_lock_cpu(void) {
	Asm( "cli r0;bitclr(r0,12);sti r0;" : : : "r0" );
}

JSP_L1_CODE
Inline void t_unlock_cpu(void) {
	Asm( "cli r0;bitset(r0,12);sti r0;" : : : "r0" );
}

/*
 *  CPU���b�N�Ƃ��̉����i��^�X�N�R���e�L�X�g�p�j
 */

JSP_L1_CODE
Inline void i_lock_cpu(void) {
	Asm( "cli r0;bitclr(r0,12);sti r0;" : : : "r0" );
}

JSP_L1_CODE
Inline void i_unlock_cpu(void) {
	Asm( "cli r0;bitset(r0,12);sti r0;" : : : "r0" );
}

/*
 *  �^�X�N�f�B�X�p�b�`��
 */

/*
 *  �ō��D�揇�ʃ^�X�N�ւ̃f�B�X�p�b�`�icpu_support.S�j
 *
 *  dispatch �́C�^�X�N�R���e�L�X�g����Ăяo���ꂽ�T�[�r�X�R�[������
 *  ���ŁCCPU���b�N��ԂŌĂяo���Ȃ���΂Ȃ�Ȃ��D
 */
extern void dispatch(void);

/*
 *  ���݂̃R���e�L�X�g���̂Ăăf�B�X�p�b�`�icpu_support.S�j
 *
 *  exit_and_dispatch �́CCPU���b�N��ԂŌĂяo���Ȃ���΂Ȃ�Ȃ��D
 */
extern void exit_and_dispatch(void);

/*
 *  �����݃n���h���^CPU��O�n���h���̐ݒ�
 */

/*
 *  �����݃n���h���̐ݒ�
 *
 *  �x�N�g���ԍ� inhno �̊����݃n���h���̋N���Ԓn�� inthdr �ɐݒ肷��D
 * evtvector ��start.asm�Œ�`����Ă���B
 */
extern void (*dev_vector[])(void);

extern void (*exc_vector)(VP);
Inline void define_inh(INHNO inhno, ATR inhatr, FP inthdr) {
	UINT priority = inhatr;
	volatile uint32_t *reg = pREG_SEC0_SCTL0;
	reg += inhno * 2;
	*reg = priority << 8;

	dev_vector[inhno] = inthdr;

}

/*
 *  CPU��O�n���h���̐ݒ�
 *
 *  �x�N�g���ԍ� excno ��CPU��O�n���h���̋N���Ԓn�� exchdr �ɐݒ肷��D
 */
Inline void define_exc(EXCNO excno, FP exchdr) {
//	exc_vector[excno] = exchdr;		// ��O�n���h����z��Ɋi�[
	exc_vector = (void (*)(VP)) exchdr; // ��O�n���h�����i�[
}

/*
 *  �����݃n���h���^CPU��O�n���h���̏o��������
 */

/*
 *  �����݃n���h���̏o���������̐����}�N��
 *
 *  reqflg ���`�F�b�N����O�Ɋ����݂��֎~���Ȃ��ƁCreqflg ���`�F�b�N��
 *  �ɋN�����ꂽ�����݃n���h�����Ńf�B�X�p�b�`���v�����ꂽ�ꍇ�ɁC�f�B
 *  �X�p�b�`����Ȃ��D
 */

#define	INTHDR_ENTRY(inthdr)	extern void inthdr(void);
#define	INT_ENTRY(inthdr)	inthdr

/*
 *  CPU��O�n���h���̏o���������̐����}�N��
 *
 *  reqflg ���`�F�b�N����O�Ɋ����݂��֎~���Ȃ��ƁCreqflg ���`�F�b�N��
 *  �ɋN�����ꂽ�����݃n���h�����Ńf�B�X�p�b�`���v�����ꂽ�ꍇ�ɁC�f�B
 *  �X�p�b�`����Ȃ��D
 */

#define	EXCHDR_ENTRY(exchdr)	extern void exchdr( VP );
#define	EXC_ENTRY(exchdr)	exchdr

/*
 *  CPU��O�̔����������̃V�X�e����Ԃ̎Q��
 */

/*
 *  CPU��O�̔����������̃R���e�L�X�g�̎Q��
 */
Inline BOOL
exc_sense_context(VP p_excinf) {
	return (*__pIPEND & 0x7FE6); // IVG15, GIE, EXP, EMU �ȊO�̃r�b�g�������Ă���Δ�^�X�N�R���e�L�X�g
}

/*
 *  CPU��O�̔�����������CPU���b�N��Ԃ̎Q�ƁB�Ǘ��O���荞�݂̏�Ԃ͖�������B
 */
Inline BOOL
exc_sense_lock(VP p_excinf) {
	return sense_lock();
}

/*
 *  �v���Z�b�T�ˑ��̏�����
 */
extern void cpu_initialize(void);

/*
 *  �v���Z�b�T�ˑ��̏I��������
 */
extern void cpu_terminate(void);


/*
 * 	�V�X�e���G���[�@�i�I���W�i���R�[�h�j
 */

// system error ���N���������ɌĂԃR�[�h
void __kernel_system_error(const char* s,... );

// system error �̊֐����I�[�o�[���C�h�ł���
void __kernel_set_system_error_message_handler( void (*func)(const char *str) );

// system error �̖₢���킹
const char* __kernel_check_system_error( void );

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
