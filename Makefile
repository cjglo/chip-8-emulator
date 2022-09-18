ROOT_TO_SOURCE_FILES := src/main.cpp src/commands.cpp src/display/drawing.cpp
SOURCE_FILES := main.cpp commands.cpp display/drawing.cpp
LIBRARIES := -lraylib -lglfw3 -lGL -lopenal -lm -ldl -pthreads

build: ${ROOT_TO_SOURCE_FILES}
	cd src && g++ ${SOURCE_FILES} ${LIBRARIES}

run: src/a.out
	cd src && ./a.out

clean:
	rm src/a.out
