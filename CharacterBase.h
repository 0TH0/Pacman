#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Collider.h"

//���������Ǘ�����N���X
class CharacterBase : public GameObject
{
protected:
    int hModel_;    //���f���ԍ�

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
    //�R���X�g���N�^
    CharacterBase(GameObject* parent);
    //�p���p�R���X�g���N�^
    CharacterBase(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~CharacterBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    float Diff(float x1, float x2);
};