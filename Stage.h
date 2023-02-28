#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[2];    //���f���ԍ�

    static const int STAGE_SIZE_X = 15;
    static const int STAGE_SIZE_Z = 15;

    int map_[STAGE_SIZE_X][STAGE_SIZE_Z];

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����͕ǁH
    bool IsWall(int x, int z);

    //�����͏��H
    bool IsFloor(int x, int z);
};