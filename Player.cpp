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
	transform_.position_ = XMFLOAT3(1.5, 0, 1.5);
}

void Player::DrawBase()
{
}

void Player::Action()
{
}

void Player::Command()
{
	if (Input::IsKey(DIK_D))
	{
		dir2_ = CharacterBase::DIR::R;
	}

	if (Input::IsKey(DIK_A))
	{
		dir2_ = CharacterBase::DIR::L;
	}

	if (Input::IsKey(DIK_W))
	{
		dir2_ = CharacterBase::DIR::U;
	}

	if (Input::IsKey(DIK_S))
	{
		dir2_ = CharacterBase::DIR::D;
	}
}
