// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalItem.h"

AnimalItem::AnimalItem() : GameItem()
{
}

AnimalItem::~AnimalItem()
{
}

void AnimalItem::Parse(const TSharedPtr<FJsonObject>& _jsonObject)
{
	GameItem::Parse(_jsonObject);
	
}
