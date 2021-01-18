#include "State.h"
#include "ObjectManager.h"

namespace StarBangBang
{
	class TestState2 : public State
	{
	public:
		TestState2();
		virtual void Load();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual void Free();
		virtual void Unload();
	private:
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
		GameObject* object1;
	};
}