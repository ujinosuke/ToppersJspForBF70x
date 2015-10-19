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

#if  defined(BARE_START)

#define _MACRO_ONLY

#include "jsp_kernel.h"
#include <sys/platform.h>

#define LOADIMM32REG(R,VAL) R = VAL;

/* Mask of interrupt bits to be enabled by default. Bits 0-4 unmaskable. */
#define INTERRUPT_BITS (BITM_IMASK_IVG11 | BITM_IMASK_IVG15)

#define UNASSIGNED_VAL 0x81818181

// The requiredForROMBoot file attribute is included here as this source
// defines code and data that are used before, or as part of, the meminit
// memory initialization support.
.FILE_ATTR requiredForROMBoot;

.global start;
.extern _exc_vector;
.extern ldf_stack_end;
.extern _kernel_start;
.extern _reqflg;
.extern ExpEntry;
.extern NmiEntry;
.extern IvHWEntry;
.extern IvTMREntry;
.extern Ivg7Entry;
.extern Ivg8Entry;
.extern Ivg9Entry;
.extern Ivg10Entry;
.extern Ivg11Entry;
.extern Ivg12Entry;
.extern Ivg13Entry;
.extern Ivg14Entry;
.extern _adi_initpinmux;

.SECTION/DOUBLEANY program;
.ALIGN 2;

start:
      // The assembler warning for anomaly 05-00-0312, issued when interrupts
      // are enabled and an an SSYNC, CSYNC or loop register load is used, is
      // not needed till interrupts are enabled. So we suppress it.
      .MESSAGE/SUPPRESS 5515;

      // Disable CPLBs as they might be enable by initialization code
      // or still be enabled after a software reset.
      .EXTERN __disable_cplbs;
      .TYPE __disable_cplbs,STT_FUNC;
      CALL.X __disable_cplbs;

      // Set RCU0_SVECT0 to allow a self-initiated core only reset to bypass
      // the boot code and vector straight to the beginning of L1 memory.
      R0 = start;
      [REG_RCU0_SVECT0] = R0;

      // Enable the Branch Target Buffer.
      R0 = [REG_BP_CFG];
      BITSET (R0,BITP_BP_CFG_JUMPCCEN);
      [REG_BP_CFG] = R0;
      // SYSCFG:BPEN (on by default) gets set when SYSCFG is configured.

	R0 = 0;
	LC0 = R0;
	LC1 = R0;
	L0 = R0;
	L1 = R0;
	L2 = R0;
	L3 = R0;
	.extern ldf_stack_end;
    LOADIMM32REG( p0, ldf_stack_end )
    sp = p0;
    
#ifdef USE_RUNTIME_INIT			// board_config.h ���Q��
    sp += -12;
	.EXTERN _mi_initialize;
	.TYPE _mi_initialize,STT_FUNC
	call.x _mi_initialize;   
	sp += 12;
	cc = r0;					// �Ԃ�l���`�F�b�N
invalid :
	if cc jump invalid; 		// ��0�Ȃ�G���[    
#endif

	// Set IVG3( Exception Handler)
	LOADIMM32REG(P0, EVT3)
	LOADIMM32REG(R0, ExpEntry)
	[p0++] = r0;
	
	// set IVG5 (Hardware Error)
	LOADIMM32REG(P0, EVT5)
	LOADIMM32REG(R0, IvHWEntry)
	[p0++] = r0;
	
	// set IVG6 (Core Timer)
	LOADIMM32REG(R0, IvTMREntry)
	[p0++] = r0;
	
	// set IVG7 - IVG15
	LOADIMM32REG(R0, Ivg7Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg8Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg9Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg10Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg11Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg12Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg13Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg14Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, task_level)
	[p0++] = r0;

	LOADIMM32REG( p2, user)				// �_�~�[�̖߂�Ԓn��ݒ�
	reti = p2;
	csync;
	raise	15;					// IVG15�𐶋N����B���荞�݂͒x����������B

      // Configure SYSCFG.
      R1 = SYSCFG;

      R0 = ( BITM_SYSCFG_CCEN |       // Enable the cycle counter.
             BITM_SYSCFG_SNEN |       // Enable self-nesting interrupts.
             BITM_SYSCFG_BPEN |       // Enable branch prediction.
             BITM_SYSCFG_MPWEN );     // Enable MMR posted writes.
      R1 = R0 | R1;

      SYSCFG = R1;
      
      
	r0 = ~(1<<MANAGED_INT_IVG)(z);				// IVG15����t�\��(CPU���b�N���)
	sti r0;
	csync;
	
	
	rti;						// ���[�U�[���[�h�֑J�ڂ���

task_level:                     // ��������^�X�N�̎��s����

	
	// Call Pin Config for CCES
      .EXTERN _adi_initpinmux;
      .TYPE _adi_initpinmux,STT_FUNC
      CALL.X _adi_initpinmux;
	
      // Call constructors for C++ global scope variables.
      .EXTERN ___ctorloop;
      .TYPE ___ctorloop,STT_FUNC
      CALL.X ___ctorloop;

	// SEC initial set
	r0 = 1;
	[REG_SEC0_CCTL0] = r0;
	[REG_SEC0_GCTL] = r0;
	

      .EXTERN _kernel_start;
      .TYPE _kernel_start,STT_FUNC;

    [--sp] = reti;				// �߂�Ԓn���̂ĂĊ��荞�݉\�ɂ���
    
    jump.x _kernel_start;			// kernel_stgart()����͖߂��Ă��Ȃ�

user:
	jump	user;
.start.end: // End label required by the linker to find the size of the start
            // as necessary for absolute placement.
      .GLOBAL start;
      .type start,STT_FUNC;

      // This is a NULL terminated table of functions pointers for C++
      // constructor calls before main(). The LDF should contiguously map this
      // ctor.SECTION first, then others and then ctorl. The ctorl.SECTION
      // contains the NULL terminator.
      // We need to define some data at the start of the.SECTION here so that
      // the start label is placed correctly by the linker. The data could be
      // anything as it is unused. We set it to the address of the ctor end
      // .SECTION label to force that section end label to always be required.
      // This avoids unknowingly not having the ctorl defined NULL terminator
      // linked and the various unexpected results that could cause.
.SECTION/DOUBLEANY ctor;
      .ALIGN 4;
      .GLOBAL ___ctor_table;
      .type ___ctor_table,STT_OBJECT;
      .EXTERN ___ctor_end;
      .type ___ctor_end,STT_OBJECT;
      .BYTE4 ___ctor_table = ___ctor_end;

      // The .gdt sections (global dispatch table) are used by the C++ exception
      // runtime library support to determine which area of code to which a
      // particular address belongs. These sections must be mapped contiguously
      // into memory by the LDF starting with this one and followed by .gdtl.
.SECTION/DOUBLEANY .gdt;
      .ALIGN 4;
      .GLOBAL ___eh_gdt;
      .TYPE ___eh_gdt,STT_OBJECT;
      .EXTERN ___eh_gdt_end;
      .type ___eh_gdt_end,STT_OBJECT;
      .BYTE4 ___eh_gdt = ___eh_gdt_end;





//----------------------------------------------------------------------
//--- start from main 
//---        call StartJspKernel
//----------------------------------------------------------------------
#else	// defined(BARE_START)

#define _MACRO_ONLY

#include "jsp_kernel.h"
#include <sys/platform.h>

#define LOADIMM32REG(R,VAL) R = VAL;

/* Mask of interrupt bits to be enabled by default. Bits 0-4 unmaskable. */
#define INTERRUPT_BITS (BITM_IMASK_IVG11 | BITM_IMASK_IVG15)

#define UNASSIGNED_VAL 0x81818181

// The requiredForROMBoot file attribute is included here as this source
// defines code and data that are used before, or as part of, the meminit
// memory initialization support.
.FILE_ATTR requiredForROMBoot;

.global _StartJspKernel;
.extern _exc_vector;
.extern ldf_stack_end;
.extern _kernel_start;
.extern _reqflg;
.extern ExpEntry;
.extern NmiEntry;
.extern IvHWEntry;
.extern IvTMREntry;
.extern Ivg7Entry;
.extern Ivg8Entry;
.extern Ivg9Entry;
.extern Ivg10Entry;
.extern Ivg11Entry;
.extern Ivg12Entry;
.extern Ivg13Entry;
.extern Ivg14Entry;

.SECTION/DOUBLEANY program;
.ALIGN 2;

_StartJspKernel:
      // The assembler warning for anomaly 05-00-0312, issued when interrupts
      // are enabled and an an SSYNC, CSYNC or loop register load is used, is
      // not needed till interrupts are enabled. So we suppress it.
      .MESSAGE/SUPPRESS 5515;

	R0 = 0;
	LC0 = R0;
	LC1 = R0;
	L0 = R0;
	L1 = R0;
	L2 = R0;
	L3 = R0;
	.extern ldf_stack_end;
    LOADIMM32REG( p0, ldf_stack_end )
    sp = p0;
    

	// Set IVG3( Exception Handler)
	LOADIMM32REG(P0, EVT3)
	LOADIMM32REG(R0, ExpEntry)
	[p0++] = r0;
	
	// set IVG5 (Hardware Error)
	LOADIMM32REG(P0, EVT5)
	LOADIMM32REG(R0, IvHWEntry)
	[p0++] = r0;
	
	// set IVG6 (Core Timer)
	LOADIMM32REG(R0, IvTMREntry)
	[p0++] = r0;
	
	// set IVG7 - IVG15
	LOADIMM32REG(R0, Ivg7Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg8Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg9Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg10Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg11Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg12Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg13Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, Ivg14Entry)
	[p0++] = r0;
	LOADIMM32REG(R0, task_level)
	[p0++] = r0;

	LOADIMM32REG( p2, user)				// �_�~�[�̖߂�Ԓn��ݒ�
	reti = p2;
	csync;
	raise	15;					// IVG15�𐶋N����B���荞�݂͒x����������B

      // Configure SYSCFG.
      R1 = SYSCFG;

      R0 = ( BITM_SYSCFG_CCEN |       // Enable the cycle counter.
             BITM_SYSCFG_SNEN |       // Enable self-nesting interrupts.
             BITM_SYSCFG_BPEN |       // Enable branch prediction.
             BITM_SYSCFG_MPWEN );     // Enable MMR posted writes.
      R1 = R0 | R1;

      SYSCFG = R1;
      
      
	r0 = ~(1<<MANAGED_INT_IVG)(z);				// IVG15����t�\��(CPU���b�N���)
	sti r0;
	csync;
	
	
	rti;						// ���[�U�[���[�h�֑J�ڂ���

task_level:                     // ��������^�X�N�̎��s����

	
	// SEC initial set
	r0 = 1;
	[REG_SEC0_CCTL0] = r0;
	[REG_SEC0_GCTL] = r0;
	

      .EXTERN _kernel_start;
      .TYPE _kernel_start,STT_FUNC;

    [--sp] = reti;				// �߂�Ԓn���̂ĂĊ��荞�݉\�ɂ���
    
    jump.x _kernel_start;			// kernel_stgart()����͖߂��Ă��Ȃ�

user:
	jump	user;

_StartJspKernel.end: // End label required by the linker to find the size of the start


#endif	// defined(BARE_START)





