#include "CharacterBase.h"

//�R���X�g���N�^
CharacterBase::CharacterBase(GameObject* parent)
	:GameObject(parent, "Player")
{
}

CharacterBase::CharacterBase(GameObject* parent, std::string name)
	: GameObject(parent, name),hModel_(-1), pStage(nullptr), dir_(),dirNext_(), prevPosition(), speed_(0.1f), time_(0),speedTotal_(0)
{
}

//�f�X�g���N�^
CharacterBase::~CharacterBase()
{
}

//������
void CharacterBase::Initialize()
{
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	InitBase();
}

//�X�V
void CharacterBase::Update()
{
	time_++;

	//�ړ��O�̈ʒu�x�N�g��
	prevPosition = XMLoadFloat3(&transform_.position_);

	if (speedTotal_ <= 1)
	{
		switch (dir_)
		{
		case CharacterBase::DIR::L:
			transform_.position_.x -= speed_;
			speedTotal_ += speed_;
			break;
		case CharacterBase::DIR::R:
			transform_.position_.x += speed_;
			speedTotal_ += speed_;
			break;
		case CharacterBase::DIR::U:
			transform_.position_.z += speed_;
			speedTotal_ += speed_;
			break;
		case CharacterBase::DIR::D:
			transform_.position_.z -= speed_;
			speedTotal_ += speed_;
			break;
		default:
			break;
		}
	}

	if (time_ % 10 == 0)
	{
		speedTotal_ = 0;
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

	//�ǂ̓����蔻��
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

	Command();
	Action();
}

//�`��
void CharacterBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	DrawBase();
}

//�J��
void CharacterBase::Release()
{
}