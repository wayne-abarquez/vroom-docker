## VROOM Docker

This repository contains dockerized [Vehicle Routing Open-source Optimization Machine (VROOM)](https://github.com/VROOM-Project/vroom)

This project highly inspired and inherited from [chesty's](https://github.com/chesty/vroom-docker) dockerized vroom.

## Usage

Just modify the `config.js` file as you wish and build the image. The image builds [**vroom-backend (core)**](https://github.com/VROOM-Project/vroom) and exposes [**vroom-express API**](https://github.com/VROOM-Project/vroom-express) through port `3000` by default. You should modify `config.js` file especially to specify **route profiles** indicated by `var routingServers`.

### Compose File
---
See the gist [here](https://gist.github.com/iedmrc/51d02fefa9e3ee91a5608c02c452c965) for the "*`docker-compose` file stack*" I created.