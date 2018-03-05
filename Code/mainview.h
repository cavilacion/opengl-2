#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <memory>

#include "geometry.h"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    // Dit is volgend mij nodig, maar weet ik niet zeker
    QOpenGLShaderProgram currentShaderProgram;
    QOpenGLShaderProgram normalShaderProgram;
    QOpenGLShaderProgram phongShaderProgram;
    QOpenGLShaderProgram gouraudShaderProgram;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD
    };

    ShadingMode currentShading = MainView::NORMAL;

    MainView(QWidget *parent = 0);
    ~MainView();

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    // Matrices
    QMatrix4x4 modelMatrix;
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 rotationMatrix;
    QMatrix4x4 scalingMatrix;

    QMatrix3x3 normalMatrix;

    float lightPosition[4] = {10.0,10.0,10.0,0.0};

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:

    GLuint vaoModel;
    GLuint bufferId[1];

    // normal
    GLint locations;
    GLint projectionLocation;
    GLint transformation;
    GLint normalTransform;
    GLint normalLightPosition;

    // gouraud
    GLint gouraudLocations;
    GLint gouraudProjectionLocation;
    GLint gouraudTransformation;
    GLint gouraudNormalTransform;
    GLint gouraudLightPosition;

    // phong
    GLint phongLocations;
    GLint phongProjectionLocation;
    GLint phongTransformation;
    GLint phongNormalTransform;
    GLint phongLightPosition;

    // current
    GLint currentLocations;
    GLint currentProjectionLocation;
    GLint currentTransformation;
    GLint currentNormalTransform;
    GLint currentLightPosition;

    void createShaderProgram();
    Vertex createVertex(float x, float y, float z, float i, float j, float k);

    Vertex *modelVertices;
    int modelSize;

    /* OLD CODE FROM PART 1 *

    QMatrix4x4 cubeMatrix;
    QMatrix4x4 mPyramid;

    GLuint vaoCube;
    GLuint vaoPyramid;

    Square createSquare(Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6);

    Triangle createTriangle(Vertex v1, Vertex v2, Vertex v3);

    void createCube(float x1, float y1, float z1,
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4,
                    float x5, float y5, float z5,
                    float x6, float y6, float z6,
                    float x7, float y7, float z7,
                    float x8, float y8, float z8 );
    void createPyramid (float x1, float y1, float z1,
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4,
                    float x5, float y5, float z5 );

    Cube cube;
    Pyramid pyr;*/
};

#endif // MAINVIEW_H
