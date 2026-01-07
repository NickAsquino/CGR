// gcc .\TC2.c -lfreeglut -lopengl32 -lglu32 -o main.exe
// .\main.exe

#include <GL/glut.h>

typedef struct {
    float x, y;
    float velocidade;
} Particula;


#define NUM_PARTICULAS 2500
Particula chuva[NUM_PARTICULAS];

void initParticulas() {
    for (int i = 0; i < NUM_PARTICULAS; i++) {
        chuva[i].x = (rand() % 200 - 100) / 10.0f;
        chuva[i].y = (rand() % 100) / 10.0f + 5.0f;
        chuva[i].velocidade = 0.0005;
    }
}

void atualizaChuva() {
    for (int i = 0; i < NUM_PARTICULAS; i++) {
        chuva[i].y -= chuva[i].velocidade;
        if (chuva[i].y < -5) {
            chuva[i].y = 5.0f;
            chuva[i].x = (rand() % 200 - 100) / 10.0f;
        }
    }
    glutPostRedisplay();
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.5f, 0.5f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < NUM_PARTICULAS; i++) {
        glVertex2f(chuva[i].x, chuva[i].y);
    }
    glEnd();

    glColor3f(0.36f, 0.25f, 0.20f);
    glPushMatrix();
        glTranslatef(-1.0f, -1.2f, 0.0f);
        glScalef(10.0f, 2.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.36f, 0.25f, 0.20f);
    glPushMatrix();
        glTranslatef(-1.0f, 1.3f, 0.0f);
        glScalef(10.0f, 2.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.36f, 0.25f, 0.20f);
    glPushMatrix();
        glTranslatef(-0.9f, -1.15f, 0.0f);
        glScalef(0.5f, 10.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.36f, 0.25f, 0.20f);
    glPushMatrix();
        glTranslatef(0.9f, -1.15f, 0.0f);
        glScalef(0.5f, 10.0f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    // mato
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glTranslatef(-0.7f, -0.65f, 0.0f);
        glScalef(0.3f, 0.2f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, -0.63f, 0.0f);
        glScalef(0.2f, 0.3f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glTranslatef(0.58f, -0.65f, 0.0f);
        glScalef(0.3f, 0.2f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glTranslatef(0.2f, -0.68f, 0.0f);
        glScalef(0.2f, 0.1f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glTranslatef(-0.5f, -0.68f, 0.0f);
        glScalef(0.2f, 0.1f, 0.5f);
        glutSolidCube(0.5);
    glPopMatrix();
    

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chuva de Particulas");

    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glPointSize(4.0); // tamanho dos pingos
    gluOrtho2D(-10, 10, -5, 10);

    initParticulas();
    glutDisplayFunc(RenderScene);
    glutIdleFunc(atualizaChuva);

    glutMainLoop();
    return 0;
}
