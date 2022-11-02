#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "include/BmpLoader.h"

double Txval=0,Tyval=0,Tzval=0, arodure=60;
//double eyex = 5;
//double eyey = 5;
//double eyez = 25;
//double centerx = 5;
//double centery = 0;
//double centerz = 0;
//double upx = 0;
//double upy = 1;
//double upz = 0;
double myval = 0;
double windowHeight=960, windowWidth=540;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
double far_id =1000.0;
double near_id = 30.0;
unsigned int ID[100];

GLfloat eyeX = 20;
GLfloat eyeY = 20;
GLfloat eyeZ = 150;

GLfloat lookX = 20;
GLfloat lookY = 20;
GLfloat lookZ = 0;

GLfloat upX = 0;
GLfloat upY = 1;
GLfloat upZ = 0;

GLfloat scaleX = 1;
GLfloat scaleY = 1;
GLfloat scaleZ = 1;

int agun_switch = 0;
int rotating_switch_for_store2 = -1,fence_gate_switch = -1;
float rotatingVariableForStore2 = 0 , fence_gate_slide = 0;

static void resize(int width, int height)
{
    const float ar = (float) height / (float) width;
//    ini_x = width/2;
//    ini_y = height/2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -ar, ar, near_id, far_id);

    printf("he");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


GLfloat cube_coordinate[8][3] =
{
    {0.0,0.0,0.0},
    {0.0,2.0,0.0},
    {2.0,2.0,0.0},
    {2.0,0.0,0.0},

    {0.0,0.0,-2.0},
    {0.0,2.0,-2.0},
    {2.0,2.0,-2.0},
    {2.0,0.0,-2.0}


};
static GLubyte cube_indices[6][4] =
{
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},

    {1,2,6,5},
    {7,4,0,3}

};


void draw_house_cube(GLfloat c1,GLfloat c2,GLfloat c3 )
{

     GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { c1*0.3, c2*0.3, c3*0.3, 1.0 };
    GLfloat mat_diffuse[] = { c1*0.7, c2*0.7, c3*0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {


        glVertex3fv(&cube_coordinate[cube_indices[i][0]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][1]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][2]][0]);
        glVertex3fv(&cube_coordinate[cube_indices[i][3]][0]);
    }
    glEnd();
}

void draw_house_cube()
{

     GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {100};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {

        getNormal3p(cube_coordinate[cube_indices[i][0]][0], cube_coordinate[cube_indices[i][0]][1], cube_coordinate[cube_indices[i][0]][2],
                    cube_coordinate[cube_indices[i][1]][0], cube_coordinate[cube_indices[i][1]][1], cube_coordinate[cube_indices[i][1]][2],
                    cube_coordinate[cube_indices[i][2]][0], cube_coordinate[cube_indices[i][2]][1], cube_coordinate[cube_indices[i][2]][2]);
//        glColor3f(c1, c2, c3);
        glVertex3fv(&cube_coordinate[cube_indices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[cube_indices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&cube_coordinate[cube_indices[i][2]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[cube_indices[i][3]][0]);glTexCoord2f(1,0);
    }
    glEnd();
}

GLfloat mini_fence_coordinate[8][3] =
{
    {3.0,-5.0,0.0},
    {3.0,5.0,0.0},
    {1.0,5.0,0.0},
    {1.0,-5.0,0.0},

    {3.0,-5.0,2.0},
    {3.0,5.0,2.0},
    {1.0,5.0,2.0},
    {1.0,-5.0,2.0},

};
static GLubyte mini_fence_indices[6][4] =
{
    {0,3,2,1},
    {3,7,6,2},
    {7,4,5,6},
    {4,0,1,5},
    {5,1,2,6},
    {1,3,0,4}

};

void draw_mini_fence_cube()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_diffuse[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_specular[] = { 0.54, 0.27, 0.075, 1.0 };
    GLfloat mat_shininess[] = {20};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        // glColor3f(0.2f, 0.2f, 0.2f);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][0]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][1]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][2]][0]);
        glVertex3fv(&mini_fence_coordinate[mini_fence_indices[i][3]][0]);
    }
    glEnd();
}


//GLfloat cube_coordinate[8][3] =
//{
//     {0.0,0.0,0.0},
//    {0.0,2.0,0.0},
//    {2.0,2.0,0.0},
//    {2.0,0.0,0.0},
//
//    {0.0,0.0,-2.0},
//    {0.0,2.0,-2.0},
//    {2.0,2.0,-2.0},
//    {2.0,0.0,-2.0}
//
//};
//static GLubyte cube_indices[6][4] =
//{
//    {0,3,2,1},
//    {3,7,6,2},
//    {7,4,5,6},
//    {4,0,1,5},
//
//    {1,2,6,5},
//    {7,4,0,3}
//
//
//};

static GLubyte pyramid_indices[6][4] =
{
    {0,3,2,1},
    {3,7,2,2},
    {7,4,1,2},
    {4,0,1,1},

    //{1,2,6,5},
    {7,4,0,3}


};

void draw_pyramid()
{
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <5; i++)
    {
        //glColor3f(0.1f, 0.1f, 0.1f);
        //glColor3f(0.2f, 0.2f, 0.2f);
        getNormal3p(cube_coordinate[pyramid_indices[i][0]][0], cube_coordinate[pyramid_indices[i][0]][1], cube_coordinate[pyramid_indices[i][0]][2],
                    cube_coordinate[pyramid_indices[i][1]][0], cube_coordinate[pyramid_indices[i][1]][1], cube_coordinate[pyramid_indices[i][1]][2],
                    cube_coordinate[pyramid_indices[i][2]][0], cube_coordinate[pyramid_indices[i][2]][1], cube_coordinate[pyramid_indices[i][2]][2]);

        glVertex3fv(&cube_coordinate[pyramid_indices[i][0]][0]);glTexCoord2f(1,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][1]][0]);glTexCoord2f(1,1);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&cube_coordinate[pyramid_indices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();


}

void draw_fence()
{
    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(j,5,0);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(0,5,j);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=0;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(120,5,j);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=0;j<=45;j+=4)
    {
        glPushMatrix();
        glTranslatef(j,5,120);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=75;j<=120;j+=4)
    {
        glPushMatrix();
        glTranslatef(j,5,120);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    for (int j=46;j<=74;j+=4)
    {
        glPushMatrix();
        glTranslatef(j+fence_gate_slide,5,115);
        draw_mini_fence_cube();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0,0,117);
    glScalef(60,.07,1);
    draw_house_cube(0.54, 0.27, 0.075);
    glPopMatrix();
}

void draw_room()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glTranslatef(-100,0,180);
    glScalef(120,0.01,140);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

//    glPushMatrix();
//    glScalef(0.01,3,18);
//    draw_house_cube(0, 0.6, 0.9);
//    glPopMatrix();
////
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(-100,0,-100);
    glScalef(120,50,0.01);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
////
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(140,0,200);
    glScalef(1,50,150);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glTranslatef(-100,0,200);
    glScalef(1,50,150);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

double ftheta = 0;
bool frotate=0;

void draw_chorki()
{
    glPushMatrix();
    glScalef(1,10,1);
    draw_house_cube(1, 1, 1);
    glPopMatrix();

    glPushMatrix();
//    glTranslatef();
//    glTranslatef(0,40,0);
    glTranslatef(0,20,0);
    glRotatef(ftheta, 0, 0, 1);
    glTranslatef(0,-20,0);

    glPushMatrix();
    glTranslatef(-8,20,0);
    glScalef(8,.5,.5);
    draw_house_cube(1, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3,12,0);
    glRotatef(90,0,0,1);
    glScalef(8,.5,.5);
    draw_house_cube(1, 0, 0);
    glPopMatrix();
//eta ki extra?
    glPopMatrix();

}




void draw_chorki_box()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glScalef(3,3,3);
    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glScalef(3,3,3);
    glTranslatef(-3.5, 4, 1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glScalef(3,3,3);
    glTranslatef(-1.2, 1.5, 1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glScalef(3,3,3);
    glTranslatef(-1.2, 6.5, 1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void draw_agun()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(45,0,-12);
    glRotatef(270,1,0,0);
    glutSolidCone(5,2,20,10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glTranslatef(2,0,3);
    glRotatef(280,1,0,0);
    glutSolidCone(5,3,20,10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(-2,0,0);
    glRotatef(270,1,0,0);
    glutSolidCone(5,4,20,10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
    glTranslatef(2,0,-1);
    glRotatef(260,1,0,0);
    glutSolidCone(5,3,20,10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPopMatrix();

}

void draw_kettle_in_stall()
{
    glPushMatrix();
    glutSolidTeapot(5);
    glPopMatrix();
}

void chips_er_packet()
{
//    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,7);
//    glutSolidCube(2);
//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
//    glTranslatef(0,0,0);
    glScalef(2,1.5,.01);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

////
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glScalef(.01,1.5,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
////
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(4,0,0);
    glScalef(.01,1.5,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(0,0,-2);
    glScalef(2,1.5,.01);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}



void draw_stall_1()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(5,5,1);
//    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(1,5,5);
//    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(1,5,5);
    glTranslatef(8,0,0);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

//    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);
//    glScalef(5,8,1);
//    glTranslatef(0,0,-8);
//    draw_house_cube();
//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(5,10,1);
    glTranslatef(0,0,-8);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(5,.5,5);
//    glTranslatef(0,0,-8);
    draw_house_cube(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(5,.5,5);
    glTranslatef(0,40,0);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.5,5);
    glTranslatef(0,19,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(.4,.4,.4);
    glTranslatef(5,30,-10);
    draw_kettle_in_stall();
    glPopMatrix();


    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,18,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,15,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,12,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,9,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,6,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(15,3,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,18,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,15,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,12,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,9,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,6,2);
    chips_er_packet();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(9,3,2);
    chips_er_packet();
    glPopMatrix();


    if(agun_switch==1)
    {
        glPushMatrix();
        glScalef(.5,.8,.5);
        glTranslatef(4,13.5,-10);
        draw_agun();
        glPopMatrix();
    }







}

void draw_stall_2()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(10,5,1);
//    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(1,5,6);
//    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
//
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);

    glTranslatef(20,0,0);
    glRotatef(rotatingVariableForStore2,0,1,0);
    glScalef(1,5,6);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

//    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);
//    glScalef(5,8,1);
//    glTranslatef(0,0,-8);
//    draw_house_cube();
//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(10,10,1);
    glTranslatef(0,0,-10);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glScalef(10,10,1);
    glTranslatef(0,0,-8);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(10,.5,5);
//    glTranslatef(0,0,-8);
    draw_house_cube();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(10,.5,5);
    glTranslatef(0,40,0);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}

void draw_vending_machine()
{
    //shamner ta
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glScalef(4,8,1);
//    glTranslatef(1.5,4,1);
    draw_house_cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //left er ta
    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(1,8,6);
//    glTranslatef(1.5,4,1);
    draw_house_cube(.1,.1,.1);
//    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


//right er ta
    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);

    glTranslatef(8,0,0);
    glScalef(1,8,6);
    draw_house_cube(.1,.1,.1);
//    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //pichoner duita
    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(4,8,1);
    glTranslatef(0,0,-10);
    draw_house_cube(.1,.1,.1);
//    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

//    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,8);
//    glScalef(4,8,1);
//    glTranslatef(0,0,-8);
//    draw_house_cube();
//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();

    //nicher ta
    glPushMatrix();
    glScalef(4,.5,5);
//    glTranslatef(0,0,-8);
    draw_house_cube(.1,.1,.1);
    glPopMatrix();

    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,4);
    glScalef(4,.5,5);
    glTranslatef(0,30,0);
    draw_house_cube(.1,.1,.1);
//    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


int khelna_switch= 0;
double khelna_ang = 0;
void draw_khelna()
{
    glPushMatrix();
    glScalef(3,3,3);
    glRotatef(-90,0,1,0);
//    glTranslatef(-1.2, 6.5, 1);
    draw_pyramid();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,6);
    glScalef(3,3,3);
    glRotatef(90,0,1,0);
//    glTranslatef(-1.2, 6.5, 1);
    draw_pyramid();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,6,0);
    glRotatef(khelna_ang,0,0,1);
    glTranslatef(0,-6,0);

    glTranslatef(-12,6,6);

    glScalef(12,.5,3);
//    glRotatef(khelna_ang,0,0,1);
//    glRotatef(90,0,1,0);
//    glTranslatef(-1.2, 6.5, 1);
    draw_house_cube(1,1,1);
    glPopMatrix();

}




bool light_switch0 = 1, light_switch1 = 1, light_switch2 = 1;

void light0()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat light_position[] = { 10, 0.0, 50.0, 1.0 };
    GLfloat light_position[] = { 50, 60, 20, 1.0 };
   // GLfloat light_position[] = { 5,2,3, 0.0 };


    if(light_switch0)
    glEnable( GL_LIGHT0);
    else
    glDisable(GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}


void light2()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_spot[] = {0,-1.0,0.0}; // direction
    GLfloat light_position[] = { 5,25.0,0.0, 1.0 };
//    GLfloat light_position[] = { 8, -4, -55.0, 1.0 };


    if(light_switch2)
    glEnable( GL_LIGHT2);
    else
    glDisable(GL_LIGHT2);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);
     glLightf( GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
    glLightfv( GL_LIGHT2, GL_SPOT_DIRECTION, light_spot);
    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);




    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}



void draw_every()
{
    draw_room();
    glPushMatrix();
    glTranslatef(60,0,-30);
    glPushMatrix();
//    glTranslatef(3,5,-14.9);
//    glRotatef(-90,1,0,0);
    draw_chorki();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6,15,0);
    glRotatef(ftheta,0,0,1);
    glTranslatef(0.6,-15,0);
    draw_chorki_box();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(-1.2,15,0);
//    glRotatef(ftheta,0,0,1);
    glTranslatef(15,0,-24);
    draw_stall_1();
    glPopMatrix();

    glPushMatrix();
//    glTranslatef(-1.2,15,0);

    glTranslatef(-30,0,-10);
    glRotatef(90,0,1,0);
    draw_stall_1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,50);
    draw_khelna();
    glPopMatrix();

//    glPushMatrix();
//    glTranslatef(0,2,0);
//    chips_er_packet();
//    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30,0,-24);
    draw_stall_2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,0,-24);
    draw_vending_machine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50,0,-50);
    draw_fence();
    glPopMatrix();





}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-15,15, -15, 15, near_id, far_id);

    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);

    //glViewport(0, 0, windowHeight, windowWidth);
    //glRotatef(30, 0, 0, 1 );
    glScalef(scaleX,scaleY,scaleZ);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    light0();
    light2();

    glScalef(1,1.8,1);



    draw_every();


    glFlush();
    glutSwapBuffers();
}

