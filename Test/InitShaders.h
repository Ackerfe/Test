#pragma once
#include "SimpleShader.h"
#include <GL/glew.h>

namespace Ackerfe
{
	class InitShaders

	{
		GLint mBillboardProgramID = compileLinkSimpleShaders("Billboard.vert", "Billboard.frag");
		GLint mBillboardPerspectiveID;
		GLint mBillboardCameraMatrixID;
		GLint mBillboardModelMatrixID;
		GLint mBillboardScaleID;

		GLint mSkyboxProgramID = compileLinkSimpleShaders("Skybox.vert", "Skybox.frag");
		GLint mSkyboxPerspectiveID;
		GLint mSkyboxCameraMatrixID;
		GLint mSkyboxModelMatrixID;
		GLint mSkyboxLightPositionID;

		GLint mCloudProgramID = compileLinkSimpleShaders("Cloud.vert", "Cloud.frag");
		GLint mCloudPerspectiveID;
		GLint mCloudCameraMatrixID;
		GLint mCloudModelMatrixID;
		GLint mCloudModelCameraMatrixID;
		GLint mCloudTransparencyID;

		GLint mMeshProgramID = compileLinkSimpleShaders("Mesh.vert", "Mesh.frag");
		GLint mMeshPerspectiveID ;
		GLint mMeshCameraMatrixID;
		GLint mMeshModelMatrixID;
		GLint mMeshLightPositionID;
		GLint mMeshModelCameraMatrixID;
		GLint mMeshLightColourID;
		GLint mMeshLightIntensityID;
		GLint mMeshEyePositionID;
	public:
		InitShaders() {}
		~InitShaders() {}

		void init();
		
        GLint getMBillboardProgramID() const { return mBillboardProgramID; }

        GLint getMBillboardPerspectiveID() const { return mBillboardPerspectiveID; }

        GLint getMBillboardCameraMatrixID() const { return mBillboardCameraMatrixID; }

        GLint getMBillboardModelMatrixID() const { return mBillboardModelMatrixID; }

        GLint getMBillboardScaleID() const { return mBillboardScaleID; }

        GLint getMSkyboxProgramID() const { return mSkyboxProgramID; }

        GLint getMSkyboxPerspectiveID() const { return mSkyboxPerspectiveID; }

        GLint getMSkyboxCameraMatrixID() const { return mSkyboxCameraMatrixID; }

        GLint getMSkyboxModelMatrixID() const { return mSkyboxModelMatrixID; }

        GLint getMSkyboxLightPositionID() const { return mSkyboxLightPositionID; }

        GLint getMCloudProgramID() const { return mCloudProgramID; }

        GLint getMCloudPerspectiveID() const { return mCloudPerspectiveID; }

        GLint getMCloudCameraMatrixID() const { return mCloudCameraMatrixID; }

        GLint getMCloudModelMatrixID() const { return mCloudModelMatrixID; }

        GLint getMCloudModelCameraMatrixID() const { return mCloudModelCameraMatrixID; }

        GLint getMCloudTransparencyID() const { return mCloudTransparencyID; }

        GLint getMMeshProgramID() const { return mMeshProgramID; }

        GLint getMMeshPerspectiveID() const { return mMeshPerspectiveID; }

        GLint getMMeshCameraMatrixID() const { return mMeshCameraMatrixID; }

        GLint getMMeshModelMatrixID() const { return mMeshModelMatrixID; }

        GLint getMMeshLightPositionID() const { return mMeshLightPositionID; }

        GLint getMMeshModelCameraMatrixID() const { return mMeshModelCameraMatrixID; }

        GLint getMMeshLightColourID() const { return mMeshLightColourID; }

        GLint getMMeshLightIntensityID() const { return mMeshLightIntensityID; }

        GLint getMMeshEyePositionID() const { return mMeshEyePositionID; }

};
}

