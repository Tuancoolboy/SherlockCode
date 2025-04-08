/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;
class BaseItem;
enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };
class Watson;
class Map;
class MapElement {
    friend class TestStudyInPink;
protected:
    ElementType type;
public:
    MapElement(ElementType in_type):type(in_type){}
    virtual ~MapElement(){}
    virtual ElementType getType() const{
        return type;
    }
};
class Path : public MapElement {
    friend class TestStudyInPink;
    friend class Map;
public:
    Path() : MapElement(PATH) {}
};

class Wall : public MapElement {
    friend class TestStudyInPink;
public:
    Wall():MapElement(WALL){}
};

class FakeWall : public MapElement {
    friend class TestStudyInPink;
    private:
    int req_exp;
public:
FakeWall(int in_req_exp):MapElement(FAKE_WALL){
    req_exp=in_req_exp;
}
int getReqExp() const{
    return req_exp;
}
};
class Position {
    friend class TestStudyInPink;
private:
    int r, c;
public:
   
static const Position npos;
Position(int r=0, int c=0){
        this->r=r;
        this->c=c;
    }

Position(const string & str_pos){
string k,q;
int vitri;
for(int i=0;i<str_pos.size();i++){
    if (str_pos[i]==44){
        vitri=i;
        break;
    } 
}
k=str_pos.substr(1,vitri-1);
q=str_pos.substr(vitri+1,str_pos.size()-vitri-2);
r=stoi(k);
c=stoi(q);
    }
    int getRow() const{
    return r;
    }
    int getCol() const{
        return c;
    }
    void setRow(int r){
        this->r=r;
    }
    void setCol(int c){
        this->c=c;
    }
    string str() const{
 return "(" + to_string(r) + "," + to_string(c) + ")";
    }
    bool isEqual(int in_r, int in_c) const{
         return (r == in_r && c == in_c);
    }
    bool isEqual(Position obj){
        int row=obj.getRow();
        int col=obj.getCol();
        return (r==row&&c==col);
    }
};
class MovingObject {
    friend class TestStudyInPink;
protected:
    int index;
    Position pos;
    Map * map;
    string name;
public:
    MovingObject(int index, const Position pos, Map * map, const string & name=""){
        this->index=index;
        this->name=name;
        this->map=map;
        this->pos=pos;
    }
    int getindex(){
        return index;
    }
   string getName(){
       return name;
   }
   virtual int getindex() const=0;
virtual BaseItem *getitem() const =0;
    virtual ~MovingObject(){}
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual int getexp() const =0;
    virtual int gethp() const=0;
    virtual void sethp(int hp) =0;
    virtual void setexp(int exp)  =0;
virtual Position getCurrentPosition() const=0;
};
class Map {
    friend class TestStudyInPink;
private:
    int num_rows;
    int num_cols;
    MapElement ***map;
     int num_walls;
    Position *array_walls;
public:
    Map(int num_rows, int num_cols, int num_walls,Position *array_walls, int num_fake_walls, Position *array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols),num_walls(num_walls),array_walls(array_walls){
        map = new MapElement **[num_rows];
        for (int i = 0; i < num_rows; ++i) {
            map[i] = new MapElement *[num_cols];
            for (int j = 0; j < num_cols; ++j) {
                map[i][j] = new Path();
            }
        }
     for(int i=0;i<num_walls;i++){
        map[array_walls[i].getRow()][array_walls[i].getCol()] = new Wall();
        
 }   
      for(int i=0;i<num_fake_walls;i++){
          int sum=(array_fake_walls[i].getRow() * 257 + array_fake_walls[i].getCol() * 139 + 89)%900 + 1;
        map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = new FakeWall(sum);
     }
     for(int i=0;i<num_fake_walls;i++){
         for(int j=0;j<num_walls;j++){
             if ( map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()]->getType()==map[array_walls[j].getRow()][array_walls[j].getCol()]->getType()){
                  map[array_fake_walls[i].getRow()][array_fake_walls[i].getCol()] = new Wall();
             }
         }
     }
     
    }
    
    ~Map() {
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                delete map[i][j];
            }
            delete[] map[i];
        }
        delete[] map;
    }
    int getrow(){
        return num_rows;
    }
    int getcol(){
        return num_cols;
    }
    bool isValid (const Position & pos , MovingObject * mv_obj) {
  int c,r;
       c=pos.getCol();
       r=pos.getRow();
       
       if ((pos.getCol()==-1)||(pos.getRow()==-1)){
           return false;
       }
       if(map[r][c]->getType()==0){
           return true;
       }
       else if (map[r][c]->getType()==1){
           return false;
       } else if(map[r][c]->getType()==2){
          if (mv_obj->getName()=="Sherlock"||mv_obj->getName()=="Criminal"){
              return true;
          }
          else if (mv_obj->getName()=="Watson"){
           int calculate=(r * 257 + c * 139 + 89)%900 + 1;  
              FakeWall fakewall(calculate);
              fakewall.getReqExp();
              
        if (mv_obj->getexp()>fakewall.getReqExp()){
            return true;
        }
        else return false;
          }
       }
       return false;
    }
    bool check1(int r,int c){
   for(int i=0;i<num_walls;i++){
       if(map[array_walls[i].getRow()][array_walls[i].getCol()]->getType()==map[r][c]->getType()){
           return 1;
       }
}
return 0;
}
};
class BaseBag;
class Character : public MovingObject
{
    friend class TestStudyInPink;
    private:
string name;

public:
    Character(int index, const Position pos, Map *map, const string &name = ""):MovingObject(index,pos,map,name){
        this->name=name;
    }
    string getName(){
        return name;
    }
    virtual int getindex() const=0;
    virtual BaseItem *getitem() const =0;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual int getexp() const =0;
    virtual int gethp() const=0;
    virtual void sethp(int hp)=0;
    virtual void setexp(int exp)  =0;
};
class Sherlock :public Character {
    friend class TestStudyInPink;
private:
int hp;
int exp;
string moving_rule;
Position pos;
int index;
Map *map;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp):Character(index,init_pos,map,"Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp){
       if (init_hp>=500){
        init_hp=500;
        }
        else if (init_hp<=0){
            init_hp=0;
        }
        if (init_exp>=900){
            init_exp=900;
        }
        else if (init_exp<=0){
            init_exp=0;
        }
        this->map=map;
       pos = init_pos;
       hp=init_hp;
       exp=init_exp;
       this->index=index;
}
BaseItem *getitem() const override{
    return nullptr;
}
int getindex() const override {
    return index;
}
int getexp() const override{
    return exp;
}
int gethp() const override {
    return hp;
}
void setexp(int exp) override{
    
        if (exp>=900){
            exp=900;
        }
        else if (exp<=0){
            exp=0;
        }
    this->exp=exp;
}
void sethp(int hp) override{
    if (hp>=500){
        hp=500;
        }
        else if (hp<=0){
        hp=0;
        }
    this->hp=hp;
}
    Position getNextPosition() override {
        int n=moving_rule.size();
        Position nextpos=pos;
       static int i=0;
       if (i==n){
           i=0;
       }
    if(moving_rule[i]=='L'){
         nextpos.setCol(pos.getCol()-1);
    } 
    else if(moving_rule[i]=='R'){
        nextpos.setCol(pos.getCol()+1);
    }
    else if(moving_rule[i]=='U'){
        nextpos.setRow(pos.getRow()-1);
    }
    else if (moving_rule[i]=='D'){
        nextpos.setRow(pos.getRow()+1);
    }
     i++;
     if((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
        return nextpos=Position::npos;
    }
       else if (map->check1(nextpos.getRow(),nextpos.getCol())==1){
    return nextpos=Position::npos;
    }
    
return nextpos;
}
void move() override{
    Position pos2=getCurrentPosition();
Position next=getNextPosition();
if (next.getCol()==-1||next.getRow()==-1){
    pos=pos2;
}
   else pos=next;
}
Position getCurrentPosition() const override {
    return pos;
}
string str() const override{
    return "Sherlock[index="+ to_string(index)+";pos="+pos.str()+";moving_rule="+moving_rule+"]";
}
};
class Watson :public Character {
    friend class TestStudyInPink;
private:
int hp;
int exp;
string moving_rule;
Position pos;
int index;
Map *map;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp):Character(index,init_pos,map,"Watson"), moving_rule(moving_rule), hp(init_hp), exp(init_exp){
        if (init_hp>=500){
        init_hp=500;
        }
        else if (init_hp<=0){
            init_hp=0;
        }
        if (init_exp>=900){
            init_exp=900;
        }
        else if (init_exp<=0){
            init_exp=0;
        }
        this->map=map;
        pos = init_pos;
        hp=init_hp;
        exp=init_exp;
        this->index=index;
}
int getexp() const override{
    return exp;
}
int getindex() const override{
return index;
}
int gethp() const override{
    return hp;
}
void sethp(int hp) override{
 if (hp>=500){
        hp=500;
        }
        else if (hp<=0){
        hp=0;
        }
    this->hp=hp;
}
void setexp(int exp) override{
  if (exp>=900){
            exp=900;
        }
        else if (exp<=0){
            exp=0;
        }
    this->exp=exp;
}
        Position getNextPosition() override {
        int n=moving_rule.size();
        Position nextpos=pos;
       static int i=0;
       if (i==n){
           i=0;
       }
    if(moving_rule[i]=='L'){
         nextpos.setCol(pos.getCol()-1);
    } 
    else if(moving_rule[i]=='R'){
        nextpos.setCol(pos.getCol()+1);
    }
    else if(moving_rule[i]=='U'){
        nextpos.setRow(pos.getRow()-1);
    }
    else if (moving_rule[i]=='D'){
        nextpos.setRow(pos.getRow()+1);
    }
        i++;
    if((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
        return nextpos=Position::npos;
    }
    else if (map->check1(nextpos.getRow(),nextpos.getCol())==1||map->isValid(nextpos,this)==0){
       
    return nextpos=Position::npos;
    }
return nextpos;
}
void move() override{
    Position pos2=getCurrentPosition();
Position next=getNextPosition();
 if (next.getCol()==-1&&next.getRow()==-1){
    pos=pos2;
}
else pos=next;
}
Position getCurrentPosition() const override {
    return pos;
}
string str() const override{
    return "Watson[index="+ to_string(index)+";pos="+pos.str()+";moving_rule="+moving_rule+"]";
}
BaseItem *getitem() const override{
    return nullptr;
}
};
class Criminal:public Character{
    friend class TestStudyInPink;
private:
Position pos;
Sherlock *sherlock;
Watson *watson;
int count1;
int index;
Map *map;
Position pos3=Position(-1,-1);
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson):Character(index,init_pos,map,"Criminal"),pos(init_pos),watson(watson),sherlock(sherlock){
        pos=init_pos;
        count1=0;
        this->map=map;
    }
    int getindex() const override{
        return index;
    }
    BaseItem *getitem() const override{
        return nullptr;
    }
 Position getNextPosition() override{
        Position pos1=watson->getCurrentPosition();
        Position pos2=sherlock->getCurrentPosition();
    Position nextpos=pos;
    int count=0;
     int r=nextpos.getRow();
     int c=nextpos.getCol();
    int num1=abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r-1))+abs(pos2.getCol()-c);
     int num2=abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r+1))+abs(pos2.getCol()-c);
     int num3=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c-1));
     int num4=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c+1));
     int array[4]={num1,num2,num3,num4};
     for(int i=0;i<3;i++){
         for(int j=3;j>i;j--){
             if(array[j]<array[j-1]){
                 swap(array[j],array[j-1]);
             }
         }
     }
    for(int i=3;i>=0;i--){
         if (array[i]==abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r-1))+abs(pos2.getCol()-c)){
nextpos=Position(r-1,c);
             if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-1,c)==1)){
       
         }
           else return pos=Position(r-1,c);
         }
           if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c-1))){
            nextpos=Position(r,c-1);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c-1)==1)){
       
         }
           else return pos=Position(r,c-1);
         }
         if (array[i]==abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r+1))+abs(pos2.getCol()-c)){
           
            nextpos=Position(r+1,c);
             if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+1,c)==1)){
       
         }
           else return pos=Position(r+1,c);
        }
           if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c+1))){
            nextpos=Position(r,c+1);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c+1)==1)){
       
         }
           else return pos=Position(r,c+1);
        }
     
     }
    return Position::npos;
}
Position getCurrentPosition() const override{
return pos;
}
void move()override{
    pos3=pos;
Position next=getNextPosition();
if (next.getCol()==-1||next.getRow()==-1){
    pos=pos3;
}
else {pos=next;
count1++;
}
}
Position previous(){
    return pos3;
}
Position check1(Position robot){
    int r=robot.getRow();
    int c=robot.getCol();
    int row=pos3.getRow();
    int col=pos3.getCol();
    if ((r+1==row&&c==col)||(r==row&&c-1==col)||(r-1==row&&c==col)||(r==row&&c+1==col)){
        return Position(row,col);
    }
    else return Position(-1,-1);
}
string str() const override{
    return "Criminal[index="+ to_string(index)+";pos="+pos.str()+"]";
}
int getexp() const override{
    return 0;
}
int gethp() const override{
    return 0;
}
void setexp(int exp) override{
}
void sethp(int hp) override{
}
int getCount(){
    return count1;
}
};
class ArrayMovingObject {
    friend class TestStudyInPink;
private:
int capacity;
MovingObject **arr_mv_objs;
int count;

public:
    ArrayMovingObject(int capacity){
        this->capacity=capacity;
        arr_mv_objs=new MovingObject*[capacity];
        int count=0;
    }
  
    
        bool isFull() const{
            if (count==capacity){
                return true;
            }
            return false;
        }
    bool add(MovingObject * mv_obj){
      if(mv_obj->getindex()<capacity){
        arr_mv_objs[mv_obj->getindex()]=mv_obj;
        count++;
        return true;
         }
       return false;
    }
    MovingObject * get(int index) const{
        return arr_mv_objs[index];
    }
    int size() const{
        return count;
    }
    string str() const{
          string s="ArrayMovingObject[count="+to_string(count)+";capacity="+to_string(capacity)+";";
        if (count==0){
            s="ArrayMovingObject[count="+to_string(count)+";capacity="+to_string(capacity)+";"+"]";
        }
else  {   for(int i=0;i<count-1;i++){
        s=s+arr_mv_objs[i]->str()+";";
    }
    s=s+arr_mv_objs[count-1]->str()+"]";
}
    return s;
    }
};
class Robot : public MovingObject
{
    friend class TestStudyInPink;
protected:
    Criminal *criminal;
    RobotType robot_type;
public:
    Robot(int index, const Position &pos, Map *map, Criminal *criminal, const string &name = ""):MovingObject(index,pos,map,name){
    }
    virtual int getindex() const=0;
    virtual void setitem(BaseItem *item) =0;
    virtual BaseItem *getitem() const=0;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual int getDistance() const = 0;
    
};
class RobotC : public Robot
{
    friend class TestStudyInPink;
    private:
    Position pos;
    int index;
    Criminal *criminal;
    Map *map;
    BaseItem *item;
public:
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal):Robot(index,init_pos,map,criminal,"RobotC"){
   pos=init_pos;
    this->index=index;
    this->criminal=criminal;
    this->map=map;
    }
