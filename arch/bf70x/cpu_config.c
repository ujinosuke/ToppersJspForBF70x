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
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 *
 *
 */



/*
 *	プロセッサ依存モジュール（BLACKfin用）
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include <stdarg.h>

/*
 *	Override可能なSystem Error Handler
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
* イベントハンドラの入り口で保存するFPの格納変数
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
 *  プロセッサ依存の初期化
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
 *  プロセッサ依存の終了処理
 */
void
cpu_terminate()
{
	*pIMASK = 0;		/* 割り込み禁止 */
}
/*
 *	System Abort
 */

//---------------------------------------------------
//-- エラー対処コード
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
 *  システムアエラーハンドラ の設定
 */

void __kernel_set_system_error_message_handler( void (*func)(const char *str) )
{
	mfnSystemErrorHandler = func;
}

/*
 *  システムエラーの問い合わせ
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
