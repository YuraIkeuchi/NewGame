#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"

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
	
public:
	//getter
private:
	//メンバ関数
};