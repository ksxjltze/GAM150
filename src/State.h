#pragma once

class State
{
public:
	State(int id) { this->id = id; }
	inline int getID() { return id; }
	virtual void Load() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Free() = 0;
	virtual void Unload() = 0;
private:
	int id;
};