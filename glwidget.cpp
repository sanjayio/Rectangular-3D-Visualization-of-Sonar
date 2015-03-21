#include "glwidget.h"
#include <QWidget>
#include <QtGui/qevent.h>
#include <QtOpenGL>
#include <iostream>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <QThread>
#include <time.h>

using namespace std;

static int k = 0;

bool selected = false;
int screenw = 640, screenh = 480;
static int position = 9;

float array[20][60] = {0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.5, 1, 0.5, 0.05,
                        0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.5, 1, 0.5, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0.5, 1, 0.5, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0.5, 1, 0.5, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.5, 1, 0.5, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 1, 0.5, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0.5, 1, 0.5, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0.5, 1, 0.55, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.5,1, 0.5, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.5, 1,0.5, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0.5, 1, 0.5,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.5, 1, 0.5, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.5, 1, 0.5, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0.5, 1, 0.5, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0.5, 1, 0.5, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0.5, 1, 0.5, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.5, 1, 0.5, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0.5, 1, 0.5, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0.5, 1, 0.5, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,
                       0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0.5, 1, 0.5, 0, 0, 0.05, 0.05, 0, 0.05, 0.05,0, 0, 0.05, 0, 0, 0.05, 0.05, 0, 0.05, 0.05};



GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(1000);
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1280, 720);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}



void GLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.5, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();


}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::displaylatest() {
    for(int i = 0; i < 60; i ++) {
        cout<<array[position][i]<<" ";
    }
    cout<<endl;
    updateGL();
    if(position == 0)
        position = 0;
    else
        position--;
}

void GLWidget::displayolder() {
    for(int i = 0; i < 60; i ++) {
        cout<<array[position][i]<<" ";
    }
    cout<<endl;
    updateGL();
    if(position == 19)
        position = 19;
    else
        position++;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    bool x = event->button() == Qt::LeftButton;
    bool y = event->button() == Qt::RightButton;
    if(x) {displaylatest();}
    if(y) {displayolder();}
}



