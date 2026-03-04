# Binary Visualizer

Simple C program to visualize binary files as 2D images. Two pair of bytes are read from the file and adds to the brightness of the pixel with thoose coordinates. The resulting image is saved as a png. Can also read images using stb_image and then iterates over the uncompressed pixel data to visualize it.

Brightness is calculated as the logorithm of the number of times a pair of bytes occurs, normailized to the range of 0-255.

## Compilation

Written in C23, tested on Windows 11 with gcc.

```shell
gcc main.c ./lib/fcu_windows.c -std=c23 
```

## Usage

```shell
./a input_file
```

Result is saved to `result.png` in the same directory, if the file is an recognized image format, the result of the uncompressed pixel data is also saved to `raw image visualization.png`.

## Examples

### Text file

`main.c` visualized

![result for main.c](./assets/result%20main.c.png)

`lib/stb_image.h` visualized

![result for stb_image.h](./assets/result%20stb_image.png)

### Executable file

`a.exe` visualized

![result for a.exe](./assets/result%20a.png)

### x64 vs arm

The `openttd.exe` executable from the x64 version and arm64 version (Windows, OpenTTD version 15.2).

x64 version:

![result for openttd.exe x64](./assets/result%20openttd%2015.2%20win%20x64.png)

arm64 version:

![result for openttd.exe arm64](./assets/result%20openttd%2015.2%20win%20arm64.png)

### Photograph

Original image:

![original image](./assets/Rasmus%20äter%20soppa.png)

Binary visualization:

![result for Rasmus äter soppa.png](./assets/result%20Rasmus%20äter%20soppa.png)

Pixel data visualization:

![raw image visualization for Rasmus äter soppa.png](./assets/raw%20image%20visualization%20Rasmus%20äter%20soppa.png)

### Image

Original image:

![original image](./assets/Pathfinder%20Kingmaker%20Original%20Game%20Soundtrack.jpg)

Binary visualization:

![result for Pathfinder Kingmaker Original Game Soundtrack.jpg](./assets/result%20Pathfinder%20Kingmaker%20Original%20Game%20Soundtrack.png)

Pixel data visualization:

![raw image visualization for Pathfinder Kingmaker Original Game Soundtrack.jpg](./assets/raw%20image%20visualization%20Pathfinder%20Kingmaker%20Original%20Game%20Soundtrack.png)

### Avif vs Jpg

Image:

![original image](./assets/chris-greenhow-3FjIywswHSk-unsplash.avif)

Pixel data visualization:

![raw image visualization for chris-greenhow-3FjIywswHSk-unsplash.avif](./assets/raw%20image%20visualization%20chris%20greenhow.png)

Jpg binary visualization:

![result for chris-greenhow-3FjIywswHSk-unsplash.jpg](./assets/result%20chris%20greenhow%20jpg.png)

Avif binary visualization:

![result for chris-greenhow-3FjIywswHSk-unsplash.avif](./assets/result%20chris%20greenhow%20avif.png)
