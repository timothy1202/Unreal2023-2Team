// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurretPawn::ATurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//박광훈 - 스태틱 메쉬 할당
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	//박광훈 - 스태틱 메쉬 회전
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//박광훈 - 폰 감지 컴포넌트 할당
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	//박광훈 - 폰 감지
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ATurretPawn::OnSeePlayer);
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretPawn::OnSeePlayer(APawn* Pawn)
{
	ATeamUnreal2023_2Character* ThirdPerson = Cast<ATeamUnreal2023_2Character>(Pawn);
	UE_LOG(LogTemp, Warning, TEXT("P1111cted"));
	if (ThirdPerson)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player detected"));
		// 감지된 폰이 BP_ThirdPerson인 경우에만 액터가 BP_ThirdPerson을 향하도록 회전 값을 계산하고 설정합니다.
		FVector MyLocation = GetActorLocation();
		FVector TargetLocation = ThirdPerson->GetActorLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
		SetActorRotation(NewRotation);
	}
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

