#! /bin/bash

BENCHMARK_URL="https://github.com/google/benchmark.git"
BENCHMARK_DIR_NAME="benchmark"
CMAKE="cmake"

git clone --quiet --depth 1 $BENCHMARK_URL $BENCHMARK_DIR_NAME > /dev/null 2>&1
cd $BENCHMARK_DIR_NAME

if ! [ -x "$(command -v "$CMAKE")" ] ;then
    echo "$CMAKE is installing ..."
    sudo apt update && sudo apt install -y $CMAKE
    if test $? -ne 0;then
        echo "Installation failed!"
        exit 1
    fi
fi

"$CMAKE" -E make_directory "build"
"$CMAKE" -E chdir "build" "$CMAKE" -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../
"$CMAKE" --build "build" --config Release
