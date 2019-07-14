#include "OpenFaceDLL.h"

#include "OpenFaceWrapper.h"

#include <iostream>
#include <memory>


static std::unique_ptr<OpenFaceWrapper> wrapper;

void testDLL(const int i) {
	std::cout << i << '\n';
}

void loadModel() {
	wrapper = std::make_unique<OpenFaceWrapper>();
}

bool trackFace(const char* img, const double* camera_matrix, FACE_INFO* face_info)
{
	std::cout << "Tracking image...." << '\n';

	if (wrapper == nullptr)
	{
		return false;
	}
	wrapper->TrackFace(img, camera_matrix, face_info);
	return true;
	
}