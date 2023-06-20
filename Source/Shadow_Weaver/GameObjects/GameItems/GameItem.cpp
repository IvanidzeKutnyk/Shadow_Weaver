// Fill out your copyright notice in the Description page of Project Settings.


#include "GameItem.h"

void GameItem::SetId(int _id)
{
	this->m_id = _id;
}

int GameItem::GetId()
{
	return this->m_id;
}

void GameItem::Parse(const TSharedPtr<FJsonObject>& _jsonObject)
{
	_jsonObject->TryGetNumberField("ID", this->m_id);
}


GameItem::GameItem()
	: m_id(0)
{
}

GameItem::~GameItem()
{
}
