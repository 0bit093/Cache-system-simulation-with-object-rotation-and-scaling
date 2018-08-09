//Madhusudhan_Ramakrishnaiah - A04735682

#ifndef PLOTING_H
#define PLOTING_H

#include <QGLWidget>

class Plotting : public QGLWidget {

public:

    Plotting(QWidget *parent = 0,float x1 = 0.0,float y1 = 0.0 ,float z1 = 0.0);
    ~Plotting();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    float a;
    float b;
    float c;
    GLfloat t;

    void drawgraph();


};

#endif // PLOTING_H
