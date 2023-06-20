// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"

void WeaponItem::Parse(const TSharedPtr<FJsonObject>& _jsonObject)
{
	GameItem::Parse(_jsonObject);
}

WeaponItem::WeaponItem() : GameItem()
{

}

WeaponItem::~WeaponItem()
{
}
