#include "Astar.h"
#include <vector>

using namespace std;

CsvReader csv;
const unsigned int MAP_ROW = 15;	 //�s
const unsigned int MAP_COL = 15;     //��
const unsigned int MAX_COSTS = 9999; //�ő�R�X�g

//�}�b�v�̍s��
int COSTMAP[MAP_ROW][MAP_COL];

//�X�^�[�g�n�_����̍ŏ��R�X�g�l������Ă����
int totalCosts[MAP_ROW][MAP_COL];


namespace Astar
{
	CELL startCell;
	CELL GoalCell;

	//�X�^�[�g�n�_�̗���
	static int rowS;
	static int colS;

	//�S�[���n�_�̗���
	static int rowG;
	static int colG;

	int nextRow;
	int nextCol;

	bool close[MAP_ROW][MAP_COL];

	DIR dirToTar;

	void SetStartCell(int row, int col)
	{
		startCell = {row, col};
		rowS = row;
		colS = col;
	}

	void SetGoalCell(int row, int col)
	{
		GoalCell = { row, col };
		rowG = row;
		colG = col;
	}

	CELL GetStartCell()
	{
		return startCell;
	}

	CELL GetGoalCell()
	{
		return GoalCell;
	}

	DIR GetDir() 
	{
		return dirToTar; 
	}

	void MoveToTag()
	{
		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				if (totalCosts[row][col] == 1)
				{
				}
			}
		}
	}

	//�X�^�[�g�n�_�����ď�����
	void Update()
	{
		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//�S�ẴR�X�g��MAX_COSTS�ɂ���
				totalCosts[row][col] = MAX_COSTS;
			}
		}
		//�����ʒu�̃R�X�g��0�ɂ���
		totalCosts[startCell.row][startCell.col] = 0;
	}

	// �}���n�b�^�����������߂�
	int GetDistance(int from_x, int from_y, int to_x, int to_y)
	{
		int cx = from_x - to_x;
		int cy = from_y - to_y;

		if (cx < 0) cx *= -1;
		if (cy < 0) cy *= -1;

		// ����ړ��R�X�g���v�Z
		if (cx < cy) {
			return (cx + (cy - cx));
		}
		else {
			return (cy + (cx - cy));
		}
	}

	//�X�^�[�g�n�_����̃R�X�g���v�Z
	void CalcCosts(CELL cell)
	{
		for (DIRECTION dir : DIRECTIONS)
		{
			nextRow = cell.row + dir.dirRow;
			nextCol = cell.col + dir.dirCol;

			//0��菬�����͖̂���
			if (COSTMAP[nextRow][nextCol] < 0)
			{
				continue;
			}

			//���̍��W�̃R�X�g�����݂̍��W�̃R�X�g���傫��������
			if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol])
			{
				totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol];

				//�R�X�g���v�Z
				CalcCosts({ nextRow, nextCol });
			}

			if (dir.dirCol < cell.col && dir.dirRow < cell.row)
			{
				dirToTar = DIR::U;
			}
		}
	}


	//�R�X�g��\��
	void Show()
	{
		//�e�L�X�g������
		Text* pText = new Text;
		pText->Initialize();

		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//�R�X�g���ő�l����Ȃ�������X�^�[�g�n�_����̃R�X�g��\��
				if (totalCosts[row][col] == 0)
				{
					pText->Draw((row + 1) * 55 + 100, (- col) * 40 + 600 , "S");
				}
				//�S�[����������
				else if (row == rowG && col == colG)
				{
					pText->Draw((row + 1) * 55 + 100, (-col) * 40 + 600, "G");
					close[row][col] = true;
				}
				else if (totalCosts[row][col] != MAX_COSTS)
				{
					pText->Draw((row + 1) * 55 + 100, (-col) * 40 + 600, totalCosts[row][col]);
				}
				else
				{
					pText->Draw((row + 1) * 55 + 100, (-col) * 40 + 600, "|");
				}
			}
		}
	}


	//�}�b�v�ǂݍ���
	void Load(std::string fileName)
	{
		csv.Load(fileName);

		for (int row = 0; row < csv.GetHeight(); row++)
		{
			for (int col = 0; col < csv.GetWidth(); col++)
			{
				//���[�h�����f�[�^��COSTMAP�ɑ��
				COSTMAP[row][col] = csv.GetValue(row, col);
			}
		}
	}

	//�`��
	void Draw()
	{
		//�X�^�[�g�n�_����̃R�X�g���v�Z
		CalcCosts(startCell);

		//�R�X�g��\��
		Show();
	}
};