#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameOverScene::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto ptrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		ptrMultiLight->SetDefaultLighting();
	}

	void GameOverScene::CreateSprite() {
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto sprite = AddGameObject<GameOverSprite>(Vec3(100, 100, 1.0f), Vec3(size.x, size.y, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"SOIL_TX");
		sprite->SetPosTion(1280.0f / 2.0f, 800.0f / 2.0f);
	}

	void GameOverScene::CreateUI() {
		CreateSharedObjectGroup(L"GameOverUI");

		auto ptrGameOverGroup = GetSharedObjectGroup(L"GameOverUI");

		auto ptrGameOver = AddGameObject<ClearSprite>(true, Vec2(350.8f * 4.0f, 248.0f * 4.0f), Vec3(0.0f, 100.0f, 0.0f), L"GAMEOVER_TX", L"GameOver");
		auto ptrRetry = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(300.0f, -200.0f, 1.0f), L"RETRY_TX", L"Retry");
		auto ptrStageSelect = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(-300.0f, -200.0f, 1.0f), L"STAGESELECT_TX", L"StageSelect");
		ptrGameOverGroup->IntoGroup(ptrRetry);
		ptrGameOverGroup->IntoGroup(ptrStageSelect);
		ptrGameOverGroup->IntoGroup(ptrGameOver);

	}

	void GameOverScene::CreateFadeIn() {

		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto FISprite = AddGameObject<FadeInSprite>(bool(true), Vec2(size.x, size.y), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX");
		FISprite->SetDrawLayer(1000);

	}

	void GameOverScene::OnCreate() {
		CreateViewLight();
		CreateUI();
		CreateSprite();
		CreateFadeIn();
	}
	void GameOverScene::OnUpdate() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//�Q�[���X�e�[�W��
			//A�{�^������������Q�[����ʂ�
			auto GOGroupVec = GetSharedObjectGroup(L"GameOverUI")->GetGroupVector();
			for (auto v : GOGroupVec) {
				v.lock()->SetDrawActive(true);
				v.lock()->SetUpdateActive(true);
			}
			return;

			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), PtrScene, L"ToGameStage");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Decision", 0, 4.0f);
				return;
			}
			else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), PtrScene, L"ToStartStage");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Decision", 0, 4.0f);
				return;
			}
		}
	}
}