//
//  main.cpp
//  final
//
//  Created by Xuhao Zhou on 11/25/15.
//  Copyright © 2015 Xuhao Zhou. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include "glew.h"
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "glut.h"
#endif

#include "heli.550"
#include "california.h"
#include "Policecar.h"

#define BLADE_RADIUS     1.0
#define BLADE_WIDTH		 0.4
#define MS_PER_CYCLE    500

#define MS_PER_CYCLE_FLOWER    5000

#define  NUMCURVES      12
#define  NUMPOINTS      100

#define M_Pi    3.14159265

// title of these windows:

const char *WINDOWTITLE = { "CS550 -- Need for Speed -- Xuhao Zhou" };
const char *GLUITITLE   = { "Window" };


// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };


// the escape key:

#define ESCAPE		0x1b


// initial window size:

const int INIT_WINDOW_SIZE = { 600 };


// size of the box:

const float BOXSIZE = { 2.f };



// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };


// minimum allowable scale factor:

const float MINSCALE = { 0.05f };

// helicopter scale

const float HSCALE = { 1.0f };

// active mouse buttons (or them together):

const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };




// which projection:

enum Projections
{
    ORTHO,
    PERSP
};


// which button:

enum ButtonVals
{
    RESET,
    QUIT
};


// window background color (rgba):

const GLfloat BACKCOLOR[ ] = { 0., 0., 0., 1. };


// line width for the axes:

const GLfloat AXES_WIDTH   = { 3. };


// the color numbers:
// this order must match the radio button order

enum Colors
{
    RED,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    MAGENTA,
    WHITE,
    BLACK
};

char * ColorNames[ ] =
{
    "Red",
    "Yellow",
    "Green",
    "Cyan",
    "Blue",
    "Magenta",
    "White",
    "Black"
};


// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] =
{
    { 1., 0., 0. },		// red
    { 1., 1., 0. },		// yellow
    { 0., 1., 0. },		// green
    { 0., 1., 1. },		// cyan
    { 0., 0., 1. },		// blue
    { 1., 0., 1. },		// magenta
    { 1., 1., 1. },		// white
    { 0., 0., 0. },		// black
};


// non-constant global variables:

int		ActiveButton;			// current button that is down
GLuint	AxesList;				// list to hold the axes
int		AxesOn;					// != 0 means to draw the axes
int		DebugOn;				// != 0 means to print debugging info
int		DepthCueOn;				// != 0 means to use intensity depth cueing
GLuint	MyHeliList;				// object display list
GLuint  RivalHeliList;
GLuint	BladeList;
GLuint  WireList;
GLuint  StarList;
GLuint  BoxList;
GLuint  FlashList;
GLuint  RoadList;
GLuint  DestinationList;
GLuint  BladesAnimateList;
GLuint  PoliceCarList;
GLuint  MyVehicleTurn1List;
GLuint  MyVehicleTurn2List;
GLuint  MyVehicleTurn3List;
GLuint  RivalTurn1List;
GLuint  RivalTurn2List;
GLuint  RivalTurn3List;
GLuint  WindMillList;
int		MainWindow;				// window id for main graphics window
float	Scale;					// scaling factor
int		WhichColor;				// index into Colors[ ]
int		WhichProjection;		// ORTHO or PERSP
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot, Zrot;		// rotation angles in degrees
int     ViewOn;
GLfloat roofspeed = 0.;
GLfloat tailspeed = 0.;
bool	Frozen = false;
float   move = 0.;
float   rivalmove=0.;
int     MyVehicleOn;
int     RivalOn;
int     Result = 0;
bool    Light0On;
bool    Light1On;
bool    Light2On;
float   Time;
float   Time2;
bool    MyRightWay;
bool    RivalRightWay;
float   ani;
bool    DifficultyOn;
bool    BeginOn;

// function prototypes:

void	Animate( );
void	Display( );
void	DoMyVehicleMenu( int );
void	DoRivalMenu( int );
void	DoAxesMenu( int );
void	DoViewMenu( int );
void	DoColorMenu( int );
void	DoDebugMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
void    DoDifficultyMenu(int);
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );

void	Axes( float );
void	HsvRgb( float[3], float [3] );
void    DrawPoliceCar();
void    DrawCalifornia();

// main program:



int
main( int argc, char *argv[ ] )
{
    // turn on the glut package:
    // (do this before checking argc and argv since it might
    // pull some command line arguments out)
    
    glutInit( &argc, argv );
    
    
    // setup all the graphics stuff:
    
    InitGraphics( );
    
    
    // create the display structures that will not change:
    
    InitLists( );
    
    
    // init all the global variables used by Display( ):
    // this will also post a redisplay
    
    Reset( );
    
    
    // setup all the user interface stuff:
    
    InitMenus( );
    
    
    // draw the scene once and wait for some interaction:
    // (this will never return)
    
    glutSetWindow( MainWindow );
    glutMainLoop( );
    
    
    // this is here to make the compiler happy:
    
    return 0;
}


// this is where one would put code that is to be called
// everytime the glut main loop has nothing to do
//
// this is typically where animation parameters are set
//
// do not call Display( ) from here -- let glutMainLoop( ) do it

