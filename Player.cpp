#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1)
{
	
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 1.5f;
	transform_.position_.z = 1.5f;

	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
}

//�X�V
void Player::Update()
{
	//�ړ��O�̈ʒu�x�N�g��
	XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);



	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.1f;
	}

	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.1f;
	}

	if (Input::IsKey(DIK_W))
	{
		transform_.position_.z += 0.1f;
	}

	if (Input::IsKey(DIK_S))
	{
		transform_.position_.z -= 0.1f;
	}

	//���݂̈ʒu�x�N�g��
	XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

	//����̈ړ��x�N�g��
	XMVECTOR move = nowPosition - prevPosition;

	//�ړ��x�N�g���̒����𑪂�
	XMVECTOR length = XMVector3Length(move);

	//0.1�ȏ�ړ����Ă��Ȃ��]����
	if (XMVectorGetX(length) > 0.1f)
	{

		//�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
		move = XMVector3Normalize(move);

		//��ƂȂ鉜�����̃x�N�g��
		XMVECTOR front = { 0, 0, 1, 0 };

		//front��move�̓��ς����߂�
		XMVECTOR vecDot = XMVector3Dot(front, move);
		float dot = XMVectorGetX(vecDot);

		//�����Ă�p�x�����߂�i���W�A���j
		float angle = acos(dot);


		//front��move�̊O�ς����߂�
		XMVECTOR cross = XMVector3Cross(front, move);

		//�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
		if (XMVectorGetY(cross) < 0)
		{
			angle *= -1;
		}


		//���̂Ԃ��]������
		transform_.rotate_.y = angle * 180.0f / 3.14f;
	}

	if (pStage->IsWall((int)transform_.position_.x,	(int)transform_.position_.z))
	{
		XMStoreFloat3(&transform_.position_, prevPosition);
	}
}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}