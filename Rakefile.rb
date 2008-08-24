
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
OBJ = SRC.sub( /\.cpp$/, '.o' )
INC.freeze
SRC.freeze
OBJ.freeze

rule '.o' => ['.cpp'] do |t|
    sh %{gcc -c -o #{t.name} #{t.source}}
end

desc "Compile all source files into objects"
task :compile => OBJ do |t|
    # sh "cc -o #{t.name} #{t.prequisites.join( ' ' )}"
end

desc "Build the main executable"
task :build => [ :compile ] do |t|
    # sh "cc -o #{t.name} #{t.prequisites.join( ' ' )}"
end

desc "Build the test executable"
task :build_test => [ :compile ] do |t|
end

desc "Make and run tests"
task :test => [ :build_test ] do |t|
    sh "./test_shession"
end

task :default => [ :compile ]

