#!/usr/bin/ruby -w

this_file_name = File.basename( __FILE__ )
`ls`.each do |f|
    f.strip!
    next if f == this_file_name 
    next if f =~ /.*~$/

    puts "=== running #{f}"
    system( "ruby #{f}" )
    puts "=== done with #{f}\n"

end
