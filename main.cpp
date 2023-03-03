#include "DxLib.h"
#include"windows.h"
// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "xx2x_xx_ナマエ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1200;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
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
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		GetMousePoint(&MouseX, &MouseY);
		//changeFlag==trueのとき,マップチップを入れ替える
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
					//入れ替え
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
								//入れ替えるマップチップを保存
								maptipBox[0][j][i] = maptip[zBox2][j][i];
								////入れ替え
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
			//			//入れ替えるマップチップを保存
			//			maptipBox[0][j][i] = maptip[zBox2][j][i];
			//			//入れ替え
			//			maptip[zBox2][j][i] = maptip[zBox][j][i];
			//			maptip[zBox][j][i] = maptipBox[0][j][i];
			//		}
			//	}
			//	changeFlag = false;
			//}

			////入れ替えるマップチップのNo(引数)を取得,例えば引数aとb
			//if (changeFlag == false && GetAsyncKeyState(VK_LBUTTON))
			//{
			//	//マップチップとマウス座標との当たり判定
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

		// 描画処理
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

		//マウス
		DrawCircle(MouseX, MouseY, MouseRadius, GetColor(255, 255, 255), false);
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			DrawCircle(MouseX, MouseY, MouseRadius, GetColor(255, 0, 0), false);
		}

		//マップチップの枠
		for (int j = 0; j < y2; j++)//y2=2今回限定, 8=一辺のBlockの数
		{
			for (int i = 0; i < x2; i++)//x2=2今回限定
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




		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}