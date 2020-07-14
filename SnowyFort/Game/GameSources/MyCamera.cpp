/*!
@file MyPlayerCamera.cpp
@brief カメラ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyPlayerCamera::MyPlayerCamera():
		Camera(),
		m_MovePosition(0,0,0),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0,0,0),
		m_ArmLen(20.0f),
		m_ArmHeight(5.0f),
		m_RadXZ(0.0f),
		m_RotSpeed(1.0f),
		m_LRBaseMode(true)
	{}

	MyPlayerCamera::~MyPlayerCamera(){}

	shared_ptr<GameObject> MyPlayerCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyPlayerCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	float MyPlayerCamera::GetArmLengh() const {
		return m_ArmLen;
	}

	void MyPlayerCamera::SetArmLengh(const float& armLength) {
		m_ArmLen = armLength;
	}

	float MyPlayerCamera::GetArmHeight()const {
		return m_ArmHeight;
	}
	void MyPlayerCamera::SetArmHeight(const float& armHeight) {
		m_ArmHeight = armHeight;
	}

	void MyPlayerCamera::SetArmParam(const float& armLength, const float& armHeight) {
		m_ArmLen = armLength;
		m_ArmHeight = armHeight;
	}

	bool MyPlayerCamera::IsLRBaseMode() const {
		return m_LRBaseMode;
	}

	void MyPlayerCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}

	void MyPlayerCamera::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//前回のターンからの時間
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto playerPtr = GetTargetObject();

		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}

		auto keyData = App::GetApp()->GetInputDevice().GetKeyState();
		// キーボード入力で回転処理を行う
		if (!(keyData.m_bPushKeyTbl['A'] && keyData.m_bPushKeyTbl['D'])) {
			//Aボタン
			if (keyData.m_bPushKeyTbl['A']) {
				if (IsLRBaseMode()) {
					fThumbLX = -1.0f;
				}
				else {
					fThumbLX = 1.0f;
				}
			}
			//Dボタン
			if (keyData.m_bPushKeyTbl['D']) {
				if (IsLRBaseMode()) {
					fThumbLX = 1.0f;
				}
				else {
					fThumbLX = -1.0f;
				}
			}
			if (abs(m_RadXZ) >= XM_2PI) {
				//1週回ったら0回転にする
				m_RadXZ = 0;
			}
		}

		//入力を受け取る
		if (IsLRBaseMode()) {
			m_RadXZ += -fThumbLX * elapsedTime * m_RotSpeed;
		}
		else {
			m_RadXZ += fThumbLX * elapsedTime * m_RotSpeed;
		}


		if (playerPtr) {
			m_MovePosition = Vec3(m_ArmLen * cosf(-m_RadXZ), playerPtr->GetComponent<Transform>()->GetPosition().y + m_ArmHeight, m_ArmLen * sinf(-m_RadXZ));
		}

		SetAt(GetAt());
		SetEye(m_MovePosition);
		Camera::OnUpdate();
	}

	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	//構築と破棄
	ObjCamera::ObjCamera() :
		Camera(),
		m_RadXZ(0.0f),
		m_RadY(0.0f),
		m_RotSpeed(5.0f),
		m_Atlength(6.0f)
	{}

	void ObjCamera::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//前回のターンからの時間
		float elapsedTime = App::GetApp()->GetElapsedTime();

		float fThumbRX = 0.0f;
		float fThumbRY = 0.0f;
		if (cntlVec[1].bConnected) {
			fThumbRX = cntlVec[1].fThumbRX;
			fThumbRY = cntlVec[1].fThumbRY;
		}

		m_RadXZ += -fThumbRX * elapsedTime * m_RotSpeed;

		//xの角度制限
		if (abs(m_RadXZ) >= XM_2PI) {
			//1週回ったら0回転にする
			m_RadXZ = 0;
		}

		//yの角度制限
		if (m_RadY <= XM_PIDIV4 && m_RotSpeed >= -XM_PIDIV4) {
			m_RadY += fThumbRY * elapsedTime * m_RotSpeed;
		}
		if (m_RadY >= XM_PIDIV4) {
			m_RadY = XM_PIDIV4;
		}
		else if (m_RadY <= -XM_PIDIV4) {
			m_RadY = -XM_PIDIV4;
		}
		Vec3 newAt(0,0,0);
		auto cameraman = GetTargetObject();
		if (cameraman) {
			auto cameraPos = cameraman->GetComponent<Transform>()->GetPosition();
			newAt = Vec3(cameraPos.x + m_Atlength * cosf(m_RadXZ), cameraPos.y + m_Atlength * sinf(m_RadY), cameraPos.z + m_Atlength * sinf(m_RadXZ));
		}
		SetAt(newAt);
		Camera::OnUpdate();
	}

	shared_ptr<GameObject> ObjCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void ObjCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}
}