Position getCurrentPosition() const override{
return pos;
}
int getindex() const override{
    return index;
}
  void setitem(BaseItem *item) override{
        this->item=item;
    }
    BaseItem *getitem() const override{
        return item;
    }
    int getDistance(Sherlock *sherlock){
        int matthan;
        Position PS=sherlock->getCurrentPosition();
        matthan=abs(pos.getRow()-PS.getRow())+abs(pos.getCol()-PS.getCol());
        return matthan;
    }

    int getDistance(Watson *watson){
            int matthan;
        Position PW=watson->getCurrentPosition();
        matthan=abs(pos.getRow()-PW.getRow())+abs(pos.getCol()-PW.getCol());
        return matthan;
    }
    int getDistance() const override{
        return 0;
    }
    Position getNextPosition() override{
        return pos=criminal->check1(pos);
    }
    void move() override{
    Position pos3=getNextPosition();
    pos=pos3;
    }
    string str() const override{
     
        return "Robot[pos="+pos.str()+";type="+"C"+";dist="+"]";
    }
      int getexp() const override{
        return 0;
    }
    int gethp() const override{
        return 0;
    }
    void sethp(int hp) override{}
    void setexp(int exp) override{}
};
class RobotW : public Robot
{
    friend class TestStudyInPink;
private:
    Watson *watson;
    Position pos;
    int index;
    Criminal *criminal;
    Map *map;
    BaseItem *item;
public:
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson):Robot(index,init_pos,map,criminal,"RobotW"){
        this->index=index;
        pos=init_pos;
        this->watson=watson;
        this->criminal=criminal;
        this->map=map;
    }
    int getindex() const override{
    return index;
}
Position getCurrentPosition() const override{
return pos;
}
    Position getNextPosition() override{
        Position pos1=watson->getCurrentPosition();
    Position nextpos=pos;
     int r=nextpos.getRow();
     int c=nextpos.getCol();
    int num1=abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c);
     int num2=abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c);
     int num3=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1));
     int num4=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1));

   
     int array[4]={num1,num2,num3,num4};
     for(int i=0;i<3;i++){
         for(int j=3;j>i;j--){
             if(array[j]<array[j-1]){
                 swap(array[j],array[j-1]);
             }
         }
     }
   if (pos1.getRow()==pos.getRow()&&pos1.getCol()==pos.getCol()){
       return Position::npos;
   }
    for(int i=0;i<4;i++){
         if (array[i]==abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c)){
             nextpos=Position(r-1,c);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-1,c)==1)){
         }
            else return pos=Position(r-1,c);
         }
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1))){
                  nextpos=Position(r,c+1);
           if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c+1)==1)){
       
         }
        else return pos=Position(r,c+1);
        }
            if (array[i]==abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c)){
                 nextpos=Position(r+1,c);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+1,c)==1)){
       
         }
        else return pos=Position(r+1,c);
        }
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1))){
              nextpos=Position(r,c-1);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c-1)==1)){
       
         }
            else return pos=Position(r,c-1);
        }
     }
    return Position::npos;
}
    void move() override{
        Position check=pos;
    Position pos2=getNextPosition();
    if ((pos2.getRow()!=-1&&pos2.getCol()!=-1)){
        pos=pos2;
    }
    else pos=check;
    }
    string str() const override{
        return "Robot[pos="+pos.str()+";type="+"W"+";dist="+to_string(getDistance())+"]";
    }
    int getDistance() const override{
        int distance;
        Position posW=watson->getCurrentPosition();
        distance =abs(posW.getRow()-pos.getRow())+abs(posW.getCol()-pos.getCol());
        return distance;
    }
      int getexp() const override{
        return 0;
    }
    int gethp() const override{
        return 0;
    }
    void setitem(BaseItem *item)override{
        this->item=item;
    }
    BaseItem *getitem() const override{
        return item;
    }
    void sethp(int hp) override{}
    void setexp(int exp) override{}
};
class RobotS : public Robot
{
    friend class TestStudyInPink;
private:
    Sherlock *sherlock;
    Position pos;
    int index;
    Criminal *criminal;
    BaseItem *item;
public:
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock):Robot(index,init_pos,map,criminal,"RobotS"){
        this->index=index;
        pos=init_pos;
        this->sherlock=sherlock;
        this->criminal=criminal;
    }
    int getindex() const override{
    return index;
}
      void setitem(BaseItem *item)override{
        this->item=item;
    }
    BaseItem *getitem() const override{
        return item;
    }
      int getexp() const override{
        return 0;
    }
    int gethp() const override{
        return 0;
    }
    void sethp(int hp) override{}
    void setexp(int exp) override{}
           Position getNextPosition() override{
        Position pos1=sherlock->getCurrentPosition();
    Position nextpos=pos;
     int r=nextpos.getRow();
     int c=nextpos.getCol();
    int num1=abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c);
     int num2=abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c);
     int num3=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1));
     int num4=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1));
   
   
     int array[4]={num1,num2,num3,num4};
     for(int i=0;i<3;i++){
         for(int j=3;j>i;j--){
             if(array[j]<array[j-1]){
                 swap(array[j],array[j-1]);
             }
         }
     }
   if (pos1.getRow()==pos.getRow()&&pos1.getCol()==pos.getCol()){
       return Position::npos;
   }
     for(int i=0;i<4;i++){
         if (array[i]==abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c)){
             nextpos=Position(r-1,c);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-1,c)==1)){
         }
            else return pos=Position(r-1,c);
         }
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+1))){
                  nextpos=Position(r,c+1);
           if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c+1)==1)){
       
         }
        else return pos=Position(r,c+1);
        }
            if (array[i]==abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c)){
                 nextpos=Position(r+1,c);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+1,c)==1)){
       
         }
        else return pos=Position(r+1,c);
        }
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-1))){
              nextpos=Position(r,c-1);
            if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c-1)==1)){
       
         }
            else return pos=Position(r,c-1);
        }
     }
    return Position::npos;
}
    void move() override{
    Position check=pos;
    Position pos2=getNextPosition();
    if ((pos2.getRow()!=-1&&pos2.getCol()!=-1)){
        pos=pos2;
    }
    else pos=check;
    }
    string str() const override{
        return "Robot[pos="+pos.str()+";type="+"S"+";dist="+to_string(getDistance())+"]";
    }
    int getDistance() const override{
        int distance;
        Position posW=sherlock->getCurrentPosition();
        distance =abs(posW.getRow()-pos.getRow())+abs(posW.getCol()-pos.getCol());
        return distance;
    }
    Position getCurrentPosition() const override{
        return pos;
    }
};
    class RobotSW : public Robot
{
    friend class TestStudyInPink;
private:
    Watson *watson;
    Sherlock *sherlock;
    Position pos;
    int index;
    BaseItem *item;
public:
 RobotSW ( int index , const Position & init_pos , Map * map , Criminal *
criminal , Sherlock * sherlock , Watson * watson ):Robot(index,init_pos,map,criminal,"RobotSW"){
        this->index=index;
        pos=init_pos;
        this->watson=watson;
        this->sherlock=sherlock;
    }
      void setitem(BaseItem *item)override{
        this->item=item;
    }
    BaseItem *getitem() const override{
        return item;
    }
    int getindex() const override{
    return index;
}
       
