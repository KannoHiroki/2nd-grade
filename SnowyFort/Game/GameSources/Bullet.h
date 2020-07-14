/*!
@file Bullet.h
@brief ��ʂȂ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	���
	//--------------------------------------------------------------------------------------
	class SnowBall : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Vec3 m_Velocity;
		float m_GettingLargeSpeed;
		PsSphereParam m_Param;
	public:
		SnowBall(const shared_ptr<Stage>& StagePtr, const float Scale,const Vec3& Rotation,const Vec3& Position);
		SnowBall(const shared_ptr<Stage>& StagePtr, const float Scale,const Vec3& Rotation,const Vec3& Position, const Vec3& Velocity);
		virtual ~SnowBall(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& Other) override;

		//�Q�b�^�[�Z�b�^�[
		//�傫���Ȃ�X�s�[�h
		inline float GetGettingLargeSpeed() const {
			return m_GettingLargeSpeed;
		}
		inline void SetGettingLargeSpeed(float GettingLargeSpeed) {
			m_GettingLargeSpeed = GettingLargeSpeed;
		}
	};
}
//end basecross
