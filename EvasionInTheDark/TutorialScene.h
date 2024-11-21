#pragma once
class TutoUi;

class TutorialScene : public Scene
{
protected:
	TutoUi* tutoUi;


public:
	TutorialScene();
	virtual ~TutorialScene() = default;

	void Init();
	void Release();

	void Enter();
	void Exit();

	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);

};

