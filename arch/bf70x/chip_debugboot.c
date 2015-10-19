#include "jsp_kernel.h"
#include "sil.h"

/*
* gdbserver���^�[�Q�b�g�̃��Z�b�g�@�\��񋟂��Ȃ����߁Agdb�o�R�Ń^�[�Q�b�g
* �ɃA�v���b�P�[�V�������_�E�����[�h����Ɛ��������삵�Ȃ����Ƃ�����B
* ���̃��[�`���̓^�[�Q�b�g����x�������Z�b�g����B
*
* �Ȃ��A�p�����[�^ debug�� FALSE�̏ꍇ�A���Z�b�g�͂��Ȃ�
*/
void boot_for_gdb(BOOL debug)
{
	// SYSTEM_RESET		0x0007
	// DOUBLE_FAULT		0x0008
	// RESET_DOUBLE		0x2000
	// RESET_WDOG		0x4000
	// RESET_SOFTWARE	0x8000
    if ( ! (*__pSWRST & 0x8000 ) && debug ){   /* RESET_SOFTWARE �\�t�g�E�F�A���Z�b�g���N���Ă��Ȃ��Ȃ�ȉ����s�@*/
        *__pSWRST = 0x07;                     /* �����y���t�F�����̃��Z�b�g�@*/
        asm volatile( "ssync;" );
        *__pSWRST = 0x00;                     /* �����y���t�F�����̃��Z�b�g�����B */
        asm volatile( "ssync;" );
        *__pSYSCR |= 0x10;                    /* no boot on core reset */
        asm volatile( "ssync;" );
        asm volatile( "raise 1;" );         /* �R�A���Z�b�g */
        while( 1 )
            ;                               /*���Z�b�g����������܂Ń��[�v*/
    }
}
