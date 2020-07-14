/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	class FixedBox : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~FixedBox();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

	//--------------------------------------------------------------------------------------
	///	物理計算する固定のボックス
	//--------------------------------------------------------------------------------------
	class FixedPsBox : public GameObject {
		Vec3 m_Scale;
		Quat m_Qt;
		Vec3 m_Position;
	public:
		//構築と破棄
		FixedPsBox(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Quat& Qt,
			const Vec3& Position
		);
		virtual ~FixedPsBox();
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	物理計算する固定の球体
	//--------------------------------------------------------------------------------------
	class FixedPsSphere : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		FixedPsSphere(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		virtual ~FixedPsSphere() {};
		virtual void OnCreate() override;
		virtual void OnUpdate2() override;
	};
	//--------------------------------------------------------------------------------------
	//	class Wall : public GameObject;
	//--------------------------------------------------------------------------------------
	class Wall : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

	public :
		Wall(shared_ptr<Stage>&Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale);
		virtual ~Wall() {};
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Mountain : public GameObject;
	//--------------------------------------------------------------------------------------
	class Mountain : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		Mountain(const shared_ptr<Stage>& StagePtr);
		Mountain(const shared_ptr<Stage>& StagePtr, const Vec3& ScalePtr, const Vec3& RotationPtr, const Vec3& PositionPtr);
		~Mountain();
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class Tree : public GameObject;
	//--------------------------------------------------------------------------------------
	class Tree : public GameObject {
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;
	public:
		//構築と破棄
		Tree(const shared_ptr<Stage>& Stage,
			const Vec3 position,
			const Vec3 rotation
		);
		virtual ~Tree() {};
		//初期化
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	class Cameraman : public GameObject {
		bool m_Playflg;
		float m_Speed;
		float m_ToPlayerLen;
		Vec3 m_DirX;
		Vec3 m_DirY;
		InputHandler<Cameraman> m_InputHandler;
		//プレイヤーが使用するコントローラとキーボードの入力
		Vec2 GetInputState() const;
	public:
		//構築と破棄
		Cameraman(const shared_ptr<Stage>& StagePtr,
			float ToPlayerLen
		);
		virtual ~Cameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;

		//ボタンハンドラ
		void OnPushA();
		void OnPushB();
		void OnPushX();
		void OnPushY();
	};

	//--------------------------------------------------------------------------------------
	//	class Plane : public GameObject;
	//--------------------------------------------------------------------------------------
	class Plane : public GameObject
	{
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

	public :
		Plane(shared_ptr<Stage>& stage);
		~Plane() {};
		virtual void OnCreate() override;
	};
}
//end basecross
