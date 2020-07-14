/*!
@file Fort.h
@brief Ô‚È‚Ç
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
		//\’z‚Æ”jŠü
		Fort(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Fort();
		//‰Šú‰»
		virtual void OnCreate() override;
		//•ó” ‚ğŒ¸‚ç‚·
		void ReduceChest();
		//•ó” ‚Ì”‚ğ•Ô‚·
		int GetChestCount() {
			return m_chest;
		}
	};
}