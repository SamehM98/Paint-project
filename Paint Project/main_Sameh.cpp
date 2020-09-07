#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<bits/stdc++.h>
#include<vector>

//SAMEH MOHAMED 16100115


int click = 0;
int drag = 0;
int PhyWidth = 700;
int PhyHeight = 700;
int LogWidth = 100;
int LogHeight = 100;
int pk;
int MouseX = 50;
int MouseY = 50;
int centerX = LogWidth/2, centerY = LogHeight/2;
int activeColor = 6;
int buttonnumber=0;
char activebutton = 'z';
int fillstate = 0;
int waiting = 0;
int startX=0, startY=0, endX=0, endY = 0;
int fills = 0;
int colordrawer = 0;
int full = 0;
std:: stack <int> st;
int last = 0;

float colors [8][3] = {  {1.0,0.0,0.0} , {0.0,1.0,0.0} , {0.6,0.3,0}  , {1.0, 1.0, 0.0} , {1.0, 0.0, 1.0} , {0.4, 0.6, 1.0} , {0.0, 0.0, 0.0}  , {1.0, 1.0, 1.0}  };


int pens = -1;
int pointflag=0;
int shapes = -1;
int textcount = -1;
std:: string output ="";
std:: string strings[100];

int pencolors[100];
int textcolors[100];
std:: pair<int,int> textstart[100];
std:: pair<int,int> starters [5000];
std:: pair<int,int> ends [5000];
std:: pair<int,int> scheme [5000];
std:: vector<std:: vector<int> > vecx;
std:: vector<std:: vector<int> > vecy;
std:: vector<int> tempx;
std:: vector<int> tempy;

int types[5000];


void init2D()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,LogWidth,0.0,LogHeight);
}

void mouseClick(int btn, int state, int x, int y)
{

   if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        click = 1;
        MouseX = x;
        MouseX=0.5+1.0*MouseX*LogWidth/PhyWidth;
        MouseY = PhyHeight- y;
        MouseY=0.5+1.0*MouseY*LogHeight/PhyHeight;

        if(MouseX >= 3 && MouseX <= 94 && MouseY >= 3 && MouseY <= 74 && (buttonnumber == 1 || buttonnumber == 2 || buttonnumber == 3))
        {
            pointflag = 0;
            st.push(1);
            shapes++;
            waiting = 1;

            starters[shapes].first = MouseX;
            starters[shapes].second = MouseY;

            ends[shapes].first = MouseX;
            ends[shapes].second = MouseY;

            scheme[shapes].first = fillstate;
            scheme[shapes].second = activeColor;

            types[shapes] = buttonnumber;



        }
        else if(MouseX >= 3 && MouseX <= 94 && MouseY >= 3 && MouseY <= 74 && buttonnumber == 6)
        {
            pointflag = 0;
            st.push(2);
            textcount++;
            output = "";

            textcolors[textcount] = activeColor;
            textstart[textcount].first = MouseX;
            textstart[textcount].second = MouseY;
        }
        else if(MouseX >= 3 && MouseX <= 94 && MouseY >= 3 && MouseY <= 74 && buttonnumber == 5)
        {
            st.push(3);
            tempx.clear();
            tempy.clear();

            tempx.push_back(MouseX);
            tempy.push_back(MouseY);
            pointflag = 1;
            pens++;
            vecx.push_back(tempx);
            vecy.push_back(tempy);
            pencolors[pens] = activeColor;

        }
        else if( MouseX >= 25 && MouseX <= 25+8 && MouseY >= 78 && MouseY <= 82 && !st.empty())
        {
            pointflag = 0;
            last = st.top();
            st.pop();

            if(last == 1 && shapes > -1)
            {
                shapes--;
            }

            else if(last == 2 && textcount > -1)
            {
                strings[textcount] = "";
                textcount--;
            }
            else if(last == 3 && pens > -1)
            {

                vecx.erase (vecx.begin()+pens);
                vecy.erase (vecy.begin()+pens);
                pens--;
            }

        }

        else
        {
            waiting = 0;
            pointflag=0;
        }

    }
    else
    {
        waiting = 0;
        pointflag=0;
    }


    glutPostRedisplay();

}

void passiveMouse (int x,int y){
    click = 0;
    MouseX = x;
    MouseX=0.5+1.0*MouseX*LogWidth/PhyWidth;
    MouseY = PhyHeight - y;
    MouseY=0.5+1.0*MouseY*LogHeight/PhyHeight;

    glutPostRedisplay();

}

void Keyboard(unsigned char key, int x, int y)
 {
     if(buttonnumber == 6)
     {
         if(key == 8 && output.size())
         {
             full = 0;
             output = output.substr(0 , output.size() - 1);
             strings[textcount] = output;
         }

        else if(!full)
        {
           output+=key;
            strings[textcount] = output;
        }

     }

      glutPostRedisplay();
 }


