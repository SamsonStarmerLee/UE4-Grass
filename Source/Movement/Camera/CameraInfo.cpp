// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraInfo.h"

bool FCameraInfo::Equals(const FCameraInfo& Other) const
{
	FCameraInfo delta;
	delta.FOV = FOV - Other.FOV;
	delta.SpringArmLength = SpringArmLength - Other.SpringArmLength;
	return delta.IsZero();
}

bool FCameraInfo::IsZero() const
{
	return FMath::Abs(FOV) < SMALL_NUMBER && 
		   FMath::Abs(SpringArmLength) < SMALL_NUMBER;
}