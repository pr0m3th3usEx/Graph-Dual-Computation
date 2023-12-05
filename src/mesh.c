#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mesh.h"
#include "utils.h"

/***
 * Static functions
*/
static int is_obj_line_valid(char const *line, int *_nb_vertices, int *_nb_faces)
{
    char **line_split = split_c(line, ' ');
    int array_length = 0;

    if (!line_split) return 0;
    for (array_length = 0; line_split[array_length] != NULL; array_length++);

    // 4 infos seperated by space
    if (array_length != 0 && array_length != 4) {
        printf("Bad format\n");
        destroy_split_array(line_split);
        return 0;
    }

    // 1st element - v or f
    if (strcmp(line_split[0], "f") == 0) {
        *_nb_faces += 1;
    } else if (strcmp(line_split[0], "v") == 0) {
        *_nb_vertices += 1;
    } else {
        printf("Bad line information\n");
        destroy_split_array(line_split);
        return 0;
    }

    // 3 others element are decimal values
    for (int i = 1; i < NB_ELEMENT_OBJ_LINE; i++) {
        if (!is_int(line_split[i]) && is_float(line_split[i])) {
            printf("%s: not a number\n", line_split[i]);
            destroy_split_array(line_split);
            return 0;
        }
    }

    destroy_split_array(line_split);
    return 1;
}

static int is_obj_file_format_valid(FILE *file, int *_nb_vertices, int *_nb_faces)
{
    char *line = NULL;
    int line_length = 0;
    size_t linecap = 0;
   
    // Validate format
    while ((line_length = getline(&line, &linecap, file)) >= 0) {
        // Remove newline delimiter 
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        } 
        // Analyze line structure
        if (!is_obj_line_valid(line, _nb_vertices, _nb_faces)) {
            return 0;
        }
        // Free space
        free(line);
        line = NULL;
    }

    return 1;
}

static void extract_line_information(char const *line, Vertex *vertex, Face *face, int *indexV, int *indexF)
{
    char **line_split = split_c(line, ' ');
    float v_a = 0;
    float v_b = 0;
    float v_c = 0;

    if (!line_split) return;

    // Extract numbers
    v_a = strtof(line_split[1], NULL);
    v_b = strtof(line_split[2], NULL);
    v_c = strtof(line_split[3], NULL);
    
    printf("Line value: %f, %f, %f\n", v_a, v_b, v_c);


    // 1st element - v or f
    if (strcmp(line_split[0], "f") == 0) {
        face->v_a = (int) v_a - 1;
        face->v_b = (int) v_b - 1;
        face->v_c = (int) v_c - 1;
        *indexF += 1;
    }
    
    if (strcmp(line_split[0], "v") == 0) {
        vertex->x = v_a;
        vertex->y = v_b;
        vertex->z = v_c;
        *indexV += 1;
    }

    destroy_split_array(line_split);
}

static void aggregates_mesh_vertices_faces(FILE *file, Vertex *vertices, Face *faces)
{
    char *line = NULL;
    int line_length = 0;
    size_t linecap = 0;
    int indexF = 0;
    int indexV = 0;

    // Validate format
    while ((line_length = getline(&line, &linecap, file)) >= 0) {
        // Remove newline delimiter 
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        } 

        // Extract information
        extract_line_information(line, vertices + indexV, faces + indexF, &indexV, &indexF);

        // Free space
        free(line);
        line = NULL;
    }
}


void mesh_create(Maillage **mesh)
{
    // Dynamic allocation of space for 
    *mesh = (Maillage *) malloc(sizeof(Maillage));

    if ((*mesh) == NULL) {
        return;
    }
}

void mesh_destroy(Maillage **mesh)
{
    free(*mesh);
}

Maillage *create_mesh_from_obj_file(char const *filepath)
{
    Maillage *new_mesh = NULL;
    Vertex *vertices = NULL;
    Face *faces = NULL;
    FILE *file = NULL;

    int nb_vertices = 0;
    int nb_faces = 0;

    // File parsing
    file = fopen(filepath, "r");

    if (!file) {
        printf("Could not open file %s\n", filepath);
        return NULL;
    }
    
    // Validate format
    if (!is_obj_file_format_valid(file, &nb_vertices, &nb_faces)) {
        fclose(file);
        return NULL;
    }
   
    // Create mesh
    mesh_create(&new_mesh);
    vertices = (Vertex *) malloc(sizeof(Vertex) * nb_vertices);
    faces = (Face *) malloc(sizeof(Face) * nb_faces);

    if (!new_mesh || !vertices || !faces) {
        if (new_mesh) mesh_destroy(&new_mesh);
        if (vertices) free(vertices);
        if (faces) free(faces);
        fclose(file);
        return NULL;
    }

    new_mesh->vertices = vertices;
    new_mesh->faces = faces;
    new_mesh->nb_vertices = nb_vertices;
    new_mesh->nb_faces = nb_faces;

    // Line parsing
    fseek(file, 0, SEEK_SET);
    aggregates_mesh_vertices_faces(file, vertices, faces);

    fclose(file);
    return new_mesh;
}
        