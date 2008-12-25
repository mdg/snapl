
require "../rakepp.rb"

task :clean => [] do
    sh "rm -rf obj"
end

directory "obj/src"
directory "obj/test"

LINKS = "-lpthread"

INC = FileList[ 'src/*.h' ]
SRC = FileList[ 'src/*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/src/' )
INC.freeze
SRC.freeze
OBJ.freeze
SRC_DIR = 'src'
SAMPLE_INC = FileList[ 'server/*.h', 'client/*.h' ]
SAMPLE_SRC = FileList[ 'server/*.cpp', 'client/*.cpp' ]
SAMPLE_OBJ = SAMPLE_SRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/src/' )


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
    sh %{g++ -c -g -Isrc -Itestpp/include -o #{t.name} #{t.source}}
end


file "sample" => [ :compile ] do |t|
    sh "g++ -o sample #{OBJ} #{SAMPLE_OBJ} #{LINKS}"
end


file "load_shessiond" => [ :compile, "load/load.cpp" ] do |t|
    no_main_obj = OBJ.clone
    no_main_obj.exclude( 'main.o' )
    sh "g++ -Isrc -o load_shessiond #{no_main_obj} load/load.cpp"
end



task :default => [ :build ]


desc "Compile all source files into objects"
task :compile => [ "obj/src" ] + OBJ


desc "Build the main executable"
task :build => [ "sample" ]

desc "Build the test executable"
task :build_load => [ "load_shessiond" ]


desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./test_shession"
end

