# Set up ubuntu
FROM ubuntu:24.04

LABEL maintainer="Henry Hicks"

# Enviroment
ENV DEBIAN_FRONTEND=noninteractive
ENV CC=clang
ENV CXX=clang++

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    cmake \
    git \
    ccache \
    && rm -rf /var/lib/apt/lists/*

# gtest
RUN apt-get update && apt-get install -y libgtest-dev && \
    cd /usr/src/gtest && \
    cmake . && make && mv lib/*.a /usr/lib

# Create non-root user for builds
RUN useradd -ms /bin/bash kalon
USER kalon
WORKDIR /home/kalon

# Copy sources
COPY . /home/kalon

# Configure + build
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

# Default command (can be overridden)
CMD ["bash"]
# To run tests, use:
# CMD ["./build/tests/runTests"]