/*!
@file Bullet.cpp
@brief ��ʂȂǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class SnowBall : public GameObject;
	//	�p�r: ���
	//--------------------------------------------------------------------------------------
	SnowBall::SnowBall(const shared_ptr<Stage>& StagePtr,
		const float Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Velocity(0,0,0),
		m_GettingLargeSpeed(0.25f)
	{}

	SnowBall::SnowBall(const shared_ptr<Stage>& StagePtr,
		const float Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const Vec3& Velocity
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Velocity(Velocity),
		m_GettingLargeSpeed(0.25f)
	{}

	void SnowBall::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		auto ptrColl = AddComponent<CollisionSphere>();

		//�����R���|�[�l���g������
		PsSphereParam param(ptrTransform->GetWorldMatrix(),1.0f,false,PsMotionType::MotionTypeActive);
		auto PsPtr = AddComponent<RigidbodySphere>(param);
		PsPtr->SetAutoTransform(true);
		PsPtr->SetLinearVelocity(m_Velocity);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"Yukidama_TX");

		//�^�O�t��
		AddTag(L"Bullet");

		//GetStage()->AddGameObject<ActionLine>(GetThis<GameObject>(), true);
		ptrDraw->SetFogEnabled(true);

	}

	void SnowBall::OnUpdate() {
		//auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto transComp = GetComponent<Transform>();

		//�X�e�[�W�O�ɏo�������
		if (transComp->GetPosition().y < -15.0f) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}

	// �Փ˂����Ƃ�
	void SnowBall::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		// �^�O����
		if (Other->FindTag(L"Enemy")) {

		}
	}

	void SnowBall::OnCollisionExit(shared_ptr<GameObject>& Other) {

	}
}
//end basecross