void
Animate( )
{
    // put animation stuff in here -- change some global variables
    // for Display( ) to find:
    
    // animation of blades
    roofspeed = roofspeed + 7.0;
    tailspeed = tailspeed + 21.0;
    
    // animation of rival vehicle
    if (rivalmove<200&&BeginOn==true)
    {
        if (DifficultyOn==false)
            rivalmove = rivalmove + 0.35;
        else
            rivalmove = rivalmove + 0.45;
    }
    // force a call to Display( ) next time it is convenient:
    
    // animation of flash light
    int ms = glutGet( GLUT_ELAPSED_TIME );
    ms %= MS_PER_CYCLE;
    Time = (float)ms / (float)( MS_PER_CYCLE - 1 );
    
    int ms2 = glutGet( GLUT_ELAPSED_TIME );
    ms2 %= MS_PER_CYCLE_FLOWER;
    Time2 = (float)ms2 / (float)( MS_PER_CYCLE_FLOWER - 1 );

    ani= 45*sinf(2*M_PI*Time2);
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

// Curve Begin   **********************************************************
struct Point
{
    float x0, y0, z0;       // initial coordinates
    float x,  y,  z;        // animated coordinates
};

struct Curve
{
    float r, g, b;
    Point p0, p1, p2, p3;
};

Curve curve;
Curve Curves[NUMCURVES];		// if you are creating a pattern of curves
Curve Stem;                     // if you are not
Curve curves[NUMCURVES];
float hsv[3],rgb[3];

void BezierCurve(Point p0, Point p1, Point p2, Point p3, float r, float g, float b);
void RotateX( Point *p, float deg, float xc, float yc, float zc );
void RotateY( Point *p, float deg, float xc, float yc, float zc );
void RotateZ( Point *p, float deg, float xc, float yc, float zc );

void
RotateX( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;
    
    float xp = x;
    float yp = y*cos(rad) - z*sin(rad);
    float zp = y*sin(rad) + z*cos(rad);
    
    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

void
RotateY( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;
    
    float xp =  x*cos(rad) + z*sin(rad);
    float yp =  y;
    float zp = -x*sin(rad) + z*cos(rad);
    
    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

void
RotateZ( Point *p, float deg, float xc, float yc, float zc )
{
    float rad = deg * (M_PI/180.f);         // radians
    float x = p->x0 - xc;
    float y = p->y0 - yc;
    float z = p->z0 - zc;
    
    float xp = x*cos(rad) - y*sin(rad);
    float yp = x*sin(rad) + y*cos(rad);
    float zp = z;
    
    p->x = xp + xc;
    p->y = yp + yc;
    p->z = zp + zc;
}

void BezierCurve(Point p0, Point p1, Point p2, Point p3, float r, float g, float b)
{
    
    glLineWidth( 3. );
    glColor3f( r, g, b );
    glBegin( GL_LINE_STRIP );
    for( int it = 0; it <= NUMPOINTS; it++ )
    {
        float t = (float)it / (float)NUMPOINTS;
        float omt = 1.f - t;
        float x = omt*omt*omt*p0.x + 3.f*t*omt*omt*p1.x + 3.f*t*t*omt*p2.x + t*t*t*p3.x;
        float y = omt*omt*omt*p0.y + 3.f*t*omt*omt*p1.y + 3.f*t*t*omt*p2.y + t*t*t*p3.y;
        float z = omt*omt*omt*p0.z + 3.f*t*omt*omt*p1.z + 3.f*t*t*omt*p2.z + t*t*t*p3.z;
        glVertex3f( x, y, z );
    }
    glEnd( );
    glLineWidth( 1. );
}

// Curve End   *********************************************************************


//************************   Lighting Function Begin   *****************************
float White[ ] = { 1.,1.,1.,1. };

// utility to create an array from 3 separate values:

float *
Array3( float a, float b, float c ) {
    static float array[4];
    array[0] = a;
    array[1] = b;
    array[2] = c;
    array[3] = 1.;
    return array;
}

// utility to create an array from a multiplier and an array:

float *
MulArray3( float factor, float array0[3] ) {
    
    static float array[4];
    array[0] = factor * array0[0];
    array[1] = factor * array0[1];
    array[2] = factor * array0[2];
    array[3] = 1.;
    return array;
}

void
SetMaterial( float r, float g, float b, float shininess )
{
    glMaterialfv( GL_BACK, GL_EMISSION, Array3( 0., 0., 0. ) );
    glMaterialfv( GL_BACK, GL_AMBIENT, MulArray3( .4f, White ) );
    glMaterialfv( GL_BACK, GL_DIFFUSE, MulArray3( 1., White ) );
    glMaterialfv( GL_BACK, GL_SPECULAR, Array3( 0., 0., 0. ) );
    glMaterialf ( GL_BACK, GL_SHININESS, 2.f );
    
    glMaterialfv( GL_FRONT, GL_EMISSION, Array3( 0., 0., 0. ) );
    glMaterialfv( GL_FRONT, GL_AMBIENT, Array3( r, g, b ) );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, Array3( r, g, b ) );
    glMaterialfv( GL_FRONT, GL_SPECULAR, MulArray3( .8f, White ) );
    glMaterialf ( GL_FRONT, GL_SHININESS, shininess );
}

void
SetPointLight( int ilight, float x, float y, float z, float r, float g, float b )
{
    glLightfv( ilight, GL_POSITION, Array3( x, y, z ) );
    glLightfv( ilight, GL_AMBIENT, Array3( 0., 0., 0. ) );
    glLightfv( ilight, GL_DIFFUSE, Array3( r, g, b ) );
    glLightfv( ilight, GL_SPECULAR, Array3( r, g, b ) );
    glLightf ( ilight, GL_CONSTANT_ATTENUATION, 1. );
    glLightf ( ilight, GL_LINEAR_ATTENUATION, 0. );
    glLightf ( ilight, GL_QUADRATIC_ATTENUATION, 0. );
    glEnable( ilight );
}
//************************   Lighting Function End   *****************************

void
DrawPoliceCar()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, PolicecarVerts);
    glNormalPointer(GL_FLOAT, 0, PolicecarNormals);
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0,1.6,0);
    glScalef(11, 11, 11);
    SetMaterial( .0, 0.0, 0.3, 50 );
    glDrawArrays(GL_TRIANGLES, 0, PolicecarNumVerts);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void
DrawCalifornia()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, californiaVerts);
    glNormalPointer(GL_FLOAT, 0, californiaNormals);
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0,1.5,0);
    glRotatef(180, 0, 1, 0);
    glRotatef(90, -1, 0, 0);
    glScalef(11, 11, 11);
    SetMaterial( 0.8, 0.2, 0.2, 10 );
    glDrawArrays(GL_TRIANGLES, 0, californiaNumVerts);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

// draw the complete scene:

