# Dependency installation

Install same dependencies as OpenFace https://github.com/TadasBaltrusaitis/OpenFace/wiki/Unix-Installation

## OpenCv
Same as in OpenFace.
```
wget https://github.com/opencv/opencv/archive/4.1.0.zip
sudo unzip 4.1.0.zip
cd opencv-4.1.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_TIFF=ON -D WITH_TBB=ON -D BUILD_SHARED_LIBS=OFF ..
came --build . -j 4
sudo make install
cd ..
```
## Dlib
Compared to Openface installation, here we use an additional flag when running cmake.
```
wget http://dlib.net/files/dlib-19.13.tar.bz2;
tar xf dlib-19.13.tar.bz2;
cd dlib-19.13;
mkdir build;
cd build;
cmake .. -DCMAKE_CXX_FLAGS="-fPIC"
cmake --build . --config Release -j 4
sudo make install
sudo ldconfig
cd ..
```
 
## OpenFace
Download Openface.
```
wget https://github.com/TadasBaltrusaitis/OpenFace/archive/OpenFace_2.2.0.zip
sudo unzip OpenFace_2.2.0.zip
```


## OpenFaceWrapper
Download and build OpenFaceWrapper to generate shared library .so.
```
git clone https://github.com/crisie/OpenFaceWrapper.git
cd OpenFaceWrapper/OpenFaceDLL
mkdir build 
cd build
cmake -D CMAKE_CXX_COMPILER=g++-8 -D CMAKE_C_COMPILER=gcc-8 -D CMAKE_BUILD_TYPE=RELEASE ..
cmake --build . -j 4
```

Copy all the open face models and AU_predictors to the folder in which .so is generated.
