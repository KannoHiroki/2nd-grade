/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera
	};
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//�Z���N�g����Ă���J�����̎��
		CameraSelect m_CameraSelect;
		wstring m_csvName;
		//�G�t�F�N�g�̃C���^�[�t�F�C�X
		shared_ptr<EfkInterface> m_EfkInterface;
		//�r���[�̍쐬
		void CreateViewLight();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�v���C���[�̍쐬
		void CreatePlayer();
		void CreateHPGauge();

		void CreateEnemy();

		void CreateObjectGroups();

		void CreateParticle();
		void CreateCameraTarget();
		void CreateCsvMap();
		void CreateCsvWall();
		void CreateCsvEnemy();
		void CreateCsvPlant();
		void CreateCsvSpawnBlock();
		void CreateCsvTargetObject();
		void CreateUI();
		void CreateTower();
		void CreateEreaBox();

		void CreateFadeIn();
		void CreateCrearSE();
		void CreateFadeOut();
		void CreateNextStage();
		public:
		void CreateCsvFence();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�G�t�F�N�g�̃C���^�[�t�F�C�X�̎擾
		shared_ptr<EfkInterface>GetEfkInterface() const {
			return m_EfkInterface;
		}
		//�`��
		virtual void OnDraw() override;
		CameraSelect GetNowSelectCamera() {
			return m_CameraSelect;
		}
		void SetNowSelectCamera(CameraSelect camera) {
			m_CameraSelect = camera;
		}
		shared_ptr<SingleView> GetMyCameraView() {
			return m_MyCameraView;
		}
		shared_ptr<SingleView> GetOpeningCameraView() {
			return m_OpeningCameraView;
		}

		void GameStage::ToMyCamera();
		void GameStage::ToOpeningCamera();
	};


}
//end basecross

