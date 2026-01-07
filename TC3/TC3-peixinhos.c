// gcc .\TC3.c -lfreeglut -lopengl32 -lglu32 -o main.exe
// .\main.exe

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// quantidade de peixinhos
#define NUM_FISH 200

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// velocidade maxima de cada peixinho
#define MAX_SPEED 0.3f

// distancia que um peixinho "enxerga" os outros
#define NEIGHBOR_RADIUS 20.0f

// distancia entre os peixinhos
#define SEPARATION_RADIUS 15.0f

float camAngleY = 0.0f; 
float camAngleX = 0.0f;
float camDist = 120.0f;

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float tailAngle;
    float tailSpeed;
} Fish;

Fish fish[NUM_FISH];

void initLight() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat light_pos[] = { 0.0f, 50.0f, 50.0f, 1.0f };
    GLfloat light_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_dif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);

    glClearColor(0.0, 0.5, 1.0, 1.0);
}

// Gera os peixinhos com posicoes e velocidades aleatorias
void initFish() {
    srand(time(NULL));
    for (int i = 0; i < NUM_FISH; i++) {
        fish[i].x = (rand() % 100) - 50;
        fish[i].y = (rand() % 100) - 50;
        fish[i].z = (rand() % 100) - 50;
        fish[i].vx = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
        fish[i].vy = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;
        fish[i].vz = ((float)rand() / RAND_MAX - 0.5f) * 0.2f;

        fish[i].tailAngle = 0.0f;
        fish[i].tailSpeed = ((float)rand() / RAND_MAX - 0.5f) * 5.0f;
    }
}

// Desenha o peixinho
void drawFish(Fish f) {
    float angleY = atan2(f.vx, f.vz) * 180.0 / M_PI;

    glPushMatrix();
        glTranslatef(f.x, f.y, f.z);
        glRotatef(angleY, 0, 1, 0);

        // Corpo
        glColor3f(1.0f, 0.5f, 0.0f);
        glutSolidSphere(3.0, 20, 20);

        // Cauda
        glPushMatrix();
            glRotatef(f.tailAngle, 0, 1, 0);
            glBegin(GL_TRIANGLES);
                glColor3f(0.5f, 0.2f, 0.2f);
                glVertex3f(0.0f, 0.0f, -3.0f);
                glVertex3f(0.0f, 1.5f, -6.0f);
                glVertex3f(0.0f, -1.5f, -6.0f);
            glEnd();
        glPopMatrix();

        // Olho direito
        glPushMatrix();
            glDisable(GL_LIGHTING);
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(0.8f, 0.8f, 2.5f);
            glutSolidSphere(0.4, 10, 10);
            glEnable(GL_LIGHTING);
        glPopMatrix();

        // Olho esquerdo
        glPushMatrix();
            glDisable(GL_LIGHTING);
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(-0.8f, 0.8f, 2.5f);
            glutSolidSphere(0.4, 10, 10);
            glEnable(GL_LIGHTING);
        glPopMatrix();

        float finAngle = f.tailAngle * 0.4f;
        // Nadadeira direita
        glPushMatrix();
            glColor3f(0.8f, 0.3f, 0.3f);
            glTranslatef(2.5f, -1.0f, 0.0f);
            glRotatef(-15.0f + finAngle/2, 0, 1, 0);
            glRotatef(-20.0f + finAngle, 1, 0, 0);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, -2.0f);
                glVertex3f(0.0f, -1.0f, -2.0f);
            glEnd();
        glPopMatrix();

        // Nadadeira esquerda
        glPushMatrix();
            glColor3f(0.8f, 0.3f, 0.3f);
            glTranslatef(-2.5f, -1.0f, 0.0f);
            glRotatef(15.0f - finAngle/2, 0, 1, 0);
            glRotatef(-20.0f - finAngle, 1, 0, 0);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, -2.0f);
                glVertex3f(0.0f, -1.0f, -2.0f);
            glEnd();
        glPopMatrix();

    glPopMatrix();
}

