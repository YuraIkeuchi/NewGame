#include "ImageManager.h"

bool ImageManager::load = false;


ImageManager* ImageManager::GetInstance() {
	static ImageManager instans;
	return &instans;
}
//スプライトの読み込み
void ImageManager::StartLoad2D() {
	IKESprite::LoadTexture(TITLE, L"Resources/2d/sceneback/title.png");
	IKESprite::LoadTexture(PLAY, L"Resources/2d/sceneback/game.png");
	IKESprite::LoadTexture(GAMEOVER, L"Resources/2d/sceneback/over.png");
	IKESprite::LoadTexture(GAMECLEAR, L"Resources/2d/sceneback/clear.png");
}

void ImageManager::SecondLoad2D() {

}

//テクスチャの読み込み
void ImageManager::LoadTex2D() {

}

void ImageManager::LoadParticle() {

	ParticleManager::LoadTexture(Normal, "effect1");
	ParticleManager::LoadTexture(Smoke, "hootEffect");
	load = true;
}

