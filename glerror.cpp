#include "glerror.h"

#ifdef WIN32
#  include <GL/glew.h>
#elif __APPLE__
#  include <OpenGL/gl3.h>
#else
#  include <GL/gl.h>
#endif

using namespace std;

void _check_gl_error(const char *file, int line) {
    QString prefix = "File: ";
    prefix += file;
    prefix += " :";
    prefix += file;
//    prefix.append(file);
//    prefix << ":" << line;
    switch (glGetError()) {
        {
        case GL_NO_ERROR:
            //qDebug() << prefix << tr("No error.");
            break;
        case GL_INVALID_ENUM:
            qDebug() << prefix << QObject::tr("Invalid enum.");
            break;
        case GL_INVALID_VALUE:
            qDebug() << prefix << QObject::tr("Invalid value.");
            break;
        case GL_INVALID_OPERATION:
            qDebug() << prefix << QObject::tr("Invalid operation.");
            break;
        case GL_STACK_OVERFLOW:
            qDebug() << prefix << QObject::tr("Stack overflow.");
            break;
        case GL_STACK_UNDERFLOW:
            qDebug() << prefix << QObject::tr("Stack underflow.");
            break;
        case GL_OUT_OF_MEMORY:
            qDebug() << prefix << QObject::tr("Out of memory.");
            break;
        default:
            qDebug() << prefix << QObject::tr("Unknown error.");
            break;
        }
    }
}
