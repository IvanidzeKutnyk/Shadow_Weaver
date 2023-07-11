#pragma once

#include "CoreMinimal.h"

class SHADOW_WEAVER_API DebugSystem
{
public:
	DebugSystem();
	~DebugSystem();

public: 
	static void ShowIntoLog_Int(FString _fromclass,FString _Name,int _value);
	static void ShowIntoLog_FString(FString _fromclass,FString _Name, FString _value);
};
