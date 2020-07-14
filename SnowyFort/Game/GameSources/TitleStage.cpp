/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
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

	//�X�v���C�g�̍쐬
	void TitleStage::CreateTitleSprite() {
		//�e�N�X�`���ǂݍ���
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strTexture = dataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = dataDir + L"Tx_BackGround.png";
		App::GetApp()->RegisterTexture(L"BACKGROUND_TX", strTexture);
		strTexture = dataDir + L"Press B.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = dataDir + L"Tx_Title_Snow.png";
		App::GetApp()->RegisterTexture(L"SNOW_TX", strTexture);

		//�I�u�W�F�N�g����
		AddGameObject<TitleSprite>(L"BACKGROUND_TX", false, Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
		AddGameObject<TitleSprite>(L"TITLE_TX", true,
			Vec2(256.0f, 128.0f) * 3.5, Vec2(0.0f, 120.0f));
		AddGameObject<AnimeSprite>(L"MESSAGE_TX", true, Vec2(518.0f, 256.0f), Vec2(0.0f, -300.0f));

		AddGameObject<MoveSprite>(L"SNOW_TX", true, Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));		
	}

	//������
	void TitleStage::OnCreate() {
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
	}

	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	void TitleStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWaitStage");
	}

}