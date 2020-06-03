#define M_PI 3.14159265358979323846
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <memory>

#include <utility>
#include <string>
#include <vector>
#include <map>

#include <chrono>
#include "omp.h"
#include "CImg.h"
#include "geometry.hpp"
#include "data_processing.hpp"
#include "fun.hpp"

void autotest() { 
    ScreenData scr_data = scan_data("screen_data.txt", "test.bmp");
    std::vector<box*> spheres = scan_box("box_data.txt", scr_data);
    if (spheres.size() == 0) {
        return;
    }
    render(scr_data, spheres);

    for (size_t i = 0; i < spheres.size(); i++) {
        delete spheres[i];
    }

    std::cout << "test: OK " << std::endl;
}

   
