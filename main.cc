#include "Common.h"

#include "Camera.h"
// Scene-specific objects
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"

int main() {
    // World
    HittableList world;

    auto matGround = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto matCenter = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto matLeft = make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto matRight = make_shared<Metal>(Color(0.8, 0.6, 0.2));

    world.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, matGround));
    world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, matCenter));
    world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, matLeft));
    world.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, matRight));

    // Camera
    Camera cam;
    cam.aspectRatio(16.0 / 9.0);
    cam.imageWidth(400);
    cam.samplesPerPixel(100);
    cam.maxDepth(50);

    // Render
    cam.Render(world);
}