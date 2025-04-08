#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int cHP(int &HP){
    if (HP<0){
        HP=0;
    }
    if (HP>666){
        HP=666;
    }
    return HP;
}
int cEXP(int &EXP){
    if (EXP<0){
        EXP=0;
    }
    if (EXP>600)
    {
        EXP=600;
    }
    return EXP;
}
int cM(int &M){
    if (M<0){
        M=0;
    }
    if (M>3000){
        M=3000;
    }
    return M;
}
// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    if(e1<0||e1>99){
    return -99;
}
if (exp1<0){
    exp1=0;
}
if (exp2<0){
    exp2=0;
}
if (exp1>600){
    exp1=600;
}
if (exp2>600){
    exp2=600;
}
float a=exp1;
float b=exp2;
switch (e1) {
case 0: b = b + 29; break;
case 1: b = b + 45; break;
case 2: b = b + 75; break;
case 3: b = b + 29 + 45 + 75; break;
}

int D = e1 * 3 + exp1 * 7;
if(e1>=0&&e1<=3){
if (D % 2 == 0){
    a=a+D*1.0/200;
}
else
    a=a-D*1.0/100;
}
if(e1<=19&&e1>=4){

b=b+((e1*1.0/4)+19);
a=a-e1;
}
else if(e1<=49&&e1>=20){
b=b+((e1*1.0/9)+21);
a=a-e1;
}
else if(e1<=65&&e1>=50){
    a=a-e1;
    b=b+((e1*1.0/16)+17);
}
else if (e1<=79&&e1>=66){
b=b+((e1*1.0/4)+19);
exp2=b;
if(b>exp2){
 b=exp2+1;
}
else b=exp2;
if(b>200){
b=b+((e1*1.0/9)+21);
}
a=a-e1;
}
else if (e1<=99&&e1>=80){
    b=b+((e1*1.0/4)+19);
    exp2=b;
    if(b>exp2){
    b=exp2+1;
    }
    else b=exp2;
    b=b+((e1*1.0/9)+21);
    exp2=b;
    if(b>exp2){
    b=exp2+1;
    }
    else b=exp2;
    if(b>400){
b=b+((e1*1.0/16)+17);
exp2=b;
if(b>exp2){
    b=exp2+1;
}
else b=exp2;
 b=b+0.15*b;
    exp2=b;
    if(b>exp2){
        b=exp2+1;
    } else b=exp2;
    }
    a=a-e1;
}
if (a<0){
    a=0;
}
if (b<0){
    b=0;
}
if (a>600){
    a=600;
}
if(b>600){
b=600;
}
exp1=a;
exp2=b;
if(a>exp1){
    exp1=exp1+1;
}
if(b>exp2){
    exp2=exp2+1;
}
return exp1 + exp2;
}
// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
if(E2<0||E2>99){
    return -99;
}
if (HP1<0){
    HP1=0;
}
if (HP1>666){
    HP1=666;
}
if (EXP1<0){
    EXP1=0;
}
if (EXP1>600){
    EXP1=600;
}
if (M1<0){
    M1=0;
}
if (M1>3000){
    M1=3000;
}
float s=sqrt(EXP1);
int b=sqrt(EXP1);
int c;
if (abs(s-b)>abs(s-(b+1))){
c=(b+1)*(b+1);
}
else c=b*b;
float P1;
if (EXP1>=c){
    P1=100;
}
else P1=(((EXP1*1.0/c)+80)*1.0/123)*100;
if (E2%2!=0){
float coin=M1*0.5;
int pay=0;
float check1=HP1;
float check2=EXP1;
while(pay<=coin){
     if (coin==0){
        break;
    }
if (HP1<200){
check1=check1+0.3*check1;
M1=M1-150;
pay=pay+150;
}
else if (HP1>=200){
check1=check1+0.1*check1;
M1=M1-70;
pay=pay+70;
}
HP1=check1;
if (check1>HP1){
HP1=HP1+1;
}
else HP1=check1;
if (HP1>666){
    HP1=666;
}
if (HP1<0){
    HP1=0;
}
check1=HP1;
if (pay>coin){
    break;
}
if (EXP1<400){
M1=M1-200;
pay=pay+200;
}
else if (EXP1>=400){
    M1=M1-120;
    pay=pay+120;
}
check2=check2+0.13*check2;
EXP1=check2;
if (check2>EXP1){
    EXP1=EXP1+1;
}
else EXP1=check2;
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
check2=EXP1;
if (pay>coin){
    break;
}
if (EXP1<300){
    M1=M1-100;
    pay=pay+100;
}
else if (EXP1>=300){
    M1=M1-120;
    pay=pay+120;
}
check2=check2-0.1*check2;
EXP1=check2;
if (check2>EXP1){
    EXP1+=1;
}
else EXP1=check2;
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
check2=EXP1;
}
check1=check1-0.17*check1;
check2=check2+0.17*check2;
HP1=check1;
EXP1=check2;
if (check1>HP1){
    HP1=HP1+1;
}
else HP1=check1;
if (check2>EXP1){
    EXP1=EXP1+1;
}
else EXP1=check2;
if (HP1>666){
    HP1=666;
}
if (HP1<0){
    HP1=0;
}
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
}
else if (E2%2==0){
    float check1=HP1;
    float check2=EXP1;
if (HP1<200&&M1>0){
check1=check1+0.3*check1;
M1=M1-150;
}
else if (HP1>=200&&M1>0){
check1=check1+0.1*check1;
M1=M1-70;
}
HP1=check1;
if (check1>HP1){
HP1=HP1+1;
}
else HP1=check1;
if (HP1>666){
    HP1=666;
}
if (HP1<0){
    HP1=0;
}
check1=HP1;
if (EXP1<400&&M1>0){
M1=M1-200;
check2=0.13*EXP1+EXP1;
}
else if (EXP1>=400&&M1>0){
    M1=M1-120;
    check2=EXP1+0.13*EXP1;
}
EXP1=check2;
if (check2>EXP1){
    EXP1=EXP1+1;
}
else EXP1=check2;
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
check2=EXP1;
if (EXP1<300&&M1>0){
    M1=M1-100;
    check2=check2-0.1*check2;
}
else if (EXP1>=300&&M1>0){
    M1=M1-120;
    check2=check2-0.1*check2;
}
EXP1=check2;
if (check2>EXP1){
    EXP1+=1;
}
else EXP1=check2;
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
check2=EXP1;
check1=check1-0.17*check1;
check2=check2+0.17*check2;
HP1=check1;
EXP1=check2;
if(check1>HP1){
    HP1+=1;
}
else HP1=check1;
if (check2>EXP1){
    EXP1+=1;
}
else EXP1=check2;
if (HP1>666){
    HP1=666;
}
if (HP1<0){
    HP1=0;
}
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
}
float S=sqrt(EXP1);
int t=sqrt(EXP1);
int k;
float P2;
if (abs(S-t)>abs(S-t-1)){
    k=(t+1)*(t+1);
}else k=t*t;
if (EXP1>=k){
P2=100;
}
else P2=((EXP1*1.0/k)*1.0+80)/123*100;
int array[10]={32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
float P3;
if (E2>=0&&E2<=9){
P3=array[E2];
}
else if (E2>=10&&E2<=99){
int g,h,sum;
h=E2%10;
g=E2/10;
sum=g+h;
P3=array[sum%10];
}
float average;
float check6=HP1;
float check7=EXP1;
average=((P1+P2+P3)*1.0/3);
int p=average;
if (average>p){
    p=p+1;
}
else p=average;
if (p==100){
    check7=check7-0.25*check7;
}
else if(p<50){
check7=check7+0.15*check7;
check6=check6-0.15*check6;
}
else if (p>=50&&p<100){
    check7=check7+0.2*check7;
    check6=check6-0.1*check6;
}
HP1=check6;
EXP1=check7;
if (check7>EXP1){
EXP1=EXP1+1;
}
else EXP1=check7;
if (check6>HP1){
    HP1=HP1+1;
}
else HP1=check6;
if (HP1>666){
    HP1=666;
}
if (HP1<0){
    HP1=0;
}
if (EXP1>600){
    EXP1=600;
}
if (EXP1<0){
    EXP1=0;
}
if (M1<0){
    M1=0;
}
if (M1>3000){
    M1=3000;
}
return HP1 + EXP1 + M1;
}
// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    if (E3<0||E3>99){
    return -99;
}
HP1=cHP(HP1);
HP2=cHP(HP2);
EXP1=cEXP(EXP1);
EXP2=cEXP(EXP2);
int a[10][10];
    int count1=0;
    int count2=0;
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    float HP3=HP1;
    float HP4=HP2;
    float EXP3=EXP1;
    float EXP4=EXP2;
    for (int i=0;i<10;i++){
        for(int j=0;j<10;j++){
        a[i][j]=(E3*j+i*2)*(i-j);    
        }
    }
    for (int i=0;i<10;i++){
        for(int j=0;j<10;j++){
        if (a[i][j]>(E3*2)){
            count1++;
        }
        if (a[i][j]<(-E3)){
            count2++;
        }
        }
    }
   while (count1>9&&count1<100){
        b=count1/10;
       c=count1%10;
       count1=b+c;
   }
   while(count2>9&&count2<100){
       d=count2/10;
       e=count2%10;
       count2=d+e;
   }
