# Copyright 2008 Matthew Graham
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


require 'pathname'


class CppCompiler
    attr_reader :compiler

    def __initialize__( compiler )
        @compiler = compiler
    end

    def compile()
    end
end

def header_path( inc, inc_dirs )
    inc_dirs.each do |id|
        path = id +"/"+ inc
        if File.exists?( path )
            return path
        end
    end
    return nil
end

# This function should be modified to use yield
# somehow.  Haven't quite got yield figured out
# enough for that yet though.
def cpp_headers( cpp, inc_dirs )
    headers = []

    p = Pathname.new( cpp )
    path_prefix = p.dirname.to_s + "/"
    # print path_prefix, "\n"
    cpp_file = File.new( cpp, "r" )
    cpp_file.each do |line|
        # print line
        inc = line.match( /#include +"([\w]+\.h)"/ )
        if ( ! inc.nil? )
            # inc_path = path_prefix + inc[1]
            inc_path = header_path( inc[1], inc_dirs )
            if not inc_path.nil?
                # print inc_path, "\n"
                headers << inc_path
            end
        end
    end
    return headers
end

