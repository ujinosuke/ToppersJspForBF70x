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
 *	�v���Z�b�T�ˑ����W���[�� �A�Z���u�����ꕔ�iBLACKfin�p�j
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 */

			// 32bit ���W�X�^�ɑ��l�����[�h����}�N��
#ifdef __GNUC__
#define LOADLABEL( reg, value32 ) reg##.h = value32; reg##.l = value32;
#define LOADVALUE( reg, value32 ) reg##.h = ( value32 >> 16 ) &0xFFFF; reg##.l = value32 & 0xFFFF;
#elif defined(__ECC__)
#define LOADVALUE( reg, value32 ) reg = value32;
#define LOADLABEL LOADVALUE
#else
#error "Compiler is not supported"
#endif



/*
 * DEBUG_ISR_IN_ASM_CALL_C
 *
 *	(1) �Ǘ��O���荞�݂̃A�Z���u���R�[���ł�C�ŏ����ꂽ�R�[�h�����s�ł���i�f�o�b�O�p�j 
*/
#define	DEBUG_ISR_IN_ASM_CALL_C		(0)

/*
 *	Workaround Define
 */
#define WORKAROUND_nestcheck		(0)

#define	_MACRO_ONLY
#include "jsp_kernel.h"
#include "offset.h"
#include "defBF707.h"


/*
 *  �^�X�N�f�B�X�p�b�`��
 *
 *  dispatch �́C�����݋֎~��ԂŌĂяo���Ȃ���΂Ȃ��
 *  ���Dexit_and_dispatch ���C�����݋֎~��ԂŌĂяo���B
 *  p0 : &runtsk
 *  p1 : &schedtsk
 *  p2 : runtsk
 *  p3 : schedtsk
 *  p4 : &reqflg
 */
#ifdef __GNUC__
.section .text;
#elif defined(__ECC__)

#ifdef JSP_OMIT_HW_SECTION
.section program;
#else
.section L1_code;
#endif

#else
#error "Compiler is not supported"
#endif

.global _dispatch;
.global _exit_and_dispatch;
.extern ldf_stack_end;
.extern _reqflg;
.extern _call_texrtn;
.extern _runtsk, _schedtsk;
.extern _kernel_switch_event_stack;
.extern _kernel_running_ivg;
#ifdef __GNUC__
.type _dispatch, STT_FUNC;
#elif defined(__ECC__)
#else
#error "Compiler is not supported"
#endif


_dispatch:
	[--sp] = (r7:4, p5:3);
	[--sp] = rets;
	[--sp] = fp;
	LOADLABEL( p0,  _runtsk )
	LOADLABEL( p1,  _schedtsk)
	p2 = [p0];					// p2 �� runtsk ��
	r1 = p2;
	cc = r1;
	if !cc jump dispatcher;
	
	[p2+TCB_sp] = sp;			// �^�X�N�X�^�b�N��ۑ�
	LOADLABEL( r1, dispatch_r )	// ���s�ĊJ�Ԓn��ۑ�
	[p2+TCB_pc] = r1;
			// �X�P�W���[�����ꂽ�^�X�N�����o��
dispatcher:
	r0 = [p1];
	[p0] = r0;					// runtsk = schedtsk
	cc = r0;
	if !cc jump dispatcher_1;	// runtsk��������Ί��荞�ݑ҂��ɁB
	p3 = r0;					// p3��schedtsk
	sp = [p3+TCB_sp];			// �^�X�N�X�^�b�N���A
	p5 = [p3+TCB_pc];			// ���s�ĊJ�Ԓn���A
	jump (p5);					// ���s�ĊJ�Ԓn�֔��

			// ready �^�X�N���Ȃ��ꍇ�̊����ݑ҂�
dispatcher_1:

	// unlock cpu
    cli r0;               		// ���݂̃}�X�N�����o��
    bitset( r0, MANAGED_INT_IVG );
    /*
    r1 = 1(z);
    [_kernel_switch_event_stack] = r1;
	LOADLABEL( r1, ldf_stack_end)	// �C�x���g�X�^�b�N�|�C���^��ݒ�
	sp = r1;
	*/
	sti r0;						// CPU �A�����b�N
	
	
wait_dispatch:

	csync;
	idle;
	csync;

	jump wait_dispatch;
	
	

			// �^�X�N�̍ĊJ�Ԓn�B�^�X�N��O�̏����������Ȃ��A
			// dispatch()����߂�
			// ���̃A�h���X�ւ͕K�� dispatcher������ł���B
			// ���������āAp3�͕K��schedtsk�̓��e�ɂȂ��Ă���B
dispatch_r:
	fp = [sp++];
	r2 = [p3+TCB_texptn];		// schedtsk->texptn
	cc = r2 == 0;				// texptrn��0�Ȃ�cc => 1
//	r0 = [p3+TCB_enatex];
//	LOADVALUE( r1, TCB_enatex_mask )
	r0 = b[p3+TCB_enatex](z);
	r1 = TCB_enatex_mask;
	r0 = r0 & r1;				// enatex��0�Ȃ�Aaz => 1
	cc |= az;					// cc = ( !enatex || ! texptn ) = !( enatex && texptn )
	if cc jump dispatch_r_1(bp);	// if ( !enatex || !texptn ) �����^�[��
	sp += -12;					// �_�~�[�����̈�m��
	call _call_texrtn;
	sp += 12;					// �_�~�[�����̈�J��
dispatch_r_1:
	rets = [sp++];
	(r7:4, p5:3) = [sp++];
	rts;
__kernel_dispatch.end:

#ifdef __GNUC__
.size	_dispatch, .-_dispatch
#elif defined(__ECC__)
#else
#error "Compiler is not supported"
#endif


/*
 *	TOPPERS/JSP�J�n����:
 *	 start.asm �� kernel_start��CPU���b�N��ԁA�^�X�N�D�揇�ʂŌĂԁB
 *	 kernel_start�͂��̂܂�exit_and_dispatch���ĂԁB
 *	 _exit_and_dispatch�́A����܂ł̃X�^�b�N��ԂȂǂ�P�ɔp�����A
 *	 �X�P�W���[�����ꂽ�^�X�N���J�n����B
*/
_exit_and_dispatch:
		// dispatcher�ȍ~�Ŏg���|�C���^��ݒ�
	LOADLABEL( p0,  _runtsk )
	LOADLABEL( p1,  _schedtsk)
	jump dispatcher;
__kernel_exit_and_dispatch.end:

/*
 *  �^�X�N�N��������
 *  _activate_r�ւ͂��Ȃ炸dispatcher������ł���B���̂��߁ACPU���b�N��
 * �͂����Ȃ���΂Ȃ�Ȃ��B
 */

	.global _activate_r;
_activate_r:
    cli r0;         // ���݂̃}�X�N�����o���B
                        // �Ǘ��O���荞�݂��g��Ȃ��Ƃ��ɂ��A���荞�݋֎~�̂���cli���K�v
    bitset(r0,MANAGED_INT_IVG);
	sti r0;				// CPU �A�����b�N

	p0 = [sp++];		// �^�X�N�G���g���[�����o��
	r0 = [sp++];		// ext_tsk�̔Ԓn�����o��
	rets = r0;			// ext_tsk���_�~�[�̖߂�Ԓn�ɂ���
	r0 = [sp++];		// ext_inf�����o�� : r0 �͈���1
	sp += -12;
	jump (p0);			// �^�X�N�̊J�n
__kernel_activate_r.end:


/*
*	�����ݏ����̃G���g��
*
*	interrupt_handler�ւ�ivgXXEntry����W�����v���Ă���Bp0���W�X�^�ɂ�
*	���荞�݃��x���ԍ����i�[����Ă���B
*	���荞�݂Ƃ̃l�X�g�֌W�𒲂ׁA�l�X�g���Ă��Ȃ��Ȃ�C�x���g�X�^�b�N���Z�b�g����B
*		p2 : reqflg�̃A�h���X
*		r6 : �^�X�N�X�^�b�N
*		r7 : ASTAT�̑ޔ����
*
*/

#include "saverestore.h"

.extern _dev_vector, _enadsp;
.extern _event_fp;

#ifdef __GNUC__
.type interrupt_dispatcher, STT_FUNC;
#elif defined(__ECC__)
#else
#error "Compiler is not supported"
#endif
Ivg12Entry:

	save_regs_0
	
	// i_lock_cpu()
	cli r1;
	bitclr(r1,MANAGED_INT_IVG);
	sti r1;
		
//-------------- WORKAROUND BF70x rev0.0 start
	r0 = [_kernel_running_ivg];
	p0 = r0;
	cc = bittst(r0,MANAGED_INT_IVG);
	bitset(r0,MANAGED_INT_IVG);
	[_kernel_running_ivg] = r0;
	
#if WORKAROUND_nestcheck
	if !cc jump skip_nestcheck12;
	
	r0 = reti;
	cc = bittst(r0,0);
	if cc jump skip_nestcheck12;
	
	// NEST ERROR
	// bit 0 is not set even in nested interrupt
	emuexcpt;
	csync;
	
skip_nestcheck12:
	r0 = p0;
	cc = bittst(r0,0);
#endif
	
	r0 = reti;
	r1 = reti;
	bitset(r1,0);	
	if cc r0 = r1;
	reti = r0;
//-------------- WORKAROUND BF70x rev0.0 end

	r1 = [ REG_SEC0_CSID0 ];
	[ REG_SEC0_CSID0 ]  = r1;
	

	[--sp] = reti;				// �����Ŋ��荞�݉\�ɂȂ� 

	save_regs_1
	
	
	// r0: reti
	// r1: [ REG_SEC0_CSID0 ]
	// p1: [_kernel_running_ivg]
	r5 = r0;					// r5�� reti��ۑ�
	p4 = p0;					// p4�Ɂ@_kernel_running_ivg ��ۑ�
	p5 = r1;					// p5 �� [REG_SRC0_CSID0] ��ۑ� 

	r0 = 0;
	l0 = r0;
	l1 = r0;
	l2 = r0;
	l3 = r0;
	lc0 = r0;					// ���\�ቺ�}���̂��߂�LCx���N���A
	lc1 = r0;
	


	//----- �N���e�B�J���ȕϐ�����
	// Global ���荞�݋֎~ 
	//----------------------------------------------------------
	// Stack�̎g�p�t���O�� �C�x���g�X�^�b�N(1) �ɂ��� 
	r7 = [_kernel_switch_event_stack];
	cc = r7;
	r1 = 1;
	cli r0;						// ���荞�݋֎~
	[_kernel_switch_event_stack] = r1;
	r6 = sp;					// �^�X�N�X�^�b�N�|�C���^��ޔ�
	
	p0 = ldf_stack_end;			// Event Stack �ɐ؂�ւ� 
	if cc p0 = r6;
	sp = p0;	
	bitset(r0, MANAGED_INT_IVG);
	sti r0;						// unlock���Ă��ׂĂ̊��荞�݂�������B
	//----------------------------------------------------------
	
	
	// r5: reti
	// r6: previous SP
	// r7: previous _kernel_switch_event_stack value
	// p4: previous _kernel_running_ivg value
	// p5: REG_SEC0_CSID0
	
	LOADLABEL( p0, _dev_vector)
	p0 = p0 + (p5 <<2);
	p0 = [ p0 ];
	sp += -12;					// �_�~�[�����m�� (A)
	call	(p0);				// C����ŏ����ꂽ�f�o�C�X�f�B�X�p�b�`�����Ă�
	sp += 12;					// �_�~�[�����J�� (A)
	
	//----- �N���e�B�J���ȕϐ�����
	// Global ���荞�݋֎~ 
	//----------------------------------------------------------
	cli r0;
	[ REG_SEC0_END ] = p5;		// SEC0�Ɋ��荞�ݏI����m�点�� 
	[_kernel_running_ivg] = p4;
	[_kernel_switch_event_stack] = r7;
	sp = r6;
	bitclr(r0, MANAGED_INT_IVG);
	sti r0;						// i_lock_cpu �Ǘ��O���荞�݂͋�����
	//----------------------------------------------------------
	
	cc = r7;
	if cc jump get_back_nest;		// �����l�X�g���Ă���Ȃ�΁A���̂܂܋A��

								// �����ł͊��荞�݂̓l�X�g���Ă��Ȃ�
	
	r0 = [_reqflg];				// reqflg�̒l���擾
	cc = r0;					// �f�B�X�p�b�`���^�X�N��O�̗v���͏o�Ă��邩
	if !cc jump get_back_nest(bp);	// �o�Ă��Ȃ��Ȃ�Ί��荞�܂ꂽ�^�X�N�ɖ߂�

								// �R���e�L�X�g�؂�ւ���ƊJ�n
	r0 = 0;						//
	[_reqflg] = r0;					// reqflg���N���A����.

	p0 = task_context;
	
	cli r0;						//�@���荞�݋֎~ (reti�̕ی�)
	reti = p0;					// ���x��"task_context"�����荞�݂���̖߂�Ԓn�ɂ��� 	// Caution! �Ǘ��O���荞�݋��̎��ɂ͉��Ă��� 
	rti;						// ���荞�݂���߂�B�R���e�L�X�g�̓^�X�N�ɂȂ�
	csync;
task_context:					// �����̓^�X�N�R���e�L�X�g�ŁACPU���b�N��Ԃł���

	sti r0;						// ���荞�݋���  CPU���b�N��ԁB�@�Ǘ��O���荞�݂͋��� 

	r2 = [_enadsp];					// load enadsp
	cc = r2;					// �f�B�X�p�b�`�\���H
	if !cc jump go_tex;			// �����f�B�X�p�b�`�֎~�Ȃ��O�`�F�b�N��

	r1 = [_runtsk];				// runtsk
	r0 = [_schedtsk];			// schedtsk
	cc = r0 == r1;				// schedtsk == runtsk�@���H
	if cc jump go_tex(bp);		// ���� schedtsk == runtsk�@�Ȃ�΁A�^�X�N��O�ɍs��
								// �����łȂ���΃f�B�X�p�b�`����
	sp += -12;					// �_�~�[�����̈�m�� (C)
	call _dispatch;				// ���b�c�S�[
	sp += 12;					// �_�~�[�����̈�J�� (C)
	jump return_as_task;		// �^�X�N�ɖ߂�

go_tex:
	p1 = [_runtsk];					// runtsk
	r0 = [_runtsk + TCB_texptn];		// runtsk->texptrn���擾 ( UINT )
	cc = r0 == 0;				// texptn��0�Ȃ�1
//	r0 = [p1 + TCB_enatex];		// runtsk->enatex���擾
//	LOADVALUE( r1, TCB_enatex_mask)
	r0 = b[_runtsk + TCB_enatex](z);		// runtsk->enatex���擾
	r1 = TCB_enatex_mask;
	r1 = r0 & r1;				// �^�X�N��O��������Ă��Ȃ����1
	cc |= az;					// ��O��������Ă��Ȃ����Atexptn��0�Ȃ�Α��A��
	if cc jump return_as_task(bp);	// ������Ă��Ȃ���΃^�X�N�ɖ߂�
	sp += -12;					// �_�~�[�����̈�m�� (D)
	call _call_texrtn;			// ��������������̂Ń^�X�N��O�������s���B
	sp += 12;					// �_�~�[�����̈�J�� (D)

return_as_task:					// �^�X�N�R���e�L�X�g��Ԃł̖߂�

	restore_regs_1
	
	// i_unlock_cpu()
	cli r1;
	bitset(r1,MANAGED_INT_IVG);
	sti r1;

	reti = [sp++];				// �߂�Ԓn�𕜋A�B�Ȍ�rti�܂Ŋ����݋֎~
	r0 = reti;
	bitset(r0,0);
	reti = r0;		
	
	restore_regs_0
	excpt	0;
	rti;

get_back_nest:

	restore_regs_1

	// i_unlock_cpu()
	cli r1;
	bitset(r1,MANAGED_INT_IVG);
	sti r1;
		
	reti = [sp++];				// �߂�Ԓn�𕜋A�B�Ȍ�rti�܂Ŋ����݋֎~

	restore_regs_0
	excpt	0;
	rti;
Ivg12Entry.end:

	
.global ExpEntry;
.global NmiEntry;
.global IvHWEntry;
.global IvTMREntry;
.global Ivg7Entry;
.global Ivg8Entry;
.global Ivg9Entry;
.global Ivg10Entry;
.global Ivg11Entry;
.global Ivg12Entry;
.global Ivg13Entry;
.global Ivg14Entry;
#ifdef __GNUC__
.section .text;
.type ExpEntry, STT_FUNC;
.type NmiEntry, STT_FUNC;
.type IvTMREntry, STT_FUNC;
.type IvHWEntry, STT_FUNC;
.type Ivg7Entry, STT_FUNC;
.type Ivg8Entry, STT_FUNC;
.type Ivg9Entry, STT_FUNC;
.type Ivg10Entry, STT_FUNC;
.type Ivg11Entry, STT_FUNC;
.type Ivg12Entry, STT_FUNC;
.type Ivg13Entry, STT_FUNC;
.type Ivg14Entry, STT_FUNC;
#elif defined(__ECC__)

#else
#error "Compiler is not supported"
#endif


/*
*	��O�����̃G���g��
*
*	���荞�݂Ƃ̃l�X�g�֌W�𒲂ׁA�l�X�g���Ă��Ȃ��Ȃ�C�x���g�X�^�b�N���Z�b�g����B
*		p0 : ���[�U�[��`�̗�O�n���h���̃A�h���X
*		p1 : IPEND�̃A�h���X
*		p2 : reqflg�̃A�h���X
*		r6 : �^�X�N�X�^�b�N
*		r7 : ASTAT�̑ޔ����
*
*/
ExpEntry:
	[--sp] = r0;
	[--sp] = p0;
	[--sp] = astat;
	
	r0 = seqstat;	
	r0 <<= 26;
	r0 >>= 26;
	
	cc = r0 == 0;
	if !cc jump exception_hander;
	
	
	r0 = reti;
	cc = bittst(r0,0);
	if !cc jump not_nested;	
	// Getback to task
	[--sp] = reti;		// Global Interrpt Enable
	r0 = reti;
	bitclr(r0,0);
	retx = r0;
	sp+=4;
	
not_nested:
	astat = [sp++];
	p0 = [sp++];
	r0 = [sp++];
	rtx;


exception_hander:

	r0 = 2;
	[REG_PORTB_DATA_SET]  = r0;
	ssync;
	ssync;
	emuexcpt;
	astat = [sp++];
	p0 = [sp++];
	r0 = [sp++];
	rtx;

#ifdef __GNUC__
.size	ExpEntry, .-ExpEntry
#elif defined(__ECC__)
ExpEntry.end:
#else
#error "Compiler is not supported"
#endif



// �C�x���g�n���h���̃G���g���[�R�[�h�Q�B
// EVT�̃G���g���ɂ͑Ή�����ȉ��̃R�[�h�̃��x�����i�[�����B
// ���ꂼ��̃R�[�h�̓C�x���g���ɂ�p0�Ɋi�[������A
// interrupt_dispatcher�ɃW�����v����
// evtvector�̓��[�U�[�n���h���ւ̃|�C���^�̔z��


IvHWEntry:
	emuexcpt;
	rti;
IvHWEntry.end:


IvTMREntry:
	emuexcpt;
	rti;
IvTMREntry.end:


Ivg7Entry:
	emuexcpt;
	rti;
Ivg7Entry.end:

Ivg8Entry:
	emuexcpt;
	rti;
Ivg8Entry.end:

Ivg9Entry:
	emuexcpt;	
	rti;
Ivg9Entry.end:

Ivg10Entry:
	emuexcpt;
	rti;
Ivg10Entry.end:

Ivg11Entry:
	[--sp] = r0;
	[--sp] = r1;
	[--sp] = p0;
	[--sp] = p1;
	[--sp] = astat;
	
//-------------- WORKAROUND BF70x rev0.0 start
	r0 = [_kernel_running_ivg];
	[--sp] = r0;
	cc = bittst(r0,11);
	bitset(r0,11);
	[_kernel_running_ivg] = r0;
	
#if WORKAROUND_nestcheck
	if !cc jump skip_nestcheck11;
	
	r0 = reti;
	cc = bittst(r0,0);
	if cc jump skip_nestcheck11;
	
	// NEST ERROR
	// bit 0 is not set even in nested interrupt
	emuexcpt;
	csync;
	
skip_nestcheck11:
	r0 = [sp++];
	sp += -4;
	cc = bittst(r0,11);
#endif
	
	r0 = reti;
	r1 = reti;
	bitset(r1,0);	
	if cc r0 = r1;
	reti = r0;
//-------------- WORKAROUND BF70x rev0.0 end

	r0 = [_kernel_running_ivg];
	bitset(r0,11);
	[_kernel_running_ivg] = r0;
	
	r1 = REG_SEC0_SCTL0;
	r0 = [ REG_SEC0_CSID0 ];
	r0 <<= 3;
	r0 = r0 + r1;
	p0 = r0;
	r0 = [p0];
	
	cc = bittst(r0, 15 );
	if cc jump TOPPERS_MANAGED_ISR;
	
	//----- �Ǘ��O���荞�� 

	// Stack�̎g�p�t���O�� �C�x���g�X�^�b�N(1) �ɂ��� 
	r1 = [_kernel_switch_event_stack];
	p1 = r1;
	cc = r1;
	r1 = 1;
	[_kernel_switch_event_stack] = r1;
	r1 = sp;					// �^�X�N�X�^�b�N�|�C���^��ޔ�
	
	p0 = ldf_stack_end;			// Event Stack �ɐ؂�ւ� 
	if cc p0 = r1;
	sp = p0;	
	
	cc = bittst(r0, 14 );
	r0 = p1;
	if cc jump UNMANAGED_ISR_IN_C;
	
//----------------------------------------------------------
UNMANAGED_ISR_IN_ASM:
	p1 = [ REG_SEC0_CSID0 ];

	// r0: _kernel_switch_event_stack
	// r1: previous SP
	// p1: REG_SEC0_CSID0

	[ REG_SEC0_CSID0 ] = r0;		// write any value to ack

	[--sp] = reti;				// ���荞�݉\ 
	[--sp] = rets;
	
	LOADLABEL( p0, _dev_vector)
	p0 = p0 + (p1 <<2);
	p0 = [ p0 ];	

#if DEBUG_ISR_IN_ASM_CALL_C 
	save_regs_all_c;
	sp += -12;
#endif
	
	call (p0);

#if DEBUG_ISR_IN_ASM_CALL_C
	sp += 12;
	restore_regs_all_c;
#endif
	
	rets = [sp++];
	reti = [sp++];				// ���荞�݋֎~ 
	
	
	// r0: _kernel_switch_event_stack	
	// r1: previous SP
	// p1: REG_SEC0_CSID0
	[ REG_SEC0_END ] = p1;		// SEC0�Ɋ��荞�ݏI����m�点�� 

	sp = r1;
	[_kernel_switch_event_stack] = r0;
	
	r0 = [sp++];
	[_kernel_running_ivg] = r0;
	
	astat = [sp++];
	p1 = [sp++];
	p0 = [sp++];
	r1 = [sp++];
	r0 = [sp++];
	excpt	0;
	rti;
	
//----------------------------------------------------------
UNMANAGED_ISR_IN_C:


	p1 = [ REG_SEC0_CSID0 ];
	[ REG_SEC0_CSID0 ] = r0;		// write any value to ack

	// r0: _kernel_switch_event_stack
	// r1: previoud SP
	// p1: REG_SEC0_CSID0

	[--sp] = reti;				// ���荞�݉\ 
	
	save_regs_all_c;
	
	r0 = 0;
	l0 = r0;
	l1 = r0;
	l2 = r0;
	l3 = r0;
	lc0 = r0;					// ���\�ቺ�}���̂��߂�LCx���N���A
	lc1 = r0;	
	
	LOADLABEL( p0, _dev_vector)
	p0 = p0 + (p1 <<2);
	p0 = [ p0 ];	
	sp += -12;
	call (p0);
	sp += 12;
	
	restore_regs_all_c;

	reti = [sp++];				// ���荞�݋֎~ 
	
	// r0: _kernel_switch_event_stack	
	// r1: previous SP
	// p1: REG_SEC0_CSID0
	[ REG_SEC0_END ] = p1;		// SEC0�Ɋ��荞�ݏI����m�点�� 

	sp = r1;
	[_kernel_switch_event_stack] = r0;
	
	r0 = [sp++];
	[_kernel_running_ivg] = r0;
	
	astat = [sp++];
	p1 = [sp++];
	p0 = [sp++];
	r1 = [sp++];
	r0 = [sp++];
	excpt	0;
	rti;
	
//----------------------------------------------------------
TOPPERS_MANAGED_ISR:

	raise MANAGED_INT_IVG;
	
	r0 = [sp++];
	[_kernel_running_ivg] = r0;
	
	astat = [sp++];
	p1 = [sp++];
	p0 = [sp++];
	r1 = [sp++];
	r0 = [sp++];
	excpt 0;
	rti;
Ivg11Entry.end:

#if 0
Ivg12Entry:
	emuexcpt;
	rti;
Ivg12Entry.end:
#endif

Ivg13Entry:
	emuexcpt;
	rti;
Ivg13Entry.end:

Ivg14Entry:
	emuexcpt;
	rti;
Ivg14Entry.end:

NmiEntry:
	jump	NmiEntry;
	rtn;
#ifdef __GNUC__
.size	NmiEntry, .-NmiEntry
#elif defined(__ECC__)
NmiEntry.end:
#else
#error "Compiler is not supported"
#endif




/*
 *  �������ԑ҂�
 *  �����̃��[�v��12�T�C�N���ŉ��B
 */
	.global _sil_dly_nse;
_sil_dly_nse:
	r1 = SIL_DLY_TIM1;
	r2 = SIL_DLY_TIM2;
	r0 = r0 - r1;			// dilay - SIL_DLY_TIM1
	cc = an;			// ���ʂ�0���傫�����
	if !cc jump _sil_dly_nse_1;	// ���[�v
	rts;
_sil_dly_nse_1:
	r0 = r0 - r2;
	nop;
	cc = an;			// ���ʂ�0���傫�����
	if !cc jump _sil_dly_nse_1;	// ���[�v
	rts;
_sil_dly_nse.end:




