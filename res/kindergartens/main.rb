require "nokogiri"

xml = Nokogiri::XML(STDIN)

xml.css("Point coordinates").map(&:text).each do |txt|
    puts txt.strip.gsub(" ", "\t").gsub(",", " ")
end

