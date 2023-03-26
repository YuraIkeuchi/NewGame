#include "Player.h"
#include "ModelManager.h"

//ƒ‚ƒfƒ‹“Ç‚İ‚İ
Player::Player() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::Player);

	m_Object = make_unique<IKEObject3d>();
	m_Object->Initialize();
	m_Object->SetModel(m_Model);
}

//‰Šú‰»
bool Player::Initialize() {
	m_Position = { 0.0f,1.0f,0.0f };
	m_Scale = { 2.0f,2.0f,2.0f };
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Color = { 1.0f,1.0f,1.0f,1.0 };
	return true;
}

//XV
void Player::Update() {
	Obj_SetParam();
}

//•`‰æ
void Player::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}