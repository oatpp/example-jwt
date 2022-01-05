FROM alpine:latest

RUN apk update && apk upgrade

RUN apk add g++

RUN apk add git
RUN apk add make
RUN apk add cmake
RUN apk add postgresql-dev
RUN apk add openssl-dev

WORKDIR /deps

RUN git clone -b v0.5.1 https://github.com/Thalhammer/jwt-cpp.git

WORKDIR /deps/jwt-cpp/build

RUN cmake ..
RUN make install

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh Release

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000 8000

ENTRYPOINT ["./example-jwt-exe"]
