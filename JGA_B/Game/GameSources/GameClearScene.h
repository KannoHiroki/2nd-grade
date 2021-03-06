#pragma once
#include "stdafx.h"

namespace basecross {
	class GameClearScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		bool m_CntrolLock;
		void CreateSpraite();
	public:
		//構築と破棄
		GameClearScene() :Stage() {}
		virtual ~GameClearScene() {}

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}