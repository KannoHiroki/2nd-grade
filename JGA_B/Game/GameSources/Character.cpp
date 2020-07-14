/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class CameraTarget : public GameObject;
	//--------------------------------------------------------------------------------------
	CameraTarget::CameraTarget(const shared_ptr<Stage>& Stage)
		:GameObject(Stage)
	{
		m_distance = 1.5f;
		m_maxSpeed = 13.0f;
		m_minSpeed = 6.0f;
		m_speed = m_minSpeed;
		m_force = Vec3(0);
		m_velocity = Vec3(0);

		m_chase = false;
	}

	CameraTarget::~CameraTarget() {};

	void CameraTarget::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		auto ptrPlayer = GetStage()->GetSharedGameObject <Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		ptrTrans->SetPosition(playerPos.x, playerPos.y + 1.5f, playerPos.z);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		auto ptrDraw = AddComponent<BcPNStaticDraw>();
		auto mesh = MeshResource::CreateCube(0.25f, true);

		ptrDraw->SetMeshResource(mesh);
		ptrDraw->SetOriginalMeshResource(mesh);
		ptrDraw->GetOriginalMeshResource()->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetOwnShadowActive(false);
		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraである
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			//ptrCamera->SetTargetToAt(Vec3(0, 0.5f, 0));

		}
		SetTarget(ptrPlayer->GetThis<GameObject>());
		SetDrawActive(false);
		SetDrawLayer(100);

	}
	void CameraTarget::OnUpdate() {
		PosAdjustment();
	}
	void CameraTarget::SetTarget(shared_ptr<GameObject>& Obj) {
		m_ptrTarget = Obj;
	}
	void CameraTarget::PosAdjustment() {
		const float Speed = 0.95f;
		const float Height = 1.5f;
		const float Distance = 0.1f;
		m_force.setAll(0.0f);
		auto ptrSeek = GetBehavior<SeekSteering>();
		auto ptrArriv = GetBehavior<ArriveSteering>();

		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto pos = m_ptrTarget->GetComponent<Transform>()->GetPosition();
		pos.y += Height;
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		float elpasedTime = App::GetApp()->GetElapsedTime();
		auto vec = pos - myPos;
		if (m_distance < vec.length()) {
			m_chase = true;
		}
		else if (vec.length() <= Distance) {
			m_chase = false;
		}
		if (m_chase) {

			m_force = ptrArriv->Execute(m_force, m_velocity, pos);
			float ElapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity += m_force * ElapsedTime;
			m_velocity *= Speed;
			myPos += m_velocity * ElapsedTime * m_maxSpeed;
			ptrTrans->SetPosition(myPos);
			auto pos = ptrTrans->GetPosition();
		}

	}

	void CameraTarget::Target() {
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			//LB
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				auto groupVec = GetStage()->GetSharedObjectGroup(L"Enemy")->GetGroupVector();
				for (auto v : groupVec) {
					auto enemyPos = v.lock()->GetComponent<Transform>()->GetPosition();
					auto playerPos = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
					auto vec = enemyPos - playerPos;

				}

			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	カメラを取得し動かすオブジェクト
	//--------------------------------------------------------------------------------------
	CameraBox::CameraBox(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_pos(0),
		m_rot(0),
		m_isPlus(false),
		m_isMinus(false),
		m_imageLength(100.0f),
		m_pushCount(0),
		m_moveStop(false),
		m_stopSelect(true)
	{
		m_isStartActionArrive = true;
	}
	void CameraBox::OnCreate()
	{
		//トランスフォーム
		auto ptrTrans = GetComponent<Transform>();
		m_stageSelectSpherePos[0] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_1")->GetComponent<Transform>()->GetPosition();
		m_stageSelectSpherePos[1] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_2")->GetComponent<Transform>()->GetPosition();
		m_stageSelectSpherePos[2] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_3")->GetComponent<Transform>()->GetPosition();
		m_stageSelectSpherePos[3] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_4")->GetComponent<Transform>()->GetPosition();
		m_stageSelectSpherePos[4] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_5")->GetComponent<Transform>()->GetPosition();
		m_stageSelectSpherePos[5] = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_6")->GetComponent<Transform>()->GetPosition();


		ptrTrans->SetPosition(Vec3(0.0f, 40.0f, 0.0f));
		ptrTrans->SetRotation(m_rot);

		//描画コンポーネント
		auto drawPtr = AddComponent<PNTStaticDraw>();
		drawPtr->SetMeshResource(L"DEFAULT_CUBE");
		drawPtr->SetDrawActive(false);
		drawPtr->SetTextureResource(L"SKY_TX");
		AddComponent<Action>();
		//メインカメラの取得
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		if (ptrCamera)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			//ptrCamera->SetEye(m_pos);
			ptrCamera->SetAt(pos);
		}
		SetDrawLayer(100);
		TargetMove();

	}
	void CameraBox::OnUpdate()
	{
		auto ptrAct = GetComponent<Action>();
		auto ctl = App::GetApp()->GetInputDevice().GetControlerVec();
		if (ptrAct->GetArrived() == false) {
			m_isStartActionArrive = false;
		}
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		if (ptrCamera)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			//ptrCamera->SetEye(m_pos);
			ptrCamera->SetAt(pos);
		}
		auto gm = GameManager::GetGM();
		auto num = gm->GetselectedStageNum();
		auto ptrSprt = GetStage()->GetSharedGameObject<MultiSprite>(L"LevelSprite");
		switch (num)
		{
		case 1:
			ptrSprt->ChangeTexture(L"NORMALPLANET_TX");
			break;

		case 2:
			ptrSprt->ChangeTexture(L"HOTPLANET_TX");
			break;
		case 3:
			ptrSprt->ChangeTexture(L"POLLUTIONPLANET_TX");
			break;
		case 4:
			ptrSprt->ChangeTexture(L"DRYPLANET_TX");
			break;
		case 5:
			ptrSprt->ChangeTexture(L"COLDPLANET_TX");
			break;
		case 6:
			ptrSprt->ChangeTexture(L"MACHINEPLANET_TX");
			break;
		default:
			ptrSprt->ChangeTexture(L"NORMALPLANET_TX");
			break;
		}
	}

	//ステージセレクトの惑星が左右に対象を指定して動く処理
	void CameraBox::Move(int num, wstring Ope)
	{
		if (!m_isStartActionArrive) {
			auto ptrAction = GetComponent<Action>();
			num = num - 1;
			// numの後ろ
			int backNum = 0;
			if (num == 0) {
				backNum = m_maxStageNum;
			}
			else {
				backNum = num - 1;
			}

			// numの前
			int frontNum = 0;
			if (num == m_maxStageNum) {
				frontNum = 0;
			}
			else {
				frontNum = num + 1;
			}

			if (Ope == L"-") {
				ptrAction->AllActionClear();
				ptrAction->AddMoveTo(0.75f, m_stageSelectSpherePos[backNum]);
				ptrAction->Run();
				m_nowSelectStageNum = backNum;
				auto gm = GameManager::GetGM();
				gm->SetSelectedStageNum(backNum + 1);
			}
			else if (Ope == L"+") {
				ptrAction->AllActionClear();
				ptrAction->AddMoveTo(0.75f, m_stageSelectSpherePos[frontNum]);
				ptrAction->Run();
				m_nowSelectStageNum = frontNum;
				auto gm = GameManager::GetGM();
				gm->SetSelectedStageNum(frontNum + 1);
			}
		}
	}

	//ステージセレクトシーン移行時上から目標値まで移動するアクション
	void CameraBox::TargetMove() {
		auto ptrAction = GetComponent<Action>();

		ptrAction->AllActionClear();
		ptrAction->AddMoveTo(0.9f, Vec3(0, 0, 3), Lerp::EaseOut);
		ptrAction->Run();
	}

	//--------------------------------------------------------------------------------------
	//	カメラボックスを使用する為だけのボックス
	//--------------------------------------------------------------------------------------
	CamBox::CamBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_position(Position)
	{
	}

	void CamBox::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.2f, 0.2f, 0.2f));
		ptrTrans->SetRotation(Vec3(0));
		ptrTrans->SetPosition(Vec3(0, 0, 0));
		//タグをつける
		AddTag(L"CamBox");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(false);

		auto ptrEarth = GetStage()->GetSharedGameObject<StageSelectObject>(L"Planet_1");
		auto posEarth = ptrEarth->GetComponent<Transform>()->GetPosition();

		auto ptrAct = AddComponent<Action>();
		ptrAct->AllActionClear();
		ptrAct->AddMoveTo(0.6f, Vec3(100, 0, 0));
		ptrAct->Run();
		SetDrawActive(false);
	}

	void CamBox::OnUpdate() {
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto ptrCam = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCam) {
			ptrCam->SetTargetObject(GetThis<CamBox>());
		}
	}


	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
		m_UPic = 20.0f;
		m_VPic = 20.0f;
	}
	FixedBox::~FixedBox() {}

	//初期化
	void FixedBox::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");
		//タイリング
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float Ucount = m_Scale.x / m_UPic;
		float Vcount = m_Scale.y / m_VPic;
		for (size_t i = 0; i < vertices.size(); i++) {
			//上面
			float UpBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, -1));
			if (UpBetween < 0.01f) {
				if (vertices[i].position.x == -0.5f) {
					vertices[i].textureCoordinate.x = 0.0f;
				}
				else if (vertices[i].position.x == 0.5f) {
					vertices[i].textureCoordinate.x = Ucount;
				}
				if (vertices[i].position.y == -0.5f) {
					vertices[i].textureCoordinate.y = Vcount;
				}
				else if (vertices[i].position.y == 0.5f) {
					vertices[i].textureCoordinate.y = 0.0f;
				}
			}
		}
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->CreateOriginalMesh(vertices, indices);
		ptrDraw->SetOriginalMeshUse(true);
		ptrDraw->SetTextureResource(L"SOIL_TX");
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}
	//--------------------------------------------------------------------------------------
	//	class wall : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	wall::wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
		m_UPic = 2.0f;
		m_VPic = 2.0f;
		m_alpha = 1.0f;
		m_FrameCount = 0.0f;
		m_TransparentTime = 0.3f;
	}
	wall::~wall() {}

	//初期化
	void wall::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"Wall");
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");
		//タイリング処理
		vector<VertexPositionNormalTexture> vertices;
		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		float Ucount, Vcount;
		if (m_Scale.x != 1.0f) {
			Ucount = m_Scale.x / 2;
			Vcount = m_Scale.y / 2;

			for (size_t i = 0; i < vertices.size(); i++) {
				//上面
				float UpBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				//右面
				float RightBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(1, 0, 0));
				//左面
				float LeftBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(-1, 0, 0));
				//手前面
				float NearBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, -1));
				//奥面
				float FarBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, 1));


				//上面
				if (UpBetween < 0.01f) {
					if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = Ucount;
					}
					if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.y = 1.0f;
					}
					else if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//右面
				else if (RightBetween < 0.01f) {
					if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.x = 1.0f;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//左面
				else if (LeftBetween < 0.01f) {
					if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.x = 1.0f;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//手前面
				else if (NearBetween < 0.01f) {
					if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = Ucount;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//奥面
				else if (FarBetween < 0.01f) {
					if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = Ucount;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
			}
		}
		else {
			Ucount = m_Scale.z / 2;
			Vcount = m_Scale.y / 2;

			for (size_t i = 0; i < vertices.size(); i++) {
				//上面
				float UpBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 1, 0));
				//右面
				float RightBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(1, 0, 0));
				//左面
				float LeftBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(-1, 0, 0));
				//手前面
				float NearBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, -1));
				//奥面
				float FarBetween = bsm::angleBetweenNormals(vertices[i].normal, Vec3(0, 0, 1));


				//上面
				if (UpBetween < 0.01f) {
					if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = 1.0f;
					}
					if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.y = Ucount;
					}
					else if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//右面
				else if (RightBetween < 0.01f) {
					if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.x = Ucount;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//左面
				else if (LeftBetween < 0.01f) {
					if (vertices[i].position.z == 0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.z == -0.5f) {
						vertices[i].textureCoordinate.x = Ucount;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//手前面
				else if (NearBetween < 0.01f) {
					if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = 1.0f;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
				//奥面
				else if (FarBetween < 0.01f) {
					if (vertices[i].position.x == 0.5f) {
						vertices[i].textureCoordinate.x = 0.0f;
					}
					else if (vertices[i].position.x == -0.5f) {
						vertices[i].textureCoordinate.x = 1.0f;
					}
					if (vertices[i].position.y == -0.5f) {
						vertices[i].textureCoordinate.y = Vcount;
					}
					else if (vertices[i].position.y == 0.5f) {
						vertices[i].textureCoordinate.y = 0.0f;
					}
				}
			}
		}
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->CreateOriginalMesh(vertices, indices);
		ptrDraw->SetOriginalMeshUse(true);
		ptrDraw->SetTextureResource(L"WALL_TX");
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		SetDrawLayer(107);
	}

	void wall::ReturnAlpha() {
		if (m_alpha < 1.0f) {
			if (m_FrameCount > m_TransparentTime) {
				m_alpha = 1.0f;
				m_FrameCount = 0.0f;
			}
			m_FrameCount += App::GetApp()->GetElapsedTime();
		}
		auto PtrDraw = GetComponent<PNTStaticDraw>();
		PtrDraw->SetDiffuse(Col4(0.1f, 0.1f, 0.1f, m_alpha));
	}

	//--------------------------------------------------------------------------------------
	//	プレイヤーのHPゲージ
	//--------------------------------------------------------------------------------------
	HPGauge::HPGauge(shared_ptr<Stage>& stage, const Vec2 position, bool isFix)
		:GameObject(stage),
		m_position(position),
		m_isFix(isFix)
	{
		m_damageOne = 0.0f;
		m_pastHp = 100;
	}

	HPGauge::~HPGauge() {};

	void HPGauge::OnCreate() {
		float HelfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(-0,HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,0.0f)) },
			{VertexPositionColorTexture(Vec3(HelfSize*2.0f,HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(-0,-HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,1.0f)) },
			{VertexPositionColorTexture(Vec3(HelfSize*2.0f,-HelfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,1.0f))}
		};
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position.x, m_position.y, 0.0f);
		if (m_isFix == false) {
			ptrTrans->SetScale(360.0f, 250.0f, 1.0f);
			m_Per = 350.0f / 100.0f;
			ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
			ptrDraw->SetTextureResource(L"HP_TX");
			SetDrawLayer(150);
		}
		else {
			ptrTrans->SetScale(363.0f, 260.0f, 1.0f);
			ptrDraw->SetTextureResource(L"HPFRAME_TX");
			SetDrawLayer(149);
		}
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
	}

	void HPGauge::OnUpdate() {
		if (m_isFix == false) {
			SetHP();
			Damage();
		}
	}
	void HPGauge::Damage() {
		if (m_pastHp == m_PlayerHitPoint) {
			return;
		}
		else {
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();
			scale.x = m_Per * float(m_PlayerHitPoint);
			ptrTrans->SetScale(scale);
		}
	}

	void HPGauge::SetHP() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_PlayerHitPoint = ptrPlayer->GetHP();

	}
	//--------------------------------------------------------------------------------------
	//	HPゲージのよこに置くスプライト
	//--------------------------------------------------------------------------------------
	HPGaugeFace::HPGaugeFace(shared_ptr<Stage> &stage, Vec2 Position)
		:GameObject(stage),
		m_pos(Position)
	{

	}

	HPGaugeFace::~HPGaugeFace() {};
	void HPGaugeFace::OnCreate() {
		float halfSize = 0.5f;
		//頂点配列
		vector<VertexPositionTexture> backupVertices = {
			{ VertexPositionTexture(Vec3(-halfSize, halfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, halfSize, 0), Vec2(1.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-halfSize, -halfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(halfSize, -halfSize, 0), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		SetAlphaActive(true);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(370.0f, 250.0f, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_pos.x, m_pos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(backupVertices, indices);
		ptrDraw->SetTextureResource(L"CHARAICON_TX");
		SetDrawLayer(150);
	}

	//--------------------------------------------------------------------------------------
	// 緑化
	//--------------------------------------------------------------------------------------
	CircleGrass::CircleGrass(shared_ptr<Stage>& Stage, Vec3 Position)
		:GameObject(Stage),
		m_pos(Position),
		m_scale(Vec3(4.0f, 4.0f, 1.0f))
	{
		m_rad = 2.0f;
		m_tmpScale = Vec3(0);
	}
	CircleGrass::~CircleGrass() {};
	void CircleGrass::OnCreate() {
		AddTag(L"Green");
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetRotation(XM_PIDIV2, 0, 0);
		ptrTrans->SetScale(0.0f, 1.0f, 0.0f);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		SetAlphaActive(true);
		ptrDraw->SetTextureResource(L"CIRCLEGRASS_TX");
		auto ptrAct = AddComponent<Action>();
		ptrAct->AllActionClear();
		ptrDraw->SetDepthStencilState(DepthStencilState::None);
		SetDrawLayer(0);


	}

	void CircleGrass::OnUpdate() {
	}

	void CircleGrass::AddScale(Vec2 scale) {
		m_tmpScale.x = m_tmpScale.x + scale.x;
		m_tmpScale.y = m_tmpScale.y + scale.y;
		auto ptrAct = GetComponent<Action>();
		ptrAct->AllActionClear();
		ptrAct->AddScaleTo(0.3f, Vec3(m_tmpScale.x, m_tmpScale.y, 1.0f));
		ptrAct->Run();
	}
	//--------------------------------------------------------------------------------------
	//	カメラ演出用オブジェクト
	//--------------------------------------------------------------------------------------
	CameraTargetObject::CameraTargetObject(shared_ptr<Stage>& Stage, Vec3 startPos)
		: GameObject(Stage),
		m_StartPos(startPos),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 10.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{
		m_at = Vec3(0);
		m_eye = Vec3(0);
		m_TotalTime = 0.0f;
	}
	void CameraTargetObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.25f, 0.25f, 0.25f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(m_StartPos);
		AddComponent<Action>();
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

	}
	void CameraTargetObject::OnUpdate() {
		if (m_StartProd.Start == true && m_StartProd.End == false) {
			m_AtPos = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetPosition();
			auto ptrAct = GetComponent<Action>();				
			m_TotalTime += App::GetApp()->GetElapsedTime();
			if (m_TotalTime > 5.05f) {
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Landing", 0, 0.9f);
				m_TotalTime = 0.0f;
			}
			//　ゲームスタート時のカメラ演出が終わったら
			if (ptrAct->GetArrived() == true) {
				auto ptrGameGtage = GetTypeStage<GameStage>();
				ptrGameGtage->ToMyCamera();
				GameManager::GetGM()->SetIsCameraActive(true);
				GameManager::GetGM()->SetIsPlayerActive(true);
				m_StartProd.End = true;
				m_TotalTime = 0.0f;
			}
		}
		FenceCollapce();

		if (m_FenceCollapse.Start == true && m_FenceCollapse.End == false) {
			auto ptrAct = GetComponent<Action>();



			//　フェンス壊れた時のカメラ演出が終わったら
			if (ptrAct->GetArrived() == true) {
				auto ptrGameGtage = GetTypeStage<GameStage>();
				ptrGameGtage->ToMyCamera();
				GameManager::GetGM()->SetIsCameraActive(true);
				GameManager::GetGM()->SetIsPlayerActive(true);
				m_FenceCollapse.End = true;
			}
		}
		ClearEnding();
		if (m_ClearEnding.Start == true && m_ClearEnding.End == false) {
			auto ptrAct = GetComponent<Action>();
			//　ゲームスタート時のカメラ演出が終わったら
			if (ptrAct->GetArrived() == true) {
				m_ClearEnding.End = true;
				auto GOGroupVec = GetStage()->GetSharedObjectGroup(L"ClearUI")->GetGroupVector();
				for (auto v : GOGroupVec) {
					v.lock()->SetDrawActive(true);
					v.lock()->SetUpdateActive(true);
				}
			}
		}
	}

	void CameraTargetObject::ToStartEnter() {
		if (m_StartProd.Start == false) {
			GetStage()->AddGameObject<EffectPlayObj>(Vec3(0.0f, 0.0f, 0.0f), L"PlayerLanding3.efk");
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetPosition(-11.0f, 5.0f, 0.0f);
			auto ptrAct = GetComponent<Action>();
			ptrAct->AllActionClear();
			ptrAct->AddMoveTo(6.5f, Vec3(-10.0f, 5.0f, 0.0f));
			ptrAct->Run();
			m_StartProd.Start = true;
			auto ptrCamera = dynamic_pointer_cast<OpeningCamera>(OnGetDrawCamera());
			if (ptrCamera) {
				ptrCamera->SetCameraObject(GetThis<CameraTargetObject>());
			}
		}
	}

	void CameraTargetObject::FenceCollapce() {
		if (m_StartProd.End == true) {
			auto ptrTrans = GetComponent<Transform>();
			ptrTrans->SetRotation(0.0f, -XM_PIDIV2, 0.0f);
			auto myPos = ptrTrans->GetPosition();
			auto ptrAct = GetComponent<Action>();
			auto ptrFence = GetStage()->GetSharedGameObject<Fence>(L"FenceA");
			auto fencePos = ptrFence->GetComponent<Transform>()->GetPosition();
			auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(ptrFence->GetDistrictName());
			m_AtPos = fencePos;
			if (ptrPlant->GetIsMaxCircleScale() == true && m_FenceCollapse.Start == false) {
				ptrTrans->SetPosition(Vec3(fencePos.x + 15.0f, fencePos.y + 20.0f, fencePos.z + 5.0f));
				ptrAct->AllActionClear();
				ptrAct->AddMoveTo(3.0f, Vec3(fencePos.x + 15.0f, fencePos.y + 20.01f, fencePos.z + 5.0f));
				ptrAct->Run();
				m_FenceCollapse.Start = true;
				auto ptrTarget = GetStage()->GetSharedGameObject<CameraTarget>(L"CameraTarget");
				auto ptrGameGtage = GetTypeStage<GameStage>();
				ptrGameGtage->ToOpeningCamera();

				GameManager::GetGM()->SetIsPlayerActive(false);
			}
			if (m_FenceCollapse.Start == true && m_FenceCollapse.End == false) {
				auto ptrCamera = dynamic_pointer_cast<OpeningCamera>(OnGetDrawCamera());
				if (ptrCamera) {
					ptrCamera->SetEye(myPos.x - 5.0f, myPos.y + 3.0f, myPos.z);
				}
			}


		}
	}
	void CameraTargetObject::ClearEnding() {
		if (m_FenceCollapse.End == true) {
			auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

			// クリア演出が開始されていないとき
			if (m_ClearEnding.Start == false) {
				// 100％になったプラントが何個か調べる
				auto groupVec = GetStage()->GetSharedObjectGroup(L"Plants")->GetGroupVector();
				int Count = 0;
				int MaxCount = 0;
				for (auto v : groupVec) {
					Count++;
					auto ptr = v.lock();
					auto ptrPlant = dynamic_pointer_cast<Plant>(ptr);
					if (ptrPlant->GetIsMaxCircleScale() == true) {
						MaxCount++;
					}
				}
				// プラントの数と100％になったプラントの数が一緒になったら演出開始
				if (MaxCount == Count) {
					auto ptrGameGtage = GetTypeStage<GameStage>();
					ptrGameGtage->ToOpeningCamera();
					GameManager::GetGM()->SetIsPlayerActive(false);
					auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
					m_ClearEnding.Start = true;
					GetComponent<Transform>()->SetPosition(playerPos.x + 10.0f, playerPos.y + 10.0f, playerPos.z);
					auto ptrAct = GetComponent<Action>();
					ptrAct->AllActionClear();
					ptrAct->AddMoveTo(6.0f, Vec3(playerPos.x + 10.0f, playerPos.y - 0.5f, playerPos.z));
					ptrAct->Run();
					GetStage()->AddGameObject<EffectPlayObj>(playerPos, L"EndingJump2.efk");
				}
			}

			if (m_ClearEnding.Start == true && m_ClearEnding.End == false) {
				auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
				m_AtPos = playerPos;
				m_TotalTime += App::GetApp()->GetElapsedTime();
				if (m_TotalTime > 2.5f) {
					auto vec = Vec3(playerPos.x, 120.0f, playerPos.z) - playerPos;
					vec.normalize();
					ptrPlayer->GetComponent<Transform>()->SetPosition(playerPos + vec * 0.8f);
				}
			}
		}
	}
	//カメラ演出のステート
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() {
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<CameraTargetObject>& Obj) {
		//Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<CameraTargetObject>& Obj) {
		//if (Obj->ExcuteBehavior(2.0f)) {
		//	Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		//}
	}
	void OpeningCameramanToGoalState::Exit(const shared_ptr<CameraTargetObject>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<CameraTargetObject>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance() {
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<CameraTargetObject>& Obj) {
		Obj->ToStartEnter();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<CameraTargetObject>& Obj) {
		//if (Obj->ExcuteBehavior(3.0f)) {
		//	Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		//}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<CameraTargetObject>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<CameraTargetObject>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() {
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}
	void OpeningCameramanEndState::Enter(const shared_ptr<CameraTargetObject>& Obj) {
		//Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<CameraTargetObject>& Obj) {
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<CameraTargetObject>& Obj) {
	}


	//--------------------------------------------------------------------------------------
	///	エフェクトを再生させるときに使うオブジェクト
	/// ポジション、エフェクトのファイル名(拡張子まで！)
	//--------------------------------------------------------------------------------------
	EffectPlayObj::EffectPlayObj(shared_ptr<Stage>& stage, const Vec3& Position, const wstring EffectKey) :
		GameObject(stage),
		m_pos(Position),
		m_effectKey(EffectKey)
	{

	}
	void EffectPlayObj::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetRotation(Vec3(0));
		ptrTrans->SetScale(Vec3(0.1f, 0.1f, 0.1f));
		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + m_effectKey;
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, ptrTrans->GetPosition());
		SetDrawLayer(110);
	}
	void EffectPlayObj::OnUpdate() {
		EffectEndCheck();
	}

	void EffectPlayObj::EffectEndCheck() {
		if (m_EfkPlay->GetArrive() == false) {
			GetStage()->RemoveGameObject<EffectPlayObj>(GetThis<EffectPlayObj>());
		}
	}

	//--------------------------------------------------------------------------------------
	///	プラント
	//--------------------------------------------------------------------------------------
	Plant::Plant(shared_ptr<Stage>& stage, const Vec3& position, const Vec3& scale, wstring districtName, Vec3 MaxScale)
		:GameObject(stage),
		m_pos(position),
		m_scale(scale),
		m_districtName(districtName),
		m_MaxScale(MaxScale)
	{
		m_isRun = false;
		m_isMaxCircleScale = false;
		m_maxScaleOneThird = m_MaxScale / 4;
		m_modelName = L"WAKABA_MESH";
	}

	void Plant::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetRotation(Vec3(0.0f, XM_PIDIV4, 0.0f));
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"WAKABA_MESH");
		ptrDraw->SetTextureResource(L"WAKABA_TX");
		SetAlphaActive(true);
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.3f));
		GetStage()->SetSharedGameObject(m_districtName, GetThis<Plant>());
		SetDrawLayer(105);

		auto ptrAct = AddComponent<Action>();
		SetGerminationAct();
		auto ptrLeaf = GetStage()->AddGameObject<Leaf>(GetThis<Plant>());
	}
	void Plant::OnUpdate() {
		SearchPlayer();
		ExamineScale();
		ModelChange();
	}

	void Plant::SearchPlayer() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto vec = myPos - playerPos;
		float len = vec.length();
		auto cntl = App::GetApp()->GetInputDevice().GetControlerVec();
		if (len <= 4.0f && m_isRun == false) {
			if (cntl[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto ptrPlayerDraw = ptrPlayer->GetComponent<PNTBoneModelDraw>();
				if (ptrPlayerDraw->GetCurrentAnimation() != L"Plant") {
					ptrPlayerDraw->ChangeCurrentAnimation(L"Plant");
					GetComponent<Action>()->Run();
					GetComponent<Transform>()->SetScale(Vec3(0));
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"Plant", 0, 0.7f);
				}
				m_isRun = true;
				auto ptrDraw = GetComponent<PNTStaticModelDraw>();
				ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
				m_myGrass = GetStage()->AddGameObject<CircleGrass>(myPos);
				
			}
		}
	}

	void Plant::ExamineScale() {
		if (m_isMaxCircleScale == false && m_isRun == true) {
			auto ptrGrass = m_myGrass.lock();
			auto grassScale = ptrGrass->GetComponent<Transform>()->GetScale();
			if (m_MaxScale.x <= grassScale.x) {
				m_isMaxCircleScale = true;
				auto myPos = GetComponent<Transform>()->GetPosition();
				GetStage()->AddGameObject<EffectPlayObj>(myPos, L"MaxGreenEffect.efk");
			}
		}
	}

	void Plant::SetGerminationAct() {
		auto ptrAct = GetComponent<Action>();
		ptrAct->AllActionClear();
		ptrAct->AddScaleTo(0.5f, Vec3(m_scale.x - 0.8f, m_scale.y + 2.0f, m_scale.z - 0.8f), Lerp::EaseOut);
		ptrAct->AddScaleTo(0.3f, Vec3(m_scale.x + 0.8f, m_scale.y - 0.4f, m_scale.z + 0.8f));
		ptrAct->AddScaleTo(0.2f, Vec3(m_scale.x, m_scale.y + 0.7f, m_scale.z), Lerp::EaseOut);
		ptrAct->AddScaleTo(0.3f, Vec3(m_scale.x + 0.1f, m_scale.y - 0.1f, m_scale.z + 0.1f));
		ptrAct->AddScaleTo(0.1f, m_scale);
	}

	void Plant::ModelChange() {
		if (m_isRun == true) {
			auto ptrDraw = GetComponent<PNTStaticModelDraw>();
			auto circleTrans = m_myGrass.lock()->GetComponent<Transform>();
			auto nowCircleScale = circleTrans->GetScale();
			auto GM = GameManager::GetGM();
			if (nowCircleScale.x >= m_MaxScale.x) {
				if (m_modelName != L"WOODLV4_MESH") {
					ptrDraw->SetMeshResource(L"WOODLV4_MESH");
					m_modelName = L"WOODLV4_MESH";
					ptrDraw->SetTextureResource(L"WOOD2_TX");
					SetGerminationAct();
					GetComponent<Action>()->Run();
					return;
				}
				else {
					return;
				}
			}
			else if (nowCircleScale.x >= m_maxScaleOneThird.x * 2.0f) {
				if (m_modelName != L"WOODLV3_MESH") {
					ptrDraw->SetMeshResource(L"WOODLV3_MESH");
					m_modelName = L"WOODLV3_MESH";
					ptrDraw->SetTextureResource(L"WOOD_TX");
					SetGerminationAct();
					GetComponent<Action>()->Run();
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"LavelUP", 0, 0.9f);
					return;
				}
				else {
					return;
				}
			}
			else if (nowCircleScale.x >= m_maxScaleOneThird.x) {
				if (m_modelName != L"WOODLV2_MESH") {
					ptrDraw->SetMeshResource(L"WOODLV2_MESH");
					m_modelName = L"WOODLV2_MESH";
					ptrDraw->SetTextureResource(L"WOOD_TX");
					SetGerminationAct();
					GetComponent<Action>()->Run();
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"LavelUP", 0, 0.9f);
					return;
				}
				else {
					return;
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------	
	///	植木の葉っぱさん
	//--------------------------------------------------------------------------------------
	Leaf::Leaf(shared_ptr<Stage> &stage, shared_ptr<Plant> &plant)
		:GameObject(stage),
		m_plant(plant)
	{
		m_modelName = L"NONE";
	}

	void Leaf::OnCreate() {
		auto plantTrans = m_plant->GetComponent<Transform>();
		auto plantPos = plantTrans->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto plantScale = plantTrans->GetScale();
		ptrTrans->SetPosition(plantPos);
		ptrTrans->SetRotation(Vec3(0.0f, XM_PIDIV4, 0.0f));
		ptrTrans->SetScale(Vec3(1.0f, 1.0f, 1.0f));
		m_scale = ptrTrans->GetScale();
		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		AddComponent<Action>();
		SetAlphaActive(true);
		SetDrawLayer(109);
		ptrDraw->SetBlendState(BlendState::AlphaBlend);
		SetDrawActive(false);
	}

	void Leaf::OnUpdate() {
		ModelChange();
	}

	void Leaf::ModelChange() {
		if (m_plant->GetIsRun() == true)
		{
			auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
			auto modelName = m_plant->GetModelName();
			if (modelName == L"WOODLV4_MESH") {
				if (m_modelName != L"LEAFLV4_MESH") {
					ptrDraw->SetMeshResource(L"LEAFLV4_MESH");
					m_modelName = L"LEAFLV4_MESH";
					ptrDraw->SetTextureResource(L"LEAF_TX");
					SetDrawActive(true);
					SetGerminationAct();
					return;
				}
				else {
					return;
				}
			}
			else if (modelName == L"WOODLV3_MESH") {
				if (m_modelName != L"LEAFLV3_MESH") {
					ptrDraw->SetMeshResource(L"LEAFLV3_MESH");
					m_modelName = L"LEAFLV3_MESH";
					ptrDraw->SetTextureResource(L"LEAF_TX");
					SetDrawActive(true);
					SetGerminationAct();
					return;
				}
				else {
					return;
				}
			}
			else if (modelName == L"WOODLV2_MESH") {
				if (m_modelName != L"LEAFLV2_MESH") {
					ptrDraw->SetMeshResource(L"LEAFLV2_MESH");
					m_modelName = L"LEAFLV2_MESH";
					ptrDraw->SetTextureResource(L"LEAF_TX");
					SetDrawActive(true);
					SetGerminationAct();
					return;
				}
				else {
					return;
				}
			}
			else if (modelName == L"WAKABA_MESH") {
				SetDrawActive(false);
				return;
			}
		}
	}

	void Leaf::SetGerminationAct() {
		auto ptrAct = GetComponent<Action>();
		ptrAct->AllActionClear();
		ptrAct->AddScaleTo(0.5f, Vec3(m_scale.x - 0.8f, m_scale.y + 2.0f, m_scale.z - 0.8f), Lerp::EaseOut);
		ptrAct->AddScaleTo(0.3f, Vec3(m_scale.x + 0.8f, m_scale.y - 0.4f, m_scale.z + 0.8f));
		ptrAct->AddScaleTo(0.2f, Vec3(m_scale.x, m_scale.y + 0.7f, m_scale.z), Lerp::EaseOut);
		ptrAct->AddScaleTo(0.3f, Vec3(m_scale.x + 0.1f, m_scale.y - 0.1f, m_scale.z + 0.1f));
		ptrAct->AddScaleTo(0.1f, m_scale);
		ptrAct->Run();
	}
	//--------------------------------------------------------------------------------------	
	///	スポーンオブジェクト
	//--------------------------------------------------------------------------------------
	SpawnBlock::SpawnBlock(shared_ptr<Stage> &Stage, Vec3 Position, wstring DistrictName) :
		GameObject(Stage),
		m_pos(Position),
		m_districtName(DistrictName)
	{
		m_spawnTime = 0.0f;
	};

	void SpawnBlock::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		m_pos.y -= 2.5f;
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetRotation(Vec3(0.0f,-XM_PIDIV2,0.0f));
		ptrTrans->SetScale(Vec3(0.65f, 0.65f, 0.65f));

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"HOUSE_MESH");
		ptrDraw->SetTextureResource(L"HOUSE_TX");

		SetDrawLayer(100);
		
	}
	void SpawnBlock::OnUpdate() {
		auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(m_districtName);
		auto GM = GameManager::GetGM();
		auto nowEnemy = GM->GetNowEnemyNum();
		auto MaxEnemyNum = GM->GetMaxDrawEnemyNum();
		m_spawnTime += App::GetApp()->GetElapsedTime();
		if (m_spawnTime > 0.75f) {
			if (ptrPlant->GetIsRun() == true && MaxEnemyNum >= nowEnemy && ptrPlant->GetIsMaxCircleScale() == false) {
				SpawnNormal();
			}
			m_spawnTime = 0.0f;
		}
	}

	void SpawnBlock::SpawnNormal() {
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		auto ptr = GetStage()->AddGameObject<EnemyObject>(Vec3(myPos.x + float(rand() % 10), myPos.y + 1.0f, myPos.z + float(rand() % 10)), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.7f/*1.4f, 1.1f, 1.4f*/), m_districtName);
		GetStage()->AddGameObject<EnemySword>(ptr);
		auto enemyNum = GameManager::GetGM()->GetNowEnemyNum();
		GameManager::GetGM()->SetNowEnemyNum(enemyNum + 1);
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy");
		group->IntoGroup(ptr);
		ptr->SetDrawActive(true);
	}

	void SpawnBlock::SpawnLongDis() {
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		auto ptr = GetStage()->AddGameObject<LongDisEnemyObject>(Vec3(myPos.x + float(rand() % 30), myPos.y + 10.0f, myPos.x + float(rand() % 15)), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 1.2f, 0.5f), m_districtName);
		auto enemyNum = GameManager::GetGM()->GetNowEnemyNum();
		GameManager::GetGM()->SetNowEnemyNum(enemyNum + 1);
		auto group = GetStage()->GetSharedObjectGroup(L"Enemy");
		group->IntoGroup(ptr);
	}

	void SpawnBlock::Spawn(int SpawnEnemyNum, EnemyType type) {
		if (SpawnEnemyNum != 0) {

			switch (type)
			{
			case basecross::EnemyType::NormalEnemy:
				for (int i = 0; i < SpawnEnemyNum; i++) {
					SpawnNormal();
				};
				break;
			case basecross::EnemyType::LongRangeEnemy:
				for (int i = 0; i < SpawnEnemyNum; i++) {
					SpawnLongDis();
				};
				break;
			case basecross::EnemyType::BossEnemy:
				break;
			default:
				break;
			}
		}
	}
	//--------------------------------------------------------------------------------------	
	///	エリアの出入り口に置くあたり判定オブジェクト
	//--------------------------------------------------------------------------------------
	EreaBox::EreaBox(shared_ptr<Stage> &Stage, Vec3 Position, Vec3 Scale ,Vec3 Rotation, wstring NowEreaName) :
		GameObject(Stage),
		m_pos(Position),
		m_scale(Scale),
		m_rotation(Rotation),
		m_nowEreaName(NowEreaName)
	{};

	void EreaBox::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotation);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		SetDrawActive(false);	//後でfalseに

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddComponent<Action>();

		//GetStage()->SetSharedGameObject(L"EreaBox", GetThis<EreaBox>());
	}
	void EreaBox::OnUpdate() {
	}

	void EreaBox::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//所持しているエリアの名前をプレイヤーのいるエリアの名前に変える
		if (other->FindTag(L"Player")) {
			auto ptrPlayer = dynamic_pointer_cast<Player>(other);
			auto ptrErea = ptrPlayer->GetNowEreaName();
			if (ptrErea != m_nowEreaName) {
				ptrPlayer->SetNowEreaName(m_nowEreaName);
				//画面に今いるエリアのスプライトを表示
				auto ereaSprite = GetStage()->AddGameObject<FadeInAndOutSprite>(Vec2(300 * 2, 100 * 2), Vec3(0, 150, 0), L"AREA_" + m_nowEreaName + L"_TX", 0.8f, 1.5f, 0.5f);
				ereaSprite->SetDrawLayer(301);
			}
		}
	}
	//--------------------------------------------------------------------------------------	
	///	ビルボード処理された板ポリ
	//--------------------------------------------------------------------------------------
	BillboardPlate::BillboardPlate(shared_ptr<Stage>&Stage, const Vec3 pos, const wstring key, const wstring district)
		: GameObject(Stage),
		m_pos(pos),
		m_scale(Vec3(2.0f,2.0f,1.0f)),
		m_rot(Vec3(0.0f,0.0f,0.0f)),
		m_key(key),
		m_district(district)
	{}

	void BillboardPlate::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetTextureResource(m_key);
		SetAlphaActive(true);
		ptrDraw->SetBlendState(BlendState::AlphaBlend);
		SetDrawLayer(108);

		auto ptrAct = AddComponent<Action>();
		ptrAct->AddScaleTo(0.5f, Vec3(3.0f, 3.0f, 1.0f));
		ptrAct->AddScaleTo(1.0f, Vec3(2.0f, 2.0f, 1.0f));
		ptrAct->SetLooped(true);
		ptrAct->Run();
	}

	void BillboardPlate::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto ptrGameStage = GetTypeStage<GameStage>();
		if (ptrGameStage) {
			if (ptrGameStage->GetNowSelectCamera() == CameraSelect::myCamera) {
				auto myPos = GetComponent<Transform>()->GetPosition();
				auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
				auto cameraPos = ptrCamera->GetEye();

				auto vec = cameraPos - myPos;
				float rad = atan2(vec.z, vec.x);

				Vec3 rot(0.0f, -(rad + XM_PIDIV2), 0.0f);

				GetComponent<Transform>()->SetRotation(rot);

				auto plant = GetStage()->GetSharedGameObject<Plant>(m_district);
				if (plant->GetIsRun()) {
					SetDrawActive(false);
				}
			}
		}
	}

	void BillboardPlate::DeleteObject()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
	}

	//--------------------------------------------------------------------------------------	
	///	ビルボード処理された板ポリ
	//--------------------------------------------------------------------------------------
	BillboardPlate1::BillboardPlate1(shared_ptr<Stage>&Stage, const Vec3 pos, const wstring key, const wstring district)
		: GameObject(Stage),
		m_pos(pos),
		m_scale(Vec3(2.0f, 2.0f, 1.0f)),
		m_rot(Vec3(0.0f, 0.0f, 0.0f)),
		m_key(key),
		m_district(district)
	{}

	void BillboardPlate1::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetTextureResource(m_key);
		SetAlphaActive(true);
		ptrDraw->SetBlendState(BlendState::AlphaBlend);
		SetDrawLayer(108);

	}

	void BillboardPlate1::OnUpdate()
	{

		auto myPos = GetComponent<Transform>()->GetPosition();
		auto ptrCamera = dynamic_pointer_cast<Camera>(OnGetDrawCamera());
		auto cameraPos = ptrCamera->GetEye();

		auto vec = cameraPos - myPos;
		float rad = atan2(vec.z, vec.x);

		Vec3 rot(0.0f, -(rad + XM_PIDIV2), 0.0f);

		GetComponent<Transform>()->SetRotation(rot);

	}


