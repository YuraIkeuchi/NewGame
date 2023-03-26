#include "Player.h"
#include "ModelManager.h"

//モデル読み込み
Player::Player() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::Player);

	m_Object = make_unique<IKEObject3d>();
	m_Object->Initialize();
	m_Object->SetModel(m_Model);
}

//初期化
bool Player::Initialize() {
	m_Position = { 0.0f,1.0f,0.0f };
	m_Scale = { 2.0f,2.0f,2.0f };
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Color = { 1.0f,1.0f,1.0f,1.0 };
	return true;
}

//更新
void Player::Update() {
	Obj_SetParam();
}

//描画
void Player::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}