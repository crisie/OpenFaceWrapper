#pragma once
#include <iostream>
#include "Utils.cpp"

extern "C"
{
__declspec(dllexport) void testDLL(const int i);

__declspec(dllexport) void loadModel();

__declspec(dllexport) bool trackFace(const char* img, const double* camera_matrix, FACE_INFO* face_info);
//__declspec(dllexport) OpenFaceWrapper* CreateOpenFaceWrapper();
}