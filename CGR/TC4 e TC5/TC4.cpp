// g++ TC4.cpp -std=c++17 -I"C:/Users/Nicole/vcpkg/installed/x64-mingw-dynamic/include" -L"C:/Users/Nicole/vcpkg/installed/x64-mingw-dynamic/lib" -lassimp -lfreeglut -lopengl32 -lglu32 -o TC4.exe
// start .\TC4.exe

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glut.h>
#include <cstdio>

Assimp::Importer importer;
const aiScene* scene = nullptr;

float rotX = 0.0f, rotY = 0.0f;
int lastX = 0, lastY = 0;
bool mouseDown = false;
float zoom = 5.0f;
float posX = 0.0f, posY = 0.0f;

void loadModel(const char* path) {
    scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenNormals);

    if (!scene || !scene->mRootNode) {
        printf("Erro ao carregar modelo: %s\n", importer.GetErrorString());
        exit(1);
    }
}

void drawModel() {
    if (!scene) return;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        if (!mesh) continue;

        glBegin(GL_TRIANGLES);
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            const aiFace& face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; k++) {
                unsigned int index = face.mIndices[k];
                if (index >= mesh->mNumVertices) continue;

                if (mesh->HasNormals())
                    glNormal3fv(&mesh->mNormals[index].x);
                glVertex3fv(&mesh->mVertices[index].x);
            }
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, zoom,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glTranslatef(posX, posY - 1.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);

    //glColor3f(0.8f, 0.8f, 0.8f);
    glColor3f(0.3f, 0.9f, 0.3f);
    //glColor3f(0.0f, 1.0f, 0.0f);
    drawModel();

    glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        mouseDown = (state == GLUT_DOWN);
        lastX = x;
        lastY = y;
    }

    if (button == 3) zoom -= 0.5f;
    if (button == 4) zoom += 0.5f;

    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 50.0f) zoom = 50.0f;

    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:    posY -= 0.1f; break;
        case GLUT_KEY_DOWN:  posY += 0.1f; break;
        case GLUT_KEY_LEFT:  posX += 0.1f; break;
        case GLUT_KEY_RIGHT: posX -= 0.1f; break;
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        rotY += (x - lastX) * 0.5f;
        rotX += (y - lastY) * 0.5f;
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Caneca gato");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    loadModel("caneca.obj");

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glutMainLoop();
    return 0;
}
