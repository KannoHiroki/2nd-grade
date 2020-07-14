/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	class FixedBox : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedBox::FixedBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	FixedBox::~FixedBox() {}

	//初期化
	void FixedBox::OnCreate() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"FixedBox");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetTextureResource(L"SKY_TX");
	}

	//--------------------------------------------------------------------------------------
	///	物理計算する固定のボックス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	FixedPsBox::FixedPsBox(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Quat& Qt,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Qt(Qt),
		m_Position(Position)
	{}

	FixedPsBox::~FixedPsBox() {}
	//初期化
	void FixedPsBox::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetQuaternion(m_Qt);
		ptrTrans->SetPosition(m_Position);

		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetOwnShadowActive(true);
		//物理計算ボックス
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->AddExcludeCollisionTag(L"Plane");

		AddTag(L"Plane");
	}
	//--------------------------------------------------------------------------------------
	//	物理計算する固定の球体
	//--------------------------------------------------------------------------------------
	FixedPsSphere::FixedPsSphere(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position)
		: GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{

	}

	void FixedPsSphere::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, true, PsMotionType::MotionTypeFixed);
		auto ptrPs = AddComponent<RigidbodySphere>(param);

		auto ptrColl = AddComponent<CollisionSphere>();
	}

	void FixedPsSphere::OnUpdate2() {
		auto PtrPs = GetComponent<RigidbodySphere>();
		auto Ptr = GetComponent<Transform>();
		//位置を戻す
		Ptr->SetPosition(PtrPs->GetPosition());
	}

	//--------------------------------------------------------------------------------------
	//	class Mountain : public GameObject;
	//--------------------------------------------------------------------------------------
	Wall::Wall(shared_ptr<Stage>&Stage, const Vec3 position, const Vec3 rotation, const Vec3 scale)
		: GameObject(Stage),
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{

	}

	void Wall::OnCreate()
	{
		auto transPtr = GetComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetRotation(m_rotation);
		transPtr->SetScale(m_scale);

		auto drawPtr = AddComponent<BcPNTStaticDraw>();
		drawPtr->SetMeshResource(L"DEFAULT_CUBE");
		drawPtr->SetTextureResource(L"Wall_Tx");

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto collPtr = AddComponent<CollisionObb>();
		collPtr->SetFixed(true);
	}

	void Wall::OnUpdate()
	{
	
	}

	//--------------------------------------------------------------------------------------
	//	class Mountain : public GameObject;
	//--------------------------------------------------------------------------------------
	//static変数の初期化
	Mountain::Mountain(const shared_ptr<Stage>& StagePtr)
		:GameObject(StagePtr),
		m_Scale(Vec3(20.0f,20.0f,20.0f)),
		m_Rotation(Vec3(0)),
		m_Position(Vec3(0,-10.2f,0))
	{}

	Mountain::Mountain(const shared_ptr<Stage>& StagePtr, const Vec3& ScalePtr, const Vec3& RotationPtr, const Vec3& PositionPtr)
		: GameObject(StagePtr),
		m_Scale(ScalePtr),
		m_Rotation(RotationPtr),
		m_Position(PositionPtr)
	{}

	Mountain::~Mountain(){}

	void Mountain::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		//auto shadowPtr = AddComponent<Shadowmap>();
		//shadowPtr->SetMeshResource(L"MODEL_MESH");

		//メッシュ追加
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"MODEL_MESH");
		ptrDraw->SetTextureResource(L"Mountain_TX");
	}

	//--------------------------------------------------------------------------------------
	//	class Tree : public GameObject;
	//--------------------------------------------------------------------------------------
	Tree::Tree(const shared_ptr<Stage>&Stage, const Vec3 position, const Vec3 rotation)
		: GameObject(Stage),
		m_position(position),
		m_rotation(rotation)
	{
		m_scale = Vec3(0.5f, 1.0, 0.5f);
	}

	void Tree::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MODEL_TREE_MESH");

		//auto ptrColl = AddComponent<CollisionObb>();

		AddTag(L"Tree");
	}

	//--------------------------------------------------------------------------------------
	//　球体のカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Cameraman::Cameraman(const shared_ptr<Stage>& StagePtr,
		float ToPlayerLen
	) :
		GameObject(StagePtr),
		m_Playflg(true),
		m_Speed(6.0f),
		m_ToPlayerLen(ToPlayerLen),
		m_DirY(0,0,0)
	{}
	Cameraman::~Cameraman() {}
	Vec2 Cameraman::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[1].bConnected) {
			ret.x = cntlVec[1].fThumbLX;
			ret.y = cntlVec[1].fThumbLY;
		}
		return ret;
	}

	//初期化
	void Cameraman::OnCreate() {
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(0, 0.125f, 0));

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
	}

	//カメラマン操作
	void Cameraman::OnUpdate() {
		m_InputHandler.PushHandle(GetThis<Cameraman>(), 1);
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//カメラの取得
		auto ptrCamera = dynamic_pointer_cast<ObjCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			// カメラにプレイヤーを保存
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			m_DirX = Vec3(cosf(ptrCamera->GetRadXZ() - XM_PIDIV2),0,sinf(ptrCamera->GetRadXZ() - XM_PIDIV2)).normalize();
			m_DirY = Vec3(cosf(ptrCamera->GetRadXZ()),0,sinf(ptrCamera->GetRadXZ())).normalize();
		}
		Vec2 movePos = GetInputState();
		auto angle = m_DirY * movePos.y;
		angle += m_DirX * movePos.x;
		angle.normalize();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
	}

	void Cameraman::OnPushA() {
		m_Playflg ^= 1;
		shared_ptr<EnemyObject> enemy = nullptr;
		auto objs = GetStage()->GetGameObjectVec();
		for (auto& obj : objs) {
			enemy = dynamic_pointer_cast<EnemyObject>(obj);
			if (enemy) {
				enemy->SetUpdateActive(m_Playflg);
			}
		}
	}

	void Cameraman::OnPushB() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos.y += elapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(pos);
	}

	void Cameraman::OnPushX() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos.y -= elapsedTime * m_Speed;
		GetComponent<Transform>()->SetPosition(pos);
	}

	void Cameraman::OnPushY() {

	}

	//--------------------------------------------------------------------------------------
	//	class Plane : public GameObject;
	//--------------------------------------------------------------------------------------
	Plane::Plane(shared_ptr<Stage>& stage)
		: GameObject(stage)
	{
		m_position = Vec3(0.0f, -3.35f, 0.0f);
		m_rotation = Vec3(0.0f);
		m_scale = Vec3(40.0f, 1.0f, 40.0f);
	}

	void Plane::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotation);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		SetDrawActive(true);
	}
}
//end basecross
