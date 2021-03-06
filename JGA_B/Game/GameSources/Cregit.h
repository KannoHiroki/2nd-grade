#pragma once
#include "stdafx.h"

namespace basecross {
	class CregitScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		void CreateSprite();
	public:
		//構築と破棄
		CregitScene() :Stage() {}
		virtual ~CregitScene() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SceneChange();
	};
}