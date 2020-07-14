/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	enum class EnemyType
	{
		NormalEnemy,
		LongRangeEnemy,
		BossEnemy
	};


	//--------------------------------------------------------------------------------------
	//	class CameraTarget : public GameObject;
	//--------------------------------------------------------------------------------------
	class CameraTarget : public GameObject {
		float m_distance;
		float m_speed;
		bool m_chase;
		float m_maxSpeed;
		float m_minSpeed;
		Vec3 m_force;
		Vec3 m_velocity;
		shared_ptr<GameObject> m_ptrTarget;
	public:
		CameraTarget(const shared_ptr<Stage>& Stage);
		virtual ~CameraTarget();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SetTarget(shared_ptr<GameObject>& Obj);
		void PosAdjustment();
		void Target();
	};

	//--------------------------------------------------------------------------------------
	//	�J�������擾���������I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class CameraBox : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_rot;

		//�E���͂������͂��̃t���O()
		bool m_isPlus;
		bool m_isMinus;

		float m_imageLength;
		int m_pushCount;
		bool m_moveStop;

		bool m_stopSelect;
		int m_maxStageNum = 5;
		int m_minStageNum = 0;
		Vec3 m_stageSelectSpherePos[6];
		int m_nowSelectStageNum;
		bool m_isStartActionArrive;

	public:
		CameraBox(const shared_ptr<Stage>& StagePtr);
		~CameraBox() {};

		virtual void OnCreate()override;
		virtual void OnUpdate();
		//num = �X�e�[�W�̔ԍ�, Ope = +��-
		void Move(int num, wstring Ope);
		void TargetMove();

		int GetPushCount() { return m_pushCount; }

		void SetStopFlg(bool flg) { m_moveStop = flg; }

		bool GetStopSelect() { return m_stopSelect; }

		bool GetR() { return m_isPlus; }
		bool GetL() { return m_isMinus; }

	};

	//--------------------------------------------------------------------------------------
	//	�J�����{�b�N�X���g�p����ׂ����̃{�b�N�X
	//--------------------------------------------------------------------------------------
	class CamBox : public GameObject 
	{
		Vec3 m_position;
	public:
		CamBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Position
		);
		~CamBox() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
	public:
		//�\�z�Ɣj��
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//������
		virtual void OnCreate() override;
		//����
	};
	//--------------------------------------------------------------------------------------
	//	class wall : public GameObject;
	//--------------------------------------------------------------------------------------
	class wall : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_UPic;
		float m_VPic;
		float m_alpha;
		float m_FrameCount;
		float m_TransparentTime;
	public:
		//�\�z�Ɣj��
		wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~wall();
		//������
		virtual void OnCreate() override;
		//����
		void ReturnAlpha();
		void SetAlpha(float value) {
			m_alpha = value;
		}
	};
	//--------------------------------------------------------------------------------------
	//	class HPGauge : public GameObject;
	//--------------------------------------------------------------------------------------

	class HPGauge :public GameObject {
		Vec2 m_position;
		Vec2 m_scale;
		bool m_isFix;
		float m_damageOne;
		float m_Per;
		int m_PlayerHitPoint;
		int m_pastHp;
	public:
		HPGauge(shared_ptr<Stage>& Stage, const Vec2 position, bool isFix);
		virtual ~HPGauge();
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		void Damage();
		void SetHP();
	};
	//--------------------------------------------------------------------------------------
	//	class HPGaugeFace : public GameObject;
	//--------------------------------------------------------------------------------------

	class HPGaugeFace :public GameObject {
		Vec2 m_pos;
		Vec3 m_scale;
	public:
		HPGaugeFace(shared_ptr<Stage> &stage, const Vec2 Position);
		virtual ~HPGaugeFace();
		virtual void OnCreate()override;
		/*virtual void OnUpdate()override;*/
	};
	//--------------------------------------------------------------------------------------
	//	class CircleGrass : public GameObject;
	//--------------------------------------------------------------------------------------
	class CircleGrass :public GameObject {
		Vec3 m_pos;
		Vec3 m_rote;
		Vec3 m_scale;
		float m_rad;
		Vec2 m_tmpScale;
	public:
		CircleGrass(shared_ptr<Stage>& Stage, Vec3 position);
		virtual ~CircleGrass();
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
		void AddScale(Vec2 scale);
	};
	// �`�拗���֘A
	struct DrawDistance {
		float maxDistance;
		float minDistance;
		wstring meshName;
		bool isUpdate;
		bool isDraw;
		bool isCollisionSleep;
	};

	//--------------------------------------------------------------------------------------
	// �J�������o�̎n�܂�ƏI���̃t���O�܂Ƃ߂Ēu��
	//--------------------------------------------------------------------------------------
	struct CameraProductFlg
	{
		bool Start = false;
		bool End = false;
	};


	//--------------------------------------------------------------------------------------
	//	�J�������o�p�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class CameraTargetObject : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		Vec3 m_at;
		Vec3 m_eye;
		CameraProductFlg m_StartProd;
		CameraProductFlg m_FenceCollapse;
		CameraProductFlg m_ClearEnding;


		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<CameraTargetObject> >  m_StateMachine;
	public :
		CameraTargetObject(shared_ptr<Stage>& Stage,Vec3 startPos);
		~CameraTargetObject() {};
		void OnCreate() override;
		void OnUpdate() override;
		void ToStartEnter();
		//void GameOverMove();
		//void GameClearMove();
		const unique_ptr< StateMachine<CameraTargetObject> >& GetStateMachine() {
			return m_StateMachine;
		}
		const Vec3 GetAtPos() {
			return m_AtPos;
		}

		void FenceCollapce();

		void ClearEnding();
	};
	//--------------------------------------------------------------------------------------	
	///	�G�t�F�N�g�v���C�I�u�W�F�N�g
	//--------------------------------------------------------------------------------------

	class EffectPlayObj :public GameObject {
		Vec3 m_pos;
		wstring m_effectKey;
		//�G�t�F�N�g
		shared_ptr<EfkEffect> m_EfkEffect;
		//�G�t�F�N�g���s�v���W�F�N�g
		shared_ptr<EfkPlay> m_EfkPlay;
	public:
		EffectPlayObj(shared_ptr<Stage>& stage, const Vec3& Position, const wstring EffectKey);
		virtual ~EffectPlayObj() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void EffectEndCheck();
	};

	//--------------------------------------------------------------------------------------	
	///	�A��
	//--------------------------------------------------------------------------------------
	class Plant : public GameObject {
		Vec3 m_pos;
		Vec3 m_scale;
		wstring m_districtName;
		bool m_isRun;
		weak_ptr<CircleGrass> m_myGrass;
		Vec3 m_MaxScale;
		bool m_isMaxCircleScale;
		Vec3 m_maxScaleOneThird;
		wstring m_modelName;
	public:
		Plant(shared_ptr<Stage>& stage,const Vec3& position,const Vec3& scale,wstring districtName,Vec3 MaxScale);
		virtual ~Plant() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SearchPlayer();
		void ExamineScale();
		weak_ptr<CircleGrass> GetMyGreenCircle() {
			return m_myGrass;
		}

		bool GetIsRun() {
			return m_isRun;
		}
		bool GetIsMaxCircleScale() {
			return m_isMaxCircleScale;
		}
		Vec3 GetMaxScale() {
			return m_MaxScale;
		}
		void SetGerminationAct();

		void ModelChange();

		wstring GetModelName() {
			return m_modelName;
		}
	};
	//--------------------------------------------------------------------------------------	
	///	�A�؂̗t���ς���
	//--------------------------------------------------------------------------------------
	class Leaf : public GameObject {
		shared_ptr<Plant> m_plant;
		Vec3 m_scale;
		wstring m_modelName;
	public:
		Leaf(shared_ptr<Stage> &stage, shared_ptr<Plant> &plant);
		virtual ~Leaf() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void ModelChange();
		void SetGerminationAct();
	};



	//--------------------------------------------------------------------------------------	
	///	�X�|�[���I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class SpawnBlock :public GameObject {
		Vec3 m_pos;
		wstring m_districtName;
		float m_spawnTime;
	public:
		SpawnBlock(shared_ptr<Stage> &Stage, Vec3 Position, wstring DistrictName);
		virtual ~SpawnBlock() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void Spawn(int SpawnEnemyNum, EnemyType type);

		void SpawnNormal();
		void SpawnLongDis();
	};

	//--------------------------------------------------------------------------------------	
	///	�G���A�̏o������ɒu�������蔻��I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class EreaBox :public GameObject {
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rotation;
		wstring m_nowEreaName;
	public:
		EreaBox(shared_ptr<Stage> &Stage, Vec3 Position, Vec3 Scale, Vec3 Rotation, wstring NowEreaName);
		virtual ~EreaBox() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};
	//--------------------------------------------------------------------------------------	
	///	�r���{�[�h�������ꂽ�|��
	//--------------------------------------------------------------------------------------
	class BillboardPlate : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rot;
		wstring m_key;
		wstring m_district;
	public :
		BillboardPlate(shared_ptr<Stage>&Stage, const Vec3 pos, const wstring key, const wstring district);
		virtual ~BillboardPlate() {};
		
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void DeleteObject();
	};
	//--------------------------------------------------------------------------------------	
	///	�r���{�[�h�������ꂽ�|��(stageselect)
	//--------------------------------------------------------------------------------------
	class BillboardPlate1 : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_scale;
		Vec3 m_rot;
		wstring m_key;
		wstring m_district;
	public:
		BillboardPlate1(shared_ptr<Stage>&Stage, const Vec3 pos, const wstring key, const wstring district);
		virtual ~BillboardPlate1() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------	
	///	�J�������o�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	class OpeningCameramanToGoalState : public ObjState<CameraTargetObject>
	{
		OpeningCameramanToGoalState() {}
	public:
		static shared_ptr<OpeningCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Execute(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Exit(const shared_ptr<CameraTargetObject>& Obj)override;
	};

	class OpeningCameramanToStartState : public ObjState<CameraTargetObject>
	{
		OpeningCameramanToStartState() {}
	public:
		static shared_ptr<OpeningCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Execute(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Exit(const shared_ptr<CameraTargetObject>& Obj)override;
	};

	class OpeningCameramanEndState : public ObjState<CameraTargetObject>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Execute(const shared_ptr<CameraTargetObject>& Obj)override;
		virtual void Exit(const shared_ptr<CameraTargetObject>& Obj)override;
	};
	//--------------------------------------------------------------------------------------	
	///	�؂̃t�F���X(�n���Ή�������|�����)
	//--------------------------------------------------------------------------------------
	class Fence :public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
		wstring m_districtName;
		bool m_isCollapse;
	public:
		Fence(shared_ptr<Stage> &stage, Vec3 Position,Vec3 Rotate, wstring DistrictName);
		~Fence() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void Collapse();
		bool GetIsCollapse() {
			return m_isCollapse;
		}
		wstring GetDistrictName() {
			return m_districtName;
		}
	};
	//--------------------------------------------------------------------------------------	
	/// �S�u�̉Ƃ̑O�̍Y
	//--------------------------------------------------------------------------------------
	class Hang : public GameObject {
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
	public :
		Hang(shared_ptr<Stage>&stage, Vec3 pos);
		~Hang() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