      Position getNextPosition() override{
        Position pos1=watson->getCurrentPosition();
        Position pos2=sherlock->getCurrentPosition();
    Position nextpos=pos;
     int r=nextpos.getRow();
     int c=nextpos.getCol();
    int num1=abs(pos1.getRow()-(r-2))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r-2))+abs(pos2.getCol()-c);
     int num2=abs(pos1.getRow()-(r+2))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r+2))+abs(pos2.getCol()-c);
     int num3=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-2))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c-2));
     int num4=abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+2))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c+2));
     int num5=abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-(c-1))+abs(pos2.getRow()-(r-1))+abs(pos2.getCol()-(c-1));
     int num6=abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-(c+1))+abs(pos2.getRow()-(r-1))+abs(pos2.getCol()-(c+1));
     int num7=abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-(c-1))+abs(pos2.getRow()-(r+1))+abs(pos2.getCol()-(c-1));
     int num8=abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-(c+1))+abs(pos2.getRow()-(r+1))+abs(pos2.getCol()-(c+1));
     int array[8]={num1,num2,num3,num4,num5,num6,num7,num8};
     for(int i=0;i<7;i++){
         for(int j=7;j>i;j--){
             if(array[j]<array[j-1]){
                 swap(array[j],array[j-1]);
             }
         }
     }
     for(int i=0;i<8;i++){
         if (array[i]==abs(pos1.getRow()-(r-2))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r-2))+abs(pos2.getCol()-c)){
         nextpos=Position(r-2,c);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-2,c)==1)){
         }
       
            else return pos=Position(r-2,c);
         }
           if (array[i]==abs(pos1.getRow()-(r-1))+abs(pos1.getCol()-c-1)+abs(pos2.getRow()-(r-1))+abs(pos2.getCol()-c-1)){
            nextpos=Position(r-1,c+1);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-1,c+1)==1)){
         }
            else return pos=Position(r-1,c+1);
         }
         
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c+2))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c+2))){
             nextpos=Position(r,c+2);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c+2)==1)){
         }
       
        else return pos=Position(r,c+2);
        }
         if (array[i]==abs(pos1.getRow()-r-1)+abs(pos1.getCol()-(c+1))+abs(pos2.getRow()-r-1)+abs(pos2.getCol()-(c+1))){
            nextpos=Position(r+1,c+1);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+1,c+1)==1)){
         }
       
        else return pos=Position(r+1,c+1);
        }
         if (array[i]==abs(pos1.getRow()-(r+2))+abs(pos1.getCol()-c)+abs(pos2.getRow()-(r+2))+abs(pos2.getCol()-c)){
           nextpos=Position(r+2,c);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+2,c)==1)){
         }
       
        else return pos=Position(r+2,c);
        }
         if (array[i]==abs(pos1.getRow()-(r+1))+abs(pos1.getCol()-c+1)+abs(pos2.getRow()-(r+1))+abs(pos2.getCol()-c+1)){
            nextpos=Position(r+1,c-1);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r+1,c-1)==1)){
         }
       
        else return pos=Position(r+1,c-1);
        }
         if (array[i]==abs(pos1.getRow()-r)+abs(pos1.getCol()-(c-2))+abs(pos2.getRow()-r)+abs(pos2.getCol()-(c-2))){
            nextpos=Position(r,c-2);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r,c-2)==1)){
         }
       
            else return pos=Position(r,c-2);
        }
          if (array[i]==abs(pos1.getRow()-r+1)+abs(pos1.getCol()-(c-1))+abs(pos2.getRow()-r+1)+abs(pos2.getCol()-(c-1))){
              nextpos=Position(r-1,c-1);
         if ((nextpos.getRow()>=map->getrow())||(nextpos.getRow()<0)||(nextpos.getCol()>=map->getcol())||(nextpos.getCol()<0)){
                
            }
            else  if ((map->check1(r-1,c-1)==1)){
         }
       
            else return pos=Position(r-1,c-1);
        }
     }
    return Position::npos;
}
    void move() override{
        Position check=pos;
    Position pos2=getNextPosition();
    if ((pos2.getRow()!=-1&&pos2.getCol()!=-1)){
        pos=pos2;
    }
    else pos=check;
    }
    string str() const override{
        return "Robot[pos="+pos.str()+";type="+"SW"+";dist="+to_string(getDistance())+"]";
    }
    int getDistance() const override{
        int distance;
        Position posW=watson->getCurrentPosition();
        Position posS=sherlock->getCurrentPosition();
        distance =abs(posW.getRow()-pos.getRow())+abs(posW.getCol()-pos.getCol())+abs(posS.getRow()-pos.getRow())+abs(posS.getCol()-pos.getCol());
        return distance;
    }
        Position getCurrentPosition() const override{
        return pos;
    }
        int getexp() const override{
        return 0;
    }
    int gethp() const override{
        return 0;
    }
    void sethp(int hp) override{}
    void setexp(int exp) override{}
};
class Configuration {
    friend class TestStudyInPink;
    friend class StudyPinkProgram;
public:
int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position* arr_walls;
    int num_fake_walls;
    Position* arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;
public:
    Configuration(const string & filepath){
        ifstream file;
        file.open(filepath);
        string s;
        while(getline(file,s)){
            int pos=s.find('=');
            if (s.substr(0,pos)=="MAP_NUM_ROWS") map_num_rows=stoi(s.substr(pos+1));
            else if (s.substr(0,pos)=="MAP_NUM_COLS") map_num_cols=stoi(s.substr(pos+1));
            else if (s.substr(0,pos)=="MAX_NUM_MOVING_OBJECTS") max_num_moving_objects=stoi(s.substr(pos+1));
            else if (s.substr(0,pos)=="ARRAY_WALLS"){
                int count=0;
            for(int i=0;i<s.size();i++){
                char c=40;
                if(s[i]==c){
                    count++;
                }
            }
            num_walls=count;
            arr_walls=new Position[num_walls];
                    for(int i=0;i<num_walls;i++){
            int count1=s.find('(');
            int count2=s.find(',');
            int count3=s.find(')');
            string row,col;
            row=s.substr(count1+1,count2-count1-1);
            col=s.substr(count2+1,count3-count2-1);
            arr_walls[i]=Position(stoi(row),stoi(col));
            s=s.erase(count1,count3-count1+2);
        }
            } 
           
            else if (s.substr(0,pos)=="ARRAY_FAKE_WALLS"){
                   int count=0;
            for(int i=0;i<s.size();i++){
                char c=40;
                if(s[i]==c){
                    count++;
                }
            }
            num_fake_walls=count;
            arr_fake_walls=new Position[num_fake_walls];
                    for(int i=0;i<num_fake_walls;i++){
            int count1=s.find('(');
            int count2=s.find(',');
            int count3=s.find(')');
            string row,col;
            row=s.substr(count1+1,count2-count1-1);
            col=s.substr(count2+1,count3-count2-1);
            arr_fake_walls[i]=Position(stoi(row),stoi(col));
         s=s.erase(count1,count3-count1+2);
        }
            } 
            else if (s.substr(0,pos)=="SHERLOCK_INIT_HP") sherlock_init_hp=stoi(s.substr(pos+1));
           else if (s.substr(0,pos)=="SHERLOCK_INIT_EXP") sherlock_init_exp=stoi(s.substr(pos+1)); 
            else if (s.substr(0,pos)=="SHERLOCK_MOVING_RULE") sherlock_moving_rule=s.substr(pos+1);
           else if (s.substr(0,pos)=="SHERLOCK_INIT_POS"){
           int count1=s.find('(');
           if(count1!=string::npos){
             string row,col;
             row=s.substr(count1+1,1);
             col=s.substr(count1+3,1);
             sherlock_init_pos=Position(stoi(row),stoi(col));
           }
            }
            else if (s.substr(0,pos)=="WATSON_INIT_HP") watson_init_hp=stoi(s.substr(pos+1));
           else if (s.substr(0,pos)=="WATSON_INIT_EXP") watson_init_exp=stoi(s.substr(pos+1)); 
             else if (s.substr(0,pos)=="WATSON_MOVING_RULE") watson_moving_rule=s.substr(pos+1);
           else if (s.substr(0,pos)=="WATSON_INIT_POS"){
           int count1=s.find('(');
           if(count1!=string::npos){
             string row,col;
             row=s.substr(count1+1,1);
             col=s.substr(count1+3,1);
             watson_init_pos=Position(stoi(row),stoi(col));
           }
            }
            else if (s.substr(0,pos)=="WATSON_INIT_HP") watson_init_hp=stoi(s.substr(pos+1));
           else if (s.substr(0,pos)=="WATSON_INIT_EXP") watson_init_exp=stoi(s.substr(pos+1)); 
            else if (s.substr(0,pos)=="CRIMINAL_INIT_POS"){
                 int count1=s.find('(');
           if(count1!=string::npos){
             string row,col;
             row=s.substr(count1+1,1);
             col=s.substr(count1+3,1);
             criminal_init_pos=Position(stoi(row),stoi(col));
           }
            }
            else if (s.substr(0,pos)=="NUM_STEPS") num_steps=stoi(s.substr(pos+1));
        }
    }
    string str() const {
        string result = "Configuration[\n";
        result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
        result += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
        result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
        result += "NUM_WALLS=" + to_string(num_walls) + "\n";
        result += "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; ++i) {
            result += "(" + to_string(arr_walls[i].getRow()) + "," + to_string(arr_walls[i].getCol()) + ")";
            if (i < num_walls - 1) result += ";";
        }
        result+="]\n";
        result+="NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
        result+="ARRAY_FAKE_WALLS=[";
        for (int i=0;i<num_fake_walls; ++i) {
            result+="(" + to_string(arr_fake_walls[i].getRow())+","+to_string(arr_fake_walls[i].getCol())+")";
            if (i < (num_fake_walls-1)) {
                result+=";";
            }
        }
        result+="]\n";
        result+="SHERLOCK_MOVING_RULE="+sherlock_moving_rule+"\n";
        result+="SHERLOCK_INIT_POS=("+to_string(sherlock_init_pos.getRow())+","+to_string(sherlock_init_pos.getCol())+")\n";
        result+="SHERLOCK_INIT_HP="+to_string(sherlock_init_hp)+"\n";
        result+="SHERLOCK_INIT_EXP="+to_string(sherlock_init_exp) +"\n";
        result+="WATSON_MOVING_RULE="+ watson_moving_rule+"\n";
        result+="WATSON_INIT_POS=("+to_string(watson_init_pos.getRow())+"," +to_string(watson_init_pos.getCol()) + ")\n";
        result+="WATSON_INIT_HP="+to_string(watson_init_hp)+"\n";
        result+="WATSON_INIT_EXP="+to_string(watson_init_exp)+"\n";
        result+="CRIMINAL_INIT_POS=("+to_string(criminal_init_pos.getRow())+","+to_string(criminal_init_pos.getCol()) + ")\n";
        result+="NUM_STEPS="+to_string(num_steps)+"\n";
        result+="]";
        return result;
    }
};
class BaseItem{
    friend class TestStudyInPink;
  protected:
    ItemType type;
public:
    BaseItem(ItemType in_type):type(in_type){}
    virtual ItemType getType() const{
        return type;
    }
    virtual string getName() const = 0;
    virtual string type1() const =0;
   virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use ( Character * obj , Robot * robot ) = 0;
};
class MagicBook :public BaseItem{
    friend class TestStudyInPink;
    public:
    MagicBook():BaseItem(MAGIC_BOOK){
    }
   bool canUse ( Character * obj , Robot * robot ) override{
       if (obj->getexp()<=350&&obj->getexp()>0){
           return true;
       }
       else return false;
   }
    void use ( Character * obj , Robot * robot ) override{
             obj->setexp(ceil(obj->getexp()+0.25*obj->getexp()));
        
    }
    string getName() const override{
    return "MagicBook";
    }
    string type1() const override{
        return "";
    }
}; 
class EnergyDrink:public BaseItem{
    friend class TestStudyInPink;
public:
EnergyDrink():BaseItem(ENERGY_DRINK){}
 string getName() const override{
    return "EnergyDrink";
    }
     string type1() const override{
        return "";
    }
  bool canUse ( Character * obj , Robot * robot ) override{
       if (obj->gethp()<=100&&obj->gethp()>0){
           return true;
       }
       else return false;
   }
    void use ( Character * obj , Robot * robot ) override{
        int num=ceil(obj->gethp()+0.20*obj->gethp());
            return obj->sethp(num);
        
    }
};
class FirstAid:public BaseItem{
    friend class TestStudyInPink;
public:
FirstAid():BaseItem(FIRST_AID){}
  bool canUse ( Character * obj , Robot * robot ) override{
       if ((obj->gethp()<=100&&obj->gethp()>0)||((obj->getexp()<=350&&obj->getexp()>0))){
           return true;
       }
       else return false;
   }
    string type1() const override{
        return "";
    }
    void use ( Character * obj , Robot * robot ) override{
            return obj->sethp(ceil(obj->gethp()+0.5*obj->gethp()));
    }
     string getName() const override{
    return "FirstAid";
    }
};
class ExcemptionCard:public BaseItem{
    friend class TestStudyInPink;
public:
ExcemptionCard():BaseItem(EXCEMPTION_CARD){}
 string getName() const  override{
    return "ExcemptionCard";
    }
     string type1() const override{
        return "";
    }
 bool canUse ( Character * obj , Robot * robot ) override{
     int hp=obj->gethp()%2;
       if (obj->getName()=="Sherlock"&&(hp!=0)){
           return true;
       }
       else return false;
   }
    void use ( Character * obj , Robot * robot ) override{
    }
};
class PassingCard: public BaseItem{
    friend class TestStudyInPink;
  private:
 string challenge;
    int t;
public:
PassingCard():BaseItem(PASSING_CARD){}
PassingCard(string s):BaseItem(PASSING_CARD){}
PassingCard(int i,int j):BaseItem(PASSING_CARD){
   t=(i*11 + j)%4;
   if (t==0){
       challenge="RobotS";
   }
   else if (t==1){
       challenge="RobotC";
   }
   else if (t==2){
       challenge="RobotSW";
   }
   else if (t==3){
       challenge="all";
   }
}
string type1() const override{
    return challenge;
}
 string getName() const  override{
    return "PassingCard";
    }
 bool canUse ( Character * obj , Robot * robot ) override{
     int hp=obj->gethp()%2;
       if (obj->getName()=="Watson"&&(hp==0)){
           return true;
       }
       else return false;
   }
    void use ( Character * obj , Robot * robot ) override{
       if (challenge!=robot->getName()){
           obj->setexp(obj->getexp()-50);
       }
    }
};
class Node{
    friend class TestStudyInPink;
public:
BaseItem *item;
Node *next;
Node(BaseItem* item) :item(item),next(nullptr) {}
};
class BaseBag{
    protected:
       Node *head;
       int itemcount;
private:
Character *obj;
int maxitem;
public:
BaseBag(int numbag,Character *obj){
    maxitem=numbag;
    this->obj=obj;
    head=nullptr;
    itemcount=0;
}
int getCount(){
    return itemcount;
}

virtual bool insert ( BaseItem * item ){
    if (itemcount>=maxitem){
        return false;
    }
    if (item==nullptr) return false;
    Node *newnode= new Node(item);
    newnode->next=head;

    head=newnode;
    itemcount++;
    return true;
}
virtual bool check(BaseItem *item){
    Node *cur=head;
    while(cur!=nullptr){
        if (cur->item->getName()==item->getName()){
            return true;
        }
        cur=cur->next;
    }
    return false;
}
int check1(BaseItem *item){
    Node *cur=head;
    int count=0;
     while(cur!=nullptr){
        if (cur->item->getName()==item->getName()){
            count++;
        }
        cur=cur->next;
    }
    return count;
}
  virtual BaseItem* get()  {
     if (head!=nullptr){
         Node *newnode=head;
         newnode->next=head->next;
         BaseItem *item=newnode->item;
         head=head->next;
         itemcount--;
         delete newnode;
          return item;
     }
     return nullptr;
  }

virtual BaseItem * get( ItemType itemType ) {
    
    Node *pre=nullptr;
    Node *cur=head;
    Node *pos=nullptr;
    int count=0;
    BaseItem *items;
    if (itemType==0){
        items=new MagicBook();
    }
    else if(itemType==1){
        items=new EnergyDrink();
    }
    else if (itemType==2){
        items=new FirstAid();
    }
    else if (itemType==3){
        items=new ExcemptionCard();
    }
    else if (itemType==4){
        items=new PassingCard();
    }
    while(cur!=nullptr){
if (head->item->getName()==items->getName()){
            Node *new1 = head;
            BaseItem *item1=head->item;
            new1->next=head->next;
            head=head->next;
            delete new1;
            itemcount--;
            count++;
         return item1;
        }
        if (cur->item->getName()==items->getName()){
     pre->next=head;
     cur->next=head->next;
     head->next=pos;
     head=cur;
     count++;
     break;
    }
    pre=cur;
    cur=cur->next;
    if (cur!=nullptr){
    pos=cur->next;
}
    }
    if (count==0){
        return nullptr;
    }
    
    BaseItem *use=head->item;
    Node *delete1=head;
    delete1->next=head->next;
    head=head->next;
    delete delete1;
    itemcount--;
    return use;
}





virtual BaseItem* get1()  {
    Node *pre=nullptr;
    Node *cur=head;
    Node *pos=nullptr;
    int count=0;
    Robot *robot=nullptr;
    while(cur!=NULL){
                if ((head->item->getName()=="FirstAid"||head->item->getName()=="EnergyDrink"||head->item->getName()=="MagicBook")&&head->item->canUse(obj,robot)==1){
            head->item->use(obj,robot);
            Node *new1 = head;
            BaseItem *item1=head->item;
            new1->next=head->next;
            head=head->next;
            delete new1;
            itemcount--;
         return item1;
        }
  
        if ((cur->item->getName()=="FirstAid"||cur->item->getName()=="EnergyDrink"||cur->item->getName()=="MagicBook")&&cur->item->canUse(obj,robot)==1){
    cur->item->use(obj,robot);
     pre->next=head;
     cur->next=head->next;
     head->next=pos;
     head=cur;
     count++;
     break;
    }
    pre=cur;
    cur=cur->next;
   if (cur!=nullptr){
    pos=cur->next;
}
    }
    if (count==0){
        return nullptr;
    }
    BaseItem *use=head->item;
    Node *delete1=head;
    delete1->next=head->next;
    head=head->next;
    delete delete1;
    itemcount--;
    return use;
}

virtual BaseItem * get2( ItemType itemType ) {
    
    Node *pre=nullptr;
    Node *cur=head;
    Node *pos=nullptr;
    int count=0;
    BaseItem *items;
    if (itemType==0){
        items=new MagicBook();
    }
    else if(itemType==1){
        items=new EnergyDrink();
    }
    else if (itemType==2){
        items=new FirstAid();
    }
    else if (itemType==3){
        items=new ExcemptionCard();
    }
    else if (itemType==4){
        items=new PassingCard();
    }
    while(cur!=nullptr){
if (head->item->getName()==items->getName()&&head->item->canUse(obj,nullptr)){
            Node *new1 = head;
            BaseItem *item1=head->item;
            new1->next=head->next;
            head=head->next;
            delete new1;
            itemcount--;
            count++;
         return item1;
        }
        if (cur->item->getName()==items->getName()&&cur->item->canUse(obj,nullptr)){
     pre->next=head;
     cur->next=head->next;
     head->next=pos;
     head=cur;
     count++;
     break;
    }
    pre=cur;
    cur=cur->next;
    if (cur!=nullptr){
    pos=cur->next;
}
    }
    if (count==0){
        return nullptr;
    }
    
    BaseItem *use=head->item;
    Node *delete1=head;
    delete1->next=head->next;
    head=head->next;
    delete delete1;
    itemcount--;
    return use;
}
void deleteitem(BaseItem *baseitem){
    Node *previos=nullptr;
    Node *current=head;
    while(current!=NULL){
          if (head->item->getName()==baseitem->getName()){
          Node *delete1=head;
          delete1->next=head->next;
          head=head->next;
          delete delete1;
          itemcount--;
    break;
          }
        else if (current->item->getName()==baseitem->getName()){
            previos->next=current->next;
            itemcount--;
            delete current;
    break;
        }
        previos=current;
        current=current->next;
    }
}
  virtual string str() const {
        string result = "Bag[count=" + to_string(itemcount) + ";";
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->next==NULL){
                  result += curr->item->getName();
            }
            else result += curr->item->getName() + ";";
            curr = curr->next;
        }
        result += "]";
        return result;
    }
};
class WatsonBag;
class SherlockBag: public BaseBag{
    friend class TestStudyInPink;
private:
Sherlock *sherlock;
public:
SherlockBag(Sherlock *sherlock):BaseBag(15,sherlock){
    this->sherlock=sherlock;
}
};
class WatsonBag:public BaseBag{
    friend class TestStudyInPink;
 private:
 Watson *watson;
 public:
 WatsonBag(Watson *watson):BaseBag(13,watson){
     this->watson=watson;
 }
};

