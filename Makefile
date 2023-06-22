all:
	mkdir -p build
	cmake -B./build/ -S.
	cd build && cmake --build .

wasm:
	mkdir -p build
	cd src/ && emcc -sUSE_SDL=2 -sSINGLE_FILE snake.cpp -o ../build/snake.html
