#include<stdio.h>
#include<string>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<iostream>
using namespace std;

#define WIDTH 800
#define HEIGHT 600

int win_id=0;
int projectionMode = 0;                     // 0 = Perspective, 1 = Orthographic


struct viewDetails {
    float fieldOfView, aspectRatio, nearField, farField,
        orthoLeft, orthoRight, orthoBottom, orthoTop;
};

struct viewDetails view;

void printModelViewMatrix() {
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    cout << "Top most matrix in the stack:-" << endl;
    cout << m[0] << ' ' << m[4] << ' ' << m[8] << ' ' << m[12] << endl;
    cout << m[1] << ' ' << m[5] << ' ' << m[9] << ' ' << m[13] << endl;
    cout << m[2] << ' ' << m[6] << ' ' << m[10] << ' ' << m[14] << endl;
    cout << m[3] << ' ' << m[7] << ' ' << m[11] << ' ' << m[15] << endl;
    return;
}


void setView(
        float fieldOfView = 60.0f, float aspectRatio = (GLfloat)WIDTH/(GLfloat)HEIGHT, 
        float orthoLeft = -10.0f, float orthoRight = 10.0f, float orthoBottom = -10.0f, float orthoTop = 10.0f,
        float nearField = 1.0f, float farField = 100.0f
    ) {

    view.fieldOfView = fieldOfView;
    view.aspectRatio = aspectRatio;

    view.nearField = nearField;
    view.farField = farField;

    view.orthoTop = orthoTop;
    view.orthoLeft = orthoLeft;
    view.orthoRight = orthoRight;
    view.orthoBottom = orthoBottom;

    return;
}

void project() {

    glMatrixMode(GL_PROJECTION);                        // Switch to Project Matrix Mode
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();                                   // Reset Projection Matrix to Identity for avoiding Artefacts
    if(projectionMode == 0) {
        // Field of View: 60 degrees (i.e., 30 to left and 30 to right), Aspect Ratio: width/height, Nearest plane: 1 units, Farthest plane: 100 units
        // gluPerspective( 60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
        gluPerspective( view.fieldOfView, view.aspectRatio, view.nearField, view.farField);
        printf("Perspective mode\n");
    }
    else {
        glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, view.nearField, view.farField);
        printf("Orthographic mode\n");
    }
    glMatrixMode(GL_MODELVIEW);                         // Switch back to Model View Matrix Mode

    return;
}

// Camera position and orientation :-
struct Camera {
    float xPos = 0.0, yPos = 0.0, zPos = -10.0;
};
struct Camera camera;

void setCamera(float xPos = 0.0f, float yPos = 0.0f, float zPos = -10.0f) {

    camera.xPos = xPos; 
    camera.yPos = yPos;
    camera.zPos = zPos;
    glLoadIdentity();
    glTranslatef( camera.xPos, camera.yPos, camera.zPos);

    glutPostRedisplay();
    return;
}

////////// Objects :-
struct Primitive {
    int shape;                      // 0 = Cube, 1 = Sphere, 2 = Torus, 3 = Cylinder
    int primitive_id = -1;
    float xPos, yPos, zPos, xRot, yRot, zRot;
};
struct Primitive primitive;

void setPrimitive(int shape = 0, float xPos = 0.0f, float yPos = 0.0f, float zPos = 0.0f, 
    float xRot = 0.0f, float yRot = 0.0f, float zRot = 0.0f) {
    
    primitive.shape = shape;

    primitive.xPos = xPos;
    primitive.yPos = yPos;
    primitive.zPos = zPos;

    primitive.xRot = xRot;
    primitive.yRot = yRot;
    primitive.zRot = zRot;

    return;
}

