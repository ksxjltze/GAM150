#include "Serialization.h"
#include <fstream>

void StarBangBang::Serialization::SaveObject(ISerializable const& sObject)
{
	std::ofstream ofs;
	ofs.open("../Resources/test.bin", std::fstream::binary | std::ostream::trunc);
	if (ofs.is_open())
	{
		sObject.Save(ofs);
		ofs.close();
	}
	else
		fprintf(stderr, "Object Manager: ERROR WRITING TO FILE");
}

void StarBangBang::Serialization::LoadObject(ISerializable& sObject)
{
	std::ifstream ifs;
	ifs.open("../Resources/test.bin");

	if (ifs.is_open())
	{
		sObject.Load(ifs);
		ifs.close();
	}
	else
		fprintf(stderr, "Object Manager: ERROR READING FILE");
}
