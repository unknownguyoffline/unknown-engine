#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Unk
{
	CameraProperty Camera::GetProperty() const
	{
		return mProperty;
	}

	void Camera::SetProperty(const CameraProperty& property)
	{
		mProperty = property;
	}

	void Camera::SetViewMatrix(const glm::mat4& view)
	{
		mViewMatrix = view;
	}

	void Camera::SetProjectionMatrix(const glm::mat4& projection)
	{
		mProjectionMatrix = projection;
	}

	void Camera::Calculate()
	{
		if (mProperty.type == FirstPerson)
			mViewMatrix = glm::lookAt(mProperty.position, mProperty.lookAt + mProperty.position, mProperty.up);
		else if (mProperty.type == Orbital)
			mViewMatrix = glm::lookAt(mProperty.position, mProperty.lookAt, mProperty.up);

		if (mProperty.projectionType == Perspective)
			mProjectionMatrix = glm::perspective(mProperty.fov, mProperty.size.x / mProperty.size.y, mProperty.nearPlane, mProperty.farPlane);
		else if (mProperty.projectionType == Orthographic)
		{
			float left = -(mProperty.size.x / mProperty.size.y);
			float right = mProperty.size.x / mProperty.size.y;
			mProjectionMatrix = glm::ortho(left, right, -1.f, 1.f, mProperty.nearPlane, mProperty.farPlane);
		}
	}

	CameraProperty& Camera::GetPropertyRef()
	{
		return mProperty;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return mViewMatrix;
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return mProjectionMatrix;
	}
}
