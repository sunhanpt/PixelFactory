#ifndef __F_SCENEMANAGER__
#define __F_SCENEMANAGER__

// An interface to the private scene manager implementationo of a scene. ‰÷»æscene¿‡
class UPrimitiveComponent;
class ULightComponent;

class FSceneInterface
{
public:
	/**
	* Adds a new primitive component to the scene
	*
	*@param Primitive - primitive component to add
	*/
	virtual void AddPrimitive(UPrimitiveComponent * Primitive) = 0;

	virtual void RemovePrimitive(UPrimitiveComponent * Primitive) = 0;

	virtual void ReleasePrimitive(UPrimitiveComponent * Primitive) = 0;

	virtual void UpdatePrimitiveTransform(UPrimitiveComponent* Primitive) = 0;

	virtual void UpdatePrimitiveAttachment(UPrimitiveComponent* Primitive) = 0;

	virtual void AddLight(ULightComponent* Light) = 0;

	virtual void RemoveLight(ULightComponent* Light) = 0;


public:
	virtual ~FSceneInterface() {}
};
#endif