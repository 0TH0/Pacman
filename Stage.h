#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[2];    //モデル番号

    static const int STAGE_SIZE_X = 15;
    static const int STAGE_SIZE_Z = 15;

    int map_[STAGE_SIZE_X][STAGE_SIZE_Z];

public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //そこは壁？
    bool IsWall(int x, int z);

    //そこは床？
    bool IsFloor(int x, int z);
};