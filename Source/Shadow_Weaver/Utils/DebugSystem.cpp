// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugSystem.h"

DebugSystem::DebugSystem()
{
}

DebugSystem::~DebugSystem()
{
}

void DebugSystem::ShowIntoLog_Int(FString _fromclass, FString _Name, int _value)
{
	UE_LOG(LogTemp, Warning, TEXT("( %s )-> | %s : ( %i )"), *_fromclass, *_Name, _value);
}

void DebugSystem::ShowIntoLog_FString(FString _fromclass, FString _Name, FString _value)
{
	UE_LOG(LogTemp, Warning, TEXT("( %s )-> | %s : ( %s )"), *_fromclass, *_Name, *_value);
}