void
Display( )
{
    if( DebugOn != 0 )
    {
        fprintf( stderr, "Display\n" );
    }
    
    
    // set which window we want to do the graphics into:
    
    glutSetWindow( MainWindow );
    
    
    // erase the background:
    
    glDrawBuffer( GL_BACK );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );
    
    
    // specify shading to be flat:
    
    glShadeModel( GL_FLAT );
    
    
    // set the viewport to a square centered in the window:
    
    GLsizei vx = glutGet( GLUT_WINDOW_WIDTH );
    GLsizei vy = glutGet( GLUT_WINDOW_HEIGHT );
    GLsizei v = vx < vy ? vx : vy;			// minimum dimension
    GLint xl = ( vx - v ) / 2;
    GLint yb = ( vy - v ) / 2;
    glViewport( xl, yb,  v, v );
    
    
    // set the viewing volume:
    // remember that the Z clipping  values are actually
    // given as DISTANCES IN FRONT OF THE EYE
    // USE gluOrtho2D( ) IF YOU ARE DOING 2D !
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    if( WhichProjection == ORTHO )
        glOrtho( -3., 3.,     -3., 3.,     0.1, 1000. );
    else
        gluPerspective( 90., 1.,	0.1, 1000. );
    
    
    // place the objects into the scene:
    
    glMatrixMode( GL_MODELVIEW );
    
    // change view:
    
    // outside view
    if (ViewOn==0)
    {
        glLoadIdentity( );
        
        // set the eye position, look-at position, and up-vector:
        gluLookAt( 2.2, 13.0, 20.1-move,     3., 6., 0.-move,     0., 1., 0. );
    }
    

    // inside view
    if( ViewOn == 1)
    {
        glLoadIdentity( );
        gluLookAt( 6.0, 8.8, -4.9-move,     6.7, 8.8, -10.5-move,     0., 1., 0. );
    }

    
    // rear view
    if (ViewOn==2)
    {
        glLoadIdentity( );
        gluLookAt( -2., 12., -17.-move,     -2., 7., -10.-move,     0., 1., 0. );
    }
    
    // rotate the scene:
    
    glRotatef( (GLfloat)Xrot, 1., 0., 0. );
    glRotatef( (GLfloat)Yrot, 0., 1., 0. );
    glRotatef( (GLfloat)Zrot, 0., 0., 1. );
    
    // uniformly scale the scene:
    
    if( Scale < MINSCALE )
        Scale = MINSCALE;
    glScalef( (GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale );
    
    
    // possibly draw the axes:
    
    if( AxesOn != 0 )
    {
        glColor3fv( &Colors[WhichColor][0] );
        glCallList( AxesList );
    }
    

    
    // since we are using glScalef( ), be sure normals get unitized:
    
    glEnable( GL_NORMALIZE );
    
    // draw the current object:
    
    // enable LIGHTING
    glEnable( GL_LIGHTING );
    
    if( Light0On )
        glEnable( GL_LIGHT0 );
    else
        glDisable( GL_LIGHT0 );

    // Magenta Torus
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(6.5,9.,0.);
    glTranslatef(0, 1, -5);
    SetMaterial( 1., 0., 1., 50 );
    glutSolidTorus(0.2, 5.3, 50, 50);
    glPopMatrix();
    
    // Yellow Torus
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(6.5,9.,0.);
    glTranslatef(0, 1, -55);
    SetMaterial( 1., 1., 0., 50 );
    glutSolidTorus(0.2, 5.3, 50, 50);
    glPopMatrix();
    
    // Purple Torus
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(6.5,9.,0.);
    glTranslatef(0, 1, -105);
    SetMaterial( 0.5, 0.1, 0.5, 50 );
    glutSolidTorus(0.2, 5.3, 50, 50);
    glPopMatrix();
    
    // Cyan Torus
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(6.5,9.,0.);
    glTranslatef(0, 1, -155);
    SetMaterial( 0., 1., 1., 50 );
    glutSolidTorus(0.2, 5.3, 50, 50);
    glPopMatrix();

    
    
    //Flash Light List Begin   **********************************
    FlashList = glGenLists( 1 );
    glNewList( FlashList, GL_COMPILE );
    
    //red cube1
    SetPointLight( GL_LIGHT1, 0.15, 2.3, -4., 1., 0., 0. );
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.2, 2.3, -4);
    glColor3f(1, 0, 0);
    SetMaterial( 1., 0., 0., 50 );
    glutSolidCube(0.4);
    if( Time<0.5 )
        glEnable( GL_LIGHT1 );
    else
        glDisable( GL_LIGHT1 );
    glutPostRedisplay();
    glPopMatrix();
    
    //red cube2
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.4, 2.3, -4);
    glColor3f(1, 0, 0);
    SetMaterial( 1., 0., 0., 50 );
    glutSolidCube(0.4);
    glPopMatrix();

    //red cube3
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.6, 2.3, -4);
    glColor3f(1, 0, 0);
    SetMaterial( 1., 0., 0., 50 );
    glutSolidCube(0.4);
    glPopMatrix();
    
    //red cube4
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.8, 2.3, -4);
    glColor3f(1, 0, 0);
    SetMaterial( 1., 0., 0., 50 );
    glutSolidCube(0.4);
    glPopMatrix();


    // blue cube1
    SetPointLight( GL_LIGHT2, -0.15, 2.3, -4., 0., 0., 1. );
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(-0.2, 2.3, -4);
    glColor3f(0, 0, 1);
    SetMaterial( 0., 0., 1., 50 );
    glutSolidCube(0.4);
    if( Time>0.5 )
        glEnable( GL_LIGHT2 );
    else
        glDisable( GL_LIGHT2 );
    glutPostRedisplay();
    glPopMatrix();
    
     // blue cube2
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(-0.4, 2.3, -4);
    glColor3f(0, 0, 1);
    SetMaterial( 0., 0., 1., 50 );
    glutSolidCube(0.4);
    glPopMatrix();
    
    // blue cube3
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(-0.6, 2.3, -4);
    glColor3f(0, 0, 1);
    SetMaterial( 0., 0., 1., 50 );
    glutSolidCube(0.4);
    glPopMatrix();

    // blue cube3
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(-0.8, 2.3, -4);
    glColor3f(0, 0, 1);
    SetMaterial( 0., 0., 1., 50 );
    glutSolidCube(0.4);
    glPopMatrix();


    glEndList( );
    

    
    //Flash Light List End   **********************************
    
    // Draw Police Car *******************
    
     if (MyVehicleOn==2)
     {
         if (MyRightWay==true)
         {
             glPushMatrix();
             glTranslatef(5, 0, -move);
             DrawPoliceCar();
             glPopMatrix();
             
             glPushMatrix();
             glTranslatef(0, 0, -move);
             glTranslatef(5, 0.5, 6.1);
             glScalef(1.2, 1.2, 1.2);
             glCallList(FlashList);
             glPopMatrix();
         }
         else
         {
             glPushMatrix();
             glTranslatef(-12.5, 0, 0);
             
             glPushMatrix();
             glTranslatef(5, 0, -move);
             DrawPoliceCar();
             glPopMatrix();
             
             glPushMatrix();
             glTranslatef(0, 0, -move);
             glTranslatef(5, 0.5, 6.1);
             glScalef(1.2, 1.2, 1.2);
             glCallList(FlashList);
             glPopMatrix();

             
             glPopMatrix();
         }
         
     }
    
    // Draw California Car *******************
    if (MyVehicleOn==3)
    {
        if (MyRightWay==true)
        {
            glPushMatrix();
            glTranslatef(5, 0, -move);
            DrawCalifornia();
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(-12.5, 0, 0);
            
            glPushMatrix();
            glTranslatef(5, 0, -move);
            DrawCalifornia();
            glPopMatrix();

            glPopMatrix();
        }

    }

    
    if (RivalOn==2)
    {
        if (MyRightWay==true)
        {
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            DrawPoliceCar();
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            glTranslatef(0, 0.5, 6.1);
            glScalef(1.2, 1.2, 1.2);
            glCallList(FlashList);
            glPopMatrix();

        }
        else
        {
            glPushMatrix();
            glTranslatef(12.5, 0, 0);
            
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            DrawPoliceCar();
            glPopMatrix();
            
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            glTranslatef(0, 0.5, 6.1);
            glScalef(1.2, 1.2, 1.2);
            glCallList(FlashList);
            glPopMatrix();
            
            glPopMatrix();
        }
    }

    if (RivalOn==3)
    {
        if (MyRightWay==true)
        {
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            DrawCalifornia();
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(12.5, 0, 0);
            
            glPushMatrix();
            glTranslatef(-6, 0, -rivalmove);
            DrawCalifornia();
            glPopMatrix();
            
            glPopMatrix();
        }

    }

    
    glDisable(GL_LIGHTING);
    
    // Draw Star
    
    glPushMatrix();
    glTranslatef(15.,15.,-25.);
    glRotatef(90, 0, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    glCallList(StarList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(15.,15.,-75.);
    glRotatef(90, 0, 1, 0);
    glColor3f(1.0, 0.5, 0.0);
    glCallList(StarList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(15.,15.,-125.);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0, 0);
    glCallList(StarList);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(15.,15.,-175.);
    glRotatef(90, 0, 1, 0);
    glColor3f(1, 0, 1);
    glCallList(StarList);
    glPopMatrix();
    
    // Draw Windmill
    
    glPushMatrix();
    glTranslatef(15.,15.,-25.);
    glRotatef(90, 0, 1, 0);
    glColor3f(0.5, 0.5, 1.0);
    glScalef(8, 8, 8);
    glCallList(WindMillList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(15.,15.,-75.);
    glRotatef(90, 0, 1, 0);
    glColor3f(1.0, 0.0, 0.5);
     glScalef(8, 8, 8);
    glCallList(WindMillList);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(15.,15.,-125.);
    glRotatef(90, 0, 1, 0);
    glColor3f(0, 1, 1);
     glScalef(8, 8, 8);
    glCallList(WindMillList);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(15.,15.,-175.);
    glRotatef(90, 0, 1, 0);
    glColor3f(0, 1, 0);
     glScalef(8, 8, 8);
    glCallList(WindMillList);
    glPopMatrix();
    
    // My Vehicle Setting Begin ********************************
   
    // MyVehicleOn  ==1 Heli
    //              ==2 PoliceCar
    //              ==3 Porsche
    
    if (MyVehicleOn==1) {
        
      
        MyVehicleTurn1List= glGenLists( 1 );
        glNewList( MyVehicleTurn1List, GL_COMPILE );

        // Call HeliList
        
        glPushMatrix( );
        glTranslatef(6.5,7.,0.);
        glTranslatef(0.,0.,-move);
        glCallList( MyHeliList );
        glPopMatrix( );

        // Blades Animate

        glPushMatrix( );
        glTranslatef(6.5,7.,0.);
        glTranslatef(0.,2.9,-2.-move);
        glRotatef(roofspeed, 0., 1., 0.);
        glRotatef(90.0, 1., 0., 0.);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(4.5, 4.5, 4.5);
        glCallList(BladeList);
        glutPostRedisplay();
        glPopMatrix( );


        glPushMatrix( );
        glTranslatef(6.5,7.,0.);
        glTranslatef(.5,2.5,9.-move);
        glRotatef(tailspeed, 1., 0., 0.);
        glRotatef(90.0, 0., 1., 0.);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(1.5, 1.5, 1.5);
        glCallList(BladeList);
        glutPostRedisplay();
        glPopMatrix( );
        
        glEndList();
        
        if (MyRightWay==true)
        {
            glCallList(MyVehicleTurn1List);
        }
        else
        {
            glPushMatrix();
            glTranslatef(-12.5, 0, 0);
            glCallList(MyVehicleTurn1List);
            glPopMatrix();
        }
    }
    
    // Rival setting
    // RivalOn  ==1 Heli
    //          ==2 PoliceCar
    //          ==3 Porsche
    if (RivalOn==1)
    {
        RivalTurn1List= glGenLists( 1 );
        glNewList( RivalTurn1List, GL_COMPILE );

        
        glPushMatrix( );
        glTranslatef(3.,7.,0.);
        glTranslatef(-10.,0.,-rivalmove);
        glCallList( RivalHeliList );
        glPopMatrix( );
        
        // Blades Animate

        glPushMatrix( );
        glTranslatef(3.,7.,0.);
        glTranslatef(-10.,0.,0.);
        glTranslatef(0.,2.9,-2.-rivalmove);
        glRotatef(roofspeed, 0., 1., 0.);
        glRotatef(90.0, 1., 0., 0.);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(4.5, 4.5, 4.5);
        glCallList(BladeList);
        glutPostRedisplay();
        glPopMatrix( );
        
        
        glPushMatrix( );
         glTranslatef(3.,7.,0.);
        glTranslatef(-10,0.,0.);
        glTranslatef(.5,2.5,9.-rivalmove);
        glRotatef(tailspeed, 1., 0., 0.);
        glRotatef(90.0, 0., 1., 0.);
        glColor3f(1.0, 1.0, 1.0);
        glScalef(1.5, 1.5, 1.5);
        glCallList(BladeList);
        glutPostRedisplay();
        glPopMatrix( );
        
        glEndList();
        
        if (MyRightWay==true)
        {
            glCallList(RivalTurn1List);
        }
        else
        {
            glPushMatrix();
            glTranslatef(13.5, 0, 0);
            glCallList(RivalTurn1List);
            glPopMatrix();
        }

    }
    
    
    // Vehicle Setting End   *************************************************
    
    // Road Setting Begin   *****************************
    RoadList = glGenLists( 1 );
    glNewList( RoadList, GL_COMPILE );
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(0.2, 0,-222);
    glVertex3f(0.2, 0, 22);
    glVertex3f(-0.2,0, 22);
    glVertex3f(-0.2,0,-222);
    glEnd();
    glPopMatrix();
    glEndList();
    
    DestinationList = glGenLists( 1 );
    glNewList( DestinationList, GL_COMPILE );
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(0.2, 0,-12);
    glVertex3f(0.2, 0, 12);
    glVertex3f(-0.2,0, 12);
    glVertex3f(-0.2,0,-12);
    glEnd();
    glPopMatrix();
    glEndList();
    
    // middle yellow strip
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    //   SetMaterial( 1, 1, 0, 10 );
    glColor3f( 1, 1, 0);
    glCallList(RoadList);
    glPopMatrix();
    
    
    // right white strip
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(12,0,0);
    //   SetMaterial( 1, 1, 0, 10 );
    glColor3f( 1, 1, 1);
    glCallList(RoadList);
    glPopMatrix();
    
    // left white strip
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.2,0,0);
    glTranslatef(-12,0,0);
    //   SetMaterial( 1, 1, 0, 10 );
    glColor3f( 1, 1, 1);
    glCallList(RoadList);
    glPopMatrix();
    
    //  white strip at destination
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0,0,-200);
    glRotatef(90, 0, 1, 0);
    glColor3f( 1, 1, 1);
    glCallList(DestinationList);
    glPopMatrix();
    
    // grey road
    glPushMatrix();
    glShadeModel( GL_SMOOTH );
    glTranslatef(0.2,0,0);
    glScalef(60, 60, 60);
    //   SetMaterial( 0.42, 0.42, 0.42, 10 );
    glColor3f( 0.42, 0.42, 0.42);
    glCallList(RoadList);
    glPopMatrix();
    
    // Road Setting End   *****************************

    
    // animated 3D curves begin ******************************************
    for (int i=0; i<12;i++)
    {
        int j = 30 *i;
        
        hsv[0]=j+135;
        hsv[1]=1.0;
        hsv[2]=1;
        HsvRgb(hsv, rgb);
        
        curves[i].r=rgb[0];
        curves[i].g=rgb[1];
        curves[i].b=rgb[2];
        
        curves[i].p0.x0=sinf(M_Pi*j/180)*0.68;
        curves[i].p0.y0=cosf(M_Pi*j/180)*0.68;
        curves[i].p0.z0=0;
        curves[i].p0.x=curves[i].p0.x0;
        curves[i].p0.y=curves[i].p0.y0;
        curves[i].p0.z=curves[i].p0.z0;
        
        curves[i].p1.x0=sinf(M_Pi*j/180)*4.0;
        curves[i].p1.y0=cosf(M_Pi*j/180)*4.0;
        curves[i].p1.z0=sinf(2*M_PI*Time2);
        curves[i].p1.x=curves[i].p1.x0;
        curves[i].p1.y=curves[i].p1.y0;
        curves[i].p1.z=curves[i].p1.z0;
        
        curves[i].p2.x0=sinf(M_Pi*(j+30)/180)*4.0;
        curves[i].p2.y0=cosf(M_Pi*(j+30)/180)*4.0;
        curves[i].p2.z0=sinf(2*M_PI*Time2);
        curves[i].p2.x=curves[i].p2.x0;
        curves[i].p2.y=curves[i].p2.y0;
        curves[i].p2.z=curves[i].p2.z0;
        
        
        curves[i].p3.x0=sinf(M_Pi*(j+30)/180)*0.68;
        curves[i].p3.y0=cosf(M_Pi*(j+30)/180)*0.68;
        curves[i].p3.z0=0;
        curves[i].p3.x=curves[i].p3.x0;
        curves[i].p3.y=curves[i].p3.y0;
        curves[i].p3.z=curves[i].p3.z0;
        
        RotateZ( &curves[i].p0, ani, 0, 0, 0 );
        RotateZ( &curves[i].p1, -ani, 0, 0, 0 );
        RotateZ( &curves[i].p2, -ani, 0, 0, 0 );
        RotateZ( &curves[i].p3, ani, 0, 0, 0 );
        
    }
    
    for (int i=0;i<12;i++) {
        glPushMatrix();
        glTranslatef(0, 15, -210);
        glScalef(3, 3, 3);
        BezierCurve(curves[i].p0, curves[i].p1, curves[i].p2, curves[i].p3, curves[i].r, curves[i].g, curves[i].b);
        glPopMatrix();
    }

    
    
    // stationary 3D curves
    
    for (int i=0; i<12;i++)
    {
        int j = 30 *i;
        
        hsv[0]=j+270;
        hsv[1]=1.0;
        hsv[2]=1;
        HsvRgb(hsv, rgb);
        
        curves[i].r=rgb[0];
        curves[i].g=rgb[1];
        curves[i].b=rgb[2];
        
        curves[i].p0.x0=sinf(M_Pi*j/180)*0.1;
        curves[i].p0.y0=cosf(M_Pi*j/180)*0.1;
        curves[i].p0.z0=0;
        curves[i].p0.x=curves[i].p0.x0;
        curves[i].p0.y=curves[i].p0.y0;
        curves[i].p0.z=curves[i].p0.z0;
        
        curves[i].p1.x0=sinf(M_Pi*j/180)*0.68;
        curves[i].p1.y0=cosf(M_Pi*j/180)*0.68;
        curves[i].p1.z0=0;
        curves[i].p1.x=curves[i].p1.x0;
        curves[i].p1.y=curves[i].p1.y0;
        curves[i].p1.z=curves[i].p1.z0;
        
        curves[i].p2.x0=sinf(M_Pi*(j+30)/180)*0.68;
        curves[i].p2.y0=cosf(M_Pi*(j+30)/180)*0.68;
        curves[i].p2.z0=0;
        curves[i].p2.x=curves[i].p2.x0;
        curves[i].p2.y=curves[i].p2.y0;
        curves[i].p2.z=curves[i].p2.z0;
        
        
        curves[i].p3.x0=sinf(M_Pi*(j+30)/180)*0.1;
        curves[i].p3.y0=cosf(M_Pi*(j+30)/180)*0.1;
        curves[i].p3.z0=0;
        curves[i].p3.x=curves[i].p3.x0;
        curves[i].p3.y=curves[i].p3.y0;
        curves[i].p3.z=curves[i].p3.z0;
        
    }
    
    for (int i=0;i<12;i++) {
        glPushMatrix();
        glTranslatef(0, 15, -210);
        glScalef(3, 3, 3);
        BezierCurve(curves[i].p0, curves[i].p1, curves[i].p2, curves[i].p3, curves[i].r, curves[i].g, curves[i].b);
        glPopMatrix();
    }
    
  //Animated 3D Curves End*****************************************************
    
    // Frozen
    
    if( Frozen )
        glutIdleFunc( NULL );
    else
        glutIdleFunc( Animate );
    
    
    // Print result.
    
    glDisable( GL_DEPTH_TEST );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D( 0., 100.,     0., 100. );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glColor3f( 1., 1., 1. );
    if (move >= 200 && rivalmove <= move && Result == 0)
        Result=1;
    else if(rivalmove >= 200 && move < rivalmove && Result == 0)
        Result=2;
    if (Result==1)
          DoRasterString( 5., 5., 0., "You Win!" );
    else if (Result==2)
            DoStrokeString( 5., 5., 0., 5.0, "You are second! Try again? (Press t)" );
    
    
    // swap the double-buffered framebuffers:
    
    glutSwapBuffers( );
    
    
    // be sure the graphics buffer has been sent:
    // note: be sure to use glFlush( ) here, not glFinish( ) !
    
    glFlush( );
}

