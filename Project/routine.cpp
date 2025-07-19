#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"enemy.h"
#include"collision.h"

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
    //�Q�[�����[�v�Ăяo��
    gameRoop();

    //�f���[�g
    sceneManager = nullptr;
}

/// <summary>
/// �Q�[�����[�v
/// </summary>
void Routine::gameRoop()
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

        SetFPS();

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

        Enemy* e = dynamic_cast<Enemy*>(it->get());
        Player* p = dynamic_cast<Player*>(player.get());

        if (e && p) 
        {
            if (hitPlayerWithEnemy(e, p))
            {
                sceneManager->proceedToResult();
            }
        }

        if (pos.x > 1920 || pos.x < 0 || hitShotWithEnemy(e,p))
        {
            it = enemy.erase(it);
        }
        else
        {
            ++it;
        }
    }

    timer_++;
    if (timer_ > 300 && spawnLevel_ > 1)
    {
        timer_ = 0;
        spawnLevel_--;
    }
}

void Routine::result()
{

}

void Routine::spawnEnemy()
{
    spawnCount_++;

    if (spawnCount_ == max_spawn_count * spawnLevel_)
    {
        enemy.emplace_back(make_shared<Enemy>());
        spawnCount_ = 0;
    }
}

void Routine::reset()
{
    spawnCount_ = 0;
    timer_ = 0;
    spawnLevel_ = 30;
}