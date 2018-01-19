#ifndef __U_LEVEL__
#define __U_LEVEL__

#include "Object.h"
#include <vector>

class AActor;
class ULevel : public UObject
{
public:
	ULevel() {}
	virtual ~ULevel() {}
public:
	std::vector<AActor*> Actors;
};

#endif // !__U_LEVEL__
