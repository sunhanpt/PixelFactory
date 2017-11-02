#ifndef __U_WORLD__
#define __U_WORLD__

class FSceneInterface;
class UWorld
{
public:

	FSceneInterface*				Scene;

public:
	UWorld() {}
	virtual ~UWorld() {}
};
#endif