// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "ConstructorHelpers.h"

// Sets default values
ATurretBullet::ATurretBullet()
{
	//�ڱ��� - ���Ǿ� ������Ʈ �߰�
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComponent"));
	RootComponent = SphereComponent;

	//�ڱ��� - ������Ÿ�Ϲ����Ʈ ������Ʈ �߰�
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyProjectileMovementComponent"));

	//�ڱ��� - ����ƽ�޽� ������Ʈ �߰�
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SphereComponent);

	//�ڱ��� - ����ƽ �޽� �Ҵ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}

	//�ڱ��� - ��Ƽ���� �Ҵ�
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

