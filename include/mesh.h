#ifndef MESH_H
#define MESH_H

typedef struct face_s
{
    int v_a;
    int v_b;
    int v_c;
} Face;

typedef struct vertex_s
{
    float x;
    float y;
    float z;
} Vertex;

typedef struct mesh_s
{
    Vertex *vertices;
    Face *faces;

    int nb_vertices;
    int nb_faces;
} Maillage;

void mesh_create(Maillage **mesh);
void mesh_destroy(Maillage **mesh);

Maillage *create_mesh_from_obj_file(char const *file);

static const int NB_ELEMENT_OBJ_LINE = 4;

#endif