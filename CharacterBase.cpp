#include "CharacterBase.h"

//コンストラクタ
CharacterBase::CharacterBase(GameObject* parent)
	:GameObject(parent, "Player")
{
}

CharacterBase::CharacterBase(GameObject* parent, std::string name)
	: GameObject(parent, name),hModel_(-1), pStage(nullptr), dir_(), prevPosition(), speed_(0.1f)
{
	for (int i = 0; i < 15; i++)
	{
		map_[i][i] = 0;
	}
}

//デストラクタ
CharacterBase::~CharacterBase()
{
}

//初期化
void CharacterBase::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	InitBase();
}

//更新
void CharacterBase::Update()
{
	time_++;

	//移動前の位置ベクトル
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
		dir_ = dir2_;
	}

	//現在の位置ベクトル
	XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

	//今回の移動ベクトル
	XMVECTOR move = nowPosition - prevPosition;

	//移動ベクトルの長さを測る
	XMVECTOR length = XMVector3Length(move);

	//0.1以上移動してたなら回転処理
	if (XMVectorGetX(length) > 0.1f)
	{

		//角度を求めるために長さを１にする（正規化）
		move = XMVector3Normalize(move);

		//基準となる奥向きのベクトル
		XMVECTOR front = { 0, 0, 1, 0 };

		//frontとmoveの内積を求める
		XMVECTOR vecDot = XMVector3Dot(front, move);
		float dot = XMVectorGetX(vecDot);

		//向いてる角度を求める（ラジアン）
		float angle = acos(dot);


		//frontとmoveの外積を求める
		XMVECTOR cross = XMVector3Cross(front, move);

		//外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
		if (XMVectorGetY(cross) < 0)
		{
			angle *= -1;
		}

		//そのぶん回転させる
		transform_.rotate_.y = angle * 180.0f / 3.14f;
	}

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

	Command();
	Action();
}

//描画
void CharacterBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	DrawBase();
}

//開放
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