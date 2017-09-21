#include <stdio.h>
#include "app/capp.h"
#include "core/cstring.h"
#include "core/cmemory.h"
#include "app/cmixer.h"

int fps;
void onDisplay(CObject* context, CObject* args) {
  CApp* appObj = (CApp*)context;
  //
  // clear screen
  glClearColor(1.0, 0.7, 0.7, 1.0);//rgba
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  //
  // redisplay and update screen buffer
  capp_postRedisplay(appObj);
  capp_flushBuffers(appObj);

  //
  // fps check
  if(fps != appObj->fps) {
    fps = appObj->fps;
    printf("fps:%d;\r\n",fps);
  }
}

int main(int argc, char** argv) {
  printf("call main \r\n");
  //
  // call mixer
  // mixer is singlton
  CMixer* mixer = getCMixer();
  CMixerMusic* music1 = cmixer_createMusic(mixer, "examples/assets/se_maoudamashii_element_thunder05.ogg");
  cmixer_playMusic(mixer, music1, -1);

  //
  // create app
  CApp* appObj = createCApp(300, 300);
  capp_addDisplayEventListener(appObj, (CObject*)appObj , onDisplay);
  capp_run(appObj);
  return 0;
}
