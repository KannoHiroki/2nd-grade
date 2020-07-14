/*!
@file ResultStage.h
@brief ���U���g�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//���̓n���h���[
		InputHandler<ResultStage> m_InputHandler;
	public:
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//B�{�^��
		void OnPushB();
		void OnPushX() {}
	};
}