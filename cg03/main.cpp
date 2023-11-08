#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

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


int main( int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowSize(800, 800);       // Set the width and height of the window

    glutInitWindowPosition(100, 100);   // Set the position of the window

    glutCreateWindow("An OpenGL Window");

    glutDisplayFunc(display);           // Set the displaying function as "display"
    glutReshapeFunc(reshape);           // Set the reshaping function as "reshape"
    glutIdleFunc(display);              // Set the displaying function when idle

    glutMainLoop();                     // Enter GLUT's main loop
}  