#include "Fence.h"
#include "Graphics.h"

namespace Ghurund {
    Status Fence::init(ID3D12Device *device) {
        if(FAILED(device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)))) {
            Logger::log(_T("device->CreateFence() failed\n"));
            return Status::CALL_FAIL;
        }
        fenceValue++;

        // Create an event handle to use for frame synchronization.
        fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if(fenceEvent == nullptr) {
            if(FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
                Logger::log(_T("HRESULT_FROM_WIN32() failed\n"));
                return Status::CALL_FAIL;
            }
        }

        return Status::OK;
    }

    Status Fence::wait(ID3D12CommandQueue * commandQueue) {
        // Schedule a Signal command in the queue.
        if(FAILED(commandQueue->Signal(fence.Get(), fenceValue))) {
            Logger::log(_T("commandQueue->Signal() failed\n"));
            return Status::CALL_FAIL;
        }

        // Wait until the fence has been processed.
        if(FAILED(fence->SetEventOnCompletion(fenceValue, fenceEvent))) {
            Logger::log(_T("fence->SetEventOnCompletion() failed\n"));
            return Status::CALL_FAIL;
        }
        WaitForSingleObjectEx(fenceEvent, INFINITE, FALSE);

        // Increment the fence value for the current frame.
        fenceValue++;

        return Status::OK;
    }
}