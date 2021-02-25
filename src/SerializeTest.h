#pragma once
#include "ISerializable.h"

namespace StarBangBang
{
	class SerializeTest : public ISerializable
	{
	public:
		SerializeTest(int id);
		int test { 69 };
	private:
		//temp
		friend class Serialization;

		std::ostream& Save(std::ostream&) const;
		std::istream& Load(std::istream&);

	};

}