#include "Block.h"
#include "imgui.h"
#include "ModelManager.h"
#include "VariableCommon.h"
Block* Block::GetInstance()
{
	static Block instance;

	return &instance;
}

//モデル読み込み
void Block::ModelInit() {
	modelNormalBlock = ModelManager::GetInstance()->GetModel(ModelManager::Block);
	//マップチップ用のオブジェクトの初期化
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objNormalBlock[y][x] = make_unique<IKEObject3d>();
			objNormalBlock[y][x]->Initialize();
			objNormalBlock[y][x]->SetModel(modelNormalBlock);
			objNormalBlock[y][x]->SetScale({ 5.0f,5.0f,5.0f });
			objNormalBlock[y][x]->SetTiling({ 5.0f });
			objNormalBlock[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
		}
	}
}
//初期化
void Block::Initialize(std::vector<std::vector<int>>& map, int mapNumber,int StageNumber) {

	stagemap = map;
	MapChip::LoadCsvMap(stagemap, "Resources/csv/stage/stage1.csv");
	MapCreate(0,StageNumber);
}
//更新
void Block::Update() {
	//ステージごとに違う
		//各ブロックのアップデート
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			if ((objNormalBlock[y][x]->GetPosition().y != 1000.0f)) {
				objNormalBlock[y][x]->Update();
			}
		}
	}
}
//描画
void Block::Draw() {
	IKEObject3d::PreDraw();
	//マップチップの描画
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			if ((objNormalBlock[y][x]->GetPosition().y != 1000.0f)) {
				objNormalBlock[y][x]->Draw();
			}
		}
	}
}
//ブロック配置
void Block::MapCreate(int mapNumber, int StageNumber)
{
	
	for (int y = 0; y < map_max_y; y++) {//(yが15)
		for (int x = 0; x < map_max_x; x++) {//(xが59)

			if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 1)
			{
				//位置と大きさの変更
				objNormalBlock[y][x]->SetPosition({ x * LAND_SCALE,-2.0f,-y * LAND_SCALE});
			}
		}
	}
}

//マップチップの初期化
void Block::ResetBlock() {
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objNormalBlock[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
		}
	}
}