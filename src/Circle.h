#ifndef KOR_H
#define KOR_H
#include "Line.h"

#define PI 3.141592653589793238462643383279

std::vector<PONT> p1a;

class Kor {
public:
	PONT p;
	GLfloat r;
	VECTOR2 v;
	int pontok; 

	Kor(PONT p, float r, VECTOR2 v, int pontok){
		this->p = p;
		this->r = r;
		this->v = v;
		this->pontok = pontok;
	}
		
	PONT getKozeppont(){
		return p;
	}
	void setKozeppont(float x, float y){
		p.x = x;
		p.y = y;
	}
	
	GLfloat getSugar(){
		return r;
	}
	void setSugar(float r){
		this->r = r;
	}

	VECTOR2 getSebessegvektor(){
		return v;
	}
		
	void setSebessegvektor(float x, float y){
		v.x = x;
		v.y = y;
	}
	
	void frissit(){
		setKozeppont(p.x + v.x,p.y + v.y);
	}
	
	void rajz(){
		glBegin (GL_LINE_LOOP);
			for(int i=0;i<24;i+=1){
				glVertex2f(getKozeppont().x+getSugar()*cos(i*2*PI/24), getKozeppont().y+getSugar()*sin(i*2*PI/24));
			}
    	glEnd ( );

		glBegin(GL_LINE_LOOP);
			for (int i = 0; i < pontok; i++){
				glVertex2f(getKozeppont().x + getSugar() * sin(2.0*PI*i/pontok), getKozeppont().y + getSugar() * cos(2.0*PI*i/pontok));
			}
   		glEnd();
		
		p1a.clear();

		for (int i = 0; i < pontok; i++){
			GLfloat pointDist = (360 / pontok) * (PI / 180);
			GLfloat tempx = getKozeppont().x + getSugar() * cos(i * pointDist);
			GLfloat tempy = getKozeppont().y + getSugar() * sin(i * pointDist);
			p1a.emplace_back(PONT{tempx,tempy});
		}

		glBegin(GL_LINES);
			for (int i = 0; i < pontok; i++)
				for (int j = i + 1; j < pontok; j++){
				glVertex2d(p1a.at(i).x, p1a.at(i).y);
				glVertex2d(p1a.at(j).x, p1a.at(j).y);
				}
		glEnd();
	}
};

#endif