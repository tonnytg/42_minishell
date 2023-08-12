FROM arm64v8/ubuntu:latest
WORKDIR /app
COPY . .
RUN apt-get update  \
    && apt-get install -y \
    python3 python3-pip \
    valgrind gdb \
    libreadline-dev
RUN pip3 install norminette