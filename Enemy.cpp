#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Player.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{

}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 1.5f;
	transform_.position_.z = 5.5f;

	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
}

//更新
void Enemy::Update()
{
	//移動前の位置ベクトル
	XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

	if (Input::IsKey(DIK_L))
	{
		transform_.position_.x += 0.1f;
	}

	if (Input::IsKey(DIK_J))
	{
		transform_.position_.x -= 0.1f;
	}

	if (Input::IsKey(DIK_I))
	{
		transform_.position_.z += 0.1f;
	}

	if (Input::IsKey(DIK_K))
	{
		transform_.position_.z -= 0.1f;
	}

	//Player * pPlayer = (Player*)FindObject("Player");
	//transform_.position_.x = pPlayer->GetPosition().x - 1;
	//transform_.position_.z = pPlayer->GetPosition().z - 1;

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

	if (pStage->IsWall((int)transform_.position_.x, (int)transform_.position_.z))
	{
		XMStoreFloat3(&transform_.position_, prevPosition);
	}
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}