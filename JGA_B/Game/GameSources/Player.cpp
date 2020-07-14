/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	class GameManager
//	�p�r: �I������Ă���X�e�[�W�Ȃǂ�c�����Ă���
//------------------------------------------------------------------------------------------
	GameManager* GameManager::GM = nullptr;

	GameManager* GameManager::GetGM() {
		if (GM == nullptr) {
			GM = new GameManager();
		}
		return GM;
	}

	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Velocity(0)
	{
		auto gm = GameManager::GetGM();
		m_attackCombo = 0;
		m_tmpAttackCombo = 0;
		m_KnockBackVec = Vec3(0.0f);
		m_KnockBackSpeed = 0.3f;
		m_KnockBack.Time = 0.3f;
		m_KnockBack.FrameCount = 0.0f;
		m_jumpCoolDown = 15.0f;
		m_HP = 100;
		m_isAttack = false;
		m_attackComboTimer = gm->GetPlayerComboMaxTime();
		m_isDamegeCoolDown = true;
		m_nowEreaName = L"NONE";
	}

	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].fThumbLX != 0 || cntlVec[0].fThumbLY != 0) {
				auto ptrDraw = GetComponent<PNTBoneModelDraw>();
				float moveLength = 0;	//���������̃X�s�[�h
				auto ptrTransform = GetComponent<Transform>();
				auto ptrCamera = OnGetDrawCamera();
				//�i�s�����̌������v�Z
				auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
				front.y = 0;
				front.normalize();
				//�i�s������������̊p�x���Z�o
				float frontAngle = atan2(front.z, front.x);
				//�R���g���[���̌����v�Z
				float moveX = cntlVec[0].fThumbLX;
				float moveZ = cntlVec[0].fThumbLY;
				Vec2 moveVec(moveX, moveZ);
				float moveSize = moveVec.length();
				//�R���g���[���̌�������p�x���v�Z
				float cntlAngle = atan2(-moveX, moveZ);
				//�g�[�^���̊p�x���Z�o
				float totalAngle = frontAngle + cntlAngle;
				//�p�x����x�N�g�����쐬
				angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
				//���K������
				angle.normalize();
				//�ړ��T�C�Y��ݒ�B
				angle *= moveSize;
				//Y���͕ω������Ȃ�
				angle.y = 0;
			}

		}
		return angle;
	}

	void Player::MovePlayer() {
		// �v���C���[�̓�������
		const float playerSpeed = 6.0f;
		// SE�������Ԃ̃��~�b�g
		const float SELimit = 0.7f;
		// SE�{�����[��
		const float SEVol = 0.45f;

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		Vec3 pos = Vec3(0);
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		m_timeSE += elapsedTime;
		if (angle.length() > 0.0f) {
			if (ptrDraw->GetCurrentAnimation() != L"Walk") {
				ChangeAnim(L"Walk");
			}
			pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * playerSpeed;
			GetComponent<Transform>()->SetPosition(pos);
			if (m_timeSE > SELimit) {
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(L"Walk", 0, SEVol);
				m_timeSE = 0.0f;
			}
		}
		else if (ptrDraw->GetCurrentAnimation() != L"Idle"  && ptrDraw->GetCurrentAnimation() != L"Plant") {
			ChangeAnim(L"Idle");
		}
		else if (ptrDraw->GetCurrentAnimation() == L"Plant" && ptrDraw->IsTargetAnimeEnd() == true) {
			ChangeAnim(L"Idle");
		}
		//��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
		m_moveVec = angle;

	}


	void Player::AttackMove() {
		const float playerMoveSpeed = 0.6f;
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		Vec3 pos = Vec3(0);
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (angle.length() > 0.0f) {
			pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * playerMoveSpeed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		if (ptrDraw->IsTargetAnimeEnd()) {
			//��]�̌v�Z
			if (angle.length() > 0.0f) {
				auto utilPtr = GetBehavior<UtilBehavior>();
				angle.y *= -1.0f;
				utilPtr->RotToHead(angle, 1.0f);
			}
		}
		m_moveVec = angle;
	}
	//������
	void Player::OnCreate() {

		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.5f, 3.0f, 0.5f);
		ptr->SetRotation(0.0f, XM_PIDIV2 * -1.0f, 0.0f);
		ptr->SetPosition(0, 130.0f, 0);

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(false);
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		Mat4x4 SpanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		SpanMat.affineTransformation(
			Vec3(1.0f, 0.18f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\Attack3.efk";
		auto ShEfkInterface = GetTypeStage<GameStage>()->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"PLAYER_MESH");
		//�`�悷��e�N�X�`����ݒ�
		//ptrDraw->SetTextureResource(L"TRACE_TX");
		SetAlphaActive(true);
		ptrDraw->SetTextureResource(L"PLAYER_TX");

		AddTag(L"Player");
		SetDrawLayer(100);
		ptrDraw->SetMeshToTransformMatrix(SpanMat);
		
		auto &bones = ptrDraw->GetVecLocalBones();

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new LayeredStateMachine<Player>(GetThis<Player>()));
		//�ŏ��̃X�e�[�g��PlayerDefault�Ƀ��Z�b�g
		m_StateMachine->Reset(PlayerDefaultState::Instance());
		m_StateMachine->Push(PlayerDefaultState::Instance());
		//�X�e�[�g�̃X�^�b�N���
		m_StateMachine->SetMaxStack(30);
		// �A�j���[�V����
		ptrDraw->AddAnimation(L"Idle", 310, 31,true, 10.0f);
		ptrDraw->AddAnimation(L"Walk", 0, 41, true, 30.0f);
		ptrDraw->AddAnimation(L"Attack1", 60, 30, false, 60.0f);
		ptrDraw->AddAnimation(L"Attack2", 90, 35, false, 60.0f);
		ptrDraw->AddAnimation(L"Attack3", 125, 56, false, 60.0f);
		ptrDraw->AddAnimation(L"Damage", 485, 30, false, 30.0f);
		ptrDraw->AddAnimation(L"Plant", 590, 40, false, 15.0f);
		ptrDraw->ChangeCurrentAnimation(L"Idle");


	}

	//�X�V
	void Player::OnUpdate() {
		auto gm = GameManager::GetGM();

		m_jumpCoolDown += App::GetApp()->GetElapsedTime();
		m_damageCoolDown += App::GetApp()->GetElapsedTime();
		if (m_damageCoolDown >= 1.7f) {
			m_isDamegeCoolDown = true;
		}
		else {
			m_isDamegeCoolDown = false;
		}
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		if (ptrDraw) {
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);
		}

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());

		//�X�e�[�g�}�V���X�V
		m_StateMachine->Update();
		
	}
	void Player::OnUpdate2() {
		//������̕\��
		//DrawStrings();
	}

	//A�{�^��
	void Player::OnPushA() {
	}

	//������̕\��
	void Player::DrawStrings() {

		//������\��
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring fpsStr(L"FPS: ");
		fpsStr += Util::UintToWStr(fps);
		fpsStr += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		fpsStr += Util::FloatToWStr(ElapsedTime);
		fpsStr += L"\n";

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring gravStr(L"GravityVelocoty:\t");
		auto gravVelocity = GetComponent<Gravity>()->GetGravityVelocity();
		gravStr += L"X=" + Util::FloatToWStr(gravVelocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Y=" + Util::FloatToWStr(gravVelocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		gravStr += L"Z=" + Util::FloatToWStr(gravVelocity.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring animName(L"AnimationName:\t");
		auto NowEnemy = GameManager::GetGM()->GetNowEnemyNum();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		animName += ptrDraw->GetCurrentAnimation() + L"\t"+ Util::IntToWStr(NowEnemy) + L"\n";
		wstring greenPer(L"Percentage:\t");
		auto per = GameManager::GetGM()->GetGreenPer();
		greenPer += Util::FloatToWStr(per, 2, Util::FloatModify::Fixed) + L"%\t\n";

		auto ptrPlant = GetStage()->GetSharedGameObject<Plant>(L"A");
		wstring plant(L"IsRun:\t");
		auto isRun = ptrPlant->GetIsRun();
		if (isRun) {
			plant += L"true\t IsMaxScale:\t";
		}
		else {
			plant += L"false\t IsMaxScale:\t";

		}
		if (ptrPlant->GetIsMaxCircleScale() == true) {
			plant += L"true\n";
		}
		else {
			plant += L"false\n";
		}

		wstring NowStateName(L"NowStateName:\t");
		NowStateName += GetNowStateName() + L"\n";

		auto ptrNum = GetStage()->GetSharedGameObject<ScoreSprite>(L"Number");
		wstring GreenPercent(L"Percent:\t");
		GreenPercent += Util::FloatToWStr(ptrNum->GetPercent(), 6, Util::FloatModify::Fixed) + L"\n";

		wstring EreaName(L"EreaName:\t");
		EreaName += m_nowEreaName + L"\n";

		wstring str = fpsStr + positionStr + gravStr + animName + greenPer + plant + NowStateName + GreenPercent + EreaName;


		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void Player::KnockBackBehaviour() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (m_KnockBack.FrameCount > m_KnockBack.Time) {
			m_KnockBack.FrameCount = 0.0f;
			ptrDraw->SetDrawActive(true);
			m_StateMachine->Reset(PlayerDefaultState::Instance());
			return;
		}
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		ptrTrans->SetPosition(myPos + m_KnockBackVec * m_KnockBackSpeed);
		if (ptrDraw->GetDrawActive() == false) {
			ptrDraw->SetDrawActive(true);
		}
		else if (ptrDraw->GetDrawActive() == true) {
			ptrDraw->SetDrawActive(false);
		}
		if(ptrDraw->GetCurrentAnimation() != L"Damage"){
			ptrDraw->ChangeCurrentAnimation(L"Damage");
		}
		m_KnockBack.FrameCount += ElapsedTime;
	}

	void Player::DamageEffect() {



	}


	void Player::OnCollisionEnter(shared_ptr<GameObject>& Obj) {
		if (Obj->FindTag(L"Enemy")) {
			if (GetNowStateName() != L"KnockBackState" && m_isDamegeCoolDown == true) {
				VeloMake(Obj);
				Player::GetStateMachine()->Push(PlayerKnockBackState::Instance());
			}
		}
	}
	// �A�j���[�V������ς���֐�
	void Player::ChangeAnim(wstring animName) {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->ChangeCurrentAnimation(animName);
	}
	// �R���{�^�C�}�[
	void Player::AttackComboTimer() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		// �R���{���������Ԍv��
		if (ptrDraw->IsTargetAnimeEnd()) {
			m_attackComboTimer -= App::GetApp()->GetElapsedTime();
			m_isAttack = false;
		}
		// �������ԗ�������R���{���Z�b�g
		if (m_attackComboTimer < 0.0f) {
			m_attackCombo = 0;
			m_attackComboTimer = GameManager::GetGM()->GetPlayerComboMaxTime();
			Player::GetStateMachine()->Pop();

		}
	}

	// �U���̏���
	void Player::Attack() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_StateMachine->Push(PlayerAttackState::Instance());
			}
		}
	}
	
	void Player::AttackAnimPlay(int animNum) {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		wstring anim = L"Attack" + Util::IntToWStr(animNum);
		if (ptrDraw->GetCurrentAnimation() != anim && m_NowStateName== L"PlayerAttackState" && animNum != 0) {
			ChangeAnim(anim);
		}
	}

	void Player::VeloMake(shared_ptr<GameObject>& obj) {
		auto ptrEnemy = dynamic_pointer_cast<EnemyObject>(obj);
		auto enemyPos = ptrEnemy->GetComponent<Transform>()->GetPosition();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto velo = enemyPos - myPos;
		m_KnockBackVec = velo.normalize();
		m_KnockBackVec.x *= -1.0f;
		m_KnockBackVec.z *= -1.0f;
		m_KnockBackVec.y = 0.0f;
	}
	void Player::ComboCheck() {
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		AttackComboTimer();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
				m_isAttack = true;
				switch (m_attackCombo)
				{
				case 0:
					m_attackCombo += 1;
					AttackAnimPlay(m_attackCombo);

					break;
				case 1:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				case 2:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				case 3:
					if (ptrDraw->IsTargetAnimeEnd()) {
						m_attackCombo = 0;
						m_attackCombo += 1;
						AttackAnimPlay(m_attackCombo);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	//�v���C���[�̃X�e�[�g
	//--------------------------------------------------------------------------------------
	///	�ʏ�X�e�[�g
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerDefaultState)
		void PlayerDefaultState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"DefaultState");
	}

	void PlayerDefaultState::Execute(const shared_ptr<Player>& Obj) {
		auto gm = GameManager::GetGM();
		if (gm->GetIsPlayerActive()) {
			Obj->MovePlayer();
		}
		Obj->Attack();
	}

	void PlayerDefaultState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	///	�v���C���[�m�b�N�o�b�N�X�e�[�g
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerKnockBackState)
		void PlayerKnockBackState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"KnockBackState");
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Start(L"PlayerDamage", 0, 1.0f);	
	}

	void PlayerKnockBackState::Execute(const shared_ptr<Player>& Obj) {
		Obj->KnockBackBehaviour();
		Obj->DamageEffect();
	}

	void PlayerKnockBackState::Exit(const shared_ptr<Player>& Obj) {
		Obj->GetComponent<PNTBoneModelDraw>()->SetDrawActive(true);
	}
	//--------------------------------------------------------------------------------------
	/// �A�^�b�N�X�e�[�g
	//--------------------------------------------------------------------------------------
	IMPLEMENT_SINGLETON_INSTANCE(PlayerAttackState)
		void PlayerAttackState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetNowStateName(L"PlayerAttackState");
		Obj->SetCombo(1);
		Obj->AttackAnimPlay(Obj->GetCombo());
		Obj->SetIsAttack(true);
	}

	void PlayerAttackState::Execute(const shared_ptr<Player>& Obj) {
		Obj->AttackMove();
		Obj->ComboCheck();
		Obj->AttackComboTimer();
	}

	void PlayerAttackState::Exit(const shared_ptr<Player>& Obj) {
		Obj->SetIsAttack(false);
	}
	//---------------------------------------------------------------------
	/// �v���C���[�̘r�̓����蔻��A�U�����ɂ����A�N�e�B�u��!!!!!
	//---------------------------------------------------------------------
	ArmCollision::ArmCollision(const shared_ptr<Stage>& Stage, const shared_ptr<Player>& ParentPtr, const wstring positionName, const int BoneNum,Vec3 &LocalPosition) :
		GameObject(Stage),
		m_parentPtr(ParentPtr),
		m_positionName(positionName),
		m_selectBoneNum(BoneNum),
		m_position(LocalPosition)
	{

	}

	void ArmCollision::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(1.5f));
		auto mesh = MeshResource::CreateCube(0.5f);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		mesh->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		ptrDraw->SetOriginalMeshResource(mesh);
		ptrDraw->SetOriginalMeshUse(true);
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->AddExcludeCollisionTag(L"Player");
		ptrColl->AddExcludeCollisionTag(L"FixedBox");
		ptrColl->AddExcludeCollisionTag(L"Wall");
		ptrColl->AddExcludeCollisionTag(L"weapon");

		AddTag(L"weapon");
		ptrColl->SetAfterCollision(AfterCollision::None);
		SetDrawActive(false);
	}

	void ArmCollision::OnUpdate() {
		//CollActive();
		PositionSet();
	}
	void ArmCollision::PositionSet() {
		auto bonePtr = m_parentPtr;
		auto boneTrans = bonePtr->GetComponent<Transform>();
		auto boneDraw = bonePtr->GetComponent<PNTBoneModelDraw>();

		auto& bones = boneDraw->GetVecLocalBones();

		Mat4x4 mat = bones[m_selectBoneNum];
		auto mesh = boneDraw->GetMeshResource();
		vector<Vec3> positions;
		mesh->GetLocalPositions(positions);

		Mat4x4 localMat;
		Vec3 LocalPos(1.0f, 0.0f, 0.0f);


		localMat.translation(m_position);
		localMat *= mat;
		localMat *= boneTrans->GetWorldMatrix();

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(localMat.transInMatrix());
		auto Qt = localMat.quatInMatrix();
		ptrTrans->SetQuaternion(Qt);
	}
	void ArmCollision::CollActive() {
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto ptrColl = GetComponent<CollisionObb>();
		if (ptrPlayer->GetStateMachine()->GetTopState()->GetStateName() == L"PlayerAttackState") {
			ptrColl->SetAfterCollision(AfterCollision::Auto);
		}
		else {
			ptrColl->SetAfterCollision(AfterCollision::None);
		}
	}
}
//end basecross