void draw1(){
   glColor3f(0.0f, 0.0f, 0.0f);

   glBegin(GL_POLYGON); //draw outer frame black

      glVertex2f(2, 2);
      glVertex2f(95, 2);
      glVertex2f(95, 75);
      glVertex2f(2, 75);

   glEnd();

   glColor3f(1.0f, 1.0f, 1.0f);

   glBegin(GL_POLYGON); //draw inner frame white 3 to 94 and 3 to 74

      glVertex2f(3, 3);
      glVertex2f(94, 3);
      glVertex2f(94, 74);
      glVertex2f(3, 74);


   glEnd();

   int stpos = 55;


   for(int i=0;i<8;i++) //colors: 55, 60, etc. Square of  3
   {


        glColor3f(0.0f, 0.0f, 0.0f);

            glBegin(GL_POLYGON); //draw inner frame white

            glVertex2f(stpos-0.5, 82.5);
            glVertex2f(stpos+3.5, 82.5);
            glVertex2f(stpos+3.5, 86.5);
            glVertex2f(stpos-0.5, 86.5);


        glEnd();

       if(i==0)
       glColor3f(1.0f, 0.0f, 0.0f);
       else if(i==1)
       glColor3f(0.0f, 1.0f, 0.0f);
       else if(i==2)
       glColor3f(0.6f, 0.3f, 0.0f);
       else if(i==3)
       glColor3f(1.0f, 1.0f, 0.0f);

       else if(i==4)
       glColor3f(1.0f, 0.0f, 1.0f);
       else if(i==5)
       glColor3f(0.4f, 0.6f, 1.0f);
       else if(i==6)
       glColor3f(0.0f, 0.0f, 0.0f);
       else if(i==7)
       glColor3f(1.0f, 1.0f, 1.0f);






       glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(stpos, 83);
        glVertex2f(stpos+3, 83);
        glVertex2f(stpos+3, 86);
        glVertex2f(stpos, 86);


        glEnd();



        stpos+=5;

   }

}

void MMouse (int x,int y){

    click = 0;
    MouseX = x;
    MouseX=0.5+1.0*MouseX*LogWidth/PhyWidth;
    MouseY = PhyHeight - y;
    MouseY=0.5+1.0*MouseY*LogHeight/PhyHeight;

    if(waiting == 1 && MouseX >= 3 && MouseX <= 94 && MouseY >= 3 && MouseY <= 74 && (buttonnumber == 1 || buttonnumber == 2 || buttonnumber == 3))
    {
       // printf("hi");
        ends[shapes].first = MouseX;
        ends[shapes].second = MouseY;
    }

    else if(MouseX >= 3 && MouseX <= 94 && MouseY >= 3 && MouseY <= 74 && buttonnumber == 5 && pointflag == 1)
        {
            vecx[pens].push_back(MouseX);
            vecy[pens].push_back(MouseY);
            //pencolors[pens] = activeColor;
        }

    glutPostRedisplay();

}

int color() //83 to 86, 55 and size of 3
{
    if(MouseY >= 83 && MouseY <= 86 && click == 1)
    {
        if(MouseX >= 55 && MouseX <= 55+3)
        return 0;
        else if(MouseX >= 60 && MouseX <= 60+3)
        return 1;
        else if(MouseX >= 65 && MouseX <= 65+3)
        return 2;
        else if(MouseX >= 70 && MouseX <= 70+3)
        return 3;
        else if(MouseX >= 75 && MouseX <= 75+3)
        return 4;
        else if(MouseX >= 80 && MouseX <= 80+3)
        return 5;
        else if(MouseX >= 85 && MouseX <= 85+3)
        return 6;
        else if(MouseX >= 90 && MouseX <= 90+3)
        return 7;
    }

    return 8;
}


