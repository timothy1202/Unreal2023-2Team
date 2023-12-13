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
	//�ڱ��� - ��Ʈ ���� �ݸ����ڽ� �Ҵ�
	RootCollisionBox = CreateDefaultSubobject< UBoxComponent>(TEXT("RootCollisionBox"));
	RootCollisionBox->SetupAttachment(RootComponent);

	//�ڱ��� - ����ƽ �޽� �Ҵ�
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootCollisionBox);

	//�ڱ��� - ����ƽ �޽� ȸ��
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//�ڱ��� - �� ���� ������Ʈ �Ҵ�
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	//�ڱ��� - ���� ������Ʈ �Ҵ�
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

//�ڱ��� - �ͷ��� ȸ���� ���
void ATurretPawn::CustomEvent(APawn* Pawn)
{
	ATeamUnreal2023_2Character* ThirdPerson = Cast<ATeamUnreal2023_2Character>(Pawn);
	if (ThirdPerson)
	{
		// ������ ���� BP_ThirdPerson�� ��쿡�� ���Ͱ� BP_ThirdPerson�� ���ϵ��� ȸ�� ���� ����ϰ� �����մϴ�.
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


