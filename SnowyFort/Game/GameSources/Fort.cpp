/*!
@file Fort.cpp
@brief �ԂȂǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Fort : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
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

	//������
	void Fort::OnCreate() {		
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"Fort");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"MODEL_FORT_MESH");
		ptrDraw->SetTextureResource(L"Fort_TX");
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetOwnShadowActive(true);
	}

	//�󔠂����炷
	void Fort::ReduceChest() {
		m_chest--;

		//�󔠂��O�ɂȂ����烊�U���g�ɂƂ΂�
		if (m_chest <= 0) {
			GetStage()->PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToResultStage");
		}
	}
}