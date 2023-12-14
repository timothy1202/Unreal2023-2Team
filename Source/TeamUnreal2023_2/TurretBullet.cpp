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
	SphereComponent->SetCollisionProfileName("Bullet");
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

//�ڱ��� - ���Ǿ�������Ʈ ũ�� ����
void ATurretBullet::ScaleDownSphereComponent()
{
	if (SphereComponent)
	{
		FVector NewScale = FVector(0.05f, 0.05f, 0.05f);
		SphereComponent->SetWorldScale3D(NewScale);
	}

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurretBullet::OnBeginOverlap);
}

//������ - �Ѿ��� �÷��̾����� ����� �� �Ѿ� ����
void ATurretBullet::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != this) && (OtherComp->ComponentHasTag("Player")))
	{
		Destroy();
	}
}

//�ڱ��� - �߷� ���� �Լ�
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

