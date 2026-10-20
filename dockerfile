# Reproducible Linux build + test environment for kalon.
#   docker build -t kalon .
#   docker run --rm kalon            # runs the test suite
FROM ubuntu:24.04

LABEL maintainer="Henry Hicks"

ENV DEBIAN_FRONTEND=noninteractive
ENV CC=clang
ENV CXX=clang++

# Toolchain + GoogleTest (Ubuntu 24.04's libgtest-dev ships prebuilt libs
# and a CMake package config, so no manual gtest build is needed).
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        cmake \
        ccache \
        libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Non-root user for builds
RUN useradd -ms /bin/bash kalon
USER kalon
WORKDIR /home/kalon/src

COPY --chown=kalon:kalon . .

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j"$(nproc)"

CMD ["ctest", "--test-dir", "build", "--output-on-failure"]
