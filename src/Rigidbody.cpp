#include "Rigidbody.h"
using namespace StarBangBang;

Rigidbody::Rigidbody(AEVec2 _position, float _mass, float _gravityScale = 1.0f)
{
	position = _position;
	mass = _mass;
	inv_mass = 1.0f / mass;
	gravityScale = _gravityScale;

}

