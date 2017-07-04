#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <time.h>
#include <vector>
#include "Circle.h"
#include "Line.h"
#include <iostream>

#define winH 600
#define winW 800

#define lepeskoz 5

GLint keyStates[256]; 

std::vector<Kor> Korok;

Vonal felsovonal, alsovonal, balvonal, jobbvonal, fuggvonal, vizvonal;

float vectorNorm(VECTOR2 v){
    return sqrt(v.x * v.x + v.y * v.y);
}

float dPL(Vonal L, PONT p){
    return abs(L.egyenes().A * p.x + L.egyenes().B * p.y + L.egyenes().C) / vectorNorm(L.egyenes().n);
}

float dPP(PONT l, PONT p){
    return sqrt(pow((p.x-l.x),2) + pow((p.y-l.y),2));
}

void init(void){
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, winW, 0.0, winH);
    glShadeModel(GL_FLAT);
    glPointSize(2.0);
    glEnable(GL_LINE_SMOOTH);
    felsovonal = Vonal(PONT{0.f,winH},PONT{winW,winH});
    alsovonal = Vonal(PONT{0.f,0.f},PONT{winW,0.f});
    balvonal = Vonal(PONT{0.f,0.f},PONT{0.f,winH});
    jobbvonal = Vonal(PONT{winW,0.f},PONT{winW,winH});
    fuggvonal = Vonal(PONT{0.f,winH/2},PONT{winW,winH/2});
    vizvonal = Vonal(PONT{winW/2,0.f},PONT{winW/2,winH});
}

void keyPressed(unsigned char key, int x, int y){
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y){
    keyStates[key] = 0;
}

void keyOperations(){
    if(keyStates['a']){
        if(fuggvonal.b.y <= winH && fuggvonal.e.y >= 0){
            fuggvonal.b.y+=1;
            fuggvonal.e.y-=1;
        }
    }

    if(keyStates['d']){
        if(fuggvonal.b.y >= 0 && fuggvonal.e.y <= winH){
            fuggvonal.b.y--;
            fuggvonal.e.y++;
        }
    }

    if(keyStates['w']){
        if(vizvonal.b.x <=winW && vizvonal.e.x >= 0){
            vizvonal.b.x++;
            vizvonal.e.x--;
        }
    }

    if(keyStates['s']){
        if(vizvonal.b.x >=0 && vizvonal.e.x <= winW){
            vizvonal.b.x--;
            vizvonal.e.x++;
        }
    }

    if(keyStates['c']){
        Korok.clear();
    }

    glutPostRedisplay();
}

void processMouse(GLint button, GLint action, GLint xMouse , GLint yMouse){
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        PONT a;
        VECTOR2 vec;

        vec.x = randomFloat(1,6);
        vec.y = randomFloat(1,6);
        a.x = xMouse;
        a.y = 600 - yMouse;

        int pontok = randomFloat(3,10);

        Korok.push_back(Kor(a,20,vec,pontok));        
    }

    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
        PONT a, b;
        for(int i = 0; i < Korok.size(); i++){
            a.x = Korok.at(i).getKozeppont().x;
            a.y = Korok.at(i).getKozeppont().y;
            b.x = xMouse;
            b.y = 600-yMouse;
            if (dPP(a,b) < Korok.at(i).getSugar()){
                Korok.erase(Korok.begin()+i);
            }
        }   
    }
    
    if (button == 3){
        PONT a, b;
        for(int i = 0; i < Korok.size(); i++){
            a.x = Korok.at(i).getKozeppont().x;
            a.y = Korok.at(i).getKozeppont().y;
            b.x = xMouse;
            b.y = 600-yMouse;
            if (dPP(a,b) < Korok.at(i).getSugar()){
                Korok.at(i).setSugar(Korok.at(i).getSugar()+1);
            }
        } 
    }

    if (button == 4){
        PONT a, b;
        for(int i = 0; i < Korok.size(); i++){
            if(Korok.at(i).getSugar()>=10){
                a.x = Korok.at(i).getKozeppont().x;
                a.y = Korok.at(i).getKozeppont().y;
                b.x = xMouse;
                b.y = 600-yMouse;
                if (dPP(a,b) < Korok.at(i).getSugar()){
                    Korok.at(i).setSugar(Korok.at(i).getSugar()-1);
                }
            }
        } 
    }
}

