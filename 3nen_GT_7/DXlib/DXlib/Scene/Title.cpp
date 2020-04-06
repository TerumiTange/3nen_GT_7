#include "Title.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input())
{
}

Title::~Title()
{
}

void Title::Init()
{
	input->Init();
}

void Title::Update()
{
	if (input->GetKeyDown(A))
	{
		NextScene();
	}
}

void Title::Draw()
{
}

void Title::NextScene()
{
	mSceneChanger->ChangeScene(SceneGamePlay);
}
