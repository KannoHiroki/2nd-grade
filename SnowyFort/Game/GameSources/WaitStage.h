/*!
@file WaitStage.h
@brief リソース読み込み用ステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リソース読み込みステージクラス
	//--------------------------------------------------------------------------------------
	class WaitStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//リソースロード用のスレッド（スタティック関数）
		static void LoadResourceFunc();
		//リソースを読み込んだことを知らせるフラグ（スタティック変数）
		static bool m_Loaded;
		//ミューテックス
		static std::mutex mtx;
	public:
		WaitStage() :Stage() {}
		virtual ~WaitStage() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}