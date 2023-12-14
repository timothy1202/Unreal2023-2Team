// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "ConstructorHelpers.h"

// Sets default values
ATurretBullet::ATurretBullet()
{
	//¹Ú±¤ÈÆ - ½ºÇÇ¾î ÄÄÆ÷³ÍÆ® Ãß°¡
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	SphereComponent->SetCollisionProfileName("Bullet");
	RootComponent = SphereComponent;

	//¹Ú±¤ÈÆ - ÇÁ·ÎÁ§Å¸ÀÏ¹«ºê¸ÕÆ® ÄÄÆ÷³ÍÆ® Ãß°¡
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyProjectileMovementComponent"));

	//¹Ú±¤ÈÆ - ½ºÅÂÆ½¸Þ½¬ ÄÄÆ÷³ÍÆ® Ãß°¡
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SphereComponent);

	//¹Ú±¤ÈÆ - ½ºÅÂÆ½ ¸Þ½¬ ÇÒ´ç
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	//¹Ú±¤ÈÆ - ¸ÓÆ¼¸®¾ó ÇÒ´ç
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("'/Engine/MapTemplates/Materials/BasicAsset02.BasicAsset02'"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComponent->SetMaterial(0, MaterialAsset.Object);
	}
}

//¹Ú±¤ÈÆ - ½ºÇÇ¾îÄÄÆ÷³ÍÆ® Å©±â Á¶Á¤
void ATurretBullet::ScaleDownSphereComponent()
{
	if (SphereComponent)
	{
		FVector NewScale = FVector(0.05f, 0.05f, 0.05f);
		SphereComponent->SetWorldScale3D(NewScale);
	}

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurretBullet::OnBeginOverlap);
}

//À½¿µÁØ - ÃÑ¾ËÀÌ ÇÃ·¹ÀÌ¾îÇÑÅ× ´ê¾ÒÀ» ¶§ ÃÑ¾Ë ¾ø¾Ú
void ATurretBullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherComp->ComponentHasTag("Player")))
	{
		Destroy();
	}
}

//¹Ú±¤ÈÆ - Áß·Â ²ô´Â ÇÔ¼ö
void ATurretBullet::TurnOffGravity()
{
	if (SphereComponent)
	{
		SphereComponent->SetEnableGravity(false);
	}
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetEnableGravity(false);
	}
}

// Called when the game starts or when spawned
void ATurretBullet::BeginPlay()
{
	Super::BeginPlay();
	ScaleDownSphereComponent();
	TurnOffGravity();
}

// Called every frame
void ATurretBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

