# OpenFaceWrapper

Wrapping [OpenFace](https://github.com/TadasBaltrusaitis/OpenFace) into a shared library :sparkles::sparkles:

Follow the instructions below to build the library for [Unix](#unix) or [Windows](#windows) environment.

# Unix

## Dependency installation 

Install same dependencies as OpenFace https://github.com/TadasBaltrusaitis/OpenFace/wiki/Unix-Installation

### OpenCv
Same as in OpenFace.
```bash
wget https://github.com/opencv/opencv/archive/4.1.0.zip
unzip 4.1.0.zip
cd opencv-4.1.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_TIFF=ON -D WITH_TBB=ON -D BUILD_SHARED_LIBS=OFF ..
came --build . -j 4
sudo make install
cd ..
```
### Dlib
Compared to Openface installation, here we use an additional flag when running cmake.
```bash
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
 
### OpenFace
Download Openface.
```bash
wget https://github.com/TadasBaltrusaitis/OpenFace/archive/OpenFace_2.2.0.zip
unzip OpenFace_2.2.0.zip
```


## Compile OpenFaceWrapper
Download and build OpenFaceWrapper to generate shared library .so.
```bash
git clone https://github.com/crisie/OpenFaceWrapper.git
cd OpenFaceWrapper
mkdir build 
cd build
cmake -D OPENFACE_DIR='your-openface-path' -D CMAKE_CXX_COMPILER=g++-8 -D CMAKE_C_COMPILER=gcc-8 -D CMAKE_BUILD_TYPE=RELEASE ..
cmake --build . --target OpenFaceWrapper -j 4
```

Copy all the OpenFace models and AU_predictors to the folder in which you run the app importing the shared lib.

# Windows

1. Install same dependencies as OpenFace https://github.com/TadasBaltrusaitis/OpenFace/wiki/Windows-Installation.

2. Open Visual Studio project and modify Include directories and Additional Library Directories items according to your paths definitions, so that they point to the 3rd party OpenFace libraries.

3. Build project. It will produce a DLL file in the Release folder.

4. Copy all the OpenFace models and AU_predictors to the folder in which you run the app importing the shared lib.

