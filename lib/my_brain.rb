require_relative "./my_native_brain"
require "rest-client"

class MyBrain
  def path_to_resources
    File.join(File.dirname(File.expand_path(__FILE__)), 'res/')
  end

  def initialize
    @my_test = MyNativeBrain.new path_to_resources
  end

  def query lat, lon
    feature_vector = @my_test.query lat, lon

    obj = {
      "Inputs": {
        "input1": {
          "ColumnNames": [
            "gyms",
            "kindergardens",
            "retail_pharmacies",
            "water_projects",
            "hawker_centres",
            "libraries",
            "parks",
            "waste_treatment",
            "hotels",
            "quit_centres",
            "wifi_hotspots"
          ],
          "Values": [
              feature_vector
          ]
        }
      },
      "GlobalParameters": {}
    }
    url = "https://ussouthcentral.services.azureml.net/workspaces/78206f728a8e478cb9e3c06f96a217d4/services/07b5c26b721449e3a625534482c24e56/execute?api-version=2.0&details=true"
    headers = {
        "Authorization": "Bearer #{ENV["AZURE_SG_DENGUE_API_KEY"]}",
        "Content-Type": "application/json",
        "Accept": "application/json"
    }
    res = JSON.parse(RestClient.post(url, obj.to_json, headers))
    res["Results"]["output1"]["value"]["Values"][0][1].to_f
  end
end

