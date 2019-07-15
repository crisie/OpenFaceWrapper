import numpy as np
import os
import sys
from ctypes import *
import time
from numpy.ctypeslib import ndpointer
import cv2 as cv

landmarks_model_num = 68
landmarks2D_size = 2*landmarks_model_num
landmarks3D_size = 3*landmarks_model_num
pose_size = 3
aus_intensity_size = 17
aus_presence_size = 18

landmarks2D_array = c_double * landmarks2D_size
landmarks3D_array = c_double * landmarks3D_size
head_pose_array = c_double * pose_size
aus_intensity_array = c_double * aus_intensity_size
aus_presence_array = c_double * aus_presence_size

class FACE_INFO(Structure):
    _fields_ = [("certainty", c_float),
                ("detection_success", c_bool),
                ("landmarks2D", landmarks2D_array),
                ("landmarks3D", landmarks3D_array),
                ("head_rotation", head_pose_array),
                ("head_position", head_pose_array),
                ("aus_intensity", aus_intensity_array),
                ("aus_presence", aus_presence_array)]




class Info3DEstimation(object):
    def __init__(self):
        start = time.time()
        #os.environ['PATH'] = ';'.join([os.environ['PATH'], 'C://Users//Crisi//Documents//OpenFace//OpenFaceRoger//x64//Release'])
        self.info3D_model = cdll.LoadLibrary("/home/vcrom/Cris/OpenFaceWrapper/OpenFaceDLL/build/libOpenFaceWrapper.so")
        self.info3D_model.loadModel()
        current = time.time()
        self.counter = 0
        print("Time: ", current-start)
        start = current

    def get_3Dinformation(self, image, calib_matrix, certainty_threshold = 0.5):
        start = time.time()
        calib_matrix_np = np.array(calib_matrix).reshape((9, 1))
        self.info3D_model.trackFace.argtypes = [c_char_p, ndpointer(c_double, flags="C_CONTIGUOUS"), POINTER(FACE_INFO)]
        face_info = FACE_INFO(0.0, 0)
        success = self.info3D_model.trackFace(image.encode('utf-8'), calib_matrix_np, pointer(face_info))
        #print("Frame: ", self.counter)
        #self.counter +=1
        print("certainty: ", face_info.certainty)
        print("success: ", face_info.detection_success)
        if success:
            info3D = dict()

            # Landmark 2D
            info3D['landmarks2D'] = np.ndarray(buffer=landmarks2D_array.from_address(addressof(face_info.landmarks2D)),
                                     shape=(landmarks2D_size,)).reshape((2, landmarks_model_num)).transpose().copy()
            # print("Landmarks 2D", landmarks2D)

            # Landmarks 3D
            info3D['landmarks3D'] = np.ndarray(buffer=landmarks3D_array.from_address(addressof(face_info.landmarks3D)),
                                     shape=(landmarks3D_size,)).reshape((3, landmarks_model_num)).transpose().copy()
            #print("Landmarks 3D", info3D['landmarks3D'])

            # Head pose
            info3D['R'] = np.ndarray(buffer=head_pose_array.from_address(addressof(face_info.head_rotation)),
                           shape=(pose_size,)).copy()
            print("R", info3D['R'])

            # Head position
            info3D['T'] = np.ndarray(buffer=head_pose_array.from_address(addressof(face_info.head_position)),
                           shape=(pose_size,)).copy()
            print("T", info3D['T'])

            # AUS intensity
            info3D['AUSint'] = np.ndarray(buffer=aus_intensity_array.from_address(addressof(face_info.aus_intensity)),
                                shape=(aus_intensity_size,)).copy()
            # print(AUSint)

            # AUS presence
            info3D['AUSpres'] = np.ndarray(buffer=aus_presence_array.from_address(addressof(face_info.aus_presence)),
                                 shape=(aus_presence_size,)).copy()
            # print(AUSpres)

            print("Time: ", time.time() - start)
            return info3D

        print("ERROR from OpenFaceWrapper reading the input image or applying face model.")
        print("Please check image directory is correct.")
        return None


calib_matrix= [[1.2*720.0, 0.0, 360.0],
               [0.0, 1.2*720.0, 288.0],
               [0.0, 0.0, 1.0]]
meh = Info3DEstimation()
image = '/home/vcrom/Cris/OpenFaceWrapper/OpenFaceDLL/build/002950.bmp'
info = meh.get_3Dinformation(image, calib_matrix)
print(info['landmarks3D'])
print(info['R'])