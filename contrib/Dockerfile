FROM amd64/ubuntu:20.04 AS base

#If you found this docker image helpful please donate DINT to the maintainer
LABEL maintainer="RV9zdNeUTQUToZUcRp9uNF8gwH5LzDFtan"

EXPOSE 12021/tcp
EXPOSE 12022/tcp

ENV DEBIAN_FRONTEND=noninteractive

#Install runtime dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash wget net-tools libminiupnpc17 \
	libevent-2.1 libevent-pthreads-2.1 \
	libboost-system1.71 libboost-filesystem1.71 libboost-chrono1.71 \
	libboost-program-options1.71 libboost-thread1.71 \
	libzmq5 && \
	apt-get clean

FROM base AS build

#Install build dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash net-tools build-essential libtool autotools-dev automake \
	pkg-config libssl-dev libevent-dev bsdmainutils python3 \
	libboost-system1.71-dev libboost-filesystem1.71-dev libboost-chrono1.71-dev \
	libboost-program-options1.71-dev libboost-test1.71-dev libboost-thread1.71-dev \
	libzmq3-dev libminiupnpc-dev && \
	apt-get clean

#Copy source dir
COPY . /home/dinartether/build/Dinartether/
WORKDIR /home/dinartether/build/Dinartether

#build db4 from source
WORKDIR /home/dinartether/build/Dinartether/contrib
RUN ./install_db4.sh ../../

# build Dinartethercore
WORKDIR /home/dinartether/build/Dinartether
RUN ./autogen.sh && ./configure --disable-tests BDB_LIBS="-L/home/dinartether/build/db4/lib -ldb_cxx-4.8" BDB_CFLAGS="-I/home/dinartether/build/db4/include" --with-gui=no  && make -j4

FROM base AS final

#Add our service account user
RUN useradd -ms /bin/bash dinartether && \
	mkdir /var/lib/dinartether && \
	chown dinartether:dinartether /var/lib/dinartether && \
	ln -s /var/lib/dinartether /home/dinartether/.dinartether && \
	chown -h dinartether:dinartether /home/dinartether/.dinartether

VOLUME /var/lib/dinartether

#Copy the compiled binaries from the build
COPY --from=build /home/dinartether/build/Dinartether/src/dinartetherd /usr/local/bin/dinartetherd
COPY --from=build /home/dinartether/build/Dinartether/src/dinartether-cli /usr/local/bin/dinartether-cli

WORKDIR /home/dinartether
USER dinartether

CMD /usr/local/bin/dinartetherd -datadir=/var/lib/dinartether -printtoconsole -onlynet=ipv4
