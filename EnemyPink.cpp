#include "EnemyPink.h"
#include "EnemyPink.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Astar.h"
#include "Engine/Math.h"

//コンストラクタ
EnemyPink::EnemyPink(GameObject* parent)
    :CharacterBase(parent, "Enemy")
{
}

//デストラクタ
EnemyPink::~EnemyPink()
{
}

void EnemyPink::InitBase()
{
    transform_.position_ = XMFLOAT3(13.5f, 0, 1.5f);
    //モデルデータのロード
    hModel_ = Model::Load("EnemyPink.fbx");
    assert(hModel_ >= 0);
}

void EnemyPink::DrawBase()
{
}

void EnemyPink::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { (float)AI_.GetToGoalCell(totalCell).x + 0.5f, 0.0f, (float)AI_.GetToGoalCell(totalCell).z + 0.5f,0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.2f));

            if (Math::CalcDist(transform_.position_, Math::VectorToFloat3(v)) < 1.f)
            {
                transform_.position_ = Math::VectorToFloat3(v);
            }
        }
    }

    //何フレーム毎に進むか
    int frame = 20;

    //ゴールに着いたら
    if (!AI_.GetExistMinNode())
    {
        x = rand() % 15 + 1;
        z = rand() % 15 + 1;
    }

    if (count_ > frame)
    {
        //プレイヤーを探索
        if (AI_.Search("map.csv", { (int)transform_.position_.x, (int)transform_.position_.z }, { x, z}))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void EnemyPink::Command()
{
}

void EnemyPink::OnCollision(GameObject* pTarget)
{
    //敵に当たった
    if (pTarget->GetObjectName() == "Player")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }
}