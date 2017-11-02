require "rubygems"
require "benchmark/ips"

def windows?
  RbConfig::CONFIG['target_os'] =~ /mingw32|mswin/
end

def darwin?
  RbConfig::CONFIG['target_os'] =~ /darwin/
end

def nix?
  ! (darwin? || windows?)
end

if ARGV.pop == "--use-active-support-slice"
  class Hash
    def slice(*keys)
      keys.map! { |key| convert_key(key) } if respond_to?(:convert_key, true)
      keys.each_with_object(self.class.new) { |k, hash| hash[k] = self[k] if has_key?(k) }
    end
  end
else
  raise "Sorry, your platform is not supported" if windows?
  require_relative '../lib/fast_slice'
end

hash = Hash.new
("a".."z").each{|letter| hash[letter] = 1 }

Benchmark.ips do |b|
  b.time = 20
  b.report("FastSlice.slice") do
    FastSlice.slice(hash, "x".freeze, :g, :y, :h, :missing, :k)
  end
  b.hold!(".slice.bm")

  b.report("ActiveSupport's Hash#slice") do
    hash.slice("x".freeze, :g, :y, :h, :missing, :k)
  end
  b.compare!
end
