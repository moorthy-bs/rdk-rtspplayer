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

#ifndef RDK_RTSP_MEDIAPLAYER
#define RDK_RTSP_MEDIAPLAYER

#include <cassert>

#include <rtRemote.h>
#include <rtError.h>
#include <rtLog.h>

class RTSPPlayer : public rtObject {

public:
    rtDeclareObject(RTSPPlayer, rtObject);

    rtProperty(url, getCurrentURL, setCurrentURL, rtString);

    rtMethod1ArgAndNoReturn  ("play", play, rtString);
    rtMethodNoArgAndNoReturn ("stop", stop);
    rtMethodNoArgAndNoReturn ("pause", pause);

    RTSPPlayer();
    virtual ~RTSPPlayer();

    virtual void onInit();

    /* Properties */
    rtError getCurrentURL (rtString& s) const;
    rtError setCurrentURL (rtString const& s);

    /* methods */
    rtError play(const rtString& s);
    rtError stop();
    rtError pause();

private:
    std::string m_URL;
};

#endif
