# iceprog native Rasperry Pi SPI version

this iceprog version is meant for programming ice40 fpga flash via the native Raspberry Pi SPI Interface
It's core code comes from this repro: https://github.com/cliffordwolf/icestorm

## Warning

This is very alpha! I just tested it with an Icebreaker and an Raspberry 3B+ in flash mode and it works.
Use at your own risk. Other modes still need testing, happy to accept pull requests.

## Build

```
mkdir build
cd build
cmake ..
make
```

## Usage

```
./iceprog-rpicsi flash.bin
```

## Pin connections
![pinout](pinout.png)
