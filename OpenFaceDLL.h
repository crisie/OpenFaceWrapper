#pragma once
#ifndef OPEN_FACE_SHARED_LIB_H_
#define OPEN_FACE_SHARED_LIB_H_

#ifdef _WIN32
//# ifdef WIN_EXPORT
#   define EXPORTED  __declspec( dllexport )
//# else
//#   define EXPORTED  __declspec( dllimport )
//# endif
#else
# define EXPORTED
#endif

extern "C"
{
typedef struct _FACE_INFO
{
	float certainty;
	bool detection_success;
	double landmarks2D[136] = { 0.0 };
	double landmarks3D[204] = { 0.0 };
	double head_rotation[3] = { 0.0 };
	double head_position[3] = { 0.0 };
	double aus_intensity[17] = { 0.0 };
	double aus_presence[18] = { 0.0 };
} FACE_INFO;

EXPORTED void testDLL(const int i);

EXPORTED void loadModel();

EXPORTED bool trackFace(const char* img, const double* camera_matrix, FACE_INFO* face_info);
}
#endif  // OPEN_FACE_SHARED_LIB_H_