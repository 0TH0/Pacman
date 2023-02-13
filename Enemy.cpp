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
	transform_.position_ = XMFLOAT3(13.5, 0, 1.5f);
	//dir_ = Enemy::DIR::R;
	
	Player* pPlayer = (Player*)FindObject("Player");
	Astar::SetStartCell((int)transform_.position_.x + 0.5f, (int)transform_.position_.z + 0.5f);
	Astar::SetGoalCell((int)pPlayer->GetPosition().x + 0.5f, (int)pPlayer->GetPosition().z + 0.5f);
	Astar::Init();
	Astar::Load("map.csv");
}

void Enemy::DrawBase()
{
	Astar::Draw();
}

void Enemy::Action()
{
	Player* pPlayer = (Player*)FindObject("Player");
	Astar::SetStartCell((int)transform_.position_.x + 0.5f, (int)transform_.position_.z + 0.5f);
	Astar::SetGoalCell((int)pPlayer->GetPosition().x + 0.5f, (int)pPlayer->GetPosition().z + 0.5f);
	Astar::Init();
}

void Enemy::Command()
{
	if (Input::IsKey(DIK_L))
	{
		dir_ = CharacterBase::DIR::R;
	}

	if (Input::IsKey(DIK_J))
	{
		dir_ = CharacterBase::DIR::L;
	}

	if (Input::IsKey(DIK_I))
	{
		dir_ = CharacterBase::DIR::U;
	}

	if (Input::IsKey(DIK_K))
	{
		dir_ = CharacterBase::DIR::D;
	}
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