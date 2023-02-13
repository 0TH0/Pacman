#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"

//◆◆◆を管理するクラス
class Enemy : public CharacterBase
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    void InitBase() override;

    void DrawBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};