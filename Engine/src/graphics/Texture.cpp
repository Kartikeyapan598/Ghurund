#include "Texture.h"

namespace Ghurund {
    const List<ResourceFormat> Texture::formats = {ResourceFormat::AUTO, ResourceFormat::JPG};
  
    Status Texture::init(Graphics &graphics, ID3D12GraphicsCommandList *commandList, Image *image) {
		descHandle = graphics.DescriptorAllocator.allocate(graphics, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

        {
            D3D12_RESOURCE_DESC textureDesc = {};
            textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
            textureDesc.Alignment = 0;  // let the driver choose
            textureDesc.Width = image->getWidth();
            textureDesc.Height = image->getHeight();
            textureDesc.DepthOrArraySize = 1;
            textureDesc.MipLevels = 1;
            textureDesc.Format = image->getFormat();
            textureDesc.SampleDesc.Count = 1;
            textureDesc.SampleDesc.Quality = 0;
            textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;  // let the driver choose
            textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

            if(FAILED(graphics.getDevice()->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                D3D12_HEAP_FLAG_NONE,
                &textureDesc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&textureResource)))) {
                Logger::log(_T("graphics->getDevice()->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            const UINT64 uploadBufferSize = GetRequiredIntermediateSize(textureResource.Get(), 0, 1);

            if(FAILED((graphics.getDevice()->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&textureUploadHeap))))) {
                Logger::log(_T("graphics->getDevice()->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            D3D12_SUBRESOURCE_DATA textureData = {};
            textureData.pData = image->getData();
            textureData.RowPitch = image->getWidth() * image->getPixelSize();
            textureData.SlicePitch = textureData.RowPitch * image->getHeight();

            UpdateSubresources(commandList, textureResource.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
            commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(textureResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

            D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc.Format = textureDesc.Format;
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = 1;
            graphics.getDevice()->CreateShaderResourceView(textureResource.Get(), &srvDesc, descHandle.getCpuHandle());
        }

        return Status::OK;
    }
}