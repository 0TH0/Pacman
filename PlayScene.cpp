#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyRed.h"
#include "EnemyOrange.h"
#include "EnemyPink.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<EnemyRed>(this);
	Instantiate<EnemyOrange>(this);
	Instantiate<EnemyPink>(this);
	Camera::SetPosition(XMFLOAT3(7, 15, -4));
	Camera::SetTarget(XMFLOAT3(7, 0, 7));
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
