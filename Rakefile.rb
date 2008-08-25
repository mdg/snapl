
task :clean => [] do
    sh "rm -f *.o"
end

directory "obj"

INC = FileList[ 'src/*.h' ]
SRC = FileList[ 'src/*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' ).sub( /^src\//, 'obj/' )
INC.freeze
SRC.freeze
OBJ.freeze
TEST_INC = FileList[ 'test/*.h' ]
TEST_SRC = FileList[ 'test/*.cpp' ]
TEST_OBJ = TEST_SRC.sub( /\.cpp$/, '.o' )
TEST_INC.freeze
TEST_SRC.freeze
TEST_OBJ.freeze


# rule '.o' => ['.cpp'] do |t|
rule '.o' => [
    proc { |tn| tn.sub(/\.o$/,'.cpp').sub(/^obj\//, 'src/') }
] do |t|
    sh %{g++ -c -g -Isrc -o #{t.name} #{t.source}}
end


file "shessiond" => [ :compile ] do |t|
    sh "g++ -o shessiond #{OBJ}"
end


file "test_shessiond" => [ :compile, :compile_test ] do |t|
    sh "gcc -o test_shessiond #{OBJ} #{TEST_OBJ}"
end



task :default => [ :compile ]


desc "Compile all source files into objects"
task :compile => [ "obj" ] + OBJ

desc "Compile all test files into objects"
task :compile_test => TEST_OBJ


desc "Build the main executable"
task :build => [ "shessiond" ]

desc "Build the test executable"
task :build_test => [ "test_shessiond" ]


desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./test_shession"
end

