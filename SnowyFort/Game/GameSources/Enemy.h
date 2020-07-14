/*!
@file Enemy.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//---------------------------------------------------------------------------
	// �G
	//---------------------------------------------------------------------------
	class EnemyObject : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		
		float m_moveSpeed; // �ړ��X�s�[�h
		float m_rad; // �ړ��p�p�x
		float m_searchDis; // �U�����n�߂鋗��
		Vec3 m_velo; // ����
		int m_level; // ����
		bool m_enemyStop; // �~�܂��Ă鎞
		float m_stopTime; // �ł�Ŏ~�܂��Ă鎞��
		float m_frameCount; // �o�ߎ���

		shared_ptr<GameObject> m_targetObject;

		unique_ptr<LayeredStateMachine<EnemyObject>> m_stateMachine;

	public :
		EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position);
		virtual ~EnemyObject() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void MoveEnemy(); // �ړ��֐�
		void ActionPosLimit(); //�s������
		virtual void ChangeAnimation(wstring animName); //�A�j���[�V�����ύX�֐�
		void Action(); // ����\���I���֐�
		void Impatience(); // �ł�\��
		//void AttackToPlayer(); // �U���֐�
		void SearchObject(); // ���̃I�u�W�F�N�g�Ƃ̋����𑪂�֐�
		
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
 
		wstring GetStateName() {
			return m_stateMachine->GetTopState()->GetStateName();
		}
		unique_ptr<LayeredStateMachine<EnemyObject>>& GetStateMachine() {
			return m_stateMachine;
		}
	};


	//---------------------------------------------------------------------------
	// Enemy�ʏ�X�e�[�g
	//---------------------------------------------------------------------------
	class EnemyDefaultState : public ObjState<EnemyObject>
	{
		EnemyDefaultState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(EnemyDefaultState)
		virtual wstring GetStateName()const { return L"EnemyDefaultState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;

	};

	//---------------------------------------------------------------------------
	// Enemy�̊���ɕω������������̃X�e�[�g
	//---------------------------------------------------------------------------
	class EnemyFeelState : public ObjState<EnemyObject>
	{
		EnemyFeelState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(EnemyFeelState)
		virtual wstring GetStateName()const { return L"EnemyFeelState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;

	};

	//---------------------------------------------------------------------------
	// �傫���G
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

		void MoveEnemy(); // �ړ��֐�
		void ActionPosLimit(); //�s������

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};

	//---------------------------------------------------------------------------
	// �G���ł��Ă����
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
