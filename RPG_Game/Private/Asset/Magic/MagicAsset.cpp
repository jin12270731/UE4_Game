// Fill out your copyright notice in the Description page of Project Settings.


#include "Asset/Magic/MagicAsset.h"

FPrimaryAssetId UMagicAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(GetClass()->GetFName(), GetOutermost()->GetFName());
}
