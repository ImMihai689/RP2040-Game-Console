#ifndef SCENE_3D_FIXED
#define SCENE_3D_FIXED

#ifndef FIXED_POINT_ARITHMETIC
    #include "FixedPoint/FixedPoint.hpp"
#endif

#ifndef SSD1306_DRIVER
    #include "SSD1306Driver/SSD1306Driver.hpp"
#endif

#ifndef _STL_VECTOR_H
    #include <vector>
#endif

#ifndef _PICO_MALLOC_H
    #include <cstdlib>
    #include "pico/malloc.h"
#endif

struct Mesh {
    public:
        Mesh(const Vector3fix *_points, const unsigned int *triangles, unsigned int _number_of_points, unsigned int _number_of_triangles)
        {
            points = _points;
            triangles = triangles;
            number_of_points = _number_of_points;
            number_of_triangles = _number_of_triangles;
            normals = (Vector3fix *)malloc(number_of_triangles * sizeof(Vector3fix));
        }

        Mesh(const Vector3fix *_points, const unsigned int *triangles, unsigned int _number_of_points, unsigned int _number_of_triangles, const Vector3fix &_position)
        {
            position = _position;
            points = _points;
            triangles = triangles;
            number_of_points = _number_of_points;
            number_of_triangles = _number_of_triangles;
            normals = (Vector3fix *)malloc(number_of_triangles * sizeof(Vector3fix));
        }

        
        Mesh(const Vector3fix *_points, const unsigned int *triangles, unsigned int _number_of_points, unsigned int _number_of_triangles, const Vector3fix &_position, const Vector3fix &_rotation)
        {
            position = _position;
            rotation = _rotation;
            points = _points;
            triangles = triangles;
            number_of_points = _number_of_points;
            number_of_triangles = _number_of_triangles;
            normals = (Vector3fix *)malloc(number_of_triangles * sizeof(Vector3fix));
        }

        ~Mesh()
        {
            points = NULL;
            triangles = NULL;
            free(normals);
            normals = NULL;
        }

        void generate_normals()
        {
            for(int i = 0; i < number_of_triangles; i++)
            {
                Vector3fix side1 = Vector3fix(points[triangles[i * 3 + 0]]) - Vector3fix(points[triangles[i * 3 + 1]]);
                Vector3fix side2 = Vector3fix(points[triangles[i * 3 + 2]]) - Vector3fix(points[triangles[i * 3 + 1]]);
                normals[i] = (side1.cross(side2)).normalized();
            }
        }


        /// @brief Do not edit manually
        const Vector3fix *points; // Equal to number_of_points
        /// @brief Do not edit manually
        unsigned int *triangles; // Equal to number_of_triangles * 3
        /// @brief Do not edit manually
        Vector3fix *normals; // Equal to number_of_triangles
        /// @brief Do not edit manually
        unsigned int number_of_points;
        /// @brief Do not edit manually
        unsigned int number_of_triangles;
        Vector3fix position;
        /// @brief The rotation of the body, defined in radians, applied as euler angles.
        /// The numbers x, y, z apply, in order, rotation in the global axis: Y, X, Z.
        Vector3fix rotation;
};


class Scene3D
{
    public:
        Scene3D(SSD1306Driver *_display);
        Scene3D(SSD1306Driver *_display, Vector3fix light);

        ~Scene3D(void);

        void addMesh(Mesh *mesh_to_add);
        void print_to_display_buffer(Vector3fix camera);

    private:
        std::vector<Mesh *> meshes;
        SSD1306Driver *display;
        Vector3fix global_light_vector;
};

#endif