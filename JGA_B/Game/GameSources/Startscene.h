#pragma once
#include "stdafx.h"

namespace basecross {
	class StartScene : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		void CreateSprite();
	public:
		//\’z‚Æ”jŠü
		StartScene() :Stage() {}
		virtual ~StartScene() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	//	void SetRect(const Rect2D<float>& rect) {
	//	auto drawComp = GetComponent<PCT>
	};
}