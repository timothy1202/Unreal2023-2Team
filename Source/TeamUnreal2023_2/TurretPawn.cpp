// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ATurretPawn::ATurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�ڱ��� - ����ƽ �޽� �Ҵ�
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	//�ڱ��� - ����ƽ �޽� ȸ��
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//�ڱ��� - �� ���� ������Ʈ �Ҵ�
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

