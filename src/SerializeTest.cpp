#include "SerializeTest.h"

namespace StarBangBang
{
    SerializeTest::SerializeTest(int id) : ISerializable(id)
    {

    }

    std::ostream& SerializeTest::Save(std::ostream& os) const
    {
        os.write(reinterpret_cast<const char*>(this), sizeof(SerializeTest));
        return os;
    }

    std::istream& SerializeTest::Load(std::istream& is)
    {
        test = 0;
        is.read(reinterpret_cast<char*>(this), sizeof(SerializeTest));
        printf("Serialization Test: %d", test);
        return is;
    }

}

