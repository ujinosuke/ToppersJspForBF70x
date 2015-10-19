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
 *	�v���Z�b�T�ˑ����W���[���iBLACKfin�p�j
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include <stdarg.h>

/*
 *	Override�\��System Error Handler
 */
static void (*mfnSystemErrorHandler)(const char* str ) = 0;
/*
 *	System Error Flag
 */
static BOOL mbSystemErrorOccured = FALSE;

/*
 *	System Error Message
 */
static char msSystemErrorMsg[128] = { '\0' };

static void default_system_error(const char * str);

/*
* �C�x���g�n���h���̓�����ŕۑ�����FP�̊i�[�ϐ�
*/
VP event_fp;

static void dummy_exception_handler(VP exc_info);
void (* exc_vector)(VP) = &dummy_exception_handler;
void (* dev_vector[DEVICE_INTERRUPT_COUNT])(void) ;

BOOL kernel_switch_event_stack;
UW kernel_running_ivg;

static void dummy_interrupt_handler(void)
{
	asm volatile("emuexcpt;");
	//while(1)
	//	;
}

static void dummy_exception_handler(VP exc_info)
{
	asm volatile("emuexcpt;");
	while(1)
		;
}


/*
 *  �v���Z�b�T�ˑ��̏�����
 */
void
cpu_initialize()
{
	int i;

	for ( i=0; i<DEVICE_INTERRUPT_COUNT; i++ )
		dev_vector[i] = &dummy_interrupt_handler;

	kernel_switch_event_stack = FALSE;
	kernel_running_ivg = 0;

	mfnSystemErrorHandler = default_system_error;
}

/*
 *  �v���Z�b�T�ˑ��̏I������
 */
void
cpu_terminate()
{
	*pIMASK = 0;		/* ���荞�݋֎~ */
}
/*
 *	System Abort
 */

//---------------------------------------------------
//-- �G���[�Ώ��R�[�h
//---------------------------------------------------

static void default_system_error(const char* s)
{
	Asm("emuexcpt;");

	while(1);
}
void __kernel_system_error(const char* s,... )
{
//	va_list arg;
//	va_start( arg, s );
//	vsprintf( msSystemErrorMsg, s, arg );

//	asm volatile(".extern _msSystemErrorMsg;	p0.h = _msSystemErrorMsg; p0.l = _msSystemErrorMsg; ");
//	asm volatile("emuexcpt;");

	mbSystemErrorOccured = TRUE;
	if(	mfnSystemErrorHandler )
		mfnSystemErrorHandler( msSystemErrorMsg );
}

/*
 *  �V�X�e���A�G���[�n���h�� �̐ݒ�
 */

void __kernel_set_system_error_message_handler( void (*func)(const char *str) )
{
	mfnSystemErrorHandler = func;
}

/*
 *  �V�X�e���G���[�̖₢���킹
 */
const char* __kernel_check_system_error( void )
{
	return  mbSystemErrorOccured ? msSystemErrorMsg : 0;
}


//---------------------------------------------------
//-- malloc/free over-ride
//---------------------------------------------------
#define HEAP_CHECK			(0)

#include <stdlib.h>

JSP_L1_DATA
unsigned long	max_heap = 0;

JSP_L1_CODE
void *malloc(size_t size)
{
	void * result;

	if ( iniflg && !sense_lock() )
	{
		dis_dsp();
		result = heap_malloc( 0, size );
		ena_dsp();
	}
	else
	{
		result = heap_malloc( 0, size );
	}

#if HEAP_CHECK == 1
	{
		unsigned long r = (unsigned long)result + size;
		if( r > max_heap) max_heap = r;
	}
#endif

	return( result );
}

JSP_L1_CODE
void free(void *ptr)
{
	void * result;

	if ( iniflg && !sense_lock() )
	{
		dis_dsp();
		heap_free( 0, ptr );
		ena_dsp();
	}
	else
	{
		heap_free( 0, ptr );
	}

}
