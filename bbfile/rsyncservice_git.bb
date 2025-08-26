SUMMARY = "Rsyn App: Rsyn App"
DESCRIPTION = "Rsyn App"
HOMEPAGE = "https://github.com/abhilashraju/rsyncservice"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=340bb8e2a52d3a51b4914913110967a7"
DEPENDS = " \
    boost \
    systemd \
    sdeventplus \
    coroserver"

SRC_URI = "git://github.com/abhilashraju/rsyncservice.git;branch=master;protocol=https"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit systemd
inherit pkgconfig meson

EXTRA_OEMESON = " \
    --buildtype=minsize \
"

# Specify the source directory
S = "${WORKDIR}/git"

# Specify the installation directory
bindir = "/usr/bin"
FILES:${PN} += "/usr/bin/rsyncservice"

