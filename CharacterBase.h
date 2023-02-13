#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Collider.h"

//◆◆◆を管理するクラス
class CharacterBase : public GameObject
{
protected:
    int hModel_;    //モデル番号

    Stage* pStage;

    XMVECTOR prevPosition;

    enum class DIR
    {
        Default = 0,
        L,
        R,
        U,
        D
    } dir_;

    int time_;
    DIR dir2_;

    float speed_;
    float speedTotal_;

   virtual void Action() = 0;
   virtual void Command() = 0;
   virtual void InitBase() = 0;
   virtual void DrawBase() = 0;

public:
    //コンストラクタ
    CharacterBase(GameObject* parent);
    //継承用コンストラクタ
    CharacterBase(GameObject* parent, std::string name);

    //デストラクタ
    ~CharacterBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    float Diff(float x1, float x2);
};