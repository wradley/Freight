#include "SandboxApp.hpp"
using namespace Microsoft::WRL;

namespace FR8
{
    Error* SandboxApp::start()
    {
        FR8_DBG_LOG("Starting sandbox application");

#ifndef NDEBUG
        {
            FR8_DBG_LOG("Creating debug layer");
            ComPtr<ID3D12Debug> debugController;
            FR8_ASSERT(
                SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))), 
                "Could not create debug layer"
            );
            debugController->EnableDebugLayer();
        }
#endif

        FR8_DBG_LOG("Creating device");
        FR8_ASSERT(
            SUCCEEDED(D3D12CreateDevice(
                nullptr,
                D3D_FEATURE_LEVEL_12_1, 
                IID_PPV_ARGS(&mDevice))
            ), 
            "Could not create device"
        );

        FR8_ASSERT(
            SUCCEEDED(mDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence))),
            "Could not create fence"
        );

        mRtvDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        mDsvDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
        mCbvSrvUavDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

        return nullptr;
    }


    Error* SandboxApp::update()
    {
        FR8_DBG_LOG("Update sandbox application");
        return nullptr;
    }


    Error* SandboxApp::stop()
    {
        FR8_DBG_LOG("Stopping sandbox application");
        return nullptr;
    }


    Error* SandboxApp::resize()
    {
        return nullptr;
    }
};