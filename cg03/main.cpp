#include<stdio.h>
#include<string>
#include<GL/glew.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

int projectionMode = 0;                     // 0 = Perspective, 1 = Orthographic

void display(void) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Clear the background of our window to black
    glClear(GL_COLOR_BUFFER_BIT);           // Clear the colour buffer (more buffers later on)
    glLoadIdentity();                       // Load the Identity Matrix to reset our drawing locations
    glFlush();                              // Flush the OpenGL buffers to the window
}


void reshape( int width, int height) {

    glViewport( 0, 0, (GLsizei)width, (GLsizei)height); // Update the viewport height according to width and height params given
    glMatrixMode(GL_PROJECTION);                        // Switch to Project Matrix Mode
    glLoadIdentity();                                   // Reset Projection Matrix to Identity for avoiding Artefacts

    // Field of View: 60 degrees (i.e., 30 to left and 30 to right), Aspect Ratio: width/height, Nearest plane: 1 units, Farthest plane: 100 units
    gluPerspective( 60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);                         // Switch back to Model View Matrix Mode
}

void keyPressed(unsigned char ch, int mouseX, int mouseY) {
    switch(ch) {
        case 'r':
            printf("Resetting everything\n");
            break;

        case 'a':
            printf("Translating leftwards\n"); 
            break;

        case 'd':
            printf("Translating rightwards\n");
            break;

        case 'w':
            printf("Translating away from camera\n");
            break;

        case 's':
            printf("Translating towards camera\n");
            break;

        case 'q':
            printf("Translating upwards\n");
            break;

        case 'e':
            printf("Translating downwards\n");
            break;

        case 'x':
            printf("Rotating around X-axis anti-clockwise\n");
            break;
        
        case 'y':
            printf("Rotating around Y-axis anti-clockwise\n");
            break;

        case 'z':
            printf("Rotating around Z-axis anti-clockwise\n");
            break;

        case '8':
            printf("Scale up along Y-axis\n");
            break;

        case '6':
            printf("Scale up along X-axis\n");
            break;

        case '5':
            printf("Scale up along Z-axis\n");
            break;

        case 't':
            printf("Toggling from %d", projectionMode);

            if(projectionMode == 0) {
                projectionMode = 1;
            } else {
                projectionMode = 0;
            }
            printf(" to %d\n", projectionMode);
            break;

        case 'j':
            printf("Translate camera leftwards\n");
            break;

        case 'l':
            printf("Translating camera rightwards\n");
            break;

        case 'k':
            printf("Translating camera backwards\n");
            break;

        case 'i':
            printf("Translating camera forwards\n");
            break;

        case 'u':
            printf("Translating camera downwards\n");
            break;

        case 'o':
            printf("Translating camera upwards\n");
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
}

int main( int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);       // Set the width and height of the window
    glutInitWindowPosition(100, 100);   // Set the position of the window
    glutCreateWindow("Assignment 3");

    glutDisplayFunc(display);           // Set the displaying function as "display"
    glutReshapeFunc(reshape);           // Set the reshaping function as "reshape"
    glutIdleFunc(display);              // Set the displaying function when idle
    glutKeyboardFunc(keyPressed);       // Set the on-keypress function as "keyPressed"

    glutMainLoop();                     // Enter GLUT's main loop
}  