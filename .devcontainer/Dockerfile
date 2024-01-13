FROM mcr.microsoft.com/devcontainers/cpp:debian

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && curl -sSL https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb -o /tmp/chrome.deb \
    && apt-get -y install /tmp/chrome.deb
RUN wget https://github.com/Heroic-Games-Launcher/HeroicGamesLauncher/releases/tag/v2.12.0/heroic_2.12.0_amd64.deb \
    && sudo dpkg -i 