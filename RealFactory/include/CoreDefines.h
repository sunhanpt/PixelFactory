#pragma once;

#if _DEBUG
#define check(_Condition_) assert(_Condition_);
#else
#define check(_Condition_)
#endif