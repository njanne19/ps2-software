FROM ps2dev/ps2dev:latest

# Update and install bash
USER root
# install bash, make, cmake, plus the full build-base (incl. shared GMP/MPFR/MPC)
RUN apk update && apk add --no-cache \
      bash \
      make \
      cmake \
      git \
      build-base

# # Clone, build, install gsKit into $PS2DEV
# RUN cd $PS2DEV \
#     && git clone https://github.com/ps2dev/gsKit.git \
#     && mkdir -p gsKit/build \
#     && cd gsKit/build \
#     && cmake \
#       -DCMAKE_TOOLCHAIN_FILE=$PS2SDK/ps2dev.cmake \
#       -DCMAKE_INSTALL_PREFIX=$PS2DEV \
#       .. \
#     && cmake --build . --target install \
#     && rm -rf $PS2DEV/gsKit/build
      
# Use default user (root) unless you know a specific user exists
WORKDIR /workspace
