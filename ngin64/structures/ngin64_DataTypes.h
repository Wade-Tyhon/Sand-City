#ifndef NGIN64_DATATYPES_H
#define NGIN64_DATATYPES_H

#define true 1
#define false 0

#define PI 3.14159
#define RAD2DEG 57.29577

/*NGin64 styled int - unsigned*/
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

/*NGin64 styled int - signed*/
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

/*NGin64 styled Vectors*/

typedef struct {
    float r;
    float g;
    float b;
    float a;
}RGBA;

typedef struct {
    float r;
    float g;
    float b;
}RGB;

typedef struct {
    float x;
    float y;
    float z;
    float w;
}Vector4;

typedef struct {
	float x;
	float y;
	float z;
}Vector3;

typedef struct {
	float x;
	float y;
}Vector2;

typedef struct {
    int x;
    int y;
}Coords2;

typedef struct {
    int x;
    int y;
    int z;
}Coords3;

/*NGin64 styled Vertex and Tri index - for storing model data*/

typedef struct {
    Vector3 pos; //position of the vertex
    Vector2 uv[3]; //UV coordinates of the vertex. Future proof: setting this up as an array
    Vector3 vNormal; //normal direction of the vertex, typically used for scene lit, dynamic objects
    RGBA vColor; // R,G,B,A, used for static objects
}XP64_Vert;

typedef struct {
    uint16_t index[3]; //index list of the vertices used in this tri. aka (1, 4, 2)
    u8 uvIdx; //which alternate version of the UV coordinates is being used (for now, there are 3 separate versions set up, but 0 will be used XP64_Vert.uv[0] will be used by default)
}XP64_Tri;



typedef struct {
    float pos[3]; //position of the vertex
    float uv[2]; //position of the vertex
    //Vector3 uv[3]; //UV coordinates of the vertex. Future proof: setting this up as an array
    float vNormal[3]; //normal direction of the vertex, typically used for scene lit, dynamic objects
    u8 vColor[4]; // R,G,B,A, used for static objects
}gl_XP64_Vert;

typedef struct {
    uint16_t index[3]; //index list of the vertices used in this tri. aka (1, 4, 2)
}gl_XP64_Poly;

/*
static const GLfloat cube_vert[8][3] = {

    {1.0f, 1.0f, 1.0f}, //0
    {1.0f, 1.0f,-1.0f}, //1
    {-1.0f, 1.0f,-1.0f},//2
    {-1.0f, 1.0f, 1.0f},//3
    {1.0f,-1.0f, 1.0f}, //4
    {1.0f,-1.0f,-1.0f}, //5
    {-1.0f,-1.0f, 1.0f},//6
    {-1.0f,-1.0f,-1.0f},//7

};

static GLuint cube_index[12][3] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 3, 4},
    {5, 0, 4},
    {0, 5, 1},
    {4, 6, 7},
    {3, 6, 4},
    {1, 5, 7},
    {7, 3, 2},
    {7, 6, 3},
    {1, 7, 2},
    {4, 7, 5},
};
*/



#endif