FROM ubuntu:20.04

RUN apt-get -qq update && \
    apt-get install -yq tzdata software-properties-common && \
    ln -fs /usr/share/zoneinfo/America/New_York /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

RUN apt-get install -y \
                    build-essential \
                    gdb \
                    gcc-multilib-x86-64-linux-gnux32 \
                    tmux \
                    qemu-system-x86 \
                    gawk \
                    expect

ADD . /ostep-projects
COPY ./xv6-public /ostep-projects/initial-xv6/src

WORKDIR /ostep-projects

ENV TOOLPREFIX=x86_64-linux-gnu-

CMD ["/bin/bash"]
