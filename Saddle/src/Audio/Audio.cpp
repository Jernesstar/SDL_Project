#include "Audio.h"

void Audio::Init(AudioSpecification specs)
{
    Mix_OpenAudio(specs.Frequency, specs.Format, specs.ChannelCount, specs.ChunckSize);
}

void Audio::SetChannelVolume(int channel, Uint8 volume)
{
    m_Channels[channel] = volume;
    if(volume > AUDIO_MAX_VOLUME)
        m_Channels[channel] = AUDIO_MAX_VOLUME;
    else if(volume < AUDIO_MIN_VOLUME)
        m_Channels[channel] = AUDIO_MIN_VOLUME;

    Mix_Volume(channel, m_Channels[channel]);
}

void Audio::IncreaseChannelVolume(int channel, Uint8 delta)
{
    if(m_Channels.find(channel) == m_Channels.end()) // Channel is not yet in the map
        m_Channels[channel] = AUDIO_MAX_VOLUME;

    SetChannelVolume(channel, m_Channels[channel] + delta);
}

void Audio::DecreaseChannelVolume(int channel, Uint8 delta)
{
    if(m_Channels.find(channel) == m_Channels.end()) // Channel is not yet in the map
        m_Channels[channel] = AUDIO_MAX_VOLUME;

    SetChannelVolume(channel, m_Channels[channel] - delta);
}