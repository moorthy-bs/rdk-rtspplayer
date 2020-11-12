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
#include "rtspplayer.h"

rtDefineObject    (RTSPPlayer, rtObject);

rtDefineProperty  (RTSPPlayer, url);

rtDefineMethod    (RTSPPlayer, play);
rtDefineMethod    (RTSPPlayer, pause);
rtDefineMethod    (RTSPPlayer, stop);

RTSPPlayer::RTSPPlayer() {
    m_URL = "";
}

RTSPPlayer::~RTSPPlayer() {
}

void RTSPPlayer::onInit()
{
    rtLogInfo("%s\n", __PRETTY_FUNCTION__);
}

rtError RTSPPlayer::getCurrentURL(rtString& s) const
{
    s = m_URL.c_str();
    return RT_OK;
}

rtError RTSPPlayer::setCurrentURL(rtString const& s)
{
    m_URL = s.cString();

    return RT_OK;
}

rtError RTSPPlayer::play(const rtString& s) {
    return RT_OK;
}

rtError RTSPPlayer::pause() {
    return RT_OK;
}

rtError RTSPPlayer::stop() {
    return RT_OK;
}
