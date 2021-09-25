#pragma once

namespace Ghurund::Core {
    enum class Status {
        OK, INV_PARAM, INV_STATE, CALL_FAIL, IO, NOT_IMPLEMENTED, ALREADY_LOADED, UNKNOWN,
        
        UNKNOWN_TYPE, MISSING_ALLOCATOR, MISSING_CONSTRUCTOR,

        WRONG_RESOURCE_VERSION,
        WRONG_RESOURCE_TYPE,
        LOADER_MISSING,
        FILE_DOESNT_EXIST,
        FILE_EXISTS,
        FILE_EMPTY,
        INV_PATH,
        UNKNOWN_FORMAT,
        INV_FORMAT,
        UNEXPECTED_EOF,
        NOT_SUPPORTED,

        ENTRY_POINT_NOT_FOUND,
        COMPILATION_ERROR,
        SCRIPT_EXCEPTION,

        DIRECTX12_NOT_SUPPORTED,
        DEVICE_LOST,

        SOCKET,
        INV_PACKET,
        CONNECTION_REJECTED,
        DISCONNECTED
    };
}