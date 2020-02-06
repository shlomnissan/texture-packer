# texture-packer [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.com/shlomnissan/texture-packer.svg?branch=master)](https://travis-ci.com/shlomnissan/texture-packer)

A simple command-line spritesheet generator written in C++17.

Open tasks: https://github.com/shlomnissan/texture-packer/projects/1

## Usage
```
texture_packer FILE_LIST [-o output file]
```
Example:
```
texture_packer dave_0.png dave_1.png dave_2.png -o sprites
```
This will generate a spritesheet called `sprites.png` and a json sprite map `sprites.json`

## Dependencies
- FreeImage (http://freeimage.sourceforge.net/)
- RapidJSON (https://rapidjson.org/)

## Set up a development environment using Docker

#### Build the image
```
docker build -t texture-packer-dev .
```

#### Run the container
```
docker run -d -P --name texture-packer texture-packer-dev
```

#### Run bash to set up a password for root
```
docker exec -it texture-packer /bin/bash
$ passwd root
$ exit
```

#### Log in using SSH
```
ssh root@localhost -p {$PORT}
```
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
