#include <iostream>
#include <cstring>
#include <cmath>

// Function to calculate Julian Date correctly
double julianDate(int year, int month, int day) {
    if (month <= 2) {
        year -= 1;
        month += 12;
    }
    int A = year / 100;
    int B = 2 - A + (A / 4);
    double jd = int(365.25 * (year + 4716)) + int(30.6001 * (month + 1)) + day + B - 1524.5;
    return jd;
}

// Function to calculate heliocentric coordinates
void heliocentricCoordinates(double jd, const char* planet, double& lat, double& lon, double& dist) {
    const double NeptuneLat = -0.963;
    const double NeptuneLon = 259.522;
    const double NeptuneDist = 30.068;
    const double PlutoLat = -5.434;
    const double PlutoLon = 218.164;
    const double PlutoDist = 39.482;

    if (strcmp(planet, "Neptune") == 0) {
        lat = NeptuneLat - 0.058 * (jd - 2447754.5) / 365.25;  // Adjust latitude
        lon = NeptuneLon + 0.033 * (jd - 2447754.5) / 365.25;  // Adjust longitude
        dist = NeptuneDist + 0.001 * sin((jd - 2447754.5) / 365.25);  // Adjust distance
    } else if (strcmp(planet, "Pluto") == 0) {
        lat = PlutoLat - 0.012 * (jd - 2447754.5) / 365.25;  // Adjust latitude
        lon = PlutoLon + 0.023 * (jd - 2447754.5) / 365.25;  // Adjust longitude
        dist = PlutoDist + 0.002 * sin((jd - 2447754.5) / 365.25);  // Adjust distance
    }
}

int main() {
    // Input dates: {Year, Month, Day}
    int dates[][3] = {{1989, 9, 5}, {2015, 7, 14}, {2023, 10, 1}};
    const char* planets[] = {"Neptune", "Pluto"};

    // Loop through each date
    for (int i = 0; i < 3; i++) {
        // Calculate Julian Date for the given year, month, and day
        double jd = julianDate(dates[i][0], dates[i][1], dates[i][2]);

        // Loop through each planet
        for (int j = 0; j < 2; j++) {
            double lat, lon, dist;

            // Calculate heliocentric coordinates for each planet
            heliocentricCoordinates(jd, planets[j], lat, lon, dist);

            // Output results
            std::cout << "Date: " << dates[i][0] << "-" << dates[i][1] << "-" << dates[i][2];
            std::cout << ", Planet: " << planets[j] << std::endl;
            std::cout << "Heliocentric ecliptic latitude: " << lat << "°" << std::endl;
            std::cout << "Heliocentric ecliptic longitude: " << lon << "°" << std::endl;
            std::cout << "Distance (AU): " << dist << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}
