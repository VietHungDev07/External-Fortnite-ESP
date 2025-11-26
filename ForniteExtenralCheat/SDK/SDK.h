#pragma once
#include <Windows.h>
#include <stdint.h>
#include <cstdint>
#include <d3d9types.h>
#include <cmath>
#define M_PI 3.14159265358979323846

struct FQuat
{
	double x;
	double y;
	double z;
	double w;
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

	bool operator==(const FVector& v) const
	{
		const double epsilon = 1e-6; 
		return (fabs(x - v.x) < epsilon) && (fabs(y - v.y) < epsilon) && (fabs(z - v.z) < epsilon);
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
struct FTransform
{
	FQuat rotation;
	FVector translation;
	uint8_t pad1c[0x8];
	FVector scale3d;
	uint8_t pad2c[0x8];

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m{};

		const FVector Scale
		(
			(scale3d.x == 0.0) ? 1.0 : scale3d.x,
			(scale3d.y == 0.0) ? 1.0 : scale3d.y,
			(scale3d.z == 0.0) ? 1.0 : scale3d.z
		);

		const double x2 = rotation.x + rotation.x;
		const double y2 = rotation.y + rotation.y;
		const double z2 = rotation.z + rotation.z;
		const double xx2 = rotation.x * x2;
		const double yy2 = rotation.y * y2;
		const double zz2 = rotation.z * z2;
		const double yz2 = rotation.y * z2;
		const double wx2 = rotation.w * x2;
		const double xy2 = rotation.x * y2;
		const double wz2 = rotation.w * z2;
		const double xz2 = rotation.x * z2;
		const double wy2 = rotation.w * y2;

		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;
		m._11 = (1.0f - (yy2 + zz2)) * Scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * Scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * Scale.z;
		m._32 = (yz2 - wx2) * Scale.z;
		m._23 = (yz2 + wx2) * Scale.y;
		m._21 = (xy2 - wz2) * Scale.y;
		m._12 = (xy2 + wz2) * Scale.x;
		m._31 = (xz2 + wy2) * Scale.z;
		m._13 = (xz2 - wy2) * Scale.x;
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