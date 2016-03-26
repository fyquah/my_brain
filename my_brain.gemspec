Gem::Specification.new do |s|
  s.name        = 'my_brain'
  s.files = Dir.glob("ext/**/*.{cpp,rb}") +
        Dir.glob("lib/*.rb")
  s.extensions << "ext/my_native_brain/extconf.rb"

  s.add_dependency "rice"
  s.add_development_dependency "rake-compiler"
end
