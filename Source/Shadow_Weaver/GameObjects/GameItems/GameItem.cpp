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

void GameItem::Parse()
{

}


GameItem::GameItem()
{
}

GameItem::~GameItem()
{
}