void draw2()
{
    int stpos = 5;

    for(int i=1;i<=4;i++)//5, 15, 25, etc. width of 8 and height of 4 88 to 92
    {
        glColor3f(0.0,0.0,0.0);

        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(stpos-0.5, 87.5);
        glVertex2f(stpos+8.5, 87.5);
        glVertex2f(stpos+8.5, 92.5);
        glVertex2f(stpos-0.5, 92.5);


        glEnd();


        if(MouseX >= stpos && MouseX <= stpos+8 && MouseY >= 88 && MouseY <= 92 && click == 0)
        glColor3f(0.0,1.0,0.0);
        else if(fillstate == 1 && i == 4)
        glColor3f(0.8,0.8,0.8);
        else if(buttonnumber == i)
        glColor3f(0.8,0.8,0.8);
        else
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(stpos, 88);
        glVertex2f(stpos+8, 88);
        glVertex2f(stpos+8, 92);
        glVertex2f(stpos, 92);


        glEnd();




        glColor3f(0.0,0.0,0.0);
        char st[20];

        if(i == 1)
        {
            char str[] = "Line";
            strcpy(st,str);
        }

        else if(i == 2)
        {
            char str[] = "Rect";
            strcpy(st,str);
        }

        else if(i == 3)
        {
            char str[] = "Circle";
            strcpy(st,str);
        }
        else if(i == 4)
        {
            char str[] = "Fill";
            strcpy(st,str);
        }




        glRasterPos2d(stpos+1,90);

        for (int i=0;i<strlen(st);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,st[i]);


        glFlush();

        stpos+=10;



    }

    stpos = 5;


    for(int i=5;i<=8;i++)//5, 15, 25, etc. width of 8 and height of 4 78 to 82
    {
        glColor3f(0.0,0.0,0.0);

        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(stpos-0.5, 77.5);
        glVertex2f(stpos+8.5, 77.5);
        glVertex2f(stpos+8.5, 82.5);
        glVertex2f(stpos-0.5, 82.5);


        glEnd();


        if(MouseX >= stpos && MouseX <= stpos+8 && MouseY >= 78 && MouseY <= 82 && click == 0)
        glColor3f(0.0,1.0,0.0);
        else if(fillstate == 0 && i == 8)
        glColor3f(0.8,0.8,0.8);
        else if(buttonnumber == i)
        glColor3f(0.8,0.8,0.8);
        else
        glColor3f(1.0,1.0,1.0);


        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(stpos, 78);
        glVertex2f(stpos+8, 78);
        glVertex2f(stpos+8, 82);
        glVertex2f(stpos, 82);


        glEnd();




        glColor3f(0.0,0.0,0.0);
        char st[20];

        if(i == 5)
        {
            char str[] = "Pen";
            strcpy(st,str);
        }

        else if(i == 6)
        {
            char str[] = "Text";
            strcpy(st,str);
        }

        else if(i == 7)
        {
            char str[] = "Undo";
            strcpy(st,str);
        }
        else if(i == 8)
        {
            char str[] = "No Fill";
            strcpy(st,str);
        }




        glRasterPos2d(stpos+1,80);

        for (int i=0;i<strlen(st);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,st[i]);


        glFlush();

        stpos+=10;



    }


}

void plot (int x , int y)
{

        glBegin(GL_POINTS);
        glVertex2i(x , y);
        glEnd();
}



void btnnumber()
{

    if(MouseY >= 88 && MouseY <= 92 && click == 1)
    {
        if(MouseX >= 5 && MouseX <= 5+8)
        buttonnumber = 1;
        else if(MouseX >= 15 && MouseX <= 15+8)
        buttonnumber = 2;
        else if(MouseX >= 25 && MouseX <= 25+8)
        buttonnumber = 3;
    }
    else if(MouseY >= 78 && MouseY <= 82 && click == 1)
    {
        if(MouseX >= 5 && MouseX <= 5+8)
        buttonnumber = 5;
        else if(MouseX >= 15 && MouseX <= 15+8)
        buttonnumber = 6;
        else if(MouseX >= 25 && MouseX <= 25+8)
        {
            buttonnumber = 7;
        }

    }
}

void rectdraw(int startX , int startY, int endX, int endY)
{
    int w , l;

    if(endX >= startX && endY >= startY)
    {
        l = endY-startY;
        w = endX-startX;

        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(startX+w,startY);
        glVertex2f(endX, endY);
        glVertex2f(startX, endY);


        glEnd();
    }

    else if(startX >= endX && startY >= endY)
    {
        l = startY - endY;
        w = startX - startX;

        glBegin(GL_POLYGON);

        glVertex2f(startX, startY);
        glVertex2f(startX,endY);
        glVertex2f(endX, endY);
        glVertex2f(endX, startY);

        glEnd();
    }

    else if(endX <= startX && endY >= startY)
    {
        l = endY-startY;
        w = startX-endX;

        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(startX,endY);
        glVertex2f(endX, endY);
        glVertex2f(endX, startY);


        glEnd();
    }
    else if(endX >= startX && startY >= endY)
    {
        glBegin(GL_POLYGON); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(endX,startY);
        glVertex2f(endX, endY);
        glVertex2f(startX, endY);


        glEnd();
    }


}


