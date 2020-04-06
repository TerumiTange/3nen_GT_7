#include "Ending.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input())
{
}

Ending::~Ending()
{
}

void Ending::Init()
{
	input->Init();
}

void Ending::Update()
{
	if (input->GetKeyDown(A))
	{
		NextScene();
	}
}

void Ending::Draw()
{
}

void Ending::NextScene()
{
	mSceneChanger->ChangeScene(SceneTitle);
}
