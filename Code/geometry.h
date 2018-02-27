#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Vertex {
    // position
    float x;
    float y;
    float z;

    // normal
    float i;
    float j;
    float k;
};

/* Square consists of three triangles, so 6 vertices
*/
struct Square {
    // Vertices
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Vertex v4;
    Vertex v5;
    Vertex v6;
};

typedef struct C* Cube;
struct C {
    Square s1;
    Square s2;
    Square s3;
    Square s4;
    Square s5;
    Square s6;
};

struct Triangle {
    Vertex v1;
    Vertex v2;
    Vertex v3;
};

typedef struct P* Pyramid;
struct P {
    Square bottom;
    Triangle t1;
    Triangle t2;
    Triangle t3;
    Triangle t4;
};

#endif

