#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"enemy.h"
#include"collision.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    reset();
    backGraph_ = LoadGraph("graph/Dark Gothic Castle.png");
    titleGraph_ = LoadGraph("graph/ahoge-samunegazou.png");
    hitSount_ = LoadSoundMem("sound/大砲2.mp3");
    bgm_ = LoadSoundMem("sound/死後の世界.mp3");

    PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP, TRUE);
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
Routine::~Routine()
{
    DeleteGraph(backGraph_);
    DeleteGraph(titleGraph_);
    DeleteSoundMem(hitSount_);
    DeleteSoundMem(bgm_);
}

/// <summary>
/// ゲーム
/// </summary>
void Routine::game()
{
    //ゲームループ呼び出し
    gameRoop();

    //デリート
    sceneManager = nullptr;
}

/// <summary>
/// ゲームループ
/// </summary>
void Routine::gameRoop()
{
    while (gameRoopSetting)
    {
        //画面に描かれた物を消す(ゲームループの最初に呼ぶ)
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

        // 裏画面の内容を表画面に反映(ゲームループの最後に呼ぶ)
        ScreenFlip();
    }
}

void Routine::title()
{
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, titleGraph_, TRUE);
    DrawString(575, 800, "Enterでスタート", GetColor(255, 0, 0));
    sceneManager->proceedToPlay();
}

void Routine::play()
{
    DrawExtendGraph(0, 0, screenWIDTH, screenHEIGHT, backGraph_, TRUE);
    DrawString(800, 1000, "A,Dで移動、マウスで標準移動、spaceで食べる", GetColor(255, 255, 255));
    DrawFormatString(0, 0, GetColor(255, 0, 0), "ニンニクパワー：%d", player->GetgageLevel_());

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

        bool isOutScreen = pos.x > 1920 || pos.x < 0;
        bool isHit = hitShotWithEnemy(e, p);

        if (isOutScreen || isHit)
        {
            it = enemy.erase(it);

            if (isHit)
            {
                PlaySoundMem(hitSount_, DX_PLAYTYPE_BACK, TRUE);
                dieCount_++;
            }
        }
        else
        {
            ++it;
        }
    }

    /*DrawFormatString(650, 600, GetColor(255, 0, 0), "討伐数：%d", dieCount_);
    DrawFormatString(650, 700, GetColor(255, 0, 0), "スポーンレベル：%d", spawnLevel_);
    DrawFormatString(650, 800, GetColor(255, 0, 0), "スポーンkaunnto：%d", spawnCount_);*/
}

void Routine::result()
{
    DrawString(700, 500, "GAMEOVER", GetColor(255, 0, 0));
    DrawFormatString(650, 600, GetColor(255, 0, 0), "討伐数：%d", dieCount_);
    DrawString(500, 800, "spaceでタイトルへ戻る", GetColor(255, 0, 0));

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
        if (spawnLevel_ > 5)
        {
            spawnLevel_--;
        }
        
    }
}

void Routine::reset()
{
    spawnCount_ = 0;
    timer_ = 0;
    spawnLevel_ = 30;
    dieCount_ = 0;
}