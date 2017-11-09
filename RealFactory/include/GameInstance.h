#ifndef __GAMEINSTANCE_H__
#define __GAMEINSTANCE_H__

#include "Object.h"

class UGameInstance : public UObject
{
public:
	UGameInstance() {}
	virtual ~UGameInstance() {}

public:
	class UWorld* GetWorld() const;
	class UEngine* GetEngine() const;
	class UGameViewportClient* GetGameViewportClient() const;

	virtual void StartGameInstance();
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown();
};

#endif
