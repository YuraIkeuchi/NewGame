#include "Player.h"
#include "ModelManager.h"
#include "Input.h"
#include "VariableCommon.h"
using namespace std;         //  ���O��Ԏw��
//���f���ǂݍ���
Player::Player() {
	m_Model = ModelManager::GetInstance()->GetModel(ModelManager::Player);

	m_Object = make_unique<IKEObject3d>();
	m_Object->Initialize();
	m_Object->SetModel(m_Model);
}

//������
bool Player::Initialize() {
	m_Position = { 0.0f,1.0f,0.0f };
	m_Scale = { 2.0f,2.0f,2.0f };
	m_Rotation = { 0.0f,0.0f,0.0f };
	m_Color = { 1.0f,1.0f,1.0f,1.0 };
	return true;
}

//�X�V
void Player::Update() {
	Input* input = Input::GetInstance();
	m_StickrotX = input->GetPosX();
	m_StickrotY = input->GetPosY();
	const float STICK_MAX = 32767.0f;
	//�ړ�
	//��
	if (input->LeftTiltStick(input->Up)) {
		XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,m_Velocity,0 }, m_Angle);
		m_Position.z -= vecvel.z * (m_StickrotY / STICK_MAX);
	}
	//��
	if (input->LeftTiltStick(input->Down)) {
		XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,-m_Velocity,0 }, m_Angle);
		m_Position.z += vecvel.z * (m_StickrotY / STICK_MAX);
	}
	//�E
	if (input->LeftTiltStick(input->Right)) {
		XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ m_Velocity,0,0,0 }, m_Angle);
		m_Position.x += vecvel.x * (m_StickrotX / STICK_MAX);
	}
	//��
	if (input->LeftTiltStick(input->Left)) {
		XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ -m_Velocity,0,0,0 }, m_Angle);
		m_Position.x -= vecvel.x * (m_StickrotX / STICK_MAX);
	}

	m_Rotation.y = m_Angle - (atan2f(m_StickrotX / STICK_MAX, m_StickrotY / STICK_MAX) * (180.0f / XM_PI));
	Obj_SetParam();
}

//�`��
void Player::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}

void Player::ImGuiDraw() {
	ImGui::Begin("Player");
	ImGui::Text("X:%f", m_StickrotX);
	ImGui::Text("Y:%f", m_StickrotY);
	ImGui::Text("PosX:%f", m_Position.x);
	ImGui::Text("PosZ:%f", m_Position.z);
	ImGui::Text("RotY:%f", m_Rotation.y);
	ImGui::End();
}
