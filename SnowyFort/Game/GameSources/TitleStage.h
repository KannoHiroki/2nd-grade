/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_SoundItem;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//���̓n���h���[
		InputHandler<TitleStage> m_InputHandler;
	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//B�{�^��
		void OnPushB();
		void OnPushX(){}
	};
}