void renderCube(float size) 
{

    float x = (size/2.0) + primitive.xPos,  y = (size/2.0) + primitive.yPos, z = (size/2.0) + primitive.zPos;
    float xNeg = -1.0*(size/2.0) + primitive.xPos, yNeg = -1.0*(size/2.0) + primitive.yPos, zNeg = -1.0*(size/2.0) + primitive.zPos;

    //Constructing cube as a set of 6 faces. Each face is formed by a Triangle Strip made of 2 triangles :-

    //Back face (farthest from Camera)
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 1.0f, 0.0f, 1.0f );
        
        glVertex3f(    x, yNeg, zNeg );
        glVertex3f( xNeg, yNeg, zNeg );
        glVertex3f(    x,    y, zNeg );
        glVertex3f( xNeg,    y, zNeg );
    glEnd();

    //Top face
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 0.0f, 0.0f, 1.0f);

        glVertex3f( xNeg, y,    z);
        glVertex3f(    x, y,    z);
        glVertex3f( xNeg, y, zNeg);
        glVertex3f(    x, y, zNeg);
    glEnd();

    //Bottom face
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 1.0f, 1.0f, 1.0f);

        glVertex3f( xNeg, yNeg,    z);
        glVertex3f(    x, yNeg,    z);
        glVertex3f( xNeg, yNeg, zNeg);
        glVertex3f(    x, yNeg, zNeg);
    glEnd();

    //Right face
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 0.0f, 1.0f, 0.0f);

        glVertex3f( x, yNeg,    z);
        glVertex3f( x,    y,    z);
        glVertex3f( x, yNeg, zNeg);
        glVertex3f( x,    y, zNeg);
    glEnd();

    //Left face
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 0.0f, 1.0f, 1.0f);

        glVertex3f( xNeg, yNeg,    z);
        glVertex3f( xNeg,    y,    z);
        glVertex3f( xNeg, yNeg, zNeg);
        glVertex3f( xNeg,    y, zNeg);
    glEnd();

    //Front face (nearest to camera)
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 1.0f, 0.0f, 0.0f );
        
        glVertex3f( xNeg,    y, z);
        glVertex3f( xNeg, yNeg, z);
        glVertex3f(    x,    y, z);
        glVertex3f(    x, yNeg, z);
    glEnd();
    return;
}

void renderObject() {
    switch(primitive.shape) {
        case 0:
            renderCube(1);
            break;
        case 1:
        case 2:
        case 3:
        default:
            primitive.shape = 0;
            renderCube(1);
            break;
    }
    return;
}

void translate(float x, float y, float z) {
    
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    printModelViewMatrix();
        // GLfloat m[16];
        // glGetFloatv(GL_MODELVIEW_MATRIX, m);
        // cout << m[0] << ' ' << m[4] << ' ' << m[8] << ' ' << m[12] << endl;
        // cout << m[1] << ' ' << m[5] << ' ' << m[9] << ' ' << m[13] << endl;
        // cout << m[2] << ' ' << m[6] << ' ' << m[10] << ' ' << m[14] << endl;
        // cout << m[3] << ' ' << m[7] << ' ' << m[11] << ' ' << m[15] << endl;
            
        glTranslatef(x, y, z);
        renderObject();

        // glGetFloatv(GL_MODELVIEW_MATRIX, m);
        // cout << m[0] << ' ' << m[4] << ' ' << m[8] << ' ' << m[12] << endl;
        // cout << m[1] << ' ' << m[5] << ' ' << m[9] << ' ' << m[13] << endl;
        // cout << m[2] << ' ' << m[6] << ' ' << m[10] << ' ' << m[14] << endl;
        // cout << m[3] << ' ' << m[7] << ' ' << m[11] << ' ' << m[15] << endl;

    printModelViewMatrix();
    return;
}

float reduceAngle(float x) {
    while(x > 360.0f) {
        x -= 360.0f;
    }
    return x;
}

void rotate(float x, float y, float z) {

   
    //To handle ever increasing Angle value from going out of range, keep it under 360 degrees
    x = reduceAngle(x);
    y = reduceAngle(y);
    z = reduceAngle(z);
    
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

        // Apply the rotation
        glRotatef(x, 1.0f, 0.0f, 0.0f);  // Rotate around the X-axis
        glRotatef(y, 0.0f, 1.0f, 0.0f);  // Rotate around the Y-axis
        glRotatef(z, 0.0f, 0.0f, 1.0f);  // Rotate around the Z-axis

        // Render the object
        renderObject();

    // glPopMatrix();

    // glutPostRedisplay();
    return;
}

void scale(float x, float y, float z) {
    printModelViewMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(x,y,z);
    renderObject();
    printModelViewMatrix();
    return;
}
///////////

void display(void) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Clear the background of our window to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // Clear the colour buffer (more buffers later on)
    renderObject();                         // Render object based on the shape of primitive
    glFlush();                              // Flush the OpenGL buffers to the window
    glutSwapBuffers();

}


void reshape( int width, int height) {
    glViewport( 0, 0, (GLsizei)width, (GLsizei)height); // Update the viewport height according to width and height params given

    project();
    return;
}

void reset() {

    //Reset to Perspective mode
    // projectionMode = 0;
    glLoadIdentity();
    setCamera();

    setPrimitive();
    project();
    return;
}

