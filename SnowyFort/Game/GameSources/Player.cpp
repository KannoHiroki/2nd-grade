/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Scale(0.25f),
		m_Rotation(0.0f,-XM_PIDIV2,0.0f),
		m_Position(0, 0, 0),
		m_DefScale(m_Scale),
		m_DefRotation(m_Rotation),
		m_DefPosition(m_Position),
		m_PlayerMoveCircleHalf(1.5f),
		m_Speed(1.0f),
		m_DefSpeed(m_Speed),
		m_Rad(0.0f),
		m_DEFAULTSHOTSCALE(0.25f),
		m_ShotScale(m_DEFAULTSHOTSCALE),
		m_ShotRotation(0),
		m_GettingLargeSpeed(0.1f),
		m_MaxShotScale(1.0f)
	{}

	Player::Player(const shared_ptr<Stage>& StagePtr, const float Scale, const Vec3& Rotation, const Vec3& Position, const float PlayerMoveCircleHalf):
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_DefScale(m_Scale),
		m_DefRotation(m_Rotation),
		m_DefPosition(m_Position),
		m_PlayerMoveCircleHalf(PlayerMoveCircleHalf),
		m_Speed(1.0f),
		m_DefSpeed(m_Speed),
		m_Rad(0.0f),
		m_DEFAULTSHOTSCALE(0.25f),
		m_ShotScale(m_DEFAULTSHOTSCALE),
		m_ShotRotation(0),
		m_GettingLargeSpeed(0.1f)
	{}

	//コントローラーの入力を取得
	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//同時押しは入力を受け取らない
		if (!(KeyState.m_bPushKeyTbl['A'] && KeyState.m_bPushKeyTbl['D'])) {
			//Aボタン
			if (KeyState.m_bPushKeyTbl['A']) {
				//左
				ret.x = -1.0f;
			}
			//Dボタン
			if (KeyState.m_bPushKeyTbl['D']) {
				//右
				ret.x = 1.0f;
			}
		}
		return ret;
	}

	void Player::MovePlayer() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto inPut = GetInputState();
		//プレイヤーの移動スピードをイーズアウト処理する
		float t = (m_ShotScale / (m_DEFAULTSHOTSCALE*6.0f)); //イーズアウトする最大値
		t /= 1;
		t -= 1;
		m_Speed = -1.5f * (pow(4.0f, t) - 1) + 0.0f;
		if (m_Speed < 0.0f) {
			m_Speed = 0.0f;
		}

		//アニメーションを切り替える
		//auto animComp = GetComponent<BcPNTBoneModelDraw>();
		//animComp->ChangeCurrentAnimation(L"PlayerWalk");

		if (inPut.x != 0) {
			m_Rad += inPut.x * elapsedTime * m_Speed;

			m_ShotScale += abs(inPut.x) * elapsedTime * m_GettingLargeSpeed * m_Speed;

			//発射口の位置を更新
			ShotPosUpdate();
			if (m_MaxShotScale <= m_ShotScale) {
				auto ptrTrans = GetComponent<Transform>();
				auto rot = ptrTrans->GetRotation();
				rot = Vec3(0, -m_Rad, 0);
				auto ptrBullet = GetStage()->AddGameObject<SnowBall>(m_ShotScale, rot, m_ShotPosition);
				ResetShotScale();
			}
		}
		PlayerRadToPos();
	}

	void Player::OnCreate() {
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//直径25センチの球体
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(Vec3(m_PlayerMoveCircleHalf + m_Position.x, m_Position.y + -0.2f, m_Position.z));
		
		PlayerRadToPos();

		//発射口の位置を更新
		ShotPosUpdate();

		//CollisionSphere衝突判定を付ける
		//auto ptrColl = AddComponent<CollisionSphere>();

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		//アニメーションコンポーネントを追加する
		auto animComp = AddComponent<BcPNTBoneModelDraw>();
		animComp->SetMeshResource(L"BoneModel_Player");
		animComp->SetDiffuse(Col4(0, 0, 0, 1.0f));
		//アニメーションキーを設定
		animComp->AddAnimation(
			L"PlayerWalk",		//const wstring& Name,		アニメーションキー
			0,					//int StartSample,			開始位置
			39,					//int SampleLength,			終了位置
			true,				//bool Loop,				ループするか
			30.0f				//float SamplesParSecond	アニメーションのスピード
		);
		animComp->ChangeCurrentAnimation(L"PlayerWalk");

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		// UIの作成
		UICreate();

		auto ptrCamera = dynamic_pointer_cast<MyPlayerCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			// カメラにプレイヤーを保存
			ptrCamera->SetTargetObject(GetThis<GameObject>());
		}
		GetStage()->SetSharedGameObject(L"PlayerObj", GetThis<Player>());
	}

	void Player::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		//雪玉（半透明）の大きさ、回転、位置を更新
		UIMove();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);
		ptrDraw->SetDrawActive(true);
	}

	void Player::OnUpdate2() {
		//文字列の表示
		DrawStrings();
	}

	//Aボタン
	void Player::OnPushB() {
		auto ptrTrans = GetComponent<Transform>();
		auto rot = ptrTrans->GetRotation();
		rot = Vec3(0, -m_Rad, 0);
		auto ptrBullet = GetStage()->AddGameObject<SnowBall>(m_ShotScale, rot, m_ShotPosition);
		ResetShotScale();
	}

	//雪玉のUIの初期化
	void Player::UICreate() {
		//UI用のObject
		auto ptrUISnowBallObj = GetStage()->AddGameObject<SnowBall>(m_ShotScale, Vec3(0, -m_Rad, 0), m_ShotPosition);
		m_ShotScale = ptrUISnowBallObj->GetComponent<Transform>()->GetScale().x;
		// UIの透過
		ptrUISnowBallObj->SetAlphaActive(true);
		auto ptrUIDraw = ptrUISnowBallObj->GetComponent<BcPNTStaticDraw>();
		ptrUIDraw->SetColorAndAlpha(Col4(1, 1, 1, 0.4f));
		ptrUISnowBallObj->SetUpdateActive(false);
	}

	//雪玉（半透明）の大きさ、回転、位置を更新
	void Player::UIMove() {
		auto input = GetInputState();
		shared_ptr<SnowBall> snowballUIobj = nullptr;
		auto objs = GetStage()->GetGameObjectVec();
		for (auto obj : objs) {
			snowballUIobj = dynamic_pointer_cast<SnowBall>(obj);
			if (snowballUIobj) {
				break;
			}
		}
		auto ptrTrans = snowballUIobj->GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(m_ShotScale));
		m_ShotRotation = Vec3(m_Rad, -m_Rad, 0);
		ptrTrans->SetRotation(m_ShotRotation);
		ptrTrans->SetPosition(m_ShotPosition);
	}

	//プレイヤーの移動後の座標を求める
	void Player::PlayerRadToPos() {
		auto transComp = GetComponent<Transform>();
		auto rot = transComp->GetRotation();
		Vec3 moveRot = Vec3(0, -m_Rad + -XM_PIDIV2, 0);
		auto pos = transComp->GetPosition();
		Vec3 movePos = Vec3((m_PlayerMoveCircleHalf - m_ShotScale/2) * cosf(m_Rad), m_DefPosition.y + -0.2f, (m_PlayerMoveCircleHalf - m_ShotScale/2) * sinf(m_Rad));
		
		//雪を転がす為の位置に移動させる
		Vec3 wrapRot = PlayerWrapRot(moveRot);
		Vec3 wrapPos = PlayerWrapPos(movePos);
		transComp->SetRotation(wrapRot);
		transComp->SetPosition(wrapPos);
	}

	//雪玉の進行方向の反対側に回り込む
	Vec3 Player::PlayerWrapPos(Vec3 pos) {
		auto input = GetInputState();
		Vec3 wrapPos = pos;
		if (input.x != 0) {
			auto dir = input.x * XM_PIDIV2 + atan2f((pos.z - m_ShotPosition.z), (pos.x - m_ShotPosition.x));
			wrapPos = Vec3(m_ShotPosition.x + (m_Scale.x/2 + m_ShotScale/2) * cosf(dir), pos.y, m_ShotPosition.z + (m_Scale.x/2 + m_ShotScale / 2) * sinf(dir));
		}
		return wrapPos;
	}

	//雪玉の進行方向を向く
	Vec3 Player::PlayerWrapRot(Vec3 rot) {
		auto input = GetInputState();
		Vec3 wrapRot = rot;
		if (input.x != 0) {
			wrapRot = Vec3(rot.x, rot.y + (-XM_PIDIV2 * input.x) , rot.z);
		}
		return wrapRot;
	}

	//雪玉の発生位置を更新
	void Player::ShotPosUpdate() {
		m_ShotPosition = Vec3(
			(m_PlayerMoveCircleHalf + m_Scale.getX()/2) * cosf(m_Rad),	//半径＋弾（雪玉）の半径＊角度をつける
			m_Position.getY() - m_Scale.getX() + m_ShotScale / 2,
			(m_PlayerMoveCircleHalf + m_Scale.getX()/2) * sinf(m_Rad));
	}

	//雪玉のリセット
	void Player::ResetShotScale() {
		m_ShotScale = m_DEFAULTSHOTSCALE;
		m_Speed = m_DefSpeed;
		ShotPosUpdate();
	}

	//文字列の表示
	void Player::DrawStrings() {

		//文字列表示
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto rot = GetComponent<Transform>()->GetRotation();
		wstring rotationStr(L"Rotation:\t");
		rotationStr += L"X=" + Util::FloatToWStr(rot.x, 6, Util::FloatModify::Fixed) + L",\t";
		rotationStr += L"Y=" + Util::FloatToWStr(rot.y, 6, Util::FloatModify::Fixed) + L",\t";
		rotationStr += L"Z=" + Util::FloatToWStr(rot.z, 6, Util::FloatModify::Fixed) + L"\n";

		//wstring gravStr(L"GravityVelocoty:\t");
		//auto gravVelocity = GetComponent<Gravity>()->GetGravityVelocity();
		//gravStr += L"X=" + Util::FloatToWStr(gravVelocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		//gravStr += L"Y=" + Util::FloatToWStr(gravVelocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		//gravStr += L"Z=" + Util::FloatToWStr(gravVelocity.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring updatePerStr(L"UpdatePerformance:\t");
		updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		updatePerStr += L"\tmillisecond\n";

		wstring drawPerStr(L"DrawPerformance:\t");
		drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		drawPerStr += L"\tmillisecond\n";

		wstring collPerStr(L"CollisionPerform:\t");
		collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		collPerStr += L"\tmillisecond\n";

		wstring collMiscStr(L"ColMiscPerform:\t");
		collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		collMiscStr += L"\tmillisecond\n";

		wstring collTernCountStr(L"CollisionCountOfTern:\t");
		collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		collTernCountStr += L"\n";

		wstring inputStr(L"input:");
		inputStr += Util::FloatToWStr(GetInputState().x);
		inputStr += L"\n";

		wstring radStr(L"rad:");
		radStr += Util::FloatToWStr(GetRad());
		radStr += L"\n";

		wstring shotScaleStr(L"m_ShotScale:");
		shotScaleStr += Util::FloatToWStr(m_ShotScale);
		shotScaleStr += L"\n";

		wstring enemyCount(L"EnemyCount:");
		enemyCount += Util::IntToWStr((int)GetStage()->GetSharedObjectGroup(L"Enemy")->size());
		enemyCount += L"\n";

		wstring chestCount(L"ChestCount:");
		chestCount += Util::IntToWStr((int)GetStage()->GetSharedGameObject<Fort>(L"Fort")->GetChestCount());
		chestCount += L"\n";

		wstring str = fpsStr/* + positionStr + rotationStr + /*gravStr + updatePerStr + drawPerStr + collPerStr + collMiscStr
			+ collTernCountStr + inputStr + radStr */+ shotScaleStr /*+ enemyCount*/ + chestCount;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

}
//end basecross

