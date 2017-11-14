#pragma once
#include "Struct.h"
#include <math.h>

Vector OldAimPunch;

#define 	M_PI   3.14159265358979323846f

#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )
#define M_RADPI 57.295779513082f

namespace Maths {

	void GetNormalAngles(Vector &angle)
	{
		while (angle.x > 89.0f) {
			angle.x -= 180.f;
		}
		while (angle.x < -89.0f) {
			angle.x += 180.f;
		}
		while (angle.y > 180.f) {
			angle.y -= 360.f;
		}
		while (angle.y < -180.f) {
			angle.y += 360.f;
		}
	}

	void MakeVector(float *pfIn, float *pfOut)
	{
		float pitch;
		float yaw;
		float tmp;

		pitch = (float)(pfIn[0] * M_PI / 180);
		yaw = (float)(pfIn[1] * M_PI / 180);
		tmp = (float)cos(pitch);

		pfOut[0] = (float)(-tmp * -cos(yaw));
		pfOut[1] = (float)(sin(yaw)*tmp);
		pfOut[2] = (float)-sin(pitch);
	}
	void CalcAngle2(float *src, float *dst, float *angles)
	{
		double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

		angles[0] = (float)(atan(delta[2] / hyp) * M_RADPI);
		angles[1] = (float)(atan(delta[1] / delta[0]) * M_RADPI);
		angles[2] = 0.0f;

		if (delta[0] >= 0.0) { angles[1] += 180.0f; }
	}

	float GetFOV(float *angle, float *src, float *dst)
	{
		float ang[3], aim[3];
		float fov;

		CalcAngle2(src, dst, ang);
		MakeVector(angle, aim);
		MakeVector(ang, ang);

		float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
		float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));

		float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

		fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);

		return fov;
	}

	void ClampAngles(Vector &angles)
	{
		if (angles.y > 180.0f)
			angles.y = 180.0f;
		else if (angles.y < -180.0f)
			angles.y = -180.0f;

		if (angles.x > 89.0f)
			angles.x = 89.0f;
		else if (angles.x < -89.0f)
			angles.x = -89.0f;

		angles.z = 0;
	}

	static bool Clamp(Vector &angles)
	{
		Vector a = angles;
		GetNormalAngles(a);
		ClampAngles(a);

		if (isnan(a.x) || isinf(a.x) ||
			isnan(a.y) || isinf(a.y) ||
			isnan(a.z) || isinf(a.z)) {
			return false;
		}
		else {
			angles = a;
			return true;
		}
	}

	void AngleVectors(const Vector &angles, Vector *forward)
	{
		float    sp, sy, cp, cy;


		//SinCos(DEG2RAD(angles[1]), &sy, &cy);
		sy = sin(angles.y * 4.0 * atan(1.0) / 180.0);
		cy = cos(angles.y * 4.0 * atan(1.0) / 180.0);
		//SinCos(DEG2RAD(angles[0]), &sp, &cp);
		sp = sin(angles.x * 4.0 * atan(1.0) / 180.0);
		cp = cos(angles.x * 4.0 * atan(1.0) / 180.0);


		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	void CalcAngle(Vector src, Vector dst, Vector &angles)
	{
		double delta[3] = { (src.x - dst.x), (src.y - dst.y), (src.z - dst.z) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		angles.x = (float)(atan2(delta[2], hyp) * 57.295779513082f);
		angles.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
		angles.z = 0.0f;
		if (delta[0] >= 0.0) { angles.y += 180.0f; }
	}


	float GetFov(const Vector& viewAngle, const Vector& aimAngle)
	{
		Vector ang, aim;

		AngleVectors(viewAngle, &aim);
		AngleVectors(aimAngle, &ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}
}