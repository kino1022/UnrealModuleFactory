// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionAbility.h"
#include "Character/CharacterBase.h"


ACharacterBase* UActionAbility::GetOwnerCharacter () const {
	return Cast<ACharacterBase>(GetAvatarActorFromActorInfo());
}

