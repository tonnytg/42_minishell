# 42_minishell

[![Minishell Core Test](https://github.com/tonnytg/42_minishell/actions/workflows/core-test.yml/badge.svg)](https://github.com/tonnytg/42_minishell/actions/workflows/core-test.yml)

This project aims to build a shell prompt with shell commands.

Github Actions:
    - Test make
    - Test norminette

## Docker Setup

To use the Docker image for the development environment, you must first build the Docker image. You can do this with the following command:

```BASH
docker build -t 42_minishell .
```

This command will build the Docker image according to the instructions in the Dockerfile and will name it '42_minishell'.

After building the image, you can start a container using the following command line:

```BASH
docker run -it 42_minishell
```

* Inside the container, you can use gdb, valgrind, norminette, and git among others.

### Troubleshooting

If you encounter any error while building the Docker image, make sure your Dockerfile is set up correctly.

If the error persists, you may try to clean all Docker containers, images, and volumes on your machine and try again. But be careful, as this will erase all your Docker data:

```BASH
docker system prune -a --volumes
```
After that, you can try to build the image again.