// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_DungeonTile.h"
#include <vector>
#include <deque>
#include "UObject/NoExportTypes.h"
#include "C_ProcGenAlgs.generated.h"


/**
 * 
 */
UCLASS()
class CMPAGE_PROJECT_API UC_ProcGenAlgs : public UObject
{
	GENERATED_BODY()
public:
	std::vector< TArray<TArray<AC_DungeonTile*>>> binarySpacePartitioning(TArray<TArray<AC_DungeonTile*>> fullGrid, int32 minWidth,int32 minHeight);
private:
	void splitGridXaxis(int32 minWidth, int32 minHeight, std::deque<TArray<TArray<AC_DungeonTile*>>> roomQueue, TArray<TArray<AC_DungeonTile*>> room);
	void splitGridYaxis(int32 minWidth, int32 minHeight, std::deque<TArray<TArray<AC_DungeonTile*>>> roomQueue, TArray<TArray<AC_DungeonTile*>> room);
};
