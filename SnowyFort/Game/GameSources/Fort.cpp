/*!
@file Fort.cpp
@brief 砦など実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Fort : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Fort::Fort(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
		m_chest = 3;
	}
	Fort::~Fort() {}

	//初期化
	void Fort::OnCreate() {		
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"Fort");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"MODEL_FORT_MESH");
		ptrDraw->SetTextureResource(L"Fort_TX");
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetOwnShadowActive(true);
	}

	//宝箱を減らす
	void Fort::ReduceChest() {
		m_chest--;

		//宝箱が０になったらリザルトにとばす
		if (m_chest <= 0) {
			GetStage()->PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
		}
	}
}