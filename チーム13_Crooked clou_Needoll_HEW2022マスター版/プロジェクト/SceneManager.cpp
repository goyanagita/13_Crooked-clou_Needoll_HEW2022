#include "SceneManager.h"
#include "StageSelect.h"


//===================================================================
// コンストラクタ
//===================================================================
SceneManager::SceneManager():m_NextScene(eScene::NONE)
{
	m_Scene = (BaseScene*) new Title(this);
}

//=============================================================================
// 初期化処理
//=============================================================================
void SceneManager::Init()
{
	m_Scene->Init();
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneManager::Uninit()
{
	if (m_Scene != nullptr) {

		m_Scene->Uninit();
		delete m_Scene;
		m_Scene = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneManager::Upadate()
{
	//次のシーンがセットされていたら
	if (m_NextScene != eScene::NONE) {
		m_Scene->Uninit();
		//ステージの情報取得
		if (stage_select) {
			stage_next = m_Scene->GetStage();
			if(stage_info < stage_next)
				stage_info = stage_next;
			stage_select = false;
		}
		if(m_Scene != nullptr)
			delete m_Scene;

		switch (m_NextScene) {
		case eScene::TITLE:
			m_Scene = (BaseScene*) new Title(this);
			break;

		//宮部追加
		case eScene::SELECT:
			m_Scene = (BaseScene*) new StageSelect(this);
			stage_select = true;
			break;

		case eScene::GAME:
			m_Scene = (BaseScene*) new Game(this);
			m_Scene->SetStageInfo(stage_next);
			break;
		case eScene::GAMEOVER:
			m_Scene = (BaseScene*) new GameOver(this);
			stage_next = stage_info;
			break;
		case eScene::GAMECLEAR:
			m_Scene = (BaseScene*) new GameClear(this);
			break;
		}
		m_NextScene = eScene::NONE;
		m_Scene->Init();
		if (stage_select) {
			m_Scene->SetStageInfo(stage_info);
		}
	}
	m_Scene->Update();
	//タイトルでの終了処理
	exit_check = m_Scene->ExitCheck();
	game_exit = m_Scene->ErrorCheck();
	
	
	if ((stage_clear && stage_select)|| stage_info > stage_next) {
		//ごーるしたよ
		//ステージセレクトのclearフラグを立てる
		m_Scene->SetClear();
		stage_clear = false;
	}
	stage_clear = m_Scene->CheckClear();
	if (exit_check == true) {
		m_Scene->Uninit();
		delete m_Scene;
		m_Scene = nullptr;
		
	}

	//異常終了時
	if (game_exit == true) {
		m_Scene->Uninit();
		delete m_Scene;
		m_Scene = nullptr;
		exit(1);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneManager::Draw()
{
	m_Scene->Draw();
}

//=============================================================================
// シーン遷移処理
//=============================================================================
void SceneManager::ChangeScene(eScene NextScene)
{
	m_NextScene = NextScene;
}
