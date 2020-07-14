/*!
@file SpawnBlock.h
@brief ìGÇ™èoåªÇ∑ÇÈÇ‚Ç¬
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	class SpawnBlock : public GameObject
	{

		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_position;

		int m_HP;
		float m_elapsedTime;
		float m_spawnTime;

	public :
		SpawnBlock(shared_ptr<Stage>&Stage,const Vec3& position);
		virtual ~SpawnBlock() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}