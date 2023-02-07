#pragma once
#include "CharacterBase.h"

//◆◆◆を管理するクラス
class Player : public CharacterBase
{
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    void InitBase() override;

    void Action() override;

    void Command() override;
};