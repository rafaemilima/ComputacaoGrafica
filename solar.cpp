#include <GL/freeglut.h>

// COLORS
#define RED       0.9, 0.1, 0.0
#define GREEN     0.2, 1.0, 0.0
#define BLUE      0.0, 0.2, 1.0
#define YELLOW    1.0, 0.8, 0.0
#define BROWN     0.8, 0.4, 0.3
#define ORANGE    0.8, 0.5, 0.1
#define ROSE      0.7, 0.1, 0.6
#define PURPLE    0.6, 0.2, 0.5


// ALUNO: RAFAEL EMÍLIO LIMA ALVES
// INSTRUÇÃO: Para rotacionar os planetas (movimento de translação): pressione a tecla yetas) - "y"

int day = 0, year = 0;
double lX = 0, lY = 0, lZ = 0, angY = 0;


void reshape(int w, int h){
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, (double) w / h, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void updateSchedule(int value){
    glutTimerFunc(10, updateSchedule, 1);
    year++;
    day++;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 27:
            exit(0);
        case 'y':
            glutTimerFunc(10, updateSchedule, 1);
            break;
        default:
            break;
    }
}

void generatePlanet(float angle, float angle2, float yr, float yr2, float xt, float yt, float zt, float radius, float stacks) {
    glRotatef(angle * year, 0, yr, 0);
    glTranslatef(xt, yt, zt);
    glRotatef(angle2 * day, 0, yr2, 0);
    glutSolidSphere(radius, 100, stacks); // Generate planet
    glPopMatrix();
}

void displayPlanets(){
    // PLANET ARGO II
    glPushMatrix();
    glColor3f(RED);
    generatePlanet(2, 2, -1, 1, -1, 0.05, 0, 0.1, 80);

    // PLANET LAPLACE
    glPushMatrix();
    glColor3f(ORANGE);
    generatePlanet(3, 2.5, 1, 1, 1.1, 0.4, 1, 0.1, 70);

    // PLANET JARVAN IV
    glPushMatrix();
    glColor3f(ROSE);
    generatePlanet(4, 3, -1, 1, -2, -0.4, 0, 0.2, 90);

    // PLANET TARS
    glPushMatrix();
    glColor3f(BLUE);
    generatePlanet(-0.5, -1, -1, 1, -2.5, 0.4, -1, 0.15, 50);
}

void generateMoon(float radius, float angle, float xr, float yr, float zr, float xt, float yt){
    glRotatef(angle *day, xr, yr, zr);
    glTranslatef(xt, yt, 0);
    glutSolidSphere(radius, 100, 100);
    glPopMatrix();
}

void displayMoonPlanet(){
    // PLANET PANDORA
    glPushMatrix();
    glColor3f(GREEN);
    glRotatef(year, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glPushMatrix();
    glRotatef(day, 0, 1, 0);
    glutSolidSphere(0.2, 100, 100);
    glPopMatrix();

    // MOON CIPRIAN
    glPushMatrix();
    glColor3f(PURPLE);
    generateMoon(0.05, 1.5, 0, 1, 0, 0.45, 0.1);

    // MOON COOPER III
    glPushMatrix();
    glColor3f(BROWN);
    generateMoon(0.07, 1.75, 1, 1.2, 0, 0.35, 0);

    glPopMatrix();
}

void displaySun(){
    // SUN CERBERUS
    glPushMatrix();
    glColor3f(YELLOW);
    glRotatef(year, 1, 0, 0);
    glRotatef(day, 0, 0, 1);
    glutSolidSphere(0.6, 100, 100); // Generate sun
    glPopMatrix();
}


void displaySolarSystem(){
    displaySun();
    displayMoonPlanet();
    displayPlanets();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glPushMatrix();

    glColor3f(255, 255, 255);
    glRotated(angY, 0, 1, 0);
    glTranslated(lX, lY, lZ);
    glutSolidSphere(0.05, 100, 100);

    glPopMatrix();
    displaySolarSystem();
    glPopMatrix();
    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("SOLAR SYSTEM");
    glutInitWindowPosition(100, 100);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}