void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);

    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void GLWidget::draw()
{
    if(k == 20) {
        k = 0;
    }
    int c = k++;
    glColor3f(1, 1, 1);
    glPointSize(2.0);
    glBegin(GL_QUADS);
    for(int d = 0; d < c; d++) {
        for(int j = 0; j < 59; j++) {
            if(((array[d][j] > 0.8) && (array[d][j] <= 1)) || ((array[d][j+1] > 0.8) && (array[d][j+1] <= 1)) || ((array[d+1][j+1] > 0.8) && (array[d+1][j+1] <= 1)) || ((array[d+1][j] > 0.8) && (array[d+1][j] <= 1))) {
                glColor3f(1, 0, 0);
                glVertex3f(0.05 * d, 0.05 * j, array[d][j]);
                glVertex3f(0.05 * (d+1), 0.05 * j, array[d+1][j]);
                glVertex3f(0.05 * (d+1), 0.05 * (j+1), array[d+1][j+1]);
                glVertex3f(0.05 * d, 0.05 * (j+1), array[d][j+1]);
            }
            if(((array[d][j] > 0.6) && (array[d][j] <= 0.8)) || ((array[d][j+1] > 0.6) && (array[d][j+1] <= 0.8)) || ((array[d+1][j] > 0.6) && (array[d+1][j] <= 0.8)) || ((array[d+1][j+1] > 0.6) && (array[d+1][j+1] <= 0.8))) {
                glColor3f(0.6, 0.4, 0);
                glVertex3f(0.05 * d, 0.05 * j, array[d][j]);
                glVertex3f(0.05 * (d+1), 0.05 * j, array[d+1][j]);
                glVertex3f(0.05 * (d+1), 0.05 * (j+1), array[d+1][j+1]);
                glVertex3f(0.05 * d, 0.05 * (j+1), array[d][j+1]);
            }
            if(((array[d][j] > 0.4) && (array[d][j] <= 0.6)) || ((array[d][j+1] > 0.4) && (array[d][j+1] <= 0.6)) || ((array[d+1][j] > 0.4) && (array[d+1][j] <= 0.6)) || ((array[d+1][j+1] > 0.4) && (array[d+1][j+1] <= 0.6))) {
                glColor3f(0.4, 0.6, 0);
                glVertex3f(0.05 * d, 0.05 * j, array[d][j]);
                glVertex3f(0.05 * (d+1), 0.05 * j, array[d+1][j]);
                glVertex3f(0.05 * (d+1), 0.05 * (j+1), array[d+1][j+1]);
                glVertex3f(0.05 * d, 0.05 * (j+1), array[d][j+1]);
            }
            if(((array[d][j] > 0.05) && (array[d][j] <= 0.4)) || ((array[d][j+1] > 0.1) && (array[d][j+1] <= 0.4)) || ((array[d+1][j] > 0.05) && (array[d+1][j] <= 0.4)) || ((array[d+1][j+1] > 0.05) && (array[d+1][j+1] <= 0.4))) {
                glColor3f(0.05, 0.8, 0);
                glVertex3f(0.05 * d, 0.05 * j, array[d][j]);
                glVertex3f(0.05 * (d+1), 0.05 * j, array[d+1][j]);
                glVertex3f(0.05 * (d+1), 0.05 * (j+1), array[d+1][j+1]);
                glVertex3f(0.05 * d, 0.05 * (j+1), array[d][j+1]);
            }
            if(((array[d][j] >= 0.0) && (array[d][j] <= 0.1)) || ((array[d][j+1] > 0.0) && (array[d][j+1] <= 0.05)) || ((array[d+1][j] > 0.0) && (array[d+1][j] <= 0.05)) || ((array[d+1][j+1] > 0.0) && (array[d+1][j+1] <= 0.05))) {
                glColor3f(0, 1, 0);
                glVertex3f(0.05 * d, 0.05 * j, array[d][j]);
                glVertex3f(0.05 * (d+1), 0.05 * j, array[d+1][j]);
                glVertex3f(0.05 * (d+1), 0.05 * (j+1), array[d+1][j+1]);
                glVertex3f(0.05 * d, 0.05 * (j+1), array[d][j+1]);
            }
        }
    }
    glEnd();
    glBegin(GL_LINES);
    glLineWidth(10.0);
    glColor3f(0, 0, 1);
    for(int i = 0; i < 60; i++) {
        glVertex3f(position * 0.05, 0.05 * i, array[position][i]);
        glVertex3f(position * 0.05, 0.05 * (i+1), array[position][i+1]);
    }
    glEnd();
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < 59; j ++) {
            glVertex3f(0.05 * i, 0.05 * j, 0);
            glVertex3f(0.05 * i, 0.05 * (j+1), 0);
            glVertex3f(0.05 * i, 0.05 * (j+1), 0);
            glVertex3f(0.05 * (i+1), 0.05 * (j+1), 0);
            glVertex3f(0.05 * (i+1), 0.05 * (j+1), 0);
            glVertex3f(0.05 * (i+1), 0.05 * j, 0);
            glVertex3f(0.05 * (i+1), 0.05 * j, 0);
            glVertex3f(0.05 * i, 0.05 * j, 0);
        }
    }
    for(int i = 0; i < 59; i++) {
        for(int j = 0; j < 20; j ++) {
                glVertex3f(0, 0.05 * i, 0.05 * j);
                glVertex3f(0, 0.05 * i, 0.05 * (j+1));
                glVertex3f(0, 0.05 * i, 0.05 * (j+1));
                glVertex3f(0, 0.05 * (i+1), 0.05 * (j+1));
                glVertex3f(0, 0.05 * (i+1), 0.05 * (j+1));
                glVertex3f(0, 0.05 * (i+1), 0.05 * j);
                glVertex3f(0, 0.05 * (i+1), 0.05 * j);
                glVertex3f(0, 0.05 * i, 0.05 * j);
        }
    }
    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < 20; j ++) {
                glVertex3f(0.05 * i, 0, 0.05 * j);
                glVertex3f(0.05 * i, 0, 0.05 * (j+1));
                glVertex3f(0.05 * i, 0, 0.05 * (j+1));
                glVertex3f(0.05 * (i+1), 0, 0.05 * (j+1));
                glVertex3f(0.05 * (i+1), 0, 0.05 * (j+1));
                glVertex3f(0.05 * (i+1), 0, 0.05 * j);
                glVertex3f(0.05 * (i+1), 0, 0.05 * j);
                glVertex3f(0.05 * i, 0, 0.05 * j);
        }
    }
    glEnd();

    glColor3f(1, 1, 1);
    for(int i = -30, j = 0; i <= 30; i+=5, j++) {
        renderText(1.1, j*0.24, 0, QString::number(i));
    }
    for(int j = 0; j < 20; j++) {
        renderText(j*0.05, 3, 0, QString::number(j));
    }
    for(int j = 0; j < 20; j++) {
        renderText(0, 3, j*0.05, QString::number(j*0.1));
    }

}

