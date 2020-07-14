/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//スプライトの作成
	void TitleStage::CreateTitleSprite() {
		//テクスチャ読み込み
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strTexture = dataDir + L"title.png";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = dataDir + L"Tx_BackGround.png";
		App::GetApp()->RegisterTexture(L"BACKGROUND_TX", strTexture);
		strTexture = dataDir + L"Press B.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = dataDir + L"Tx_Title_Snow.png";
		App::GetApp()->RegisterTexture(L"SNOW_TX", strTexture);

		//オブジェクト生成
		AddGameObject<TitleSprite>(L"BACKGROUND_TX", false, Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
		AddGameObject<TitleSprite>(L"TITLE_TX", true,
			Vec2(256.0f, 128.0f) * 3.5, Vec2(0.0f, 120.0f));
		AddGameObject<AnimeSprite>(L"MESSAGE_TX", true, Vec2(518.0f, 256.0f), Vec2(0.0f, -300.0f));

		AddGameObject<MoveSprite>(L"SNOW_TX", true, Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));		
	}

	//初期化
	void TitleStage::OnCreate() {
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
	}

	//更新
	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	void TitleStage::OnPushB() {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToWaitStage");
	}

}