void
DoDifficultyMenu( int id)
{
    DifficultyOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

void
DoMyVehicleMenu( int id)
{
    MyVehicleOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

void
DoRivalMenu( int id)
{
    RivalOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

void
DoViewMenu( int id )
{
    ViewOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}

void
DoAxesMenu( int id )
{
    AxesOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


void
DoDebugMenu( int id )
{
    DebugOn = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// main menu callback:

void
DoMainMenu( int id )
{
    switch( id )
    {
        case RESET:
            Reset( );
            break;
            
        case QUIT:
            // gracefully close out the graphics:
            // gracefully close the graphics window:
            // gracefully exit the program:
            glutSetWindow( MainWindow );
            glFinish( );
            glutDestroyWindow( MainWindow );
            exit( 0 );
            break;
            
        default:
            fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
    }
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
    WhichProjection = id;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
    glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );
    
    char c;			// one character to print
    for( ; ( c = *s ) != '\0'; s++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, c );
    }
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
    glPushMatrix( );
    glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
    float sf = ht / ( 119.05f + 33.33f );
    glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
    char c;			// one character to print
    for( ; ( c = *s ) != '\0'; s++ )
    {
        glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
    }
    glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
    // get # of milliseconds since the start of the program:
    
    int ms = glutGet( GLUT_ELAPSED_TIME );
    
    // convert it to seconds:
    
    return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
    glutSetWindow( MainWindow );
    
    
    int myvehiclemenu = glutCreateMenu( DoMyVehicleMenu );
    
    glutAddMenuEntry( "Helicopter",  1 );
    glutAddMenuEntry( "Police Car",  2 );
    glutAddMenuEntry( "Ferrari California",  3 );
    
    int rivalmenu = glutCreateMenu( DoRivalMenu );
    
    glutAddMenuEntry( "Helicopter",  1 );
    glutAddMenuEntry( "Police Car",  2 );
    glutAddMenuEntry( "Ferrari California",  3 );
    
    int difficultymenu = glutCreateMenu( DoDifficultyMenu );
    glutAddMenuEntry( "Easy",  0 );
    glutAddMenuEntry( "Hard",  1 );
    
    int viewmenu = glutCreateMenu( DoViewMenu );

    glutAddMenuEntry( "Outside",  0 );
    glutAddMenuEntry( "Inside",   1 );
    glutAddMenuEntry( "Rear",     2 );
    
    
    int axesmenu = glutCreateMenu( DoAxesMenu );
    glutAddMenuEntry( "Off",  0 );
    glutAddMenuEntry( "On",   1 );
    
    
    int debugmenu = glutCreateMenu( DoDebugMenu );
    glutAddMenuEntry( "Off",  0 );
    glutAddMenuEntry( "On",   1 );
    
    int projmenu = glutCreateMenu( DoProjectMenu );
    glutAddMenuEntry( "Orthographic",  ORTHO );
    glutAddMenuEntry( "Perspective",   PERSP );
    
    int mainmenu = glutCreateMenu( DoMainMenu );
    glutAddSubMenu(   "My Vehicles",    myvehiclemenu);
    glutAddSubMenu(   "Rival Vehicles", rivalmenu);
    glutAddSubMenu(   "Difficulty",    difficultymenu);
    glutAddSubMenu(   "View",          viewmenu);
    glutAddSubMenu(   "Axes",          axesmenu);
    glutAddSubMenu(   "Projection",    projmenu );
    glutAddMenuEntry( "Reset",         RESET );
    glutAddSubMenu(   "Debug",         debugmenu);
    glutAddMenuEntry( "Quit",          QUIT );
    
    // attach the pop-up menu to the right mouse button:
    
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}



// initialize the glut and OpenGL libraries:
//	also setup display lists and callback functions

void
InitGraphics( )
{
    // request the display modes:
    // ask for red-green-blue-alpha color, double-buffering, and z-buffering:
    
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    
    // set the initial window configuration:
    
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );
    
    // open the window and set its title:
    
    MainWindow = glutCreateWindow( WINDOWTITLE );
    glutSetWindowTitle( WINDOWTITLE );
    
    // set the framebuffer clear values:
    
    glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );
    
    // setup the callback functions:
    // DisplayFunc -- redraw the window
    // ReshapeFunc -- handle the user resizing the window
    // KeyboardFunc -- handle a keyboard input
    // MouseFunc -- handle the mouse button going down or up
    // MotionFunc -- handle the mouse moving with a button down
    // PassiveMotionFunc -- handle the mouse moving with a button up
    // VisibilityFunc -- handle a change in window visibility
    // EntryFunc	-- handle the cursor entering or leaving the window
    // SpecialFunc -- handle special keys on the keyboard
    // SpaceballMotionFunc -- handle spaceball translation
    // SpaceballRotateFunc -- handle spaceball rotation
    // SpaceballButtonFunc -- handle spaceball button hits
    // ButtonBoxFunc -- handle button box hits
    // DialsFunc -- handle dial rotations
    // TabletMotionFunc -- handle digitizing tablet motion
    // TabletButtonFunc -- handle digitizing tablet button hits
    // MenuStateFunc -- declare when a pop-up menu is in use
    // TimerFunc -- trigger something to happen a certain time from now
    // IdleFunc -- what to do when nothing else is going on
    
    glutSetWindow( MainWindow );
    glutDisplayFunc( Display );
    glutReshapeFunc( Resize );
    glutKeyboardFunc( Keyboard );
    glutMouseFunc( MouseButton );
    glutMotionFunc( MouseMotion );
    glutPassiveMotionFunc( NULL );
    glutVisibilityFunc( Visibility );
    glutEntryFunc( NULL );
    glutSpecialFunc( NULL );
    glutSpaceballMotionFunc( NULL );
    glutSpaceballRotateFunc( NULL );
    glutSpaceballButtonFunc( NULL );
    glutButtonBoxFunc( NULL );
    glutDialsFunc( NULL );
    glutTabletMotionFunc( NULL );
    glutTabletButtonFunc( NULL );
    glutMenuStateFunc( NULL );
    glutTimerFunc( -1, NULL, 0 );
    glutIdleFunc( NULL );
    
    // init glew (a window must be open to do this):
    
#ifdef WIN32
    GLenum err = glewInit( );
    if( err != GLEW_OK )
    {
        fprintf( stderr, "glewInit Error\n" );
    }
    else
        fprintf( stderr, "GLEW initialized OK\n" );
    fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
    
}


// initialize the display lists that will not change:
// (a display list is a way to store opengl commands in
//  memory so that they can be played back efficiently at a later time
//  with a call to glCallList( )


float
Dot( float v1[3], float v2[3] )
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}
void
Cross( float v1[3], float v2[3], float vout[3] )
{
    float tmp[3];
    tmp[0] = v1[1]*v2[2] - v2[1]*v1[2];
    tmp[1] = v2[0]*v1[2] - v1[0]*v2[2];
    tmp[2] = v1[0]*v2[1] - v2[0]*v1[1];
    vout[0] = tmp[0];
    vout[1] = tmp[1];
    vout[2] = tmp[2];
}

