#include <RSGL/RSGL.hpp>
#include <iostream>

const int size = 25;

RSGL::window win("RSGL Snake",{500,500,485,485},{0,0,0});
bool running=true; 

std::vector<std::vector<RSGL::rect>> map;
std::vector<RSGL::point> snake; RSGL::point apple;

int QLearning(std::vector<int> data){
      
}


int main(){
      srand(time(NULL));
      for (int y=0; y < win.r.length/size; y++){
            map.insert(map.end(),{{}});
            for (int x=0; x < win.r.width/size; x++){
                  map.at(y).insert(map.at(y).end(),{{x*size + (x*2),y*size + (y*2) + size,size,size}});
            }
      }
      snake.insert(snake.end(),{rand() % ((win.r.length/size)-1), rand() % ((win.r.width/size)-2)});
      apple = {rand() % ((win.r.length/size)-1) , rand() % (( win.r.width/size)-2)};
      int frame=0; int dir=1;
      std::vector<int> move; bool dead=false; int points=0;
      while(running){
            win.checkEvents();
            for (int y=0; y < snake.size(); y++){ 
                  for (int x=0; x < snake.size(); x++){
                        if (snake.at(x).x == snake.at(y).x && snake.at(x).y == snake.at(y).y && x != y) dead=true;
                  }
            }
            frame++; if (frame == 9 && !dead){ 
                  move.insert(move.begin(),dir); 
                  for (int i=0; i < snake.size(); i++){
                        switch(move.at(i)){
                              case 1: if (snake.at(i).x < (win.r.width/size)-2) snake.at(i).x++; else i=snake.size(); break;
                              case 2: if (snake.at(i).y < (win.r.length/size)-3) if (snake.at(i).y < (win.r.length/size)-2) snake.at(i).y++; else i=snake.size(); break;
                              case 3: if (snake.at(i).x) snake.at(i).x--; else i=snake.size(); break;
                              case 0: if (snake.at(i).y) snake.at(i).y--; else i=snake.size(); break;
                        } 
                  } frame=0;
            }
            if (apple.x == snake.at(0).x && apple.y == snake.at(0).y){ 
                  switch (move.at(snake.size()-1)){
                        case 1: snake.insert(snake.end(),{snake.at(snake.size()-1).x-1,snake.at(snake.size()-1).y}); break;
                        case 2: snake.insert(snake.end(),{snake.at(snake.size()-1).x,snake.at(snake.size()-1).y-1}); break;
                        case 3: snake.insert(snake.end(),{snake.at(snake.size()-1).x+1,snake.at(snake.size()-1).y-1}); break;
                        case 0: snake.insert(snake.end(),{snake.at(snake.size()-1).x,snake.at(snake.size()-1).y+1}); break;
                        default: break;
                  }
                  apple = {rand() % ((win.r.length/size)-1), rand() % ((win.r.width/size)-2)}; points++;
            }
            switch(win.event.type){
                 case RSGL::quit: running=false; break;
                 case RSGL::KeyPressed:
                        if (win.event.key == "Right" && dir != 3) dir=1;
                        else if (win.event.key == "Left" && dir != 1) dir = 3;
                        else if (win.event.key == "Up" && dir != 2) dir = 0;
                        else if (win.event.key == "Down" && dir) dir =2;
                 default: break;
            }
            for (int y=0; y < map.size(); y++) for (int x=0; x < map.at(y).size(); x++){ 
                  RSGL::color c = {255,255,255};
                  if (apple.x == x && apple.y == y ){c={255,0,0};}
                  for (int i=0; i < snake.size(); i++){
                        if (snake.at(i).x == x && snake.at(i).y == y ){c={0,255,0}; break;}
                  } 
                  RSGL::drawRect(map.at(y).at(x),c); 
            }
            RSGL::drawRect({350,0,25,25},{255,0,0});
            RSGL::drawText(": " + std::to_string(points),{380,0,25},"/usr/share/fonts/TTF/DejaVuSans-Bold.ttf",{255,255,255});
            win.clear();
      } win.close();
}