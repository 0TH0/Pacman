#include "Enemy.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Astar.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:CharacterBase(parent, "Enemy")
{
}

//デストラクタ
Enemy::~Enemy()
{
}

void Enemy::InitBase()
{
	transform_.position_ = XMFLOAT3(13.4f, 0, 1.4f);
	Astar::Load("map.csv");
	speed_ *= 0.5f;
	//モデルデータのロード
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);
}

void Enemy::DrawBase()
{
	Astar::Draw();
}

void Enemy::Action()
{
	Player* pPlayer = (Player*)FindObject("Player");
	playerPos_.x = (int)pPlayer->GetPosition().x + 0.5f;
	playerPos_.z = (int)pPlayer->GetPosition().z + 0.5f;
	Astar::SetStartCell((int)transform_.position_.x + 0.5f, (int)transform_.position_.z + 0.5f);
	Astar::SetGoalCell(playerPos_.x, playerPos_.z);
	Astar::Update();

	if (playerPos_.x == (int)transform_.position_.x + 0.5f)
	{
		if (playerPos_.z >= (int)transform_.position_.z + 0.5f)
		{
			dir_ = DIR::U;

		}
		else if (playerPos_.z <= (int)transform_.position_.z + 0.5f)
		{
			dir_ = DIR::D;
		}
	}
	else if (playerPos_.x <= (int)transform_.position_.x + 0.5f)
	{
		dir_ = DIR::L;
	}
	else if (playerPos_.x >= (int)transform_.position_.x + 0.5f)
	{
		dir_ = DIR::R;
	}
}

void Enemy::Command()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	//敵に当たった
	if (pTarget->GetObjectName() == "Player")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}