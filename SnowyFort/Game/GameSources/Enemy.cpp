/*!
@file Enemy.cpp
@brief 敵など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//---------------------------------------------------------------------------
	// 敵
	//---------------------------------------------------------------------------
	EnemyObject::EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position)
		: GameObject(Stage),
		m_position(position),
		m_rotation(Vec3(0)),
		m_scale(Vec3(0.2f))
	{
		m_moveSpeed = 0.3f;
		m_rad = 0.0f;
		m_searchDis = 3.0f;
		m_level = 3;
		m_stopTime = 4.0f;
		m_frameCount = 0.0f;
	}

	void EnemyObject::OnCreate()
	{
		// 初期設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		// 描画設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(false);
		//ptrDraw->SetTextureResource(L"ENEMY_TX");
		ptrDraw->SetMeshResource(L"ENEMY_MESH");
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));
		//透明処理
		SetAlphaActive(true);
		SetDrawActive(true);

		// コリジョン
		auto ptrColl = AddComponent<CollisionSphere>();
		
		auto ptrGra = AddComponent<Gravity>();

		AddTag(L"Enemy");

		// ステートマシン
		m_stateMachine.reset(new LayeredStateMachine<EnemyObject>(GetThis<EnemyObject>()));
		m_stateMachine->Reset(EnemyDefaultState::Instance());

		//アニメーション,
		ptrDraw->AddAnimation(L"Walk", 0, 30, true, 30.0f);
		ChangeAnimation(L"Walk");
		
		//影
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void EnemyObject::OnUpdate()
	{
		m_stateMachine->Update();
		ActionPosLimit();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elpasedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elpasedTime);
		SetDrawActive(true);
	}
	
	void EnemyObject::MoveEnemy()
	{
		auto eTime = App::GetApp()->GetElapsedTime();

		m_targetObject = GetStage()->GetSharedGameObject<Fort>(L"Fort");
		auto targetPos = m_targetObject->GetComponent<Transform>()->GetPosition();

		auto myPos = GetComponent<Transform>()->GetPosition();

		Vec3 velo = targetPos - myPos;
		velo.normalize();
		m_velo = velo;

		myPos += m_velo * eTime * m_moveSpeed;

		this->GetComponent<Transform>()->SetPosition(myPos);

		auto ptrUtil = GetBehavior<UtilBehavior>();
		if (m_velo.length() > 0) {
			ptrUtil->RotToHead(m_velo * -1.0f, 1.0f);
		}

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto animName = ptrDraw->GetCurrentAnimation();
		if (animName != L"Walk") {
			ChangeAnimation(L"Walk");
		}
	}
	
	void EnemyObject::ActionPosLimit() {
		auto transComp = GetComponent<Transform>();

		//ステージ外に出たら消す
		if (transComp->GetPosition().y < -15.0f) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}

	/*void EnemyObject::AttackToPlayer()
	{
		Vec3 pos = GetComponent<Transform>()->GetPosition();
		pos.y += 1.0f;
		Vec3 rot = GetComponent<Transform>()->GetRotation();

		GetStage()->AddGameObject<Bullet>(pos, rot, Vec3(-1.0f,1.0f,-1.0f));
	}*/

	void EnemyObject::SearchObject()
	{
		//自分のポジション
		auto myPos = GetComponent<Transform>()->GetPosition();
		//プレイヤーの情報・ポジションをとってくる
		auto ptrB_Enemy = GetStage()->GetSharedGameObject<BigEnemyObject>(L"Enemy");
		auto B_EnemyPos = ptrB_Enemy->GetComponent<Transform>()->GetPosition();

		//方向

		//距離を出す
		float length = (B_EnemyPos - myPos).length();

		if ( length > m_searchDis && GetStateName() == L"EnemyDefaultState")
		{
			//m_stateMachine->Push();
		}
		else
		{
			//AttackToPlayer();
			m_stateMachine->Pop();
		}
		
	}

	void EnemyObject::ChangeAnimation(wstring animName)
	{
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(animName);
	}

	void EnemyObject::Action()
	{
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto bulletGroup = GetStage()->GetSharedObjectGroup(L"Bullet")->GetGroupVector();
		for (auto v : bulletGroup) {
			auto bulletPos = v.lock()->GetComponent<Transform>()->GetPosition();

			auto length = (myPos - bulletPos).length();

			if (length < 3.0f && myPos.y > bulletPos.y) {
				Impatience();
			}			
		}
	}

	void EnemyObject::Impatience()
	{
		ChangeAnimation(L"Stop");
		m_frameCount += App::GetApp()->GetElapsedTime();

		if (m_stopTime > m_frameCount)
		{
			auto ptrTrans = GetComponent<Transform>();
			auto myPos = ptrTrans->GetPosition();

			ptrTrans->SetPosition(myPos);
		}else {
			m_frameCount = 0.0f;
			m_stateMachine->Pop();
		}
	}

	void EnemyObject::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Bullet")) 
		{
			//死亡判定用処理
			//ChangeAnimation(L"Die");
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"ENEMY_KILL_SE", 0, 1.0);
			GetStage()->RemoveGameObject<EnemyObject>(GetThis<EnemyObject>());
		}

		if (other->FindTag(L"Fort"))
		{
			auto ptrFort = GetStage()->GetSharedGameObject<Fort>(L"Fort");
			ptrFort->ReduceChest();
			GetStage()->RemoveGameObject<EnemyObject>(GetThis<EnemyObject>());	
			
		}
	}

	//---------------------------------------------------------------------------
	// Enemy通常ステート
	//---------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(EnemyDefaultState)
		void EnemyDefaultState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}

	void EnemyDefaultState::Execute(const shared_ptr<EnemyObject>& Obj) {
			Obj->MoveEnemy();
	}

	void EnemyDefaultState::Exit(const shared_ptr<EnemyObject>& Obj) {

	}
	//---------------------------------------------------------------------------
	// Enemyの感情に変化があった時のステート
	//---------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(EnemyFeelState)
		void EnemyFeelState::Enter(const shared_ptr<EnemyObject>& Obj) {
	}

	void EnemyFeelState::Execute(const shared_ptr<EnemyObject>& Obj) {
		//Obj->MoveEnemy();
	}

	void EnemyFeelState::Exit(const shared_ptr<EnemyObject>& Obj) {

	}

	//---------------------------------------------------------------------------
	// 大きい敵
	//---------------------------------------------------------------------------
	BigEnemyObject::BigEnemyObject(shared_ptr<Stage>&stage, const Vec3 position)
		: GameObject(stage),
		m_position(position)
	{
		m_rotation = Vec3(0);
		m_scale = Vec3(1.0f);
		m_level = 3;
		m_moveSpeed = 0.1f;
		m_HP = 10;
	}

	void BigEnemyObject::OnCreate()
	{
		// 初期設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		// 描画設定
		auto ptrDraw = AddComponent<BcPNTBoneModelDraw>();
		ptrDraw->SetFogEnabled(false);
		ptrDraw->SetMeshResource(L"BIG_ENEMY_MESH");
		ptrDraw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));
		//透明処理
		SetAlphaActive(true);
		SetDrawActive(true);

		// コリジョン
		auto ptrColl = AddComponent<CollisionObb>();

		auto ptrGra = AddComponent<Gravity>();

		AddTag(L"BigEnemy");

		// ステートマシン
		//m_stateMachine.reset(new LayeredStateMachine<BigEnemyObject>(GetThis<BigEnemyObject>()));
		//m_stateMachine->Reset(EnemyDefaultState::Instance());

		//アニメーション,
		ptrDraw->AddAnimation(L"Walk", 0, 30, true, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Walk");

		//影
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
	}

	void BigEnemyObject::OnUpdate()
	{
		MoveEnemy();
		ActionPosLimit();

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		float elpasedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elpasedTime);
		SetDrawActive(true);
	}

	void BigEnemyObject::MoveEnemy()
	{
		auto eTime = App::GetApp()->GetElapsedTime();

		m_targetObject = GetStage()->GetSharedGameObject<Fort>(L"Fort");
		auto targetPos = m_targetObject->GetComponent<Transform>()->GetPosition();

		auto myPos = GetComponent<Transform>()->GetPosition();

		Vec3 velo = targetPos - myPos;
		velo.normalize();
		m_velo = velo;

		myPos += m_velo * eTime * m_moveSpeed;

		this->GetComponent<Transform>()->SetPosition(myPos);

		auto ptrUtil = GetBehavior<UtilBehavior>();
		if (m_velo.length() > 0) {
			ptrUtil->RotToHead(m_velo * -1.0f, 1.0f);
		}

		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto animName = ptrDraw->GetCurrentAnimation();
		if (animName != L"Walk") {
			ptrDraw->ChangeCurrentAnimation(L"Walk");
		}
	}

	void BigEnemyObject::ActionPosLimit() {
		auto transComp = GetComponent<Transform>();

		//ステージ外に出たら消す
		if (transComp->GetPosition().y < -15.0f) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}

	void BigEnemyObject::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Bullet"))
		{
			//死亡判定用処理
			if (m_HP <= 0) {
				//ChangeAnimation(L"Die");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"ENEMY_KILL_SE", 0, 1.0);
				GetStage()->RemoveGameObject<BigEnemyObject>(GetThis<BigEnemyObject>());
			}
		}

		if (other->FindTag(L"Fort"))
		{
			auto ptrFort = GetStage()->GetSharedGameObject<Fort>(L"Fort");
			ptrFort->ReduceChest();
			GetStage()->RemoveGameObject<BigEnemyObject>(GetThis<BigEnemyObject>());

		}
	}

	//---------------------------------------------------------------------------
	// 敵が打ってくる矢
	//---------------------------------------------------------------------------
	/*Bullet::Bullet(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 velo)
		: GameObject(Stage),m_position(position),m_rotation(rotation),m_velo(velo)
	{
		m_scale = Vec3(0.25f, 0.25f, 0.25f);
		m_moveSpeed = 0.5f;
	}

	void Bullet::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrColl = AddComponent<CollisionObb>();
		
		auto ptrGra = AddComponent<Gravity>();
		
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
		GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
	}*/
}
//end basecross
