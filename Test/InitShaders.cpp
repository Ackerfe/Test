#include "InitShaders.h"

namespace Ackerfe
{
	void InitShaders::init()
	{
		 mMeshPerspectiveID = glGetUniformLocation(mMeshProgramID, "Perspective");
		 mMeshCameraMatrixID = glGetUniformLocation(mMeshProgramID, "CameraMatrix");
		 mMeshModelMatrixID = glGetUniformLocation(mMeshProgramID, "ModelMatrix");
		 mMeshLightPositionID = glGetUniformLocation(mMeshProgramID, "LightPosition");
		 mMeshModelCameraMatrixID = glGetUniformLocation(mMeshProgramID, "ModelCameraMatrix");
		 mMeshLightColourID = glGetUniformLocation(mMeshProgramID, "LightColour");
		 mMeshLightIntensityID = glGetUniformLocation(mMeshProgramID, "LightIntensity");
		 mMeshEyePositionID = glGetUniformLocation(mMeshProgramID, "eye_position");

		 mCloudPerspectiveID = glGetUniformLocation(mCloudProgramID, "Perspective");
		 mCloudCameraMatrixID = glGetUniformLocation(mCloudProgramID, "CameraMatrix");
		 mCloudModelMatrixID = glGetUniformLocation(mCloudProgramID, "ModelMatrix");
		 mCloudModelCameraMatrixID = glGetUniformLocation(mCloudProgramID, "ModelCameraMatrix");
		 mCloudTransparencyID = glGetUniformLocation(mCloudProgramID, "transparency");

		 mSkyboxPerspectiveID = glGetUniformLocation(mSkyboxProgramID, "Perspective");
		 mSkyboxCameraMatrixID = glGetUniformLocation(mSkyboxProgramID, "CameraMatrix");
		 mSkyboxModelMatrixID = glGetUniformLocation(mSkyboxProgramID, "ModelMatrix");
		 mSkyboxLightPositionID = glGetUniformLocation(mSkyboxProgramID, "LightPosition");

		 mBillboardPerspectiveID = glGetUniformLocation(mBillboardProgramID, "Perspective");
		 mBillboardCameraMatrixID = glGetUniformLocation(mBillboardProgramID, "CameraMatrix");
		 mBillboardModelMatrixID = glGetUniformLocation(mBillboardProgramID, "ModelMatrix");
		 mBillboardScaleID = glGetUniformLocation(mBillboardProgramID, "Scale");
	}
}