/*!
@file ResultStage.h
@brief リザルトステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//入力ハンドラー
		InputHandler<ResultStage> m_InputHandler;
	public:
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//Bボタン
		void OnPushB();
		void OnPushX() {}
	};
}