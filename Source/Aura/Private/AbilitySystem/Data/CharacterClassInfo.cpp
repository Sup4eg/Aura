// Copyright Fireteam Interactive


#include "Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(const ECharacterClass CharacterClass) const
{
    return CharacterClassInformation.FindChecked(CharacterClass);
}