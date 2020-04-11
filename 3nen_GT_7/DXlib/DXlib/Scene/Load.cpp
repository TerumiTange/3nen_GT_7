#include "Load.h"
#include "DxLib.h"
#include <memory>

Load::Load():
	number(Number::zero),
	Graph()
{
	Graph = LoadGraph("./Assets/Texture/Load.png");
}

Load::~Load()
{
	End();
}

void Load::Start()
{
	DrawGraph(0, 0, Graph, TRUE);
	DeleteGraph(Graph);
}

void Load::Loading()
{
	switch (number)
	{
	case zero:
		number = Number::first;
		WaitTimer(1000);
		End();
		break;
	case first:
		Graph = LoadGraph("./Assets/Texture/Load1.png");
		DrawGraph(0, 0, Graph, TRUE);
		DeleteGraph(Graph);
		number = Number::second;
		WaitTimer(1000);
		End();
		break;
	case second:
		Graph = LoadGraph("./Assets/Texture/Load2.png");
		DrawGraph(0, 0, Graph, TRUE);
		DeleteGraph(Graph);
		number = Number::third;
		WaitTimer(1000);
		End();
		break;
	case third:
		Graph = LoadGraph("./Assets/Texture/Load3.png");
		DrawGraph(0, 0, Graph, TRUE);
		DeleteGraph(Graph);
		number = Number::fourth;
		WaitTimer(1000);
		End();
		break;
	case fourth:
		Graph = LoadGraph("./Assets/Texture/Load4.png");
		DrawGraph(0, 0, Graph, TRUE);
		DeleteGraph(Graph);
		number = Number::fifth;
		WaitTimer(1000);
		End();
		break;
	case fifth:
		Graph = LoadGraph("./Assets/Texture/Load5.png");
		DrawGraph(0, 0, Graph, TRUE);
		DeleteGraph(Graph);
		number = Number::first;
		WaitTimer(1000);
		End();
		break;
	default:
		break;
	}
}

void Load::End()
{
	ClearDrawScreen();
}
