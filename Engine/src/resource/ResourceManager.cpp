#include "ResourceManager.h"
#include <functional>
#include "TextResource.h"

namespace Ghurund {
    Status ResourceManager::loadInternal(Resource & resource, ResourceContext & context, const String & fileName, LoadOption options) {
        Status result = resource.load(*this, context, fileName, nullptr, options);
        if(result!=Status::OK) {
            Logger::log(_T("failed to load file: %s\n"), fileName.getData());
            return result;
        }

        if(hotReloadEnabled&&!(options&LoadOption::DONT_WATCH)) {
            watcher.addFile(fileName, [this, &resource, &context](const String &fileName, FileChange fileChange) {
                if(fileChange==FileChange::MODIFIED) {
                    section.enter();
                    bool found = false;
                    for(size_t i = 0; i<reloadQueue.Size; i++) {
                        if(reloadQueue[i]->Resource.FileName==resource.FileName) {
                            found = true;
                            break;
                        }
                    }
                    if(!found) {
                        resource.Valid = false;
                        reloadQueue.add(ghnew ReloadTask(*this, context, resource));
                    }
                    section.leave();
                }
            });
        }
        add(resource);

        return Status::OK;
    }

    ResourceManager::ResourceManager() {
        loadingThread.start();
    }

    ResourceManager::~ResourceManager() {
        loadingThread.finish();
        delete resourceFactory;

#ifdef _DEBUG
        PointerList<Resource*> unreleasedResources;
#endif

        for(size_t i = 0; i<resources.Size; i++) {
            Resource *resource = resources.getValue(i);
#ifdef _DEBUG
            if(resource->ReferenceCount>1)
                unreleasedResources.add(resource);
#endif
            resource->release();
        }

#ifdef _DEBUG
        for(size_t i = 0; i<unreleasedResources.Size; i++) {
            Resource *resource = unreleasedResources[i];
            if(resource->ReferenceCount>1)
                Logger::log(_T("unreleased ResourceManager resource: [%#x] %hs %s refCount=%lu\n"), (int)resource, typeid(*resource).name(), resource->FileName.getData(), resource->ReferenceCount);
            while(resource->ReferenceCount>1)
                resource->release();
#endif
        }
    }

    void ResourceManager::reload() {
        section.enter();
        for(size_t i = 0; i<reloadQueue.Size; i++) {
            ReloadTask *task = reloadQueue.get(i);
            task->execute();    // TODO: try to reload in place
            delete task;
        }
        reloadQueue.clear();
        section.leave();
    }

    Status ResourceManager::save(Resource & resource, SaveOption options) {
        return resource.save(*this, options);
    }

    Status ResourceManager::save(Resource & resource, const String & fileName, SaveOption options) {
        if(resource.FileName.Empty) {
            Logger::log(_T("The file name is empty\n"));
            return Status::INV_PARAM;
        } else {
            return resource.save(*this, fileName, options);
        }
    }

    Status ResourceManager::save(Resource & resource, File & file, SaveOption options) {
        if(file.Name.Empty) {
            Logger::log(_T("The file's name is empty\n"));
            return Status::INV_PARAM;
        } else {
            return resource.save(*this, file, options);
        }
    }

    Status ResourceManager::save(Resource & resource, MemoryOutputStream & stream, SaveOption options) {
        resourceFactory->describeResource(resource, stream);
        if(resource.FileName.Empty) {
            stream.writeBoolean(true);  // full binary
            return resource.save(*this, stream, options);
        } else {
            stream.writeBoolean(false); // file reference
            stream.writeUnicode(resource.FileName);
            Status result = resource.save(*this, resource.FileName, options);
            if(options&SaveOption::SKIP_IF_EXISTS&&result==Status::FILE_EXISTS)
                return Status::OK;
            return result;
        }
    }

    Resource * ResourceManager::get(const String & fileName) {
        section.enter();
        Resource *resource = nullptr;
        size_t index = resources.findKey(fileName);
        if(index!=resources.Size)
            resource = resources.getValue(index);
        section.leave();
        return resource;
    }

    void ResourceManager::add(Resource & resource) {
        section.enter();
        resources.set(resource.FileName, &resource);
        section.leave();
    }

    void ResourceManager::remove(const String & fileName) {
        section.enter();
        resources.remove(fileName);
        section.leave();
    }

    void ResourceManager::clear() {
        section.enter();
        resources.clear();
        section.leave();
    }
}