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
	const float STICK_MAX = 1000.0f;
	//�ړ�
	if (input->TriggerButton(input->Button_X) && (!m_Move)) {
		m_Move = true;
		if (m_Velocity > m_ResetFew) {
			m_Veltype = Adove;
		}
		else {
			m_Veltype = Below;
		}
	}

	if (m_Move) {
		m_Position.x += m_Velocity;

		m_Velocity *= m_damp1;//���X�ɑ��x�𗎂Ƃ�
		//�ړ��͂��Ȃ��Ȃ����瓮������
		if (m_Veltype == Adove) {
			if (m_Velocity < 0.1f) {
				m_Velocity = m_ResetFew;
				m_Move = false;
			}
		}
		else {
			if (m_Velocity > -0.1f) {
				m_Velocity = m_ResetFew;
				m_Move = false;
			}
		}
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
	ImGui::SliderFloat("Velocity", &m_Velocity, -3.0f, 3.0f);
	ImGui::End();
}
