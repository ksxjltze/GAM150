#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
namespace StarBangBang
{
	
	class Color
	{
	private:
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	public:
		Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
		{
			this->r = r >= 0 && r <= 1.0f ? r : 1.0f;
			this->g = g >= 0 && g <= 1.0f ? g : 1.0f;
			this->b = b >= 0 && b <= 1.0f ? b : 1.0f;
			this->a = a >= 0 && a <= 1.0f ? a : 1.0f;
		

		}
		constexpr float R() const { return r; }
		constexpr float G() const { return g; }
		constexpr float B() const { return b; }
		constexpr float A() const { return a; }
		
	};
	
	 const Color Red();
	 const Color White();
	 const Color Blue();
	 const Color Green();
	 const Color Black();
	 const Color Cyan();
	
	

	void InitBasicMesh();

	void DrawBoxWired(AEVec2 size, AEVec2 pos, Color color = White());

	void DrawBox(AEVec2 size, AEVec2 pos , Color color = White());

	void DrawCircle(float radius, AEVec2 pos, Color color = White());

	void DrawLine(float length, AEVec2 pos, float angle, Color color = White());

	void FreeUnitMeshes(void);

}