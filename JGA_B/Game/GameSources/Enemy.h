#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	敵
	//--------------------------------------------------------------------------------------
	class EnemyObject : public GameObject {
		Vec3 m_rotVec;
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_searchDis;
		float m_moveSpeed;
		float m_rad; //移動用角度

		bool m_enemyStop;
		float m_stopTime;

		int m_HP;


		bool m_isAddScale;
		// ノックバック関連
		float m_knockBackTime;
		float m_knockBackFrameCount;
		float m_knockBackSpeed;
		Vec3 m_knockBackVelo;
		bool m_knockBackFlg;

		Vec3 m_moveForce;
		Vec3 m_moveVelo;

		bool m_isUpdate;
		unique_ptr<LayeredStateMachine<EnemyObject>> m_stateMachine;

		shared_ptr<SoundItem> m_audioObject;
		wstring m_playSEName;
		bool m_isDeath;
		wstring m_districtName;
		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		shared_ptr<EfkEffect> m_EfkGreenOut;
		//エフェクト実行プロジェクト
		shared_ptr<EfkPlay> m_EfkPlay;
		shared_ptr<EfkPlay> m_EfkPlay2;


	public:
		EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName);
		virtual ~EnemyObject() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		// プレイヤーを探す
		virtual void PlayerSearch();
		// プレイヤーを追いかける
		virtual void AttackToPlayer();
		// プレイヤーに攻撃した際の硬直
		void AttackDelay();
		// ノックバックする方向を求める
		void KnockBackVeloMake(shared_ptr<GameObject> Obj);
		// プレイヤーに攻撃されたときのノックバック
		void KnockBack();
		// 自分が死んだか死んでないかの確認
		void DeathCheacker();
		//通常時の移動
		void MoveEnemy();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		void GreenChecker();
		//ノックバックフラグ
		bool GetKnockBackFlg() {
			return m_knockBackFlg;
		}

		wstring GetStateName() {
			return m_stateMachine->GetTopState()->GetStateName();
		}
		unique_ptr<LayeredStateMachine<EnemyObject>>& GetStateMachine() {
			return m_stateMachine;
		}
		bool GetIsUpdate() {
			return m_isUpdate;
		}
		void SetIsUpdate(bool b) {
			m_isUpdate = b;
		}
		void RotateHead();
		void ChangeAnimation(wstring animName);

		bool GetIsDeath() {
			return m_isDeath;
		}
		bool GetIsAddScale() {
			return m_isAddScale;
		}
	};

	//--------------------------------------------------------------------------------------	
	///	ゴブリンソード
	//--------------------------------------------------------------------------------------
	class EnemySword :public GameObject {
		Vec3 m_pos;
		shared_ptr<EnemyObject> m_weaponOwner;
	public:
		EnemySword(shared_ptr<Stage> &stage, shared_ptr<EnemyObject> &obj);
		virtual ~EnemySword() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void ChangeAnimation(wstring animName);
		void PositionSetting();
		void AnimMatch();
		void DeathCheck();
	};
	//エネミーのステート
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	class EnemyDefaultState : public ObjState<EnemyObject>
	{
		EnemyDefaultState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(EnemyDefaultState)
		virtual wstring GetStateName()const { return L"EnemyDefaultState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};
	//--------------------------------------------------------------------------------------	
	///	プレイヤーを追いかけるステート
	//--------------------------------------------------------------------------------------
	class EnemyPlayerChaseState : public ObjState<EnemyObject>
	{
		EnemyPlayerChaseState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(EnemyPlayerChaseState)
		virtual wstring GetStateName()const { return L"EnemyPlayerChaseState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};
	//--------------------------------------------------------------------------------------	
	///	ノックバックステート
	//--------------------------------------------------------------------------------------
	class EnemyKnockBackState : public ObjState<EnemyObject>
	{
		EnemyKnockBackState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(EnemyKnockBackState)
		virtual wstring GetStateName()const { return L"EnemyKnockBackState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//　遠距離攻撃してくる敵
	//--------------------------------------------------------------------------------------

	class LongDisEnemyObject : public EnemyObject{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_interval; //攻撃のインターバル
		float m_elapsedTime; //経過時間
		float m_searchDis; //攻撃範囲
		float m_moveSpeed;
	public:
		LongDisEnemyObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale,const wstring DistrictName);
		~LongDisEnemyObject() {};
		void OnCreate() override;
		void OnUpdate() override;
		void AttackToPlayer() override;
		void PlayerSearch() override;
	};

	//--------------------------------------------------------------------------------------
	//　遠距離の敵が飛ばす弾
	//--------------------------------------------------------------------------------------

	class Bullet : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec3 m_velo;
		float m_moveSpeed;
		int m_damage;
	public :
		Bullet(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 velo,int damage);
		~Bullet() {};
		void OnCreate() override;
		void OnUpdate() override;
		void MoveBullet();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};

	//--------------------------------------------------------------------------------------
	//　中ボス
	//--------------------------------------------------------------------------------------
	class MidBossObject : public EnemyObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_searchDis;
		float m_moveSpeed;

		bool m_enemyStop;
		float m_stopTime;
	public:
		MidBossObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName);
		virtual ~MidBossObject() {};
		void OnCreate()override;
		void OnUpdate()override;
		//void PlayerSearch();

		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

	//--------------------------------------------------------------------------------------
	//　ボス
	//--------------------------------------------------------------------------------------
	class BossObject : public EnemyObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_searchDis;
		float m_moveSpeed;

		bool m_enemyStop;
		float m_stopTime;
	public:
		BossObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale , const wstring DistrictName);
		virtual ~BossObject() {};
		void OnCreate()override;
		void OnUpdate()override;
		//void PlayerSearch()override;

		//virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

	};

}