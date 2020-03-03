#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//FINAL VERSION//

using namespace std;

// Store the width and height of the window
int width = 640, height = 640;
float thetaInc = 0;
void appReshapeFunc(int w, int h);
void windowToScene(float& x, float& y);
bool click = false;
float X1;
float Y1;
float X2;
float Y2;

float red, green, blue = 0;
int counter = 3;
vector<bool> DRAW = {false};

bool bblack, bred, bgreen, bblue = false;
float mx = 0;
float my = 0;
float xP = 0;
float yP = 0;

bool erase = false;
bool drag = false;
bool draw = false;



//FAKE PSIZE NEED TO USE THE CORRECT WAY!
int pSize = 7;

struct ColorPallet{
    
    float red, green, blue, width, height, x, y, pSize, radius;
    string color;
    ColorPallet(){
        red = 0;
        green = 0;
        blue = 0;
        width = -0.7;
        height = 0;
        
    }
    
    ColorPallet(float x, float y, float pSize){
        this->x = x;
        this->y = y;
        this->pSize = pSize;
        this->radius = pSize/2;
    }
    
    ColorPallet(float red, float green, float blue, float x, float y, float width, float height, string color){
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
        this->color = color;
    }
    
    bool clickedOnPalletColor(float mx, float my){
        return (mx > x && mx < x + width && my < y && my > y - height);
    }
    
    void drawColorBox(){
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y - height );
        glVertex2f(x, y - height);
        glEnd();
    }
    
    void drawColorPSize(){
        glPointSize(pSize);
        glColor3f(0, 0, 0);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
    
    bool insideCircle(float mx, float my){
        return sqrt(pow(x - mx, 2) + pow(y - my, 2)) <= radius;
    }
    string getColor(){
        return color;
    }
    float getWidth(){
        return width;
    }
};
vector<ColorPallet> CPv;
vector<ColorPallet> CPv1;
ColorPallet CP;

struct Point{
    float x; float y; float red; float green; float blue; float pSize;
    // Color C;
    Point(){
        
    }
    //Set X coord & Y coord for Point Object
    Point(float x, float y, float pSize, float red, float green, float blue){
        this->x = x;
        this->y = y;
        this->pSize= pSize;
        this->red = red;
        this->green = green;
        this->blue = blue;
        
    }
    
    void setColor(float red, float green, float blue){
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    
    //    void setPSize(float pSize){
    //        this->pSize = pSize;
    //    }
    
    void drawPoint(){
        glColor3f(red, green, blue);
        glPointSize(pSize);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
};
vector<Point> Pv;

//struct Line{
//    float x1; float y1; float x2; float y2;
//
//    Line (float x1, float y1, float x2, float y2){
//        this->x1 = x1;
//        this->y1 = y1;
//        this->x2 = x2;
//        this->y2 = y2;
//    }
//
//    void drawLine(float x1, float y1, float x2, float y2 ){
//
//        glColor3f(1,1, 0);
//        glLineWidth(10);
//        glBegin(GL_LINES);
//        glVertex2f(x1, y1);
//        glVertex2f(x2, y2);
//        glEnd();
//    }
//};







//Color C;



//vector<Line> L;
//ColorPallet CP(0,0,0,-0.7,1);

//-------------------------------------------------------
// A function to draw the sceeen
//-------------------------------------------------------
Point P;
void appDrawScene() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    
    for (int i = 0; i < CPv1.size(); i++)
        CPv1[i].drawColorPSize();
    
    for (int i = 0; i < CPv.size(); i++)
        CPv[i].drawColorBox();
    
    
    
    
    //    for (int i = 0; i < P.size(); i++)
    //            L[i].drawLine(X1, Y1, X2, Y2);
    
    
    for (int i = 0; i < Pv.size(); i++)
        Pv[i].drawPoint();
    
    
    glEnd();
    glFlush();
    glutSwapBuffers();
}



//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments:
//    b    - mouse button that was clicked, left or right
//    s      - state, either mouse-up or mouse-down
//    x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
    // Convert from Window to Scene coordinates
    mx = (float)x;
    my = (float)y;
    
    windowToScene(mx, my);
    if (b == 0){
        if (s == 0) {
            drag = true;
            if (erase) {
                for (int i = 0; i <= Pv.size(); i++)
                    Pv.erase(Pv.begin(), Pv.begin() + i);
                erase = !erase;
            }
            
            if(CPv1[2].insideCircle(mx, my)){
                cout << "BIG BRUSH " << endl;
            }
            
            for (int i  = 0; i < CPv.size(); i++) {
                if(CPv[i].clickedOnPalletColor(mx, my))
                {
                    if (CPv[i].getColor() == "black")
                    { bblack = true; bred = false; bgreen = false; bblue = false;  break; }
                    if(CPv[i].getColor() == "red")
                    {  bblack = false; bred = true; bgreen = false; bblue = false;  break;}
                    if(CPv[i].getColor() == "blue")
                    {    bblack = false; bred = false; bgreen = false; bblue = true;  break;}
                    if(CPv[i].getColor() == "green")
                    {   bblack = false; bred = false; bgreen = true; bblue = false;  break;}
                    
                }
                
            }
        }
    }
    
    
    glutPostRedisplay();
    
}










