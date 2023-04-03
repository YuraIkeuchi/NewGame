#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
using namespace std;         //  ���O��Ԏw��

class Player :
	public ObjCommon {
public:
	Player();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Initialize() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

	void ImGuiDraw();
	
public:
	//getter
private:
	const float XM_PI = 3.141592654f;
	//�����o�֐�
	float m_Angle = 0.0f;
	XMFLOAT3 m_Velocity = {};
	float m_StickrotX = 0.0f;
	float m_StickrotY = 0.0f;
	//���C�ɂ�錸��
	float m_damp1 = 0.95f;
	bool m_Move = false;

	XMFLOAT3 m_OldPos = {};
	enum VelType {
		Adove = 1,//0�ȏ�
		Below = -1,//0�ȉ�
	};

	int m_Veltype = Adove;
};