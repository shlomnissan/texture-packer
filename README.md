# texture-packer 

A simple command-line spritesheet generator written in C++17. It has similar features to the TexturePacker app (texturepacker.com).

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
