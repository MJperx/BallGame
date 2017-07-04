#ifndef VONAL_H
#define VONAL_H

typedef struct {GLfloat x, y;} VECTOR2;
typedef struct {GLfloat x, y;} PONT;
typedef struct {GLfloat A, B, C; VECTOR2 n;} VONAL;

VECTOR2 init(GLfloat x, GLfloat y){
    VECTOR2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

class Vonal{
    public:
        PONT b;
        PONT e;
        VECTOR2 v;

        Vonal(){};
        
        Vonal(PONT b, PONT e){
            this->b=b;
            this->e=e;
        }

        VONAL egyenes(){
            VONAL l;
            l.A = -(e.y - b.y);
            l.B = e.x - b.x;
            l.C = ((e.y - b.y) * b.x) - ((e.x - b.x) * b.y);
            l.n = init(l.A,l.B);
            return l;
        }

        float egyenlet(PONT p){
            return egyenes().A * p.x + egyenes().B * p.y + egyenes().C;
        }

        void rajz(){
            glBegin(GL_LINES);
                glVertex2f(b.x,b.y);
                glVertex2f(e.x,e.y);
            glEnd();
        } 
};

#endif