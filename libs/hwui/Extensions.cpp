/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Extensions.h"

#include "Debug.h"
#include "Properties.h"
#include "utils/StringUtils.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <utils/Log.h>

namespace android {
namespace uirenderer {

// Debug
#if DEBUG_EXTENSIONS
    #define EXT_LOGD(...) ALOGD(__VA_ARGS__)
#else
    #define EXT_LOGD(...)
#endif


Extensions::Extensions() {
    auto extensions = StringUtils::split((const char*) glGetString(GL_EXTENSIONS));
    mHasNPot = extensions.has("GL_OES_texture_npot");
    mHasFramebufferFetch = extensions.has("GL_NV_shader_framebuffer_fetch");
    mHasDiscardFramebuffer = extensions.has("GL_EXT_discard_framebuffer");
    mHasDebugMarker = extensions.has("GL_EXT_debug_marker");
    mHas1BitStencil = extensions.has("GL_OES_stencil1");
    mHas4BitStencil = extensions.has("GL_OES_stencil4");
    mHasUnpackSubImage = extensions.has("GL_EXT_unpack_subimage");

    const char* version = (const char*) glGetString(GL_VERSION);

    // Section 6.1.5 of the OpenGL ES specification indicates the GL version
    // string strictly follows this format:
    //
    // OpenGL<space>ES<space><version number><space><vendor-specific information>
    //
    // In addition section 6.1.5 describes the version number thusly:
    //
    // "The version number is either of the form major number.minor number or
    // major number.minor number.release number, where the numbers all have one
    // or more digits. The release number and vendor specific information are
    // optional."

    if (sscanf(version, "OpenGL ES %d.%d", &mVersionMajor, &mVersionMinor) != 2) {
        // If we cannot parse the version number, assume OpenGL ES 2.0
        mVersionMajor = 2;
        mVersionMinor = 0;
    }
}

}; // namespace uirenderer
}; // namespace android
