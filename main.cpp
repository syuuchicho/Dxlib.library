#include "DxLib.h"
#include"windows.h"
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
	const int x = 4;
	const int y = 4;
	const int z = 4;
	int zBox = 0;
	int zBox2 = 0;
	int cx1 = 0;
	int cy1 = 0;
	int cx2 = 0;
	int cy2 = 0;
	const int blockSize = 32;
	int maptipWid = x * blockSize;
	int maptipHei = y * blockSize;
	int MouseX = 0;
	int MouseY = 0;
	int MouseRadius = 7;
	int MouseInput = 0;
	int changeFlag = 0;
	const int chanTimer = 60;
	int changetime = 0;

	enum maptip
	{
		none,//0
		block//1
	};
	int maptip[z][y][x] =
	{
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{1,1,1,1},//z=0
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},//z=1
		},
		{
			{0,0,1,1},
			{0,1,0,1},
			{1,0,1,0},
			{1,1,0,0},//z=2

		},
		{
			{1,1,0,0},
			{1,0,1,0},
			{0,1,0,1},
			{0,0,1,1},//z=3
		}
	};

	int maptipBox[z][y][x] =
	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
		}
	};

	const int x2 = 2;
	const int y2 = 2;

	int maptipWin[x2][y2] =
	{
		{0,0},
		{0,0}
	};


	int blockHandle = 0;
	blockHandle = LoadGraph("Resource/block.png");
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
		GetMousePoint(&MouseX, &MouseY);
		//changeFlag==true�̂Ƃ�,�}�b�v�`�b�v�����ւ���
		for (int j = 0; j < y2; j++)
		{
			for (int i = 0; i < x2; i++)
			{
				cx1 = i * 8 * blockSize / x2;
				cy1 = j * 8 * blockSize / y2;
				cx2 = i * 8 * blockSize / x2 + 8 * blockSize / 2;
				cy2 = j * 8 * blockSize / y2 + 8 * blockSize / 2;

				if (MouseX >= cx1 && MouseX <= cx2 && MouseY >= cy1 && MouseY <= cy2)
				{
					zBox = 2 * j + i;
					maptipWin[j][i] = 1;
				}

				else
				{
					maptipWin[j][i] = 0;
				}
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON)&&changeFlag==1)
		{
			changeFlag = 2;
			
			for (int j = 0; j < y; j++)
			{
				for (int i = 0; i < x; i++)
				{
					//����ւ�
					maptip[zBox2][j][i] = maptip[zBox][j][i];
					maptip[zBox][j][i] = maptipBox[0][j][i];

				}
			}
		}

		if (keys[KEY_INPUT_SPACE])
		{
			changeFlag = 0;
		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			for (int j = 0; j < y2; j++)
			{
				for (int i = 0; i < x2; i++)
				{
					if (maptipWin[j][i] == 1)
					{
						changeFlag = 1;
						zBox2 = 2 * j + i;
						for (int j = 0; j < y; j++)
						{
							for (int i = 0; i < x; i++)
							{
								//����ւ���}�b�v�`�b�v��ۑ�
								maptipBox[0][j][i] = maptip[zBox2][j][i];
								////����ւ�
								//maptip[zBox2][j][i] = maptip[zBox][j][i];
								//maptip[zBox][j][i] = maptipBox[0][j][i];
							}
						}
					}

					/*if (changeFlag==0)
					{
						zBox = 2 * j + i;
						changeFlag = true;
					}*/

				}
			}
			

			//if (changeFlag == true && GetAsyncKeyState(VK_LBUTTON))
			//{
			//	for (int j = 0; j < y2; j++)
			//	{
			//		for (int i = 0; i < x2; i++)
			//		{
			//			int cx1 = i * 8 * blockSize / x2;
			//			int cy1 = j * 8 * blockSize / y2;
			//			int cx2 = i * 8 * blockSize / 2 + 8 * blockSize / 2;
			//			int cy2 = j * 8 * blockSize / 2 + 8 * blockSize / 2;
			//			if (MouseX >= cx1 && MouseX <= cx2 || MouseY >= cy1 && MouseY <= cy2)
			//			{
			//				int zBox2 = 2 * j + i;
			//			}
			//		}
			//	}

			//	for (int j = 0; j < y; j++)
			//	{
			//		for (int i = 0; i < x; i++)
			//		{
			//			//����ւ���}�b�v�`�b�v��ۑ�
			//			maptipBox[0][j][i] = maptip[zBox2][j][i];
			//			//����ւ�
			//			maptip[zBox2][j][i] = maptip[zBox][j][i];
			//			maptip[zBox][j][i] = maptipBox[0][j][i];
			//		}
			//	}
			//	changeFlag = false;
			//}

			////����ւ���}�b�v�`�b�v��No(����)���擾,�Ⴆ�Έ���a��b
			//if (changeFlag == false && GetAsyncKeyState(VK_LBUTTON))
			//{
			//	//�}�b�v�`�b�v�ƃ}�E�X���W�Ƃ̓����蔻��
			//	for (int j = 0; j < y2; j++)
			//	{
			//		for (int i = 0; i < x2; i++)
			//		{
			//			int cx1 = i * 8 * blockSize / x2;
			//			int cy1 = j * 8 * blockSize / y2;
			//			int cx2=i * 8 * blockSize / 2 + 8 * blockSize / 2;
			//			int cy2=j * 8 * blockSize / 2 + 8 * blockSize / 2;
			//			if (MouseX>=cx1&&MouseX<=cx2||MouseY>=cy1&&MouseY<=cy2)
			//			{
			//				int zBox = 2 * j + i;
			//			}
			//		}
			//	}
			//				changeFlag = true;
		}




		DrawFormatString(500, 100, GetColor(255, 255, 255), "changeFlag:%d", changeFlag);
		DrawFormatString(500, 120, GetColor(255, 255, 255), "zBox:%d", zBox);
		DrawFormatString(500, 140, GetColor(255, 255, 255), "zBox2:%d", zBox2);
		DrawFormatString(500, 160, GetColor(255, 255, 255), "maptipWin[0][0]:%d", maptipWin[0][0]);
		DrawFormatString(500, 180, GetColor(255, 255, 255), "maptipWin[0][1]:%d", maptipWin[0][1]);
		DrawFormatString(500, 200, GetColor(255, 255, 255), "maptipWin[1][0]:%d", maptipWin[1][0]);
		DrawFormatString(500, 220, GetColor(255, 255, 255), "maptipWin[1][1]:%d", maptipWin[1][1]);



		/*DrawFormatString(0, 180, GetColor(255, 255, 255), "arrayBox[0][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[0][0][0], 0, 0, 0);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "arrayBox[1][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[1][0][0], 1, 0, 0);
		DrawFormatString(0, 220, GetColor(255, 255, 255), "arrayBox[2][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[2][0][0], 2, 0, 0);


		DrawFormatString(0, 120, GetColor(255, 255, 255), "array[0][y][x]:%d,z:%d,y:%d,x:%d\n", array[0][0][0], 0, 0, 0);
		DrawFormatString(0, 140, GetColor(255, 255, 255), "array[1][y][x]:%d,z:%d,y:%d,x:%d\n", array[1][0][0], 1, 0, 0);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "array[2][y][x]:%d,z:%d,y:%d,x:%d\n", array[2][0][0], 2, 0, 0);*/

		// �`�揈��
		for (int k = 0; k < z; k++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int i = 0; i < x; i++)
				{
					if (maptip[k][j][i] == block)
					{
						switch (k)
						{
						case 0:
							DrawGraph(i * blockSize, j * blockSize, blockHandle, false);
							break;
						case 1:
							DrawGraph(x * blockSize + i * blockSize, j * blockSize, blockHandle, false);
							break;
						case 2:
							DrawGraph(i * blockSize, y * blockSize + j * blockSize, blockHandle, false);
							break;
						default:
							DrawGraph(x * blockSize + i * blockSize, y * blockSize + j * blockSize, blockHandle, false);
							break;
						}
					}
				}
			}
		}

		//�}�E�X
		DrawCircle(MouseX, MouseY, MouseRadius, GetColor(255, 255, 255), false);
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			DrawCircle(MouseX, MouseY, MouseRadius, GetColor(255, 0, 0), false);
		}

		//�}�b�v�`�b�v�̘g
		for (int j = 0; j < y2; j++)//y2=2�������, 8=��ӂ�Block�̐�
		{
			for (int i = 0; i < x2; i++)//x2=2�������
			{
				if (maptipWin[j][i] == 0)
				{
					DrawBox(
						i * 8 * blockSize / x2,
						j * 8 * blockSize / y2,
						i * 8 * blockSize / x2 + 8 * blockSize / 2,
						j * 8 * blockSize / y2 + 8 * blockSize / 2,
						GetColor(255, 255, 255), false);
				}

				if (maptipWin[j][i] == 1)
				{
					DrawBox(
						i * 8 * blockSize / x2,
						j * 8 * blockSize / y2,
						i * 8 * blockSize / x2 + 8 * blockSize / 2,
						j * 8 * blockSize / y2 + 8 * blockSize / 2,
						GetColor(255, 255, 0), false);
				}
			}
		}


		/*DrawBox(x * blockSize, y * blockSize, x * blockSize + x * blockSize, y * blockSize + y * blockSize, GetColor(255, 255, 255), false);

		DrawBox(0, 0, x * blockSize, y * blockSize, GetColor(255, 255, 255), false);

		DrawBox(x * blockSize, 0, x * blockSize + x * blockSize, y * blockSize, GetColor(255, 255, 255), false);

		DrawBox(0, y * blockSize, x * blockSize, y * blockSize + y * blockSize, GetColor(255, 255, 255), false);*/




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