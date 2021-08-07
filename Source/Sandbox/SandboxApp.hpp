#pragma once
#include "Freight/Freight.hpp"
#include "Freight/Log.hpp"

#include <d3d12.h>
#include <d3d12sdklayers.h>
#include <wrl.h>

namespace FR8
{
    class SandboxApp : public Freight
    {
    public:

        Error* start();
        Error* update();
        Error* stop();

    private:

        Error* resize();

        Microsoft::WRL::ComPtr<ID3D12Device> mDevice;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCmdQ;
        Microsoft::WRL::ComPtr<ID3D12Fence> mFence;

        UINT mRtvDescriptorSize;
        UINT mDsvDescriptorSize;
        UINT mCbvSrvUavDescriptorSize;

    };
};