#pragma once
#include <iostream>

//Abstract class
//Classes that implement this interface will be able to be serialized and deserialized from a binary file.
namespace StarBangBang
{
	class ISerializable
	{
	protected:
		ISerializable(int id) : id{ id } {}
		virtual std::ostream& Save(std::ostream&) const = 0;
		virtual std::istream& Load(std::istream&) = 0;
	private:
		friend class Serialization;
		const int id;

	};

}