#include"DxLib.h"
#include"sceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
{
	reset();
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// リセット
/// </summary>
void SceneManager::reset()
{
	sceneType_ = TITLE;
}


void SceneManager::proceedToResult()
{
	sceneType_ = RESULT;
}

void SceneManager::proceedToPlay()
{
	if (CheckHitKey(KEY_INPUT_RETURN) == true)
	{
		sceneType_ = PLAY;
	}
}

void SceneManager::proceedToTitle()
{
		sceneType_ = TITLE;
}