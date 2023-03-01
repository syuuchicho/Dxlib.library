#include "DxLib.h"

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
		//入れ替えるマップチップのNo(引数)を取得,例えば引数aとb
		int a = 0;
		int b = 1;
		int c = 2;
		//マップチップの入れ替え
		if (changeFlag == false&&keys[KEY_INPUT_SPACE])
		{
			changeFlag = true;
			arrayBox[a][0][0] = array[c][0][0];
			arrayBox[b][0][0] = array[a][0][0];
			//arrayBox[c][0][0] = array[b][0][0];
			//保存したデータを配列に格納
			array[a][0][0] = arrayBox[a][0][0];
			array[b][0][0] = arrayBox[b][0][0];
			array[c][0][0] = arrayBox[c][0][0];
		}

		DrawFormatString(0, 100, GetColor(255, 255, 255), "入れ替えた後\n");
		DrawFormatString(0, 180, GetColor(255, 255, 255), "arrayBox[0][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[0][0][0], 0, 0, 0);
		DrawFormatString(0, 200, GetColor(255, 255, 255), "arrayBox[1][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[1][0][0], 1, 0, 0);
		DrawFormatString(0, 220, GetColor(255, 255, 255), "arrayBox[2][y][x]:%d,z:%d,y:%d,x:%d\n", arrayBox[2][0][0], 2, 0, 0);
		

		DrawFormatString(0, 120, GetColor(255, 255, 255), "array[0][y][x]:%d,z:%d,y:%d,x:%d\n", array[0][0][0], 0, 0, 0);
		DrawFormatString(0, 140, GetColor(255, 255, 255), "array[1][y][x]:%d,z:%d,y:%d,x:%d\n", array[1][0][0], 1, 0, 0);
		DrawFormatString(0, 160, GetColor(255, 255, 255), "array[2][y][x]:%d,z:%d,y:%d,x:%d\n", array[2][0][0], 2, 0, 0);

		// 描画処理
		for (int k = 0; k < z; k++)
		{
			if (k == 0)//z=0
			{
				DrawBox(0, 0, array[k][0][0] * Block_Size, 0 + Block_Size, GetColor(0, 0, 255), true);//青
			}
			if (k == 1)//z=1
			{
				DrawBox(0, 40, array[k][0][0] * Block_Size, 40 + Block_Size, GetColor(0, 255, 0), true);//緑
			}
			if (k == 2)//z=2
			{
				DrawBox(0,80, array[k][0][0] * Block_Size, 80 + Block_Size, GetColor(255, 0, 0), true);//赤
			}
		}

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