Fence::Fence(shared_ptr<Stage>& stage, Vec3 Position, Vec3 Rotate, wstring DistrictName)
	:GameObject(stage),
	m_pos(Position),
	m_rot(Rotate),
	m_districtName(DistrictName)
{
	m_scale = Vec3(16.0f, 16.0f, 2.0f);
	m_isCollapse = false;
}

	void Fence::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"FENCE_MESH");
		ptrDraw->SetTextureResource(L"FENCE_TX");
		ptrDraw->SetBlendState(BlendState::AlphaBlend);
		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f/m_scale.x, 1.0f / m_scale.y, 1.0f/ m_scale.z),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.05f, 0.0f)
		);
		ptrDraw->SetMeshToTransformMatrix(SpanMat);


		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		auto ptrAct = AddComponent<Action>();
		ptrAct->AllActionClear();
		ptrAct->AddRotateTo(0.6f, Vec3(-XM_PIDIV2, -XM_PIDIV2, 0.0f));
		SetDrawLayer(101);
	}

	void Fence::OnUpdate() {
		Collapse();
	}
	
	void Fence::Collapse() {
		auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(m_districtName);
		auto ptrAct = GetComponent<Action>();
		if (ptrPlant) {
			if (ptrPlant->GetIsMaxCircleScale() == true && m_isCollapse == false) {
				ptrAct->Run();
				m_isCollapse = true;
				auto ptrColl = GetComponent<CollisionObb>();
				ptrColl->SetAfterCollision(AfterCollision::None);
			}
			else if (m_isCollapse == true && ptrAct->GetArrived() == true) {
				auto ptrDraw = GetComponent<PNTStaticModelDraw>();
				auto diff = ptrDraw->GetDiffuse();
				ptrDraw->SetDiffuse(Col4(diff.x, diff.y, diff.z, diff.w - App::GetApp()->GetElapsedTime() * 0.3f));
				if (diff.w <= 0.0f) {
					SetDrawActive(false);
				}
			}
		}
	}

	Hang::Hang(shared_ptr<Stage>&stage, Vec3 pos) 
		:GameObject(stage)
	{
		pos.y -= 2.45f;
		m_pos = pos;
		m_rot = Vec3(0.0f, XM_PIDIV2, 0.0f);
		m_scale = Vec3(0.65f, 0.65, 0.65f);
	}

	void Hang::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_pos);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"HANG_MESH");
		ptrDraw->SetTextureResource(L"HANG_TX");

		SetDrawLayer(100);
	}

	void Hang::OnUpdate()
	{

	}
}
//end basecross
