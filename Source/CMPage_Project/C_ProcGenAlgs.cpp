// Fill out your copyright notice in the Description page of Project Settings.

#include <deque>
#include "Math/UnrealMathUtility.h"
#include "C_ProcGenAlgs.h"


//using namespace std;
std::vector<TArray<TArray<AC_DungeonTile*>>> UC_ProcGenAlgs::binarySpacePartitioning(TArray<TArray<AC_DungeonTile*>> fullGrid, int32 minWidth, int32 minHeight)
{
	UE_LOG(LogTemp, Warning, TEXT("test"));
	std::deque<TArray<TArray<AC_DungeonTile*>>> roomsQueue = {fullGrid};
	std::vector<TArray<TArray<AC_DungeonTile*>>> roomsList;
	//roomsQueue.push_back(fullGrid);
	
	while (roomsQueue.size() > 0) 
	{
	
	
		TArray<TArray<AC_DungeonTile*>> room = roomsQueue[0];
		roomsQueue.pop_front();
		if (room.Num() >= minWidth && room[0].Num() >= minHeight)
		{
			
			if (rand()%10 >5) 
			{
				UE_LOG(LogTemp, Warning, TEXT("test2"));
				if (room[0].Num() >= minHeight * 2) 
				{
					splitGridYaxis(minWidth,roomsQueue,room);
				}
				else if (room.Num() >= minWidth * 2)
				{
					splitGridXaxis(minHeight, roomsQueue, room);
				}
				else if (room.Num() >= minWidth && room[0].Num() >= minHeight)
				{
					roomsList.push_back(room);
				}
			}
			else 
			{
				if (room.Num() >= minWidth * 2)
				{
					splitGridXaxis(minHeight, roomsQueue, room);
				}
				else if (room[0].Num() >= minHeight * 2)
				{
					splitGridYaxis(minWidth, roomsQueue, room);
				}
				else if (room.Num() >= minWidth && room[0].Num() >= minHeight)
				{
					roomsList.push_back(room);
				}
			}
		}
	}

	return std::vector<TArray<TArray<AC_DungeonTile*>>>();
}

void UC_ProcGenAlgs::splitGridXaxis(int32 minHeight, std::deque<TArray<TArray<AC_DungeonTile*>>> roomQueue, TArray<TArray<AC_DungeonTile*>> room)
{

}

void UC_ProcGenAlgs::splitGridYaxis(int32 minWidth, std::deque<TArray<TArray<AC_DungeonTile*>>> roomQueue, TArray<TArray<AC_DungeonTile*>> room)
{
	int32 ySplit = rand() % room[0].Num();
	TArray<TArray<AC_DungeonTile*>> room1;
	TArray<TArray<AC_DungeonTile*>> room2;
	room1.SetNumZeroed(minWidth);
	//for (int i = 0; i < DungeonGrid.Num(); i++)
	//{
	//	DungeonGrid[i].SetNumZeroed(DungeonSize);
	//}
}
