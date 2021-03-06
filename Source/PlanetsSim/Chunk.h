// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FastNoiseWrapper.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Chunk.generated.h"

UCLASS()
class PLANETSSIM_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	int PolySize = 128;
	int VerticesQuantity = 10;
	float UVScale = 3.0f;
	int HeighScale = 1200;
	int Vertices = 0;
	// int Size = 115;

	UMaterialInterface* LandscapeMat;
	TArray<int32> Triangles;
	TArray<FVector> Vertex;
	TArray<FVector2d> UVs;
	TArray<FLinearColor> VertexColors;
	TArray<FVector> normals;
	TArray<FProcMeshTangent> tangents;

	virtual void SpawnChunk();

protected:
	UPROPERTY(VisibleAnywhere)
	
	UProceduralMeshComponent* Mesh;
	UFastNoiseWrapper* NoiseRef;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
