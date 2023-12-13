// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TurretBullet.h"

// Sets default values
ATurretPawn::ATurretPawn()
{
	//박광훈 - 루트 전용 콜리전박스 할당
	RootCollisionBox = CreateDefaultSubobject< UBoxComponent>(TEXT("RootCollisionBox"));
	RootCollisionBox->SetupAttachment(RootComponent);

	//박광훈 - 스태틱 메쉬 할당
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootCollisionBox);

	//박광훈 - 스태틱 메쉬 회전
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//박광훈 - 폰 감지 컴포넌트 할당
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	//박광훈 - 방향 컴포넌트 할당
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MyArrowComponent"));
	ArrowComponent->SetupAttachment(StaticMeshComponent);

}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &ATurretPawn::DelayedFunction, 0.2f, false);
}

void ATurretPawn::DelayedFunction()
{

		FVector Location = ArrowComponent->GetComponentLocation();
		FRotator Rotation = ArrowComponent->GetComponentRotation();
		FActorSpawnParameters SpawnParams;

		ATurretBullet* NewActor = GetWorld()->SpawnActor<ATurretBullet>(ATurretBullet::StaticClass(), Location, Rotation, SpawnParams);
	/*if (NewActor)
	{
		NewActor->ScaleDownSphereComponent();
		NewActor->TurnOffGravity();
	}*/
}

//박광훈 - 터렛의 회전값 계산
void ATurretPawn::CustomEvent(APawn* Pawn)
{
	ATeamUnreal2023_2Character* ThirdPerson = Cast<ATeamUnreal2023_2Character>(Pawn);
	if (ThirdPerson)
	{
		// 감지된 폰이 BP_ThirdPerson인 경우에만 액터가 BP_ThirdPerson을 향하도록 회전 값을 계산하고 설정합니다.
		FVector MyLocation = GetActorLocation();
		FVector TargetLocation = ThirdPerson->GetActorLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
		SetActorRotation(NewRotation);
	}
	DelayedFunction();
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


