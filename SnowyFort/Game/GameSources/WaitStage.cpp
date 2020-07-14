/*!
@file WaitStage.cpp
@brief リソース読み込み用ステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ウエイトステージクラス
	//--------------------------------------------------------------------------------------

	bool WaitStage::m_Loaded = false;
	std::mutex WaitStage::mtx;

	void WaitStage::LoadResourceFunc() {
		//二回目は読み込まない
		if (!m_Loaded) {
			mtx.lock();
			m_Loaded = false;
			mtx.unlock();

			// GameStage用リソース読み込み
			wstring dataDir;
			App::GetApp()->GetAssetsDirectory(dataDir);
			wstring strTexture = dataDir + L"trace.png";
			App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
			strTexture = dataDir + L"sky.jpg";
			App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
			strTexture = dataDir + L"wall.jpg";
			App::GetApp()->RegisterTexture(L"Wall_Tx", strTexture);
			strTexture = dataDir + L"trace.png";
			App::GetApp()->RegisterTexture(L"Enemy_Tx", strTexture);
			strTexture = dataDir + L"number.png";
			App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
			strTexture = dataDir + L"Tx_SnowMountain.png";
			App::GetApp()->RegisterTexture(L"Mountain_TX", strTexture);
			strTexture = dataDir + L"Tx_Yukidama-.png";
			App::GetApp()->RegisterTexture(L"Yukidama_TX", strTexture);
			strTexture = dataDir + L"Tx_Fort02.png";
			App::GetApp()->RegisterTexture(L"Fort_TX", strTexture);
			strTexture = dataDir + L"Tx_Yumi_Enemy.png";
			App::GetApp()->RegisterTexture(L"ENEMY_TX", strTexture);
			strTexture = dataDir + L"Chest.png";
			App::GetApp()->RegisterTexture(L"CHEST_TX", strTexture);

			//スタティックモデルのリソース
			auto staticModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Obj_SnowMountain.bmf");
			App::GetApp()->RegisterResource(L"MODEL_MESH", staticModelMesh);
			staticModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Obj_Fort.bmf");
			App::GetApp()->RegisterResource(L"MODEL_FORT_MESH", staticModelMesh);
			staticModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Obj_Tree.bmf");
			App::GetApp()->RegisterResource(L"MODEL_TREE_MESH", staticModelMesh);
			staticModelMesh = MeshResource::CreateStaticModelMesh(dataDir, L"Obj_Hole.bmf");
			App::GetApp()->RegisterResource(L"MODEL_SPAWNBLOCK_MESH", staticModelMesh);

			//ボーンモデルのリソース
			auto boneModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Player_Walk.bmf");
			App::GetApp()->RegisterResource(L"BoneModel_Player", boneModelMesh);
			boneModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Enemy_Walk.bmf");
			App::GetApp()->RegisterResource(L"ENEMY_MESH", boneModelMesh);
			boneModelMesh = MeshResource::CreateBoneModelMesh(dataDir, L"Enemy02_Walk.bmf");
			App::GetApp()->RegisterResource(L"BIG_ENEMY_MESH", boneModelMesh);

			//BGM
			wstring strSound;
			App::GetApp()->GetAssetsDirectory(dataDir);
			strSound = dataDir + L"Sound\\" + L"Title_BGM.wav";
			App::GetApp()->RegisterWav(L"TITLE_BGM", strSound);

			//SE
			auto strSE = dataDir + L"SE\\" + L"SE_Enemy_Kill.wav";
			App::GetApp()->RegisterWav(L"ENEMY_KILL_SE", strSE);

			mtx.lock();
			m_Loaded = true;
			mtx.unlock();
		}
	}

	void WaitStage::CreateViewLight() {
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

	void WaitStage::CreateTitleSprite() {
		wstring dataDir;
		App::GetApp()->GetAssetsDirectory(dataDir);
		wstring strTexture = dataDir + L"wait.png";
		App::GetApp()->RegisterTexture(L"WAIT_TX", strTexture);
		AddGameObject<AnimeSprite>(L"WAIT_TX", true, Vec2(256.0f, 64.0f), Vec2(400.0f, -350.0f));
	}

	void WaitStage::OnCreate() {
		//他のリソースを読み込むスレッドのスタート
		std::thread LoadThread(LoadResourceFunc);
		//終了までは待たない
		LoadThread.detach();

		CreateViewLight();
		CreateTitleSprite();
	}

	void WaitStage::OnUpdate() {
		if (m_Loaded) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}
}