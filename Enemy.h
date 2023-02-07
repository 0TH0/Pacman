#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Enemy : public CharacterBase
{
public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    void InitBase() override;

    void Action() override;

    void Command() override;

    void OnCollision(GameObject* pTarget) override;
};