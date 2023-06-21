# Raytracing

This project is an implementation and follow through of the [Ray Tracing in a Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) series (specifically the first book). This is my first finished graphics-related project with more coming soon hopefully.

I added some things as a personal touch:
 - Multi-threading with OpenMP.
 - Timing and performance metrics.
 - Input arguments.

## Platforms

Currently this project only supports Linux. I've been working on this project on Ubuntu.
But I do have plans to add support for Windows.

## Build

To build the project:
 1. Clone the project to the directory of choice
 2. Create a bin folder in the root directory.
 3. Run the following command: ```make```

## Run

To run the program:
 1. ```./rtk``` or if you're in the root directory ```./bin/rtk``` (easy, huh?)

### Some input arguments

 - ```-s``` or ```-S```: This specifies the resolution of the image to output. (e.g. ```-s 1280 720```)
 - ```-a``` or ```-A```: This specifies the anti-aliasing number of samples. (e.g. ```-a 32```)
 - ```-d``` or ```-D```: This specifies the amounts of bounces a ray can have. (e.g. ```-d 8```)
 - ```-o```: This specifies the output directory to save the rendered image to. (e.g. ```-o path/to/dir/name.png```)
 - ```-help```: Shows a little help menu in the terminal that describes the valid input arguments. (e.g. ```-help```)

My personal favourite configuration: ```./rtk -s 1280 720 -a 128 -d 50```
