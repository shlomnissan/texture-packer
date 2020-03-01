# texture-packer [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.com/shlomnissan/texture-packer.svg?branch=master)](https://travis-ci.com/shlomnissan/texture-packer)

A simple command-line spritesheet generator written in C++17. The algorithm will do its best to pack the sprites using as little space possible, but ultimately, no bin packing algorithm is perfect. Feel free to modify it to suit your needs.

Open tasks: https://github.com/shlomnissan/texture-packer/projects/1

## Usage
```
texture_packer FILE_LIST [-i input text file] [-o output file]
```
### Examples
1. Without text file list:
```
texture_packer dave_0.png dave_1.png dave_2.png -o sprites
```
2. With text file list:
```
texture_packer sprites.txt -o sprites
```
The text file should be *plain text* containing the full path of each file you wish to pack delimited by a new line.

### Output

Both examples will generate a spritesheet called `sprites.png` and a json file called `sprites.json`

`sprites.png`

![sprites](https://user-images.githubusercontent.com/3165988/74093487-90e21f00-4a87-11ea-8066-d157b46edaa2.png)

`sprites.json`

```
{
    "sprites": [
        {
            "name": "assets/red-diamond.png",
            "x": 96,
            "y": 0,
            "width": 28,
            "height": 20
        },
        {
            "name": "assets/dave-head.png",
            "x": 96,
            "y": 20,
            "width": 28,
            "height": 24
        },
        {
        ...
    ]
}
```

## Dependencies
- FreeImage (http://freeimage.sourceforge.net)
- RapidJSON (https://rapidjson.org)
- gflags (https://github.com/gflags/gflags)

## Development 
This project is configured to run in VSCode from within a container using [Microsoft's Remote Containers plugin](https://code.visualstudio.com/docs/remote/containers). If this plugin is installed, opening this project in VSCode will automatically prompt you to install the development container and all the necessary dependencies. See `.devcontainer` folder for Docker's container configurations..

## MIT license:	

 ```	
Copyright (c) 2020 Shlomi Nissan	
 Permission is hereby granted, free of charge, to any person obtaining a copy	
of this software and associated documentation files (the "Software"), to deal	
in the Software without restriction, including without limitation the rights	
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	
copies of the Software, and to permit persons to whom the Software is	
furnished to do so, subject to the following conditions:	
 The above copyright notice and this permission notice shall be included in all	
copies or substantial portions of the Software.	
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	
SOFTWARE.	
```
