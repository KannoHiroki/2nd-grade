/*!
@file Enemy.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//---------------------------------------------------------------------------
	// 敵
	//---------------------------------------------------------------------------
	class EnemyObject : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		
		float m_moveSpeed; // 移動スピード
		float m_rad; // 移動用角度
		float m_searchDis; // 攻撃を始める距離
		Vec3 m_velo; // 方向
		int m_level; // 強さ
		bool m_enemyStop; // 止まってる時
		float m_stopTime; // 焦りで止まってる時間
		float m_frameCount; // 経過時間

		shared_ptr<GameObject> m_targetObject;

		unique_ptr<LayeredStateMachine<EnemyObject>> m_stateMachine;

	public :
		EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position);
		virtual ~EnemyObject() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void MoveEnemy(); // 移動関数
		void ActionPosLimit(); //行動制限
		virtual void ChangeAnimation(wstring animName); //アニメーション変更関数
		void Action(); // 感情表現選択関数
		void Impatience(); // 焦り表現
		//void AttackToPlayer(); // 攻撃関数
		void SearchObject(); // 他のオブジェクトとの距離を測る関数
		
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
 
		wstring GetStateName() {
			return m_stateMachine->GetTopState()->GetStateName();
		}
		unique_ptr<LayeredStateMachine<EnemyObject>>& GetStateMachine() {
			return m_stateMachine;
		}
	};


	//---------------------------------------------------------------------------
	// Enemy通常ステート
	//---------------------------------------------------------------------------
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

	//---------------------------------------------------------------------------
	// Enemyの感情に変化があった時のステート
	//---------------------------------------------------------------------------
	class EnemyFeelState : public ObjState<EnemyObject>
	{
		EnemyFeelState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(EnemyFeelState)
		virtual wstring GetStateName()const { return L"EnemyFeelState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;

	};

	//---------------------------------------------------------------------------
	// 大きい敵
	//---------------------------------------------------------------------------
	class BigEnemyObject : public GameObject
	{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Vec3 m_velo;
		float m_moveSpeed;
		int m_level;
		int m_HP;

		shared_ptr<GameObject> m_targetObject;

		//unique_ptr<LayeredStateMachine<BigEnemyObject>> m_stateMachine;

	public:
		BigEnemyObject(shared_ptr<Stage>& Stage, const Vec3 position);
		virtual ~BigEnemyObject() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void MoveEnemy(); // 移動関数
		void ActionPosLimit(); //行動制限

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};

	//---------------------------------------------------------------------------
	// 敵が打ってくる矢
	//---------------------------------------------------------------------------
	/*class Bullet : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		float m_moveSpeed;
		Vec3 m_velo;

	public :
		Bullet(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 velo);
		virtual ~Bullet() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void MoveBullet();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	
	};*/
}
//end basecross
