#include"DxLib.h"
#include"collision.h"
#include"player.h"
#include"enemy.h"
#include"garlicShot.h"

bool hitPlayerWithEnemy(Enemy* enemy,Player* player)
{
	if (enemy->Getposition_().x < player->Getposition_().x + graph_width / 2 &&
		player->Getposition_().x + graph_width / 2 < enemy->Getposition_().x + graph_width &&
		enemy->Getposition_().y < player->Getposition_().y + graph_height / 2 &&
		player->Getposition_().y + graph_width / 2 < enemy->Getposition_().y + graph_height)
	{
		return true;
	}
	
	return false;
}

bool hitShotWithEnemy(Enemy* enemy, Player* player)
{
	if (enemy->GetcanExist_())
	{
		for (auto it = player->garlicShot_.begin(); it != player->garlicShot_.end(); )
		{
			if ((*it)->GetcanExist_())
			{
				if (enemy->Getposition_().x < (*it)->Getposition_().x + widht / 2 &&
					(*it)->Getposition_().x + widht / 2 < enemy->Getposition_().x + graph_width &&
					enemy->Getposition_().y < (*it)->Getposition_().y + height / 2 &&
					(*it)->Getposition_().y + graph_width / 2 < enemy->Getposition_().y + graph_height)
				{
					it = player->garlicShot_.erase(it);  // erase は次のイテレータを返す
					return true;
				}
				else
				{
					++it;
				}
			}
		}
	}

	return false;
}