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
 *	プロセッサ依存モジュール アセンブリ言語部（BLACKfin用）
 *  Copyright (C) 2004,2006,2006 by Takemasa Nakamura
 */

			// 32bit レジスタに即値をロードするマクロ
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
 *	(1) 管理外割り込みのアセンブラコールでもCで書かれたコードを実行できる（デバッグ用） 
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
 *  タスクディスパッチャ
 *
 *  dispatch は，割込み禁止状態で呼び出さなければならな
 *  い．exit_and_dispatch も，割込み禁止状態で呼び出す。
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
	p2 = [p0];					// p2 を runtsk に
	r1 = p2;
	cc = r1;
	if !cc jump dispatcher;
	
	[p2+TCB_sp] = sp;			// タスクスタックを保存
	LOADLABEL( r1, dispatch_r )	// 実行再開番地を保存
	[p2+TCB_pc] = r1;
			// スケジュールされたタスクを取り出す
dispatcher:
	r0 = [p1];
	[p0] = r0;					// runtsk = schedtsk
	cc = r0;
	if !cc jump dispatcher_1;	// runtskが無ければ割り込み待ちに。
	p3 = r0;					// p3はschedtsk
	sp = [p3+TCB_sp];			// タスクスタック復帰
	p5 = [p3+TCB_pc];			// 実行再開番地復帰
	jump (p5);					// 実行再開番地へ飛ぶ

			// ready タスクがない場合の割込み待ち
dispatcher_1:

	// unlock cpu
    cli r0;               		// 現在のマスクを取り出す
    bitset( r0, MANAGED_INT_IVG );
    /*
    r1 = 1(z);
    [_kernel_switch_event_stack] = r1;
	LOADLABEL( r1, ldf_stack_end)	// イベントスタックポインタを設定
	sp = r1;
	*/
	sti r0;						// CPU アンロック
	
	
wait_dispatch:

	csync;
	idle;
	csync;

	jump wait_dispatch;
	
	

			// タスクの再開番地。タスク例外の処理をおこない、
			// dispatch()から戻る
			// このアドレスへは必ず dispatcherから飛んでくる。
			// したがって、p3は必ずschedtskの内容になっている。
dispatch_r:
	fp = [sp++];
	r2 = [p3+TCB_texptn];		// schedtsk->texptn
	cc = r2 == 0;				// texptrnが0ならcc => 1
//	r0 = [p3+TCB_enatex];
//	LOADVALUE( r1, TCB_enatex_mask )
	r0 = b[p3+TCB_enatex](z);
	r1 = TCB_enatex_mask;
	r0 = r0 & r1;				// enatexが0なら、az => 1
	cc |= az;					// cc = ( !enatex || ! texptn ) = !( enatex && texptn )
	if cc jump dispatch_r_1(bp);	// if ( !enatex || !texptn ) 即リターン
	sp += -12;					// ダミー引数領域確保
	call _call_texrtn;
	sp += 12;					// ダミー引数領域開放
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
 *	TOPPERS/JSP開始処理:
 *	 start.asm は kernel_startをCPUロック状態、タスク優先順位で呼ぶ。
 *	 kernel_startはそのままexit_and_dispatchを呼ぶ。
 *	 _exit_and_dispatchは、それまでのスタック状態などを単に廃棄し、
 *	 スケジュールされたタスクを開始する。
*/
_exit_and_dispatch:
		// dispatcher以降で使うポインタを設定
	LOADLABEL( p0,  _runtsk )
	LOADLABEL( p1,  _schedtsk)
	jump dispatcher;
__kernel_exit_and_dispatch.end:

/*
 *  タスク起動時処理
 *  _activate_rへはかならずdispatcherから飛んでくる。そのため、CPUロックを
 * はずさなければならない。
 */

	.global _activate_r;
_activate_r:
    cli r0;         // 現在のマスクを取り出す。
                        // 管理外割り込みを使わないときにも、割り込み禁止のためcliが必要
    bitset(r0,MANAGED_INT_IVG);
	sti r0;				// CPU アンロック

	p0 = [sp++];		// タスクエントリーを取り出す
	r0 = [sp++];		// ext_tskの番地を取り出す
	rets = r0;			// ext_tskをダミーの戻り番地にする
	r0 = [sp++];		// ext_infを取り出す : r0 は引数1
	sp += -12;
	jump (p0);			// タスクの開始