void toggleViewMode() {
    if(projectionMode == 0) {
        projectionMode = 1;
    } else {
        projectionMode = 0;
    }
    project();
    return;
}

void keyPressed(unsigned char ch, int mouseX, int mouseY) {
    switch(ch) {
        case 'r':
            printf("Resetting everything\n");
            reset();
            break;

        case 'a':
            printf("Translating object leftwards\n"); 
            translate(-2.0, 0.0, 0.0);
            break;

        case 'd':
            printf("Translating object rightwards\n");
            translate(2.0, 0.0, 0.0);
            break;

        case 'w':
            printf("Translating object towards camera\n");
            translate(0.0, 0.0, 2.0);
            break;

        case 's':
            printf("Translating object away from camera\n");
            translate(0.0, 0.0, -2.0);
            break;

        case 'q':
            printf("Translating object upwards\n");
            translate(0.0, 2.0, 0.0);
            break;

        case 'e':
            printf("Translating object downwards\n");
            translate(0.0, -2.0, 0.0);
            break;

        case 'x':
            printf("Rotating object around X-axis anti-clockwise\n");
            rotate(20.0, 0.0, 0.0);
            break;
        
        case 'y':
            printf("Rotating object around Y-axis anti-clockwise\n");
            rotate(0.0, 20.0, 0.0);
            break;

        case 'z':
            printf("Rotating object around Z-axis anti-clockwise\n");
            rotate(0.0, 0.0, 20.0);
            break;

        case '8':
            printf("Scale up object along Y-axis\n");
            scale(1.0, 2.0, 1.0);
            break;

        case '6':
            printf("Scale up object along X-axis\n");
            scale(2.0, 1.0, 1.0);
            break;

        case '5':
            printf("Scale up object along Z-axis\n");
            scale(1.0, 1.0, 2.0);
            break;

        case 't':
            printf("Toggled to ");
            toggleViewMode();
            break;

        case 'k':
            printf("Translating camera backwards\n");
            setCamera(camera.xPos, camera.yPos, camera.zPos - 2.0);

            break;

        case 'i':
            printf("Translating camera forwards\n");
            setCamera(camera.xPos, camera.yPos, camera.zPos + 2.0);
            break;

        case '0':
            printf("Switching back to Cube\n");
            primitive.shape = 0;
            glutPostRedisplay();
            break;

        case '1':
            printf("Switching to Torus\n");
            break;

        case '2':
            printf("Switching to Sphere\n");
            break;
                
        case '3':
            printf("Switching to Cone\n");
            break;

        case 'c':
            printf("Switching to Cylinder\n");
            break;

        case '+':
            printf("Increase Field of View by 10\n");
            view.fieldOfView += 10;
            project();
            break;

        case '-':
            printf("Decrease Field of View by 10\n");
            view.fieldOfView -= 10;
            project();
            break;

        case 27:
            glutDestroyWindow ( win_id );
            exit(0);
            break;
        default:
            break;
    }

    return;
}

void specialKeyPressed(int ch, int mouseX, int mouseY) {
    switch(ch) {
        case GLUT_KEY_LEFT:
            printf("Translating camera leftwards\n");
            setCamera(camera.xPos + 2.0, camera.yPos, camera.zPos);
            break;
        case GLUT_KEY_RIGHT:
            printf("Translating camera rightwards\n");
            setCamera(camera.xPos - 2.0, camera.yPos, camera.zPos);
            break;

        case GLUT_KEY_UP:
            printf("Translating camera upwards\n");
            setCamera( camera.xPos, camera.yPos -2.0, camera.zPos);
            break;
        case GLUT_KEY_DOWN:
            printf("Translating camera downwards\n");
            setCamera(camera.xPos, camera.yPos + 2.0, camera.zPos);
            break;
    }
    return;
}

int main( int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);       // Set the width and height of the window
    glutInitWindowPosition(800, 100);        // Set the position of the window
    win_id = glutCreateWindow("Assignment 3");
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    glLoadIdentity();
    setCamera();
    
    glutDisplayFunc(display);               // Set the displaying function as "display"
    setView();                              // Specify the View parameters
    glutReshapeFunc(reshape);               // Set the reshaping function as "reshape"
    glutIdleFunc(display);                  // Set the displaying function when idle

    glutKeyboardFunc(keyPressed);           // Set the on-keypress function as "keyPressed"
    glutSpecialFunc(specialKeyPressed);     // Tell GLUT to use the method "keyPressed" for key presses
    // Set the depth function
    glDepthFunc(GL_LESS);
    glutMainLoop();                         // Enter GLUT's main loop
}