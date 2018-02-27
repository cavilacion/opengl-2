#include "mainview.h"
#include "math.h"
#include "geometry.h"

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    // Create Cube
    createCube( -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f);

    cubeMatrix.translate(2.0f,0.0f,-6.0f);

    // create pyramid
    createPyramid( -1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f,  1.0f,
                    1.0f, -1.0f, -1.0f,
                   -1.0f, -1.0f, -1.0f,
                    0.0f,  1.0f,  0.0f);
    mPyramid.translate(-2.0f,0.0f,-6.0f);

    projectionMatrix.perspective(60.0f, width()/height(), 0.1f, 20.0f);
    rotationMatrix.setToIdentity();

    Model *sphere = new Model(":/models/sphere.obj");
    QVector<QVector3D> sphereCoordinates = sphere->getVertices();
    sphereLength = sphereCoordinates.length();

    for(int i = 0; i < sphereCoordinates.length(); i++){
        sphereVertices[i] = createVertex(sphereCoordinates[i].x(),
                                         sphereCoordinates[i].y(),
                                         sphereCoordinates[i].z(),
                                         (float) (std::rand() / (float) RAND_MAX),
                                         (float) (std::rand() / (float) RAND_MAX),
                                         (float) (std::rand() / (float) RAND_MAX));
    }

    sphereMatrix.translate(0,0,-10);
    sphereMatrix.scale(0.04f);
}

void MainView::createCube (float x1, float y1, float z1,
                 float x2, float y2, float z2,
                 float x3, float y3, float z3,
                 float x4, float y4, float z4,
                 float x5, float y5, float z5,
                 float x6, float y6, float z6,
                 float x7, float y7, float z7,
                 float x8, float y8, float z8 ) {
    cube = (Cube) malloc (sizeof(C));
    cube->s1 = createSquare(
                createVertex( x1, y1, z1, 0.0f,0.0f,1.0f),
                createVertex( x2, y2, z2, 0.0f,0.0f,1.0f),
                createVertex( x3, y3, z3, 0.0f,0.0f,1.0f),
                createVertex( x1, y1, z1, 0.0f,0.0f,1.0f),
                createVertex( x3, y3, z3, 0.0f,0.0f,1.0f),
                createVertex( x4, y4, z4, 0.0f,0.0f,1.0f)
                );
    cube->s2 = createSquare(
                createVertex( x2, y2, z2, 0.0f,1.0f,0.0f),
                createVertex( x6, y6, z6, 0.0f,1.0f,0.0f),
                createVertex( x7, y7, z7, 0.0f,1.0f,0.0f),
                createVertex( x2, y2, z2, 0.0f,1.0f,0.0f),
                createVertex( x7, y7, z7, 0.0f,1.0f,0.0f),
                createVertex( x3, y3, z3, 0.0f,1.0f,0.0f)
                );
    cube->s3 = createSquare(
                createVertex( x4, y4, z4, 1.0f,0.0f,0.0f),
                createVertex( x3, y3, z3, 1.0f,0.0f,0.0f),
                createVertex( x7, y7, z7, 1.0f,0.0f,0.0f),
                createVertex( x4, y4, z4, 1.0f,0.0f,0.0f),
                createVertex( x7, y7, z7, 1.0f,0.0f,0.0f),
                createVertex( x8, y8, z8, 1.0f,0.0f,0.0f)
                );
    cube->s4 = createSquare(
                createVertex( x5, y5, z5, 1.0f,1.0f,1.0f),
                createVertex( x1, y1, z1, 1.0f,1.0f,1.0f),
                createVertex( x4, y4, z4, 1.0f,1.0f,1.0f),
                createVertex( x4, y4, z4, 1.0f,1.0f,1.0f),
                createVertex( x8, y8, z8, 1.0f,1.0f,1.0f),
                createVertex( x5, y5, z5, 1.0f,1.0f,1.0f)
                );
    cube->s5 = createSquare(
                createVertex( x1, y1, z1, 0.0f,1.0f,1.0f),
                createVertex( x5, y5, z5, 0.0f,1.0f,1.0f),
                createVertex( x6, y6, z6, 0.0f,1.0f,1.0f),
                createVertex( x6, y6, z6, 0.0f,1.0f,1.0f),
                createVertex( x2, y2, z2, 0.0f,1.0f,1.0f),
                createVertex( x1, y1, z1, 0.0f,1.0f,1.0f)
                );
    cube->s6 = createSquare(
                createVertex( x7, y7, z7, 1.0f,0.0f,1.0f),
                createVertex( x6, y6, z6, 1.0f,0.0f,1.0f),
                createVertex( x5, y5, z5, 1.0f,0.0f,1.0f),
                createVertex( x8, y8, z8, 1.0f,0.0f,1.0f),
                createVertex( x7, y7, z7, 1.0f,0.0f,1.0f),
                createVertex( x5, y5, z5, 1.0f,0.0f,1.0f)
                );
}

