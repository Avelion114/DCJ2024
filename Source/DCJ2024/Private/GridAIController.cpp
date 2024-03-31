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
		int32 Lowest = 0;
		for (int32 i = 0; i < OpenNodes.Num(); i++)
		{
			if (*GI->GridSpaces.Find(OpenNodes[i]) < *GI->GridSpaces.Find(OpenNodes[Lowest]))
			{
				Lowest = i;
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Lowest: %i"), Lowest);

		for (auto I : OpenNodes)
		{
			auto G = GI->GridSpaces.Find(I);
			UE_LOG(LogTemp, Warning, TEXT("Point: %s, G: %i, H: %i, F: %i"), *I.ToString(), G->GCost, G->HCost, G->GetFCost());
		}

		FIntPoint Current = OpenNodes[Lowest];
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
				FIntPoint Diff = FIntPoint{ FMath::Abs(G.X - Target.X), FMath::Abs(G.Y - Target.Y) };
				GI->GridSpaces[G].HCost = Diff.X + Diff.Y;

				Diff = FIntPoint{ FMath::Abs(G.X - Current.X), FMath::Abs(G.Y - Current.Y) };
				GI->GridSpaces[G].GCost = GI->GridSpaces.Find(Current)->GCost + (Diff.X + Diff.Y);

				GI->GridSpaces[G].Parent = Current;
				OpenNodes.Add(G);
			}
		}
	}
}
