#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Image.h"
#include "ColliderAABB.h"
#include "Drag.h"

namespace TempTeam
{
	class TestObject : public GameObject
	{
	public:
		void Init();
		void Update();
		void Draw();
		void Exit();
	private:
		Image image;
		ColliderAABB collider;
		Drag dragComponent;
		
	};
}