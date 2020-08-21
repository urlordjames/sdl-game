FROM debian:10

WORKDIR /root
RUN apt-get update && apt-get install build-essential cmake libsdl2-* -y
COPY CMakeLists.txt .
COPY src src
