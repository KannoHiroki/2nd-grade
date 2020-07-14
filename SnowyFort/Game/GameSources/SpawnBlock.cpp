/*!
@file SpawnBlock.cpp
@brief ìGÇ™èoåªÇ∑ÇÈÇ‚Ç¬
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpawnBlock::SpawnBlock(shared_ptr<Stage>&Stage, const Vec3& position)
		: GameObject(Stage),
		  m_position(position),
		  m_rotation(Vec3(0)),
		  m_scale(Vec3(0.1f))
	{
		m_HP = 100;
		m_elapsedTime = 0.0f;
		m_spawnTime = 10.0f;
	}

	void SpawnBlock::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_SPAWNBLOCK_MESH");

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		auto ptrPlayer = GetStage()->GetSharedGameObject<Fort>(L"Fort");
		auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();

		auto velo = playerPos - m_position;
		velo.normalize();

		auto ptrUtil = GetBehavior<UtilBehavior>();
		if (velo.length() > 0) {
			ptrUtil->RotToHead(velo * -1.0f, 1.0f);
		}
	}

	void SpawnBlock::OnUpdate()
	{
		m_elapsedTime += App::GetApp()->GetElapsedTime();
		if (m_elapsedTime > m_spawnTime) {
			m_elapsedTime = 0.0f;
		}
	}
		
	void SpawnBlock::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (other->FindTag(L"Bullet")) {
			m_HP -= 10;
		}

		if (m_HP <= 0) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<SpawnBlock>());
		}
	}
}