//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments:
//    x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
    // Convert from Window to Scene coordinates
    mx = (float)x;
    my = (float)y;
    windowToScene(mx, my);
    
    if(drag){
        if(mx >  CP.getWidth()){
            Pv.push_back(Point(mx,my,pSize, red, green, blue));
            // L.push_back(Line(X1,Y1,X2,Y2));
            xP = mx;
            yP = my;
        }
        
        //        if(counter % 2 == 0){
        //            X1 = mx;
        //            Y1 = my;
        //        }
        //        if(counter % 2 != 0){
        //            X2 = mx;
        //            Y2 = my;
        //        }
        
    }
    
    
    // Again, we redraw the scene
    glutPostRedisplay();
}





void appKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
            erase = true;
            break;
        default:
            break;
        case 49:
            pSize = 7;
            break;
        case 50:
            pSize = 14;
            break;
        case 51:
            pSize = 21;
            break;
            
            // After all the state changes, redraw the scene
            glutPostRedisplay();
    }
}


void appSpecialKey(int key, int x, int y){
    glutPostRedisplay();
}

void appSpecialUp(int key, int x, int y){
    glutPostRedisplay();
}





void idle() {
    counter++;
    if (bblack) {
        red = 0;
        blue = 0;
        green = 0;
        
    }
    if (bred) {
        red = 1;
        blue = 0;
        green = 0;
        
    }
    if (bgreen) {
        red = 0;
        blue = 0;
        green = 1;
    }
    if(bblue){
        red = 0;
        blue = 1;
        green = 0;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    
    // Setup window position, size, and title
    glutInitWindowPosition(20, 60);
    glutInitWindowSize(width, height);
    glutCreateWindow("CSE165 OpenGL Demo");
    
    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    
    CPv1.push_back(ColorPallet(-0.8, -0.425, 10));
    CPv1.push_back(ColorPallet(-0.8, -0.5, 20));
    CPv1.push_back(ColorPallet(-0.8, -0.6, 30));
    CPv1.push_back(ColorPallet(-0.8, -0.735, 40));
    
    //ColorPallet(red, green, blue, x, y, width, height)
    CPv.push_back(ColorPallet(0,0,0,-0.95,0.95,0.3,0.3,"black"));
    CPv.push_back(ColorPallet(1,0,0,-0.95,0.65,0.3,0.3,"red"));
    CPv.push_back(ColorPallet(0,1,0,-0.95,0.35,0.3,0.3,"green"));
    CPv.push_back(ColorPallet(0,0,1,-0.95,0.05,0.3,0.3,"blue"));
    CPv.push_back(ColorPallet(0.2,0.2,0.2,-1,1,0.4,2, "Background Color"));
    
    
    
    // Set callback for drawing the scene
    glutDisplayFunc(appDrawScene);
    
    // Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);
    
    // Set callback to handle mouse clicks
    glutMouseFunc(appMouseFunc);
    
    // Set callback to handle mouse dragging
    glutMotionFunc(appMotionFunc);
    
    // Set callback to handle keyboad events
    glutKeyboardFunc(appKeyboardFunc);
    
    glutSpecialFunc(appSpecialKey);
    
    glutSpecialUpFunc(appSpecialUp);
    
    glutIdleFunc(idle);
    
    // Start the main loop
    glutMainLoop();
}













































// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments:
//    x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
    x = (2.0f*(x / float(width))) - 1.0f;
    y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments:
//    b    - mouse button that was clicked, left or right
//    s      - state, either mouse-up or mouse-down
//    x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
    // Window size has changed
    width = w;
    height = h;
    
    double scale, center;
    double winXmin, winXmax, winYmin, winYmax;
    
    // Define x-axis and y-axis range
    const double appXmin = -1.0;
    const double appXmax = 1.0;
    const double appYmin = -1.0;
    const double appYmax = 1.0;
    
    // Define that OpenGL should use the whole window for rendering
    glViewport(0, 0, w, h);
    
    // Set up the projection matrix using a orthographic projection that will
    // maintain the aspect ratio of the scene no matter the aspect ratio of
    // the window, and also set the min/max coordinates to be the disered ones
    w = (w == 0) ? 1 : w;
    h = (h == 0) ? 1 : h;
    
    if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
        scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
        center = (appXmax + appXmin) / 2;
        winXmin = center - (center - appXmin)*scale;
        winXmax = center + (appXmax - center)*scale;
        winYmin = appYmin;
        winYmax = appYmax;
    }
    else {
        scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
        center = (appYmax + appYmin) / 2;
        winYmin = center - (center - appYmin)*scale;
        winYmax = center + (appYmax - center)*scale;
        winXmin = appXmin;
        winXmax = appXmax;
    }
    
    // Now we use glOrtho to set up our viewing frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}





//struct Color{
//
//    float red; float green; float blue;
//    Color(){
//        red = 0;
//        green = 0;
//        blue = 0;
//    }
//
//    Color(float red, float green, float blue){
//        this->red = red;
//        this->green = green;
//        this->blue = blue;
//    }
//
//    void setColorRed(float red){
//        this->red = red;
//    }
//    void setColorGreen(float green){
//        this->green = green;
//    }
//    void setColorBlue(float blue){
//        this->blue = blue;
//    }
//
//    float getColorRed(){
//        return red;
//    }
//    float getColorGreen(){
//        return green;
//    }
//    float getColorBlue(){
//        return blue;
//    }
//};
