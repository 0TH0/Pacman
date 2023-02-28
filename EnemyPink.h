#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Astar.h"

//◆◆◆を管理するクラス
class EnemyPink : public CharacterBase
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int time_;
    int x = rand() % 15 + 1;
    int z = rand() % 15 + 1;
public:
    //コンストラクタ
    EnemyPink(GameObject* parent);

    //デストラクタ
    ~EnemyPink();

    void InitBase() override;

    void DrawBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};