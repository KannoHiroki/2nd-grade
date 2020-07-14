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

	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//ビューのカメラの設定
		m_MyCameraView= ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrMyCamera = ObjectFactory::Create<MyCamera>();
		ptrMyCamera->SetEye(Vec3(0.0f, 3.0f, 0.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_MyCameraView->SetCamera(ptrMyCamera);
		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect::openingCamera;
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}

	//固定のボックスの作成
	void GameStage::CreateFixedBox() {
		//配列の初期化

		vector< vector<Vec3> > vec = {
			{
				Vec3(100.0f, 1.0f, 100.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.0f)
			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			auto ptr = AddGameObject<FixedBox>(v[0], v[1], v[2]);
			ptr->AddTag(L"Plane");
			SetSharedGameObject(L"Plane", ptr);
		}

		vector<vector<Vec3>> vec2 = {
			{
				Vec3(100.0f, 5.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 2.5f, 50.0f)
			},
			{
				Vec3(100.0f, 5.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 2.5f, -50.0f)
			},
			{
				Vec3(100.0f, 5.0f, 1.0f),
				Vec3(0.0f, XM_PIDIV2, 0.0f),
				Vec3(50.0f, 2.5f, 0.0f)
			},

			{
				Vec3(100.0f, 5.0f, 1.0f),
				Vec3(0.0f, XM_PIDIV2, 0.0f),
				Vec3(-50.0f, 2.5f, 0.0f)
			}
		};

		for (auto v : vec2) {
			AddGameObject<wall>(v[0], v[1], v[2]);
		}
	}

	void GameStage::CreateHPGauge() {
		auto ptr  = AddGameObject<HPGauge>(Vec2(-600.0f + 70.0f, - 337.0f),false);
		ptr->SetDrawLayer(150);
		auto ptr2 = AddGameObject<HPGauge>(Vec2(-600.0f + 70.0f, - 275.0f),true);
		SetSharedGameObject(L"HPGauge", ptr);
		AddGameObject<HPGaugeFace>(Vec2(-590.0f, -335.0f));
		ptr2->SetDrawLayer(149);
		//AddGameObject<Plant>(Vec3(-60.0f, 0.5f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), L"A",Vec3(60.0f,0.0f,60.0f));
	}

	void GameStage::CreateEnemy() {
		auto group = GetSharedObjectGroup(L"Enemy");
		for (int i = 0; i < 10; i++) {
			
			auto ptr = AddGameObject<EnemyObject>(Vec3(-float(i)-20.0f, 5.0f, 0), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 1.2f, 0.5f),L"A");
			group->IntoGroup(ptr);
			GameManager::GetGM()->SetNowEnemyNum(GameManager::GetGM()->GetNowEnemyNum() + 1);
		};
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>();
		//AddGameObject<weapon>(PlayerPtr->GetComponent<Transform>()->GetPosition(), Vec3(0.0f, 0.0f, 0.0f), Vec3(3.0f, 0.65f, 0.65f));
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", PlayerPtr);
		auto boneDraw = PlayerPtr->GetComponent<PNTBoneModelDraw>();

		
		AddGameObject<ArmCollision>(PlayerPtr, L"Left", 12, Vec3(1.5f, -0.2f, 0.0f));
		AddGameObject<ArmCollision>(PlayerPtr, L"Right", 14, Vec3(-1.5f, -0.2f, 0.0f));

	}

	void GameStage::CreateObjectGroups() {
		//エネミーのグループ(ボス含めたすべてのエネミーオブジェクトもこのグループに)
		CreateSharedObjectGroup(L"Enemy");
		//ボスエネミーだけを入れるグループ
		CreateSharedObjectGroup(L"BossEnemy");
		//ザコ敵だけを入れるグループ
		CreateSharedObjectGroup(L"NormalEnemy");
		// 緑地のグループ
		CreateSharedObjectGroup(L"Grass");

		CreateSharedObjectGroup(L"Plants");

		CreateSharedObjectGroup(L"ClearUI");
		CreateSharedObjectGroup(L"GameOverUI");
		CreateSharedObjectGroup(L"DistrictA");
		CreateSharedObjectGroup(L"DistrictB");
		CreateSharedObjectGroup(L"DistrictC");
		CreateSharedObjectGroup(L"DistrictD");
		CreateSharedObjectGroup(L"DistrictE");
	}

	void GameStage::CreateParticle() {
		auto ptr = AddGameObject<MultiSpark>();
		SetSharedGameObject(L"MultiSpark", ptr);
	}
	//カメラターゲット
	void GameStage::CreateCameraTarget() {
		auto ptr = AddGameObject<CameraTarget>();
		SetSharedGameObject(L"CameraTarget", ptr);
	}
	void GameStage::CreateCsvMap() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"TilingPlate");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			Rot.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Rot.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Rot.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);

			auto ptr = AddGameObject<FixedBox>(Scale, Rot, Pos);
			ptr->AddTag(L"Plane");
			SetSharedGameObject(L"Plane", ptr);

		}
	}

	void GameStage::CreateCsvWall() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"FixedBox");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			Quat Qt;
			Qt.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Qt.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Qt.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			Rot = Qt.toRotVec();
			AddGameObject<wall>(Scale, Rot, Pos);
		}

	}

	void GameStage::CreateCsvEnemy() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"EnemyObject");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			Quat Qt;
			Qt.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Qt.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Qt.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			Rot = Qt.toRotVec();
			wstring district = L"A";
			auto ptr = AddGameObject<EnemyObject>(Pos, Rot, Scale, district);
			auto group = GetSharedObjectGroup(L"Enemy");
			group->IntoGroup(ptr);
			GameManager::GetGM()->SetNowEnemyNum(GameManager::GetGM()->GetNowEnemyNum() + 1);
		}
	}

	//UI関連まとめ置き場
	void GameStage::CreateUI() {
		auto erosionUI = AddGameObject<MultiSprite>(true, Vec2(280, 280), Vec3(500, -250, 0), L"EROSION_TX");
		erosionUI->SetDrawLayer(152);
		auto maruUI = AddGameObject<MultiSprite>(true, Vec2(280, 280), Vec3(500, -250, 0), L"UI_MARU_TX");
		maruUI->SetDrawLayer(150);

		//数字スプライト
		auto numberSprite = AddGameObject<ScoreSprite>(3,
			L"NUMBERS_TX",
			true,
			Vec2(170.0f, 160.0f),
			Vec3(490.0f, -250.0f, 0.0f));
		numberSprite->SetDrawLayer(152);
		SetSharedGameObject(L"Number", numberSprite);

		//緑化ui
		auto grass = AddGameObject<ScaleMoveSprite>(true, Vec2(0, 0), Vec2(500, -260), L"CIRCLEGRASS_TX");
		grass->SetDrawLayer(151);

		auto ptrClearGroup = GetSharedObjectGroup(L"ClearUI");
		auto ptrGameOverGroup = GetSharedObjectGroup(L"GameOverUI");

		auto ptrRetry = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(300.0f, -200.0f, 1.0f), L"RETRY_TX", L"Retry");
		auto ptrStageSelect = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(-300.0f, -200.0f, 1.0f), L"STAGESELECT_TX", L"StageSelect");
		auto ptrBlackSprite = AddGameObject<BlackSprite>(true, Vec2(2000.0f, 2000.0f), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX", L"BlackSprite");
		auto ptrGameOver = AddGameObject<ClearSprite>(true, Vec2(350.8f * 4.0f, 248.0f * 4.0f), Vec3(0.0f, 100.0f, 0.0f), L"GAMEOVER_TX", L"GameOver");
		auto ptrGameClear = AddGameObject<ClearSprite>(true, Vec2(350.8f * 4.0f, 248.0f * 4.0f), Vec3(0.0f, 100.0f, 0.0f), L"CLEAR_TX", L"Clear");
		auto ptrCRetry = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(300.0f, -200.0f, 1.0f), L"RETRY_TX", L"Retry");
		auto ptrCStageSelect = AddGameObject<RetrySprite>(true, Vec2(350.8f * 2.0f, 248.0f * 2.0f), Vec3(-300.0f, -200.0f, 1.0f), L"STAGESELECT_TX", L"StageSelect");
		auto ptrCBlackSprite = AddGameObject<BlackSprite>(true, Vec2(2000.0f, 2000.0f), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX", L"BlackSprite");

		ptrGameOverGroup->IntoGroup(ptrRetry);
		ptrGameOverGroup->IntoGroup(ptrStageSelect);
		ptrGameOverGroup->IntoGroup(ptrBlackSprite);
		ptrGameOverGroup->IntoGroup(ptrGameOver);

		ptrClearGroup->IntoGroup(ptrCRetry);
		ptrClearGroup->IntoGroup(ptrCStageSelect);
		ptrClearGroup->IntoGroup(ptrCBlackSprite);
		ptrClearGroup->IntoGroup(ptrGameClear);

		auto GOGroupVec = ptrGameOverGroup->GetGroupVector();
		for (auto v : GOGroupVec) {
			auto ptr = v.lock();
			ptr->SetDrawActive(false);
			ptr->SetUpdateActive(false);
		}
		auto GCGroupVec = ptrClearGroup->GetGroupVector();
		for (auto v : GCGroupVec) {
			auto ptr = v.lock();
			ptr->SetDrawActive(false);
			ptr->SetUpdateActive(false);
		}
	}

	void GameStage::CreateTower() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"Plant");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			Vec3 Rot;
			Quat Qt;
			Qt.x = (Tokens[4] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[4].c_str());
			Qt.y = (Tokens[5] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[5].c_str());
			Qt.z = (Tokens[6] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(Tokens[6].c_str());
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			Rot = Qt.toRotVec();
			AddGameObject<FixedBox>(Scale, Rot, Pos);

		}
	}
	void GameStage::CreateCsvPlant() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		CsvFile GameStageCsv2;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv2.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		GameStageCsv2.ReadCsv();
		vector<wstring> LineVec;
		vector<wstring> LineVec2;
		GameStageCsv.GetSelect(LineVec, 0, L"Plant");
		GameStageCsv2.GetSelect(LineVec2, 0, L"GreenCircleMaxSize");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Scale(1.0f, 1.0f, 1.0f);
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			wstring district = Tokens[10].c_str();

			for (auto &v2 : LineVec2) {
				vector<wstring> Tokens2;
				Util::WStrToTokenVector(Tokens2, v2, L',');
				if (Tokens2[10].c_str() == district) {
					Vec3 MaxScale(
						(float)_wtof(Tokens2[1].c_str()),
						(float)_wtof(Tokens2[2].c_str()),
						(float)_wtof(Tokens2[3].c_str())
					);
					MaxScale.y = 0.5f;
					auto ptr = AddGameObject<Plant>(Pos, Scale, district, MaxScale);
					GetSharedObjectGroup(L"Plants")->IntoGroup(ptr);
					Pos.y += 2.0f;
					auto ptrPlate = AddGameObject<BillboardPlate>(Pos, L"CALLOUT_TX",district);
				}

			}
		}
	}

	void GameStage::CreateCsvSpawnBlock() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"SpawnBlock");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			wstring districtName = Tokens[10].c_str();
			auto ptr = AddGameObject<SpawnBlock>(Pos, districtName);

			auto ptrGroup = GetSharedObjectGroup(L"District" + districtName);
			ptrGroup->IntoGroup(ptr);

			AddGameObject<Hang>(Pos);
		}
	}
	void GameStage::CreateCsvFence() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"Fence");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			wstring districtName = Tokens[10].c_str();
			auto ptr = AddGameObject<Fence>(Pos,Vec3(0.0f,-XM_PIDIV2,0.0f), districtName);
			SetSharedGameObject(L"Fence"+districtName, ptr);
		}
	}

	void GameStage::CreateCsvTargetObject() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"TargetStart");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			auto ptr = AddGameObject<CameraTargetObject>(Pos);
			SetSharedGameObject(L"TargetObject", ptr);
			ptr->ToStartEnter();
		}
	}

	//各エリアの判定を取るボックス
	void GameStage::CreateEreaBox() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		CsvFile GameStageCsv;
		GameStageCsv.SetFileName(DataDir + m_csvName);
		GameStageCsv.ReadCsv();
		vector<wstring> LineVec;
		GameStageCsv.GetSelect(LineVec, 0, L"AreaChecker");
		for (auto &v : LineVec)
		{
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, v, L',');
			Vec3 Pos(
				(float)_wtof(Tokens[7].c_str()),
				(float)_wtof(Tokens[8].c_str()),
				(float)_wtof(Tokens[9].c_str())
			);
			Vec3 Scale(
				(float)_wtof(Tokens[1].c_str()),
				(float)_wtof(Tokens[2].c_str()),
				(float)_wtof(Tokens[3].c_str())
			);
			wstring districtName = Tokens[10].c_str();
			auto ptr = AddGameObject<EreaBox>(Pos,Scale, Vec3(0.0f, 0.0f, 0.0f), districtName);
			ptr->SetDrawActive(false);
		}

	}
	void GameStage::CreateFadeIn() {
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto FISprite = AddGameObject<FadeInSprite>(bool(true), Vec2(size.x, size.y), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX");
		FISprite->SetDrawLayer(1000);
	}

	void GameStage::CreateCrearSE() {
		bool CrearSEflg = false;

		if (CrearSEflg == true) {
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"Clear", 0, 4.0f);
		}
	}
	
	void GameStage::CreateFadeOut() {

		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto FOSpraite = AddGameObject<FadeOutSprite>(bool(true), Vec2(size.x, size.y), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX");
		FOSpraite->SetDrawLayer(199);
	}

	void GameStage::CreateNextStage() {
		if (GameManager::GetGM()->GetFadeFlg() == true) {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int StageNum = PtrScene->GetStageNum();

			PostEvent(0.0f, GetThis<ObjectInterface>(), PtrScene, L"ToGameOver");
		}
	}

	void GameStage::OnCreate() {
		m_csvName = L"GameStageTest.csv";
		try {
			m_EfkInterface = ObjectFactory::Create<EfkInterface>();
			//グループを作成
			CreateObjectGroups();
			//ビューとライトの作成
			CreateViewLight();
			//固定のボックスの作成
			//CreateFixedBox();
			CreateCsvWall();
			CreateCsvMap();
			//プレーヤーの作成
			CreatePlayer();
			CreateCameraTarget();
			CreateParticle();
			CreateHPGauge();
			//CreateEnemy();
			//CreateCsvEnemy();
			CreateUI();
			CreateCsvPlant();
			CreateCsvSpawnBlock();
			AddGameObject<SkyBox>();
			CreateCsvFence();
			CreateCsvTargetObject();
			CreateEreaBox();
			//エフェクトの作成
			CreateFadeIn();
		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {

		m_EfkInterface->OnUpdate();

		//シーンの取得
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		auto PtrPlayer = GetSharedGameObject<Player>(L"Player");
		//プレイヤーの体力が0になったらゲームオーバーシーンへ
		int PlayerHP = PtrPlayer->GetHP();
		if (PlayerHP == 0) {
			CreateFadeOut();
			//CreateNextStage();
			//auto targetObj = GetSharedGameObject<CameraTargetObject>(L"TargetObject");
			//targetObj->GameOverMove();
			auto GOGroupVec = GetSharedObjectGroup(L"GameOverUI")->GetGroupVector();
			for (auto v : GOGroupVec) {
				v.lock()->SetDrawActive(true);
				v.lock()->SetUpdateActive(true);
			}
			auto gm = GameManager::GetGM();
			gm->SetIsCameraActive(false);
			gm->SetIsCameraActive(false);
			return;
		}

		//すべてのプラントのフラグがTrueだったらクリアシーンへ
		//auto ptrGroup = GetSharedObjectGroup(L"Plants");
		//if (ptrGroup) {
		//	vector<bool> isMax;
		//	auto groupVec = ptrGroup->GetGroupVector();
		//	for (auto v : groupVec) {
		//		auto ptrPlant = dynamic_pointer_cast<Plant>(v.lock());
		//		isMax.push_back(ptrPlant->GetIsMaxCircleScale());
		//	}

		//	for (int i = 0; i < int(isMax.size());i++) {
		//		if (isMax[i] == false) {
		//			return;
		//		}
		//		else {
		//			auto GOGroupVec = GetSharedObjectGroup(L"ClearUI")->GetGroupVector();
		//			for (auto v : GOGroupVec) {
		//				v.lock()->SetDrawActive(true);
		//				v.lock()->SetUpdateActive(true);
		//			}
		//			return;
		//		}
		//	}
		//}
	}

	void GameStage::OnDraw(){
		auto& camera = GetView()->GetTargetCamera();
		m_EfkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_EfkInterface->OnDraw();
	}
	void GameStage::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<CameraTarget>(L"CameraTarget");
		//MyCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraViewを使う
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect::myCamera;
		}
	}

	void GameStage::ToOpeningCamera()   {
		auto ptrPlayer = GetSharedGameObject<CameraTarget>(L"CameraTarget");
		//OpeningCameraに変更
		auto ptrMyCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrMyCamera) {
			//m_MyCameraViewを使う
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect::openingCamera;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"Sak", 0, 3.0f);
		}
	}
}
//end basecross
