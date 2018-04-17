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
``` bash
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

## Start both enunode and keosd containers

```bash
docker volume create --name=enunode-data-volume
docker volume create --name=keosd-data-volume
docker-compose up -d
```

After `docker-compose up -d`, two services named `enunoded` and `keosd` will be started. enunode service would expose ports 8888 and 9876 to the host. keosd service does not expose any port to the host, it is only accessible to enucli when runing enucli is running inside the keosd container as described in "Execute enucli commands" section.


### Execute enucli commands

You can run the `enucli` commands via a bash alias.

```bash
alias enucli='docker-compose exec keosd /opt/enumivo/bin/enucli -H enunoded'
enucli get info
enucli get account inita
```

Upload sample exchange contract

```bash
enucli set contract exchange contracts/exchange/exchange.wast contracts/exchange/exchange.abi
```

If you don't need keosd afterwards, you can stop the keosd service using

```bash
docker-compose stop keosd
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
docker volume rm keosd-data-volume
```
