FROM debian:buster
MAINTAINER temoslav

ENV TZ=Europe/Moscow

RUN apt-get update && apt-get -y install g++

RUN apt install -y build-essential cmake git pkg-config libgtk-3-dev
RUN apt install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev 
RUN apt install -y libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev
RUN apt install -y gfortran openexr libatlas-base-dev python3-dev python3-numpy
RUN apt install -y libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev  
RUN apt install -y libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

RUN mkdir ~/opencv_build && cd ~/opencv_build && \
git clone https://github.com/opencv/opencv.git && \
git clone https://github.com/opencv/opencv_contrib.git

RUN cd ~/opencv_build/opencv && mkdir -p build && cd build  

RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON .. && \
    make -j8 && \
    make install 
RUN mkdir /tmp/221_project
WORKDIR /tmp/221_project

COPY . /tmp/221_project
 

