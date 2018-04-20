# Run in docker

Simple and fast setup of Enumivo on Docker is also available.

## Install Dependencies

- [Docker](https://docs.docker.com) Docker 17.05 or higher is required
- [docker-compose](https://docs.docker.com/compose/) version >= 1.10.0

## Docker Requirement

- At least 8GB RAM (Docker -> Preferences -> Advanced -> Memory -> 8GB or above)

## Build eos image

```bash
git clone https://github.com/enumivo/enumivo.git --recursive
cd eos/Docker
docker build . -t enumivo/eos
```

## Start enunode docker container only

```bash
docker run --name enunode -p 8888:8888 -p 9876:9876 -t enumivo/eos enunoded.sh arg1 arg2
```

By default, all data is persisted in a docker volume. It can be deleted if the data is outdated or corrupted:

```bash
$ docker inspect --format '{{ range .Mounts }}{{ .Name }} {{ end }}' enunode
fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
$ docker volume rm fdc265730a4f697346fa8b078c176e315b959e79365fc9cbd11f090ea0cb5cbc
```

Alternately, you can directly mount host directory into the container

```bash
docker run --name enunode -v /path-to-data-dir:/opt/enumivo/bin/data-dir -p 8888:8888 -p 9876:9876 -t enumivo/eos enunoded.sh arg1 arg2
```

## Get chain info

```bash
curl http://127.0.0.1:8888/v1/chain/get_info
```

## Start both enunode and enuwallet containers

```bash
docker volume create --name=enunode-data-volume
docker volume create --name=enuwallet-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `enunoded` and `enuwallet` will be started. enunode service would expose ports 8888 and 9876 to the host. enuwallet service does not expose any port to the host, it is only accessible to enucli when runing enucli is running inside the enuwallet container as described in "Execute enucli commands" section.

### Execute enucli commands

You can run the `enucli` commands via a bash alias.

```bash
alias enucli='docker-compose exec enuwallet /opt/enumivo/bin/enucli -H enunoded'
enucli get info
enucli get account inita
```

Upload sample exchange contract

```bash
enucli set contract exchange contracts/exchange/exchange.wast contracts/exchange/exchange.abi
```

If you don't need enuwallet afterwards, you can stop the enuwallet service using

```bash
docker-compose stop enuwallet
```

### Change default configuration

You can use docker compose override file to change the default configurations. For example, create an alternate config file `config2.ini` and a `docker-compose.override.yml` with the following content.

```yaml
version: "2"

services:
  enunode:
    volumes:
      - enunode-data-volume:/opt/enumivo/bin/data-dir
      - ./config2.ini:/opt/enumivo/bin/data-dir/config.ini
```

Then restart your docker containers as follows:

```bash
docker-compose down
docker-compose up
```

### Clear data-dir

The data volume created by docker-compose can be deleted as follows:

```bash
docker volume rm enunode-data-volume
docker volume rm enuwallet-data-volume
```

### Docker Hub

Docker Hub image available from [docker hub](https://hub.docker.com/r/enumivo/eos/).
Replace the `docker-compose.yaml` file with the content below

```bash
version: "3"

services:
  enunoded:
    image: enumivo/eos:latest
    command: /opt/enumivo/bin/enunoded.sh
    hostname: enunoded
    ports:
      - 8888:8888
      - 9876:9876
    expose:
      - "8888"
    volumes:
      - nodeos-data-volume:/opt/enumivo/bin/data-dir

  enuwallet:
    image: enumivo/eos:latest
    command: /opt/enumivo/bin/enuwallet
    hostname: enuwallet
    links:
      - enunoded
    volumes:
      - enuwallet-data-volume:/opt/enumivo/bin/data-dir

volumes:
  nodeos-data-volume:
  enuwallet-data-volume:

```

*NOTE:* the defalut version is the latest, you can change it to what you want

run `docker pull enumivo/eos:latest` 

run `docker-compose up`

### Dawn3.0 Testnet

We can easliy set up a dawn3.0 local testnet using docker images. Just run the following commands:

```
# pull images
docker pull enumivo/enumivo:dawn3x
# create volume
docker volume create --name=nodeos-data-volume
docker volume create --name=enuwallet-data-volume
# start containers
docker-compose -f docker-compose-dawn3.0.yaml up -d
# get chain info
curl http://127.0.0.1:8888/v1/chain/get_info
# get logs
docker-compose logs enunoded
```

The `blocks` data are stored under `--data-dir` by default, and the wallet files are stored under `--wallet-dir` by default, of course you can change these as you want.
