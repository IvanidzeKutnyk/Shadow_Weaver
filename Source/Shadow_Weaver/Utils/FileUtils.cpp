// Fill out your copyright notice in the Description page of Project Settings.


#include "FileUtils.h"

bool FileUtils::CheckFileExist(const FString& _FilePath)
{

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*_FilePath)) 
	{
		return true;
	}
	
	return false;
}

bool FileUtils::ReadFileSTR(const FString& _FilePath, FString& _OutputData)
{
	if (CheckFileExist(_FilePath) && FFileHelper::LoadFileToString(_OutputData, *_FilePath))
	{
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error: Try to read non-existent file")); // Check Error
	return false;
}

bool FileUtils::WriteFileSTR(const FString& _FilePath, FString& _InputData)
{
	if (CheckFileExist(_FilePath) && FFileHelper::SaveStringToFile(_InputData, *_FilePath))
	{
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error: Try to write to non-existent file")); // Check Error 
	return false;
}

bool FileUtils::CreateJsonObjectFromString(const FString& _OutputData, TSharedPtr<FJsonObject>& _JsonObject)
{

	if (FJsonSerializer::Deserialize(TJsonReaderFactory<TCHAR>::Create(_OutputData), _JsonObject))
	{
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error: Try to create JsonObject.")); // Check Error 
	return false;
}

bool FileUtils::CreateStringFromJsonObject(FString& _OutputData, const TSharedPtr<FJsonObject>& _JsonObject)
{
	if (FJsonSerializer::Serialize(_JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&_OutputData, 0)))

	{
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("Error: Try to create String.")); // Check Error 
	return false;
}

TSharedPtr<FJsonObject> FileUtils::ReadJson(const FString& _FilePath)
{
	FString JsonString = "";
	
	if (!ReadFileSTR(_FilePath, JsonString))
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> JsonObject;
	
	CreateJsonObjectFromString(JsonString, JsonObject);
	
	return JsonObject;
	
}

void FileUtils::WriteJson(const FString& _FilePath, TSharedPtr<FJsonObject> _JsonObject)
{
	FString JsonString = "";
	if (!CreateStringFromJsonObject(JsonString, _JsonObject)) 
	{
		return;
	}

	if (!WriteFileSTR(_FilePath, JsonString))
	{
		return;
	}
}

FileUtils::FileUtils()
{
}

FileUtils::~FileUtils()
{
}
