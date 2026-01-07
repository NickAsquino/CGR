#include <GL/glut.h>

static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //glClearColor(0.7f, 0.9f, 1.0f, 1.0f);

    GLfloat light_pos[] = {3.0f, 6.0f, 6.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void ChangeSize(int w, int h) {
    GLfloat fAspect;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, fAspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.2f, 0.6f, 0.8f, 1.0f);
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) xRot -= 5.0f;
    if (key == GLUT_KEY_DOWN) xRot += 5.0f;
    if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
    if (key == GLUT_KEY_RIGHT) yRot += 5.0f;
    glutPostRedisplay();
}

void DrawRobot() {
    GLUquadric *q = gluNewQuadric();

    // Tronco
    glColor3f(0.6f, 0.6f, 0.6f);
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(q, 0.6, 0.6, 1.0, 20, 20);
    glPopMatrix();

    // Cintura
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.3f, 0.0f);
        glutSolidCube(0.6);
    glPopMatrix();

    // Cabeça
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, 1.2f, 0.0f);
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    // Orelhas
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
        glTranslatef(-0.13f, 1.19f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 0.45f, 0.0f);
            glVertex3f(-0.15f, 0.0f, 0.1f);
            glVertex3f(0.15f, 0.0f, 0.1f);
        glEnd();
        glTranslatef(0.28f, -0.01f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0f, 0.46f, 0.0f);
            glVertex3f(-0.15f, 0.0f, 0.1f);
            glVertex3f(0.15f, 0.0f, 0.1f);
        glEnd();
    glPopMatrix();

    // Ombros
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
        glTranslatef(0.7f, 0.7f, 0.0f);
        glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-0.7f, 0.7f, 0.0f);
        glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    // Bracos
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(1.25f, 0.7f, 0.0f);
        glScalef(1.5f, 0.5f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.25f, 0.7f, 0.0f);
        glScalef(1.5f, 0.5f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    // Pernas
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
        glTranslatef(-0.3f, -1.15f, 0.0f);
        glScalef(0.5f, 2.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.3f, -1.15f, 0.0f);
        glScalef(0.5f, 2.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    // Pés
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(-0.3f, -1.7f, 0.3f);
        glScalef(0.7f, 0.3f, 1.0f);
        glutSolidCube(0.5);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.3f, -1.7f, 0.3f);
        glScalef(0.7f, 0.3f, 1.0f);
        glutSolidCube(0.5);
    glPopMatrix();

    // Maos
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(1.8f, 0.7f, 0.0f);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.8f, 0.7f, 0.0f);
        glutSolidSphere(0.15, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(q);
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    DrawRobot();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Robo 3D");

    init();

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
    return 0;
}
