#include "Scene3D/Scene3D.hpp"


Scene3D::Scene3D(SSD1306Driver *_display)
{
    display = _display;
    global_light_vector = Vector3fix(0, -1, 0);
    meshes.clear();
}

Scene3D::Scene3D(SSD1306Driver *_display, Vector3fix light)
{
    display = _display;
    global_light_vector = light;
    meshes.clear();
}

Scene3D::~Scene3D(void)
{
    meshes.clear();
}

Scene3D::addMesh(Mesh *mesh_to_add)
{
    meshes.push_back(mesh_to_add);
}

Scene3D::print_to_display_buffer(Vector3fix camera)
{

}