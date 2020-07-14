/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		//MyCameraView用のビュー
		const Vec3 at(0.0f, 0.0f, 0.0f);
		//ビューのカメラの設定
		m_PtrCamera = ObjectFactory::Create<MyPlayerCamera>();
		//カメラの設定
		m_PtrCamera->SetArmParam(
			15.0f,		//カメラから注視点までの距離（float& armLength）
			3.0f		//ターゲットオブジェクト（プレイヤー）のy座標からカメラまでの高さ（float& armHeight）
		);
		m_PtrCamera->SetAt(at);

		//ObjCameraView用のビュー
		auto ptrObjCamera = ObjectFactory::Create<ObjCamera>();
		ptrObjCamera->SetEye(Vec3(0.0f, 12.0f, 0.1f));
		ptrObjCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_CameraSelect = CameraSelect::myCamera;

		//メインカメラの位置とサイズ
		Viewport viewport{
			0,			//float TopLeftX;
			0,			//float TopLeftY;
			1280,		//float Width;
			800,		//float Height;
			0,			//float MinDepth;
			1.0f,		//float MaxDepth;
		};

		//ミニマップの位置とサイズ
		Viewport miniMap{
			1280/3*2,	//float TopLeftX;
			0,			//float TopLeftY;
			1280/3,		//float Width;
			800/3,		//float Height;
			0,			//float MinDepth;
			1.0f,		//float MaxDepth;
		};

		m_MyMultiView = ObjectFactory::Create<MultiView>(GetThis<Stage>());
		m_MyMultiView->SetTargetIndex(m_MyMultiView->AddView(viewport,m_PtrCamera));
		m_MyMultiView->SetTargetIndex(m_MyMultiView->AddView(miniMap,ptrObjCamera));
		m_MyMultiView->SetViewport(0, viewport);
		m_MyMultiView->SetViewport(1, miniMap);
		m_MyMultiView->SetCamera(0, m_PtrCamera);
		m_MyMultiView->SetCamera(1, ptrObjCamera);

		SetView(m_MyMultiView);

		m_MyMultiView->ChangeNextView();

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();

		CreateSharedObjectGroup(L"Enemy");
	}

	void GameStage::CreateSkyObj() {
		AddGameObject<FixedBox>(Vec3(-30.0f,-30.0f,-30.0f), Vec3(0.0f,0.0f,0.0f), Vec3(0.0f,0.0f,0.0f));
	}

	//山のボックスの作成
	void GameStage::CreateFixedBox() {
		//雪山
		//AddGameObject<Mountain>(Vec3(1.1f, 1.f, 1.1f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0, -2.8f, 0.0f));
		//AddGameObject<Mountain>();
		float slopeAngle = XMConvertToRadians(-18.9f); // 斜面の角度
		float slopeLength = 3.8f;
		float slopePositionY = -1.8f;
		float angle = 360.0f / 8.0f;
		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();
		//山頂
		Quat moveQt;

		//AddGameObject< FixedPsBox>(Vec3(2.3f,0.5f,2.3f), Quat(0,0,0,0), Vec3(playerPtr->GetDefPos().x,playerPtr->GetDefPos().y + -0.55f,playerPtr->GetDefPos().z));

	/*	for (int i = 0; i < (int)360.0f / angle; i++) {
			//プレイヤーの足場作成(山頂)
			rad = XMConvertToRadians(angle * i);
			Vec3 scaffoldingPos = Vec3(
				playerPtr->GetDefPos().x + (playerPtr->GetPlayerMoveCircleHalf() * 0.9f) * cosf(rad),
				playerPtr->GetDefPos().y + -0.5f,
				playerPtr->GetDefPos().z + (playerPtr->GetPlayerMoveCircleHalf() * 0.9f) * sinf(rad)
			);
			moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));

			AddGameObject<FixedPsBox>(
				Vec3(0.3f, 0.5f, 1.1f),
				moveQt,
				Vec3(scaffoldingPos)
			);
		}*/

		AddGameObject<FixedPsSphere>(Vec3(20.0f), Vec3(0.0f), Vec3(0.0f, -10.2f, 0.0f));
	
		/*Vec3 scaffoldingPos;
		angle = 360.0f / 12.0f; // 麓の分割数
		//山の麓(ふもと)
		for (int i = 0; i < (int)360.0f / angle; i++) {
			//プレイヤーの足場作成(山頂)
			rad = XMConvertToRadians(angle * i + angle / 2); // 30度ずつずらして配置 + 15度ずらして調整
			moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
			scaffoldingPos = Vec3(
				playerPtr->GetDefPos().x + (playerPtr->GetPlayerMoveCircleHalf() * 6.f) * cosf(rad),
				playerPtr->GetDefPos().y + -3.1f,
				playerPtr->GetDefPos().z + (playerPtr->GetPlayerMoveCircleHalf() * 6.f) * sinf(rad)
			);
			AddGameObject<FixedPsBox>(
				Vec3(1.f, 0.5f, 4.5f),
				moveQt,
				Vec3(scaffoldingPos)
			);
			//配置する列
			for (int j = 0; j < 8; j++) {
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, slopeAngle));
				scaffoldingPos.normalize(); // 大きさを1にする
				float slopeScale = 1.1f + (j* 0.5f);
				Vec3 slopePos = Vec3(scaffoldingPos.x, scaffoldingPos.y, scaffoldingPos.z) * (j + 2.0f);
				AddGameObject<FixedPsBox>(
					Vec3(1.f, 0.5f, slopeScale),
					moveQt,
					Vec3(slopePos)
				);

				//if (j >= 4) {
				//	for (int i = 0; i < 1; i++) {
				//		auto ptrEnemy = AddGameObject<EnemyObject>(Vec3(slopePos.x, slopePos.y + 1.0f, slopePos.z));				
				//		auto group = GetSharedObjectGroup(L"Enemy");
				//		group->IntoGroup(ptrEnemy);
				//	}
				//}
			}
		}
		*/

		AddGameObject<Plane>();
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"Player", ptrPlayer);
	}

	//スコアスプライト作成
	void GameStage::CreateNumSprite() {
		AddGameObject<NumSprite>(2,
			L"NUMBER_TX",
			true,
			Vec2(128.0f, 80.0f),
			Vec3(-350.0f, 350.0f, 0.0f),
			99.0f + 1.0f); // 制限時間
	}

	//砦の作成
	void GameStage::CreateFort() {
		auto ptr = AddGameObject<Fort>(Vec3(1.0f,1.0f,1.0f), Vec3(0.0f,0.0f,0.0f), Vec3(0.0f,-0.3f,0.0f));
		SetSharedGameObject(L"Fort", ptr);
	}

	//動画用配置
	void GameStage::CreateMovieStage() {
		AddGameObject<BigEnemyObject>(Vec3(4.0f, 0, 4.0f));
		AddGameObject<EnemyObject>(Vec3(3.0f - 0.1f, 0, 4.3f - 0.1f));
		AddGameObject<EnemyObject>(Vec3(3.6f, 0, 4.5f));
		AddGameObject<EnemyObject>(Vec3(3.8f, 0, 4.2f));
		AddGameObject<EnemyObject>(Vec3(3.5f, 0, 4.8f));
	}

	//木の作成
	void GameStage::CreateTree() {
		//ランダム関数用
		srand((unsigned int)time(NULL));

		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();
		Quat moveQt;

		Vec3 treePos;
		auto angle = 360.0f / 30.0f; // 麓の分割数
		//山の麓(ふもと)
		for (float i = 6.0f; i < 10.0f; i++) {
			for (int j = 0; j < (int)360.0f / angle; j++) {
				//プレイヤーの足場作成(山頂) 
				rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * j); // 30度ずつずらして配置 + 15度ずらして調整
				float randLength = (playerPtr->GetPlayerMoveCircleHalf() * i) + (float)((rand() % 20 + 1) / 10); //0.0f～2.0fまでのランダムな値分ずらす
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
				treePos = Vec3(
					playerPtr->GetDefPos().x + randLength * cosf(rad),
					playerPtr->GetDefPos().y + -3.1f,
					playerPtr->GetDefPos().z + randLength * sinf(rad)
				);

				AddGameObject<Tree>(treePos, Vec3(0));
			}
		}
	}

	//スポーン作成
	void GameStage::CreateSpawnBlock() {
		auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
		auto rad = playerPtr->GetRad();

		Vec3 spawnPos;
		auto angle = 360.0f / 3.0f; // 分割数
		for (int i = 0; i < (int)360.0f / angle; i++) {
			rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * i);
			float randLength = 7.0f;
			spawnPos = Vec3(
				playerPtr->GetDefPos().x + randLength * cosf(rad),
				playerPtr->GetDefPos().y + -2.5f,
				playerPtr->GetDefPos().z + randLength * sinf(rad)
			);

			AddGameObject<SpawnBlock>(spawnPos);
		}
	}

	//カメラマンの作成
	void GameStage::CreateCameraman() {
		auto ptrCameraman = AddGameObject<Cameraman>(2.0f);
		//シェア配列にCameramanを追加
		SetSharedGameObject(L"Cameraman", ptrCameraman);
	}

	//敵ランダム配置
	void GameStage::CreateEnemy() {
		m_elapsedTime += App::GetApp()->GetElapsedTime();

		if (m_elapsedTime > 7.0f) {
			m_elapsedTime = 0;

			auto playerPtr = GetSharedGameObject<Player>(L"PlayerObj");
			auto rad = playerPtr->GetRad();
			Quat moveQt;

			Vec3 enemyPos;
			auto angle = 360.0f / 10.0f; // 分割数
			for (int i = 0; i < (int)360.0f / angle; i++) {
				rad = XMConvertToRadians((angle + (float)((rand() % 20 + 1) / 10)) * i);
				float length = 7.0f;
				moveQt.rotationRollPitchYawFromVector(Vec3(0.0f, -rad, 0.0f));
				enemyPos = Vec3(
					playerPtr->GetDefPos().x + length * cosf(rad),
					playerPtr->GetDefPos().y - 2.5f,
					playerPtr->GetDefPos().z + length * sinf(rad)
				);
				
				AddGameObject<EnemyObject>(enemyPos);
			}
		}
	}

	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			//スカイボックス
			CreateSkyObj();
			//砦の作成
			CreateFort();
			//プレーヤーの作成
			CreatePlayer();
			//固定のボックスの作成
			CreateFixedBox();
			//UIスプライトの作成
			CreateNumSprite();
			////カメラマンの作成
			//CreateCameraman();
			CreateMovieStage();

			//CreateEnemy();

			CreateSpawnBlock();
			CreateTree();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<GameStage>());
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto numSpritePtr = GetSharedGameObject<NumSprite>(L"NumSprite");
		auto time = numSpritePtr->GetScore();
		time -= elapsedTime;
		numSpritePtr->SetScore(time);

		//カメラのスピードをプレイヤーと合わせる
		auto playerPtr = GetSharedGameObject<Player>(L"Player");
		m_PtrCamera->SetRotSpeed(playerPtr->GetSpeed());

		//シーン遷移
		if (numSpritePtr->GetScore() <= 0) {
			App::GetApp()->GetXAudio2Manager()->Stop(m_SoundItem);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
			numSpritePtr->SetScore(1 + 1);
		}		

		//CreateEnemy();
	}

	void GameStage::ToObjCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//ObjCameraに変更
		auto ptrCameraman = GetSharedGameObject<Cameraman>(L"Cameraman");
		auto ptrObjCamera = dynamic_pointer_cast<ObjCamera>(m_ObjCameraView->GetCamera());
		if (ptrObjCamera) {
			ptrObjCamera->SetCameraObject(ptrCameraman);
			//ptrObjCamera->SetTargetObject(ptrPlayer);
			//m_ObjCameraViewを使う
			SetView(m_ObjCameraView);
			m_CameraSelect = CameraSelect::objCamera;
		}
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(L"Player");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyPlayerCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	//Xボタンカメラの変更
	void GameStage::OnPushX() {
		switch (m_CameraSelect) {
		case CameraSelect::myCamera:
		{
			ToObjCamera();
		}
		break;
		case CameraSelect::objCamera:
		{
			ToMyCamera();
		}
		break;
		}
	}
}
//end basecross