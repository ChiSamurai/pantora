#include "viewWindow.h"

viewWindow::viewWindow(QWidget *parent)
    : QGLViewer(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent )
{
    project = NULL;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0, 1.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0, 1.0);
    qtBackgroundColor.setNamedColor("#e4f2f8");

    cameraPos = QVector3D(0.0f, 4.0f, 10.0f);
    lookAtPoint = QVector3D(0.0, 0.0, 2.0);
    axisCoords = QVector3D(0.0, 0.0, 0.0);

}

void viewWindow::init(){
    qglClearColor(qtPurple); //Hintergrundfarbe setzen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);  //Tiefentest aktivieren
//    glEnable(GL_CULL_FACE); //Wenn Enabled werden Rückseiten von Polygonen (im Uhrzeigersinn) nicht gezeichnet

    glShadeModel(GL_SMOOTH);
    glEnable ( GL_COLOR_MATERIAL ) ;
    glEnable (GL_BLEND);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    camera()->setZClippingCoefficient(5.0);
    setSceneRadius(50.0);
    camera()->showEntireScene();

    fiatLux();
}

void viewWindow::draw(){

    glPushMatrix();
//    //X-Achse Invertieren?
    if(project->getInvertXAxis()){
        glScalef(-1.0f, 1.0f, 1.0f);
    }

    drawRotationCross(lookAtPoint);

    // *** Raster zeichnen
    drawRaster(QVector3D(project->getNullPoint().x() - 25, project->getNullPoint().y() - 0.0 , project->getNullPoint().z() - 25), 50.0f, 50.0f, 1.0f);

    // *** INFORMATIONEN AUSGEBEN
    drawInfoQuad();

    // *** Nullpunkt markieren
    drawMainAxis(QVector3D(project->getNullPoint().x(), project->getNullPoint().y(), project->getNullPoint().z()));

    if(project != NULL) project->GLdraw(this);
    glPopMatrix();


//    swapBuffers();
}


void viewWindow::drawInfoQuad(){
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    GLfloat viewportInfos[4];
    glGetFloatv(GL_VIEWPORT, viewportInfos);
    glColor3f(0.0f, 0.0f, 0.0f);
    QString width = "width: " + QString::number(viewportInfos[2]);
    QString height = "height: " + QString::number(viewportInfos[3]);
    QString s_cameraPos = "cameraPos.: x=" + QString::number(cameraPos.x()) + " y=" + QString::number(cameraPos.y()) + " z=" + QString::number(cameraPos.z());
    QString s_axisPos = "lookAtPoint.: x=" + QString::number(lookAtPoint.x()) + " y=" + QString::number(lookAtPoint.y()) + " z=" + QString::number(lookAtPoint.z());

    renderText(0.2f, 0.39f, -1.0, (width  + " " + height));
    renderText(0.2f, 0.37f, -1.0, s_cameraPos);

    renderText(0.2f, 0.33f, -1.0, s_axisPos);

    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void viewWindow::drawRotationCross(QVector3D middle){
    glPushMatrix();
    qglColor(QColor(0, 255, 0, 255));
//	 glLoadIdentity();
     glTranslatef(middle.x(), middle.y(), middle.z());

     glBegin(GL_LINES);
      glVertex3f(-0.2f, 0.0f, 0.0f);
      glVertex3f(0.2f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.2f, 0.0f);
      glVertex3f(0.0f, -0.2f, 0.0f);
      glVertex3f(0.0f, 0.0f, 0.2f);
      glVertex3f(0.0f, 0.0f, -0.2f);
     glEnd();
    glPopMatrix();
}

void viewWindow::fiatLux(){
    glEnable(GL_LIGHT0);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void viewWindow::drawMainAxis(QVector3D coords){
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(coords.x(), coords.y(), coords.z());
    glScalef(1.0, 1.0, 1.0);
    qglColor(Qt::red);

    glBegin(GL_LINES);
     glVertex3f(0.0, 0.0, 0.0);
     glVertex3f(1.0, 0.0, 0.0);

     glVertex3f(0.0, 0.0, 0.0);
     glVertex3f(0.0, 1.0, 0.0);

     glVertex3f(0.0, 0.0, 0.0);
     glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    renderText(0.0, 0.0, 0.0 , "(" + QString::number(coords.x()) + " | " + QString::number(coords.y()) + " | " + QString::number(coords.z()));
    renderText(1.0, 0.0, 0.0 , "x");
    renderText(0.0, 1.0, 0.0 , "y");
    renderText(0.0, 0.0, 1.0 , "z");

    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//void viewWindow::redraw(void){
//	updateGL();
////	this->draw();
//}

void viewWindow::setProject(Project *p){
    project = p;
    //Initial-Kameraposition setzen
    cameraPos.setX(project->getCamPos().x());
    cameraPos.setY(project->getCamPos().y());
    cameraPos.setZ(project->getCamPos().z());
    setCamPos(cameraPos);

    lookAtPoint.setX(project->getNullPoint().x());
    lookAtPoint.setY(project->getNullPoint().y());
    lookAtPoint.setZ(project->getNullPoint().z());
    setLookAtPoint(lookAtPoint);

//    updateGL();
}

void viewWindow::drawRaster(QVector3D start, float lengthx, float lengthy, float pace){
    glPushMatrix();
     glTranslatef(start.x(), start.y(), start.z());
     qglColor(Qt::red);
     glPointSize(2);
     glBegin(GL_POINTS);
     for(float i = 0; i <= lengthx; i += pace){
         for (float j = 0; j <= lengthy; j++){
//            glTranslatef(i * pace, j * pace, 0.0f);
            glVertex3f(i * pace, 0, j * pace);
         }
     }
     glEnd();
    glPopMatrix();
}

void viewWindow::setCamPos(QVector3D p){
    cameraPos = p;
    Vec cpos(cameraPos.x(), cameraPos.y(), cameraPos.z());
    camera()->setPosition(cpos);

    Vec lap(lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z());
    camera()->lookAt(lap);
    setSceneRadius(50.0);

    updateGL();
}

void viewWindow::setLookAtPoint(QVector3D p){
    lookAtPoint = p;
    Vec lap(lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z());
    camera()->lookAt(lap);
    camera()->setRevolveAroundPoint(lap);
    setSceneCenter(lap);

    setSceneRadius(50.0);

    updateGL();
}

