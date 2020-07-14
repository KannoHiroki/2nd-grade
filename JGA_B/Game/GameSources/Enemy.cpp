#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	敵
	//--------------------------------------------------------------------------------------
	EnemyObject::EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName)
		:GameObject(Stage),
		m_position(position),
		m_rotation(rotation),
		m_scale(scale),
		m_districtName(DistrictName)
	{
		m_enemyStop = true;
		m_stopTime = 0.0f;
		m_HP = 60;
		m_searchDis = 30.0f;
		m_moveSpeed = 0.025f;
		m_knockBackTime = 0.4f;
		m_knockBackSpeed = 15.0f;
		m_knockBackVelo = Vec3(0);
		m_knockBackFlg = false;
		m_moveForce = Vec3(0);
		m_moveVelo = Vec3(0);
		m_isUpdate = true;
		m_isDeath = false;
		m_isAddScale = false;
	}

	void EnemyObject::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotation);
		//衝突判定をつける
		auto ptrColl = AddComponent<CollisionSphere>();
		//ptrColl->SetDrawActive(true);
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetMeshResource(L"GOBLINSWORD_MESH");
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));
		//ptrDraw->SetTextureResource(L"GOBLIN_TX");
		//透明処理をする
		SetAlphaActive(true);
		SetDrawActive(true);
		AddTag(L"Enemy");
		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);


		m_stateMachine.reset(new LayeredStateMachine<EnemyObject>(GetThis<EnemyObject>()));
		m_stateMachine->Reset(EnemyDefaultState::Instance());
		SetDrawLayer(100);
		//アニメーション
		ptrDraw->AddAnimation(L"Idle", 0, 60, true, 30.0f);
		ptrDraw->AddAnimation(L"Die", 70, 30, false, 30.0f);
		ptrDraw->AddAnimation(L"Damage", 110, 20, false, 30.0f);
		ptrDraw->AddAnimation(L"Attack", 140, 75, false, 60.0f);
		ptrDraw->AddAnimation(L"Walk", 220, 60, true, 60.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
	}
	void EnemyObject::OnUpdate() {
		//DrawDisCheck();
		if (m_isUpdate == true) {
			m_stateMachine->Update();
		}
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elpasedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elpasedTime);
		SetDrawActive(true);
	}

	void EnemyObject::PlayerSearch() {
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto length = (playerPos - myPos).length();

		auto ptrTrans = GetComponent<Transform>();
		if (m_searchDis > length && GetStateName() == L"EnemyDefaultState") {
			m_stateMachine->Push(EnemyPlayerChaseState::Instance());
			return;
		}
		else if (m_searchDis < length &&GetStateName() == L"EnemyPlayerChaseState") {
			m_stateMachine->Pop();
			return;
		}
	}
	void EnemyObject::AttackDelay() {
		if (m_enemyStop == false) {
			m_stopTime += App::GetApp()->GetElapsedTime();
			m_moveSpeed = 0;

		}
		if (m_enemyStop == false && m_stopTime > 1.5f) {
			m_enemyStop = true;
			m_stopTime = 0.0f;
			m_moveSpeed = GameManager::GetGM()->GetEnemySpeed();
		}
	}

	void EnemyObject::AttackToPlayer() {
		const float speed = 15.0f;
		m_moveForce.setAll(0);
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrArrive = GetBehavior<ArriveSteering>();
		m_moveForce = ptrArrive->Execute(m_moveForce, m_moveVelo, playerPos);
		m_moveVelo = m_moveForce * ElapsedTime;
		auto myPos = GetComponent<Transform>()->GetPosition();
		myPos += m_moveVelo * ElapsedTime * speed;
		GetComponent<Transform>()->SetPosition(myPos);

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto animName = ptrDraw->GetCurrentAnimation();
		if (animName != L"Walk" && animName != L"Attack") {
			ptrDraw->ChangeCurrentAnimation(L"Walk");
		}
		else if (animName == L"Attack" && ptrDraw->IsTargetAnimeEnd() == true) {
			ptrDraw->ChangeCurrentAnimation(L"Walk");
		}
	}


	void EnemyObject::KnockBackVeloMake(shared_ptr<GameObject> Obj) {
		const float reverse = -1.0f;
		const int damage = 20;
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		if (ptrPlayer->GetIsAttack() == true) {
			if (Obj->FindTag(L"weapon")) {
				auto ptrTrans = GetComponent<Transform>();
				auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
				auto myPos = GetComponent<Transform>()->GetPosition();
				auto velo = playerPos - myPos;
				m_knockBackVelo = velo.normalize();
				m_knockBackVelo.x *= reverse;
				m_knockBackVelo.z *= reverse;


				if (GetStateName() != L"EnemyKnockBackState") {
					m_HP -= damage;
					GetStateMachine()->Push(EnemyKnockBackState::Instance());
					return;
				}
			}

			if (Obj->FindTag(L"Enemy")) {
				auto ptrTrans = GetComponent<Transform>();
				auto ptrEnemy = dynamic_pointer_cast<EnemyObject>(Obj);
				if (ptrEnemy->GetKnockBackFlg()) {
					auto targetEnemyPos = Obj->GetComponent<Transform>()->GetPosition();
					auto myPos = GetComponent<Transform>()->GetPosition();
					auto velo = targetEnemyPos - myPos;
					m_knockBackVelo = velo.normalize();
					m_knockBackVelo.x *= reverse;
					m_knockBackVelo.z *= reverse;

					if (GetStateName() != L"EnemyKnockBackState") {
						m_HP -= damage;
						GetStateMachine()->Push(EnemyKnockBackState::Instance());
						return;
					}
				}
			}
		}
	}
	void EnemyObject::RotateHead() {
		auto UtilPtr = GetBehavior<UtilBehavior>();
		if (GetStateName() == L"EnemyPlayerChaseState") {
			if (m_moveVelo.length() > 0) {
				UtilPtr->RotToHead(m_moveVelo*-1.0f, 1.0f);
			}
		}
		if (GetStateName() == L"EnemyDefaultState") {
			if (m_rotVec.length() > 0) {
				UtilPtr->RotToHead(m_rotVec*-1.0f, 1.0f);
			}

		}
	}
	void EnemyObject::KnockBack() {
		float elpasedTime = App::GetApp()->GetElapsedTime();
		m_knockBackFrameCount += elpasedTime;
		if (m_knockBackTime > m_knockBackFrameCount) {
			m_knockBackFlg = true;
			auto ptrTrans = GetComponent<Transform>();
			auto myPos = ptrTrans->GetPosition();
			ptrTrans->SetPosition(myPos.x + (m_knockBackVelo.x*elpasedTime * m_knockBackSpeed), myPos.y, myPos.z + (m_knockBackVelo.z*elpasedTime* m_knockBackSpeed));
			auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
			auto animName = ptrDraw->GetCurrentAnimation();
			if (animName != L"Die") {
				ptrDraw->ChangeCurrentAnimation(L"Die");
			}
		}
		else {
			m_knockBackFrameCount = 0.0f;
			m_knockBackVelo = Vec3(0);
			m_knockBackFlg = false;
			GetStateMachine()->Pop();
		}
	}

	void EnemyObject::DeathCheacker() {
		const float SEVolume = 0.4f;
		GreenChecker();
		if (m_HP <= 0) {
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			auto myPos = GetComponent<Transform>()->GetPosition();
			auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(m_districtName);
			auto gm = GameManager::GetGM();
			auto ptrCircle = ptrPlant->GetMyGreenCircle();
			auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
			if (ptrDraw->GetCurrentAnimation() != L"Die") {
				ChangeAnimation(L"Die");
			}

			if (ptrDraw->IsTargetAnimeEnd() == true) {
				if (ptrPlant->GetIsRun() == true && ptrPlant->GetIsMaxCircleScale() == false && m_isAddScale == false) {
					ptrCircle.lock()->AddScale(Vec2(gm->GetAddScaleValue(), gm->GetAddScaleValue()));
					if (ptrPlant->GetIsMaxCircleScale() == false) {
						GetStage()->AddGameObject<EffectPlayObj>(myPos, L"GreenOut.efk");
						GetStage()->AddGameObject<EffectPlayObj>(ptrPlant->GetComponent<Transform>()->GetPosition(), L"GreenIn.efk");
						m_playSEName = L"塗る2_WAV";
						m_audioObject = ptrXA->Start(m_playSEName, 0, SEVolume);
					}
					m_isAddScale = true;
				}
				else if (ptrPlant->GetIsMaxCircleScale() == true && m_isAddScale == false) {
					m_isAddScale = true;
				}
			}

			m_isDeath = true;
		}
	}

	void EnemyObject::MoveEnemy() {
		m_rad += App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		Vec3 velo(sinf(m_rad), 0.0f, cosf(m_rad));
		velo.normalize();
		m_rotVec = velo * m_moveSpeed;
		myPos += m_rotVec;
		ptrTrans->SetPosition(myPos);

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto animName = ptrDraw->GetCurrentAnimation();
		if (animName != L"Walk") {
			ptrDraw->ChangeCurrentAnimation(L"Walk");
		}
	}

	void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& other) {
		const int damage = 10;
		if (other->FindTag(L"Player") && m_knockBackFlg == false) {
			m_enemyStop = false;
			auto ptrPlayer = dynamic_pointer_cast<Player>(other);
			ptrPlayer->DamageToPlayer(damage);
			ChangeAnimation(L"Attack");
		}
		KnockBackVeloMake(other);
	}

	void EnemyObject::ChangeAnimation(wstring animName) {
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(animName);
	}
	void EnemyObject::GreenChecker() {
		auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(m_districtName);
		if (ptrPlant->GetIsMaxCircleScale() == true) {
			m_HP = 0;
		}
	}
	//--------------------------------------------------------------------------------------
	//	ゴブリンソード
	//--------------------------------------------------------------------------------------
	EnemySword::EnemySword(shared_ptr<Stage> &stage, shared_ptr<EnemyObject> &obj)
		:GameObject(stage),
		m_weaponOwner(obj)
	{

	}

	void EnemySword::OnCreate() {
		auto ptrOwnerTrans = m_weaponOwner->GetComponent<Transform>();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(ptrOwnerTrans->GetPosition());
		ptrTrans->SetRotation(ptrOwnerTrans->GetRotation());
		ptrTrans->SetScale(ptrOwnerTrans->GetScale());

		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"SWORD_MESH");
		ptrDraw->SetTextureResource(L"SWORD_TX");
		//アニメーション
		ptrDraw->AddAnimation(L"Idle", 0, 60, true, 30.0f);
		ptrDraw->AddAnimation(L"Die", 70, 30, false, 60.0f);
		ptrDraw->AddAnimation(L"Damage", 110, 20, false, 30.0f);
		ptrDraw->AddAnimation(L"Attack", 140, 75, false, 60.0f);
		ptrDraw->AddAnimation(L"Walk", 220, 60, true, 60.0f);
		ptrDraw->ChangeCurrentAnimation(L"Idle");
		SetDrawLayer(100);

	}

	void EnemySword::OnUpdate() {
		DeathCheck();
		GetComponent<BcPNTBoneModelDraw>()->UpdateAnimation(App::GetApp()->GetElapsedTime());
		AnimMatch();
		PositionSetting();

	}
	void EnemySword::ChangeAnimation(wstring animName) {
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(animName);
	}

	void EnemySword::PositionSetting() {
		auto ptrOwnerTrans = m_weaponOwner->GetComponent<Transform>();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(ptrOwnerTrans->GetPosition());
		ptrTrans->SetQuaternion(ptrOwnerTrans->GetQuaternion());
	}

	void EnemySword::AnimMatch() {
		auto ptrOwnerDraw = m_weaponOwner->GetComponent<BcPNTBoneModelDraw>();
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		if (ptrOwnerDraw->GetCurrentAnimation() != ptrDraw->GetCurrentAnimation()) {
			ChangeAnimation(ptrOwnerDraw->GetCurrentAnimation());
		}
	}

	void EnemySword::DeathCheck() {
		auto ptrOenerDraw = m_weaponOwner->GetComponent<BcPNTBoneModelDraw>();
		if (m_weaponOwner->GetIsDeath() == true) {
			SetDrawActive(false);
		}
		if (m_weaponOwner->GetIsDeath() == true && m_weaponOwner->GetIsAddScale()) {

			GameManager::GetGM()->SetNowEnemyNum(GameManager::GetGM()->GetNowEnemyNum() - 1);
			GetStage()->RemoveGameObject<EnemyObject>(m_weaponOwner);
			GetStage()->RemoveGameObject<EnemySword>(GetThis<EnemySword>());

		}

	}

	//エネミーのステート
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(EnemyDefaultState)
		void EnemyDefaultState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}

	void EnemyDefaultState::Execute(const shared_ptr<EnemyObject>& Obj) {
		if (Obj->GetIsDeath() == false) {
			Obj->MoveEnemy();
			Obj->PlayerSearch();
			Obj->AttackDelay();
			Obj->RotateHead();
		}
		Obj->DeathCheacker();
	}

	void EnemyDefaultState::Exit(const shared_ptr<EnemyObject>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	///	プレイヤーを追いかけるステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(EnemyPlayerChaseState)
		void EnemyPlayerChaseState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}

	void EnemyPlayerChaseState::Execute(const shared_ptr<EnemyObject>& Obj) {
		if (Obj->GetIsDeath() == false) {
			Obj->PlayerSearch();
			Obj->AttackToPlayer();
			Obj->RotateHead();
			Obj->AttackDelay();
		}
		Obj->DeathCheacker();
	}

	void EnemyPlayerChaseState::Exit(const shared_ptr<EnemyObject>& Obj) {

	}
	//--------------------------------------------------------------------------------------
	///	ノックバックステート
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(EnemyKnockBackState)
		void EnemyKnockBackState::Enter(const shared_ptr<EnemyObject>& Obj) {
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Start(L"Attack1", 0, 0.9f);
		auto pos = Obj->GetComponent<Transform>()->GetPosition();
		Obj->GetStage()->AddGameObject<EffectPlayObj>(pos, L"damageEfk.efk");
	}
	void EnemyKnockBackState::Execute(const shared_ptr<EnemyObject>& Obj) {
		Obj->KnockBack();

	}
	void EnemyKnockBackState::Exit(const shared_ptr<EnemyObject>& Obj) {
		Obj->DeathCheacker();
	}

	//--------------------------------------------------------------------------------------
	//　遠距離攻撃してくる敵
	//--------------------------------------------------------------------------------------
	LongDisEnemyObject::LongDisEnemyObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName)
		: EnemyObject(Stage,position,rotation,scale,DistrictName),
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{
		m_interval = 5.0f;
		m_elapsedTime = 0.0f;
		m_searchDis = 15.0f;
		m_moveSpeed = 0.025f;
	}

	void LongDisEnemyObject::OnCreate() 
	{
		EnemyObject::OnCreate();
	}

	void LongDisEnemyObject::OnUpdate()
	{
		EnemyObject::OnUpdate();
	}

	void LongDisEnemyObject::AttackToPlayer()
	{
		m_elapsedTime += App::GetApp()->GetElapsedTime();
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		float length = (playerPos - myPos).length();
		Vec3 velo = (playerPos - myPos);
		velo.y = 2.0f;
		velo.normalize();
		
		if (m_searchDis > length) {
			if (m_elapsedTime > m_interval) {
				myPos.y = 2.0f;
				int damage = 0;
				for (int i = 0; i < 5; i++) {
					if (length > 3.0f * float(i + 1)) {
						damage = i + 1;
					}
				}
				if (damage == 0) {
					damage = 1;
				}
				GetStage()->AddGameObject<Bullet>(myPos, velo, damage);
				m_elapsedTime = 0.0f;

			}
		}	
	}

	void LongDisEnemyObject::PlayerSearch()
	{
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto length = (playerPos - myPos).length();

		auto ptrTrans = GetComponent<Transform>();
		if (m_searchDis > length && GetStateName() == L"EnemyDefaultState") {
			EnemyObject::GetStateMachine()->Push(EnemyPlayerChaseState::Instance());
			return;
		}
		else if (m_searchDis < length &&GetStateName() == L"EnemyPlayerChaseState") {
			EnemyObject::GetStateMachine()->Pop();
			return;
		}
	}

	//--------------------------------------------------------------------------------------
	//　遠距離の敵が飛ばす弾
	//--------------------------------------------------------------------------------------

	Bullet::Bullet(shared_ptr<Stage>& Stage, const Vec3 position,const Vec3 velo, int damage)
		: GameObject(Stage), m_position(position), m_velo(velo),m_damage(damage)
	{
		m_rotation = Vec3(0, 0, 0);
		m_scale = Vec3(0.25f, 0.25f, 0.25f);
		m_moveSpeed = 0.25f;
	}
	void Bullet::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);
		//形状
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//コリジョン
		auto ptrColl = AddComponent<CollisionObb>();
		//重力
		auto ptrGra = AddComponent<Gravity>();
		//影
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		MoveBullet();
	}

	void Bullet::MoveBullet()
	{
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(myPos + m_velo * m_moveSpeed);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Player")) {
			auto ptrPlayer = dynamic_pointer_cast<Player>(other);
			ptrPlayer->DamageToPlayer(m_damage);
		}
		if (!other->FindTag(L"Enemy")) {
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}
	}

	//--------------------------------------------------------------------------------------
	//　中ボス
	//--------------------------------------------------------------------------------------
	MidBossObject::MidBossObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName)
		:EnemyObject(Stage,position,rotation,scale,DistrictName),
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{
		m_enemyStop = true;
		m_stopTime = 0.0f;

		m_searchDis = 6.0f;
		m_moveSpeed = 0.025f;
	}

	void MidBossObject::OnCreate() {
		EnemyObject::OnCreate();
		auto playerScale = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(playerScale / 2);
	}

	void MidBossObject::OnUpdate() {
		EnemyObject::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//　ボス
	//--------------------------------------------------------------------------------------
	BossObject::BossObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName)
		:EnemyObject(Stage, position, rotation, scale, DistrictName),
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{
		m_enemyStop = true;
		m_stopTime = 0.0f;

		m_searchDis = 6.0f;
		m_moveSpeed = 0.025f;
	}

	void BossObject::OnCreate() {
		EnemyObject::OnCreate();
		auto playerScale = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(playerScale);
	}

	void BossObject::OnUpdate() {
		EnemyObject::OnUpdate();

	}

}