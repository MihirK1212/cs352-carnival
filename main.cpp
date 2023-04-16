#include "libs.h"
#include "index.h"

Human human;
Rides rides;
Objects objects;

GLboolean fanSwitch = false, door1 = false, orbiterFlag = false, pirateBoatFlag = false, pirateBoatCheck = false, cmOrbiterFlag = false, skyDropFlag = false, upFlag = true, downFlag1 = true, downFlag2 = false, downFlag3 = false, day = true;
static double eyeX = -10, eyeY = 5.0, eyeZ = 100, refX = 0, refY = 0, refZ = 0;

double mouse_x = -1, mouse_y = -1;
double mouse_x_prev = -1, mouse_y_prev = -1;

static double windowHeight = 1000, windowWidth = 1000;
float intensity = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    glEnable(GL_LIGHTING);

    glPushMatrix();
    sky(eyeX + (0.05 * refX), eyeY + (0.05 * refY), eyeZ + (0.05 * refZ), 250, 250, 250);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    spotLight1();
    spotLight2();
    spotLight3();
    spotLight4();
    ground();
    objects.walls();
    objects.flags();
    objects.drawPool();

    glPushMatrix();
    human.drawHuman();
    glPopMatrix();

    // for (float i = -70; i <= -10; i += 20)
    // {
    //     glPushMatrix();
    //     glTranslatef(i, -20, 55);
    //     objects.bench1();
    //     glPopMatrix();
    // }

    // for (float i = -60; i <= -20; i += 20)
    // {
    //     glPushMatrix();
    //     glTranslatef(i, -20, 55);
    //     objects.bench2();
    //     glPopMatrix();
    // }

    // for (float i = 30; i <= 100; i += 20)
    // {
    //     glPushMatrix();
    //     glTranslatef(i, -20, 55);
    //     objects.bench1();
    //     glPopMatrix();
    // }

    // for (float i = 40; i <= 90; i += 20)
    // {
    //     glPushMatrix();
    //     glTranslatef(i, -20, 55);
    //     objects.bench2();
    //     glPopMatrix();
    // }

    glPushMatrix();
    glTranslatef(-25, 0, 0);
    objects.streetLight1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 0, 0);
    objects.streetLight2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 0, 30);
    objects.streetLight3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 0, 30);
    objects.streetLight4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 10);
    objects.cafeteria();
    glPopMatrix();

    /*****/
    glPushMatrix();
    glTranslatef(-70, -5, 40);
    glTranslatef(0, 8, 0);
    glScalef(1.5, 1.5, 1.5);
    rides.rollerCoaster();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, 15, 40);
    glScalef(1.5, 1.5, 1.5);
    rides.rideFence();
    glPopMatrix();
    /*****/

    /****/
    glPushMatrix();
    glTranslatef(-70, 0, -30);
    glTranslatef(0, 10, 0);
    glScalef(1.5, 1.5, 1.5);
    rides.orbiter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, 15, -30);
    glScalef(1.5, 1.5, 1.5);
    rides.rideFence();
    glPopMatrix();
    /***/

    // glPushMatrix();
    // glTranslatef(65, 0, -30);
    // rides.ferrisWheel();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-50, 0, -30);
    // rides.complexOrbiter();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-50, 0, 10);
    // rides.pirateBoat();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-20, -20, -40);
    // rides.skyDrop();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-30, 0, 40);
    // objects.balloonCart();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(-60, 0, 40);
    // objects.balloonCart();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(45, 0, 48);
    // objects.balloonCart();
    // glPopMatrix();

    // glPushMatrix();
    // glTranslatef(80, 0, 48);
    // objects.balloonCart();
    // glPopMatrix();

    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}

float computePinchDistance(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}


void mouseMove(int x, int y)
{
    mouse_x = (double)x;
    mouse_y = (double)y;

    if (mouse_x_prev == -1)
        mouse_x_prev = mouse_x;
    if (mouse_y_prev == -1)
        mouse_y_prev = mouse_y;


    double delta_x = mouse_x - mouse_x_prev;
    double delta_y = mouse_y - mouse_y_prev;

    eyeX += (-delta_x);
    eyeY += (-delta_y);

    mouse_x_prev = mouse_x;
    mouse_y_prev = mouse_y;
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            mouse_x_prev = -1;
            mouse_y_prev = -1;
        }
    }
    if(button == 3 || button == 4) 
    {
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events

        if(button == 3) {
            //scroll up, i.e move fingers down hence zoom out
            eyeZ += 1;
        }
        else {
            //scroll in, i.e move fingers up hence zoom in
            eyeZ -= 1;
        }

        // printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
    }
}

