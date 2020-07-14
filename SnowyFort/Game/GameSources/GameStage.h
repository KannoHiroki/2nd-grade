/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class CameraSelect {
		myCamera,
		objCamera,
		CameraMax
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<MyPlayerCamera> m_PtrCamera;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera�p�̃r���[
		shared_ptr<SingleView> m_ObjCameraView;
		//�}���`�r���[
		shared_ptr<MultiView> m_MyMultiView;
		//BGM
		shared_ptr<SoundItem> m_SoundItem;
		CameraSelect m_CameraSelect;
		//���̓n���h���[
		InputHandler<GameStage> m_InputHandler;

		//�r���[�̍쐬
		void CreateViewLight();
		//�w�i�I�u�W�F�N�g�̍쐬
		void CreateSkyObj();
		//�Œ�̃{�b�N�X�̍쐬
		void CreateFixedBox();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�X�R�A�X�v���C�g�쐬
		void CreateNumSprite();
		//�Ԃ̍쐬
		void CreateFort();
		//�J�����}���̍쐬
		void CreateCameraman();
		//����p�z�u
		void CreateMovieStage();
		//�؂̍쐬
		void CreateTree();
		//�X�|�[���쐬
		void CreateSpawnBlock();
		//BMG
		void PlayBGM();
		//�o�ߎ���
		float m_elapsedTime = 0;
		//�G�����_���z�u
		void CreateEnemy();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushB(){}
		void OnPushX();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		void ToObjCamera();
		void ToMyCamera();
	};
}
//end basecross

