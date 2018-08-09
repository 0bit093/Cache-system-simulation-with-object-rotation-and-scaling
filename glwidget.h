//Madhusudhan Ramakrishnaiah - A04735682

#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QtGui>
#include <QGLWidget>

class TRS : public QGLWidget
{
    Q_OBJECT

public:

    TRS(QWidget *parent = 0);
    ~TRS();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void rotating_ob(int val);
    void scaling_ob(int val);

private:

    //for rotating around x,y,z axis
    GLfloat r_x;
    GLfloat r_y;
    GLfloat r_z;

    //for scaling around x,y,z axis
    float s_x;
    float s_y;
    float s_z;

};

#endif // GLWIDGET_H
