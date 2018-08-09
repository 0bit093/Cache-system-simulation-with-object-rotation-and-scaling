//Madhusudhan_Ramakrishnaiah - A04735682

#include "ploting.h"
#include"math.h"

Plotting::Plotting(QWidget *parent,float x1,float y1,float z1)
    : QGLWidget(parent)
{
    a=x1;
    b=y1;
    c=z1;
    t=a-b-c;
}

Plotting::~Plotting()
{

}

void Plotting::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Plotting::resizeGL( int w, int h )
{
    if(w>h)
        glViewport((w-h)/2, 3, h, h);
    else
        glViewport(3, (h-w)/2, w, w);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Plotting::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-1.0,0.0);
    glVertex2f(1.0,0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(0.0,-1.0);
    glVertex2f(0.0,1.0);
    glEnd();

    drawgraph();
    glFlush();
}

void Plotting::drawgraph()
{
    glBegin(GL_LINE_STRIP);

    //sets the color to yellow
    glColor3f(1.0,1.0,0.0);
    glLineWidth(0.8);

    GLfloat y=0.0;
    for(GLfloat x = 0.0;x<=15;x+=0.1)
    {

        y= a + b *x + c* (x*x);
        glVertex2f(x, y );


    }
    glEnd();

}





