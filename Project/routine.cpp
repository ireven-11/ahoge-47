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
    titleGraph_ = LoadGraph("graph/ahoge-samunegazou.png");
    hitSount_ = LoadSoundMem("sound/��C2.mp3");
    bgm_ = LoadSoundMem("sound/����̐��E.mp3");

    PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, TRUE);
}

/// <summary>
/// �f�X�g���N�^�F�f���[�g�����B�g�p�������\�[�X�f�[�^��Y�ꂸ�ɏ�����
/// </summary>
Routine::~Routine()
{
    DeleteGraph(backGraph_);
    DeleteGraph(titleGraph_);
    DeleteSoundMem(hitSount_);
    DeleteSoundMem(bgm_);
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
            SetFontSize(100);
            title();
            break;

        case PLAY:
            SetFontSize(50);
            play();
            break;

        case RESULT:
            SetFontSize(100);
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
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, titleGraph_, TRUE);
    DrawString(575, 800, "Enter�ŃX�^�[�g", GetColor(255, 0, 0));
    sceneManager->proceedToPlay();
}

void Routine::play()
{
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, backGraph_, TRUE);
    DrawString(800, 1000, "A,D�ňړ��A�}�E�X�ŕW���ړ��Aspace�ŐH�ׂ�", GetColor(255, 255, 255));

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
            PlaySoundMem(hitSount_, DX_PLAYTYPE_BACK, TRUE);
            dieCount_++;
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
    DrawString(700, 500, "GAMEOVER", GetColor(255, 0, 0));
    DrawFormatString(650, 600, GetColor(255, 0, 0), "�������F%d", dieCount_);
    DrawString(500, 800, "space�Ń^�C�g���֖߂�", GetColor(255, 0, 0));

    if (CheckHitKey(KEY_INPUT_SPACE) == true)
    {
        sceneManager->proceedToTitle();

        player->reset();
        enemy.clear();
        reset();
    } 
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
    dieCount_ = 0;
}