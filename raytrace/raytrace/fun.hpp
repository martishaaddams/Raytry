 #pragma once
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
#include "box.h"
/*Vec3i trace (const Vec3f &orig, const Vec3f &dir, const std::vector<box*> &spheres,
            float& tNear, box** curr_sph, ScreenData scr_data){
    *curr_sph = nullptr;
    box* curr = nullptr;
//#pragma omp parallel for
    for (size_t k = 0; k < spheres.size(); ++k) {
        float tNear_k = scr_data.limit;
        if (spheres[k]->ray_intersect(orig, dir, tNear_k) && tNear_k < tNear) {
            *curr_sph = spheres[k];
            tNear = tNear_k;
            curr = spheres[k];
        }
    }
    if (*curr_sph != nullptr)
        return (curr->color);
    else return(scr_data.backgroundColor);//is_inside
}*/

Vec3i trace(const Vec3f& orig, const Vec3f& dir, const std::vector<box*>& boxes,
    float& tNear, box** curr_sph, ScreenData scr_data) {
    *curr_sph = nullptr;
    box* curr = nullptr;
    //#pragma omp parallel for
    for (size_t k = 0; k < boxes.size(); ++k) {
        float tNear_k = INFINITY;//scr_data.limit;
        if (boxes[k]->ray_intersect(orig, dir, &tNear_k) && tNear_k < tNear) {
            *curr_sph = boxes[k];
            tNear = tNear_k;
            curr = boxes[k];
        }
    }
    if (*curr_sph != nullptr)
        return (curr->color);
    else return(scr_data.backgroundColor);//is_inside
}

/*Vec3i colourise( const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere*> &spheres,const ScreenData &scr_data){
    Vec3i curr_colour = scr_data.backgroundColor;
    float tnear = scr_data.limit;
    Sphere* curr_sph = nullptr;
    if (trace(orig, dir, spheres, tnear, &curr_sph, scr_data)){
    	if (scr_data.num_sp == 1){
            curr_colour = Vec3i(64, 64, 64);
        }
        else{
            Vec3i T; T.x = (127/(scr_data.num_sp-1)); T.y = (127/(scr_data.num_sp-1)); T.z = (127/(scr_data.num_sp-1));
            curr_colour = Vec3i(64, 64, 64) + T*(curr_sph->index - 1);
        }
    }
    return curr_colour;
}*/

/*void render( const ScreenData &scr_data,const std::vector<Sphere*> &spheres){
    std::cout<<"--------------"<<std::endl;
    for (auto it = spheres.begin(); it != spheres.end(); ++it) {
        std::cout<<" ind: "<<(*it)->index<<" is a "<<(*it)->center<< "\n";
    }

    float scale = tan(scr_data.alpha*0.5 * M_PI / 180 )*scr_data.screen_dist;//Here is the main thing
    float imageAspectRatio = scr_data.width / (float)scr_data.height;//and here

    Vec3f orig; Vec3i tmp;
    int color[3];
    cimg_library::CImg<float> img(scr_data.width, scr_data.height, 1, 3);
//#pragma omp parallel for private(color,tmp)
    for (int j = 0; j < scr_data.height; ++j) {
        for (int i = 0; i < scr_data.width; ++i) {
            float x = (2 * (i + 0.5) / (float)scr_data.width - 1) * imageAspectRatio * scale;//and here
            float y = (1 - 2 * (j + 0.5) / (float)scr_data.height) * scale;//and here
            Vec3f dir = Vec3f(x, y, -1).normalize();
            dir.normalize();

            //tmp = colourise(orig, dir, spheres, scr_data);
           // color[0] = tmp[0];
			//color[1] = tmp[1];
			//color[2] = tmp[2];
            img.draw_point(i, j, color);
        }
    }
    img.save(scr_data.output_file.c_str());
}*/
void render(const ScreenData& scr_data, const std::vector<box*>& spheres){
    std::cout << "--------------" << std::endl;
    for (auto it = spheres.begin(); it != spheres.end(); ++it) {
        std::cout << " ind: " << (*it)->min_point << " is a " << (*it)->max_point << "\n";
    }

    //float scale = tan(scr_data.alpha * 0.5 * M_PI / 180) * scr_data.screen_dist;//Here is the main thing
    float scale = scr_data.realheight;
    float imageAspectRatio = scr_data.width / (float)scr_data.height;//and here
    box* curr_sph = nullptr;
    float tnear = scr_data.limit;
    Vec3f orig; //Vec3i tmp;
    Vec3i curr_color = scr_data.backgroundColor;
    int color[3];
    cimg_library::CImg<float> img(scr_data.width, scr_data.height, 1, 3);
    int k=0;
    #pragma omp parallel for
    for (int j = 0; j < scr_data.height; ++j) {
        for (int i = 0; i < scr_data.width; ++i) {
           //float x = (2 * (i  + 0.5 / (float)scr_data.width - 1) * imageAspectRatio * scale);//and here
            //float y = -(2 * (j + 0.5) / (float)scr_data.height-1) * scale;//and here
            float x = scale * (i-scr_data.width/2)/(float)scr_data.width * imageAspectRatio ;
            float y = -(scale * (j-scr_data.height/2)/ (float)scr_data.height);
            //Vec3f dir = Vec3f(x, y, -1).normalize();
            float tnear = scr_data.limit;
            Vec3f dir = scr_data.normal;
            Vec3f orig = Vec3f(x, y, 0);
            
            dir.normalize();
            curr_color= trace(orig, dir, spheres, tnear, &curr_sph, scr_data);
           /* if (curr_color[0] != scr_data.backgroundColor[0] && curr_color[1] != scr_data.backgroundColor[1] && curr_color[2] != scr_data.backgroundColor[2])
            {
                std::cout << k << std::endl;
                k++;
            }*/
                
            //tmp = colourise(orig, dir, spheres, scr_data);
            color[0] = curr_color[0];
            color[1] = curr_color[1];
            color[2] = curr_color[2];
            img.draw_point(i, j, color);
        }
    }
    img.save(scr_data.output_file.c_str());
}