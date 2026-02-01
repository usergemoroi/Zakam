#pragma once
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include <vector>
#include <functional>

class AudioPlayer {
private:
    SLObjectItf engineObject;
    SLEngineItf engineEngine;
    SLObjectItf outputMixObject;
    SLObjectItf playerObject;
    SLPlayItf playerPlay;
    SLSeekItf playerSeek;
    SLPlaybackRateItf playerRate;
    
    std::vector<std::string> soundNames;
    int selectedSound = 0;
    const std::string SOUNDS_DIR = "/sdcard/luminate/sounds";
    
    bool isPlaying;
    std::function<void()> playbackCompleteCallback;
    
    static void playerCallback(SLPlayItf player, void* context, SLuint32 event);
    
    bool createSoundsDirectory();
    std::string getFullPath(const std::string& filename);
    std::string getFileNameWithoutExt(const std::string& filename);
    bool fileExists(const std::string& filepath);

public:
    AudioPlayer() : engineObject(nullptr), engineEngine(nullptr), 
                   outputMixObject(nullptr), playerObject(nullptr),
                   playerPlay(nullptr), playerSeek(nullptr), playerRate(nullptr),
                   isPlaying(false) {}
    
    ~AudioPlayer();

    bool init();
    bool playAudio(const std::string& filename);
    void cleanup();
    void updateSoundsList();
    bool playSelectedSound();
    void stopPlayback();
    bool isCurrentlyPlaying() const { return isPlaying; }
    void setSelectedSound(int index);
    bool hasSounds() const;
    const std::vector<std::string>& getSoundNames() const;
    int getSelectedSound() const { return selectedSound; }
    const char* getSelectedSoundName() const { 
        return soundNames.empty() ? "No sounds" : soundNames[selectedSound].c_str(); 
    }
};

extern AudioPlayer g_HitSound;