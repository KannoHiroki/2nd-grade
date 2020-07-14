#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateUI();
		void CreateSprite();
		void CreateFadeIn();
	public:
		//�\�z�Ɣj��
		GameOverScene() :Stage() {}
		virtual ~GameOverScene() {}

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}