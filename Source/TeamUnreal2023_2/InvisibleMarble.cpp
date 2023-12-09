// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleMarble.h"
#include "Components/SphereComponent.h" //�ڱ��� - ���Ǿ� ��� �߰�

// Sets default values
AInvisibleMarble::AInvisibleMarble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // �ڱ��� - ������Ʈ ����
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    
    // �ڱ��� - ����ƽ ������Ʈ ����
    ShpereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShpereMesh"));
    ShpereMesh->SetupAttachment(SphereComponent);

    // �ڱ��� - ����ƽ �޽� �ε�
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (StaticMeshAsset.Succeeded())
    {
        ShpereMesh->SetStaticMesh(StaticMeshAsset.Object);
    }

    // �ڱ��� - �� ũ�� ����
    SphereComponent->SetSphereRadius(50.f);

    // �ڱ��� - �� ��Ƽ���� ����
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/NewMaterial.NewMaterial"));
    if (MaterialAsset.Succeeded())
    {
        MyMaterial = MaterialAsset.Object;
        ShpereMesh->SetMaterial(0, MyMaterial);
    }

    // �ڱ��� - ���� �ҷ�����
    static ConstructorHelpers::FClassFinder<AActor> BPThirdPersonCharacterClassFinder(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));
    if (BPThirdPersonCharacterClassFinder.Succeeded())
    {
        BPThirdPersonCharacterClass = BPThirdPersonCharacterClassFinder.Class;
    }

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AInvisibleMarble::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AInvisibleMarble::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvisibleMarble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInvisibleMarble::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass() == BPThirdPersonCharacterClass)
    {
        Destroy();
    }
}