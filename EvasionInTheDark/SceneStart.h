#pragma once
#include "Scene.h"

class Logo;
class TitleUi;

class SceneStart :
    public Scene
{
protected:
	Logo* logo;
	TitleUi* titleUi;

public:
	SceneStart();
	virtual ~SceneStart() = default;

	void Init();
	void Release();

	void Enter();
	void Exit();

	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
};