void lighting(float X, float Y, float Z)
{
    GLfloat position[] = {X, Y, Z, 0.0}; // using directional source of light
    GLfloat noAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat whiteDiffuse[] = {intensity, intensity, intensity, 1.0f};

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, noAmbient);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a': // move ref point left along X axis
        refX -= 1.0;
        break;
    case 'd': // move eye point right along X axis
        refX += 1.0;
        break;
    case 'r':
        eyeX = -10;
        eyeY = 5.0;
        eyeZ = 100;
        refX = 0;
        refY = 0;
        refZ = 0;
        break;
    case '1':
        if (orbiterFlag == false)
        {
            orbiterFlag = true;
            break;
        }
        else if (orbiterFlag == true)
        {
            orbiterFlag = false;
            break;
        }
    case '2':
        if (fanSwitch == false)
        {
            fanSwitch = true;
            break;
        }
        else
        {
            fanSwitch = false;
            break;
        }
    case '3':
        if (skyDropFlag == false)
        {
            skyDropFlag = true;
            break;
        }
        else if (skyDropFlag == true)
        {
            skyDropFlag = false;
            break;
        }
    case '4':
        if (cmOrbiterFlag == false)
        {
            cmOrbiterFlag = true;
            break;
        }
        else if (cmOrbiterFlag == true)
        {
            cmOrbiterFlag = false;
            break;
        }
    case '5':
        if (pirateBoatFlag == false)
        {
            pirateBoatFlag = true;
            break;
        }
        else if (pirateBoatFlag == true)
        {
            pirateBoatFlag = false;
            break;
        }
    case '6':
        if (objects.switchOne == false)
        {
            objects.switchOne = true;
            glEnable(GL_LIGHT1);
            break;
        }
        else if (objects.switchOne == true)
        {
            objects.switchOne = false;
            glDisable(GL_LIGHT1);
            break;
        }
    case '7':
        if (objects.switchTwo == false)
        {
            objects.switchTwo = true;
            glEnable(GL_LIGHT2);
            break;
        }
        else if (objects.switchTwo == true)
        {
            objects.switchTwo = false;
            glDisable(GL_LIGHT2);
            break;
        }
    case '8':
        if (objects.switchThree == false)
        {
            objects.switchThree = true;
            glEnable(GL_LIGHT3);
            break;
        }
        else if (objects.switchThree == true)
        {
            objects.switchThree = false;
            glDisable(GL_LIGHT3);
            break;
        }
    case '9':
        if (objects.switchFour == false)
        {
            objects.switchFour = true;
            glEnable(GL_LIGHT4);
            break;
        }
        else if (objects.switchFour == true)
        {
            objects.switchFour = false;
            glDisable(GL_LIGHT4);
            break;
        }
    case 'z':
        if (objects.controlPointsFlag == false)
        {
            objects.controlPointsFlag = true;
            break;
        }
        else if (objects.controlPointsFlag == true)
        {
            objects.controlPointsFlag = false;
            break;
        }
    case 'g':
        if (door1 == false)
        {
            door1 = true;
            break;
        }
        else
        {
            door1 = false;
            break;
        }

    case '0':
        if (day == false)
        {
            day = true;
            // glEnable(GL_LIGHT0);
            lighting(100, 100, 100);
            break;
        }
        else if (day == true)
        {
            day = false;
            glDisable(GL_LIGHT0);
            break;
        }
        // increase intensity
    case 'i':
        if (intensity < 1.0)
        {
            intensity += 0.1;
            break;
        }
        else
        {
            intensity = 1.0;
            break;
        }
        // decrease intensity
    case 'k':
        if (intensity > 0.0)
        {
            intensity -= 0.1;
            break;
        }
        else
        {
            intensity = 0.0;
            break;
        }
    case 27:
        exit(1);
    }

    glutPostRedisplay();
}

void specialKeyboardFunc(int key, int x, int y)
{
    human.move(key, x, y);
    glutPostRedisplay();
}

void animate()
{
    rides.animateRides(skyDropFlag, upFlag, downFlag1, downFlag2, downFlag3, cmOrbiterFlag, pirateBoatFlag, pirateBoatCheck, fanSwitch, orbiterFlag, door1);
    objects.animateFlag();
    glutPostRedisplay();
}

