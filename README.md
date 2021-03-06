# php-hunspell

## Building from source

### Install gcc 4.8 for C++11 support

Add to /etc/apt/sources.list:
```
# new gcc
deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu precise main # apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA9EF27F
```

Run as root:

```
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA9EF27F
apt-get update
apt-get install gcc-4.8 g++-4.8
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 20
update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 20
```

### Install required packages

```
apt-get install php5-dev libhunspell-1.3-0 libhunspell-dev
```

### Build and install php-cpp

```
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
sudo make install
```

### Build and install php-hunspell

```
git clone git@github.com:kbaryshnikov/php-hunspell.git
cd php-hunspell
make
sudo make install
```

### Building with hunspell experimental features

Install libhunspell and libhunspell packages from http://symbi.org/files/hunspell/

```
sudo dpkg -i libhunspell-dev_1.3.3-1_amd64.deb
sudo dpkg -i libhunspell-1.3-0_1.3.3-1_amd64.deb
```

When building the extension, run ```FLAGS='-DHUNSPELL_EXPERIMENTAL' make -e``` instead of ```make```.
