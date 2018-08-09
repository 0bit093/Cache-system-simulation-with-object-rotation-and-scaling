//Madhusudhan Ramakrishnaiah - A04735682

#include "glwidget.h"
#define PI 4.0*atan(1.0)


TRS::TRS(QWidget *parent)
    : QGLWidget(parent){

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    //rotation variables, default values
    r_x = 0;
    r_y = 0;
    r_z = 0;

    //scaling variables, default values
    s_x=1.0;
    s_y=1.0;
    s_z=1.0;

}

TRS::~TRS()
{

}

void TRS::initializeGL(){

   qglClearColor(Qt::black);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

}

void TRS::resizeGL(int width, int height){

    //opens in viewport
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    //loads identity matrix
    glLoadIdentity();

    GLfloat x = (GLfloat)width / height;
    //for perscpective view passing values to top,bottom,znear,zfar
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void TRS::paintGL(){

    //clearing the buffer bits
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //modelview matrix
    glMatrixMode(GL_MODELVIEW);
    //loading identity matrix
    glLoadIdentity();
    //translates the object
    glTranslatef(0.0, 0.0, -10.0);
    //rotates the object with Circle as the center
    glRotatef(r_x, 1.0, 0.0, 0.0);
    glRotatef(r_y, 0.0, 1.0, 0.0);
    glRotatef(r_z, 0.0, 0.0, 1.0);
    //scale the object with Circle as the center
    glScalef(s_x,s_y,s_z);


    //for drawing Circle and using it as the center for Translation, Rotation and Scaling
    float i,n=36,sum;
    sum=2.0*PI/(float)n;
    glBegin(GL_POLYGON);
    //sets the color to yellow
    glColor3f(1.0,1.0,0.0);
    for(i=0;i<=n;i++)
        glVertex3f(0.3*sin(sum*(float)i),0.3*cos(sum*(float)i),0.0);
    glEnd();
    glPopMatrix();


    //LINE
    //sets the line width to 2 pixels
    glLineWidth(2.0);
    //using GL primitives
    glBegin(GL_LINES);
    //sets the color to cyan
    glColor3f(0.0,1.0,1.0);
    glVertex3f(1.1,0.3,0.0);
    glVertex3f(0.9,0.6,0.0);
    glEnd();


    //POINT
    //sets the pixels to 4
    glPointSize(4.0);
    glBegin(GL_POINTS);
    //sets the color to white
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.5,-0.5,0.0);
    //for drawing point and using it as the center for Translation and Rotation
    //glVertex3f(0.0,-0.1,0.0);
    glEnd();


    //CUBE
    //using polygon GL primitive for all the faces
    //left view
    glBegin(GL_POLYGON);
    //sets the color to magneta
    glColor3f(1.0,0.0,1.0);
    glVertex3f(0.3,0.3,-0.3);
    glVertex3f(0.3,0.7,-0.3);
    glVertex3f(0.3,0.7,0.7);
    glVertex3f(0.3,0.3,0.7);
    glEnd();

    //right view
    glBegin(GL_POLYGON);
    //sets the color to blue
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.7,0.3,-0.3);
    glVertex3f(0.7,0.7,-0.3);
    glVertex3f(0.7,0.7,0.7);
    glVertex3f(0.7,0.3,0.7);
    glEnd();

    //front view
    glBegin(GL_POLYGON);
    //sets the color to red
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.3,0.3,-0.3);
    glVertex3f(0.3,0.7,-0.3);
    glVertex3f(0.7,0.7,-0.3);
    glVertex3f(0.7,0.3,-0.3);
    glEnd();

    //back view
    glBegin(GL_POLYGON);
    //sets the color to white
    glColor3f(1.0,1.0,1.0);
    glVertex3f(0.3,0.3,0.7);
    glVertex3f(0.3,0.7,0.7);
    glVertex3f(0.7,0.7,0.7);
    glVertex3f(0.7,0.3,0.7);
    glEnd();

    //top view
    glBegin(GL_POLYGON);
    //sets the color to cyan
    glColor3f(0.0,1.0,1.0);
    glVertex3f(0.3,0.7,-0.3);
    glVertex3f(0.3,0.7,0.7);
    glVertex3f(0.7,0.7,0.7);
    glVertex3f(0.7,0.7,-0.3);
    glEnd();

    //bottom view
    glBegin(GL_POLYGON);
    //sets the color to yellow
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.3,0.3,-0.3);
    glVertex3f(0.3,0.3,0.7);
    glVertex3f(0.7,0.3,0.7);
    glVertex3f(0.7,0.3,-0.3);
    glEnd();


    //SQUARE
    glBegin(GL_QUADS);
    //sets the color to blue
    glColor3f(0.0,0.0,1.0);
    //co-ordinates for the vertices
    glVertex3f(-0.3,0.9,0.0);
    glVertex3f(-0.3,0.3,0.0);
    glVertex3f(-0.9,0.3,0.0);
    glVertex3f(-0.9,0.9,0.0);
    glEnd();


    //TRIANGLE
    glBegin(GL_TRIANGLES);
    //sets the color to red
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.9,-0.5,0.0);
    glVertex3f(0.9,-0.9,0.0);
    glVertex3f(0.5,-0.9,0.0);
    glEnd();


    //HEXAGON
    glBegin(GL_POLYGON);
    //sets color to multicolor before drawing each vertex
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-0.3,-0.4,0.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-0.3,-0.7,0.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-0.6,-0.9,0.0);
    glColor3f(0.5,1.0,1.0);
    glVertex3f(-0.9,-0.7,0.0);
    glColor3f(0.5,1.0,1.0);
    glVertex3f(-0.9,-0.4,0.0) ;
    glColor3f(0.0,1.0,0.0);
    glVertex3f(-0.6,-0.2, 0.0) ;
    glEnd();

    //before used gl commands to execute
    glFlush();

}

//fn for roatation by 1.0 using CIRCLE as center
void TRS::rotating_ob(int temp){

    for(int i=0;i<temp;i++){
        r_x+=1.0;
        r_y+=1.0;
        r_z+=1.0;
        paintGL();
        updateGL();
    }
}

//fn for scaling objects using CIRCLE as center
void TRS::scaling_ob(int temp){

    if((s_x<temp)&&(s_y<temp)&&(s_z<temp)){
        s_x = s_x + temp;
        s_y = s_y + temp;
        s_z = s_z + temp;
    }

    else if((s_x>temp)&&(s_y>temp)&&(s_z>temp)){
        s_x = s_x - temp;
        s_y = s_y - temp;
        s_z = s_z - temp;
    }

    else{
        s_x = temp;
        s_y = temp;
        s_z = temp;
    }

    paintGL();
    updateGL();
}










