#include "EnemyRed.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Astar.h"
#include "Engine/Math.h"

//�R���X�g���N�^
EnemyRed::EnemyRed(GameObject* parent)
	:CharacterBase(parent, "Enemy")
{
}

//�f�X�g���N�^
EnemyRed::~EnemyRed()
{
}

void EnemyRed::InitBase()
{
	transform_.position_ = XMFLOAT3(13.5f, 0, 13.5f);
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("EnemyRed.fbx");
	assert(hModel_ >= 0);
}

void EnemyRed::DrawBase()
{
}

void EnemyRed::Action()
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

    //���t���[�����ɐi�ނ�
    int frame = 20;

    if (count_ > frame)
    {
        int x = (int)pPlayer->GetPosition().x;
        int z = (int)pPlayer->GetPosition().z;

        //�v���C���[��T��
        if (AI_.Search("map.csv", { (int)transform_.position_.x, (int)transform_.position_.z }, { x, z }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

       count_ = 0;
    }
    count_++;
}

void EnemyRed::Command()
{
}

void EnemyRed::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Player")
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
	}
}