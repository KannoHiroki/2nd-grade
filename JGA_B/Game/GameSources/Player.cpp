/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	class GameManager
//	用途: 選択されているステージなどを把握しておく
//------------------------------------------------------------------------------------------
	GameManager* GameManager::GM = nullptr;

	GameManager* GameManager::GetGM() {
		if (GM == nullptr) {
			GM = new GameManager();
		}
		return GM;
	}

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Velocity(0)
	{
		auto gm = GameManager::GetGM();
		m_attackCombo = 0;
		m_tmpAttackCombo = 0;
		m_KnockBackVec = Vec3(0.0f);
		m_KnockBackSpeed = 0.3f;
		m_KnockBack.Time = 0.3f;
		m_KnockBack.FrameCount = 0.0f;
		m_jumpCoolDown = 15.0f;
		m_HP = 100;
		m_isAttack = false;
		m_attackComboTimer = gm->GetPlayerComboMaxTime();
		m_isDamegeCoolDown = true;
		m_nowEreaName = L"NONE";
	}

	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].fThumbLX != 0 || cntlVec[0].fThumbLY != 0) {
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();
				float moveLength = 0;	//動いた時のスピード
				auto ptrTransform = GetComponent<Transform>();
				auto ptrCamera = OnGetDrawCamera();
				//進行方向の向きを計算
				auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
				front.y = 0;
				front.normalize();
				//進行方向向きからの角度を算出
				float frontAngle = atan2(front.z, front.x);
				//コントローラの向き計算
				float moveX = cntlVec[0].fThumbLX;
				float moveZ = cntlVec[0].fThumbLY;
				Vec2 moveVec(moveX, moveZ);
				float moveSize = moveVec.length();
				//コントローラの向きから角度を計算
				float cntlAngle = atan2(-moveX, moveZ);
				//トータルの角度を算出
				float totalAngle = frontAngle + cntlAngle;
				//角度からベクトルを作成
				angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
				//正規化する
				angle.normalize();
				//移動サイズを設定。
				angle *= moveSize;
				//Y軸は変化させない
				angle.y = 0;
			}

		}
		return angle;
	}

	void Player::MovePlayer() {
		// プレイヤーの動く速さ
		const float playerSpeed = 6.0f;
		// SE流す時間のリミット
		const float SELimit = 0.7f;
		// SEボリューム
		const float SEVol = 0.45f;

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		Vec3 pos = Vec3(0);
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		m_timeSE += elapsedTime;
		if (angle.length() > 0.0f) {
			if (ptrDraw->GetCurrentAnimation() != L"Walk") {
				ChangeAnim(L"Walk");
			}
			pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * playerSpeed;
			GetComponent<Transform>()->SetPosition(pos);
			if (m_timeSE > SELimit) {
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Walk", 0, SEVol);
				m_timeSE = 0.0f;
			}
		}
		else if (ptrDraw->GetCurrentAnimation() != L"Idle"  && ptrDraw->GetCurrentAnimation() != L"Plant") {
			ChangeAnim(L"Idle");
		}
		else if (ptrDraw->GetCurrentAnimation() == L"Plant" && ptrDraw->IsTargetAnimeEnd() == true) {
			ChangeAnim(L"Idle");
		}
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
		m_moveVec = angle;

	}


	void Player::AttackMove() {
		const float playerMoveSpeed = 0.6f;
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		Vec3 pos = Vec3(0);
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (angle.length() > 0.0f) {
			pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * playerMoveSpeed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (ptrDraw->IsTargetAnimeEnd()) {
			//回転の計算
			if (angle.length() > 0.0f) {
				auto utilPtr = GetBehavior<UtilBehavior>();
				angle.y *= -1.0f;
				utilPtr->RotToHead(angle, 1.0f);
			}
		}
		m_moveVec = angle;
	}
	//初期化
	void Player::OnCreate() {

		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.5f, 3.0f, 0.5f);
		ptr->SetRotation(0.0f, XM_PIDIV2 * -1.0f, 0.0f);
		ptr->SetPosition(0, 130.0f, 0);

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(1.0f, 0.18f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\Attack3.efk";
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"PLAYER_MESH");
		//描画するテクスチャを設定
		//ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
		ptrDraw->SetTextureResource(L"PLAYER_TX");

		AddTag(L"Player");
		SetDrawLayer(100);
		ptrDraw->SetMeshToTransformMatrix(SpanMat);
		
		auto &bones = ptrDraw->GetVecLocalBones();

		//ステートマシンの構築
		m_StateMachine.reset(new LayeredStateMachine<Player>(GetThis<Player>()));
		//最初のステートをPlayerDefaultにリセット
		m_StateMachine->Reset(PlayerDefaultState::Instance());
		m_StateMachine->Push(PlayerDefaultState::Instance());
		//ステートのスタック上限
		m_StateMachine->SetMaxStack(30);
		// アニメーション
		ptrDraw->AddAnimation(L"Idle", 310, 31,true, 10.0f);
		ptrDraw->AddAnimation(L"Walk", 0, 41, true, 30.0f);
		ptrDraw->AddAnimation(L"Attack1", 60, 30, false, 60.0f);
		ptrDraw->AddAnimation(L"Attack2", 90, 35, false, 60.0f);
		ptrDraw->AddAnimation(L"Attack3", 125, 56, false, 60.0f);
		ptrDraw->AddAnimation(L"Damage", 485, 30, false, 30.0f);
		ptrDraw->AddAnimation(L"Plant", 590, 40, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Idle");


	}

	//更新
	void Player::OnUpdate() {
		auto gm = GameManager::GetGM();

		m_jumpCoolDown += App::GetApp()->GetElapsedTime();
		m_damageCoolDown += App::GetApp()->GetElapsedTime();
		if (m_damageCoolDown >= 1.7f) {
			m_isDamegeCoolDown = true;
		}
		else {
			m_isDamegeCoolDown = false;
		}
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (ptrDraw) {
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);
		}

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());

		//ステートマシン更新
		m_StateMachine->Update();
		
	}
	void Player::OnUpdate2() {
		//文字列の表示
		//DrawStrings();
	}

	//Aボタン
	void Player::OnPushA() {
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

		wstring gravStr(L"GravityVelocoty:\t");
		auto gravVelocity = GetComponent<Gravity>()->GetGravityVelocity();
		gravStr += L"X=" + Util::FloatToWStr(gravVelocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Y=" + Util::FloatToWStr(gravVelocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Z=" + Util::FloatToWStr(gravVelocity.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring animName(L"AnimationName:\t");
		auto NowEnemy = GameManager::GetGM()->GetNowEnemyNum();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		animName += ptrDraw->GetCurrentAnimation() + L"\t"+ Util::IntToWStr(NowEnemy) + L"\n";
		wstring greenPer(L"Percentage:\t");
		auto per = GameManager::GetGM()->GetGreenPer();
		greenPer += Util::FloatToWStr(per, 2, Util::FloatModify::Fixed) + L"%\t\n";

		auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(L"A");
		wstring plant(L"IsRun:\t");
		auto isRun = ptrPlant->GetIsRun();
		if (isRun) {
			plant += L"true\t IsMaxScale:\t";
		}
		else {
			plant += L"false\t IsMaxScale:\t";

		}
		if (ptrPlant->GetIsMaxCircleScale() == true) {
			plant += L"true\n";
		}
		else {
			plant += L"false\n";
		}

		wstring NowStateName(L"NowStateName:\t");
		NowStateName += GetNowStateName() + L"\n";

		auto ptrNum = GetStage()->GetSharedGameObject<ScoreSprite>(L"Number");
		wstring GreenPercent(L"Percent:\t");
		GreenPercent += Util::FloatToWStr(ptrNum->GetPercent(), 6, Util::FloatModify::Fixed) + L"\n";

		wstring EreaName(L"EreaName:\t");
		EreaName += m_nowEreaName + L"\n";

		wstring str = fpsStr + positionStr + gravStr + animName + greenPer + plant + NowStateName + GreenPercent + EreaName;


		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void Player::KnockBackBehaviour() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (m_KnockBack.FrameCount > m_KnockBack.Time) {
			m_KnockBack.FrameCount = 0.0f;
			ptrDraw->SetDrawActive(true);
			m_StateMachine->Reset(PlayerDefaultState::Instance());
			return;
		}
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(myPos + m_KnockBackVec * m_KnockBackSpeed);
		if (ptrDraw->GetDrawActive() == false) {
			ptrDraw->SetDrawActive(true);
		}
		else if (ptrDraw->GetDrawActive() == true) {
			ptrDraw->SetDrawActive(false);
		}
		if(ptrDraw->GetCurrentAnimation() != L"Damage"){
			ptrDraw->ChangeCurrentAnimation(L"Damage");
		}
		m_KnockBack.FrameCount += ElapsedTime;
	}

	void Player::DamageEffect() {



	}


	void Player::OnCollisionEnter(shared_ptr<GameObject>& Obj) {
		if (Obj->FindTag(L"Enemy")) {
			if (GetNowStateName() != L"KnockBackState" && m_isDamegeCoolDown == true) {
				VeloMake(Obj);
				Player::GetStateMachine()->Push(PlayerKnockBackState::Instance());
			}
		}
	}
	// アニメーションを変える関数
	void Player::ChangeAnim(wstring animName) {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(animName);
	}
	// コンボタイマー
	void Player::AttackComboTimer() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		// コンボが続く時間計測
		if (ptrDraw->IsTargetAnimeEnd()) {
			m_attackComboTimer -= App::GetApp()->GetElapsedTime();
			m_isAttack = false;
		}
		// 制限時間立ったらコンボリセット
		if (m_attackComboTimer < 0.0f) {
			m_attackCombo = 0;
			m_attackComboTimer = GameManager::GetGM()->GetPlayerComboMaxTime();
			Player::GetStateMachine()->Pop();

		}
	}

	// 攻撃の処理
	void Player::Attack() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_StateMachine->Push(PlayerAttackState::Instance());
			}
		}
	}
	
	void Player::AttackAnimPlay(int animNum) {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		wstring anim = L"Attack" + Util::IntToWStr(animNum);
		if (ptrDraw->GetCurrentAnimation() != anim && m_NowStateName== L"PlayerAttackState" && animNum != 0) {
			ChangeAnim(anim);
		}
	}

	void Player::VeloMake(shared_ptr<GameObject>& obj) {
		auto ptrEnemy = dynamic_pointer_cast<EnemyObject>(obj);
		auto enemyPos = ptrEnemy->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto velo = enemyPos - myPos;
		m_KnockBackVec = velo.normalize();
		m_KnockBackVec.x *= -1.0f;
		m_KnockBackVec.z *= -1.0f;
		m_KnockBackVec.y = 0.0f;
	}
	void Player::ComboCheck() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		AttackComboTimer();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
				m_isAttack = true;
				switch (m_attackCombo)
				{
				case 0:
					m_attackCombo += 1;
					AttackAnimPlay(m_attackCombo);

					break;
				case 1:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				case 2:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				case 3:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo = 0;
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	//プレイヤーのステート
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerDefaultState)
		void PlayerDefaultState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"DefaultState");
	}

	void PlayerDefaultState::Execute(const shared_ptr<Player>& Obj) {
		auto gm = GameManager::GetGM();
		if (gm->GetIsPlayerActive()) {
			Obj->MovePlayer();
		}
		Obj->Attack();
	}

	void PlayerDefaultState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	///	プレイヤーノックバックステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerKnockBackState)
		void PlayerKnockBackState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"KnockBackState");
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Start(L"PlayerDamage", 0, 1.0f);	
	}

	void PlayerKnockBackState::Execute(const shared_ptr<Player>& Obj) {
		Obj->KnockBackBehaviour();
		Obj->DamageEffect();
	}

	void PlayerKnockBackState::Exit(const shared_ptr<Player>& Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->SetDrawActive(true);
	}
	//--------------------------------------------------------------------------------------
	/// アタックステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerAttackState)
		void PlayerAttackState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"PlayerAttackState");
		Obj->SetCombo(1);
		Obj->AttackAnimPlay(Obj->GetCombo());
		Obj->SetIsAttack(true);
	}

	void PlayerAttackState::Execute(const shared_ptr<Player>& Obj) {
		Obj->AttackMove();
		Obj->ComboCheck();
		Obj->AttackComboTimer();
	}

	void PlayerAttackState::Exit(const shared_ptr<Player>& Obj) {
		Obj->SetIsAttack(false);
	}
	//---------------------------------------------------------------------
	/// プレイヤーの腕の当たり判定、攻撃時にだけアクティブに!!!!!
	//---------------------------------------------------------------------
	ArmCollision::ArmCollision(const shared_ptr<Stage>& Stage, const shared_ptr<Player>& ParentPtr, const wstring positionName, const int BoneNum,Vec3 &LocalPosition) :
		GameObject(Stage),
		m_parentPtr(ParentPtr),
		m_positionName(positionName),
		m_selectBoneNum(BoneNum),
		m_position(LocalPosition)
	{

	}

	void ArmCollision::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(1.5f));
		auto mesh = MeshResource::CreateCube(0.5f);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		ptrDraw->SetOriginalMeshResource(mesh);
		ptrDraw->SetOriginalMeshUse(true);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->AddExcludeCollisionTag(L"Player");
		ptrColl->AddExcludeCollisionTag(L"FixedBox");
		ptrColl->AddExcludeCollisionTag(L"Wall");
		ptrColl->AddExcludeCollisionTag(L"weapon");

		AddTag(L"weapon");
		ptrColl->SetAfterCollision(AfterCollision::None);
		SetDrawActive(false);
	}

	void ArmCollision::OnUpdate() {
		//CollActive();
		PositionSet();
	}
	void ArmCollision::PositionSet() {
		auto bonePtr = m_parentPtr;
		auto boneTrans = bonePtr->GetComponent<Transform>();
		auto boneDraw = bonePtr->GetComponent<PNTBoneModelDraw>();

		auto& bones = boneDraw->GetVecLocalBones();

		Mat4x4 mat = bones[m_selectBoneNum];
		auto mesh = boneDraw->GetMeshResource();
		vector<Vec3> positions;
		mesh->GetLocalPositions(positions);

		Mat4x4 localMat;
		Vec3 LocalPos(1.0f, 0.0f, 0.0f);


		localMat.translation(m_position);
		localMat *= mat;
		localMat *= boneTrans->GetWorldMatrix();

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(localMat.transInMatrix());
		auto Qt = localMat.quatInMatrix();
		ptrTrans->SetQuaternion(Qt);
	}
	void ArmCollision::CollActive() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto ptrColl = GetComponent<CollisionObb>();
		if (ptrPlayer->GetStateMachine()->GetTopState()->GetStateName() == L"PlayerAttackState") {
			ptrColl->SetAfterCollision(AfterCollision::Auto);
		}
		else {
			ptrColl->SetAfterCollision(AfterCollision::None);
		}
	}
}
//end basecross

