#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <DirectXMath.h>
// DirectX::を省略
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;
//共通の変数はまとめる(主にマジックナンバー)
const float m_ColorMax = 1.0f;//透過度の最大
const float m_ColorMin = 0.0f;//透過度の最小

//フレームの最大と最小(イージングのためのやつ)
const float m_FrameMax = 1.0f;
const float m_FrameMin = 0.0f;

//変数を0にするためやif文で(0.0f <)とかのためのもの
//int
const int m_ResetNumber = 0;
//float
const float m_ResetFew = 0.0f;
//XMFLOAT3
const XMFLOAT3 m_ResetThirdFew = { 0.0f,0.0f,0.0f };
//XMFLOAT4
const XMFLOAT4 m_ResetFourthFew = { 0.0f,0.0f,0.0f,0.0f };
//サイズ切り取りサイズ
//フルスクリーン
const int FullWidth_Cut = 1280;
const int FullHeight_Cut = 720;

//ブレンドタイプ
enum BlendType
{
	AlphaBlendType,
	AddBlendType,
	SubBlendType,
};