#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CregitScene::CreateViewLight() {
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
		//�V���h�E�}�b�v�g�p���Ȃ�
		SetShadowmapDraw(false);
	}

	void CregitScene::CreateSprite() {
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		Vec2 HalfSize;
		HalfSize.x = size.x / 2.0f;
		HalfSize.y = size.y / 2.0f;


		auto cregitSprite = AddGameObject<CregitSprite>(Vec3(100.0f, 100.0f, 1.0f), Vec3(size.x, size.y, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"CREGIT_TX");
		cregitSprite->SetPostion(HalfSize.x, HalfSize.y);
		cregitSprite->SetDrawLayer(0);

	}

	void CregitScene::OnCreate() {
		CreateViewLight();
		CreateSprite();
	}
	void CregitScene::OnUpdate() {
		//auto time = App::GetApp()->GetElapsedTime();
	}

	void CregitScene::SceneChange() {

		////�V�[���̎擾
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		PostEvent(3.0f, GetThis<ObjectInterface>(), PtrScene, L"ToStartStage");

	}
}