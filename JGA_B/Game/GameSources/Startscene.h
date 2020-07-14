#pragma once
#include "stdafx.h"

namespace basecross {
	class StartScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateSprite();
	public:
		//構築と破棄
		StartScene() :Stage() {}
		virtual ~StartScene() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	//	void SetRect(const Rect2D<float>& rect) {
	//	auto drawComp = GetComponent<PCT>
	};
}