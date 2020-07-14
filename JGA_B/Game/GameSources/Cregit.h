#pragma once
#include "stdafx.h"

namespace basecross {
	class CregitScene : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		void CreateSprite();
	public:
		//\’z‚Æ”jŠü
		CregitScene() :Stage() {}
		virtual ~CregitScene() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	};
}