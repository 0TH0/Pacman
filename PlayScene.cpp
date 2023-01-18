#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
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
	Instantiate<Enemy>(this);
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
