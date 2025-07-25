#pragma once

//シーン
enum
{
	TITLE,
	PLAY,
	RESULT
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void reset();	//リセット処理
	void proceedToResult();
	void proceedToPlay();
	void proceedToTitle();

	int GetsceneType_()const { return sceneType_; }

private:

	int sceneType_;	//シーンタイプ
};