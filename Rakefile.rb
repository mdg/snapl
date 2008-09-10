
task :clean => [] do
    sh "rm -f *.o"
    sh "rm -rf obj"
    sh "rm -f test/*.o"
end

directory "obj"
directory "test_obj"

INC = FileList[ 'src/*.h' ]
SRC = FileList[ 'src/*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/' )
INC.freeze
SRC.freeze
OBJ.freeze
TEST_INC = FileList[ 'test/*.h' ]
TEST_SRC = FileList[ 'test/*.cpp' ]
TEST_SRC.exclude( 'testpp_test.cpp' )
TEST_OBJ = TEST_SRC.sub( /\.cpp$/, '.o' ).sub( /^test\//, 'test_obj/' )
TEST_INC.freeze
TEST_SRC.freeze
TEST_OBJ.freeze


# rule '.o' => ['.cpp'] do |t|
    # sh %{g++ -c -g -Isrc -o #{t.name} #{t.source}}
# end

def obj_dep( o )
    deps = []
    cpp = o.sub(/\.o$/,'.cpp').sub(/^obj\//, 'src/') \
        .sub(/^test_obj\//, 'test/')
    deps << cpp
    deps << cpp.sub( /\.cpp$/,'.h')
    return deps
end

rule '.o' => [
    proc { |o| obj_dep( o ) }
] do |t|
    sh %{g++ -c -g -Isrc -o #{t.name} #{t.source}}
end


file "shessiond" => [ :compile ] do |t|
    sh "g++ -o shessiond #{OBJ}"
end


file "test_shessiond" => [ :compile, :compile_test ] do |t|
    no_main_obj = OBJ.clone
    no_main_obj.exclude( 'main.o' )
    sh "g++ -o test_shessiond #{no_main_obj} #{TEST_OBJ}"
end


file "load_shessiond" => [ :compile, "load/load.cpp" ] do |t|
    no_main_obj = OBJ.clone
    no_main_obj.exclude( 'main.o' )
    sh "g++ -Isrc -o load_shessiond #{no_main_obj} load/load.cpp"
end



task :default => [ :compile ]


desc "Compile all source files into objects"
task :compile => [ "obj" ] + OBJ

desc "Compile all test files into objects"
task :compile_test => [ "test_obj" ] + TEST_OBJ


desc "Build the main executable"
task :build => [ "shessiond" ]

desc "Build the test executable"
task :build_test => [ "test_shessiond" ]

desc "Build the test executable"
task :build_load => [ "load_shessiond" ]


desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./test_shession"
end

