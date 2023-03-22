#pragma once
#include <map>
#include <string>
#include "IKESprite.h"
#include "IKETexture.h"
#include "ParticleManager.h"
//2D�̓ǂݍ��ݏ���
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager& r) = default;
	ImageManager& operator= (const ImageManager& r) = default;

public:
	//�X�v���C�g�̖��O
	enum texName {
		TITLE,
		PLAY,
		GAMEOVER,
		GAMECLEAR,
	};
	//�e�N�X�`���̖��O
	enum tex2dName {
	
	};

	enum particleName {
		Normal,
		Smoke

	};
public:
	static ImageManager* GetInstance();		//�擾�p
	static bool load;
	void StartLoad2D();
	void LoadTex2D();
	void SecondLoad2D();
	void LoadParticle();
};

