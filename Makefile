# Warning: you may need more libraries than are included here on the
# build line.  The agent frequently needs various libraries in order
# to compile pieces of it, but is OS dependent and we can't list all
# the combinations here.  Instead, look at the libraries that were
# used when linking the snmpd master agent and copy those to this file.

CC = gcc
GCC = yes

OBJECTS = pgstatmibd.o pgstatDatabaseTable.o pgstatBgWriter.o
TARGETS = pgstatmibd

CFLAGS = -I. `net-snmp-config --cflags` `pg_config --cflags`
BUILDLIBS = `net-snmp-config --libs` `pg_config --libs`
BUILDAGENTLIBS = `net-snmp-config --agent-libs`

# Net-SNMP sources (or libsnmp-dev package)
#NS_SRC = /usr/src/net-snmp-5.7

# PostgreSQL sources (or libpq-dev package)
#PG_SRC = /usr/src/postgresql-8.3.8/src
#PG_SRC = /usr/src/postgresql-9.0.0/src

#override CFLAGS := -I$(NS_SRC)/include $(CFLAGS)
#override BUILDAGENTLIBS := -L$(NS_SRC)/agent/.libs -lnetsnmpmibs -lnetsnmpagent -lnetsnmphelpers \
#	-L$(NS_SRC)/snmplib/.libs -lnetsnmp $(BUILDAGENTLIBS)

# shared library flags (assumes gcc)
#DLFLAGS = -fPIC -shared

#CFLAGS += -O2 -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -fno-strict-aliasing -fwrapv

CPPFLAGS = -I`pg_config --includedir`
#CPPFLAGS += -I/usr/local/pgsql/include
#CPPFLAGS += -I$(PG_SRC)/interfaces/libpq -I$(PG_SRC)/include

LDLIBS = -lpq
#LDLIBS += -L/usr/local/pgsql/lib -lpq
#LDLIBS += -L$(PG_SRC)/interfaces/libpq -lpq

all: $(TARGETS)

pgstatmibd: $(OBJECTS)
	$(CC) -o pgstatmibd $(OBJECTS) $(BUILDAGENTLIBS) $(LDLIBS)

#pgstatDatabaseTable.o: pgstatDatabaseTable.c pgstatDatabaseTable.h

clean:
	rm $(OBJECTS) $(TARGETS)

start-agent:
	sudo ./pgstatmibd

test-client:
	MIBDIRS="+." MIBS=ALL snmpwalk localhost pgStatMIB
