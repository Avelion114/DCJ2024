// Fill out your copyright notice in the Description page of Project Settings.


#include "GridAIController.h"
#include "DungeonCrawlerGameInstance.h"

TArray<FIntPoint> AGridAIController::GetPathToLocation(FIntPoint Start, FIntPoint Target)
{

	UDungeonCrawlerGameInstance* GI = Cast<UDungeonCrawlerGameInstance>(GetWorld()->GetGameInstance());
	GI->ResetCostData();


	TArray<FIntPoint> OpenNodes;
	TArray<FIntPoint> ClosedNodes;

	OpenNodes.Add(Start);

	while (true)
	{
		//Sort the OpenNodes array by the GridSpace with the lowest F or H Cost
		TSortedMap<FGridSpaceData*, FIntPoint> Data;
		for (auto I : OpenNodes)
		{
			Data.Add(GI->GridSpaces.Find(I), I);
		}

		Data.GenerateValueArray(OpenNodes);

		FIntPoint Current = OpenNodes[0];
		ClosedNodes.Add(Current);
		OpenNodes.Remove(Current);

		if (Current == Target)
		{
			TArray<FIntPoint> Path;
			FIntPoint Coord = Current;
			while (Coord != Start)
			{
				Path.Add(Coord);
				Coord = GI->GridSpaces.Find(Coord)->Parent;
			}
			return Path;
		}
		
		//Get neighboring tiles
		TArray<FIntPoint> Neighbors;
		if (GI->GridSpaces.Find(Current + FIntPoint{ 1,0 })) { Neighbors.Add(Current + FIntPoint{ 1,0 }); }
		if (GI->GridSpaces.Find(Current + FIntPoint{ 0,1 })) { Neighbors.Add(Current + FIntPoint{ 0,1 }); }
		if (GI->GridSpaces.Find(Current + FIntPoint{ -1,0 })) { Neighbors.Add(Current + FIntPoint{ -1,0 }); }
		if (GI->GridSpaces.Find(Current + FIntPoint{ 0,-1 })) { Neighbors.Add(Current + FIntPoint{ 0,-1 }); }

		//Set Costs
		for (auto G : Neighbors)
		{
			if (ClosedNodes.Find(G) == INDEX_NONE)
			{
				FIntPoint Diff = FIntPoint{ FMath::Abs(G.X - Start.X), FMath::Abs(G.Y - Start.Y) };
				GI->GridSpaces[G].GCost = Diff.X + Diff.Y;

				Diff = FIntPoint{ FMath::Abs(G.X - Current.X), FMath::Abs(G.Y - Current.Y) };
				GI->GridSpaces[G].HCost = GI->GridSpaces.Find(Current)->HCost + (Diff.X + Diff.Y);

				GI->GridSpaces[G].Parent = Current;
				OpenNodes.Add(G);
			}
		}
	}
}
