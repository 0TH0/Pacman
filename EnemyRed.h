#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Astar.h"

//���������Ǘ�����N���X
class EnemyRed : public CharacterBase
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
public:
    //�R���X�g���N�^
    EnemyRed(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyRed();

    void InitBase() override;

    void DrawBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};