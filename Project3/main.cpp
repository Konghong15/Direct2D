#include <functional>
#include <map>
#include <string>

#include "GameObject.h"
#include "Transform.h"
#include "ObjectManager.h"

struct json
{
	std::map<std::string, std::string> KeyValue;
};

class ISerialize
{
	virtual void SerializeOut(json& object) = 0;
	virtual void SerializeIn(json& object) = 0;
};

class TempComponent : public ISerialize
{
	virtual void SerializeOut(json& object)
	{
		// do something
	}

	virtual void SerializeIn(json& object)
	{
		// do something
	}

private:
	int mData1;
	float mData2;
	std::string mData3;
};


int main(void)
{
	using namespace d2dFramework;

	std::map<std::string, std::function<ISerialize* (void)>> creator;
	creator["TempComponent"] = []() -> ISerialize*
	{
		return new TempComponent();
	};

	// ISerialize* serialize = creator[jsonObject["className"]]();
	// srialize.SerializeIn(jsonObject["className"]);
}