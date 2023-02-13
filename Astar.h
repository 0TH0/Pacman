#include <iostream>
#include <iomanip>
#include <string>
#include "Engine/Text.h"
#include "Engine/CsvReader.h"



namespace Astar
{
	//�ΏۂƂ�����W
	typedef struct tagCell {
		int row;
		int col;
	}CELL;

	//�ΏۂƂ�����W����̋���
	typedef struct tagDirection {
		int dirRow;
		int dirCol;
	}DIRECTION;

	const DIRECTION DIRECTIONS[] =
	{
		{  0, -1 },		// L
		{  0, +1 },		// R
		{ -1,  0 },		// U
		{ +1,  0 }		// D
	};

	//������
	void Init();
	//�X�^�[�g�n�_����̃R�X�g���v�Z
	void CalcCosts(CELL cell);
	//�R�X�g��\��
	void Show();
	//�}�b�v�ǂݍ���
	void Load(std::string fileName);
	//�`��
	void Draw();
	//�}���n�b�^������
	int GetDistance(int from_x, int from_y, int to_x, int to_y);

	void SetStartCell(int row, int col);

	void SetGoalCell(int row, int col);

	CELL GetStartCell();
	CELL GetGoalCell();
};