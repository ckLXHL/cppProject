#include <stdio.h>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
int main(int argc, char** argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
   glutCreateWindow("OpenGL Version");
   const GLubyte * name = glGetString(GL_VENDOR);
   const GLubyte * biaoshifu = glGetString(GL_RENDERER);
   const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
   const GLubyte * gluVersion = gluGetString(GLU_VERSION);
   printf("OpenGL实现厂商的名字：%s\n", name);
   printf("渲染器标识符：%s\n", biaoshifu);
   printf("OpenGL实现的版本号：%s\n",OpenGLVersion);
   printf("OGLU工具库版本：%s\n", gluVersion);
   return 0;
}
