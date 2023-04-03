#include "Player.h"
#include "ModelManager.h"
#include "Input.h"
#include "VariableCommon.h"
#include "Block.h"
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
	m_Position = { 10.0f,1.0f,-10.0f };
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
	const float STICK_MAX = 1000.0f;
	m_OldPos = m_Position;
	//�ړ�
	if (input->TriggerButton(input->Button_X) && (!m_Move)) {
		m_Move = true;
	}

	if (m_Move) {
		m_Position.x += m_Velocity.x;
		m_Position.z += m_Velocity.z;

		m_Velocity.x *= m_damp1;//���X�ɑ��x�𗎂Ƃ�
		m_Velocity.z *= m_damp1;
		//�ړ��͂��Ȃ��Ȃ����瓮������
		if ((m_Velocity.x < 0.05f && m_Velocity.x > -0.05f) && ((m_Velocity.z < 0.05f && m_Velocity.z > -0.05f))) {
			m_Move = false;
			m_Velocity = m_ResetThirdFew;
		}
		Block::GetInstance()->PlayerMapCollideCommon(m_Position, { 1.5f,1.5f }, m_OldPos, m_Velocity);
	}

	
	////��
	//if (input->LeftTiltStick(input->Up)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,m_Velocity,0 }, m_Angle);
	//	m_Position.z -= vecvel.z * (m_StickrotY / STICK_MAX);
	//}
	////��
	//if (input->LeftTiltStick(input->Down)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,-m_Velocity,0 }, m_Angle);
	//	m_Position.z += vecvel.z * (m_StickrotY / STICK_MAX);
	//}
	////�E
	//if (input->LeftTiltStick(input->Right)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ m_Velocity,0,0,0 }, m_Angle);
	//	m_Position.x += vecvel.x * (m_StickrotX / STICK_MAX);
	//}
	////��
	//if (input->LeftTiltStick(input->Left)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ -m_Velocity,0,0,0 }, m_Angle);
	//	m_Position.x -= vecvel.x * (m_StickrotX / STICK_MAX);
	//}

	m_Rotation.y = m_Angle - (atan2f(m_StickrotX / STICK_MAX, m_StickrotY / STICK_MAX) * (180.0f / XM_PI));
	Obj_SetParam();
}

//�`��
void Player::Draw(DirectXCommon* dxCommon) {
	Obj_Draw();
}

void Player::ImGuiDraw() {
	ImGui::Begin("Player");
	ImGui::Text("Move:%d",m_Move);
	ImGui::Text("VelType:%d", m_Veltype);
	ImGui::Text("Position.x:%f", m_Position.x);
	ImGui::SliderFloat("VelocityX", &m_Velocity.x, -3.0f, 3.0f);
	ImGui::SliderFloat("VelocityZ", &m_Velocity.z, -3.0f, 3.0f);
	ImGui::End();
}
