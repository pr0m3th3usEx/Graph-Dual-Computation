#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    printf("Hello world !\n");

    Maillage *mesh = create_mesh_from_obj_file("tests/obj_files/mesh_1.obj");

    if (!mesh) {
        printf("Could not create mesh\n");
        return 1;
    }

    printf("Faces :\n");
    for (int i = 0; i < mesh->nb_faces; i++) {
        printf("%d, %d, %d\n", mesh->faces[i].v_a, mesh->faces[i].v_b, mesh->faces[i].v_c);
    }
    printf("Vertices :\n");
    for (int i = 0; i < mesh->nb_vertices; i++) {
        printf("%f, %f, %f\n", mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z);
    }



    free(mesh->faces);
    free(mesh->vertices);
    mesh_destroy(&mesh);

    return 0;
}
