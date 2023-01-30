base_dir=$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")

function build(){
    local build_dir="$base_dir/build/"
    echo "Creating build directory: $build_dir ";

    rm -rf $build_dir
    mkdir -p $build_dir
    cd $build_dir > /dev/null

    echo "Configuring CMake..."
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
    echo "Building...";
    make -j
    cd - > /dev/null
}

function run(){
    local build_dir="$base_dir/build/"
    echo "Running supertyper...";

    cd $build_dir > /dev/null
    ./supertyper    
    cd - > /dev/null
}
