#include"DxLib.h"
#include"routine.h"
#include"setting.h"
#include"sceneManager.h"
#include"enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
Routine::Routine()
{
    reset();
    backGraph_ = LoadGraph("graph/Dark Gothic Castle.png");
}

/// <summary>
/// デストラクタ：デリート処理。使用したリソースデータを忘れずに消そう
/// </summary>
Routine::~Routine()
{
    DeleteGraph(backGraph_);
}

/// <summary>
/// ゲーム
/// </summary>
void Routine::game()
{
    //インスタンス化
    std::shared_ptr<SceneManager>sceneManager = std::make_shared<SceneManager>();

    //ゲームループ呼び出し
    gameRoop(sceneManager);

    //デリート
    sceneManager = nullptr;
}

/// <summary>
/// ゲームループ
/// </summary>
void Routine::gameRoop(shared_ptr<SceneManager> sceneManager)
{
    while (gameRoopSetting)
    {
        //画面に描かれた物を消す(ゲームループの最初に呼ぶ)
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

        // 裏画面の内容を表画面に反映(ゲームループの最後に呼ぶ)
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
            it = enemy.erase(it);  // erase は次のイテレータを返す
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