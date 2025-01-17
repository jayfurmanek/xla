# XLA developer guide

This guide shows you how to get started developing the XLA project.

Before you begin, complete the following prerequisites:

1.  Go to [CONTRIBUTING.md](../CONTRIBUTING.md) and review the contribution
    process.
2.  If you haven't already done so, sign the
    [Contributor License Agreement](https://cla.developers.google.com/about).
3.  Install or configure the following dependencies:
    -   A [GitHub](https://github.com/) account
    -   [Docker](https://www.docker.com/)

Then follow the steps below to get the source code, set up an environment, build
the repository, and create a pull request.

## Get the code

1.  Create a fork of the [XLA repository](https://github.com/openxla/xla).
2.  Clone your fork of the repo, replacing `<USER>` with your GitHub username:
    ```sh
    git clone https://github.com/<USER>/xla.git
    ```
3.  Change into the `xla` directory: `cd xla`
4.  Configure the remote upstream repo:
    ```sh
    git remote add upstream https://github.com/openxla/xla.git
    ```

## Set up an environment

1.  Install [Bazel](https://bazel.build/install).

    To build XLA, you must have Bazel installed. The recommended way to install
    Bazel is using [Bazelisk](https://github.com/bazelbuild/bazelisk#readme),
    which automatically downloads the correct Bazel version for XLA. If Bazelisk
    is unavailable, you can [install Bazel](https://bazel.build/install)
    manually.

2.  Create and run a
    [TensorFlow Docker container](https://www.tensorflow.org/install/docker).

    To get the TensorFlow Docker image for CPU, run the following command:

    ```sh
    docker run --name xla -w /xla -it -d --rm -v $PWD:/xla tensorflow/build:latest-python3.9 bash
    ```

    Alternatively, to get the TensorFlow Docker image for GPU, run the following
    command:

    ```sh
    docker run --name xla_gpu -w /xla -it -d --rm -v $PWD:/xla tensorflow/tensorflow:devel-gpu bash
    ```

## Build

Build for CPU:

```sh
docker exec xla ./configure
docker exec xla bazel build --test_output=all --spawn_strategy=sandboxed --nocheck_visibility //xla/...
```

Build for GPU:

```sh
docker exec -e TF_NEED_CUDA=1 xla_gpu ./configure
docker exec xla_gpu bazel build --test_output=all --spawn_strategy=sandboxed --nocheck_visibility //xla/...
```

Your first build will take quite a while because it has to build the entire
stack, including XLA, MLIR, and StableHLO.

To learn more about building XLA, see [Build from source](build_from_source.md).

## Create a pull request

When you're ready to send changes for review, create a
[pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

To learn about the XLA code review philosophy, see
[Code reviews](code_reviews.md).
