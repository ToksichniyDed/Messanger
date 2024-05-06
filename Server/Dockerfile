FROM ubuntu:latest

# Установка переменных окружения для предотвращения запроса конфигурации tzdata
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Установка компилятора и необходимых инструментов для сборки
RUN apt update -y && apt upgrade -y
RUN apt install -y gcc \
    git \
    g++ \
    make \
    wget \
    bison \
    python3 \
    vim  \
    pkg-config \
    libicu-dev \
    libreadline-dev \
    zlib1g-dev \
    flex \
    libpq-dev

#CMAke
RUN wget -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.29.1/cmake-3.29.1-linux-x86_64.sh \
 && chmod +x cmake-linux.sh \
 && ./cmake-linux.sh --skip-license --prefix=/usr/local \
 && rm cmake-linux.sh

#Boost
RUN git clone --recursive -j 8 https://github.com/boostorg/boost.git \
 && cd boost \
 && ./bootstrap.sh \
 && ./b2 headers \
 && ./b2 toolset=gcc -j 8 threading=multi link=static runtime-link=shared --prefix=/usr/local

WORKDIR /

#Boost::DI
RUN git clone https://github.com/boost-experimental/di.git \
 && cd di/include/boost \
 && cp -r * ../../../boost/boost

WORKDIR /

#postgresql
RUN git clone -j 8 https://git.postgresql.org/git/postgresql.git \
 && cd postgresql \
 && ./configure --prefix=/usr/local \
 && make -j 8 \
 && make install #\#
 #&& export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/postgresql/src/interfaces/libpq/

WORKDIR /

##libpqxx
RUN git clone -j 8 https://github.com/jtv/libpqxx.git \
 && cd libpqxx \
#####RUN export PKG_CONFIG_PATH=/postgresql/src/interfaces/libpq:$PKG_CONFIG_PATH \
 && ./configure --prefix=/usr/local \
 &&  make -j 8 \
 && make install

WORKDIR /

#openssl
RUN git clone -j 8 https://github.com/openssl/openssl.git \
 && cd openssl \
 && ./Configure --prefix=/usr/local \
 && make -j 8

WORKDIR /

WORKDIR /app
COPY . .

RUN mkdir build
WORKDIR /app/build
#
#Запускаем CMake
RUN cmake .. -DBoost_INCLUDE_DIR=../../boost
RUN make -j 8
##
##CMD ./Server
#
#
##psql -h host.docker.internal -U postgres -d Plotniy_Messanger -p 5432
