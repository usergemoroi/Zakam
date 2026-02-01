#include "soundPlayer.hpp"
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <dirent.h>
#include "ImGui/imgui.h"

void AudioPlayer::playerCallback(SLPlayItf player, void* context, SLuint32 event) {
    if (event == SL_PLAYEVENT_HEADATEND) {
        AudioPlayer* audioPlayer = static_cast<AudioPlayer*>(context);
        if (audioPlayer) {
            audioPlayer->isPlaying = false;
            if (audioPlayer->playbackCompleteCallback) {
                audioPlayer->playbackCompleteCallback();
            }
        }
    }
}

std::string AudioPlayer::getFileNameWithoutExt(const std::string& filename) {
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != std::string::npos) {
        return filename.substr(0, lastDot);
    }
    return filename;
}

bool AudioPlayer::createSoundsDirectory() {
    struct stat st = { 0 };

    if (stat("/sdcard/luminate", &st) == -1) {
        mkdir("/sdcard/luminate", 0777);
    }

    if (stat(SOUNDS_DIR.c_str(), &st) == -1) {
        return mkdir(SOUNDS_DIR.c_str(), 0777) == 0;
    }

    return true;
}

std::string AudioPlayer::getFullPath(const std::string& filename) {
    // Сначала ищем .mp3, если нет — пробуем .wav
    std::string mp3Path = SOUNDS_DIR + "/" + filename + ".mp3";
    std::string wavPath = SOUNDS_DIR + "/" + filename + ".wav";

    if (fileExists(mp3Path)) {
        return "file://" + mp3Path;
    }
    else if (fileExists(wavPath)) {
        return "file://" + wavPath;
    }

    return ""; // файла нет
}

void AudioPlayer::updateSoundsList() {
    soundNames.clear();

    // Проверяем каталог
    DIR* dir = opendir(SOUNDS_DIR.c_str());
    if (!dir) {
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;

        if (filename == "." || filename == "..") continue;
        if (filename.length() < 4) continue;

        std::string ext = filename.substr(filename.length() - 4);
        for (auto& c : ext) c = std::tolower(c);

        if (ext == ".mp3" || ext == ".wav") {
            soundNames.push_back(getFileNameWithoutExt(filename));
        }
    }

    closedir(dir);

    if (soundNames.empty()) {
        selectedSound = 0;
    }
    else if (selectedSound >= soundNames.size()) {
        selectedSound = soundNames.size() - 1;
    }
}

bool AudioPlayer::init() {
    if (!createSoundsDirectory()) {
        return false;
    }

    updateSoundsList();

    slCreateEngine(&engineObject, 0, nullptr, 0, nullptr, nullptr);
    (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);

    const SLInterfaceID ids[] = {};
    const SLboolean req[] = {};
    (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, ids, req);
    (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);

    return true;
}

bool AudioPlayer::playSelectedSound() {
    if (selectedSound < 0 || selectedSound >= soundNames.size()) {
        return false;
    }
    return playAudio(soundNames[selectedSound]);
}

void AudioPlayer::stopPlayback() {
    if (playerPlay != nullptr && isPlaying) {
        (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED);
        isPlaying = false;
    }
}

void AudioPlayer::setSelectedSound(int index) {
    if (index >= 0 && index < soundNames.size())
        selectedSound = index;
}

bool AudioPlayer::hasSounds() const {
    return !soundNames.empty();
}

const std::vector<std::string>& AudioPlayer::getSoundNames() const {
    return soundNames;
}

bool AudioPlayer::playAudio(const std::string& filename) {
    if (isPlaying) {
        stopPlayback();
    }

    if (playerObject != nullptr) {
        (*playerObject)->Destroy(playerObject);
        playerObject = nullptr;
        playerPlay = nullptr;
        playerSeek = nullptr;
    }

    std::string fullPath = getFullPath(filename);
    if (fullPath.empty()) return false;

    SLDataLocator_URI loc_uri = { SL_DATALOCATOR_URI, (SLchar*)fullPath.c_str() };
    SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
    SLDataSource audioSrc = { &loc_uri, &format_mime };

    SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObject };
    SLDataSink audioSnk = { &loc_outmix, NULL };

    const SLInterfaceID ids[2] = { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean req[2] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

    SLresult result = (*engineEngine)->CreateAudioPlayer(engineEngine, &playerObject,
        &audioSrc, &audioSnk,
        2, ids, req);

    if (result != SL_RESULT_SUCCESS) return false;

    (*playerObject)->Realize(playerObject, SL_BOOLEAN_FALSE);
    (*playerObject)->GetInterface(playerObject, SL_IID_PLAY, &playerPlay);
    (*playerObject)->GetInterface(playerObject, SL_IID_SEEK, &playerSeek);

    (*playerPlay)->RegisterCallback(playerPlay, playerCallback, this);
    (*playerPlay)->SetCallbackEventsMask(playerPlay, SL_PLAYEVENT_HEADATEND);

    (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING);
    isPlaying = true;

    return true;
}

void AudioPlayer::cleanup() {
    if (isPlaying && playerPlay != nullptr) {
        (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED);
        isPlaying = false;
    }

    if (playerObject != nullptr) {
        (*playerObject)->Destroy(playerObject);
        playerObject = nullptr;
        playerPlay = nullptr;
        playerSeek = nullptr;
    }

    if (outputMixObject != nullptr) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = nullptr;
    }

    if (engineObject != nullptr) {
        (*engineObject)->Destroy(engineObject);
        engineObject = nullptr;
        engineEngine = nullptr;
    }
}

AudioPlayer::~AudioPlayer() {
    cleanup();
}

bool AudioPlayer::fileExists(const std::string& filepath) {
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}

AudioPlayer g_HitSound;