apt-get install --yes build-essential xorg-dev libudev-dev libts-dev libgl1-mesa-dev libglu1-mesa-dev libasound2-dev libpulse-dev libopenal-dev libogg-dev libvorbis-dev libaudiofile-dev libpng12-dev libfreetype6-dev libusb-dev libdbus-1-dev zlib1g-dev libdirectfb-dev

mkdir SDL2
cd SDL2
wget http://www.libsdl.org/release/SDL2-2.0.4.tar.gz
tar -xvzf SDL2-2.0.4.tar.gz
cd SDL2-2.0.4
./configure
make
make install
cd ..

wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz
tar -xvzf SDL2_image-2.0.1.tar.gz
cd SDL2_image-2.0.1
./configure
make
make install
cd ..

wget https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.tar.gz
tar -xvzf SDL2_mixer-2.0.1.tar.gz
cd SDL2_mixer-2.0.1
./configure
make
make install
cd ..

# wget https://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz
# tar -xvzf SDL_ttf-2.0.11.tar.gz
# cd SDL_ttf-2.0.11
# ./configure
# make
# make install
# cd ..
# wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
# tar -xvzf SDL2_ttf-2.0.12.tar.gz
# cd SDL2_ttf-2.0.12
# ./configure
# make
# make install
