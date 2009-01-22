
require "rakepp.rb"

task :clean => [] do
    sh "rm -rf obj"
end

directory "obj/src"
directory "obj/test"

LINKS = "-lpthread -ltestpp"

INC_OPTS = '-Iinclude -Itestpp'
INC = FileList[ 'include/snapl/*.h', 'src/*.h' ]
SRC = FileList[ 'src/*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/src/' )
INC.freeze
SRC.freeze
OBJ.freeze
SRC_DIR = 'src'
TEST_DIR = 'test'
TEST_INC = FileList[ 'test/*.h' ]
TEST_SRC = FileList[ 'test/*.cpp' ]
TEST_SRC.exclude( 'testpp_test.cpp' )
TEST_OBJ = TEST_SRC.sub( /\.cpp$/, '.o' ).sub( /^test\//, 'obj/test/' )
TEST_INC.freeze
TEST_SRC.freeze
TEST_OBJ.freeze
TESTPP_OBJ = FileList[ 'testpp/*.o' ]


# Return dependencies for an object file.
def obj_dep( o )
    deps = []
    inc_dirs = [ SRC_DIR, TEST_DIR ]
    cpp = o.sub(/\.o$/,'.cpp') \
        .sub(/^obj\/src\//, 'src/') \
        .sub(/^obj\/test\//, 'test/')
    # print cpp, "\n"
    headers = cpp_headers( cpp, inc_dirs )
    # print headers.join(" "), "\n"
    deps << cpp
    deps << headers
    # deps << cpp.sub( /\.cpp$/, '.h' )
    return deps
end


rule '.o' => [ proc { |o| obj_dep( o ) } ] do |t|
    sh %{g++ -c -g -Isrc #{INC_OPTS} -o #{t.name} #{t.source}}
end


file "libsnapl.a" => [ :compile ] do |t|
    sh "ar r libsnapl.a obj/src/*.o"
end


file "run_snapl_tests" => [ :compile, :compile_test ] do |t|
    no_main_obj = FileList.new()
    no_main_obj.import( OBJ )
    no_main_obj.exclude( 'main.o' )
    sh "g++ -o run_snapl_tests #{no_main_obj} #{TEST_OBJ} #{TESTPP_OBJ} \
            #{LINKS}"
end


file "load_snapl" => [ :compile, "load/load.cpp" ] do |t|
    no_main_obj = OBJ.clone
    no_main_obj.exclude( 'main.o' )
    sh "g++ -Isrc -o load_snapl #{no_main_obj} load/load.cpp"
end



task :default => [ :build ]


desc "Compile all source files into objects"
task :compile => [ "obj/src" ] + OBJ

desc "Compile all test files into objects"
task :compile_test => [ "obj/test" ] + TEST_OBJ


desc "Build the main executable"
task :build => [ "libsnapl.a" ]

desc "Build the test executable"
task :build_test => [ "run_snapl_tests" ]

desc "Build the test executable"
task :build_load => [ "load_snapl" ]


desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./run_snapl_tests"
end

