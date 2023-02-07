#include "Player.h"

//コンストラクタ
Player::Player(GameObject* parent)
	:CharacterBase(parent, "Player")
{
}

//デストラクタ
Player::~Player()
{
}

void Player::InitBase()
{
	transform_.position_ = XMFLOAT3(1, 0, 1);
}

void Player::Action()
{
	{
		XMFLOAT3 obj = transform_.position_;

		obj.x = transform_.position_.x + 0.5f;
		obj.z = transform_.position_.z;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}

		obj.x = transform_.position_.x;
		obj.z = transform_.position_.z + 0.9f;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}

		obj.x = transform_.position_.x + 0.9f;
		obj.z = transform_.position_.z;

		if (pStage->IsWall((int)obj.x, (int)obj.z))
		{
			XMStoreFloat3(&transform_.position_, prevPosition);
		}
	}
}

void Player::Command()
{
	if (Input::IsKey(DIK_D))
	{
		dir = CharacterBase::DIR::R;
	}

	if (Input::IsKey(DIK_A))
	{
		dir = CharacterBase::DIR::L;
	}

	if (Input::IsKey(DIK_W))
	{
		dir = CharacterBase::DIR::U;
	}

	if (Input::IsKey(DIK_S))
	{
		dir = CharacterBase::DIR::D;
	}
}
