#!/usr/bin/env python2.7
from OpenGL.GL import *
from OpenGL.GLUT import *
def display():
    glClear(GL_COLOR_BUFFER_BIT)
    glBegin(GL_POLYGON)
    glVertex2f(-0.5, -0.5)
    glVertex2f(-0.5, 0.5)
    glVertex2f(0.5, 0.5)
    glVertex2f(0.5, -0.5)
    glEnd()
    glFlush()
glutInit();
#glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
glutCreateWindow("Xcode Glut Demo");
glutDisplayFunc(display);
glutMainLoop();

