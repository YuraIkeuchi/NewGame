#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"
#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
using namespace std;         //  名前空間指定

class Player :
	public ObjCommon {
public:
	Player();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dxCommon) override;

	void ImGuiDraw();
	
public:
	//getter
private:
	const float XM_PI = 3.141592654f;
	//メンバ関数
	float m_Angle = 0.0f;
	XMFLOAT3 m_Velocity = {};
	float m_StickrotX = 0.0f;
	float m_StickrotY = 0.0f;
	//摩擦による減衰
	float m_damp1 = 0.95f;
	bool m_Move = false;

	XMFLOAT3 m_OldPos = {};
	enum VelType {
		Adove = 1,//0以上
		Below = -1,//0以下
	};

	int m_Veltype = Adove;
};