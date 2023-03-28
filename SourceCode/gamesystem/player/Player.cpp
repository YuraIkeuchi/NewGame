#include "Player.h"
#include "ModelManager.h"
#include "Input.h"
#include "VariableCommon.h"
using namespace std;         //  名前空間指定
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
	Input* input = Input::GetInstance();
	m_StickrotX = input->GetPosX();
	m_StickrotY = input->GetPosY();
	const float STICK_MAX = 1000.0f;
	//移動
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

		m_Velocity *= m_damp1;//徐々に速度を落とす
		//移動力がなくなったら動かせる
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
	////上
	//if (input->LeftTiltStick(input->Up)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,m_Velocity,0 }, m_Angle);
	//	m_Position.z -= vecvel.z * (m_StickrotY / STICK_MAX);
	//}
	////下
	//if (input->LeftTiltStick(input->Down)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ 0,0,-m_Velocity,0 }, m_Angle);
	//	m_Position.z += vecvel.z * (m_StickrotY / STICK_MAX);
	//}
	////右
	//if (input->LeftTiltStick(input->Right)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ m_Velocity,0,0,0 }, m_Angle);
	//	m_Position.x += vecvel.x * (m_StickrotX / STICK_MAX);
	//}
	////左
	//if (input->LeftTiltStick(input->Left)) {
	//	XMFLOAT3 vecvel = MoveVECTOR(XMVECTOR{ -m_Velocity,0,0,0 }, m_Angle);
	//	m_Position.x -= vecvel.x * (m_StickrotX / STICK_MAX);
	//}

	m_Rotation.y = m_Angle - (atan2f(m_StickrotX / STICK_MAX, m_StickrotY / STICK_MAX) * (180.0f / XM_PI));
	Obj_SetParam();
}

//描画
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
