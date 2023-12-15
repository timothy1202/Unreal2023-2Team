// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "TeamUnreal2023_2Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TurretBullet.h"

// Sets default values
ATurretPawn::ATurretPawn() : launchCoolTime(0.5f), time(launchCoolTime)
{

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	//�ڱ��� - ����ƽ �޽� �Ҵ�
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//�ڱ��� - ����ƽ �޽� ȸ��
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//�ڱ��� - �� ���� ������Ʈ �Ҵ�
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	//�ڱ��� - ���� ������Ʈ �Ҵ�
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MyArrowComponent"));
	ArrowComponent->SetupAttachment(StaticMeshComponent);

	// ������ - �Ѿ� �Ҵ�
	static ConstructorHelpers::FClassFinder<ATurretBullet> BP_Bullet(L"Blueprint'/Game/BP_TurretBullet.BP_TurretBullet_C'");
	BulletClass = BP_Bullet.Class;
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	// ������ - "�� ���� ��"�̺�Ʈ ���ε�
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ATurretPawn::OnSeePawn);
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������ - ���� �÷��̾ ���� �Ǹ� �߻� ��Ÿ���� ������Ŵ
	if (PawnSensingComponent->CouldSeePawn(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		time += DeltaTime;
	}
}

void ATurretPawn::OnSeePawn(APawn* Pawn)
{
	if (ATeamUnreal2023_2Character* character = Cast<ATeamUnreal2023_2Character>(Pawn))
	{
		// ������ ���� BP_ThirdPerson�� ��쿡�� ���Ͱ� BP_ThirdPerson�� ���ϵ��� ȸ�� ���� ����ϰ� �����մϴ�.
		FVector MyLocation = GetActorLocation();
		FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
		SetActorRotation(NewRotation);

		// ������ - ���� �߻� ��Ÿ���� ���Ƿ� ������ ��Ÿ�ӽð��� �ʰ��ϰ� �Ǹ� LauchBullet�� ���� �Ѿ� �߻�
		if (time >= launchCoolTime)
		{
			time = 0.f;
			LaunchBullet();
		}
	}
}

//�ڱ��� - �ͷ��� ȸ���� ���
void ATurretPawn::LaunchBullet()
{
	FVector Location = ArrowComponent->GetComponentLocation();
	FRotator Rotation = ArrowComponent->GetComponentRotation();
	FActorSpawnParameters SpawnParams;

	ATurretBullet* NewActor = GetWorld()->SpawnActor<ATurretBullet>(BulletClass, Location, Rotation, SpawnParams);
}