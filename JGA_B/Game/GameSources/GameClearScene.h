#pragma once
#include "stdafx.h"

namespace basecross {
	class GameClearScene : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateSpraite();
	public:
		//\’z‚Æ”jŠü
		GameClearScene() :Stage() {}
		virtual ~GameClearScene() {}

		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}