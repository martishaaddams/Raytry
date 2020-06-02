#include "box.h"
#include<limits>
void swap(float &a, float &b)//maybe it doesnt works
{
    float t = a;
    a = b;
    b = t;

}
box::box()
{
    for (int i = 0; i < 3; i++)
    {
        min_point[i] = 0;
        max_point[i] = 0;
    }
}
box::box(Vec3f& min, Vec3f &max, Vec3i &col)
{
    min_point = min;
    max_point = max;
    color = col;
}
//tmin = (t0x > t0y) ? t0x : t0y
/*bool box::Intersect(Ray& r)
{
    
    
    float tmin = (min_point[0] - r.dot[0]) / r.direction[0];
    float tmax = (max_point[0] - r.dot[0]) / r.direction[0];

    if (tmin > tmax) swap(tmin, tmax);

    float tymin = (min_point[1] - r.dot[1]) / r.direction[0];
    float tymax = (max_point[1] - r.dot[1]) / r.direction[0];

    if (tymin > tymax) swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
          return false;

    if (tymin > tmin)
          tmin = tymin;

    if (tymax < tmax)
          tmax = tymax;

    float tzmin = (min_point[2] - r.dot[2]) / r.direction[2];
    float tzmax = (max_point[2] - r.dot[2]) / r.direction[2];;

    if (tzmin > tzmax) swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
         tmin = tzmin;

     if (tzmax < tmax)
         tmax = tzmax;
     r.t = tmin;//Check if it is right
        return true;
    
}*/
bool box::ray_intersect(const Vec3f& orig, const Vec3f& dir, float* t0)
{
    float t_near = std::numeric_limits<float>::min();
    float t_far=std::numeric_limits<float>::max();
    float t1, t2;
    for (int i = 0; i < 3; i++)
    {
        if (abs(dir[i]) >= std::numeric_limits<float>::epsilon()) {
            t1 = (this->min_point[i] - orig[i]) / dir[i];
            t2 = (this->max_point[i] - orig[i]) / dir[i];
            if (t1 > t2)
                std::swap(t1, t2);
            if (t1 > t_near)
                t_near = t1;
            if (t2 < t_far)
                t_far = t2;
            if (t_near > t_far)
                return false;
            if (t_far < 0.0)
                return false;
        }
        else {
            if (orig[i] < this->min_point[i] || orig[i] > this->max_point[i])
                return false;
        }
    }
    if (t_near <= t_far && t_far >= 0) 
        *t0 = t_near;
    return (t_near <= t_far && t_far >= 0);

 }