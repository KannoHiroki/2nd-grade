/*!
@file ProjectBehavior.h
@brief �v���W�F�N��`�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�R���g���[���̃{�^���̃n���h��
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�L�[�{�[�h�̎擾�i�D��j
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushB();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['X']) {
				Obj->OnPushX();
				return;
			}
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//B�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//X�{�^��
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
			}
		}

		//2P�ȏ�p
		void PushHandle(const shared_ptr<T>& Obj, const int& PlayerNum) {
			//�R���g���[���̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[PlayerNum].bConnected) {
				//A�{�^��
				if (cntlVec[PlayerNum].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//B�{�^��
				if (cntlVec[PlayerNum].wButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//X�{�^��
				if (cntlVec[PlayerNum].wButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				//Y�{�^��
				if (cntlVec[PlayerNum].wPressedButtons & XINPUT_GAMEPAD_Y) {
					Obj->OnPushY();
				}
			}
		}
	};

}

//end basecross