float
Unit( float vin[3], float vout[3] )
{
    float dist = vin[0]*vin[0] + vin[1]*vin[1] + vin[2]*vin[2];
    if( dist > 0.0 )
    {
        dist = sqrt( dist );
        vout[0] = vin[0] / dist;
        vout[1] = vin[1] / dist;
        vout[2] = vin[2] / dist;
    }
    else
    {
        vout[0] = vin[0];
        vout[1] = vin[1];
        vout[2] = vin[2];
    }
    return dist;
}


void
InitLists( )
{
    /*    float dx = BOXSIZE / 2.f;
     float dy = BOXSIZE / 2.f;
     float dz = BOXSIZE / 2.f;
     */
    glutSetWindow( MainWindow );
    
    // create the object:
    
    int i;
    struct point *p0, *p1, *p2;
    struct tri *tp;
    float p01[3], p02[3], n[3];
    
    //MyHeliList
    
    MyHeliList = glGenLists( 1 );
    glNewList( MyHeliList, GL_COMPILE );
    
    glPushMatrix( );
    glTranslatef( 0., -1, 0. );
    glRotatef(  97.,   0., 1., 0. );
    glRotatef( -15.,   0., 0., 1. );
    glScalef( (GLfloat)HSCALE, (GLfloat)HSCALE, (GLfloat)HSCALE );
    glBegin( GL_TRIANGLES );
    for( i=0, tp = Helitris; i < Helintris; i++, tp++ )
    {
        p0 = &Helipoints[ tp->p0 ];
        p1 = &Helipoints[ tp->p1 ];
        p2 = &Helipoints[ tp->p2 ];
        
        // fake "lighting" from above:
        
        p01[0] = p1->x - p0->x;
        p01[1] = p1->y - p0->y;
        p01[2] = p1->z - p0->z;
        p02[0] = p2->x - p0->x;
        p02[1] = p2->y - p0->y;
        p02[2] = p2->z - p0->z;
        Cross( p01, p02, n );
        Unit( n, n );
        n[1] = fabs( n[1] );
        n[1] += .25;
        if( n[1] > 1. )
            n[1] = 1.;
        glColor3f( 0.6*n[1], n[1], 0.2*n[1] );
        
        glVertex3f( p0->x, p0->y, p0->z );
        glVertex3f( p1->x, p1->y, p1->z );
        glVertex3f( p2->x, p2->y, p2->z );
    }
    glEnd( );
    glPopMatrix( );
    glEndList( );
    
    // RivalHeliList
    
    RivalHeliList = glGenLists( 1 );
    glNewList( RivalHeliList, GL_COMPILE );
    
    glPushMatrix( );
    glTranslatef( 0., -1, 0. );
    glRotatef(  97.,   0., 1., 0. );
    glRotatef( -15.,   0., 0., 1. );
    glScalef( (GLfloat)HSCALE, (GLfloat)HSCALE, (GLfloat)HSCALE );
    glBegin( GL_TRIANGLES );
    for( i=0, tp = Helitris; i < Helintris; i++, tp++ )
    {
        p0 = &Helipoints[ tp->p0 ];
        p1 = &Helipoints[ tp->p1 ];
        p2 = &Helipoints[ tp->p2 ];
        
        // fake "lighting" from above:
        
        p01[0] = p1->x - p0->x;
        p01[1] = p1->y - p0->y;
        p01[2] = p1->z - p0->z;
        p02[0] = p2->x - p0->x;
        p02[1] = p2->y - p0->y;
        p02[2] = p2->z - p0->z;
        Cross( p01, p02, n );
        Unit( n, n );
        n[1] = fabs( n[1] );
        n[1] += .25;
        if( n[1] > 1. )
            n[1] = 1.;
        glColor3f( 0.3*n[1], 0.5*n[1], n[1] );
        
        glVertex3f( p0->x, p0->y, p0->z );
        glVertex3f( p1->x, p1->y, p1->z );
        glVertex3f( p2->x, p2->y, p2->z );
    }
    glEnd( );
    glPopMatrix( );
    glEndList( );
    
    StarList = glGenLists( 1 );
    glNewList( StarList, GL_COMPILE );
    glPushMatrix( );
    glTranslatef(0., 0., -60.);
    glScalef( 9., 9., 9.);
    glBegin(GL_LINE_LOOP);  // 5 star pentagram
    glVertex3f(0,  1.5, 3);
    glVertex3f(1,  -1, 3);
    glVertex3f(-1.3, 0.5, 3);
    glVertex3f(1.3, 0.5, 3);
    glVertex3f(-1,-1, 3);
    glEnd();
    glPopMatrix( );
    
    glEndList( );
    
    
    //    Windmill List
    
    WindMillList = glGenLists( 1 );
    glNewList( WindMillList, GL_COMPILE );

    glBegin( GL_TRIANGLES );
    
//    glColor3f( 0., 1., 0. );
//    glNormal3f( 0., 0.,  1. );
    glVertex3f(  0, 0, 0 );
    glVertex3f(  1, 0, 0 );
    glVertex3f(  1, 1, 0 );
    
    
    glVertex3f(  0, 0, 0 );
    glVertex3f(  0, 1, 0 );
    glVertex3f( -1, 1, 0 );
    
    glVertex3f(  0, 0, 0 );
    glVertex3f( -1, 0, 0 );
    glVertex3f( -1,-1, 0 );
    
    glVertex3f(  0, 0, 0 );
    glVertex3f(  0,-1, 0 );
    glVertex3f(  1,-1, 0 );
    glEnd( );
    glEndList();
    
    
    // draw the helicopter blade with radius BLADE_RADIUS and
    //	width BLADE_WIDTH centered at (0.,0.,0.) in the XY plane
    
    BladeList = glGenLists( 1 );
    glNewList( BladeList, GL_COMPILE );
    glPushMatrix( );
    glBegin( GL_TRIANGLES );
    glVertex2f(  BLADE_RADIUS,  BLADE_WIDTH/2. );
    glVertex2f(  0., 0. );
    glVertex2f(  BLADE_RADIUS, -BLADE_WIDTH/2. );
    
    glVertex2f( -BLADE_RADIUS, -BLADE_WIDTH/2. );
    glVertex2f(  0., 0. );
    glVertex2f( -BLADE_RADIUS,  BLADE_WIDTH/2. );
    glEnd( );
    glPopMatrix( );
    glEndList( );
    

    // create the axes:
    AxesList = glGenLists( 1 );
    glNewList( AxesList, GL_COMPILE );
    glPushMatrix( );
    glLineWidth( AXES_WIDTH );
    Axes( 4.0 );
    glLineWidth( 1. );
    glPopMatrix( );
    glEndList( );
    
}


// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
    if( DebugOn != 0 )
        fprintf( stderr, "Keyboard: '%c' (0x%0x)\n", c, c );
    
    switch( c )
    {
        case 'f':
        case 'F':
            Frozen = ! Frozen;
            if( Frozen )
                glutIdleFunc( NULL );
            else
                glutIdleFunc( Animate );
            break;
        case 'b':
        case 'B':
            BeginOn= ! BeginOn;
            break;
        case 'a':
        case 'A':
            if (MyRightWay==true)
                MyRightWay=false;
            break;
        case 'd':
        case 'D':
            if (MyRightWay==false)
                MyRightWay=true;
            break;
        case '0':
            Light0On = ! Light0On;
            break;
        case 't':
        case 'T':
            Reset( );
            break;
        case 'w':
        case 'W':
            if (move<200&&BeginOn==true) {
                move=move+2.5;
            }
            break;
        case 's':
        case 'S':
            move=move-2;
            break;
        case 'o':   // outside view
        case 'O':
            ViewOn = 0;
            break;
        case 'i':   // inside view
        case 'I':
            if (MyVehicleOn==1)
                ViewOn = 1;
            break;
        case 'r':   // rear view
        case 'R':
            ViewOn = 2;
            break;
        case 'x':
        case 'X':
            Xrot += 30;
            break;
        case 'y':
        case 'Y':
            Yrot += 30;
            break;
        case 'z':
        case 'Z':
            Zrot += 30;
            break;
        case 'm':
        case 'M':
            Scale += 0.10;
            break;
        case 'n':
        case 'N':
            Scale -= 0.10;
            break;
        case 'p':
        case 'P':
            WhichProjection = PERSP;
            break;
            
        case 'q':
        case 'Q':
        case ESCAPE:
            DoMainMenu( QUIT );	// will not return here
            break;				// happy compiler
            
        default:
            fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
    }
    
    // force a call to Display( ):
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
    int b = 0;			// LEFT, MIDDLE, or RIGHT
    
    if( DebugOn != 0 )
        fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );
    
    
    // get the proper button bit mask:
    
    switch( button )
    {
        case GLUT_LEFT_BUTTON:
            b = LEFT;		break;
            
        case GLUT_MIDDLE_BUTTON:
            b = MIDDLE;		break;
            
        case GLUT_RIGHT_BUTTON:
            b = RIGHT;		break;
            
        default:
            b = 0;
            fprintf( stderr, "Unknown mouse button: %d\n", button );
    }
    
    
    // button down sets the bit, up clears the bit:
    
    if( state == GLUT_DOWN )
    {
        Xmouse = x;
        Ymouse = y;
        ActiveButton |= b;		// set the proper bit
    }
    else
    {
        ActiveButton &= ~b;		// clear the proper bit
    }
}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
    if( DebugOn != 0 )
        fprintf( stderr, "MouseMotion: %d, %d\n", x, y );
    
    int dx = x - Xmouse;		// change in mouse coords
    int dy = y - Ymouse;
    
    if( ( ActiveButton & LEFT ) != 0 )
    {
        Xrot += ( ANGFACT*dy );
        Yrot += ( ANGFACT*dx );
    }
    
    
    if( ( ActiveButton & MIDDLE ) != 0 )
    {
        Scale += SCLFACT * (float) ( dx - dy );
        
        // keep object from turning inside-out or disappearing:
        
        if( Scale < MINSCALE )
            Scale = MINSCALE;
    }
    
    Xmouse = x;			// new current position
    Ymouse = y;
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene

