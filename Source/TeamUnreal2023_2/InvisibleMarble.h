// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisibleMarble.generated.h"

UCLASS()
class TEAMUNREAL2023_2_API AInvisibleMarble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvisibleMarble();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/// <summary>
	/// ¹Ú±¤ÈÆ - ½ºÇÇ¾î ÄÄÆ÷³ÍÆ®
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Sphere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

public:
	/// <summary>
	/// ¹Ú±¤ÈÆ - ¸ÓÆ¼¸®¾ó ÄÄÆ÷³ÍÆ®
	/// </summary>
	UPROPERTY(EditAnyWhere)
	class UMaterial* MyMaterial;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* ShpereMesh;

	/// <summary>
	/// ¹Ú±¤ÈÆ - ¿À¹ö·¦ ÇÔ¼ö
	/// </summary>
	/// <param name="OverlappedComp"></param>
	/// <param name="OtherActor"></param>
	/// <param name="OtherComp"></param>
	/// <param name="OtherBodyIndex"></param>
	/// <param name="bFromSweep"></param>
	/// <param name="SweepResult"></param>
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// ¹Ú±¤ÈÆ - Ä³½ºÆÃÀ» À§ÇÑ º¯¼ö
	/// </summary>
	UPROPERTY()
	TSubclassOf<class AActor> BPThirdPersonCharacterClass;
};
