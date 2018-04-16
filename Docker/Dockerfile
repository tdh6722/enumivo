FROM enumivo/builder as builder

RUN git clone -b master --depth 1 https://github.com/enumivo/enumivo.git --recursive \
    && cd eos \
    && cmake -H. -B"/tmp/build" -GNinja -DCMAKE_BUILD_TYPE=Release -DWASM_ROOT=/opt/wasm -DCMAKE_CXX_COMPILER=clang++ \
       -DCMAKE_C_COMPILER=clang -DCMAKE_INSTALL_PREFIX=/tmp/build  -DSecp256k1_ROOT_DIR=/usr/local -DBUILD_MONGO_DB_PLUGIN=true \
    && cmake --build /tmp/build --target install


FROM ubuntu:16.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/lib/* /usr/local/lib/
COPY --from=builder /tmp/build/bin /opt/enumivo/bin
COPY --from=builder /tmp/build/contracts /contracts
COPY --from=builder /eos/Docker/config.ini /
COPY nodeosd.sh /opt/enumivo/bin/nodeosd.sh
ENV ENUMIVO_ROOT=/opt/enumivo
RUN chmod +x /opt/enumivo/bin/nodeosd.sh
ENV LD_LIBRARY_PATH /usr/local/lib
VOLUME /opt/enumivo/bin/data-dir
ENV PATH /opt/enumivo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
