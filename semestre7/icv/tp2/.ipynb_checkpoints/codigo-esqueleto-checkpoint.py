#!/usr/bin/python3

import cv2

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

from PIL import Image

from objloader import *
 
def initOpenGL(dimensions):

    (width, height) = dimensions
    
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)

    glEnable(GL_DEPTH_TEST)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
 
    fovy = 45
    aspect = (width)/(height)
    gluPerspective(fovy, aspect, 0.1, 100.0)
        
def object3D(obj):

    # translada o objeto para ficar 10 unidades distante da camera (para podermos ver o objeto)
    glTranslate(0,0,-10)

    # move o model em y para centralizar ele
    glTranslate(0,-2,0)
    # rotaciona o modelo para podermos ve-lo de frente
    #glRotate(90,1,0,0)
    glRotate(180,0,1,0)
    # renderiza o modelo do Pikachu
    glCallList(obj.gl_list)

    # renderiza um cubo
    # glutWireCube(2.0)

    
def displayCallback():

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    # carregar o modelo 3D do Pikachu
    obj = OBJ("Pikachu.obj", swapyz=True)

    # habilita o uso de texturas (o Pikachu tem textura)
    glEnable(GL_TEXTURE_2D)

    object3D(obj) 
        
    glutSwapBuffers()    
    

def idleCallback():

    glutPostRedisplay()
    
    
if __name__ == '__main__':
    
    dimensions = (640, 480)
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE)
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION)
    glutInitWindowSize(*dimensions)
    window = glutCreateWindow(b'Realidade Aumentada [codigo esqueleto]')
    
    initOpenGL(dimensions)
    
    glutDisplayFunc(displayCallback)
    glutIdleFunc(idleCallback)
    
    glutMainLoop()