// Aplica o comportamento dos peixes baseado no algoritmo Boids:
// 1. Alinhamento: seguem a direcao media do grupo
// 2. Coesao: movem-se em direcao ao centro do grupo
// 3. Separacao: mantem distancia dos vizinhos
void applyBoidsBehavior(Fish *f) {
    float align[3] = {0}, coh[3] = {0}, sep[3] = {0};
    int count = 0;

    for (int j = 0; j < NUM_FISH; j++) {
        if (&fish[j] == f) continue;

        float dx = fish[j].x - f->x;
        float dy = fish[j].y - f->y;
        float dz = fish[j].z - f->z;
        float dist = sqrt(dx*dx + dy*dy + dz*dz);

        if (dist < NEIGHBOR_RADIUS && dist > 0) {
            align[0] += fish[j].vx;
            align[1] += fish[j].vy;
            align[2] += fish[j].vz;

            coh[0] += fish[j].x;
            coh[1] += fish[j].y;
            coh[2] += fish[j].z;

            if (dist < SEPARATION_RADIUS) {
                sep[0] -= dx / dist;
                sep[1] -= dy / dist;
                sep[2] -= dz / dist;
            }

            count++;
        }
    }

    if (count > 0) {
        align[0] /= count; align[1] /= count; align[2] /= count;
        coh[0] /= count; coh[1] /= count; coh[2] /= count;

        coh[0] = coh[0] - f->x;
        coh[1] = coh[1] - f->y;
        coh[2] = coh[2] - f->z;
    }

    f->vx += (align[0]*0.02f + coh[0]*0.01f + sep[0]*0.05f);
    f->vy += (align[1]*0.02f + coh[1]*0.01f + sep[1]*0.05f);
    f->vz += (align[2]*0.02f + coh[2]*0.01f + sep[2]*0.05f);

    float speed = sqrt(f->vx*f->vx + f->vy*f->vy + f->vz*f->vz);
    if (speed > MAX_SPEED) {
        f->vx = (f->vx / speed) * MAX_SPEED;
        f->vy = (f->vy / speed) * MAX_SPEED;
        f->vz = (f->vz / speed) * MAX_SPEED;
    }
}

// Atualiza posicao de cada peixinho
void updateFish() {
    for (int i = 0; i < NUM_FISH; i++) {
        applyBoidsBehavior(&fish[i]);
        fish[i].x += fish[i].vx;
        fish[i].y += fish[i].vy;
        fish[i].z += fish[i].vz;

        if (fish[i].x > 80 || fish[i].x < -80) fish[i].vx = -fish[i].vx;
        if (fish[i].y > 40 || fish[i].y < -40) fish[i].vy = -fish[i].vy;
        if (fish[i].z > 80 || fish[i].z < -80) fish[i].vz = -fish[i].vz;
    }

}

// Configura a camera e desenha todos os peixinhos
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = camDist * sin(camAngleY * M_PI / 180.0f) * cos(camAngleX * M_PI / 180.0f);
    float camY = camDist * sin(camAngleX * M_PI / 180.0f);
    float camZ = camDist * cos(camAngleY * M_PI / 180.0f) * cos(camAngleX * M_PI / 180.0f);

    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    for (int i = 0; i < NUM_FISH; i++)
        drawFish(fish[i]);

    glutSwapBuffers();
}


void idle() {
    updateFish();
    glutPostRedisplay();
}

// Mantem a proporcao e o campo de visao quando a janela muda de tamanho
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y) {
    const float angleSpeed = 2.0f;
    const float zoomSpeed = 5.0f;

    switch (key) {
        case GLUT_KEY_LEFT:
            camAngleY -= angleSpeed;
            break;
        case GLUT_KEY_RIGHT:
            camAngleY += angleSpeed;
            break;
        case GLUT_KEY_UP:
            camAngleX -= angleSpeed;
            if (camAngleX < -89.0f) camAngleX = -89.0f;
            break;
        case GLUT_KEY_DOWN:
            camAngleX += angleSpeed;
            if (camAngleX > 89.0f) camAngleX = 89.0f;
            break;
        case GLUT_KEY_PAGE_UP:
            camDist -= zoomSpeed;
            if (camDist < 30.0f) camDist = 30.0f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            camDist += zoomSpeed;
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 500);
    glutCreateWindow("Peixinhos");

    initLight();
    initFish();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

        glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;
}
