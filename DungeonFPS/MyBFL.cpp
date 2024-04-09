// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBFL.h"

#include "MaterialCompiler.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

FHitResult UMyBFL::FindClosestHitResult(const FVector Center, const TArray<FHitResult> HitResults, float& Distance)
{
	FHitResult Output_Hitresult = HitResults[0];
	
	for (FHitResult hitresult : HitResults)
	{
		if (UKismetMathLibrary::Vector_Distance(hitresult.ImpactPoint, Center) <= UKismetMathLibrary::Vector_Distance(Output_Hitresult.ImpactPoint, Center))
		{
			Output_Hitresult = hitresult;
			Distance = UKismetMathLibrary::Vector_Distance(Output_Hitresult.ImpactPoint, Center);
		}
	}
	
	return Output_Hitresult;
}

void UMyBFL::CalBloodDecalTransform(const FHitResult HitResult, const float Radius, bool& CanSpawn, FTransform& SpawnTransform)
{
	TArray<AActor*> IgnoredActors;
	TArray<FHitResult> Sphere_Hitresults;
	FHitResult Closest_Hitresult;
	float Distance;
	if (UKismetSystemLibrary::SphereTraceMulti(GEngine->GameViewport->GetWorld(),HitResult.ImpactPoint, HitResult.ImpactPoint + FVector(0.0, 0.0, 0.001),
		Radius, TraceTypeQuery1, false, IgnoredActors, EDrawDebugTrace::None,
		Sphere_Hitresults, true))
	{
		Closest_Hitresult = FindClosestHitResult(HitResult.Location, Sphere_Hitresults, Distance);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,FString(Closest_Hitresult.Location.ToString()),  true);

		SpawnTransform = FTransform(UKismetMathLibrary::MakeRotFromX(Closest_Hitresult.ImpactNormal),
									Closest_Hitresult.ImpactPoint,FVector::OneVector);
		CanSpawn = true;
	}
	else
	{
		CanSpawn = false;
	}
	
}

void UMyBFL::GetRandomItemWithWeights(const TArray<int> Weights, int& Index)
{
	int TotalWeight = 0;
	for (const int Weight : Weights)
	{
		TotalWeight += Weight;
	}
	const int RandomInt = FMath::RandRange(1, TotalWeight);
	int Temp_Total = 0;
	for (int index = 0; index <= Weights.Num(); index++ )
	{
		int Weight = Weights[index];
		Temp_Total += Weight;
		if (Temp_Total >= RandomInt)    //Pick this item
		{
			Index = index;
			return;
		}
	}
}
