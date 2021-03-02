#pragma once
#include "ISerializable.h"

namespace StarBangBang
{
	class Serialization
	{
	public:
		static void SaveObject(ISerializable const& sObject);
		static void LoadObject(ISerializable& sObject);
	};

}