#ifndef __U_WORLD__
#define __U_WORLD__

#include "Object.h"

class FSceneInterface;
class UWorld final: public UObject
{
public:

	FSceneInterface*				Scene;

public:
	UWorld() {}
	virtual ~UWorld() {}
};
#endif