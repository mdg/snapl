
require 'pathname'


class CppCompiler
    attr_reader :compiler

    def __initialize__( compiler )
        @compiler = compiler
    end

    def compile()
    end
end

def cpp_headers( cpp )
    headers = []

    p = Pathname.new( cpp )
    path_prefix = p.dirname.to_s + "/"
    # print path_prefix, "\n"
    cpp_file = File.new( cpp, "r" )
    cpp_file.each do |line|
        # print line
        inc = line.match( /#include +"([\w]+\.h)"/ )
        if ( ! inc.nil? )
            inc_path = path_prefix + inc[1]
            # print inc_path, "\n"
            headers << inc_path
        end
    end
    return headers
end