__kernel_activate_r.end:


/*
*	割込み処理のエントリ
*
*	interrupt_handlerへはivgXXEntryからジャンプしてくる。p0レジスタには
*	割り込みレベル番号が格納されている。
*	割り込みとのネスト関係を調べ、ネストしていないならイベントスタックをセットする。
*		p2 : reqflgのアドレス
*		r6 : タスクスタック
*		r7 : ASTATの退避情報
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
	

	[--sp] = reti;				// ここで割り込み可能になる 

	save_regs_1
	
	
	// r0: reti
	// r1: [ REG_SEC0_CSID0 ]
	// p1: [_kernel_running_ivg]
	r5 = r0;					// r5に retiを保存
	p4 = p0;					// p4に　_kernel_running_ivg を保存
	p5 = r1;					// p5 に [REG_SRC0_CSID0] を保存 

	r0 = 0;
	l0 = r0;
	l1 = r0;
	l2 = r0;
	l3 = r0;
	lc0 = r0;					// 性能低下抑制のためにLCxをクリア
	lc1 = r0;
	


	//----- クリティカルな変数操作
	// Global 割り込み禁止 
	//----------------------------------------------------------
	// Stackの使用フラグを イベントスタック(1) にする 
	r7 = [_kernel_switch_event_stack];
	cc = r7;
	r1 = 1;
	cli r0;						// 割り込み禁止
	[_kernel_switch_event_stack] = r1;
	r6 = sp;					// タスクスタックポインタを退避
	
	p0 = ldf_stack_end;			// Event Stack に切り替え 
	if cc p0 = r6;
	sp = p0;	
	bitset(r0, MANAGED_INT_IVG);
	sti r0;						// unlockしてすべての割り込みを許可する。
	//----------------------------------------------------------
	
	
	// r5: reti
	// r6: previous SP
	// r7: previous _kernel_switch_event_stack value
	// p4: previous _kernel_running_ivg value
	// p5: REG_SEC0_CSID0
	
	LOADLABEL( p0, _dev_vector)
	p0 = p0 + (p5 <<2);
	p0 = [ p0 ];
	sp += -12;					// ダミー引数確保 (A)
	call	(p0);				// C言語で書かれたデバイスディスパッチャを呼ぶ
	sp += 12;					// ダミー引数開放 (A)
	
	//----- クリティカルな変数操作
	// Global 割り込み禁止 
	//----------------------------------------------------------
	cli r0;
	[ REG_SEC0_END ] = p5;		// SEC0に割り込み終了を知らせる 
	[_kernel_running_ivg] = p4;
	[_kernel_switch_event_stack] = r7;
	sp = r6;
	bitclr(r0, MANAGED_INT_IVG);
	sti r0;						// i_lock_cpu 管理外割り込みは許可する
	//----------------------------------------------------------
	
	cc = r7;
	if cc jump get_back_nest;		// もしネストしているならば、このまま帰る

								// ここでは割り込みはネストしていない
	
	r0 = [_reqflg];				// reqflgの値を取得
	cc = r0;					// ディスパッチかタスク例外の要求は出ているか
	if !cc jump get_back_nest(bp);	// 出ていないならば割り込まれたタスクに戻る

								// コンテキスト切り替え作業開始
	r0 = 0;						//
	[_reqflg] = r0;					// reqflgをクリアする.

	p0 = task_context;
	
	cli r0;						//　割り込み禁止 (retiの保護)
	reti = p0;					// ラベル"task_context"を割り込みからの戻り番地にする 	// Caution! 管理外割り込み許可の時には壊れている 
	rti;						// 割り込みから戻る。コンテキストはタスクになる
	csync;
task_context:					// ここはタスクコンテキストで、CPUロック状態である

	sti r0;						// 割り込み許可  CPUロック状態。　管理外割り込みは許可 

	r2 = [_enadsp];					// load enadsp
	cc = r2;					// ディスパッチ可能か？
	if !cc jump go_tex;			// もしディスパッチ禁止なら例外チェックに

	r1 = [_runtsk];				// runtsk
	r0 = [_schedtsk];			// schedtsk
	cc = r0 == r1;				// schedtsk == runtsk　か？
	if cc jump go_tex(bp);		// もし schedtsk == runtsk　ならば、タスク例外に行く
								// そうでなければディスパッチする
	sp += -12;					// ダミー引数領域確保 (C)
	call _dispatch;				// レッツゴー
	sp += 12;					// ダミー引数領域開放 (C)
	jump return_as_task;		// タスクに戻る

go_tex:
	p1 = [_runtsk];					// runtsk
	r0 = [_runtsk + TCB_texptn];		// runtsk->texptrnを取得 ( UINT )
	cc = r0 == 0;				// texptnが0なら1
//	r0 = [p1 + TCB_enatex];		// runtsk->enatexを取得
//	LOADVALUE( r1, TCB_enatex_mask)
	r0 = b[_runtsk + TCB_enatex](z);		// runtsk->enatexを取得
	r1 = TCB_enatex_mask;
	r1 = r0 & r1;				// タスク例外が許可されていなければ1
	cc |= az;					// 例外が許可されていないか、texptnが0ならば即帰る
	if cc jump return_as_task(bp);	// 許可されていなければタスクに戻る
	sp += -12;					// ダミー引数領域確保 (D)
	call _call_texrtn;			// 条件がそろったのでタスク例外処理を行う。
	sp += 12;					// ダミー引数領域開放 (D)

return_as_task:					// タスクコンテキスト状態での戻り

	restore_regs_1
	
	// i_unlock_cpu()
	cli r1;
	bitset(r1,MANAGED_INT_IVG);
	sti r1;

	reti = [sp++];				// 戻り番地を復帰。以後rtiまで割込み禁止
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
		
	reti = [sp++];				// 戻り番地を復帰。以後rtiまで割込み禁止

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
*	例外処理のエントリ
*
*	割り込みとのネスト関係を調べ、ネストしていないならイベントスタックをセットする。
*		p0 : ユーザー定義の例外ハンドラのアドレス
*		p1 : IPENDのアドレス
*		p2 : reqflgのアドレス
*		r6 : タスクスタック
*		r7 : ASTATの退避情報
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



// イベントハンドラのエントリーコード群。
// EVTのエントリには対応する以下のコードのラベルが格納される。
// それぞれのコードはイベント中にをp0に格納した後、
// interrupt_dispatcherにジャンプする
// evtvectorはユーザーハンドラへのポインタの配列


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
	
	//----- 管理外割り込み 

	// Stackの使用フラグを イベントスタック(1) にする 
	r1 = [_kernel_switch_event_stack];
	p1 = r1;
	cc = r1;
	r1 = 1;
	[_kernel_switch_event_stack] = r1;
	r1 = sp;					// タスクスタックポインタを退避
	
	p0 = ldf_stack_end;			// Event Stack に切り替え 
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

	[--sp] = reti;				// 割り込み可能 
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
	reti = [sp++];				// 割り込み禁止 
	
	
	// r0: _kernel_switch_event_stack	
	// r1: previous SP
	// p1: REG_SEC0_CSID0
	[ REG_SEC0_END ] = p1;		// SEC0に割り込み終了を知らせる 

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

	[--sp] = reti;				// 割り込み可能 
	
	save_regs_all_c;
	
	r0 = 0;
	l0 = r0;
	l1 = r0;
	l2 = r0;
	l3 = r0;
	lc0 = r0;					// 性能低下抑制のためにLCxをクリア
	lc1 = r0;	
	
	LOADLABEL( p0, _dev_vector)
	p0 = p0 + (p1 <<2);
	p0 = [ p0 ];	
	sp += -12;
	call (p0);
	sp += 12;
	
	restore_regs_all_c;

	reti = [sp++];				// 割り込み禁止 
	
	// r0: _kernel_switch_event_stack	
	// r1: previous SP
	// p1: REG_SEC0_CSID0
	[ REG_SEC0_END ] = p1;		// SEC0に割り込み終了を知らせる 

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
 *  微少時間待ち
 *  内側のループは12サイクルで回る。
 */
	.global _sil_dly_nse;
_sil_dly_nse:
	r1 = SIL_DLY_TIM1;
	r2 = SIL_DLY_TIM2;
	r0 = r0 - r1;			// dilay - SIL_DLY_TIM1
	cc = an;			// 結果が0より大きければ
	if !cc jump _sil_dly_nse_1;	// ループ
	rts;
_sil_dly_nse_1:
	r0 = r0 - r2;
	nop;
	cc = an;			// 結果が0より大きければ
	if !cc jump _sil_dly_nse_1;	// ループ
	rts;
_sil_dly_nse.end:




