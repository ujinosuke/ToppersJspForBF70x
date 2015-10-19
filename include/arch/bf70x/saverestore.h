/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 */

#define save_regs_0\
	[--sp] = astat;\
	[--sp] = p0;\
	[--sp] = r0;\
	[--sp] = r1;

#define restore_regs_0\
	r1 = [sp++];\
	r0 = [sp++];\
	p0 = [sp++];\
	astat = [sp++];

#define save_regs_1\
		link 0;	\
		[--SP] = (R7:2,P5:1);\
		[--SP] = I3;\
		[--SP] = I2;\
		[--SP] = I1;\
		[--SP] = I0;\
		[--SP] = M3;\
		[--SP] = M2;\
		[--SP] = M1;\
		[--SP] = M0;\
		[--SP] = B3;\
		[--SP] = B2;\
		[--SP] = B1;\
		[--SP] = B0;\
		[--SP] = L3;\
		[--SP] = L2;\
		[--SP] = L1;\
		[--SP] = L0;\
		[--SP] = A0.x;\
		[--SP] = A0.w;\
		[--SP] = A1.x;\
		[--SP] = A1.w;\
		[--SP] = LC1;\
		[--SP] = LC0;\
		[--SP] = LT1;\
		[--SP] = LT0;\
		[--SP] = LB1;\
		[--SP] = LB0;

#define restore_regs_1\
		LB0 = [SP++];\
		LB1 = [SP++];\
		LT0 = [SP++];\
		LT1 = [SP++];\
		LC0 = [SP++];\
		LC1 = [SP++];\
		A1.w = [SP++];\
		A1.x = [SP++];\
		A0.w = [SP++];\
		A0.x = [SP++];\
		L0 = [SP++];\
		L1 = [SP++];\
		L2 = [SP++];\
		L3 = [SP++];\
		B0 = [SP++];\
		B1 = [SP++];\
		B2 = [SP++];\
		B3 = [SP++];\
		M0 = [SP++];\
		M1 = [SP++];\
		M2 = [SP++];\
		M3 = [SP++];\
		I0 = [SP++];\
		I1 = [SP++];\
		I2 = [SP++];\
		I3 = [SP++];\
		(R7:2,P5:1) = [SP++];\
		unlink;

// Save task registers except P0.
#define save_regs\
		link 0;\
		[--SP] = (R7:0,P5:0);\
		[--SP] = I3;\
		[--SP] = I2;\
		[--SP] = I1;\
		[--SP] = I0;\
		[--SP] = M3;\
		[--SP] = M2;\
		[--SP] = M1;\
		[--SP] = M0;\
		[--SP] = B3;\
		[--SP] = B2;\
		[--SP] = B1;\
		[--SP] = B0;\
		[--SP] = L3;\
		[--SP] = L2;\
		[--SP] = L1;\
		[--SP] = L0;\
		[--SP] = A0.x;\
		[--SP] = A0.w;\
		[--SP] = A1.x;\
		[--SP] = A1.w;\
		[--SP] = LC1;\
		[--SP] = LC0;\
		[--SP] = LT1;\
		[--SP] = LT0;\
		[--SP] = LB1;\
		[--SP] = LB0;\
		[--SP] = ASTAT

// Save task registers except P0.
#define restore_regs\
		ASTAT=[SP++];\
		LB0 = [SP++];\
		LB1 = [SP++];\
		LT0 = [SP++];\
		LT1 = [SP++];\
		LC0 = [SP++];\
		LC1 = [SP++];\
		A1.w = [SP++];\
		A1.x = [SP++];\
		A0.w = [SP++];\
		A0.x = [SP++];\
		L0 = [SP++];\
		L1 = [SP++];\
		L2 = [SP++];\
		L3 = [SP++];\
		B0 = [SP++];\
		B1 = [SP++];\
		B2 = [SP++];\
		B3 = [SP++];\
		M0 = [SP++];\
		M1 = [SP++];\
		M2 = [SP++];\
		M3 = [SP++];\
		I0 = [SP++];\
		I1 = [SP++];\
		I2 = [SP++];\
		I3 = [SP++];\
		(R7:0,P5:0) = [SP++];\
		unlink


#define save_regs_all_c\
		link 0;\
		[--SP] = R0;\
		[--SP] = R1;\
		[--SP] = R2;\
		[--SP] = R3;\
		[--SP] = P0;\
		[--SP] = P1;\
		[--SP] = P2;\
		[--SP] = I3;\
		[--SP] = I2;\
		[--SP] = I1;\
		[--SP] = I0;\
		[--SP] = M3;\
		[--SP] = M2;\
		[--SP] = M1;\
		[--SP] = M0;\
		[--SP] = B3;\
		[--SP] = B2;\
		[--SP] = B1;\
		[--SP] = B0;\
		[--SP] = L3;\
		[--SP] = L2;\
		[--SP] = L1;\
		[--SP] = L0;\
		[--SP] = A0.x;\
		[--SP] = A0.w;\
		[--SP] = A1.x;\
		[--SP] = A1.w;\
		[--SP] = LC1;\
		[--SP] = LC0;\
		[--SP] = LT1;\
		[--SP] = LT0;\
		[--SP] = LB1;\
		[--SP] = LB0;\
		[--SP] = ASTAT

#define restore_regs_all_c\
		ASTAT=[SP++];\
		LB0 = [SP++];\
		LB1 = [SP++];\
		LT0 = [SP++];\
		LT1 = [SP++];\
		LC0 = [SP++];\
		LC1 = [SP++];\
		A1.w = [SP++];\
		A1.x = [SP++];\
		A0.w = [SP++];\
		A0.x = [SP++];\
		L0 = [SP++];\
		L1 = [SP++];\
		L2 = [SP++];\
		L3 = [SP++];\
		B0 = [SP++];\
		B1 = [SP++];\
		B2 = [SP++];\
		B3 = [SP++];\
		M0 = [SP++];\
		M1 = [SP++];\
		M2 = [SP++];\
		M3 = [SP++];\
		I0 = [SP++];\
		I1 = [SP++];\
		I2 = [SP++];\
		I3 = [SP++];\
		P2 = [SP++];\
		P1 = [SP++];\
		P0 = [SP++];\
		R3 = [SP++];\
		R2 = [SP++];\
		R1 = [SP++];\
		R0 = [SP++];\
		unlink

