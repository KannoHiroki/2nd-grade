/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		//MyCameraView�p�̃r���[
		const Vec3 at(0.0f, 0.0f, 0.0f);
		//�r���[�̃J�����̐ݒ�
		m_PtrCamera = ObjectFactory::Create<MyPlayerCamera>();
		//�J�����̐ݒ�
		m_PtrCamera->SetArmParam(
			15.0f,		//�J�������璍���_�܂ł̋����ifloat& armLength�j
			3.0f		//�^�[�Q�b�g�I�u�W�F�N�g�i�v���C���[�j��y���W����J�����܂ł̍����ifloat& armHeight�j
		);
		m_PtrCamera->SetAt(at);

		//ObjCameraView�p�̃r���[
		auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		ptrObjCamera->SetEye(Vec3(0.0f, 12.0f, 0.1f));
		ptrObjCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_CameraSelect = CameraSelect::myCamera;

		//���C���J�����̈ʒu�ƃT�C�Y
		Viewport viewport{
			0,			//float TopLeftX;
			0,			//float TopLeftY;
			1280,		//float Width;
			800,		//float Height;
			0,			//float MinDepth;
			1.0f,		//float MaxDepth;
		};

		//�~�j�}�b�v�̈ʒu�ƃT�C�Y
		Viewport miniMap{
			1280/3*2,	//float TopLeftX;
			0,			//float TopLeftY;
			1280/3,		//float Width;
			800/3,		//float Height;
			0,			//float MinDepth;
			1.0f,		//float MaxDepth;
		};

		m_MyMultiView = ObjectFactory::Create<MultiView>(GetThis<Stage>());
		m_MyMultiView->SetTargetIndex(m_MyMultiView->AddView(viewport,m_PtrCamera));
		m_MyMultiView->SetTargetIndex(m_MyMultiView->AddView(miniMap,ptrObjCamera));
		m_MyMultiView->SetViewport(0, viewport);
		m_MyMultiView->SetViewport(1, miniMap);
		m_MyMultiView->SetCamera(0, m_PtrCamera);
		m_MyMultiView->SetCamera(1, ptrObjCamera);

		SetView(m_MyMultiView);

		m_MyMultiView->ChangeNextView();

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

		CreateSharedObjectGroup(L"Enemy");
	}

	void GameStage::CreateSkyObj() {
		AddGameObject<FixedBox>(Vec3(-30.0f,-30.0f,-30.0f), Vec3(0.0f,0.0f,0.0f), Vec3(0.0f,0.0f,0.0f));
	}

	//�R�̃{�b�N�X�̍쐬
	void GameStage::CreateFixedBox() {
		//��R
		//AddGameObject<Mountain>(Vec3(1.1f, 1.f, 1.1f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0, -2.8f, 0.0f));
		//AddGameObject<Mountain>();
		float slopeAngle = XMConvertToRadians(-18.9f); // �Ζʂ̊p�x
		float slopeLength = 3.8f;
		float slopePositionY = -1.8f;
		float angle = 360.0f / 8.0f;
		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();
		//�R��
		Quat moveQt;

		//AddGameObject< FixedPsBox>(Vec3(2.3f,0.5f,2.3f), Quat(0,0,0,0), Vec3(playerPtr->GetDefPos().x,playerPtr->GetDefPos().y + -0.55f,playerPtr->GetDefPos().z));

	/*	for (int i = 0; i < (int)360.0f / angle; i++) {
			//�v���C���[�̑���쐬(�R��)
			rad = XMConvertToRadians(angle * i);
			Vec3 scaffoldingPos = Vec3(
				playerPtr->GetDefPos().x + (playerPtr->GetPlayerMoveCircleHalf() * 0.9f) * cosf(rad),
				playerPtr->GetDefPos().y + -0.5f,
				playerPtr->GetDefPos().z + (playerPtr->GetPlayerMoveCircleHalf() * 0.9f) * sinf(rad)
			);
			moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));

			AddGameObject<FixedPsBox>(
				Vec3(0.3f, 0.5f, 1.1f),
				moveQt,
				Vec3(scaffoldingPos)
			);
		}*/

		AddGameObject<FixedPsSphere>(Vec3(20.0f), Vec3(0.0f), Vec3(0.0f, -10.2f, 0.0f));
	
		/*Vec3 scaffoldingPos;
		angle = 360.0f / 12.0f; // �[�̕�����
		//�R�̘[(�ӂ���)
		for (int i = 0; i < (int)360.0f / angle; i++) {
			//�v���C���[�̑���쐬(�R��)
			rad = XMConvertToRadians(angle * i + angle / 2); // 30�x�����炵�Ĕz�u + 15�x���炵�Ē���
			moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
			scaffoldingPos = Vec3(
				playerPtr->GetDefPos().x + (playerPtr->GetPlayerMoveCircleHalf() * 6.f) * cosf(rad),
				playerPtr->GetDefPos().y + -3.1f,
				playerPtr->GetDefPos().z + (playerPtr->GetPlayerMoveCircleHalf() * 6.f) * sinf(rad)
			);
			AddGameObject<FixedPsBox>(
				Vec3(1.f, 0.5f, 4.5f),
				moveQt,
				Vec3(scaffoldingPos)
			);
			//�z�u�����
			for (int j = 0; j < 8; j++) {
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, slopeAngle));
				scaffoldingPos.normalize(); // �傫����1�ɂ���
				float slopeScale = 1.1f + (j* 0.5f);
				Vec3 slopePos = Vec3(scaffoldingPos.x, scaffoldingPos.y, scaffoldingPos.z) * (j + 2.0f);
				AddGameObject<FixedPsBox>(
					Vec3(1.f, 0.5f, slopeScale),
					moveQt,
					Vec3(slopePos)
				);

				//if (j >= 4) {
				//	for (int i = 0; i < 1; i++) {
				//		auto ptrEnemy = AddGameObject<EnemyObject>(Vec3(slopePos.x, slopePos.y + 1.0f, slopePos.z));				
				//		auto group = GetSharedObjectGroup(L"Enemy");
				//		group->IntoGroup(ptrEnemy);
				//	}
				//}
			}
		}
		*/

		AddGameObject<Plane>();
	}

	//�v���C���[�̍쐬
	void GameStage::CreatePlayer() {
		//�v���[���[�̍쐬
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"Player", ptrPlayer);
	}

	//�X�R�A�X�v���C�g�쐬
	void GameStage::CreateNumSprite() {
		AddGameObject<NumSprite>(2,
			L"NUMBER_TX",
			true,
			Vec2(128.0f, 80.0f),
			Vec3(-350.0f, 350.0f, 0.0f),
			99.0f + 1.0f); // ��������
	}

	//�Ԃ̍쐬
	void GameStage::CreateFort() {
		auto ptr = AddGameObject<Fort>(Vec3(1.0f,1.0f,1.0f), Vec3(0.0f,0.0f,0.0f), Vec3(0.0f,-0.3f,0.0f));
		SetSharedGameObject(L"Fort", ptr);
	}

	//����p�z�u
	void GameStage::CreateMovieStage() {
		AddGameObject<BigEnemyObject>(Vec3(4.0f, 0, 4.0f));
		AddGameObject<EnemyObject>(Vec3(3.0f - 0.1f, 0, 4.3f - 0.1f));
		AddGameObject<EnemyObject>(Vec3(3.6f, 0, 4.5f));
		AddGameObject<EnemyObject>(Vec3(3.8f, 0, 4.2f));
		AddGameObject<EnemyObject>(Vec3(3.5f, 0, 4.8f));
	}

	//�؂̍쐬
	void GameStage::CreateTree() {
		//�����_���֐��p
		srand((unsigned int)time(NULL));

		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();
		Quat moveQt;

		Vec3 treePos;
		auto angle = 360.0f / 30.0f; // �[�̕�����
		//�R�̘[(�ӂ���)
		for (float i = 6.0f; i < 10.0f; i++) {
			for (int j = 0; j < (int)360.0f / angle; j++) {
				//�v���C���[�̑���쐬(�R��) 
				rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * j); // 30�x�����炵�Ĕz�u + 15�x���炵�Ē���
				float randLength = (playerPtr->GetPlayerMoveCircleHalf() * i) + (float)((rand() % 20 + 1) / 10); //0.0f�`2.0f�܂ł̃����_���Ȓl�����炷
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
				treePos = Vec3(
					playerPtr->GetDefPos().x + randLength * cosf(rad),
					playerPtr->GetDefPos().y + -3.1f,
					playerPtr->GetDefPos().z + randLength * sinf(rad)
				);

				AddGameObject<Tree>(treePos, Vec3(0));
			}
		}
	}

	//�X�|�[���쐬
	void GameStage::CreateSpawnBlock() {
		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();

		Vec3 spawnPos;
		auto angle = 360.0f / 3.0f; // ������
		for (int i = 0; i < (int)360.0f / angle; i++) {
			rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * i);
			float randLength = 7.0f;
			spawnPos = Vec3(
				playerPtr->GetDefPos().x + randLength * cosf(rad),
				playerPtr->GetDefPos().y + -2.5f,
				playerPtr->GetDefPos().z + randLength * sinf(rad)
			);

			AddGameObject<SpawnBlock>(spawnPos);
		}
	}

	//�J�����}���̍쐬
	void GameStage::CreateCameraman() {
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//�V�F�A�z���Cameraman��ǉ�
		SetSharedGameObject(L"Cameraman", ptrCameraman);
	}

	//�G�����_���z�u
	void GameStage::CreateEnemy() {
		m_elapsedTime += App::GetApp()->GetElapsedTime();

		if (m_elapsedTime > 7.0f) {
			m_elapsedTime = 0;

			auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
			auto rad = playerPtr->GetRad();
			Quat moveQt;

			Vec3 enemyPos;
			auto angle = 360.0f / 10.0f; // ������
			for (int i = 0; i < (int)360.0f / angle; i++) {
				rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * i);
				float length = 7.0f;
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
				enemyPos = Vec3(
					playerPtr->GetDefPos().x + length * cosf(rad),
					playerPtr->GetDefPos().y - 2.5f,
					playerPtr->GetDefPos().z + length * sinf(rad)
				);
				
				AddGameObject<EnemyObject>(enemyPos);
			}
		}
	}

	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�X�J�C�{�b�N�X
			CreateSkyObj();
			//�Ԃ̍쐬
			CreateFort();
			//�v���[���[�̍쐬
			CreatePlayer();
			//�Œ�̃{�b�N�X�̍쐬
			CreateFixedBox();
			//UI�X�v���C�g�̍쐬
			CreateNumSprite();
			////�J�����}���̍쐬
			//CreateCameraman();
			CreateMovieStage();

			//CreateEnemy();

			CreateSpawnBlock();
			CreateTree();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameStage>());
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto numSpritePtr = GetSharedGameObject<NumSprite>(L"NumSprite");
		auto time = numSpritePtr->GetScore();
		time -= elapsedTime;
		numSpritePtr->SetScore(time);

		//�J�����̃X�s�[�h���v���C���[�ƍ��킹��
		auto playerPtr = GetSharedGameObject<Player>(L"Player");
		m_PtrCamera->SetRotSpeed(playerPtr->GetSpeed());

		//�V�[���J��
		if (numSpritePtr->GetScore() <= 0) {
			App::GetApp()->GetXAudio2Manager()->Stop(m_SoundItem);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			numSpritePtr->SetScore(1 + 1);
		}		

		//CreateEnemy();
	}

	void GameStage::ToObjCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCamera�ɕύX
		auto ptrCameraman = GetSharedGameObject<Cameraman>(L"Cameraman");
		auto ptrObjCamera = dynamic_pointer_cast<ObjCamera>(m_ObjCameraView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			//ptrObjCamera->SetTargetObject(ptrPlayer);
			//m_ObjCameraView���g��
			SetView(m_ObjCameraView);
			m_CameraSelect = CameraSelect::objCamera;
		}
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyPlayerCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	//X�{�^���J�����̕ύX
	void GameStage::OnPushX() {
		switch (m_CameraSelect) {
		case CameraSelect::myCamera:
		{
			ToObjCamera();
		}
		break;
		case CameraSelect::objCamera:
		{
			ToMyCamera();
		}
		break;
		}
	}
}
//end basecross