BUILD_DIR=./build
CMAKE=cmake

.PHONY: all clean

all:
	@mkdir -p ${BUILD_DIR}
	${CMAKE} -S . -B ${BUILD_DIR} && ${CMAKE} --build ${BUILD_DIR} -j8 -- --no-print-directory

clean:
	rm -rf ${BUILD_DIR}
