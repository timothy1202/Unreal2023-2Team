// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MonsterBehavior.h"

#include "Monster.generated.h"

UCLASS()
class TEAMUNREAL2023_2_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EMonsterBehavior> myBehavior;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* BehaviorWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 새로 추가한 함수
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "UI")
	void SetUI(const EMonsterBehavior& newBevior);

	void SetUIRef();
	void UILookCamera();
	
};
