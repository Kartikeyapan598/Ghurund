#pragma once

#include "Audio.h"
#include "core/collection/Array.h"
#include "core/collection/List.h"
#include "core/resource/Resource.h"

namespace Ghurund::Audio {
    enum class PlaybackState {
        STOPPED, PAUSED, PLAYING
    };

    class Sound: public Resource {
    private:
        IXAudio2SourceVoice* sourceVoice;
        WAVEFORMATEX* waveFormat;
        unsigned int waveFormatLength;
        List<BYTE> audioData;
        XAUDIO2_BUFFER audioBuffer;
        PlaybackState state = PlaybackState::STOPPED;

        Status setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status loadData(MemoryInputStream& stream, LoadOption options);

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;

        virtual unsigned int getVersion() const {
            return 0;
        }

        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ~Sound() {
            sourceVoice->DestroyVoice();
        }

        Status play();

        Status stop() {
            if (state == PlaybackState::STOPPED)
                return Status::INV_STATE;

            if (isPlaying())
                sourceVoice->Stop();
            if (state != PlaybackState::STOPPED) {
                sourceVoice->FlushSourceBuffers();
                state = PlaybackState::STOPPED;
                return Status::OK;
            }
            return Status::CALL_FAIL;
        }

        inline Status pause() {
            if (state != PlaybackState::PLAYING)
                return Status::INV_STATE;

            sourceVoice->Stop();
            state = PlaybackState::PAUSED;
            return Status::OK;
        }

        inline bool isPlaying() const {
            return state == PlaybackState::PLAYING;
        }

        __declspec(property(get = isPlaying)) bool Playing;

        inline float getPosition() const {
            XAUDIO2_VOICE_STATE voiceState;
            sourceVoice->GetState(&voiceState, 0);
            return (float)voiceState.SamplesPlayed / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getPosition)) float Position;

        inline float getLength() const {
            return ((float)(audioData.Size) / (waveFormat->wBitsPerSample * waveFormat->nChannels / 8)) / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getLength)) float Length;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"wav", true, false)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}