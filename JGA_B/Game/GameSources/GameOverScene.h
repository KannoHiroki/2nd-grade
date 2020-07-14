#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverScene : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateUI();
		void CreateSprite();
		void CreateFadeIn();
	public:
		//\’z‚Æ”jŠü
		GameOverScene() :Stage() {}
		virtual ~GameOverScene() {}

		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}