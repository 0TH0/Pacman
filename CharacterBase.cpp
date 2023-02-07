#include "CharacterBase.h"

//�R���X�g���N�^
CharacterBase::CharacterBase(GameObject* parent)
	:GameObject(parent, "Player")
{
}

CharacterBase::CharacterBase(GameObject* parent, std::string name)
	: GameObject(parent, name),hModel_(-1), pStage(nullptr), dir(), prevPosition(), speed_(0.1f)
{
	for (int i = 0; i < 15; i++)
	{
		map_[i][i] = 0;
	}
}

//�f�X�g���N�^
CharacterBase::~CharacterBase()
{
}

//������
void CharacterBase::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	InitBase();
}

//�X�V
void CharacterBase::Update()
{
	//�ړ��O�̈ʒu�x�N�g��
	prevPosition = XMLoadFloat3(&transform_.position_);

	if (speedTotal_ <= 1)
	{
		switch (dir)
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

		//1�i�񂾂�
		if (speedTotal_ >= 1)
		{
			speedTotal_ = 0;

			float difX = Diff(transform_.position_.x, (float)round(transform_.position_.x));
			float difZ = Diff(transform_.position_.z, (float)round(transform_.position_.z));

			if (transform_.position_.x >= difX)
			{
				transform_.position_.x = (float)round(transform_.position_.x);
			}
			if (transform_.position_.z >= difZ)
			{
				transform_.position_.z = (float)round(transform_.position_.z);
			}
		}
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

	//{
	//	XMFLOAT3 obj = transform_.position_;

	//	if (pStage->IsWall((int)obj.x, (int)obj.z))
	//	{
	//		XMStoreFloat3(&transform_.position_, prevPosition);
	//		//if (dir == CharacterBase::DIR::L)
	//		//{
	//		//	dir = CharacterBase::DIR::D;
	//		//}
	//		//else if (dir == CharacterBase::DIR::D)
	//		//{
	//		//	dir = CharacterBase::DIR::R;
	//		//}
	//	}

	//	obj.z = transform_.position_.z + 0.7f;

	//	if (pStage->IsWall((int)obj.x, (int)obj.z))
	//	{
	//		XMStoreFloat3(&transform_.position_, prevPosition);
	//		//if (dir == CharacterBase::DIR::U)
	//		//{
	//		//	dir = CharacterBase::DIR::L;
	//		//}
	//	}

	//	obj.x = transform_.position_.x + 0.7f;
	//	obj.z = transform_.position_.z;

	//	if (pStage->IsWall((int)obj.x, (int)obj.z))
	//	{
	//		XMStoreFloat3(&transform_.position_, prevPosition);
	//		//dir = CharacterBase::DIR::U;
	//	}
	//}

	Command();
	Action();
}

//�`��
void CharacterBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void CharacterBase::Release()
{
}

float CharacterBase::Diff(float x1, float x2)
{
	if (x1 >= x2)
	{
		return x1 - x2;
	}
	else
	{
		return x2 - x1;
	}

}