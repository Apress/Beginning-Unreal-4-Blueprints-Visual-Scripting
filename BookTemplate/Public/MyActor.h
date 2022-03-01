// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class BOOKTEMPLATE_API AMyActor : public AActor
{
	GENERATED_BODY()

private:

	/* Our root component for this actor. We can assign a Mesh to this component using Mesh variable. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	/* Material to be used as the parent for Material Instance Dynamic.*/
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ParentMaterial;

	/* Cached reference to the instance created. */
	UPROPERTY()
	class UMaterialInstanceDynamic* MID;

	/* Use this color in MID. */
	UPROPERTY(EditAnywhere)
	FLinearColor NewColor;

	/* Determines if this item can be collected. */
	UPROPERTY(EditAnywhere)
	bool bCanBeCollected;

	/* Just an example to show toggleable option using metadata specifier. */
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bCanBeCollected"))
	int32 ToggleableOption;
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	/* This is the same as Construction Script in Blueprints */
	virtual void OnConstruction(const FTransform& Transform) override;

	/* We create the same function from Blueprint which can change the color in MID. */
	UFUNCTION(BlueprintCallable, Category = "My Actor")
	void ChangeColorTo();

	/* Collect this actor. Blueprint exposed example function. This also acts as a tooltip in Blueprint Graph. */
	UFUNCTION(BlueprintCallable, Category = "My Actor")
	void CollectMe(bool bDestroy = true);

};
