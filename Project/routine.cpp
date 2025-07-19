#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Routine::Routine()
{
    reset();
    backGraph_ = LoadGraph("graph/Dark Gothic Castle.png");
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
Routine::~Routine()
{
    DeleteGraph(backGraph_);
}

/// <summary>
/// �Q�[��
/// </summary>
void Routine::game()
{
    //�C���X�^���X��
    std::shared_ptr<SceneManager>sceneManager = std::make_shared<SceneManager>();

    //�Q�[�����[�v�Ăяo��
    gameRoop(sceneManager);

    //�f���[�g
    sceneManager = nullptr;
}

/// <summary>
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager)
{
    while (gameRoopSetting)
    {
        //��ʂɕ`���ꂽ��������(�Q�[�����[�v�̍ŏ��ɌĂ�)
        ClearDrawScreen();

        switch (sceneManager->GetsceneType_())
        {
        case TITLE:
            title();
            break;

        case PLAY:
            play();
            break;

        case RESULT:
            result();
            break;

        }

        // ����ʂ̓��e��\��ʂɔ��f(�Q�[�����[�v�̍Ō�ɌĂ�)
        ScreenFlip();
    }
}

void Routine::title()
{
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, backGraph_, TRUE);
}

void Routine::play()
{
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, backGraph_, TRUE);

    spawnEnemy();

    player->update();

    for (auto it = enemy.begin(); it != enemy.end(); )
    {
        (*it)->update();

        auto pos = (*it)->Getposition_();
        if (pos.x > 1920 || pos.x < 0)
        {
            it = enemy.erase(it);  // erase �͎��̃C�e���[�^��Ԃ�
        }
        else
        {
            ++it;
        }
    }
}

void Routine::result()
{

}

void Routine::spawnEnemy()
{
    spawnCount_++;

    if (spawnCount_ == max_spawn_count)
    {
        enemy.emplace_back(make_shared<Enemy>());
        spawnCount_ = 0;
    }
}

void Routine::reset()
{
    spawnCount_ = 0;
}