void
Reset( )
{
    ActiveButton = 0;
    AxesOn = 0;
    ViewOn = 0;
    DebugOn = 0;
    DepthCueOn = 0;
    Scale  = 1.0;
    WhichColor = WHITE;
    WhichProjection = PERSP;
    Xrot = Yrot = Zrot = 0.;
    move = 0.;
    rivalmove=0.;
    MyVehicleOn = 1;
    RivalOn = 2;
    Result = 0;
    Light0On=true;
    MyRightWay=true;
    RivalRightWay=false;
    DifficultyOn=false;
    BeginOn=false;
}


// called when user resizes the window:

void
Resize( int width, int height )
{
    if( DebugOn != 0 )
        fprintf( stderr, "ReSize: %d, %d\n", width, height );
    
    // don't really need to do anything since window size is
    // checked each time in Display( ):
    
    glutSetWindow( MainWindow );
    glutPostRedisplay( );
}


// handle a change to the window's visibility:

void
Visibility ( int state )
{
    if( DebugOn != 0 )
        fprintf( stderr, "Visibility: %d\n", state );
    
    if( state == GLUT_VISIBLE )
    {
        glutSetWindow( MainWindow );
        glutPostRedisplay( );
    }
    else
    {
        // could optimize by keeping track of the fact
        // that the window is not visible and avoid
        // animating or redrawing it ...
    }
}



