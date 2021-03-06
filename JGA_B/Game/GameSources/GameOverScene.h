#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateUI();
		void CreateSprite();
		void CreateFadeIn();
	public:
		//構築と破棄
		GameOverScene() :Stage() {}
		virtual ~GameOverScene() {}

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}