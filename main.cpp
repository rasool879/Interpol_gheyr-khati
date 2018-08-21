#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
using namespace std ;
class Interpolate2d    // class for interpolate 2d Points with serface equation
{
public:
    double ** points;
    double *array;
    double *x_y;
    unsigned int matHeight,matWidth; // variable that show number of row and column
    void open_file( string ipolmatfileName)  // read content of a text file and store to 2d points
    {                                        // content are double number with n line and 3 column beacause in each line fuction get x ,y and q
        ifstream in(ipolmatfileName); // get direction of file
        string str;
        vector<string> vecOfStrs;
        if(!in)
            cout << "file not found\n";
        while(getline(in,str)){       // find number of lines in text file
            if(str.size() > 0)
                vecOfStrs.push_back(str);
        }
        unsigned int count = 1;
        for( unsigned int i = 0; i <vecOfStrs[0].size(); i++){ // find number of columns in text file
            if((vecOfStrs[0])[i] == ' ')
                count++;
        }
        matWidth=vecOfStrs.size();
        matHeight=count;
        points = (double **)malloc( matWidth * sizeof(double *));
        for ( unsigned int i=0; i<vecOfStrs.size(); i++)
        {
            points[i] = (double *)malloc(matHeight * sizeof(double));
        }
        cout << "lines: " << vecOfStrs.size() << '\n';
        cout << "columns: " << count  <<endl;
        ifstream input(ipolmatfileName);
        for(unsigned int i = 0; i < vecOfStrs.size() ; ++i)
        {
            for( unsigned int j =0; j < count ; ++j)
            {
                input >> points[i][j];
            }
        }
        in.close();
    }
public:
    double min_x,max_x,max_y,min_y;
    typedef struct // creat struct that store x,y and q from input text file
    {
        double x;
        double y;
        double q;
        //int m;
    }Points;
    Points *info;   // creat pointer of struct that keep information of points (x,y,q)
    Points* noghat(void)  // to transfer content of points to struct info till access easilyy to x,y,q
    {
        info=(Points *)malloc(matWidth*sizeof(Points));
        for( unsigned int i=0;i<matWidth;i++)
        {
            int j=0,k=1,u=2;
            info[i].x=points[i][j];
            info[i].y=points[i][k];
            info[i].q=points[i][u];
            cout <<info[i].x<< " "<<info[i].y<<" "<<info[i].q<<endl;
        }
        return info;
    }
    double Max_X(void) // find maximum of value x
    {
        double *info2;
        info2= (double *)malloc(sizeof(double)*matWidth);// creat info2 copy array of info for sorting data
        for(unsigned int j=0;j<matWidth;j++)
        {
            info2[j]=info[j].x;
        }
        max_x=*std::max_element(info2,info2+matWidth);
        cout <<"Max X is : " <<max_x <<endl;
        return max_x;   // return maximum of value x
    }
    // remember to creat info2 for each function //////////////
    double Min_X(void)  //find minimum of value x
    {
        double *info2;
        info2= (double *)malloc(sizeof(double)*matWidth);
        for(unsigned int j=0;j<matWidth;j++)
        {
            info2[j]=info[j].x;
        }
        min_x=*std::min_element(info2,info2+matWidth);
        cout <<"Min X is : " <<min_x <<endl;
        return min_x;  //return minimum of  value X
    }
    double Max_Y(void) //find maximum value of y
    {
        double *info2;
        info2= (double *)malloc(sizeof(double)*matWidth);
        //Points info[matWidth];
        for( unsigned int j=0;j<matWidth;j++)
        {
            info2[j]=info[j].y;
        }
        max_y=*std::max_element(info2,info2+matWidth);
        cout <<"Max Y is : " <<max_y <<endl;
        return max_y;
    }
    double Min_y(void)  // find minimum value of y
    {
        double *info2;
        info2= (double *)malloc(sizeof(double)*matWidth);
        //Points info[matWidth];
        for( unsigned int j=0;j<matWidth;j++)
        {
            info2[j]=info[j].y;
        }
        min_y=*std::min_element(info2,info2+matWidth);
        cout << "Min Y is : " <<min_y <<endl;
        return min_y;      //return minimum value of Y
    }
    double * distance(double x,double y) //function to find 4 points around the new points with least distance
    {
        double q,X,Y;
        double *Sort_,R,*Sort2_,*store_q,*store_x,*store_y;  // Sort2_ is copy of Sort_ to keep value
        Sort_=(double *)malloc(sizeof(double)*matWidth); // to keep distance of all variable from the new point
        Sort2_=(double *)malloc(sizeof(double)*matWidth);// copy of Sort_ for sorting data
        store_q=(double *)malloc(sizeof(double)*matWidth);
        array=(double *)malloc(sizeof(double)*10); //to keep x,y,q of closet points around the new point
        store_x=(double *)malloc(sizeof(double)*matWidth);
        store_y=(double *)malloc(sizeof(double)*matWidth);
        for(unsigned int i=0;i<matWidth;i++)
        {
            R=sqrt((x-info[i].x)*(x-info[i].x) +(y-info[i].y)*(y-info[i].y));
            Sort_[i]=R;
        }
        for(unsigned int i=0;i<matWidth;i++)
        {
            Sort2_[i]=Sort_[i];
        }
        for(unsigned int i=0;i<matWidth;i++)
        {
            // cout << "variable without sort are : "<< Sort_[i]<< " "<<endl;
        }
        sort(Sort2_,Sort2_+matWidth);  // sort number of array Sort2_
        for (size_t i = 0; i != matWidth; ++i)
        {
            //cout << Sort2_[i] << " ";
        }
        int flag,count;
        flag=0;    count=1;
        for(unsigned int i=0;i<matWidth;i++) //find specifications of 4 points around the new points with comparing distance
        {
            for(unsigned int j=0;j<matWidth;j++)
            {
                if(fabs(Sort2_[i]-Sort_[j])<0.0000001)   //Sort2_[i]==Sort_[j]
                {
                    double l;
                    flag++;
                    store_q[i]=info[j].q;
                    q=store_q[i];
                    store_x[i]=info[j].x;
                    X=store_x[i];
                    store_y[i]=info[j].y;
                    Y=store_y[i];
                    Sort_[j]=Sort_[j]-((0.001)*count);
                    count++;
                    l=Sort_[j];
                    break;
                }

            }
            if(flag==4)  // just 4 points information we need stored in array
            {
                break;
            }
        }
        for(int i=0;i<4;i++) // 4 number are q with least distance from the new point stored in array
        {
            array[i]=store_q[i];
        }
        int h;
        h=0;
        for(int i=4;i<7;i++) // 3 number are x with least distance from the new point stored in array
        {
            array[i]=store_x[h];
            h++;
        }
        int g;
        g=0;
        for(int i=7;i<10;i++) //3 number are y with least distance from the new point stored in array
        {
            array[i]=store_y[g];
            g++;
        }
        //cout << "This is content of Array :: -------------  ";
        for(int i=0;i<10;i++)
        {
            //cout <<array[i] << " ";
        }
        //cout <<endl;
        return array;
    }
    double Serface(double x,double y)  // seface equation that interpolate points
    {
        double *ans,a,b,c,x1,x2,x3,y1,y2,y3,q1,q2,q3;
        double result,xi,yi,qi,xj,yj,qj;
        ans=(double *)malloc(sizeof(double)*10);
        for(int i=0;i<10;i++)
        {
            ans[i]=array[i];
        }
        x1=ans[4];   x2=ans[5];  x3=ans[6];
        y1=ans[7];   y2=ans[8];    y3=ans[9];
        q1=ans[0];   q2=ans[1];    q3=ans[2];
        xi=x2-x1;    yi=y2-y1;     qi=q2-q1;
        xj=x3-x1;    yj=y3-y1;     qj=q3-q1;
        a=(qj*yi)-(qi*yj);
        b=(-1)*((qj*xi)-(qi*xj));
        c=(yj*xi)-(xj*yi);
        if(c==0)
        {
            result=78; // WHY c==0 ?  //find location c==0
        }
        else
        {
            result=((c*q1)+(b*y1)-(b*y)+(a*x1)-(a*x))/c;
        }
        return result;
    }
};
int main(int argc, char** argv) {
    double result;
    string name;
    name="test.txt";  //give name of file that you want to read
    Interpolate2d Test;  //creat class Interpolate2d Test
    Test.open_file(name);  // open and read from the file
    Test.noghat();
    Test.Max_X();
    Test.Min_X();
    Test.Max_Y();
    Test.Min_y();
    int p,q,a,stepx,stepy;
    double Precision;  // means number of pixcel that you want to interpolate
    Precision=0.1;
    p=1;  q=1;  a=1;
    stepx=(Test.max_x-Test.min_x)/Precision;
    stepy=(Test.max_y-Test.min_y)/Precision;
    ofstream myfile;
    myfile.open ("example.txt");
    for(int i=0;i<stepx;i++)
    {
        for(int j=0;j<stepy;j++)
        {
            double x,y;
            x=Test.min_x+(Precision*q);
            y=Test.min_y+(Precision*p);
            q++;
            a++;
            Test.distance(x,y);
            result=Test.Serface(x,y);
            myfile << result<< " " ;
        }
        myfile <<endl;
        p++;
        q=1;
    }
    myfile.close();
    return 0;
}
