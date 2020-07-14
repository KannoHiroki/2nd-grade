#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameClearScene::CreateViewLight() {
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

	void GameClearScene::CreateSpraite() {
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto sprite = AddGameObject<GameClearSprite>(Vec3(100, 100, 1.0f), Vec3(size.x, size.y, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"GAMECLEAR_TX");
		sprite->SetPosTion(1280.0f / 2.0f, 800.0f / 2.0f);
	}

	void GameClearScene::OnCreate() {
		CreateViewLight();

		CreateSpraite();
	}
	void GameClearScene::OnUpdate() {
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//�Q�[���X�e�[�W��
			//A�{�^������������Q�[����ʂ�
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