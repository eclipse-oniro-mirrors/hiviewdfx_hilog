/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HILOG_DATA_H
#define HILOG_DATA_H

#include <cstring>
#include <iostream>
#include <securec.h>

#include <hilog/log.h>
#include <hilog_common.h>

namespace OHOS {
namespace HiviewDFX {
struct HilogData {
    uint16_t len; /* tag length plus fmt length include '\0' */
    uint16_t version : 3;
    uint16_t type : 3;  /* APP,CORE,INIT,SEC etc */
    uint16_t level : 4;
    uint16_t tagLen : 6; /* include '\0' */
    uint32_t tv_sec;
    uint32_t tv_nsec;
    uint32_t mono_sec;
    uint32_t pid;
    uint32_t tid;
    uint32_t domain;
    char* tag;
    char* content;

    void Init(const char *mtag, uint16_t mtagLen, const char *mfmt, size_t mfmtLen)
    {
        if (unlikely(mtagLen > MAX_TAG_LEN || mtagLen == 0 || mfmtLen > MAX_LOG_LEN || mfmtLen <= 0)) {
            return;
        }

        len = mtagLen + mfmtLen;
        char* tmp = new (std::nothrow) char[len];
        if (unlikely(tmp == nullptr)) {
            return;
        }
        tag = tmp;
        content = tmp + mtagLen;
        if (strncpy_s(tag, mtagLen + 1, mtag, mtagLen - 1)) {
            return;
        }
        if (strncpy_s(content, mfmtLen + 1, mfmt, mfmtLen - 1)) {
            return;
        }
    }

    HilogData() : len(0), tag(nullptr), content(nullptr) {}
    explicit HilogData(const HilogMsg& msg)
        : len(0), version(msg.version), type(msg.type), level(msg.level), tagLen(msg.tagLen),
        tv_sec(msg.tv_sec), tv_nsec(msg.tv_nsec), mono_sec(msg.mono_sec), pid(msg.pid), tid(msg.tid),
        domain(msg.domain), tag(nullptr), content(nullptr)
    {
        Init(msg.tag, msg.tagLen, CONTENT_PTR((&msg)), CONTENT_LEN((&msg)));
    }

    HilogData(const HilogData& copy)
    {
        if (unlikely(memcpy_s(this, sizeof(HilogData), &copy, sizeof(HilogData)) != 0)) {
            std::cerr << "HilogData copy error." << std::endl;
        }
        tag = new (std::nothrow) char[len];
        if (unlikely(tag == nullptr)) {
            return;
        }
        if (unlikely(memcpy_s(tag, len, copy.tag, len) != 0)) {
            return;
        }
        content = tag + tagLen;
    }

    HilogData& operator=(const HilogData&) = delete;

    HilogData(HilogData&&) = delete;

    ~HilogData()
    {
        delete []tag;
        tag = nullptr;
        content = nullptr;
    }
};
} // namespace HiviewDFX
} // namespace OHOS
#endif /* HILOG_DATA_H */
