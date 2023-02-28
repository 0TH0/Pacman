#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Astar.h"

//◆◆◆を管理するクラス
class EnemyRed : public CharacterBase
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
public:
    //コンストラクタ
    EnemyRed(GameObject* parent);

    //デストラクタ
    ~EnemyRed();

    void InitBase() override;

    void DrawBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};