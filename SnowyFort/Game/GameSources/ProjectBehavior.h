/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//キーボードの取得（優先）
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushB();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['X']) {
				Obj->OnPushX();
				return;
			}
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Bボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//Xボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
			}
		}

		//2P以上用
		void PushHandle(const shared_ptr<T>& Obj, const int& PlayerNum) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[PlayerNum].bConnected) {
				//Aボタン
				if (cntlVec[PlayerNum].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//Bボタン
				if (cntlVec[PlayerNum].wButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//Xボタン
				if (cntlVec[PlayerNum].wButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				//Yボタン
				if (cntlVec[PlayerNum].wPressedButtons & XINPUT_GAMEPAD_Y) {
					Obj->OnPushY();
				}
			}
		}
	};

}

//end basecross

