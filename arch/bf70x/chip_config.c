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
 *	ターゲットシステム依存モジュール（ADSP-BF70x用）
 */

#include "jsp_kernel.h"
#include <sil.h>


#define SYSCFG_VALUE 0x36

/*
 *  ターゲットシステム依存の初期化
 */
void
sys_initialize()
{

}



/*
* SIC_IARxを解析して、イベント順位ごとに割り当てられている割り込み
* のビットマップを作る。SIC_IARxのフィールド値は優先順位-7なので
* その分補正する。
*/
#define INSTALL_PRIORITY    \
    for ( i=0; i<8; i++ ){ \
        priority = iar & 0xf;                         /* IARから優先順位を取り出す */ \
        priority_mask[priority + 7] |= device;        /* 取り出した優先順位に基づきデバイスを登録 */ \
        device <<= 1;                                 /* 次のデバイス */ \
        iar >>= 4;                                    /* 次のIARフィールド */ \
    }

JSP_L1_CODE
void make_priority_mask( void )
{

}


/*
 * 割り込みの許可、禁止
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
 * dis_int()は、この実装ではSIC_IMASKの指定ビットをクリアする。
 *
 * しかし、SIC_IMASKのクリアはアプリケーション実行中には危険であり、
 * Blackfinのマニュアルでも婉曲的に禁止されている。そのため、TOPPERS/JSP for Blackfin
 * では、この関数を実装しない。
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
 * chg_ims()は、この実装ではSIC_IMASKを変更する。
 *
 * しかし、SIC_IMASKのビットのクリアはアプリケーション実行中には危険であり、
 * Blackfinのマニュアルでも婉曲的に禁止されている。そのため、TOPPERS/JSP for
 * Blackfinでは、この関数を実装しない。
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
 *  割り込みをデバイスに割り当てる
 */
JSP_L1_CODE
void sec_device_dispatcher( unsigned int devno )
{
}



/*
 *  ターゲットシステムの終了
 */
void
sys_exit()
{
	while(1)
		;
}
/*
 *  ターゲットシステムの文字出力
 */
JSP_L1_CODE
void
sys_putc(char c)
{
}



