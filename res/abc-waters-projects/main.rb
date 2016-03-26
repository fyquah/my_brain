require "nokogiri"

xml = Nokogiri::XML(STDIN)

xml.css("coordinates").map(&:text).each do |txt|
    puts "#{txt.strip.gsub(" ", "\t").gsub(",", " ")} 0"
end

