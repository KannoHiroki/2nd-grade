#pragma once
#include "stdafx.h"

namespace basecross {
	class StartScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		void CreateSprite();
	public:
		//�\�z�Ɣj��
		StartScene() :Stage() {}
		virtual ~StartScene() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	//	void SetRect(const Rect2D<float>& rect) {
	//	auto drawComp = GetComponent<PCT>
	};
}