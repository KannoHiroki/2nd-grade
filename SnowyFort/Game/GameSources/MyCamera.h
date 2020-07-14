/*!
@file MyCamera.h
@brief �v���C���[�J����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	MyPlayerCamera�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//�@�v���C���[���f���J����
	//--------------------------------------------------------------------------------------
	class MyPlayerCamera : public Camera {
		Vec3 m_MovePosition;
		weak_ptr<GameObject> m_TargetObject;
		float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl
		bsm::Vec3 m_TargetToAt;	//�ڕW���王�_�𒲐�����ʒu�x�N�g��
		float m_RadXZ;
		float m_ArmLen;
		float m_ArmHeight;
		// �J�����̉�]���x
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
		//�J�����̒����_����̋����ƃ^�[�Q�b�g�I�u�W�F�N�g��y���W����̍�����ݒ肷��
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
	//	ObjCamera�J�����i�R���|�[�l���g�ł͂Ȃ��j
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