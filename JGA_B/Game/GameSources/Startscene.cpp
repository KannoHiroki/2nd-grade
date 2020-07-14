#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartScene ::CreateViewLight() {
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

	void StartScene::CreateSprite(){

		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		Vec2 HalfSize;
		HalfSize.x = size.x / 2.0f;
		HalfSize.y = size.y / 2.0f;

		auto Txsprite = AddGameObject<StartSprite>(Vec3(100.0f, 100.0f, 1.0f), Vec3(size.x, size.y, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"STARTSCENE_TX");
		Txsprite->SetPostion(HalfSize.x, HalfSize.y);
		Txsprite->SetDrawLayer(0);
		auto PABsprite = AddGameObject<PressAnyButtonSprite>(Vec3(0.0f, -230.0f, 1.0f), Vec3(300.0f, 100.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), L"PRESSANYBUTTON_TX");
		PABsprite->SetDrawLayer(1);
	}

	void StartScene::OnCreate() {
		CreateViewLight();
		CreateSprite();
	}
	void StartScene::OnUpdate() {
		//デバッグ キーボード用
		auto keyVec = App::GetApp()->GetInputDevice().GetKeyState();
		if (keyVec.m_bPushKeyTbl['X']) {
			PostEvent(1.5f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClear");
		}
		if (keyVec.m_bPushKeyTbl['Z']) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
		}

	}

	void StartScene::SceneChange() {

		//シーンの取得
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		PostEvent(0.0f, GetThis<ObjectInterface>(), PtrScene, L"ToSelectStage");

	}
}