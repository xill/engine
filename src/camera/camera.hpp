#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math/mat4x4.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "camera/follow_point.hpp"

class Camera
{
public:
	virtual void onCameraMotion(const Vec2f &motion) = 0;
	virtual void onCameraZoom(float factor) = 0;
	virtual void updateModelViewMatrix() = 0;

	virtual void setupScene() const = 0;

	virtual const Mat4x4f &getProjectionMatrix() const = 0;
	virtual const Mat4x4f &getModelViewMatrix() const = 0;
	virtual const Mat4x4f &getModelViewMatrixInverse() const = 0;

	virtual void setLookAt(Vec3f) = 0;
	virtual void setLookAt(FollowPoint*) = 0;

	/**
	 * Converts 2d screen space point to 3d ray starting from the
	 * camera position.
	 *
	 * @param  point on screen
	 * @param  z The window point for the z value.
	 *           between 0 and 1.
	 *           0 meaning the near clipping plane and 1 for the far.
	 *
	 * @return ray
	 */
	Vec3f screenSpacePointTo3DRay(const Vec2i &screen_point, float z) const;

	Vec3f rotatePointAroundAxis(
		const Vec3f &point, const Vec3f &axis, float theta);
};

#endif // CAMERA_HPP
