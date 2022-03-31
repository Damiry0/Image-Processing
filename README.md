# Image Processing

Small C script to manipulate pgm/ppm photos with various effectts:

## Usage
Run in terminal:
```
make
./myapp -i <filename> [-k -n -d -o <filename>]
```
Where:
```
-k => contouring
-n => negative
-d => display in ImageMagick
-o <filename> => save to path
-p <value> => thresholding
-pc <value> => thresholding to zero
-pb <value> => thresholding to zero inverted
```
## Example:
```
./myapp -i kubus.pgm -n -o kubus_output.pgm
```

Before             |  After
:-------------------------:|:-------------------------:
![](https://i.imgur.com/7Vxa3qN.jpg)  |  ![](https://i.imgur.com/P6MMq26.jpg)

```
./myapp -i Lena.ppm -n -d
```

Before             |  After
:-------------------------:|:-------------------------:
![](https://i.imgur.com/T639lwL.jpg)  |  ![](https://i.imgur.com/hceGwcJ.jpg)