///////////////////////////////////////   HANDY UTILITIES:  //////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
    0.f, 1.f, 0.f, 1.f
};

static float xy[ ] = {
    -.5f, .5f, .5f, -.5f
};

static int xorder[ ] = {
    1, 2, -3, 4
};

static float yx[ ] = {
    0.f, 0.f, -.5f, .5f
};

static float yy[ ] = {
    0.f, .6f, 1.f, 1.f
};

static int yorder[ ] = {
    1, 2, 3, -2, 4
};

static float zx[ ] = {
    1.f, 0.f, 1.f, 0.f, .25f, .75f
};

static float zy[ ] = {
    .5f, .5f, -.5f, -.5f, 0.f, 0.f
};

static int zorder[ ] = {
    1, 2, 3, 4, -5, 6
};

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)

void
Axes( float length )
{
    glBegin( GL_LINE_STRIP );
    glVertex3f( length, 0., 0. );
    glVertex3f( 0., 0., 0. );
    glVertex3f( 0., length, 0. );
    glEnd( );
    glBegin( GL_LINE_STRIP );
    glVertex3f( 0., 0., 0. );
    glVertex3f( 0., 0., length );
    glEnd( );
    
    float fact = LENFRAC * length;
    float base = BASEFRAC * length;
    
    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 4; i++ )
    {
        int j = xorder[i];
        if( j < 0 )
        {
            
            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
    }
    glEnd( );
    
    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 5; i++ )
    {
        int j = yorder[i];
        if( j < 0 )
        {
            
            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
    }
    glEnd( );
    
    glBegin( GL_LINE_STRIP );
    for( int i = 0; i < 6; i++ )
    {
        int j = zorder[i];
        if( j < 0 )
        {
            
            glEnd( );
            glBegin( GL_LINE_STRIP );
            j = -j;
        }
        j--;
        glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
    }
    glEnd( );
    
}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
    // guarantee valid input:
    
    float h = hsv[0] / 60.f;
    while( h >= 6. )	h -= 6.;
    while( h <  0. ) 	h += 6.;
    
    float s = hsv[1];
    if( s < 0. )
        s = 0.;
    if( s > 1. )
        s = 1.;
    
    float v = hsv[2];
    if( v < 0. )
        v = 0.;
    if( v > 1. )
        v = 1.;
    
    // if sat==0, then is a gray:
    
    if( s == 0.0 )
    {
        rgb[0] = rgb[1] = rgb[2] = v;
        return;
    }
    
    // get an rgb from the hue itself:
    
    float i = floor( h );
    float f = h - i;
    float p = v * ( 1.f - s );
    float q = v * ( 1.f - s*f );
    float t = v * ( 1.f - ( s * (1.f-f) ) );
    
    float r, g, b;			// red, green, blue
    switch( (int) i )
    {
        case 0:
            r = v;	g = t;	b = p;
            break;
            
        case 1:
            r = q;	g = v;	b = p;
            break;
            
        case 2:
            r = p;	g = v;	b = t;
            break;
            
        case 3:
            r = p;	g = q;	b = v;
            break;
            
        case 4:
            r = t;	g = p;	b = v;
            break;
            
        case 5:
            r = v;	g = p;	b = q;
            break;
    }
    
    
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

