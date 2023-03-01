#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "xx2x_xx_�i�}�G: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1200;

// �E�B���h�E�c��
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	const int x = 1;
	const int y = 1;
	const int z = 3;
	const int Block_Size = 20;



	bool changeFlag = false;

	int array[z][y][x] =
	{
		{
			{2}//z=0
		},

		{
			{1}//z=1
		},

		{
			{0}//z=2
		}
	};

	int arrayBox[z][y][x] =
	{
		{
			{3}//z=0
		},
		{
			{4}//z=1
		},
		{
			{5}//z=2
		},
	};

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//����ւ���}�b�v�`�b�v��No(����)���擾,�Ⴆ�Έ���a��b
		int a = 0;
		int b = 1;
		int c = 2;
		//�}�b�v�`�b�v�̓���ւ�
		if (changeFlag == false&&keys[KEY_INPUT_SPACE])
		{
			changeFlag = true;
			arrayBox[a][0][0] = array[c][0][0];
			arrayBox[b][0][0] = array[a][0][0];
			//arrayBox[c][0][0] = array[b][0][0];
			//�ۑ������f�[�^��z��Ɋi�[
			array[a][0][0] = arrayBox[a][0][0];
			array[b][0][0] = arrayBox[b][0][0];
			array[c][0][0] = arrayBox[c][0][0];
		}

		DrawFormatString(0, 100, GetColor(255, 255, 255), "����ւ�����\n");
		DrawFormatString(0, 180, GetColor(255, 255, 255), "arrayBox[0][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[0][0][0], 0, 0, 0);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "arrayBox[1][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[1][0][0], 1, 0, 0);
		DrawFormatString(0, 220, GetColor(255, 255, 255), "arrayBox[2][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[2][0][0], 2, 0, 0);
		

		DrawFormatString(0, 120, GetColor(255, 255, 255), "array[0][y][x]:%d,z:%d,y:%d,x:%d\n", array[0][0][0], 0, 0, 0);
		DrawFormatString(0, 140, GetColor(255, 255, 255), "array[1][y][x]:%d,z:%d,y:%d,x:%d\n", array[1][0][0], 1, 0, 0);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "array[2][y][x]:%d,z:%d,y:%d,x:%d\n", array[2][0][0], 2, 0, 0);

		// �`�揈��
		for (int k = 0; k < z; k++)
		{
			if (k == 0)//z=0
			{
				DrawBox(0, 0, array[k][0][0] * Block_Size, 0 + Block_Size, GetColor(0, 0, 255), true);//��
			}
			if (k == 1)//z=1
			{
				DrawBox(0, 40, array[k][0][0] * Block_Size, 40 + Block_Size, GetColor(0, 255, 0), true);//��
			}
			if (k == 2)//z=2
			{
				DrawBox(0,80, array[k][0][0] * Block_Size, 80 + Block_Size, GetColor(255, 0, 0), true);//��
			}
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}