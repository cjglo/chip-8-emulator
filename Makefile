ROOT_TO_SOURCE_FILES := src/main.cpp src/commands.cpp src/display/drawing.cpp src/instruction_loop/fetch.cpp src/instruction_loop/decode.cpp  
SOURCE_FILES := main.cpp commands.cpp display/drawing.cpp instruction_loop/fetch.cpp instruction_loop/decode.cpp
LIBRARIES := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build: ${ROOT_TO_SOURCE_FILES}
	cd src && g++ ${SOURCE_FILES} ${LIBRARIES}

run: src/a.out
	cd src && ./a.out

clean:
	rm src/a.out