class StudyPinkProgram {
    friend class TestStudyInPink;
private:
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    Map * map;
    ArrayMovingObject * arr_mv_objs;
    SherlockBag *sherlockbag;
    WatsonBag *watsonbag;
public:
    StudyPinkProgram(const string & config_file_path){
         config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
   if (config->max_num_moving_objects<3){
       arr_mv_objs = new ArrayMovingObject(3);
   }
   else arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    SherlockBag *sherlockbag=new SherlockBag(sherlock);
    WatsonBag *watsonbag=new WatsonBag(watson);
    }

    bool isStop() const{
        if (sherlock->gethp()==1||watson->gethp()==1||sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())||watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())){
        
            return true;
        }
        else return false;
    }

   void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }
BaseItem *createitem(int i,int j){
        int p=i*j;
        int s=0;
   while(p!=0){
       int n;
       n=p%10;
       s+=n;
       p=p/10;
     if (s>9&&p==0){
         p=s;
         s=0;
     }
   }
   if (s<=1&&s>=0){
       return new MagicBook();
   }
   else if (s>=2&&s<=3){
       return new EnergyDrink();
   }
   else if (s>=4&&s<=5){
       return new FirstAid();
   }
   else if (s>=6&&s<=7){
       return new ExcemptionCard();
   }
   else if (s>=8&&s<=9){
       return new PassingCard(i,j);
   }
   return nullptr;
    }
       static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson){
           int distance1=abs(criminal->getCurrentPosition().getCol()-sherlock->getCurrentPosition().getCol())+abs(criminal->getCurrentPosition().getRow()-sherlock->getCurrentPosition().getRow());
                   int distance2=abs(criminal->getCurrentPosition().getCol()-watson->getCurrentPosition().getCol())+abs(criminal->getCurrentPosition().getRow()-watson->getCurrentPosition().getRow());
               Robot *robot;
               if (distance1>distance2){
                  robot =new RobotW(index,criminal->previous(),map,criminal,watson);
               }
               else if (distance1<distance2){
                  robot =new RobotS(index,criminal->previous(),map,criminal,sherlock);
               }
               else  if (distance1==distance2) {
                   robot =new RobotSW(index,criminal->previous(),map,criminal,sherlock,watson);
               }
               else robot=nullptr;
               return robot;
       }
      void run(bool verbose) {

        // Note: This is a sample code. You can change the implementation as you like.
 int count=0;
int count11=0;
int count1=0;
int count3=0;
Position pos;
       for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                pos=arr_mv_objs->get(i)->getCurrentPosition();
                if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&sherlock->getexp()==0)||(arr_mv_objs->get(i)->getName()=="Watson"&&sherlock->getexp()==0)){
                    continue;
                }
                arr_mv_objs->get(i)->move();
              if (((pos.getCol()==arr_mv_objs->get(i)->getCurrentPosition().getCol())&&(pos.getRow()==arr_mv_objs->get(i)->getCurrentPosition().getRow()))&&((arr_mv_objs->get(i)->getName()=="RobotS")||(arr_mv_objs->get(i)->getName()=="RobotC")||(arr_mv_objs->get(i)->getName()=="RobotSW")||(arr_mv_objs->get(i)->getName()=="RobotW"))){
         if (count1!=0){
            continue;
         }
              }
              if (count3!=0){
                  continue;
              }
         for(int j=0;j<arr_mv_objs->size();j++){
            if (j!=i){
                if (arr_mv_objs->get(i)->getCurrentPosition().isEqual(arr_mv_objs->get(j)->getCurrentPosition())){
             if (arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="Watson"){
                 count3++;
             }
              if ((arr_mv_objs->get(i)->getName()=="Sherlock")&&(arr_mv_objs->get(j)->getName()=="RobotS"||arr_mv_objs->get(j)->getName()=="RobotSW"||arr_mv_objs->get(j)->getName()=="RobotC"||arr_mv_objs->get(j)->getName()=="RobotW")){
                   count1++;
               }
               else if ((arr_mv_objs->get(i)->getName()=="Watson")&&(arr_mv_objs->get(j)->getName()=="RobotS"||arr_mv_objs->get(j)->getName()=="RobotSW"||arr_mv_objs->get(j)->getName()=="RobotC"||arr_mv_objs->get(j)->getName()=="RobotW")){
               count1++;
               }
               if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="Watson")||(arr_mv_objs->get(i)->getName()=="Watson"&&arr_mv_objs->get(j)->getName()=="Sherlock")){
                 
                  if (sherlockbag->getCount()==0||watsonbag->getCount()==0||sherlockbag->check(new PassingCard())==0||watsonbag->check(new ExcemptionCard())==0){
                      
                  }
                  else {
                  
                     int number=sherlockbag->check1(new PassingCard());
                while(number!=0){
                    if (watsonbag->getCount()==13){
                        break;
                    }
                }
                    watsonbag->insert(sherlockbag->get2(PASSING_CARD));
                    number--;
                int number1=watsonbag->check1(new ExcemptionCard());
                 while(number!=0){
                      if (sherlockbag->getCount()==15){
                        break;
                    }
                    sherlockbag->insert(sherlockbag->get2(PASSING_CARD));
                    number1--;
                }
                  }
                   }
            else  if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="RobotS")||(arr_mv_objs->get(i)->getName()=="RobotS"&&arr_mv_objs->get(j)->getName()=="Sherlock")){
                  
                       if (sherlock->getexp()>400){
                            if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                       if (arr_mv_objs->get(i)->getName()=="RobotS"){
                        sherlockbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  sherlockbag->insert(arr_mv_objs->get(j)->getitem());
                       }
                       else if (sherlock->getexp()<=400){
                            if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                       else sherlock->setexp(ceil(sherlock->getexp()-0.1*sherlock->getexp()));
                       }
                   
                       if (sherlockbag->get1()!=nullptr){
                                    sherlockbag->get1();
                                }
                   }
                              else  if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="RobotW")||(arr_mv_objs->get(i)->getName()=="RobotW"&&arr_mv_objs->get(j)->getName()=="Sherlock")){
                              
                   if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                              
                         sherlockbag->get2(EXCEMPTION_CARD);
                       }
                         if (arr_mv_objs->get(i)->getName()=="RobotW"){
                        sherlockbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  sherlockbag->insert(arr_mv_objs->get(j)->getitem());
                         if (sherlockbag->get1()!=nullptr){
                                    sherlockbag->get1();
                                }
                   }
                         else  if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="RobotC")||(arr_mv_objs->get(i)->getName()=="RobotC"&&arr_mv_objs->get(j)->getName()=="Sherlock")){
                         
                       if (sherlock->getexp()>500){
                           if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                     
                         if (sherlockbag->get1()!=nullptr){
                                    sherlockbag->get1();
                                }
                                count11++;
                           arr_mv_objs->get(i)->move();
                           break;
                       }
                       else if(sherlock->getexp()<=500){
                              
                               if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                             if (arr_mv_objs->get(i)->getName()=="RobotC"){
                        sherlockbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  sherlockbag->insert(arr_mv_objs->get(j)->getitem());
                                if (sherlockbag->get1()!=nullptr){
                                    sherlockbag->get1();
                                }
                       }
                   }
                else  if ((arr_mv_objs->get(i)->getName()=="Sherlock"&&arr_mv_objs->get(j)->getName()=="RobotSW")||(arr_mv_objs->get(i)->getName()=="RobotSW"&&arr_mv_objs->get(j)->getName()=="Sherlock")){
                    
                       if (sherlock->getexp()>300&&sherlock->gethp()>335){
                            if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                     if (arr_mv_objs->get(i)->getName()=="RobotSW"){
                        sherlockbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  sherlockbag->insert(arr_mv_objs->get(j)->getitem());
                       }
                       else if (sherlock->getexp()<=300&&sherlock->gethp()<=335){
                               if (sherlockbag->check(new ExcemptionCard())==1&&(sherlockbag->get2(EXCEMPTION_CARD)->canUse(sherlock,nullptr)==1)){
                               sherlockbag->get2(EXCEMPTION_CARD);
                       }
                       }
                       else {
                           sherlock->sethp(ceil(sherlock->gethp()-0.15*sherlock->gethp()));
                           watson->setexp(ceil(sherlock->getexp()-0.15*sherlock->getexp()));
                       }
                       if (sherlockbag->get1()!=nullptr){
                                    sherlockbag->get1();
                                }
                   }
                else  if ((arr_mv_objs->get(i)->getName()=="Watson"&&arr_mv_objs->get(j)->getName()=="RobotS")||(arr_mv_objs->get(i)->getName()=="RobotS"&&arr_mv_objs->get(j)->getName()=="Watson")){
            
                  if (watsonbag->check(new PassingCard())==1&&(watsonbag->get2(PASSING_CARD)->canUse(watson,nullptr)==1)){
                               if((watsonbag->get2(PASSING_CARD)->type1()=="RobotS")||watsonbag->get2(PASSING_CARD)->type1()=="all"){
                                   watsonbag->get2(PASSING_CARD);
                               }
                               else watson->setexp(watson->getexp()-50);
                    
                 }
                  if (watsonbag->get1()!=nullptr){
                                    watsonbag->get1();
                                }
                   }
           else  if ((arr_mv_objs->get(i)->getName()=="Watson"&&arr_mv_objs->get(j)->getName()=="RobotW")||(arr_mv_objs->get(i)->getName()=="RobotW"&&arr_mv_objs->get(j)->getName()=="Watson")){
                     
                      if (watsonbag->check(new PassingCard())==1&&(watsonbag->get2(PASSING_CARD)->canUse(watson,nullptr)==1)){
                               if(watsonbag->get2(PASSING_CARD)->type1()=="RobotW"||watsonbag->get2(PASSING_CARD)->type1()=="all"){
                                   watsonbag->get2(PASSING_CARD);
                                if (arr_mv_objs->get(i)->getName()=="RobotW"){
                        watsonbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  watsonbag->insert(arr_mv_objs->get(j)->getitem());
                               }
                               else watson->setexp(watson->getexp()-50);
                 }
                 else if (watson->gethp()>350){
                     if (arr_mv_objs->get(i)->getName()=="RobotW"){
                        watsonbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  watsonbag->insert(arr_mv_objs->get(j)->getitem());
                 }
                 else watson->sethp(ceil(watson->gethp()-watson->gethp()*0.05));
                   if (watsonbag->get1()!=nullptr){
                                  watsonbag->get1();
                                }
                   }
                  else  if ((arr_mv_objs->get(i)->getName()=="Watson"&&arr_mv_objs->get(j)->getName()=="RobotSW")||(arr_mv_objs->get(i)->getName()=="RobotSW"&&arr_mv_objs->get(j)->getName()=="Watson")){
            
                      if (watsonbag->check(new PassingCard())==1&&(watsonbag->get2(PASSING_CARD)->canUse(watson,nullptr)==1)){
                               if(watsonbag->get2(PASSING_CARD)->type1()=="RobotSW"||watsonbag->get2(PASSING_CARD)->type1()=="all"){
                                   watsonbag->get2(PASSING_CARD);
                                  if (arr_mv_objs->get(i)->getName()=="RobotSW"){
                        watsonbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  watsonbag->insert(arr_mv_objs->get(j)->getitem());
                               }
                               else watson->setexp(watson->getexp()-50);
                 }
                 else if(watson->getexp()>600&&watson->gethp()>165){
                          watsonbag->insert(arr_mv_objs->get(j)->getitem());
                 }
                 else {
                     watson->setexp(watson->getexp()-watson->getexp()*0.15);
                         watson->sethp(watson->gethp()-watson->gethp()*0.15);
                 }
                     if (watsonbag->get1()!=nullptr){
                                    watsonbag->get1();
                                }
                 
                 
                   }
                     else  if ((arr_mv_objs->get(i)->getName()=="Watson"&&arr_mv_objs->get(j)->getName()=="RobotC")||(arr_mv_objs->get(i)->getName()=="RobotC"&&arr_mv_objs->get(j)->getName()=="Watson")){
                       
                            if (watsonbag->check(new PassingCard())==1&&(watsonbag->get2(PASSING_CARD)->canUse(watson,nullptr)==1)){
                               if(watsonbag->get2(PASSING_CARD)->type1()=="RobotC"||watsonbag->get2(PASSING_CARD)->type1()=="all"){
                                   watsonbag->get2(PASSING_CARD);
                               }
                               else watson->setexp(watson->getexp()-50);
                 }
            if (arr_mv_objs->get(i)->getName()=="RobotC"){
                        watsonbag->insert(arr_mv_objs->get(i)->getitem());
                       }
                       else  watsonbag->insert(arr_mv_objs->get(j)->getitem());
                  if (watsonbag->get1()!=nullptr){
                                  watsonbag->get1();
                                }
                 
                   }
          
                   }
                   
                   
                   
                   
                   
                   
                }
            }
            
if (count11!=0){
     printStep(istep); 
    count++;
    break;
}
             if (isStop()) {
                    printStep(istep); 
                    count++;
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
                 if (arr_mv_objs->get(i)->getName()=="Criminal"){
                      if (criminal->getCount()==3){
                          RobotC *robotC= new RobotC(arr_mv_objs->size(),criminal->previous(),map,criminal);
                   BaseItem *base=createitem(robotC->getCurrentPosition().getRow(),robotC->getCurrentPosition().getCol()); 
                          robotC->setitem(base);
                          arr_mv_objs->add(robotC);
                      }
                      else if (criminal->getCount()>3&&criminal->getCount()%3==0){
                          Robot *robot=create(arr_mv_objs->size(),map,criminal,sherlock,watson);
                              BaseItem *base=createitem(robot->getCurrentPosition().getRow(),robot->getCurrentPosition().getCol()); 
                          robot->setitem(base);
                          arr_mv_objs->add(robot);
                      }
                  }
        }
        count1=0;
        count3=0;
        if (count!=0){
        printResult();
        break;
        }
    }
    if (count==0){
        printResult();
    }
}
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
