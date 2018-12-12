#pragma once

#include "Fence.h"
#include "core/Logger.h"
#include "Graphics.h"
#include "core/NamedObject.h"
#include "collection/PointerList.h"

namespace Ghurund {
    class Shader;

    enum class CommandListState {
        INVALID,
        RECORDING,  // can be closed
        CLOSED, // executing, can be waited for
        FINISHED    // can be only reset
    };

    class CommandList: public NamedObject, public Pointer {
    private:
        Fence fence;
        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
        ID3D12CommandQueue *commandQueue = nullptr;
        CommandListState state = CommandListState::INVALID;

        ID3D12PipelineState *pipelineState = nullptr;
        ID3D12RootSignature *rootSignature = nullptr;

        List<ID3D12Object*> resourceRefs;

    public:

        CommandList() {
#ifdef _DEBUG
            Name = _T("unnamed CommandList");
#endif
        }

        ~CommandList();

        Status init(Graphics &graphics, ID3D12CommandQueue *queue);

        Status wait();

        Status reset();

        Status finish();

        inline ID3D12GraphicsCommandList *get() {
            return commandList.Get();
        }

        inline CommandListState getState() {
            return state;
        }

        __declspec(property(get = getState)) CommandListState State;

        virtual void setName(const String &name) override {
            NamedObject::setName(name);
            commandList->SetName(name);
        }

        void setPipelineState(ID3D12PipelineState *pipelineState);

        void setGraphicsRootSignature(ID3D12RootSignature *rootSignature);

        virtual const Ghurund::Type &getType() const override {
            return Type::COMMAND_LIST;
        }

        void addResourceRef(ID3D12Object *resource) {
            resource->AddRef();
            resourceRefs.add(resource);
        }
    };
}