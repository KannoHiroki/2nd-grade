/*!
@file Fort.h
@brief �ԂȂ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Fort : public GameObject;
	//--------------------------------------------------------------------------------------
	class Fort : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		int m_chest;
	public:
		//�\�z�Ɣj��
		Fort(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Fort();
		//������
		virtual void OnCreate() override;
		//�󔠂����炷
		void ReduceChest();
		//�󔠂̐���Ԃ�
		int GetChestCount() {
			return m_chest;
		}
	};
}