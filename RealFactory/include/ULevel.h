#ifndef __U_LEVEL__
#define __U_LEVEL__

#include "UObject.h"
#include <vector>

class AActor;
class ULevel : public UObject
{
public:
	ULevel() {}
	virtual ULevel() {}
property:
	std::vector<AActor*> Actors;
};

#endif // !__U_LEVEL__
