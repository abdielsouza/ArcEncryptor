# Arc Encryptor Project

![arc](./images/arc.png)

## What is Arc Encryptor?

The "Arc" is a new cryptography standard created by myself that can be used to
encrypt files and raw text contents. The algorithm is based on the concept of an
arc mathematical expression where the limits go from -3.14 to 3.14. The Arc Encryptor
uses trigonometric expressions to encode data and a symmetric key to decode it back.

## Tech Stack
- Pure C++
- STL
- CMake

## Some notes about this project
- **this library was not projected to be used on real projects for production (YET!)**
- **this algorithm is still very weak**, so don't expect so much from it.

## How to install
- Clone this git repo
- Go to the root directory
- Run the commands (adapted for linux):

```
mkdir build && cd build
sudo cmake ..
sudo make install
```