#include <GL/glut.h>

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    GLfloat light_pos[] = {2.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLUquadric* quad = gluNewQuadric();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Base
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, -0.68f, 0.0f);
        gluSphere(quad, 0.5, 30, 30);
    glPopMatrix();

    // Meio
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.0f, 0.0f);
        gluSphere(quad, 0.35, 30, 30);
    glPopMatrix();

    // Cabeça
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.0f, 0.55f, 0.0f);
        gluSphere(quad, 0.25, 30, 30);
    glPopMatrix();

    // Nariz
    glPushMatrix();
        glColor3f(1.0f, 0.2f, 0.0f);
        glTranslatef(0.0f, 0.28f, 1.5f);
        glRotatef(10, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.03f, 0.3f, 20, 20);
    glPopMatrix();

    // Olho esquerdo
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(-0.1f, 0.6f, 0.22f);
        glutSolidSphere(0.03f, 20, 20);
    glPopMatrix();

    // Olho direito
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.1f, 0.6f, 0.22f);
        glutSolidSphere(0.03f, 20, 20);
    glPopMatrix();

    // Botoes
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.08f, 0.35f);
        glutSolidSphere(0.04f, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -0.11f, 0.35f);
        glutSolidSphere(0.04f, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -0.35f, 0.6f);
        glutSolidSphere(0.04f, 20, 20);
    glPopMatrix();

    // Cartola
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.75f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);

        // Aba da cartola
        gluDisk(quad, 0.0f, 0.35f, 30, 1);

        // Corpo da cartola
        gluCylinder(quad, 0.2f, 0.2f, 0.4f, 30, 30);

        // Tampa da cartola
        glTranslatef(0.0f, 0.0f, 0.4f);
        gluDisk(quad, 0.0f, 0.2f, 30, 1);
    glPopMatrix();

    // Braço esquerdo
    glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        glTranslatef(-0.7f, 0.1f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        gluCylinder(quad, 0.02f, 0.015f, 0.5f, 20, 20);

        // Primeira ramificação
        glPushMatrix();
            glTranslatef(0.3f, 0.0f, 0.1f);
            glRotatef(220, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, 0.01f, 0.008f, 0.18f, 30, 30);
        glPopMatrix();

        // Segunda ramificação
        glPushMatrix();
            glTranslatef(0.2f, 0.0f, 0.1f);
            glRotatef(140, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, 0.01f, 0.008f, 0.2f, 30, 30);
        glPopMatrix();
    glPopMatrix();

    // Braço direito
    glPushMatrix();
        glColor3f(0.55f, 0.27f, 0.07f);
        glTranslatef(0.7f, 0.1f, 0.0f);
        glRotatef(-90, 0.0f, 1.0f, 0.0f);
        gluCylinder(quad, 0.02f, 0.015f, 0.5f, 20, 20);
        
        // Primeira ramificação
        glPushMatrix();
            glTranslatef(-0.3f, 0.0f, 0.1f);
            glRotatef(220, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, 0.01f, 0.008f, 0.2f, 30, 30);
        glPopMatrix();

        // Segunda ramificação
        glPushMatrix();
            glTranslatef(-0.2f, 0.0f, 0.1f);
            glRotatef(140, 1.0f, 0.0f, 0.0f);
            gluCylinder(quad, 0.01f, 0.008f, 0.12f, 30, 30);
        glPopMatrix();
    glPopMatrix();

    // Boca
    glColor3f(0.0f, 0.0f, 0.0f);
    float bx = 0.0f;
    float by = 0.41f;
    float bz = 0.26f;

    for (int i = -2; i <= 2; i++) {
        glPushMatrix();
            float x = bx + i * 0.03f;                     
            float y = by + 0.005f * (i*i);
            glTranslatef(x, y, bz);
            glutSolidSphere(0.01f, 20, 20);
        glPopMatrix();
    }

    // Cachecol
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.29f, 0.12f); // posiciona entre o meio e a cabeça
        glRotatef(-90, 1.0f, 0.0f, 0.0f); // deita o cilindro na horizontal
        gluCylinder(quad, 0.13f, 0.12f, 0.05f, 30, 20); // cilindro largo e curto
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(-0.18f, 0.06f, 0.3f); 
        glRotatef(-90, 1.0f, 0.0f, 0.0f); 
        glRotatef(20, 0.0f, 1.0f, 0.0f); 
        gluCylinder(quad, 0.03f, 0.025f, 0.25f, 20, 20);
    glPopMatrix();
    /*
    // Ponta do cachecol
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(0.1f, 0.35f, 0.0f); 
        glRotatef(-90, 1.0f, 0.0f, 0.0f); 
        glRotatef(-20, 0.0f, 1.0f, 0.0f); 
        gluCylinder(quad, 0.03f, 0.025f, 0.25f, 20, 20);
    glPopMatrix();*/

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 10.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Esfera");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}
