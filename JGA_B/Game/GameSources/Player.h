/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class GameManager {
	private:
		GameManager() {
			m_enemyMoveSpeed = 1.0f;
			m_nowEnemyNum = 0;
			m_selectedStageNum = 1;
			m_playerComboMaxTime = 1.0f;
			m_greenPer = 0;
			m_addScaleValue = 5.0f;
			m_MaxDrawEnemy = 15;
			m_menuSelect = 1;
			m_isPlayerActive = false;
			m_isGameObjectActive = true;
			m_isCameraActive = false;
			m_isFade = false;
		}
		~GameManager() {
			delete GM;
		}
	

		static GameManager* GM;
		// �G�̓����X�s�[�h
		float m_enemyMoveSpeed;
		// ���݂̃G�l�~�[�̐�
		int m_nowEnemyNum;
		int m_selectedStageNum;
		float m_playerComboMaxTime;
		// �Ή��̃p�[�Z���e�[�W
		float m_greenPer;
		// �Α�����
		float m_addScaleValue;
		// �`����E�l
		int m_MaxDrawEnemy;
		// ���j���[�őI�΂�Ă�̂��Ȃɂ� 1�����g���C�A2���X�e�[�W�Z���N�g
		int m_menuSelect;
		// �v���C���[�̓������~�߂邩�~�߂Ȃ���
		bool m_isPlayerActive;
		// �Q�[���I�u�W�F�N�g�̓������~�߂Ȃ���
		bool m_isGameObjectActive;
		// �J�����̓������~�߂邩�~�߂Ȃ���
		bool m_isCameraActive;
		wstring m_sceneName;

		int m_fenceNum;
		bool m_isFade;
	public:
		static GameManager* GetGM();
		//�G�̃X�s�[�h��getter,setter

		float GetEnemySpeed() {
			return m_enemyMoveSpeed;
		}
		void SetEnemySpeed(float val) {
			m_enemyMoveSpeed = val;
		}
		// ������G��getter,setter
		int GetNowEnemyNum() {
			return m_nowEnemyNum;
		}
		void SetNowEnemyNum(int val) {
			m_nowEnemyNum = val;
		}
		// �X�e�[�W�i���o�[��getter,setter
		int GetselectedStageNum() {
			return m_selectedStageNum;
		}

		void SetSelectedStageNum(int stagenum)
		{
			m_selectedStageNum = stagenum;
		}
		// �v���C���[�̃R���{�������Ԃ�getter,setter

		float GetPlayerComboMaxTime() {
			return m_playerComboMaxTime;
		}
		void SetPlayerComboMaxTime(float v) {
			m_playerComboMaxTime = v;
		}
		float GetGreenPer() {
			return m_greenPer;
		}
		void SetGreenPer(float val) {
			m_greenPer += val;
		}

		// �Α����ʂ�getter
		float GetAddScaleValue() {
			return m_addScaleValue;
		}

		int GetMaxDrawEnemyNum() {
			return m_MaxDrawEnemy;
		}

		void Reset() {
			m_nowEnemyNum = 0;
			m_isFade = false;
		}

		bool GetFadeFlg() {
			return m_isFade;
		}
		void SetFadeFlg(bool b) {
			m_isFade = b;
		}
		

		// ���j���[�őI�΂�Ă�̂��Ȃɂ���getter,setter
		int GetMenuSelect(){
			return m_menuSelect;
		}
		void SetMenuSelect(int value) {
			m_menuSelect = value;
		}

		bool GetIsCameraActive() {
			return m_isCameraActive;
		}
		void SetIsCameraActive(bool b) {
			m_isCameraActive = b;
		}

		bool GetIsGameObjectActive() {
			return m_isGameObjectActive;
		}
		void SetIsGameObjectActive(bool b) {
			m_isGameObjectActive = b;
		}

		bool GetIsPlayerActive() {
			return m_isPlayerActive;
		}
		void SetIsPlayerActive(bool b) {
			m_isPlayerActive = b;
		}

		wstring GetSceneName() {
			return m_sceneName;
		}
		void SetSceneName(wstring SceneName) {
			m_sceneName = SceneName;
		}
		int GetFenceNum() {
			return m_fenceNum;
		}
		void SetFenceNum(int value) {
			m_fenceNum = value;
		}
	};


	struct EventWithTime {
		float Time;
		float FrameCount;
		bool IsEvent;
	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		bool m_isAttack;
		float m_attackComboTimer;

		int m_attackCombo;
		int m_tmpAttackCombo;
		//HP
		int m_HP;
		// �W�����v�̐�������
		float m_jumpCoolDown;
		// �v���C���[�̃_���[�W�^�C��
		float m_damageCoolDown;
		// �R���g���[����������x�N�g���𓾂�
		Vec3 GetMoveVector() const;
		//������̕\��
		void DrawStrings();
		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		//���x
		Vec3 m_Velocity;


		//----�Ȃ񂶂Ⴑ���----
		vector<int> p;
		int i;
		//----------------------


		//�m�b�N�o�b�N�����Ƃ��̃C�x���g
		EventWithTime m_KnockBack = { 0.0f ,0.0f, false };
		//�m�b�N�o�b�N�̕���
		Vec3 m_KnockBackVec;
		//�m�b�N�o�b�N�̑���
		float m_KnockBackSpeed;
		//�K�w���X�e�[�g�}�V�[��
		unique_ptr<LayeredStateMachine<Player>>  m_StateMachine;

		// ���݂̃X�e�[�g�}�V����c������
		wstring m_NowStateName;

		//���݂̃G���A�l�[��
		wstring m_nowEreaName;
		
		Vec3 m_moveVec;
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�v���W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;
		//SE�pTIME
		float m_timeSE;
		bool m_isDamegeCoolDown;
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		unique_ptr<LayeredStateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//A�{�^��
		void OnPushA();
		void MovePlayer();
		void KnockBackBehaviour();
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Obj)override;

		wstring GetNowStateName() {
			return m_NowStateName;
		}
		void SetNowStateName(wstring stateName) {
			m_NowStateName = stateName;
		}
		Vec3 GetMoveVec() {
			return m_moveVec;
		}

		int GetHP() {
			return m_HP;
		}
		void ChangeAnim(wstring animName);

		void Attack();

		void AttackComboTimer();

		void AttackAnimPlay(int animNum);

		bool GetIsAttack() {
			return m_isAttack;
		}
		void DamageToPlayer(int value) {
			if (m_isDamegeCoolDown == true) {
				m_HP -= value;
				m_damageCoolDown = 0.0f;
			}
		}
		void DamageEffect();
		void VeloMake(shared_ptr<GameObject>& obj);
		wstring GetNowEreaName() {
			return m_nowEreaName;
		}
		void SetNowEreaName(wstring EreaName) {
			m_nowEreaName = EreaName;
		}
		void ComboCheck();
		void SetCombo(int val) {
			m_attackCombo = val;
		}
		int GetCombo() {
			return m_attackCombo;
		}
		void AttackMove();
		void SetIsAttack(bool b) {
			m_isAttack = b;
		}
	};

	//�v���C���[�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerDefaultState : public ObjState<Player>
	{
		PlayerDefaultState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerDefaultState)
		virtual wstring GetStateName()const { return L"PlayerDefaultState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	///	�m�b�N�o�b�N�X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerKnockBackState : public ObjState<Player>
	{
		PlayerKnockBackState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerKnockBackState)
		virtual wstring GetStateName()const { return L"PlayerKnockBackState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	///	�U���̃X�e�[�g
	//--------------------------------------------------------------------------------------
	class PlayerAttackState : public ObjState<Player>
	{
		PlayerAttackState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		DECLARE_SINGLETON_INSTANCE(PlayerAttackState)
		virtual wstring GetStateName()const { return L"PlayerAttackState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	/// �v���C���[�̘r�̓����蔻�蕔��
	//--------------------------------------------------------------------------------------

	class ArmCollision : public GameObject {
		wstring m_positionName;
		shared_ptr<Player> m_parentPtr;
		int m_selectBoneNum;
		Vec3 m_position;
	public:
		ArmCollision(const shared_ptr<Stage>& Stage, const shared_ptr<Player>& ParentPtr, const wstring positionName, const int BoneNum, Vec3 &LocalPosition);
		virtual ~ArmCollision() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void PositionSet();
		void CollActive();
	};
}
//end basecross

