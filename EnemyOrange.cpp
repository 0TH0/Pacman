#include "EnemyOrange.h"
#include "EnemyOrange.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Astar.h"
#include "Engine/Math.h"

//コンストラクタ
EnemyOrange::EnemyOrange(GameObject* parent)
    :CharacterBase(parent, "Enemy")
{
}

//デストラクタ
EnemyOrange::~EnemyOrange()
{
}

void EnemyOrange::InitBase()
{
    transform_.position_ = XMFLOAT3(7.5f, 0, 7.5f);
    //モデルデータのロード
    hModel_ = Model::Load("EnemyOrange.fbx");
    assert(hModel_ >= 0);
}

void EnemyOrange::DrawBase()
{
}

void EnemyOrange::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");

    //プレイヤーとオレンジの距離が８以下なら
    bool isPlayerNear = (Math::CalcDist(GetPosition(), pPlayer->GetPosition()) <= 8);

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

    if (isPlayerNear)
    {
        //何フレーム毎に進むか
        int frame = 20;

        if (count_ > frame)
        {
            int x = 0;
            int z = 0;

            x = (int)pPlayer->GetPosition().x;
            z = (int)pPlayer->GetPosition().z;


            //プレイヤーを探索
            if (AI_.Search("map.csv", { (int)transform_.position_.x, (int)transform_.position_.z }, { x, z }))
            {
                totalCell = AI_.GetToGoalTotalCell();
                CanMove_ = true;
            }

            count_ = 0;
        }
        count_++;
    }
}

void EnemyOrange::Command()
{
}

void EnemyOrange::OnCollision(GameObject* pTarget)
{
    //敵に当たった
    if (pTarget->GetObjectName() == "Player")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }
}