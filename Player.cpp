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
	//モデルデータのロード
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(1.5f, 0, 1.5f);
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
		dirNext_ = CharacterBase::DIR::R;
	}

	if (Input::IsKey(DIK_A))
	{
		dirNext_ = CharacterBase::DIR::L;
	}

	if (Input::IsKey(DIK_W))
	{
		dirNext_ = CharacterBase::DIR::U;
	}

	if (Input::IsKey(DIK_S))
	{
		dirNext_ = CharacterBase::DIR::D;
	}

	if (time_ % 10 == 0)
	{
		dir_ = dirNext_;
	}
}
