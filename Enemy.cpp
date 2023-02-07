#include "Enemy.h"
#include "Engine/SceneManager.h"

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
	transform_.position_ = XMFLOAT3(13, 0, 1);
	dir = Enemy::DIR::R;
}

void Enemy::Action()
{
	{
		XMFLOAT3 obj = transform_.position_;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
			if (dir == Enemy::DIR::L)
			{
				dir = Enemy::DIR::D;
			}
			else if (dir == Enemy::DIR::D)
			{
				dir = Enemy::DIR::R;
			}
		}

		obj.z = transform_.position_.z + 0.7f;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
			if (dir == Enemy::DIR::U)
			{
				dir = Enemy::DIR::L;
			}
		}

		obj.x = transform_.position_.x + 0.7f;
		obj.z = transform_.position_.z;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
			dir = Enemy::DIR::U;
		}
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