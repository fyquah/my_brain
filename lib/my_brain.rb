require_relative "./my_native_brain"

class MyBrain
  def path_to_resources
    File.join(File.dirname(File.expand_path(__FILE__)), 'res/')
  end

  def initialize
    @my_test = MyNativeBrain.new path_to_resources
  end

  def query lat, lon
    @my_test.query lat, lon
  end
end

