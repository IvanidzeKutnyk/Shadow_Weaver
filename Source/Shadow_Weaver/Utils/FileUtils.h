#pragma once

#include "CoreMinimal.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

class FJsonObject;

class SHADOW_WEAVER_API FileUtils
{

public:
	static bool CheckFileExist(const FString& _FilePath);
	static bool ReadFileSTR(const FString& _FilePath, FString& _OutputData);
	static bool WriteFileSTR(const FString& _FilePath, FString& _InputData);

	static TSharedPtr<FJsonObject> ReadJson(const FString& _FilePath);
	static bool CreateJsonObjectFromString(const FString& _OutputData, TSharedPtr<FJsonObject>& _JsonObject);
	static bool CreateStringFromJsonObject(FString& _OutputData, const TSharedPtr<FJsonObject>& _JsonObject);
	static void WriteJson(const FString& _FilePath, TSharedPtr<FJsonObject> _JsonObject);

public:
	FileUtils();
	~FileUtils();
};
