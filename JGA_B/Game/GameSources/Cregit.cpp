#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CregitScene::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
		//シャドウマップ使用しない
		SetShadowmapDraw(false);
	}

	void CregitScene::CreateSprite() {
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		Vec2 HalfSize;
		HalfSize.x = size.x / 2.0f;
		HalfSize.y = size.y / 2.0f;


		auto cregitSprite = AddGameObject<CregitSprite>(Vec3(100.0f, 100.0f, 1.0f), Vec3(size.x, size.y, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"CREGIT_TX");
		cregitSprite->SetPostion(HalfSize.x, HalfSize.y);
		cregitSprite->SetDrawLayer(0);

	}

	void CregitScene::OnCreate() {
		CreateViewLight();
		CreateSprite();
	}
	void CregitScene::OnUpdate() {
		//auto time = App::GetApp()->GetElapsedTime();
	}

	void CregitScene::SceneChange() {

		////シーンの取得
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		PostEvent(3.0f, GetThis<ObjectInterface>(), PtrScene, L"ToStartStage");

	}
}