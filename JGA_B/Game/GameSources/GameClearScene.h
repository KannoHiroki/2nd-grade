#pragma once
#include "stdafx.h"

namespace basecross {
	class GameClearScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateSpraite();
	public:
		//�\�z�Ɣj��
		GameClearScene() :Stage() {}
		virtual ~GameClearScene() {}

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}