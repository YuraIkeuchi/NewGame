#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//マップのサイズ(基本は1)
const int map_size = 1;
//縦横の最大数(マップによって変更)
const int map_max_x = 10, map_max_y = 10;

class MapChip
{
public:
	//csv読み込み
	static void LoadCsvMap(std::vector<std::vector<int>>& mapData, std::string fName);
	//マップ番号
	static int GetChipNum(int x,int y, std::vector<int> map);
};

