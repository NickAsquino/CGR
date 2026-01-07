#include <GL/glut.h>

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

void janela(float x, float y, float z) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(0.1f, 0.1f, 0.2f);
        glScalef(0.4f, 0.05f, 0.4f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, y+0.01f, z);
        glColor3f(0.1f, 0.1f, 0.2f);
        glScalef(0.15f, 0.01f, 0.25f);
        glutSolidCube(1.0);
    glPopMatrix();
}

void torre(GLUquadric* quad) {
    glColor3f(0.9f, 0.6f, 0.4f);
    gluCylinder(quad, 0.4, 0.4, 1.2, 30, 30);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.2f);
        glColor3f(0.7f, 0.3f, 0.2f);
        glutSolidCone(0.5, 0.8, 30, 30);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.35f, 0.4f);
        janela(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -0.35f, 0.7f);
        janela(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.35f, 0.0f, 0.5f);
        janela(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.35f, 0.0f, 0.9f);
        janela(0, 0, 0);
    glPopMatrix();
}


void muralha(float comprimento) {
    glColor3f(0.9f, 0.6f, 0.4f);
    glPushMatrix();
        glScalef(comprimento, 0.4f, 1.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    for (float i = -comprimento/2 + 0.4f; i <= comprimento/2 - 0.4f; i += 0.4f) {
        glPushMatrix();
            glTranslatef(i, 0.0f, 0.55f);
            glColor3f(0.8f, 0.5f, 0.3f);
            glScalef(0.2f, 0.2f, 0.2f);
            glutSolidCube(1.0);
        glPopMatrix();
    }
}

void torreCentral(GLUquadric* quad) {
    glColor3f(0.9f, 0.6f, 0.4f);
    glPushMatrix();
        glScalef(1.0f, 1.0f, 2.2f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.1f);
        glColor3f(0.7f, 0.3f, 0.2f);
        glutSolidCone(1.0, 0.9, 4, 4);
    glPopMatrix();

    janela(0.4f, 0.0f, 0.4f);
    janela(-0.4f, 0.0f, 0.8f);
    janela(0.0f, 0.4f, 0.6f);
}

void portao() {
    glPushMatrix();
        glColor3f(0.3f, 0.15f, 0.05f);
        glTranslatef(0.0f, -0.29f, 0.3f);
        glScalef(0.6f, 0.1f, 0.8f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, -0.02f, 0.8f);
        glColor3f(0.25f, 0.1f, 0.05f);
        glutSolidSphere(0.25, 20, 20);
    glPopMatrix();
}

void entrada() {
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.3f);
        glColor3f(0.85f, 0.55f, 0.35f);
        glScalef(1.5f, 0.6f, 1.1f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.3f);
        glColor3f(0.2f, 0.1f, 0.05f);
        glScalef(0.6f, 0.1f, 1.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
        glTranslatef(-0.7f, 0.0f, -0.25f);
        gluCylinder(quad, 0.25, 0.25, 1.1, 20, 20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.7f, 0.0f, -0.25f);
        gluCylinder(quad, 0.25, 0.25, 1.1, 20, 20);
    glPopMatrix();

    portao();
}

void patio() {
    glPushMatrix();
        glColor3f(0.2f, 0.8f, 0.4f);
        glTranslatef(-0.3f, 1.2f, -0.5f);
        glScalef(6.0f, 6.0f, 0.1f);
        glutSolidCube(1.0);
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(3.0, -8.0, 3.0,
            0.0, 0.0, 0.5,
            0.0, 0.0, 1.0);


    GLUquadric* quad = gluNewQuadric();

    float dist = 2.2f;

    // --- Torres ---
    glPushMatrix();
        glTranslatef(-dist, -dist, 0.0f);
        torre(quad);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(dist, -dist, 0.0f);
        torre(quad);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-dist, dist, 0.0f);
        torre(quad);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(dist, dist, 0.0f);
        torre(quad);
    glPopMatrix();

    // --- Muralhas ---
    glPushMatrix();
        glTranslatef(0.0f, -dist, 0.5f);
        muralha(4.5f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, dist, 0.5f);
        muralha(4.5f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-dist, 0.0f, 0.5f);
        glRotatef(90, 0, 0, 1);
        muralha(4.5f);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(dist, 0.0f, 0.5f);
        glRotatef(90, 0, 0, 1);
        muralha(4.5f);
    glPopMatrix();

    // --- Torre central ---
    glPushMatrix();
        torreCentral(quad);
    glPopMatrix();

    // --- Entrada ---
    glPushMatrix();
        glTranslatef(0.0f, -dist-0.3f, 0.3f);
        entrada();
    glPopMatrix();

    patio();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 30.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Castelo 3D - Com Entrada");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
