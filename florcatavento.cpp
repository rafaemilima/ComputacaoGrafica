#include <GL/glut.h>
#include <cmath>

// COLORS

#define BROWN     0.8, 0.4, 0.3
#define PURPLE    0.6, 0.2, 0.5

typedef struct Vertex {
    GLfloat x, y;
} Vert;

// ALUNO: RAFAEL EMÍLIO LIMA ALVES
// INSTRUÇÃO:
// Para alterar a velocidade pressione "q" ou "e"
// Para girar horizontalmente pressione "a" ou "d"

float pi = 3.14, sen_60 = 0.86;
float velangl = pi / 4;

Vert flor[] = {
        {12.5, 25 * sen_60},
        {-12.5, 25 * sen_60},
        {25.0, 0.0},
        {12.5, 25 * (-sen_60)},
        {-25.0, 0.0},
        {-12.5, 25 * (-sen_60)}
};

Vert haste[] = {
        {-1.5, 0.0},
        {1.5, 0.0},
        {-1.5, -50.0},
        {1.5, -50.0}
};


void spinFlower(float angle)
{
    Vert aux;
    int i = 0;
    while (i < 6) {
        for (int j = i; j <= i+1; j++) {
            aux = flor[j];
            flor[j].x = (aux.x * std::cos(angle)) - (aux.y * std::sin(angle));
            flor[j].y = (aux.y * std::cos(angle)) + (aux.x * std::sin(angle));
        }
        i+=2;
    }

    glutPostRedisplay();
}

void renderFlower(){
    int i = 0;
    while (i < 6) {
        glBegin(GL_TRIANGLES);
        glColor3f(PURPLE);
        glVertex2f(0.0,0.0);

        int j = i;
        while (j < (i+2)) {
            GLfloat x = flor[j].x;
            GLfloat y = flor[j].y;
            glVertex2f(x,y);
            j++;
        }
        i += 2;

        glEnd();
    }
}

void renderStem(){
    for (int i=0; i<2; i++) {
        glBegin(GL_TRIANGLES);

        glColor3f(BROWN);
        int j = i;
        while (j < i+3) {
            GLfloat x = haste[j].x;
            GLfloat y = haste[j].y;
            glVertex2i(x, y);
            j++;
        }

        glEnd();
    }
}

void keyboard(unsigned char key, int x, int y){
    float change;
    if (key == 'a'){
        spinFlower(velangl);
    }
    else if (key == 'd'){
        spinFlower(-velangl);
    }
    else if (key == 'q'){
        change = velangl + (1.0f * pi / 16);
        velangl = change;
    }
    else if (key == 'e'){
        change = velangl - (1.0f * pi / 16);
        velangl = change;
    }

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    renderStem();
    renderFlower();
    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Flor de Abril em Catavento");
    glClearColor(0.5, 0.3, 0.2, 1.0);
    glOrtho(-100.0, 100.0, -100.0, 100.0, 1.0, -1.0);
    glutReshapeWindow(800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}