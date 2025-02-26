// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
	startLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}
void AMovingPlatform::MovePlatform(float DeltaTime)
{

	if (ShoulPlatformReturn())
	{
		FVector MoveDirection = platformVelocity.GetSafeNormal();
		startLocation = startLocation + MoveDirection * MovedDistance;
		SetActorLocation(startLocation);
		platformVelocity = -platformVelocity;
	}
	else
	{
		FVector currentLocation = GetActorLocation();
		currentLocation = currentLocation + (platformVelocity * DeltaTime);
		SetActorLocation(currentLocation);
	}
}
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
bool AMovingPlatform::ShoulPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistance;
}
float AMovingPlatform::GetDistanceMoved() const
{
	float distance = FVector::Distance(startLocation, GetActorLocation());
	return distance;
}