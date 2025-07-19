#include"DxLib.h"
#include"collision.h"
#include"player.h"
#include"enemy.h"

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

}