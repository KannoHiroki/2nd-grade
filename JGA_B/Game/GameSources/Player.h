/*!
@file Player.h
@brief プレイヤーなど
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
		// 敵の動くスピード
		float m_enemyMoveSpeed;
		// 現在のエネミーの数
		int m_nowEnemyNum;
		int m_selectedStageNum;
		float m_playerComboMaxTime;
		// 緑化のパーセンテージ
		float m_greenPer;
		// 緑増加量
		float m_addScaleValue;
		// 描画限界値
		int m_MaxDrawEnemy;
		// メニューで選ばれてるのがなにか 1がリトライ、2がステージセレクト
		int m_menuSelect;
		// プレイヤーの動きを止めるか止めないか
		bool m_isPlayerActive;
		// ゲームオブジェクトの動きを止めないか
		bool m_isGameObjectActive;
		// カメラの動きを止めるか止めないか
		bool m_isCameraActive;
		wstring m_sceneName;

		int m_fenceNum;
		bool m_isFade;
	public:
		static GameManager* GetGM();
		//敵のスピードのgetter,setter

		float GetEnemySpeed() {
			return m_enemyMoveSpeed;
		}
		void SetEnemySpeed(float val) {
			m_enemyMoveSpeed = val;
		}
		// 今いる敵のgetter,setter
		int GetNowEnemyNum() {
			return m_nowEnemyNum;
		}
		void SetNowEnemyNum(int val) {
			m_nowEnemyNum = val;
		}
		// ステージナンバーのgetter,setter
		int GetselectedStageNum() {
			return m_selectedStageNum;
		}

		void SetSelectedStageNum(int stagenum)
		{
			m_selectedStageNum = stagenum;
		}
		// プレイヤーのコンボ制限時間のgetter,setter

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

		// 緑増加量のgetter
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
		

		// メニューで選ばれてるのがなにかのgetter,setter
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
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		bool m_isAttack;
		float m_attackComboTimer;

		int m_attackCombo;
		int m_tmpAttackCombo;
		//HP
		int m_HP;
		// ジャンプの制限時間
		float m_jumpCoolDown;
		// プレイヤーのダメージタイム
		float m_damageCoolDown;
		// コントローラから方向ベクトルを得る
		Vec3 GetMoveVector() const;
		//文字列の表示
		void DrawStrings();
		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		//速度
		Vec3 m_Velocity;


		//----なんじゃこりゃ----
		vector<int> p;
		int i;
		//----------------------


		//ノックバックしたときのイベント
		EventWithTime m_KnockBack = { 0.0f ,0.0f, false };
		//ノックバックの方向
		Vec3 m_KnockBackVec;
		//ノックバックの速さ
		float m_KnockBackSpeed;
		//階層化ステートマシーン
		unique_ptr<LayeredStateMachine<Player>>  m_StateMachine;

		// 現在のステートマシンを把握する
		wstring m_NowStateName;

		//現在のエリアネーム
		wstring m_nowEreaName;
		
		Vec3 m_moveVec;
		//エフェクト
		shared_ptr<EfkEffect> m_EfkEffect;
		//エフェクト実行プロジェクト
		shared_ptr<EfkPlay> m_EfkPlay;
		//SE用TIME
		float m_timeSE;
		bool m_isDamegeCoolDown;
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		unique_ptr<LayeredStateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		//Aボタン
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

	//プレイヤーのステート
	//--------------------------------------------------------------------------------------
	///	通常ステート
	//--------------------------------------------------------------------------------------
	class PlayerDefaultState : public ObjState<Player>
	{
		PlayerDefaultState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(PlayerDefaultState)
		virtual wstring GetStateName()const { return L"PlayerDefaultState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	///	ノックバックステート
	//--------------------------------------------------------------------------------------
	class PlayerKnockBackState : public ObjState<Player>
	{
		PlayerKnockBackState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(PlayerKnockBackState)
		virtual wstring GetStateName()const { return L"PlayerKnockBackState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	///	攻撃のステート
	//--------------------------------------------------------------------------------------
	class PlayerAttackState : public ObjState<Player>
	{
		PlayerAttackState() {}
	public:
		//ステートのインスタンス取得
		DECLARE_SINGLETON_INSTANCE(PlayerAttackState)
		virtual wstring GetStateName()const { return L"PlayerAttackState"; }
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	/// プレイヤーの腕の当たり判定部分
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

