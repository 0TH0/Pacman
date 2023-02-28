#include <iostream>
#include <iomanip>
#include <string>
#include "Engine/Text.h"
#include "Engine/CsvReader.h"



namespace Astar
{
	//対象とする座標
	typedef struct tagCell {
		int row;
		int col;
	}CELL;

	//対象とする座標からの距離
	typedef struct tagDirection {
		int dirRow;
		int dirCol;
	}DIRECTION;

	enum DIR
	{
		L = 0,
		R,
		D,
		U
	 };

	const DIRECTION DIRECTIONS[] =
	{
		{  0, -1 },		// L
		{  0, +1 },		// R
		{ -1,  0 },		// D
		{ +1,  0 }		// U
	};

	bool Init(CELL startCell, CELL goalCell);
	//初期化
	void Update();
	//スタート地点からのコストを計算
	void CalcCosts(CELL cell);
	//コストを表示
	void Show();
	//マップ読み込み
	void Load(std::string fileName);
	//描画
	void Draw();
	//マンハッタン距離
	int GetDistance(int from_x, int from_y, int to_x, int to_y);

	void SetStartCell(int row, int col);

	void SetGoalCell(int row, int col);

	CELL GetStartCell();
	CELL GetGoalCell();

	//目標地点に移動
	void MoveToTag();
};