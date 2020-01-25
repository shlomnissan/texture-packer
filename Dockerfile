FROM ubuntu:18.04

# Install dependencies
RUN apt-get update \
    && apt-get install -y \
    xz-utils \
    build-essential \
    curl \
    vim \
    libfreeimage3 \
    libfreeimage-dev \
    openssh-server \
    cmake \
    rsync \
    gdb \
    sed \
    && rm -rf /var/lib/apt/lists/*

# Install LLVM 9/Clang
RUN curl -SL http://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz | tar -xJC . \
    && mv clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04 clang_9.0.0 \
    && echo 'export PATH=/clang_9.0.0/bin:$PATH' >> ~/.bashrc \
    && echo 'export LD_LIBRARY_PATH=/clang_9.0.0/lib:$LD_LIBRARY_PATH' >> ~/.bashrc

# Configure SSH
RUN mkdir /var/run/sshd && \
    echo "PermitRootLogin yes" >> /etc/ssh/sshd_config && \
    echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]