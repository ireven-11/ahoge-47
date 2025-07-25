#include"DxLib.h"
#include"setting.h"

//スクリーン設定関数
void ScreenSetting()
{
    ChangeWindowMode(TRUE);				   //ウィンドウモードにする
    SetWindowStyleMode(7);				   //最大化ボタンが存在するウインドウモードに変更

    // サイズ変更を可能にする
    SetWindowSizeChangeEnableFlag(TRUE, FALSE);

    // ウインドウサイズはゲーム画面と一致させる
    SetWindowSize(screenWIDTH, screenHEIGHT);

    SetMainWindowText("gamename");              //ウィンドウ（白いところ）にゲーム名を書く
    SetDrawScreen(DX_SCREEN_BACK);		        //背景をセットする
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//ウィンドウのサイズとカラーモードを決める
}

void SetFPS()
{
    //waitの部分の数値を増やすほどｆｐｓがさがっていく
    const int wait = 16;
    int term;
    static int t = 0;
    term = GetNowCount() - t;
    if (wait - term > 0)
        Sleep(wait - term);
    t = GetNowCount();
}