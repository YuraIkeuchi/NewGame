#include "Block.h"
#include "imgui.h"
#include "ModelManager.h"
#include "VariableCommon.h"
Block* Block::GetInstance()
{
	static Block instance;

	return &instance;
}

//���f���ǂݍ���
void Block::ModelInit() {
	modelNormalBlock = ModelManager::GetInstance()->GetModel(ModelManager::Block);
	//�}�b�v�`�b�v�p�̃I�u�W�F�N�g�̏�����
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
//������
void Block::Initialize(std::vector<std::vector<int>>& map, int mapNumber,int StageNumber) {

	stagemap = map;
	MapChip::LoadCsvMap(stagemap, "Resources/csv/stage/stage1.csv");
	MapCreate(0,StageNumber);
}
//�X�V
void Block::Update() {
	//�X�e�[�W���ƂɈႤ
		//�e�u���b�N�̃A�b�v�f�[�g
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
//�`��
void Block::Draw() {
	IKEObject3d::PreDraw();
	//�}�b�v�`�b�v�̕`��
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
//�u���b�N�z�u
void Block::MapCreate(int mapNumber, int StageNumber)
{
	
	for (int y = 0; y < map_max_y; y++) {//(y��15)
		for (int x = 0; x < map_max_x; x++) {//(x��59)

			if (MapChip::GetChipNum(x, y, stagemap[mapNumber]) == 1)
			{
				//�ʒu�Ƒ傫���̕ύX
				objNormalBlock[y][x]->SetPosition({ x * LAND_SCALE,-2.0f,-y * LAND_SCALE});
			}
		}
	}
}

//�}�b�v�`�b�v�̏�����
void Block::ResetBlock() {
	for (int y = 0; y < map_max_y; y++)
	{
		for (int x = 0; x < map_max_x; x++)
		{
			objNormalBlock[y][x]->SetPosition({ 1000.0f,1000.0f,1000.0f });
		}
	}
}