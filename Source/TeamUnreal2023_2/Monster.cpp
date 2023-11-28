// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

// Sets default values
AMonster::AMonster()
{
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BehaviorWidget"));
	BehaviorWidget->SetupAttachment(RootComponent);
	BehaviorWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
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

	this->UILookCamera();
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::UILookCamera()
{
	FVector UILocation = BehaviorWidget->GetComponentLocation();
	FVector cameraLoction = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();

	FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(UILocation, cameraLoction);

	BehaviorWidget->SetWorldRotation(newRotation);
}

