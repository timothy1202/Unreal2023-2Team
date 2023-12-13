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

// Called when the game starts or when spawned
void ATurretBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

