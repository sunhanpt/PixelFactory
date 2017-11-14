#pragma once

#include "Platform.h"

/** Contains CPU utilization data. */
struct FCPUTime
{
	/** Initialization constructor. */
	FCPUTime(float InCPUTimePct, float InCPUTimePctRelative)
		: CPUTimePct(InCPUTimePct)
		, CPUTimePctRelative(InCPUTimePctRelative)
	{}

	FCPUTime& operator+=(const FCPUTime& Other)
	{
		CPUTimePct += Other.CPUTimePct;
		CPUTimePctRelative += Other.CPUTimePctRelative;
		return *this;
	}

	/** Percentage CPU utilization for the last interval. */
	float CPUTimePct;

	/** Percentage CPU utilization for the last interval relative to one core,
	** so if CPUTimePct is 8.0% and you have 6 core this value will be 48.0%. */
	float CPUTimePctRelative;
};

/**
* Generic implementation for most platforms
**/
struct FGenericPlatformTime
{
	/**
	* Get the system date
	*
	* @param Dest Destination buffer to copy to
	* @param DestSize Size of destination buffer in characters
	* @return Date string
	*/
	static TCHAR* StrDate(TCHAR* Dest, SIZE_T DestSize);
	/**
	* Get the system time
	*
	* @param Dest Destination buffer to copy to
	* @param DestSize Size of destination buffer in characters
	* @return Time string
	*/
	static TCHAR* StrTime(TCHAR* Dest, SIZE_T DestSize);

	/**
	* Returns a timestamp string built from the current date and time.
	* NOTE: Only one return value is valid at a time!
	*
	* @return timestamp string
	*/
	static const TCHAR* StrTimestamp();

	/**
	* Returns a pretty-string for a time given in seconds. (I.e. "4:31 min", "2:16:30 hours", etc)
	*
	* @param Seconds Time in seconds
	* @return Time in a pretty formatted string
	*/
	static FString PrettyTime(double Seconds);

	/** Updates CPU utilization, called through a delegate from the Core ticker. */
	static bool UpdateCPUTime(float DeltaTime)
	{
		return false;
	}

	/**
	* @return structure that contains CPU utilization data.
	*/
	static FCPUTime GetCPUTime()
	{
		return FCPUTime(0.0f, 0.0f);
	}

	/**
	* @return seconds per cycle.
	*/
	static double GetSecondsPerCycle()
	{
		return SecondsPerCycle;
	}
	/** Converts cycles to milliseconds. */
	static float ToMilliseconds(const uint32 Cycles)
	{
		return (float)double(SecondsPerCycle * 1000.0 * Cycles);
	}

	/** Converts cycles to seconds. */
	static float ToSeconds(const uint32 Cycles)
	{
		return (float)double(SecondsPerCycle * Cycles);
	}
	/**
	* @return seconds per cycle.
	*/
	static double GetSecondsPerCycle64();
	/** Converts cycles to milliseconds. */
	static double ToMilliseconds64(const uint64 Cycles)
	{
		return ToSeconds64(Cycles) * 1000.0;
	}

	/** Converts cycles to seconds. */
	static double ToSeconds64(const uint64 Cycles)
	{
		return GetSecondsPerCycle64() * double(Cycles);
	}

protected:

	static double SecondsPerCycle;
	static double SecondsPerCycle64;
};