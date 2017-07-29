FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y build-essential gdb valgrind

RUN mkdir /var/projects
WORKDIR /var/projects
