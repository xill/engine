#ifndef LOOK_AT
#define LOOK_AT

#include "camera/camera.hpp"
#include "camera/follow_point.hpp"
#include "math/mat4x4.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"

class LookAt : public Camera
{
private:
	// lookat point
	Vec3f m_lookat;

	// up vector
	Vec3f m_up;

	/*
	 * position of the camera 
	 * or relative position when follow point is set.
	 */
	Vec3f m_position;

	/*
	 * if set. This object will update 
	 * the look at point as the follow point moves. 
	 * It also makes the camera position relative.
	 */
	FollowPoint* m_followpoint;

	Mat4x4f m_modelViewMatrix;
	Mat4x4f m_modelViewMatrixInverse; // cached.

public:
	LookAt(const Vec3f &position, const Vec3f &lookat, const Vec3f &up);

	LookAt(FollowPoint* followpoint , const Vec3f &position, const Vec3f &up);

	void onCameraMotion(const Vec2f &motion);
	void onCameraZoom(float factor);
	void updateModelViewMatrix();

	void setupScene() const;

	const Mat4x4f &getProjectionMatrix() const;
	const Mat4x4f &getModelViewMatrix() const;
	const Mat4x4f &getModelViewMatrixInverse() const;

	void setLookAt(Vec3f);
	void setLookAt(FollowPoint*);

};

#endif // LOOK_AT
