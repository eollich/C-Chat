require 'socket'

s = TCPSocket.new 'localhost', 9898

s.write("test");


s.each_line do |line|
  puts line
end
s.close
