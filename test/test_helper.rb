require 'minitest/autorun'

def windows?
  RbConfig::CONFIG['target_os'] =~ /mingw32|mswin/
end

def darwin?
  RbConfig::CONFIG['target_os'] =~ /darwin/
end

def nix?
  ! (darwin? || windows?)
end

if darwin?
  require_relative '../lib/fast_slice.bundle'
elsif nix?
  require_relative '../lib/fast_slice.so'
else
  raise "Sorry, that platform isn't supported"
end
