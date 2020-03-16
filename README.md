# Reddit Holmes
## Description
_Quick side-project, you give it the reddit user, it gives you the information. Quite easy!_

## Installation
### Requirement
#### ArchLinux
`$ pacman -S curl cmake gcc`
#### Debian
`$ apt install curl cmake gcc`

### Compile
If you don't have curl installed add -DBUILD_CURL=On
```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/bin -DCMAKE_BUILD_TYPE=Release ..
make
```
### Installing
```bash
sudo make install
```

## Usage
```
rholmes [user]
```
Example:
```
rholmes GrbavaCigla
```
Output:
```
Serbia 100.00%
```
## Credits
Made by [Aleksa Ognjanovic](https://github.com/GrbavaCigla/)

