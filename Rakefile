require 'rake/testtask'
require 'rake/extensiontask'

spec = Gem::Specification.load('fast_slice.gemspec')
Rake::ExtensionTask.new('fast_slice', spec)

Rake::TestTask.new(test: [:clean, :clobber, :compile]) do |t|
  t.description = "Run unit tests"
  t.libs << "test"
  t.test_files = FileList['test/unit/*.rb']
  t.verbose = true
end

desc "Run benchmarks"
task benchmark: [:clean, :clobber, :compile] do
  File.delete(".slice.bm") if File.exist?(".slice.bm")
  system "$(which ruby) benchmark/bench.rb"
  system "$(which ruby) benchmark/bench.rb --use-active-support-slice"
end

task :default => ["test"]

