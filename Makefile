ROOT_TO_SOURCE_FILES := src/main.cpp
SOURCE_FILES := main.cpp

build: ${ROOT_TO_SOURCE_FILES}
	cd src && g++ ${SOURCE_FILES} 

run: src/a.out
	cd src && ./a.out

clean:
	rm src/a.out
