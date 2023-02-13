#include "Astar.h"
#include <vector>

using namespace std;

CsvReader csv;
const unsigned int MAP_ROW = 15;	 //行
const unsigned int MAP_COL = 15;     //列
const unsigned int MAX_COSTS = 9999; //最大コスト

//マップの行列
int COSTMAP[MAP_ROW][MAP_COL];

//スタート地点からの最小コスト値をいれてくやつ
int totalCosts[MAP_ROW][MAP_COL];


namespace Astar
{
	CELL startCell;
	CELL GoalCell;

	//スタート地点の乱数
	static int rowS;
	static int colS;

	//ゴール地点の乱数
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

	//スタート地点を入れて初期化
	void Update()
	{
		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//全てのコストをMAX_COSTSにする
				totalCosts[row][col] = MAX_COSTS;
			}
		}
		//初期位置のコストを0にする
		totalCosts[startCell.row][startCell.col] = 0;
	}

	// マンハッタン距離を求める
	int GetDistance(int from_x, int from_y, int to_x, int to_y)
	{
		int cx = from_x - to_x;
		int cy = from_y - to_y;

		if (cx < 0) cx *= -1;
		if (cy < 0) cy *= -1;

		// 推定移動コストを計算
		if (cx < cy) {
			return (cx + (cy - cx));
		}
		else {
			return (cy + (cx - cy));
		}
	}

	//スタート地点からのコストを計算
	void CalcCosts(CELL cell)
	{
		for (DIRECTION dir : DIRECTIONS)
		{
			nextRow = cell.row + dir.dirRow;
			nextCol = cell.col + dir.dirCol;

			//0より小さいのは無視
			if (COSTMAP[nextRow][nextCol] < 0)
			{
				continue;
			}

			//次の座標のコストが現在の座標のコストより大きかったら
			if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol])
			{
				totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol];

				//コストを計算
				CalcCosts({ nextRow, nextCol });
			}

			if (dir.dirCol < cell.col && dir.dirRow < cell.row)
			{
				dirToTar = DIR::U;
			}
		}
	}


	//コストを表示
	void Show()
	{
		//テキスト初期化
		Text* pText = new Text;
		pText->Initialize();

		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//コストが最大値じゃなかったらスタート地点からのコストを表示
				if (totalCosts[row][col] == 0)
				{
					pText->Draw((row + 1) * 55 + 100, (- col) * 40 + 600 , "S");
				}
				//ゴールだったら
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


	//マップ読み込み
	void Load(std::string fileName)
	{
		csv.Load(fileName);

		for (int row = 0; row < csv.GetHeight(); row++)
		{
			for (int col = 0; col < csv.GetWidth(); col++)
			{
				//ロードしたデータをCOSTMAPに代入
				COSTMAP[row][col] = csv.GetValue(row, col);
			}
		}
	}

	//描画
	void Draw()
	{
		//スタート地点からのコストを計算
		CalcCosts(startCell);

		//コストを表示
		Show();
	}
};