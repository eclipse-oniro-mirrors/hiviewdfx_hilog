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
#ifndef HIVIEWDFX_NAPI_VAL
#define HIVIEWDFX_NAPI_VAL

#pragma once

#include <memory>
#include <vector>
#include "uni_header.h"

namespace OHOS {
namespace HiviewDFX {
class NVal final {
public:
    NVal() = default;

    NVal(napi_env nEnv, napi_value nVal);

    NVal &operator=(const NVal &) = default;

    virtual ~NVal() = default;

    // NOTE! env_ and val_ is LIKELY to be null
    napi_env env_ = nullptr;
    napi_value val_ = nullptr;

    explicit operator bool() const;

    bool TypeIs(napi_valuetype expType) const;

    bool ValueTypeIs(napi_value value, napi_valuetype expType) const;

    /* SHOULD ONLY BE USED FOR EXPECTED TYPE */
    std::tuple<bool, std::unique_ptr<char[]>, size_t> ToUTF8String() const;

    std::tuple<bool, std::unique_ptr<char[]>, size_t> ToUTF16String() const;

    std::tuple<bool, void *> ToPointer() const;

    std::tuple<bool, bool> ToBool() const;

    std::tuple<bool, double> ToDouble() const;

    std::tuple<bool, int32_t> ToInt32() const;

    std::tuple<bool, int64_t> ToInt64() const;

    std::tuple<bool, void *, size_t> ToArraybuffer() const;

    std::tuple<bool, napi_typedarray_type, void *, size_t> ToTypedArray() const;

    std::tuple<bool, bool> IsTypeArray() const;

    std::tuple<bool, void *, size_t> ToDataview() const;

    std::tuple<bool, bool> IsArray() const;

    std::tuple<bool, void *, size_t, size_t, napi_typedarray_type> ToTypedArrayInfo() const;

    std::tuple<bool, std::string> GetValObjectAsStr() const;

    /* Static helpers to create js objects */
    static NVal CreateUndefined(napi_env env);

    static NVal CreateNull(napi_env env);

    static NVal CreateInt64(napi_env env, int64_t val);

    static NVal CreateObject(napi_env env);

    static NVal CreateBool(napi_env env, bool val);

    static NVal CreateUTF8String(napi_env env, std::string str);

    static NVal CreateUint8Array(napi_env env, void *buf, size_t bufLen);

    static NVal CreateDouble(napi_env env, double val);

    /* SHOULD ONLY BE USED FOR OBJECT */
    bool HasProp(std::string propName) const;

    NVal GetProp(std::string propName) const;

    bool AddProp(std::vector<napi_property_descriptor> &&propVec) const;

    bool AddProp(std::string propName, napi_value nVal) const;

    /* Static helpers to create prop of js objects */
    static napi_property_descriptor DeclareNapiProperty(const char *name, napi_value val);

    static napi_property_descriptor DeclareNapiStaticProperty(const char *name, napi_value val);

    static napi_property_descriptor DeclareNapiFunction(const char *name, napi_callback func);

    static napi_property_descriptor DeclareNapiStaticFunction(const char *name, napi_callback func);

    static napi_property_descriptor DeclareNapiGetter(const char *name, napi_callback getter);

    static napi_property_descriptor DeclareNapiSetter(const char *name, napi_callback setter);

    static inline napi_property_descriptor DeclareNapiGetterSetter(const char *name,
        napi_callback getter, napi_callback setter);
private:
    std::string GetPrintString(napi_value value) const;
};
} // namespace HiviewDFX
} // namespace OHOS

#endif // HIVIEWDFX_NAPI_VAL