#include "PlaySceneActor.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "imgui.h"
#include "VariableCommon.h"
#include "ParticleEmitter.h"
#include "ModelManager.h"
#include "VolumManager.h"
//������
void PlaySceneActor::Initialize(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	dxCommon->SetFullScreen(true);
	//���ʂ̏�����
	BaseInitialize(dxCommon);
	//�I�[�f�B�I
	Audio::GetInstance()->LoadSound(1, "Resources/Sound/BGM/Boss.wav");
	//�|�X�g�G�t�F�N�g�̃t�@�C���w��
	postEffect->CreateGraphicsPipeline(L"Resources/Shaders/PostEffectTestVS.hlsl", L"Resources/Shaders/NewToneMapPS.hlsl");

	PlayPostEffect = true;

	//�^�C�g��
	IKESprite* PlaySprite_;
	PlaySprite_ = IKESprite::Create(ImageManager::PLAY, { 0.0f,0.0f });
	PlaySprite.reset(PlaySprite_);

	modelGround = ModelManager::GetInstance()->GetModel(ModelManager::Ground);
	modelCube = ModelManager::GetInstance()->GetModel(ModelManager::Cube);

	objCube = make_unique<IKEObject3d>();
	objCube->Initialize();
	objCube->SetModel(modelCube);
	objCube->SetPosition({ 0.0f,5.0f,0.0f });

	objGround = make_unique<IKEObject3d>();
	objGround->Initialize();
	objGround->SetModel(modelGround);
	objGround->SetPosition({ 0.0f,0.0f,0.0f });

	player = make_unique< Player>();
	player->Initialize();
}
//�X�V
void PlaySceneActor::Update(DirectXCommon* dxCommon, DebugCamera* camera, LightGroup* lightgroup)
{
	Input* input = Input::GetInstance();
	if (input->TriggerButton(input->Button_A)) {
		SceneManager::GetInstance()->ChangeScene("GAMECLEAR");
		Audio::GetInstance()->StopWave(1);
	}
	//���y�̉��ʂ��ς��
	Audio::GetInstance()->VolumChange(0, VolumManager::GetInstance()->GetBGMVolum());
	camerawork->Update(camera);


	objCube->Update();
	objGround->Update();
	player->Update();
	lightgroup->Update();
}
//���ʂ̍X�V
void PlaySceneActor::NormalUpdate() {
	VolumManager::GetInstance()->Update();
}
//�{�X�o��̍X�V
void PlaySceneActor::BossAppUpdate() {
}
//�{�X�I���̍X�V
void PlaySceneActor::BossEndUpdate() {
}
//�`��
void PlaySceneActor::Draw(DirectXCommon* dxCommon)
{
	//�`����@
	//�|�X�g�G�t�F�N�g�������邩
	if (PlayPostEffect) {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		BackDraw(dxCommon);
		postEffect->PostDrawScene(dxCommon->GetCmdList());

		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCmdList());
		FrontDraw(dxCommon);
		ImGuiDraw(dxCommon);
		postEffect->ImGuiDraw();
		dxCommon->PostDraw();
	}
	else {
		postEffect->PreDrawScene(dxCommon->GetCmdList());
		postEffect->Draw(dxCommon->GetCmdList());
		postEffect->PostDrawScene(dxCommon->GetCmdList());
		dxCommon->PreDraw();
		BackDraw(dxCommon);
		FrontDraw(dxCommon);
		dxCommon->PostDraw();
	}
}
//���
void PlaySceneActor::Finalize()
{
}
//���f���̕`��
void PlaySceneActor::ModelDraw(DirectXCommon* dxCommon) {
	IKEObject3d::PreDraw();
	player->Draw(dxCommon);
	//objCube->Draw();
	objGround->Draw();
	IKEObject3d::PostDraw();
}
//���̕`��
void PlaySceneActor::BackDraw(DirectXCommon* dxCommon)
{
#pragma endregion
	ModelDraw(dxCommon);
}
//�|�X�g�G�t�F�N�g��������Ȃ�
void PlaySceneActor::FrontDraw(DirectXCommon* dxCommon) {
	//���S�ɑO�ɏ����X�v���C�g
	IKESprite::PreDraw();
	//PlaySprite->Draw();
	IKESprite::PostDraw();
}
//IMGui�̕`��
void PlaySceneActor::ImGuiDraw(DirectXCommon* dxCommon) {
	camerawork->ImGuiDraw();
}
//���ʂ̕`��
void PlaySceneActor::NormalDraw(DirectXCommon* dxCommon) {
}
//�{�X�o��V�[���̕`��
void PlaySceneActor::BossAppDraw(DirectXCommon* dxCommon) {
}
//�{�X�I���V�[���̕`��
void PlaySceneActor::BossEndDraw(DirectXCommon* dxCommon) {
	ParticleEmitter::GetInstance()->FlontDrawAll();
}