void fullScreen(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Amusement Park");
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    light();

    cout << "To move Eye point:"
         << "\n";
    cout << "w: up"
         << "\n";
    cout << "s: down"
         << "\n";
    cout << "a: left"
         << "\n";
    cout << "d: right"
         << "\n";
    cout << "i: zoom in"
         << "\n";
    cout << "o: zoom out"
         << "\n";
    cout << "      "
         << "\n";

    cout << "To move Camera point:"
         << "\n";
    cout << "j: up"
         << "\n";
    cout << "n: down"
         << "\n";
    cout << "b: left"
         << "\n";
    cout << "m: right"
         << "\n";
    cout << "l: move nearer"
         << "\n";
    cout << "k: move far"
         << "\n";
    cout << "      "
         << "\n";

    cout << "Press q to move to default position"
         << "\n";
    cout << "      "
         << "\n";

    cout << "To control Rides: "
         << "\n";
    cout << "1: Orbiter"
         << "\n";
    cout << "2: Ferris Wheel"
         << "\n";
    cout << "3: Sky Drop"
         << "\n";
    cout << "4: Complex Orbiter"
         << "\n";
    cout << "5: Pirate Boat"
         << "\n";
    cout << "      "
         << "\n";

    cout << "To control lights: "
         << "\n";
    cout << "6: Spotlight 1"
         << "\n";
    cout << "7: Spotlight 2"
         << "\n";
    cout << "8: Spotlight 3"
         << "\n";
    cout << "9: Spotlight 4"
         << "\n";
    cout << "      "
         << "\n";

    cout << "Other controls: "
         << "\n";
    cout << "0: Day/Night"
         << "\n";
    cout << "Z: To show control points"
         << "\n";

    LoadTexture("sgi images/whiteground.sgi", 2);
    LoadTexture("sgi images/whiteground.sgi", 3);
    LoadTexture("sgi images/pirate-copy.sgi", 4);
    // LoadTexture("sgi images/red-metal.sgi", 5);
    LoadTexture("sgi images/blue_gradient.sgi", 5);
    LoadTexture("sgi images/baskinrobbinslogo.sgi", 6);
    // LoadTexture("sgi images/pizzahut.sgi", 7);
    LoadTexture("sgi images/iitindore.sgi", 7);
    LoadTexture("sgi images/dunkindonuts.sgi", 8);

    // sky
    // LoadTexture("sgi images/front.sgi", 9);
    // LoadTexture("sgi images/left.sgi", 12);
    // LoadTexture("sgi images/right.sgi", 11);
    // LoadTexture("sgi images/back.sgi", 10);
    // LoadTexture("sgi images/up.sgi", 28);
    // LoadTexture("sgi images/nightsky.sgi", 29);

    // sky
    LoadTexture("sgi images/scorchsky.sgi", 9);
    LoadTexture("sgi images/scorchsky.sgi", 12);
    LoadTexture("sgi images/scorchsky.sgi", 11);
    LoadTexture("sgi images/scorchsky.sgi", 10);
    LoadTexture("sgi images/scorchsky.sgi", 28);
    LoadTexture("sgi images/scorchsky.sgi", 29);

    LoadTexture("sgi images/skydrop.sgi", 13);
    LoadTexture("sgi images/skydroplogo.sgi", 14);

    // LoadTexture("sgi images/grass.sgi", 15);
    // LoadTexture("sgi images/whiteground.sgi", 15);
    // LoadTexture("sgi images/sand.sgi", 15);
    // LoadTexture("sgi images/grass_alt.sgi", 15);
    LoadTexture("sgi images/sand_alt.sgi", 15);

    // LoadTexture("sgi images/blackred.sgi", 16);
    LoadTexture("sgi images/blue_gradient.sgi", 16);
    LoadTexture("sgi images/pinkblue.sgi", 17);
    LoadTexture("sgi images/baskin-robin-ad.sgi", 18);
    LoadTexture("sgi images/de5b9e.sgi", 19);
    LoadTexture("sgi images/pinkorange.sgi", 20);

    LoadTexture("sgi images/ff6d0d.sgi", 21);

    LoadTexture("sgi images/dd.sgi", 22);

    // LoadTexture("sgi images/pizzahutad.sgi", 23);
    LoadTexture("sgi images/abhinandan.sgi", 23);
    LoadTexture("sgi images/bush.sgi", 24);
    LoadTexture("sgi images/bushflower.sgi", 25);
    LoadTexture("sgi images/brickwall.sgi", 26);
    LoadTexture("sgi images/redwhite.sgi", 27);
    LoadTexture("sgi images/treebark.sgi", 30);
    LoadTexture("sgi images/bush.sgi", 31);

    // LoadTexture("sgi images/purplewall.sgi", 32);
    LoadTexture("sgi images/iitindore.sgi", 32);
    LoadTexture("sgi images/tiles.sgi", 33);
    LoadTexture("sgi images/water.sgi", 34);

    glutReshapeFunc(fullScreen);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(specialKeyboardFunc);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseButton);
    glutMainLoop();

    return 0;
}
