/*!
@file WaitStage.h
@brief ���\�[�X�ǂݍ��ݗp�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���\�[�X�ǂݍ��݃X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class WaitStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
		static void LoadResourceFunc();
		//���\�[�X��ǂݍ��񂾂��Ƃ�m�点��t���O�i�X�^�e�B�b�N�ϐ��j
		static bool m_Loaded;
		//�~���[�e�b�N�X
		static std::mutex mtx;
	public:
		WaitStage() :Stage() {}
		virtual ~WaitStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}