// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
// #include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AMyActor::AMyActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	bCanBeCollected = true;
	ToggleableOption = 0;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Make sure we have a valid material to create from.
	if (ParentMaterial != nullptr)
	{
		// Create the dynamic material instance using the static Create method.
		MID = UMaterialInstanceDynamic::Create(ParentMaterial, this);
		
		// Assign the material to Mesh Component.
		MeshComponent->SetMaterial(0, MID);
	}
}

void AMyActor::ChangeColorTo()
{
	// It is important to check if MID is valid.
	if (MID != nullptr)
	{
		// Set the color to NewColor value.
		MID->SetVectorParameterValue(FName("Color"), NewColor);
	}
}

void AMyActor::CollectMe(bool bDestroy /*= true*/)
{
	// Check if this actor can be collected...
	if (bCanBeCollected)
	{
		// ...Now check if the actor must be destroyed...
		if (bDestroy)
		{
			// ...Actor has to be destroyed so log that information and destroy.
			UE_LOG(LogTemp, Log, TEXT("Actor collected and destroyed."));
			Destroy();
		}
		else
		{
			// ...Dont destroy the actor. Just log the information.
			UE_LOG(LogTemp, Warning, TEXT("Actor collected but not destroyed."));
		}
	}
	else
	{
		// ...Actor cannot be collected thus cannot be destroyed. 
		UE_LOG(LogTemp, Error, TEXT("Actor not collected."));
	}
}