int max=a[count1][count2];
if (count1<=count2){
for(int i=0;i<=count1;i++){
    if (a[count1-i][count2-i]>max){
       max=a[count1-i][count2-i];
    }
}
}
else if (count1>count2){
    for(int i=0;i<=count2;i++){
    if (a[count1-i][count2-i]>max){
       max=a[count1-i][count2-i];
    }
}
}
if (count1<=count2){
for(int i=0;i<(10-count2);i++){
    if (a[count1+i][count2+i]>max){
       max=a[count1+i][count2+i];
    }
}
}
else if (count1>count2){
    for(int i=0;i<(10-count1);i++){
    if (a[count1+i][count2+i]>max){
       max=a[count1+i][count2+i];
    }
}
}
if (count1<=count2){
for(int i=0;i<(10-count1);i++){
    if (a[count1+i][count2-i]>max){
       max=a[count1+i][count2-i];
    }
}
}
else if (count1>count2){
    for(int i=0;i<(10-count2);i++){
    if (a[count1-i][count2+i]>max){
       max=a[count1-i][count2+i];
    }
}
}
if (count1<=count2){
for(int i=0;i<(10-count2);i++){
    if (a[count1-i][count2+i]>max){
       max=a[count1-i][count2+i];
    }
}
}
else if (count1>count2){
    for(int i=0;i<(10-count1);i++){
    if (a[count1+i][count2-i]>max){
       max=a[count1+i][count2-i];
    }
}
}

