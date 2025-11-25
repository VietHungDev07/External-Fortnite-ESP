#pragma once

#include <windows.h>

namespace Offset
{
// World:
	const uintptr_t UWorld = 0x175448B8;
//LocalPlayer:
	const uintptr_t OwningGameInstance = 0x248;
	const uintptr_t LocalPlayers = 0x38;
	const uintptr_t PlayerController = 0x30;
	const uintptr_t AcknowledgedPawn = 0x358;

//Aactor:
	const uintptr_t GameState = 0x1D0;
	const uintptr_t PlayerArray = 0x2C8;
	const uintptr_t SizePlayerArray = 0xC;
	const uintptr_t PawnPrivate = 0x328;
	//Root Componet:
	uintptr_t RootComponent = 0x1B0;
	uintptr_t RelativeLocation = 0x140;
//CameraManager:
	const uintptr_t PlayerCameraManager = 0x360;
	const uintptr_t CameraCachePrivate = 0x178;


//Mesh:
	const uintptr_t Mesh = 0x330;
	const uintptr_t CachedBoneSpaceTransforms = 0x5E8; //BoneArray
	const uintptr_t CachedComponentSpaceTransforms = 0x5F8; //BoneCache
	const uintptr_t ComponentToWorld = 0x1E0; //class alignas(0x10) USceneComponent : public UActorComponent ->



}
