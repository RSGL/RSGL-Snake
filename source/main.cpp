#include <RSGL/RSGL.hpp>
#include <iostream>

const int size = 25;

RSGL::window win("RSGL Snake",{500,500,485,485},{0,0,0});
bool running=true; 

std::vector<std::vector<RSGL::rect>> map;
std::vector<RSGL::point> snake; RSGL::point apple;

int QLearning(std::vector<int> data){
      int output; std::vector<int> bias={0,0,0,0}; // 1 negative bias, 2 strong negative bias, 0 no bias, 1 bias, 2 strong bias


      for (int i=0; i < data.size(); i++){
            
      }
      return output;
}

bool inSnake(RSGL::point p){for (int i=0; i < snake.size(); i++) if (snake.at(i).x == p.x && snake.at(i).y == p.y ) return true; return false; } 

int main(){
      srand(time(NULL));
      for (int y=0; y < win.r.length/size; y++){
            map.insert(map.end(),{{}});
            for (int x=0; x < win.r.width/size; x++){
                  map.at(y).insert(map.at(y).end(),{{x*size + (x*2),y*size + (y*2) + size,size,size}});
            }
      }
      snake.insert(snake.end(),{rand() % ((win.r.length/size)-1), rand() % ((win.r.width/size)-2)});
      do apple = {rand() % ((win.r.length/size)-1) , rand() % (( win.r.width/size)-2)}; while (inSnake(apple));
      int frame=0; int frame2=0; int dir=1;
      std::vector<int> move; bool dead=false; bool initPress=false; bool AI=false; int points=0;
      std::vector<int> AIData;
      while(running){
            win.checkEvents();
            switch(win.event.type){
                 case RSGL::quit: running=false; break;
                 case RSGL::MouseButtonReleased:
                        if (!initPress && win.event.button == 1 && RSGL::RectCollidePoint({380,0,25,25},{win.event.x,win.event.y})) AI=true;
                        break;
                 case RSGL::KeyPressed:
                        if (initPress && !AI){
                              if (win.event.key == "Right" && move.at(0) != 3 ){ dir=1; }
                              else if (win.event.key == "Left" && move.at(0) != 1 ){ dir = 3; }
                              else if (win.event.key == "Up" && move.at(0) != 2 ){ dir = 0; }
                              else if (win.event.key == "Down" && move.at(0) ){ dir =2;}
                        } else initPress=true; break;
                 default: break;
            } if (AI){ 
                  std::vector<int> walls= {snake.at(0).y, ((win.r.width/size)-2) - snake.at(0).x, ((win.r.width/size)-3) - snake.at(0).y}; int distToWall = snake.at(0).x;
                  for (int i=0; i < 3; i++) if (walls.at(i) < distToWall) distToWall=walls.at(i);
                  int distToApple=abs(snake.at(0).x-apple.x)+abs(snake.at(0).y-apple.y); int distToBody=-1; 
                  for (int i=1; i < snake.size(); i++){ int distToHead = abs(snake.at(0).x-snake.at(i).x)+abs(snake.at(0).y-snake.at(i).y); if (distToBody > distToHead) distToBody=distToHead; }
                  AIData = {dir, distToApple, distToWall, distToBody};
                  dir = QLearning(AIData);
            }
            if (initPress || AI){ frame++;
                  if (frame == 9 && !dead){ 
                        move.insert(move.begin(),dir); 
                        for (int i=0; i < snake.size(); i++){
                              switch(move.at(i)){
                                    case 1: if (snake.at(i).x < (win.r.width/size)-2) snake.at(i).x++; 
                                          else{ dead=true; i=snake.size();} break;
                                    case 2: 
                                          if (snake.at(i).y < (win.r.length/size)-3) snake.at(i).y++; 
                                          else{ dead=true; i=snake.size();} break;
                                    case 3: if (snake.at(i).x) snake.at(i).x--; 
                                          else{ dead=true; i=snake.size();} break;
                                    case 0:
                                          if (snake.at(i).y) snake.at(i).y--; 
                                          else{ dead=true; i=snake.size();} break;
                              }
                        } frame=0;
                  }
                  for (int y=0; y < snake.size(); y++){ 
                        for (int x=0; x < snake.size(); x++){
                              if (snake.at(x).x == snake.at(y).x && snake.at(x).y == snake.at(y).y && x != y) dead=true;
                        }
                  }
                  if (apple.x == snake.at(0).x && apple.y == snake.at(0).y){ 
                        switch (move.at(snake.size()-1)){
                              case 1: snake.insert(snake.end(),{snake.at(snake.size()-1).x-1,snake.at(snake.size()-1).y}); break;
                              case 2: snake.insert(snake.end(),{snake.at(snake.size()-1).x,snake.at(snake.size()-1).y-1}); break;
                              case 3: snake.insert(snake.end(),{snake.at(snake.size()-1).x+1,snake.at(snake.size()-1).y}); break;
                              case 0: snake.insert(snake.end(),{snake.at(snake.size()-1).x,snake.at(snake.size()-1).y+1}); break;
                              default: break;
                        }
                        do apple = {rand() % ((win.r.length/size)-1) , rand() % (( win.r.width/size)-2)}; while (inSnake(apple));
                        points++;
                  }
                  RSGL::drawRect({350,0,25,25},{255,0,0});
                  RSGL::drawText(": " + std::to_string(points),{380,0,25},"/usr/share/fonts/TTF/DejaVuSans-Bold.ttf",{255,255,255});
            } else{ RSGL::drawRect({380,0,25,25},{255,0,0}); RSGL::drawText("AI",{380,0,25},"/usr/share/fonts/TTF/DejaVuSans-Bold.ttf",{255,240,0}); }
            for (int y=0; y < map.size(); y++) for (int x=0; x < map.at(y).size(); x++){ 
                  RSGL::color c = {255,255,255};
                  if (apple.x == x && apple.y == y ){c={255,0,0};}
                  for (int i=0; i < snake.size(); i++){
                        if (snake.at(i).x == x && snake.at(i).y == y ){c={0,255,0}; break;}
                  } 
                  RSGL::drawRect(map.at(y).at(x),c); 
            }
            win.clear();
      } win.close();
}