#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�G
	//--------------------------------------------------------------------------------------
	class EnemyObject : public GameObject {
		Vec3 m_rotVec;
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_searchDis;
		float m_moveSpeed;
		float m_rad; //�ړ��p�p�x

		bool m_enemyStop;
		float m_stopTime;

		int m_HP;


		bool m_isAddScale;
		// �m�b�N�o�b�N�֘A
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
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		shared_ptr<EfkEffect> m_EfkGreenOut;
		//�G�t�F�N�g���s�v���W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;
		shared_ptr<EfkPlay> m_EfkPlay2;


	public:
		EnemyObject(shared_ptr<Stage>& Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale, const wstring DistrictName);
		virtual ~EnemyObject() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		// �v���C���[��T��
		virtual void PlayerSearch();
		// �v���C���[��ǂ�������
		virtual void AttackToPlayer();
		// �v���C���[�ɍU�������ۂ̍d��
		void AttackDelay();
		// �m�b�N�o�b�N������������߂�
		void KnockBackVeloMake(shared_ptr<GameObject> Obj);
		// �v���C���[�ɍU�����ꂽ�Ƃ��̃m�b�N�o�b�N
		void KnockBack();
		// ���������񂾂�����łȂ����̊m�F
		void DeathCheacker();
		//�ʏ펞�̈ړ�
		void MoveEnemy();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		void GreenChecker();
		//�m�b�N�o�b�N�t���O
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
	///	�S�u�����\�[�h
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
	//�G�l�~�[�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------
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
	//--------------------------------------------------------------------------------------	
	///	�v���C���[��ǂ�������X�e�[�g
	//--------------------------------------------------------------------------------------
	class EnemyPlayerChaseState : public ObjState<EnemyObject>
	{
		EnemyPlayerChaseState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(EnemyPlayerChaseState)
		virtual wstring GetStateName()const { return L"EnemyPlayerChaseState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};
	//--------------------------------------------------------------------------------------	
	///	�m�b�N�o�b�N�X�e�[�g
	//--------------------------------------------------------------------------------------
	class EnemyKnockBackState : public ObjState<EnemyObject>
	{
		EnemyKnockBackState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(EnemyKnockBackState)
		virtual wstring GetStateName()const { return L"EnemyKnockBackState"; }
		virtual void Enter(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Execute(const shared_ptr<EnemyObject>& Obj)override;
		virtual void Exit(const shared_ptr<EnemyObject>& Obj)override;
	};


	//--------------------------------------------------------------------------------------
	//�@�������U�����Ă���G
	//--------------------------------------------------------------------------------------

	class LongDisEnemyObject : public EnemyObject{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
		float m_interval; //�U���̃C���^�[�o��
		float m_elapsedTime; //�o�ߎ���
		float m_searchDis; //�U���͈�
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
	//�@�������̓G����΂��e
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
	//�@���{�X
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
	//�@�{�X
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