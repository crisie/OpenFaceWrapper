#include "OpenFaceDLL.h"

#include <stdio.h>

#include "OpenFaceWrapper.h"

static std::unique_ptr<OpenFaceWrapper> wrapper;

void testDLL(const int i) {
	printf("%d\n", i);
}

void loadModel() {
	wrapper = std::make_unique<OpenFaceWrapper>();
}

bool trackFace(const char* img, const double* camera_matrix, FACE_INFO* face_info)
{
	printf("Tracking image....");

	if (wrapper == NULL)
	{
		return false;
	}
	wrapper->TrackFace(img, camera_matrix, face_info);
	return true;
	
}

//OpenFaceWrapper* CreateOpenFaceWrapper()
//{
//	static OpenFaceWrapper wrapper;
//	return &wrapper;
//}