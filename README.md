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
git clone git@bitbucket.org:lingvixdev/php-hunspell.git
cd php-hunspell
make
sudo make install
```