void rectempty(int startX , int startY, int endX, int endY)
{
    int w , l;

    if(endX >= startX && endY >= startY)
    {
        l = endY-startY;
        w = endX-startX;

        glBegin(GL_LINE_LOOP); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(startX+w,startY);
        glVertex2f(endX, endY);
        glVertex2f(startX, endY);


        glEnd();
    }

    else if(startX >= endX && startY >= endY)
    {
        l = startY - endY;
        w = startX - startX;

        glBegin(GL_LINE_LOOP);

        glVertex2f(startX, startY);
        glVertex2f(startX,endY);
        glVertex2f(endX, endY);
        glVertex2f(endX, startY);

        glEnd();
    }

    else if(endX <= startX && endY >= startY)
    {
        l = endY-startY;
        w = startX-endX;

        glBegin(GL_LINE_LOOP); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(startX,endY);
        glVertex2f(endX, endY);
        glVertex2f(endX, startY);


        glEnd();
    }
    else if(endX >= startX && startY >= endY)
    {
        glBegin(GL_LINE_LOOP); //draw inner frame white

        glVertex2f(startX, startY);
        glVertex2f(endX,startY);
        glVertex2f(endX, endY);
        glVertex2f(startX, endY);


        glEnd();
    }


}




void circle(int x1,int y1,int x2 , int y2)
{
        int r = (int)sqrt((abs(x2-x1))*(abs(x2-x1))+(abs(y2-y1))*(abs(y2-y1)));

        if(x1+r>94)
        r=94-x1;
        if(x1-r<3)
        r=x1-3;
        if(y1+r>74)
        r=74-y1;
        if(y1-r<3)
        r=y1-3;


        int x = 0, y=r;

        int num_segments=50;
        glBegin(GL_POLYGON);
        for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + x1, y + y1);//output vertex
        }
        glEnd();
}


void filler()
{

    if(MouseY >= 78 && MouseY <= 82 && click == 1 && MouseX >= 35 && MouseX <= 35+8)
        fillstate = 0;
    else if(MouseY >= 88 && MouseY <= 92 && click == 1 && MouseX >= 35 && MouseX <= 35+8)
        fillstate = 1;


}

void dl(int x1,int y1,int x2 , int y2)
{
    glBegin(GL_LINE_LOOP);

    glVertex2f(x1,y1);
    glVertex2f(x2,y2);

    glEnd();
}

 void printsome(int x, int y, std:: string op)
 {
     full = 0;
     glRasterPos2d(x,y);
     int n = op.size();

    //if(x+n > 94)
     //   return;

     for(int i=0;i<n;i++)
     {
         if(float(x) + (float(i)*1.75) > 94.0)
         {
             full = 1;
             return;
         }

        full = 0;
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , op[i]);
     }

 }

 void circle2(int x1,int y1,int x2 , int y2)
{
        int r = (int)sqrt((abs(x2-x1))*(abs(x2-x1))+(abs(y2-y1))*(abs(y2-y1)));

        if(x1+r>94)
        r=94-x1;
        if(x1-r<3)
        r=x1-3;
        if(y1+r>74)
        r=74-y1;
        if(y1-r<3)
        r=y1-3;


        int x = 0, y=r;

        int num_segments=50;
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + x1, y + y1);//output vertex
        }
        glEnd();
}

 void pen(int x)
 {

     int n = vecx[x].size();

     for(int i=0;i<n;i++)
     plot(vecx[x][i] , vecy[x][i]);



 }


void drawshapes()
{
    for(int i=0;i<=shapes;i++)
    {
        glColor3f(colors[scheme[i].second][0] , colors[scheme[i].second][1] ,colors[scheme[i].second][2]);

        if(types[i] == 2)
        {
            if(scheme[i].first)
            rectdraw(starters[i].first , starters[i].second , ends[i].first , ends[i].second);
            else
            rectempty(starters[i].first , starters[i].second , ends[i].first , ends[i].second);
        }
        else if(types[i] == 3)
        {
            if(scheme[i].first)
            circle(starters[i].first , starters[i].second , ends[i].first , ends[i].second);
            else
            circle2(starters[i].first , starters[i].second , ends[i].first , ends[i].second);
        }
        else if(types[i] == 1)
           dl(starters[i].first , starters[i].second , ends[i].first , ends[i].second);
    }

    for(int i=0;i<=textcount;i++)
    {
        glColor3f(colors[textcolors[i]][0] , colors[textcolors[i]][1] ,colors[textcolors[i]][2]);
        printsome(textstart[i].first , textstart[i].second, strings[i]);
    }

    for(int i=0;i<=pens;i++)
    {
        glColor3f(colors[pencolors[i]][0] , colors[pencolors[i]][1] , colors[pencolors[i]][2] );
        pen(i);
    }




}




void Display()
{

    glClear( GL_COLOR_BUFFER_BIT);
    draw1();
    draw2();
    btnnumber();
    filler();
    if(color() != 8)
    activeColor = color();


    drawshapes();

    glutSwapBuffers();
    glFlush();




}
int main (int argc , char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(PhyWidth,PhyHeight);
    glutCreateWindow("Paint");
    init2D();


    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse);
    glutMotionFunc(MMouse);
    glutKeyboardFunc(Keyboard);

    glutDisplayFunc(Display);
    glutMainLoop();
}





