/*!
@file ResultStage.cpp
@brief ���U���g�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void ResultStage::OnCreate() {
		CreateViewLight();
		
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strTexture = (dataDir + L"Tx_Result.png");
		App::GetApp()->RegisterTexture(L"RESULT_TX", strTexture);

		AddGameObject<TitleSprite>(L"RESULT_TX", true, Vec2(1280, 800), Vec2(0, 0));
	}

	void ResultStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<ResultStage>());
	}

	void ResultStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
	}
}