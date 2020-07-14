#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageSelect::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 0.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//ptrMyCamera->SetCameraObject()
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}
	void StageSelect::CreateSprite() {
		auto leveltexture = AddGameObject<MultiSprite>(true, Vec2(250, 150), Vec3(0, -200, 0), L"NORMALPLANET_TX");
		SetSharedGameObject(L"LevelSprite", leveltexture);
		auto yazirusi = AddGameObject<LRMoveSprite>(L"YAZIRUSI_TX", true, Vec2(90, 90), Vec2(-400, -10.0f), Vec3(0.0f, 0.0f, XM_PI),true);
		auto yazirusi2 = AddGameObject<LRMoveSprite>(L"YAZIRUSI_TX", true, Vec2(90, 90), Vec2(400, 0.0f), Vec3(0.0f, 0.0f, 0.0f),false);
		auto planetLock = AddGameObject<BillboardPlate1>(Vec3(6.0f, -0.2f, -0.72f),L"LOCK_TX",L"A");
		planetLock = AddGameObject<BillboardPlate1>(Vec3(7.0f, -0.2f, -10.5f), L"LOCK_TX", L"A");
		planetLock = AddGameObject<BillboardPlate1>(Vec3(-2.6f, -0.2f, -18.0f), L"LOCK_TX", L"A");
		planetLock = AddGameObject<BillboardPlate1>(Vec3(-5.7f, -0.2f, -6.7f), L"LOCK_TX", L"A");
		planetLock = AddGameObject<BillboardPlate1>(Vec3(-9.0f, -0.2f, 1.6f), L"LOCK_TX", L"A");

		auto ptrTrans = planetLock->GetComponent<Transform>();
	}

	void StageSelect::CreateFadeIn() {
	
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());

		auto FISprite = AddGameObject<FadeInSprite>(bool(true), Vec2(size.x, size.y), Vec3(0.0f, 0.0f, 0.0f),L"FADE_TX");
		FISprite->SetDrawLayer(3);

	}

	void StageSelect::CreateFadeOut(){
		
		Vec2 size;
		size.x = float(App::GetApp()->GetGameWidth());
		size.y = float(App::GetApp()->GetGameHeight());
		
		auto FOSpraite = AddGameObject<FadeOutSprite>(bool(true), Vec2(size.x, size.y), Vec3(0.0f, 0.0f, 0.0f), L"FADE_TX");
		FOSpraite->SetDrawLayer(3);
		
		
	}
	void StageSelect::CreateNextStage(){
		if (GameManager::GetGM()->GetFadeFlg() == true) {
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int StageNum = PtrScene->GetStageNum();
			
			PostEvent(0.0f, GetThis<ObjectInterface>(), PtrScene, L"ToGameStage");
		}
	}

	void StageSelect::OnCreate() {
		CreateViewLight();
		CreateSprite();
		CreateStageSelectObject();
		CreateCameraTarget();
		AddGameObject<SkyBox>();
		CreateFadeIn();
	}

	void StageSelect::OnUpdate() {
		//シーンの取得
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int StageNum = PtrScene->GetStageNum();
		auto gm = GameManager::GetGM();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		auto ptrCT = GetSharedGameObject<CameraBox>(L"CameraTarget");

		m_frameCount += App::GetApp()->GetElapsedTime();
		if (1.0f < m_frameCount) {
			if (CntlVec[0].bConnected) {
				if (!m_cntrolLock) {
					//右に倒したら	
					if (CntlVec[0].fThumbLX >= 0.8f) {
						int NowStageNum = gm->GetselectedStageNum();
						ptrCT->Move(NowStageNum, L"+");
						m_frameCount = 0.0f;
						//効果音鳴らす
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						ptrXA->Start(L"Select", 0, 0.8f);
					}
					//左に倒したら
					if (CntlVec[0].fThumbLX <= -0.8f) {
						int NowStageNum = gm->GetselectedStageNum();
						ptrCT->Move(NowStageNum, L"-");
						m_frameCount = 0.0f;
						//効果音鳴らす
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						ptrXA->Start(L"Select", 0, 0.8f);
					}
				}
			}
		}
		m_totalTime += App::GetApp()->GetElapsedTime();

		if (CntlVec[0].bConnected) {
			//ゲームステージへ
			//Aボタンを押したらゲーム画面へ
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto gm = GameManager::GetGM();
				if (gm->GetselectedStageNum() == 1) {
					CreateFadeOut();
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"Decision", 0, 0.5f);

					return;
				}
				else {
					if (m_totalTime > 1.0f) {
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						ptrXA->Start(L"NONSTAGE", 0, 0.3f);
						m_totalTime = 0.0f;
					}
					return;
				}
			}
			if (!m_cntrolLock) {
				if (CntlVec[0].fThumbLY >= 0.8f) {
					StageNum--;
					if (StageNum < 1) {
						StageNum = 3;
					}
					m_cntrolLock = true;
					PtrScene->SetStageNum(StageNum);
					ChangeSelect(StageNum);
				}
			}
		}
		CreateNextStage();
	}

	void StageSelect::CreateStageSelectObject() {
		auto ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 3.0f), L"EARTH_TX");
		ptrPlanet->SetSelect(true);
		SetSharedGameObject(L"Planet_1", ptrPlanet);
		m_spVec[0] = ptrPlanet;

		ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(7.0f, 0.0f, 0.0f), L"EARTH2_TX");
		SetSharedGameObject(L"Planet_2", ptrPlanet);
		m_spVec[1] = ptrPlanet;

		ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.0f, 0.0f, -12.0f), L"EARTH3_TX");
		SetSharedGameObject(L"Planet_3", ptrPlanet);
		m_spVec[2] = ptrPlanet;

		ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-3.0f, 0.0f, -20.0f), L"EARTH4_TX");
		SetSharedGameObject(L"Planet_4", ptrPlanet);
		m_spVec[3] = ptrPlanet;

		ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-7.0f, 0.0f, -7.0f), L"EARTH5_TX");
		SetSharedGameObject(L"Planet_5", ptrPlanet);
		m_spVec[4] = ptrPlanet;

		ptrPlanet = AddGameObject<StageSelectObject>(Vec3(2.0f, 2.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-11.0f, 0.0f, 3.0f), L"EARTH6_TX");
		SetSharedGameObject(L"Planet_6", ptrPlanet);
		m_spVec[5] = ptrPlanet;

	}

	void StageSelect::CreateCameraTarget() {
		auto ptrCT = AddGameObject<CameraBox>();
		SetSharedGameObject(L"CameraTarget", ptrCT);
		auto ptrCam = AddGameObject<CamBox>(Vec3(0.0f, 40.0f, 0.0f));
		SetSharedGameObject(L"CamBox", ptrCam);
	}

	void StageSelect::ChangeSelect(int num) {


		for (int i = 0; i < 5; i++) {
			shared_ptr<StageSelectObject> shPtr = m_spVec[i].lock();
			if (shPtr) {
				if ((i + 1) == num) {
					shPtr->SetSelect(true);
				}
				else {
					shPtr->SetSelect(false);
				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	///	ステージセレクトオブジェクト
	//--------------------------------------------------------------------------------------
	StageSelectObject::StageSelectObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const wstring& TextureKey
	):
		GameObject(StagePtr),
		m_scale(Scale),
		m_rotation(Rotation),
		m_position(Position),
		m_textureKey(TextureKey)
	{}

	void StageSelectObject::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(m_rotation);
		ptrTransform->SetPosition(m_position);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetOwnShadowActive(false);
		ptrDraw->SetTextureResource(m_textureKey);
		ptrDraw->SetDrawActive(true);
	}

	void StageSelectObject::OnUpdate() {
		m_frameTime -= App::GetApp()->GetElapsedTime();
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetRotation(0.0f, m_frameTime, 0.0f);
	}
}