if(abs(a[count1][count2])>max){
    EXP3=EXP3-0.12*EXP3;
    EXP4=EXP4-0.12*EXP4;
    HP3=HP3-0.10*HP3;
    HP4=HP4-0.10*HP4;
}
else if (abs(a[count1][count2])<=max){
    EXP3=EXP3+0.12*EXP3;
    EXP4=EXP4+0.12*EXP4;
    HP3=HP3+0.10*HP3;
    HP4=HP4+0.10*HP4;
}
EXP1=EXP3;
EXP2=EXP4;
HP1=HP3;
HP2=HP4;
if (EXP3>EXP1){
    EXP1=EXP1+1;
}
else EXP1=EXP3;
if (EXP4>EXP2){
    EXP2=EXP2+1;
}
else EXP2=EXP4;
if (HP3>HP1){
    HP1=HP1+1;
}
else HP1=HP3;
if (HP4>HP2){
    HP2=HP2+1;
}
else HP2=HP4;
EXP1=cEXP(EXP1);
EXP2=cEXP(EXP2);
HP1=cHP(HP1);
HP2=cHP(HP2);
if (abs(a[count1][count2])>max){
return a[count1][count2];
}
else return max;
}
// Task 4
int checkPassword(const char * s, const char * email) {
    string accout=email;
    string pass=s;
    char how=64;
    int check=0;
    for (int i=0;i<accout.length();i++){
        if (accout[i]==how){
            check=accout.length()-i;
            break;
        }
    }
string se=accout.substr(0,accout.length()-check);
if (se.length()==0){
    return -1;
}
if(pass.length()<8){
    return -1;
}
else if(pass.length()>20){
    return -2;
}
else if (pass.length()>=8&&pass.length()<=20){
for(int i=0;i<pass.length();i++){
  if (pass[i]==se[0]){
     for(int j=1;j<=pass.length()-i;j++){
    if (pass.substr(i,j)==se){
      return -(300+i);
    }
     }
  }
}
for(int i=0;i<pass.length()-2;i++){
if (pass[i]==pass[i+1]&&pass[i]==pass[i+2]){
    return -(400+i);
}
}
int count1=0;
for(int i=0;i<pass.length();i++){
    char q=33;char w=35;char e=36;char r=37;char t=64;
 if (pass[i]==q||pass[i]==w||pass[i]==e||pass[i]==r||pass[i]==t){
        count1++;
    }
}
for(int i=0;i<pass.length();i++){
    int count=0;
    for(int j=48;j<=57;j++){
        char c=j;
      if(pass[i]==c){
          count++;
       break;   
      }
      }
    for(int k=65;k<=90;k++){
        char p=k;
        if(pass[i]==p){
              count++;
            break;
        }
    }
    for(int h=97;h<=122;h++){
        char l=h;
        if(pass[i]==l){
              count++;
            break;
        }
    }
    char q=33;char w=35;char e=36;char r=37;char t=64;
    if (count1==0){
        return -5;
    }
    if (count==0){
    if (pass[i]!=q&&pass[i]!=w&&pass[i]!=e&&pass[i]!=r&&pass[i]!=t){
     return i;
    }
    }
}  
}
return -10;
}
// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    int count[1000];
for(int i=0;i<num_pwds;i++){
     count[i]=0;
    for (int j=0;j<num_pwds;j++){
        if (arr_pwds[i]==arr_pwds[j]){
            count[i]=count[i]+1;
        }
    }
}
  int  max=0;string s;
for(int i=0;i<num_pwds;i++){
    if (count[i]>max){
        max=count[i];
    }
}

for(int i=0;i<num_pwds;i++){
    if (count[i]==max){
        s=arr_pwds[i];
        break;
    }
}
 string se[10000];
 for(int i=0;i<num_pwds;i++){
     se[i]=arr_pwds[i];
 }
for(int i=0;i<num_pwds;i++){
    if (count[i]==max){
        if (se[i].length()>s.length()){
            s=se[i];
        }
    }
}
int g;
for(int i=0;i<num_pwds;i++){
    if (arr_pwds[i]==s){
        g=i;
        break;
    }
}
 return g;
}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////