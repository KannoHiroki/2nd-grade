#pragma once
#include "stdafx.h"

namespace basecross {
	class CregitScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateSprite();
	public:
		//�\�z�Ɣj��
		CregitScene() :Stage() {}
		virtual ~CregitScene() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	};
}