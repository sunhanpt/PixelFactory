#ifndef __U_OBJECT__
#define __U_OBJECT__

// The base class of all objects. 
class UObject
{
public:
	UObject() {}
	virtual ~UObject() {}

	/**
	* Do any object-specific cleanup required immediately after loading an object,
	* and immediately after any undo/redo.
	*/
	virtual void PostLoad();

	/**
	* Called before destroying the object.  This is called immediately upon deciding to destroy the object, to allow the object to begin an
	* asynchronous cleanup process.
	*/
	virtual void BeginDestory();

	/**
	* Called to check if the object is ready for FinishDestroy.  This is called after BeginDestroy to check the completion of the
	* potentially asynchronous object cleanup.
	* @return True if the object's asynchronous cleanup has completed and it is ready for FinishDestroy to be called.
	*/
	virtual bool IsReadyForFinishDestroy() { return true; }

	/**
	* Called to finish destroying the object.  After UObject::FinishDestroy is called, the object's memory should no longer be accessed.
	*
	* note: because properties are destroyed here, Super::FinishDestroy() should always be called at the end of your child class's
	* FinishDestroy() method, rather than at the beginning.
	*/
	virtual void FinishDestory();

	/** UObject serializer. */
	//virtual void Serialize();

	virtual class UWorld* GetWorld() const;
};

#endif