int bv = 0;


void b_swap()
{
    if(bv==1)
    {
        int tmp = eyeY;
        eyeY = eyeZ;
        eyeZ = tmp;

        tmp = upY;
        upY = upZ;
        upZ = tmp;

    }
}








double aY = 90, aP = 90, aR = 90;

void pitch() // x axis , y er about ,  o p
{
    lookX = 400.0*(cos(aP*3.1416/180.0));
}

void yaw() // y axis, x axis about y u
{
    lookY = 400.0*(cos(aY*3.1416/180.0));
//    printf("%lf\n" , aY);
}


void roll() // z axis h j
{
    upX = 10*(cos(aR*3.1416/180.0));
    upY = 10*(sin(aR*3.1416/180.0));
    //printf("%lf %faR\n" , aR,cos(aR*3.1416/180.0));
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'T':
    case 't':
        bRotate = !bRotate;
        axis_x=1.0;
        axis_y=0.0;
        break;

    case 'o':
        if(aP>=180)
            break;
        aP+=1;
        pitch();
        glutPostRedisplay();
        break;
    case 'p':
        aP-=1;
        if(aP<=0)
            break;
        pitch();
        glutPostRedisplay();
        break;

    case 'y':

          // aY -= 360.0*floor(aY/360.0);
        if(aY >= 180.0 )break;
        aY+=1;

        yaw();
        glutPostRedisplay();
        break;
    case 'u':
        if( aY <=0)break;
        aY-=1;

           // aY += 360.0*floor(aY/360.0);
        yaw();
        glutPostRedisplay();
        break;


     case 'h':

          // aY -= 360.0*floor(aY/360.0);
        if(aR >= 270.0 )
            break;
        aR+=1;

        roll();
        glutPostRedisplay();
        break;
    case 'j':
        if( aR <= -90.0)
            break;
        aR-=1;

           // aY += 360.0*floor(aY/360.0);
        roll();
        glutPostRedisplay();
        break;
    case 'k':
        light_switch0=!light_switch0;
        //light0();
        glutPostRedisplay();
        break;
    case 'l':
        light_switch2=!light_switch2;
        //light0();
        glutPostRedisplay();
        break;



    case 'f':
        eyeZ++;
        //lookZ++;
        break;
    case 'g':
        eyeZ--;
        //lookZ--;
        break;
    case 'w':
        eyeY++;
        lookY++;
        break;
    case 's':
        eyeY--;
        lookY--;
        break;

    case 'd':
        eyeX++;
        lookX++;
        break;
    case 'a':
        eyeX--;
        lookX--;
        break;

    case 'z':
        scaleX+=0.3;
        scaleY+=0.3;
        scaleZ+=0.3;
        break;
    case 'x':
        scaleX-=0.3;
        scaleY-=0.3;
        scaleZ-=0.3;
        break;
    case 'b':
        bv = !bv;
        b_swap();
        break;
    case ';':
        frotate = !frotate;
        // uRotate = false;
        //axis_x=0.0;
        //axis_y=1.0;

        break;

    case '.': // right
        if(khelna_switch==0)
        {
            khelna_ang = -30;
            khelna_switch=1;
        }
        else if(khelna_switch==1)
        {
            khelna_ang = 0;
            khelna_switch=0;
        }


        break;
    case ',': // left

         if(khelna_switch==0)
        {
            khelna_ang = 30;
            khelna_switch=2;
        }
        else if(khelna_switch==2)
        {
            khelna_ang = 0;
            khelna_switch=0;
        }

        break;
    case '[':
        if (agun_switch ==0)
        {
            agun_switch =1;
        }
        else{
            agun_switch = 0;
        }
        break;

    case ']':
        if (rotating_switch_for_store2 ==0 || rotating_switch_for_store2 ==-1)
        {
            rotating_switch_for_store2 =1;
        }
        else{
            rotating_switch_for_store2 = 0;
        }
        break;

    case '/':
        if (fence_gate_switch ==0 || fence_gate_switch ==-1)
        {
            fence_gate_switch =1;
        }
        else{
            fence_gate_switch = 0;
        }
        break;



    case 27:	// Escape key
        exit(1);

    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += .1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }
     if (frotate == true)
    {
        ftheta -= .1;
       // if(ftheta > 360.0)
         //   ftheta -= 360.0*floor(ftheta/360.0);
    }

    if (uRotate == true)
    {
        alpha += .1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (rotating_switch_for_store2 == 1)
    {
        if(rotatingVariableForStore2 >= -90 && rotatingVariableForStore2 <=1){
            rotatingVariableForStore2 -= .1;
        }

    }
     if (rotating_switch_for_store2 == 0)
    {
        if(rotatingVariableForStore2 <= 0 && rotatingVariableForStore2 >= -91){
            rotatingVariableForStore2 += .1;
        }

    }

    if (fence_gate_switch == 1)
    {
        if(fence_gate_slide <=30 && fence_gate_slide >=-1){
            fence_gate_slide += .1;
        }

    }
     if (fence_gate_switch == 0)
    {
        if(fence_gate_slide <= 31 && fence_gate_slide >= 0){
            fence_gate_slide -= .1;
        }

    }
    glutPostRedisplay();



}

//static void idle(void)
//{
//    glutPostRedisplay();
//}

static void idle(void)
{
    glutPostRedisplay();
}
int id= 1;
void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID[id++]);
    glBindTexture(GL_TEXTURE_2D, ID[id-1]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[id-1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main (int argc, char **argv)
{
   glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // glutInitWindowSize(900,900);
    //glutInitWindowPosition(10,10);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");

    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\fire.bmp"); /// 1
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\grass.bmp"); /// 2
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\brick.bmp"); /// 3
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\stall.bmp"); /// 4
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\akash.bmp"); /// 5
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\fire2.bmp"); /// 6
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\chips.bmp"); /// 7
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\book.bmp"); /// 8
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\vending.bmp"); /// 9
    LoadTexture("C:\\Users\\faias\\Desktop\\Cse 4-2\\Computer Graphics\\Lab\\village fair\\grill.bmp"); /// 10



    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light0();
    //light1();
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutIdleFunc(idle);
    glutIdleFunc(animate);
    glutMainLoop();

    return EXIT_SUCCESS;
}

