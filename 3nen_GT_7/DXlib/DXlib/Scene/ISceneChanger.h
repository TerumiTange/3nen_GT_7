#pragma once

typedef enum 
{
	SceneTitle,
	SceneGamePlay,
	SceneEnding,
	SceneNone
}SceneType;

//シーンを変更するためのインターフェイスクラス
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//指定シーンに変更する
	virtual void ChangeScene(SceneType nextScene) = 0;
};