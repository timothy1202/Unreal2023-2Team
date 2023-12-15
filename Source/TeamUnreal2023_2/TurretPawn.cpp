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

	//박광훈 - 스태틱 메쉬 할당
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//박광훈 - 스태틱 메쉬 회전
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//박광훈 - 폰 감지 컴포넌트 할당
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	//박광훈 - 방향 컴포넌트 할당
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MyArrowComponent"));
	ArrowComponent->SetupAttachment(StaticMeshComponent);

	// 음영준 - 총알 할당
	static ConstructorHelpers::FClassFinder<ATurretBullet> BP_Bullet(L"Blueprint'/Game/BP_TurretBullet.BP_TurretBullet_C'");
	BulletClass = BP_Bullet.Class;
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	// 음영준 - "폰 보기 시"이벤트 바인딩
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ATurretPawn::OnSeePawn);
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 음영준 - 만약 플레이어가 감지 되면 발사 쿨타임을 증가시킴
	if (PawnSensingComponent->CouldSeePawn(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		time += DeltaTime;
	}
}

void ATurretPawn::OnSeePawn(APawn* Pawn)
{
	if (ATeamUnreal2023_2Character* character = Cast<ATeamUnreal2023_2Character>(Pawn))
	{
		// 감지된 폰이 BP_ThirdPerson인 경우에만 액터가 BP_ThirdPerson을 향하도록 회전 값을 계산하고 설정합니다.
		FVector MyLocation = GetActorLocation();
		FVector TargetLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);
		SetActorRotation(NewRotation);

		// 음영준 - 만약 발사 쿨타임이 임의로 지정한 쿨타임시간을 초과하게 되면 LauchBullet을 통해 총알 발사
		if (time >= launchCoolTime)
		{
			time = 0.f;
			LaunchBullet();
		}
	}
}

//박광훈 - 터렛의 회전값 계산
void ATurretPawn::LaunchBullet()
{
	FVector Location = ArrowComponent->GetComponentLocation();
	FRotator Rotation = ArrowComponent->GetComponentRotation();
	FActorSpawnParameters SpawnParams;

	ATurretBullet* NewActor = GetWorld()->SpawnActor<ATurretBullet>(BulletClass, Location, Rotation, SpawnParams);
}