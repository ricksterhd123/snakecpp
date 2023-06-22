# snakecpp
## Classic Snake using SDL2 in C++

![v0.1.1 Screenshot](.docs/v0.1.1.png)

## Prerequisites:
- Linux x86 (e.g., I build this using WSL Ubuntu on windows)
- Python3 (for wasm only)
- [emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended) (for wasm only)
- SDL2 (via package manager)

## Setup
### Locally
- `make`
- `cd build`
- `./snake`

### WASM
- `make wasm`
- `cd build`
- `python3 -m http.server`
- Go to http://localhost:8000/snake.html
