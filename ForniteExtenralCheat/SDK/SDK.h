#pragma once
#include <Windows.h>
#include <stdint.h>
#include <cstdint>
#include <d3d9types.h>
#include <cmath>
#define M_PI 3.14159265358979323846

struct alignas(0x10) FQuat final
{
public:
	float                                         X;                                             
	float                                         Y;                                             
	float                                         Z;                                             
	float                                         W;                                             
};
class FVector2D
{
public:
	FVector2D() : x(0.f), y(0.f)
	{

	}

	FVector2D(double _x, double _y) : x(_x), y(_y)
	{

	}
	~FVector2D()
	{

	}

	FVector2D operator-(FVector2D v)
	{
		return FVector2D(x - v.x, y - v.y);
	}

	double x;
	double y;
};

class FVector
{
public:
	FVector() : x(0.f), y(0.f), z(0.f)
	{

	}

	FVector(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{

	}
	~FVector()
	{

	}

	double x;
	double y;
	double z;

	inline double Dot(FVector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline double Distance(FVector v)
	{
		return double(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline double Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	FVector operator+(FVector v)
	{
		return FVector(x + v.x, y + v.y, z + v.z);
	}

	FVector operator-(FVector v)
	{
		return FVector(x - v.x, y - v.y, z - v.z);
	}

	FVector operator/(double flNum)
	{
		return FVector(x / flNum, y / flNum, z / flNum);
	}

	FVector operator*(double flNum) { return FVector(x * flNum, y * flNum, z * flNum); }
};
struct FRotator
{
	float Pitch;
	float Yaw;
	float Roll;
};
struct _MATRIX
{
	union
	{
		struct
		{
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
};
struct FTransform final
{
public:
	struct FQuat                                  Rotation;
	struct FVector                                Translation;
	struct FVector                                Scale3D;

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = Translation.x;
		m._42 = Translation.y;
		m._43 = Translation.z;

		float x2 = Rotation.X + Rotation.X;
		float y2 = Rotation.Y + Rotation.Y;
		float z2 = Rotation.Z + Rotation.Z;

		float xx2 = Rotation.X * x2;
		float yy2 = Rotation.Y * y2;
		float zz2 = Rotation.Z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * Scale3D.x;
		m._22 = (1.0f - (xx2 + zz2)) * Scale3D.y;
		m._33 = (1.0f - (xx2 + yy2)) * Scale3D.z;

		float yz2 = Rotation.Y * z2;
		float wx2 = Rotation.W * x2;
		m._32 = (yz2 - wx2) * Scale3D.z;
		m._23 = (yz2 + wx2) * Scale3D.y;

		float xy2 = Rotation.X * y2;
		float wz2 = Rotation.W * z2;
		m._21 = (xy2 - wz2) * Scale3D.y;
		m._12 = (xy2 + wz2) * Scale3D.x;

		float xz2 = Rotation.X * z2;
		float wy2 = Rotation.W * y2;
		m._31 = (xz2 + wy2) * Scale3D.z;
		m._13 = (xz2 - wy2) * Scale3D.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}

};
struct FMinimalViewInfo final
{
public:
	struct FVector                                Location;                                     
	struct FRotator                               Rotation;                                     
	float                                         FOV;                                          
};

namespace DATA
{
	//World:
	extern uintptr_t Uworld;


	//LocalPlayer
	extern uintptr_t OwningGameInstance;
	extern uintptr_t LocalPlayers;
	extern uintptr_t PlayerController;
	extern uintptr_t AcknowledgedPawn;

	//Aactor:
	extern uintptr_t GameState;
	extern uintptr_t PlayerArray;
	extern uintptr_t PawnPrivate;

	//Camera;
	extern uintptr_t PlayerCameraManager;
	extern FMinimalViewInfo CameraCachePrivate;

}
extern int ScreenHeight;
extern int ScreenWidth;
extern int ScreenLeft;
extern int ScreenRight;
extern int ScreenTop;
extern int ScreenBottom;

namespace World
{
	uintptr_t GetWorld();
}
namespace UPlayer
{
	uintptr_t GetInstanceGame();
	uintptr_t GetAPlayerController();
	uintptr_t GetLocalPlayer();

}
namespace Aactor
{
	uintptr_t GetGameState();
	uintptr_t GetPlayerArray();
	int GetPlayerArraySize();
	uintptr_t GetActorAddress(int index);
	FVector GetActorLocation(uintptr_t actor);

}
struct SCamera
{
	FVector Location;
	FVector Rotation;
	float FieldOfView;
};
struct FNRot
{
	double a;
	double b;
	double c;
};

namespace Camera
{

	 SCamera GetCamera();
	 FVector2D ProjectWorldToScreen(FVector WorldLocation);
}
namespace Bone
{
	uintptr_t GetMesh(uintptr_t AactorAddress);
	FTransform GetBoneIndex(uintptr_t AactorAddress, int index);
	FVector GetBoneWithRotation(uintptr_t AactorAddress, int id);
}