#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Array.hpp"
#include "rice/String.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
using namespace Rice;
typedef pair<double, double> pdd;

const char *location_templates[][2]= {
    {"gyms", "gyms-sg/coordinates.txt"},
    {"kindergardens", "kindergartens/coordinates.txt"},
    {"retail_pharmacies", "retail-pharmacy-locations/coordinates.txt"},
    {"water_projects", "abc-waters-projects/coordinates.txt"},
    {"hawker_centres", "hawker-centres/coordinates.txt"},
    {"libraries", "libraries/coordinates.txt"},
    {"parks", "parks-sg/coordinates.txt"},
    {"waste_treatment", "waste-treatment/coordinates.txt"},
    {"hotels", "hotels/coordinates.txt"},
    {"quit_centres", "quit-centres/coordinates.txt"},
    {"wifi_hotspots", "wireless-hotspots/coordinates.txt"}
};

const double PI = 3.141592653589079323846264338327950288419716939937510;

struct coor_t {
    double lat;
    double lon;

    bool operator <(const coor_t & p) const {
	return lon < p.lon || (lon == p.lon && lat < p.lat);
    }
};

double coor_d (coor_t p1, coor_t p2) {
    const double R = 6371000;
    double d1 = (p1.lat - p2.lat) * PI / 180;
    double d2 = (p1.lon - p2.lon) * PI / 180;
    double a = sin(d1 / 2) * sin(d1 / 2) +
        cos(p1.lat) * cos(p2.lat) *
        sin(d2) * sin(d2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return c * R;
}

struct location_t {
    std::string name;
    std::string filename;
    int boundary;
    std::vector<coor_t> coors;

    int count_near(coor_t needle) {
	int count = 0;

	for (int i = 0 ; i < coors.size() ; i++) {
            coor_t c = coors[i];
	    if (coor_d(c, needle) <= 2001) {
		count += 1;
	    }
	}

	return count;
    }

    void populate(std::string prefix) {
        std::ifstream fin((prefix + filename).c_str());

        double lat, lon, _;

        while (fin >> lon >> lat >> _) {
            coor_t c;
            c.lat = lat; c.lon = lon;
            coors.push_back(c);
        }

        fin.close();
    }
};

class MyNativeBrain {
private:
    vector<location_t> locations;
public:
    MyNativeBrain(Rice::String path) {
        const int N = sizeof(location_templates) / sizeof(location_templates[0]);
        for (int i = 0 ; i < N ; i++) {
            location_t loc;
            loc.name = location_templates[i][0];
            loc.filename = location_templates[i][1];
            locations.push_back(loc);
        }

        for (int i = 0 ;i < locations.size() ; i++) {
            locations[i].populate(from_ruby<std::string>(path));
        }
    }
    Array query(double lat, double lon) {
        coor_t needle;
        Array ret;

        needle.lat = lat;
        needle.lon = lon;

        for (int i = 0 ; i < locations.size() ; i++) {
            location_t & loc = locations[i];
            ret.push(to_ruby(loc.count_near(needle)));
        }

        return ret;
    }
    Array field_names() {
        Array ret;
        for (int i = 0 ; i < locations.size() ; i++) {
            ret.push(to_ruby(locations[i].name));
        }

        return ret;
    }
};

extern "C"
void Init_my_native_brain() {
    Class rb_c = define_class<MyNativeBrain>("MyNativeBrain")
	.define_constructor(Constructor<MyNativeBrain, Rice::String>())
	.define_method("query", &MyNativeBrain::query);
}

