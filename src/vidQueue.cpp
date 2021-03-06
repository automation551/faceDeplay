/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "vidQueue.h"
#include "ofxDirList.h"

void vidQueue::init(int w, int h){
  
  ofxDirList dir; 
  
  dir.allowExt("mov"); 
  dir.allowExt("mp4"); 
  dir.allowExt("avi");
  
  int numFiles = dir.listDir("data/");
 
  for(int i = 0; i < numFiles; i++){
    videoFilenames.push_back(dir.getName(i));
  }
  
  width = w; 
  height = h; 
  
}


void vidQueue::pushRandom(){
  if(videoFilenames.size() < 1)
    return;
  
  int idx = ofRandom(0, videoFilenames.size() - 1);
  ofVideoPlayer *player = new ofVideoPlayer(); 
  player->loadMovie(videoFilenames[idx]);
  player->setUseTexture(true);
  player->setLoopState(OF_LOOP_PALINDROME);
  player->setVolume(100);
  player->play();
  players.push_back(player); 
}


void vidQueue::popRandom(){
  if(players.size() < 1)
    return ;
  
  ofVideoPlayer * p = players.back();
  p->close();
  delete p;
  players.pop_back();
  
}

void vidQueue::update(){
  for(int i = 0; i < players.size(); i++){
    players[i]->update();
  } 
}

void vidQueue::draw(){
  draw(width, height);
}

void vidQueue::draw(int w, int h){
    ofSetColor(0xFFFFFF);

  if ( players.size() == 1 ){
    players[0]->draw(0, 0, w, h); 
    
  }
  if (players.size() == 2){
    players[0]->draw(0, 0, w/2, h/2); 
    players[1]->draw(w/2, h/2, w/2, h/2); 
    
  }
 if (players.size() == 3){
    
    players[0]->draw(0, 0, w/2, h/2); 
    players[1]->draw(w/2, h/2, w/2, h/2); 
    players[2]->draw(w/2, 0, w/2, h/2); 
    
  }

 if (players.size() == 4){
    
    players[0]->draw(0, 0, w/2, h/2); 
    players[1]->draw(w/2, h/2, w/2, h/2); 
    players[2]->draw(w/2, 0, w/2, h/2); 
    players[3]->draw(0, h/2, w/2, h/2); 
    
  }
  
}
