// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BehaviorWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> BPUserWidget(L"Blueprint'/Game/ThirdPerson/Blueprints/BehaviorUI.BehaviorUI_C'");
	if (BPUserWidget.Class != NULL)
	{
		BehaviorWidget->SetWidgetClass(BPUserWidget.Class);
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

