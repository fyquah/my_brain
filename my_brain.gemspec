Gem::Specification.new do |s|
  s.name        = 'my_brain'
  s.version     = "0.0.0"
  s.authors     = ["FY Q"]
  s.files = Dir.glob("ext/**/*.{cpp,rb}") +
        Dir.glob("lib/*.rb")
  s.extensions << "ext/my_native_brain/extconf.rb"
  s.homepage    = 'https://github.com/fyquah95/my_brain'

  s.add_dependency "rice"
  s.add_development_dependency "rake-compiler"
end
