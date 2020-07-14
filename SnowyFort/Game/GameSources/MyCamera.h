/*!
@file MyCamera.h
@brief プレイヤーカメラ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	MyPlayerCameraカメラ（コンポーネントではない）
	//　プレイヤーを映すカメラ
	//--------------------------------------------------------------------------------------
	class MyPlayerCamera : public Camera {
		Vec3 m_MovePosition;
		weak_ptr<GameObject> m_TargetObject;
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル
		float m_RadXZ;
		float m_ArmLen;
		float m_ArmHeight;
		// カメラの回転速度
		float m_RotSpeed;
		bool m_LRBaseMode;
	public:
		MyPlayerCamera();
		virtual ~MyPlayerCamera();
		virtual void OnUpdate()override;


		shared_ptr<GameObject> GetTargetObject() const;
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		float GetArmLengh()const;
		void SetArmLengh(const float& armLength);
		float GetArmHeight()const;
		void SetArmHeight(const float& armHeight);
		//カメラの注視点からの距離とターゲットオブジェクトのy座標からの高さを設定する
		void SetArmParam(const float& armLength, const float& armHeight);
		bool IsLRBaseMode() const;
		virtual void SetAt(const bsm::Vec3& At) override;
		
		//RotSpeed
		inline float GetRotSpeed() const
		{
			return m_RotSpeed;
		}
		inline void SetRotSpeed(float speed)
		{
			m_RotSpeed = speed;
		}
	};

	//--------------------------------------------------------------------------------------
	//	ObjCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class ObjCamera : public Camera {
		float m_RadXZ;
		float m_RadY;
		float m_RotSpeed;
		float m_Atlength;
		weak_ptr<GameObject> m_TargetObject;
	public:
		ObjCamera();
		virtual ~ObjCamera(){}
		virtual void OnUpdate()override;
		shared_ptr<GameObject> GetTargetObject() const;
		void SetTargetObject(const shared_ptr<GameObject>& Obj);

		inline float GetRadXZ() const {
			return m_RadXZ;
		}
		inline float GetRadY() const {
			return m_RadY;
		}
	};
}