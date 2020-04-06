#pragma once

typedef enum 
{
	SceneTitle,
	SceneGamePlay,
	SceneEnding,
	SceneNone
}SceneType;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger
{
public:
	virtual ~ISceneChanger() = 0;
	//�w��V�[���ɕύX����
	virtual void ChangeScene(SceneType nextScene) = 0;
};