// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may
// not use these files except in compliance with the License. You may obtain
// a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

namespace canvas
{
    class MockCanvasImageSourceDrawingSessionFactory : public ICanvasImageSourceDrawingSessionFactory
    {
    public:
        std::function<ComPtr<ICanvasDrawingSession>(ISurfaceImageSourceNativeWithD2D*, const Rect&, float dpi)> MockCreate;

        virtual ComPtr<ICanvasDrawingSession> Create(
            ISurfaceImageSourceNativeWithD2D* sisNative,
            const Rect& updateRect,
            float dpi) const override
        {
            if (!MockCreate)
            {
                Assert::Fail(L"Unexpected call to Create");
                ThrowHR(E_NOTIMPL);
            }

            return MockCreate(sisNative, updateRect, dpi);
        }
    };
}
