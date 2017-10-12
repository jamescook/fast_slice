Gem::Specification.new do |s|
  s.name    = "fast_slice"
  s.version = "1.0.0"
  s.summary = "Hash#slice implemented in C"
  s.author  = "James Cook"

  s.files = Dir.glob("ext/**/*.{c,rb}") +
            Dir.glob("lib/**/*.rb")

  s.extensions << "ext/fast_slice/extconf.rb"

  s.add_development_dependency "rake-compiler"
  s.add_development_dependency "minitest"
  s.required_ruby_version = '>= 1.9'
end
