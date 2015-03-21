#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
void initializeGL();
void paintGL();
void resizeGL(int width, int height);

QSize minimumSizeHint() const;
QSize sizeHint() const;
void mousePressEvent(QMouseEvent *event);
void mouseMoveEvent(QMouseEvent *event);
//void keyPressEvent(QKeyEvent *event);
void displaylatest();
void displayolder();


signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public slots:
// slots for xyz-rotation slider
void setXRotation(int angle);
void setYRotation(int angle);
void setZRotation(int angle);

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;
    QTimer timer;

    QPoint lastPos;
};

#endif // GLWIDGET_H
