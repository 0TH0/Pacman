#pragma once
#include "CharacterBase.h"

//���������Ǘ�����N���X
class Player : public CharacterBase
{
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    void InitBase() override;

    void Action() override;

    void Command() override;
};