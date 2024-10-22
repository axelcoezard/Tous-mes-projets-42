FROM frrouting/frr:latest

COPY	./vtysh.conf /etc/frr/vtysh.conf
COPY	./daemons /etc/frr/daemons

# 179: Standard port for the BGP protocol.
# 2601: Port used by the zebra daemon.
# 2605: Port used by the ospfd daemon.
# 2606: Port used by the bgpd daemon.
# 2607: Port used by the isisd daemon.
# 2608: Port used by the ripd daemon.

EXPOSE 179 2601 2605 2606 2607 2608

