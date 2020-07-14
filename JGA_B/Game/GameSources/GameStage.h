/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera
	};
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//セレクトされているカメラの種類
		CameraSelect m_CameraSelect;
		wstring m_csvName;
		//エフェクトのインターフェイス
		shared_ptr<EfkInterface> m_EfkInterface;
		//ビューの作成
		void CreateViewLight();
		//固定のボックスの作成
		void CreateFixedBox();
		//プレイヤーの作成
		void CreatePlayer();
		void CreateHPGauge();

		void CreateEnemy();

		void CreateObjectGroups();

		void CreateParticle();
		void CreateCameraTarget();
		void CreateCsvMap();
		void CreateCsvWall();
		void CreateCsvEnemy();
		void CreateCsvPlant();
		void CreateCsvSpawnBlock();
		void CreateCsvTargetObject();
		void CreateUI();
		void CreateTower();
		void CreateEreaBox();

		void CreateFadeIn();
		void CreateCrearSE();
		void CreateFadeOut();
		void CreateNextStage();
		public:
		void CreateCsvFence();
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//エフェクトのインターフェイスの取得
		shared_ptr<EfkInterface>GetEfkInterface() const {
			return m_EfkInterface;
		}
		//描画
		virtual void OnDraw() override;
		CameraSelect GetNowSelectCamera() {
			return m_CameraSelect;
		}
		void SetNowSelectCamera(CameraSelect camera) {
			m_CameraSelect = camera;
		}
		shared_ptr<SingleView> GetMyCameraView() {
			return m_MyCameraView;
		}
		shared_ptr<SingleView> GetOpeningCameraView() {
			return m_OpeningCameraView;
		}

		void GameStage::ToMyCamera();
		void GameStage::ToOpeningCamera();
	};


}
//end basecross