void racsSzin(PONT p){
    if(fuggvonal.egyenlet(p) > 0 && vizvonal.egyenlet(p) > 0){
        return glColor3f (1.0, 0.0, 0.0);
    } else if (fuggvonal.egyenlet(p) > 0 && vizvonal.egyenlet(p) < 0){
        return glColor3f (0.0, 0.0, 1.0);
    } else if (fuggvonal.egyenlet(p) < 0 && vizvonal.egyenlet(p) < 0){
        return glColor3f (0.0, 1.0, 0.0);
    } else {
        return glColor3f (1.0, 1.0, 0.0);
    }
}

void draw(void){
    keyOperations();

    glClear (GL_COLOR_BUFFER_BIT);    

    glBegin(GL_POINTS);
    PONT p;
    for (int i = lepeskoz; i <= winW - lepeskoz ; i+=lepeskoz){
        for (int j = lepeskoz; j <= winH - lepeskoz; j+=lepeskoz){
            p.x = i;
            p.y = j;
            racsSzin(p); 
            glVertex2f(i,j);
        }
    }
    glEnd();

    glColor3f (0.0, 0.0, 0.0);

    fuggvonal.rajz();
    vizvonal.rajz();

    for (int i = 0; i < Korok.size(); i++){
        Korok.at(i).rajz();
    }

    glutSwapBuffers();
}

void LineBounce(Vonal L, Kor &C){
    C.setSebessegvektor(C.getSebessegvektor().x*-1,C.getSebessegvektor().y*-1);
    
    float a = C.v.x * L.egyenes().A + C.v.y * L.egyenes().B; //sk
    float b = L.egyenes().A * L.egyenes().A + L.egyenes().B * L.egyenes().B;
    
    VECTOR2 norm = init(L.egyenes().A * (2 * (a / b)), L.egyenes().B * (2 * (a / b)));
    
    C.setSebessegvektor(norm.x - C.getSebessegvektor().x, norm.y - C.getSebessegvektor().y);
}

bool pattan(Vonal L,Kor &C){
    float tav = dPL(L, C.getKozeppont());
    if (tav <= C.getSugar()){
        return true;
    } else {
        return false;
    }
}

void update(int n){
    glClear( GL_COLOR_BUFFER_BIT ) ;
    glColor3f (0.0, 0.0, 0.0);

    for ( int i = 0; i < Korok.size(); i++){
        if(pattan(felsovonal,Korok.at(i))){
            LineBounce(felsovonal, Korok.at(i));
        }else if(pattan(alsovonal,Korok.at(i))){
            LineBounce(alsovonal, Korok.at(i));
        }else if(pattan(jobbvonal,Korok.at(i))){
            LineBounce(jobbvonal, Korok.at(i));
        }else if(pattan(balvonal,Korok.at(i))){
            LineBounce(balvonal, Korok.at(i));
        }else if(pattan(vizvonal,Korok.at(i))){
            LineBounce(vizvonal, Korok.at(i));
        }else if(pattan(fuggvonal,Korok.at(i))){
            LineBounce(fuggvonal, Korok.at(i));
        }
    }

    for(int i = 0;i < Korok.size() ;i++){
        Korok.at(i).frissit();
    }

    glutPostRedisplay();
    glutTimerFunc( 10, update, 0 );
}

int main(int argc, char** argv){
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("first");
    init();
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutDisplayFunc(draw);
    glutMouseFunc(processMouse);
    glutTimerFunc(10,update,0);
    glutMainLoop();
    return 0;
}