void MainView::createPyramid (float x1, float y1, float z1,
                        float x2, float y2, float z2,
                        float x3, float y3, float z3,
                        float x4, float y4, float z4,
                        float x5, float y5, float z5 ) {
    pyr = (Pyramid) malloc (sizeof(P));
    pyr->bottom = createSquare(
                   createVertex( x1, y1, z1, 1.0f,0.0f,0.0f),
                   createVertex( x4, y4, z4, 1.0f,0.0f,0.0f),
                   createVertex( x3, y3, z3, 1.0f,0.0f,0.0f),
                   createVertex( x3, y3, z3, 1.0f,0.0f,0.0f),
                   createVertex( x2, y2, z2, 1.0f,0.0f,0.0f),
                   createVertex( x1, y1, z1, 1.0f,0.0f,0.0f)
                  );
    pyr->t1 = createTriangle(
                   createVertex( x1, y1, z1, 0.0f,1.0f,0.0f),
                   createVertex( x2, y2, z2, 0.0f,1.0f,0.0f),
                   createVertex( x5, y5, z5, 0.0f,1.0f,0.0f)
               );
    pyr->t2 = createTriangle(
                   createVertex( x2, y2, z2, 0.0f,0.0f,1.0f),
                   createVertex( x3, y3, z3, 0.0f,0.0f,1.0f),
                   createVertex( x5, y5, z5, 0.0f,0.0f,1.0f)
               );
    pyr->t3 = createTriangle(
                   createVertex( x3, y3, z3, 1.0f,1.0f,1.0f),
                   createVertex( x4, y4, z4, 1.0f,1.0f,1.0f),
                   createVertex( x5, y5, z5, 1.0f,1.0f,1.0f)
               );
    pyr->t4 = createTriangle(
                   createVertex( x4, y4, z4, 1.0f,1.0f,0.0f),
                   createVertex( x1, y1, z1, 1.0f,1.0f,0.0f),
                   createVertex( x5, y5, z5, 1.0f,1.0f,0.0f)
               );
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();

    qDebug() << "MainView destructor";

    glDeleteBuffers(3,bufferId);
   glDeleteVertexArrays(1,&vaoPyramid);
    glDeleteVertexArrays(1,&vaoCube);
    glDeleteVertexArrays(1,&vaoSphere);
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();

    glGenBuffers(3, bufferId);

    glGenVertexArrays(1, &vaoCube);
    glGenVertexArrays(1, &vaoSphere);
    glGenVertexArrays(1, &vaoPyramid);

    glBindVertexArray(vaoCube);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId[0]);
    glBufferData(GL_ARRAY_BUFFER, 6*6*sizeof(Vertex), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0); // point
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid*)(sizeof(float)*3)); // color
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer (GL_ARRAY_BUFFER,0);

    glBindVertexArray(vaoSphere);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
    glBufferData(GL_ARRAY_BUFFER, sphereLength * sizeof(Vertex), sphereVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0); // point
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid*)(sizeof(float)*3)); // color
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer (GL_ARRAY_BUFFER,0);

    glBindVertexArray(vaoPyramid);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId[2]);
    glBufferData(GL_ARRAY_BUFFER, (6+4*3)*sizeof(Vertex), (GLvoid*)pyr, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0); // point
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid*)(sizeof(float)*3)); // color
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer (GL_ARRAY_BUFFER,0);
}

Vertex MainView::createVertex(float x, float y, float z, float r, float g, float b){
    Vertex v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.r = r;
    v.g = g;
    v.b = b;
    return v;
}

Square MainView::createSquare(Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6){
    Square s;
    s.v1 = v1;
    s.v2 = v2;
    s.v3 = v3;
    s.v4 = v4;
    s.v5 = v5;
    s.v6 = v6;
    return s;
}

Triangle MainView::createTriangle(Vertex v1, Vertex v2, Vertex v3) {
    Triangle t;
    t.v1 = v1;
    t.v2 = v2;
    t.v3 = v3;
    return t;
}

void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaderProgram.link();

    locations = shaderProgram.uniformLocation("modelTransform");
    projectionLocation = shaderProgram.uniformLocation("projectionTransform");
    transformation = shaderProgram.uniformLocation("transformation");
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();    

    glUniformMatrix4fv(projectionLocation,1,false,projectionMatrix.data());

    QMatrix4x4 transformationMatrix = rotationMatrix * scalingMatrix;

    glUniformMatrix4fv(transformation,1,false,transformationMatrix.data());

    // Draw Cube
    glUniformMatrix4fv(locations,1,false,cubeMatrix.data());
    glBindVertexArray(vaoCube);
    glDrawArrays(GL_TRIANGLES, 0, 6*6);

    // Draw Sphere
    glUniformMatrix4fv(locations,1,false,sphereMatrix.data());
    glBindVertexArray(vaoSphere);
    glDrawArrays(GL_TRIANGLES, 0, sphereLength);

    // Draw Pyramid
    glUniformMatrix4fv(locations,1,false,mPyramid.data());
    glBindVertexArray(vaoPyramid);
    glDrawArrays(GL_TRIANGLES, 0, 6+4*3);

    shaderProgram.release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    // TODO: Update projection to fit the new aspect ratio
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(60.0f, newWidth/newHeight, 0.1f, 20.0f);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    //Q_UNIMPLEMENTED();
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(rotateX, {1,0,0});
    rotationMatrix.rotate(rotateY, {0,1,0});
    rotationMatrix.rotate(rotateZ, {0,0,1});
    update();

}

void MainView::setScale(int scale)
{
    qDebug() << "Scale changed to " << scale;
    //Q_UNIMPLEMENTED();
    scalingMatrix.setToIdentity();
    float percentage = 0.01f;
    scalingMatrix.scale(scale*percentage);
    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    Q_UNIMPLEMENTED();
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}
