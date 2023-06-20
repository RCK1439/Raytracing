# Raytracing

This project is an implementation and follow through of the Ray Tracing in a Weekend series (specifically the first book). I did add some of my own personal touches to the project.

Things like:
 - Multi-threading with OpenMP.
 - Timing and performance metrics.
 - Input arguments.

## Build

To build the project:
 1. Clone the project to the directory of choice
 2. Create a bin folder in the root directory.
 3. Run the following command: ```bash make```

## Run

To run the program:
 1. ```bash ./Raytracing``` or if you're in the root directory ```bash ./bin/Raytracing``` (easy, huh?)

### Some input arguments

 - ```bash -s``` or ```bash -S```: This specifies the resolution of the image to output. (e.g. ```bash -s 1280 720```)
 - ```bash -a``` or ```bash -A```: This specifies the anti-aliasing number of samples. (e.g. ```bash -a 32```)
 - ```bash -d``` or ```bash -D```: This specifies the amounts of bounces a ray can have. (e.g. ```bash -d 8```)
 - ```bash -help```: Shows a little help menu in the terminal that describes the valid input arguments. (e.g. ```bash -help```)

My personal favourite configuration: ```bash ./Raytracing -s 1280 720 -a 128 -d 50```