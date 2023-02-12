#include "Enemy.h"
#include "Engine/SceneManager.h"
#include "Player.h"

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
}

void Enemy::Action()
{
	{
		if (pStage->IsWall((float)transform_.position_.x + 0.3, (float)transform_.position_.z + 0.3))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}

		if (pStage->IsWall((float)transform_.position_.x - 0.3, (float)transform_.position_.z - 0.3))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}

		if (pStage->IsWall((float)transform_.position_.x + 0.3, (float)transform_.position_.z - 0.3))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}

		if (pStage->IsWall((float)transform_.position_.x - 0.3, (float)transform_.position_.z + 0.3))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}
	}
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