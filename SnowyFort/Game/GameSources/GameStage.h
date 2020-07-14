/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	enum class CameraSelect {
		myCamera,
		objCamera,
		CameraMax
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		shared_ptr<MyPlayerCamera> m_PtrCamera;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//ObjCamera用のビュー
		shared_ptr<SingleView> m_ObjCameraView;
		//マルチビュー
		shared_ptr<MultiView> m_MyMultiView;
		//BGM
		shared_ptr<SoundItem> m_SoundItem;
		CameraSelect m_CameraSelect;
		//入力ハンドラー
		InputHandler<GameStage> m_InputHandler;

		//ビューの作成
		void CreateViewLight();
		//背景オブジェクトの作成
		void CreateSkyObj();
		//固定のボックスの作成
		void CreateFixedBox();
		//プレイヤーの作成
		void CreatePlayer();
		//スコアスプライト作成
		void CreateNumSprite();
		//砦の作成
		void CreateFort();
		//カメラマンの作成
		void CreateCameraman();
		//動画用配置
		void CreateMovieStage();
		//木の作成
		void CreateTree();
		//スポーン作成
		void CreateSpawnBlock();
		//BMG
		void PlayBGM();
		//経過時間
		float m_elapsedTime = 0;
		//敵ランダム配置
		void CreateEnemy();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushB(){}
		void OnPushX();
		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		void ToObjCamera();
		void ToMyCamera();
	};
}
//end basecross

