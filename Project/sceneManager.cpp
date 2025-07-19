#include"DxLib.h"
#include"sceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
{
	reset();
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
SceneManager::~SceneManager()
{
}

/// <summary>
/// ���Z�b�g
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