#include<stdio.h>
#include<string>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

#define WIDTH 800
#define HEIGHT 600


int projectionMode = 0;                     // 0 = Perspective, 1 = Orthographic
struct viewDetails {
    float fieldOfView, aspectRatio, nearField, farField,
        orthoLeft, orthoRight, orthoBottom, orthoTop;
};

struct viewDetails view;

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
    float xPos, yPos, zPos,
        xRot, yRot, zRot;
};
struct Camera camera;

void setCamera(float xPos = 0.0f, float yPos = 0.0f, float zPos = -5.0f,
    float xRot = 0.0f, float yRot = 0.0f, float zRot = 0.0f) {

    camera.xPos = xPos; 
    camera.yPos = yPos;
    camera.zPos = zPos;
    camera.xRot = xRot;
    camera.yRot = yRot;
    camera.zRot = zRot;

    glTranslatef( camera.xPos, camera.yPos, camera.zPos);
    glRotatef( camera.xRot, 1.0f, 0.0f, 0.0f);
    glRotatef( camera.yRot, 0.0f, 1.0f, 0.0f);
    glRotatef( camera.zRot, 0.0f, 0.0f, 1.0f);

    return;
}

////////// Objects :-
struct Primitive {
    int shape;                      // 0 = Cube, 1 = Sphere, 2 = Torus, 3 = Cylinder
    float xPos, yPos, zPos, xRot, yRot, zRot;
};
struct Primitive primitive;

void setPrimitive(int shape, float xPos = 0.0f, float yPos = 0.0f, float zPos = 0.0f) {
    
    primitive.shape = shape;

    primitive.xPos = 0.0f;
    primitive.yPos = 0.0f;
    primitive.zPos = 0.0f;

    primitive.xRot = 0.0f;
    primitive.yRot = 0.0f;
    primitive.zRot = 0.0f;

    return;
}

void renderCube( float size, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f) {

    float x = (size/2.0) + centerX,  y = (size/2.0) + centerY, z = (size/2.0) + centerZ;
    float xNeg = -1.0*(size/2.0) + centerX, yNeg = -1.0*(size/2.0) + centerY, zNeg = -1.0*(size/2.0) + centerZ;

    //Constructing cube as a set of 6 faces. Each face is formed by a Triangle Strip made of 2 triangles :-

    //Back face (farthest from Camera)
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f( 1.0f, 0.0f, 1.0f );
        
        glVertex3f(    x, yNeg, zNeg );
        glVertex3f( xNeg, yNeg, zNeg );
        glVertex3f(    x,    y, zNeg );
        glVertex3f( xNeg,    y, zNeg );
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
            renderCube(2, 0.0, 0.0, 0.0);
            break;
        case 1:
        case 2:
        case 3:
        default:
            primitive.shape = 0;
            renderCube(2, 0.0, 0.0, 0);
            break;
    }
    return;
}

void translate(int xPos, int yPos, int zPos) {
    return renderCube(2, xPos, yPos, zPos);
}
///////////

void display(void) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Clear the background of our window to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // Clear the colour buffer (more buffers later on)

    glLoadIdentity();                       // Load the Identity Matrix to reset our drawing locations
    setCamera();                            // Specify Camera placement and orientation
    renderObject();                         // Render object based on the shape of primitive
    glFlush();                              // Flush the OpenGL buffers to the window

}


void reshape( int width, int height) {
    glViewport( 0, 0, (GLsizei)width, (GLsizei)height); // Update the viewport height according to width and height params given

    project();
    return;
}

void reset() {

    //Reset to Perspective mode
    // projectionMode = 0;

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
            break;

        case 'd':
            printf("Translating object rightwards\n");
            translate(5.0, 0.0, 0.0);
            break;

        case 'w':
            printf("Translating object towards camera\n");
            break;

        case 's':
            printf("Translating object away from camera\n");
            break;

        case 'q':
            printf("Translating object upwards\n");
            break;

        case 'e':
            printf("Translating object downwards\n");
            break;

        case 'x':
            printf("Rotating object around X-axis anti-clockwise\n");
            break;
        
        case 'y':
            printf("Rotating object around Y-axis anti-clockwise\n");
            break;

        case 'z':
            printf("Rotating object around Z-axis anti-clockwise\n");
            break;

        case '8':
            printf("Scale up object along Y-axis\n");
            break;

        case '6':
            printf("Scale up object along X-axis\n");
            break;

        case '5':
            printf("Scale up object along Z-axis\n");
            break;

        case 't':
            printf("Toggled to ");
            toggleViewMode();
            break;

        case 'k':
            printf("Translating camera backwards\n");
            break;

        case 'i':
            printf("Translating camera forwards\n");
            break;

        case '0':
            printf("Switching back to Cube\n");
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
            printf("Increase Field of View\n");
            break;

        case '-':
            printf("Decrease Field of View\n");
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
            break;
        case GLUT_KEY_RIGHT:
            printf("Translating camera rightwards\n");
            break;

        case GLUT_KEY_UP:
            printf("Translating camera upwards\n");
            break;
        case GLUT_KEY_DOWN:
            printf("Translating camera downwards\n");
            break;
    }
    return;
}

int main( int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);       // Set the width and height of the window
    glutInitWindowPosition(100, 100);        // Set the position of the window
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    setView();                              // Specify the View parameters

    glutCreateWindow("Assignment 3");
    
    glutDisplayFunc(display);               // Set the displaying function as "display"
    glutReshapeFunc(reshape);               // Set the reshaping function as "reshape"
    glutIdleFunc(display);                  // Set the displaying function when idle
    glutKeyboardFunc(keyPressed);           // Set the on-keypress function as "keyPressed"
    glutSpecialFunc(specialKeyPressed);     // Tell GLUT to use the method "keyPressed" for key presses
    // Set the depth function
    glDepthFunc(GL_LESS);
    glutMainLoop();                         // Enter GLUT's main loop
}  