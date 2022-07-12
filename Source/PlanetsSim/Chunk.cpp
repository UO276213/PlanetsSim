// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Asignamos como componente raíz un ProceduralMeshComponent
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
	Mesh->bUseAsyncCooking = true;
	Mesh->SetCastShadow(false);
	SetRootComponent(Mesh);

	// Creamos el objeto que nos permite calcular el ruido de Perlin
	NoiseRef = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("FastNoiseWrapper"), false);
	NoiseRef->SetupFastNoise(EFastNoise_NoiseType::SimplexFractal, 1337, 0.0001, EFastNoise_Interp::Quintic, EFastNoise_FractalType::FBM, 6);
}

// Called when the game starts or when spawned

void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

void AChunk::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	SpawnChunk();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChunk::SpawnChunk()
{
	FVector ChunkLocation = GetActorLocation();

	Triangles.Empty();
	Vertex.Empty();
	UVs.Empty();

	for (int TempY = 0; TempY < VerticesQuantity; TempY++)
	{
		for (int TempX = 0; TempX < VerticesQuantity - 1; TempX++)
		{
			// Create triangles
			Triangles.Add(Vertices);
			Triangles.Add(Vertices + VerticesQuantity);
			Triangles.Add(Vertices + 1);
			Triangles.Add(Vertices + 1);
			Triangles.Add(Vertices + VerticesQuantity);
			Triangles.Add(Vertices + VerticesQuantity + 1);
			
			float NoiseAtLocation = NoiseRef->GetNoise2D(ChunkLocation.X + TempX * PolySize, ChunkLocation.Y + TempY * PolySize);
			
			// Create vertex
			Vertex.Add(FVector(TempX * PolySize, TempY * PolySize, NoiseAtLocation * HeighScale));

			// Create UVMap
			UVs.Add(FVector2d(TempX / (VerticesQuantity - 1), TempY / (VerticesQuantity - 1)));

			Vertices++;
		}
	}


	Mesh->CreateMeshSection_LinearColor(0, Vertex, Triangles, normals, UVs, VertexColors, tangents, true);
}
