#pragma once
#include "DirectXCommon.h"
#include "ObjCommon.h"

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
	
public:
	//getter
private:
	//�����o�֐�
};