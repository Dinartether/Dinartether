#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

DINTD=${DINTD:-$SRCDIR/dinartetherd}
DINTCLI=${DINTCLI:-$SRCDIR/dinartether-cli}
DINTTX=${DINTTX:-$SRCDIR/dinartether-tx}
DINTQT=${DINTQT:-$SRCDIR/qt/dinartether-qt}

[ ! -x $DINTD ] && echo "$DINTD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
DINTVER=($($DINTCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for dinartetherd if --version-string is not set,
# but has different outcomes for dinartether-qt and dinartether-cli.
echo "[COPYRIGHT]" > footer.h2m
$DINTD --version | sed -n '1!p' >> footer.h2m

for cmd in $DINTD $DINTCLI $DINTTX $DINTQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${DINTVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${DINTVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
