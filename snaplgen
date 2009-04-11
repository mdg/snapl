#! /usr/bin/ruby

require "rubygems"
require "yaml"
require "tenjin"
require "liquid"


x = <<eos
this is
a multiline
string.
eos


LIQUID_COMMAND_TEMPLATE = <<eos
#ifndef {{include_guard}}
#define {{include_guard}}

{% for cmd in commands %}

class {{ cmd.keys }}_command_c
: public snapl::command_c
{
public:
	{{ cmd.keys }}_command_c();
};
{% endfor %}

#endif
eos

p = YAML::load_file( "test/protocol.yaml" )
p["include_guard"] = "CORE_SNAPL_COMMANDS_H"

# print p.methods.join ' '
print p.inspect, "\n"

engine = Tenjin::Engine.new()
tenjin_output = engine.render( 'template/commands.rbcpp', p )

liquid_template = Liquid::Template.parse( LIQUID_COMMAND_TEMPLATE )
liquid_output = liquid_template.render( p )


# print "tenjin = \n", tenjin_output
print "liquid = \n", liquid_output

# print "'", x, "'\n"

