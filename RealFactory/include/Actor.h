#ifndef __ACTOR__
#define __ACTOR__

#include "UObject.h"
#include <vector>
class ULevel;
class UActorComponent;
class AActor : public UObject
{
public:
	AActor() {}
	virtual ~AActor() {}

public:
	virtual void Tick(float detaSeconds);

	ULevel* GetLevel() const;

protected:
	class USceneComponent* RootComponent;
	std::vector<AActor*> Children;
	std::vector<UActorComponent*> OwnedComponents;
};

#endif // !__ACTOR__
