#include "Common.h"

#include "Camera.h"
// Scene-specific objects
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

int main() {
    // World
    HittableList world;
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;
    cam.aspectRatio(16.0 / 9.0);
    cam.imageWidth(400);
    cam.samplesPerPixel(100);

    // Render
    cam.Render(world);
}