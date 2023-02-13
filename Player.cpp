#include "Player.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:CharacterBase(parent, "Player")
{
}

//�f�X�g���N�^
Player::~Player()
{
}

void Player::InitBase()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(1.4, 0, 1.4);
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

	if (time_ % 10 == 0)
	{
		dir_ = dir2_;
	}
}
