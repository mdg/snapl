
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

inc = FileList[ 'src/*.h' ]
src = FileList[ 'src/*.cpp' ]
obj = src.sub( /\.cpp$/, '.o' )

rule '.o' => ['.cpp'] do |t|
    sh %{gcc -c -o #{t.name} #{t.source}}
end

desc "Compile all source files into objects"
task :compile => [ obj.to_a.join( " " ) ] do |t|
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

