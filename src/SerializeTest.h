#pragma once
#include "ISerializable.h"

namespace StarBangBang
{
	class SerializeTest : private ISerializable
	{
	public:
		int test { 0 };
	private:
		//temp
		friend class LevelEditor;

		SerializeTest(int id);
		std::ostream& Save(std::ostream&);
		std::istream& Load(std::istream&);

	};

}