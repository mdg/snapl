
# rule '.cpp' => ['.o'] do |t|
#     sh "gcc", t.source, "-o", t.name
# end

# task :test do
#     ruby "test_all.rb"
# end

# src = 'src/main.cpp'
# target = build(

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

desc "Compile all source files into objects"
task :compile => OBJ do |t|
    # sh "cc -o #{t.name} #{t.prequisites.join( ' ' )}"
end

desc "Build the main executable"
task :build => [ :compile ] do |t|
    # t.invoke_prerequisites
    print "\n"
    print t.class
    print "\n"
    print t.prerequisites.class
    print "\n"
    print t.prerequisites.join( ' ' )
    print "\n\n"
    sh "g++ -o shessiond #{OBJ}"
end

desc "Compile all source files into objects"
task :compile_test => TEST_OBJ do |t|
    # sh "cc -o #{t.name} #{t.prequisites.join( ' ' )}"
end

desc "Build the test executable"
task :build_test => [ :compile, :compile_test ] do |t|
    sh "gcc -o test_shessiond #{t.prerequisites.join( ' ' )}"
end

desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./test_shession"
end

task :default => [ :compile ]

