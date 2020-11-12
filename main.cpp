/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include <unistd.h>

#include "rtspplayer.h"
#include "glib_tools.h"

GMainLoop *gMainLoop = 0;
int gPipefd[2];

void rtMainLoopCb(void*)
{
    rtError err = rtRemoteProcessSingleItem();
    if(err != RT_OK && err != RT_ERROR_QUEUE_EMPTY)
        rtLogInfo("rtRemote ProcessSingle Item returned %d", err);
}

void rtRemoteCallback(void*)
{
    static char temp[1];
    int ret = HANDLE_EINTR_EAGAIN(write(gPipefd[PIPE_WRITE], temp, 1));
    if (ret == -1)
        perror("can't write to pipe");
}

void log_init() {
    int level = RT_LOG_FATAL;
    char* opt = getenv("RTSP_PLAYER_LOG_LEVEL");
    if(opt != NULL)
        level = atoi(opt);

    rtLogSetLevel(static_cast<rtLogLevel>(level));
}

int main(int argc, char *argv[]) {

    log_init();

    rtLogInfo("Init rtRemote");

    rtError rc;
    gMainLoop = g_main_loop_new(0, FALSE);

    auto *source = pipe_source_new(gPipefd, rtMainLoopCb, nullptr);
    g_source_attach(source, g_main_loop_get_context(gMainLoop));

    rtRemoteRegisterQueueReadyHandler( rtEnvironmentGetGlobal(), rtRemoteCallback, nullptr );
    rc = rtRemoteInit();
    assert(rc == RT_OK);

    const char* objectName = getenv("RTSP_PLAYER_CLIENT_NAME");
    if (!objectName) objectName = "rtspplayer";
    rtLogInfo("Register: %s", objectName);
    rtObjectRef playerRef = new RTSPPlayer;

    rc = rtRemoteRegisterObject(objectName, playerRef);
    assert(rc == RT_OK);
    {
      rtLogInfo("Start main loop");
      g_main_loop_run(gMainLoop);
      g_main_loop_unref(gMainLoop);
      gMainLoop = 0;
    }

    delete playerRef;
    playerRef = nullptr;

    rtLogInfo("Shutdown");
    rc = rtRemoteShutdown();
    assert(rc == RT_OK);

    g_source_unref(source);

    return 0;
}
