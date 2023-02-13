#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Enemy : public CharacterBase
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    void InitBase() override;

    void DrawBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};